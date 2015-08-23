<?php //
mb_internal_encoding('UTF-8');
class UserProfile {
    use Form;
    const SIG = "class-userprofile";
    private $restricted=true;
    public static function sig() { return static::SIG; }
    function __construct($key=NULL,$restricted=true) {
        $v=new NView('view-userprofile_1.ixml');
        $this->iniForm($key,$v,false,"user",false);
            $this->key=$key;	            //this form only handles active users.
            $this->restricted=$restricted;	//self only.
            $this->table="sio_userprofile";
            $this->setfld('school');
            $this->setfld('role');
            $this->setfld('firstname');
            $this->setfld('familyname');
    }

    public function populate() {
        $this->vset('firstname');
        $this->vset('familyname');
        if(Settings::$usr['role'] == Sec::ROLE_DEVELOPER) {
            $this->vsetopts('school',"select name as prompt,id as value from school where active='on' order by prompt");
        } else {
            if($this->restricted) {
                $this->vsetopts('school',"select name as prompt,id as value from school where active='on' and id=".Settings::$usr['school']);
            } else {
                $this->vsetopts('school',"select name as prompt,id as value from school where active='on' order by prompt");
            }
        }
        if(Settings::$usr['role'] == Sec::ROLE_DEVELOPER) {
            $this->vsetopts('role',"select id as value,name as prompt from sio_role where active='on' order by prompt");
        } else {
            if($this->restricted) {
                if (Sec::ok(Sec::USERMGMT)) {
                    $this->vsetopts('role',"select id as value,name as prompt from sio_role where id!='".Sec::ROLE_DEVELOPER."'");
                } else {
                    $this->vsetopts('role',"select id as value,name as prompt from sio_role where id=". Settings::$usr['role']);
                }
            } else {
                $this->vsetopts('role',"select id as value,name as prompt from sio_role where active='on' order by prompt");
            }
        }
    }

	public static function edit($u=NULL,$url=NULL,$restricted=true) {
        $v = NULL;
        if (Sec::ok(Sec::USERMGMT)  || Sec::ok(Sec::SPROFILE) ) {
            if (!Sec::ok(Sec::USERMGMT)) {
                $u = Settings::$usr['ID'];
            }
            if(!is_null($u)) { //existing users only.
                $v=new NView('view-userprofile-edit.ixml');
                if (!empty($url)) {
                    $v->set("//h:a[@data-xp='back']/@href",$url);
                } else {
                    $v->set("//h:a[@data-xp='back']");
                }
                $qry="select username from sio_user where id=".$u;
                if ($rx = Settings::$sql->query($qry)) {
                    while ($f = $rx->fetch_assoc()) {
                        $v->set("//*[@data-xp='title']/child-gap()",$f['username']);
                    }
                    $rx->close();
                }
                $user=new UserProfile($u,$restricted);
                $v->set("//*[@data-xp='user']/child-gap()",$user->form(true));
                if($restricted) { //
                    $qry="select r.id,r.name from sio_role r where r.id !='".Sec::ROLE_DEVELOPER."' and r.active='on' order by r.name";
                } else {
                    $qry="select r.id,r.name from sio_role r where r.active='on' order by r.name";
                }
            }
        }
        return $v;
    }
}
