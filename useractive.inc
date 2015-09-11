<?php //SCHOOL DEPENDENT
mb_internal_encoding('UTF-8');
class UserActive {
    use Form;
    const SIG = "class-user-active";
    public static function sig() { return static::SIG; }

    function __construct($user=NULL) {
        $v=new NView('view-useractive.ixml');
        $this->iniForm($user,$v,false,"id",false);
            $this->key=$user;
            $this->table="sio_user";
			$this->setboolfld('active',null,null,'on',false);
			$this->setfld('email');
    }

    public function populate() {
        $this->vset('email');
        $this->vset('active','cb');
    }
}
