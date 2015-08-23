<?php //SCHOOL INDEPENDENT
mb_internal_encoding('UTF-8');
class UserRole {
    use Form;
    const SIG = "class-userrole";
    public static function sig() { return static::SIG; }
    function __construct($ur_key=array('user'=>NULL,'role'=>NULL),$role='unknown role') {
        $v=new NView('view-userrole_1.ixml');
        $this->iniForm($ur_key['role'],$v,false,$ur_key,false);
            $this->key=$ur_key['role'];	//role changes across the formlet instances.
            $this->table="sio_userroles";
            $this->setsub('used');
            $this->rname=$role;
    }

    public function populate() {
            $this->view->set("//*[@data-xp='label']/h:span",$this->rname);
            $this->vset('used','cb'); //
    }
}
