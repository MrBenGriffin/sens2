<?php //SCHOOL INDEPENDENT (used for schools management).
mb_internal_encoding('UTF-8');
class School {
    use Form;
    const SIG = "class-school";
    public static function sig() {
        return static::SIG;
    }
    function __construct($key = NULL) {
        $v = new NView('view-school_1.ixml');
        $this->iniForm($key, $v, false, "id", false);
        $this->key   = $key;
        $this->table = "school";
        $this->setfld('name');
        $this->setfld('address');
        $this->setfld('city');
        $this->setfld('postcode');
        $this->setfld('telephone');
        $this->setfld('active');
    }
    public function validate() {
        $this->valSignificant('name', Dict::get('errors_name_significant'));
        $this->valUnique('name', Dict::get('errors_name_unique'));
     }
    public function populate() {
        $this->vset('name');
        $this->vset('address');
        $this->vset('city');
        $this->vset('postcode');
        $this->vset('telephone');
        $this->vset('active', 'cb');
    }
    public function postcommit() {
        $id=intval($this->newid);
        $qry="insert into settings set school=".$id.",name='current_cal'";
        Settings::$sql->query($qry);
    }
    public static function listing($qs = 'a', $url = '') {
        $v = NULL;
        if (Sec::ok(Sec::SCHOOLSM)) {
            $v  = new NView('view-school-list.ixml');
            $rt = new NView($v->consume("//h:ul/h:li"));
            if ($rx = Settings::$sql->query("select id,name,active from school order by active desc,name")) {
                while ($f = $rx->fetch_assoc()) {
                    $r = new NView($rt);
                    if($f['active']!=='on') { $r->set("//h:a/@class"); }
                    $r->set("//h:a/child-gap()", $f['name']);
                    $r->set("//h:a/@href/child-gap()", $url . '?' . $qs . '=' . $f['id']);
                    $v->set("//h:ul/child-gap()", $r);
                }
                $rx->close();
            }
            $v->set("//*[@data-xp='new']/@href", $url . '?' . $qs . '=NULL');
            $v->set("//h:ul/child-gap()", $rt);
        }
        return $v;
    }
    public static function edit($id = NULL, $url = '') {
        $v = NULL;
        if (!is_null($id) && Sec::ok(Sec::SCHOOLSM)) {
            $v     = new NView('view-school-edit.ixml');
            $h     = $v->consume("//*[@data-xp='user']");
            $form  = new School(intval($id));
            $form->insert_qs = "i=[[ID]]";
            $v->set("//*[@data-xp='form']", $form->form(true));
            if ( is_null($id) && $form->success() ) {
                $form->postcommit();
            }
            $v->set("//*[@data-xp='back']/@href", $url);
            if ($rx = Settings::$sql->query("select u.id,u.active,p.firstname,p.familyname,r.name from sio_user u,sio_userprofile p,sio_role r where p.role=r.id and p.user=u.id and p.school=" . intval($id) . " order by r.name,familyname")) {
                while ($f = $rx->fetch_assoc()) {
                    $user = new NView($h);
                    if($f['active']!=='on') {$user->set("//h:a/@class");}
                    $user->set("//h:a/@href/child-gap()", $f['id']);
                    $user->set("//*[@data-xp='firstname']", $f['firstname']);
                    $user->set("//*[@data-xp='familyname']", $f['familyname']);
                    $user->set("//*[@data-xp='role']", $f['name']);
                    $v->set("//*[@data-xp='users']/child-gap()", $user);
                }
                $rx->close();
            }
        }
        return $v;
    }
}
