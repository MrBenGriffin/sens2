<?php //SCHOOL INDEPENDENT
mb_internal_encoding('UTF-8');
class Activity {
    use Form;
//go to class sec for security values.
    const SIG = "class-activity";
    public static function sig() {
        return static::SIG;
    }
    function __construct($key = NULL) {
        $v = new NView('view-activity_1.ixml');
        $this->iniForm($key, $v, false, "id", false);
        $this->key   = $key; //role changes across the formlet instances.
        $this->table = "sio_activity";
        $this->setfld('name');
        $this->setfld('code');
        $this->setfld('active');
    }
    public function validate() {
        $this->valSignificant('name', Dict::get('errors_name_significant'));
        $this->valUnique('name', Dict::get('errors_name_unique'));
    }
    public function populate() {
        $this->vset('name');
        $this->vset('code');
        $this->vset('active', 'cb');
    }
    public static function listing($qs = 'a', $url = '') {
        $v = NULL;
        if (Sec::ok(Sec::ACTIVITY)) {
            $v  = new NView('view-activity-list.ixml');
            $rt = $v->consume("//h:ul/h:li");
            if ($rx = Settings::$sql->query("select id,name,active from sio_activity order by active desc,name")) {
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
        }
        return $v;
    }
    public static function edit($id = NULL, $url = '') {
        $v = NULL;
        if (!is_null($id) && Sec::ok(Sec::ACTIVITY)) {
            $v    = new NView('view-activity-edit.ixml');
             $form = new Activity(intval($id));
            $v->set("//*[@data-xp='form']", $form->form(true));
            $v->set("//*[@data-xp='back']/@href", $url);
        }
        return $v;
    }
}
