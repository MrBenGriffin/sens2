<?php //SCHOOL INDEPENDENT
mb_internal_encoding('UTF-8');
class Role {
    use Form;
//roles set in this app..

    const SIG = "class-role";
    public static function sig() {
        return static::SIG;
    }
    function __construct($key = NULL) {
        $v = new NView('view-role_1.ixml');
        $this->iniForm($key, $v, false, "id", false);
        $this->key   = $key; //role changes across the formlet instances.
        $this->table = "sio_role";
        $this->setfld('name');
        $this->setfld('cat');
        $this->setfld('comment');
        $this->setboolfld('active',null,null,'on',false);
    }
    public function validate() {
        $this->valSignificant('name', Dict::get('errors_name_significant'));
        $this->valUnique('name', Dict::get('errors_name_unique'));
    }
    public function populate() {
        $this->vset('name');
        $this->vsetopts('cat', "select name as prompt,id as value from sio_rolecat where active='on' order by name");
        $this->vset('active', 'cb');
        $this->vset('comment', 'ta');
    }
    public static function listing($qs = 'a', $url = '') {
        $v = NULL;
        if (Sec::ok(Sec::ROLEMGMT)) {
            $v  = new NView('view-role-list.ixml');
            $rt = new NView($v->consume("//h:ul/h:li"));
            if ($rx = Settings::$sql->query("select id,name,active from sio_role order by active desc,name")) {
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
        if (!is_null($id) && Sec::ok(Sec::ROLEMGMT)) {
            $v    = new NView('view-role-edit.ixml');
            $form = new Role(intval($id));
            $v->set("//*[@data-xp='form']", $form->form(true));
            $v->set("//*[@data-xp='back']/@href", $url);
            if (Sec::ok(Sec::ACTIVITY)) {
                if ($rx = Settings::$sql->query("select id,name from sio_activity where active='on' order by name")) {
                    while ($f = $rx->fetch_assoc()) {
                        $form = new RoleActivity(array(
                            'role' => intval($id),
                            'activity' => $f['id']
                        ), $f['name']);
                        $v->set("//*[@data-xp='actedit']/child-gap()", $form->form(true));
                    }
                    $rx->close();
                }
            } else {
                $v->set("//*[@data-xp='actedit']");
            }
        }
        return $v;
    }
}
