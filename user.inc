<?php //SCHOOL DEPENDENT
mb_internal_encoding('UTF-8');
class User {
    use Form;
    const SIG = "class-user";
    public static function sig() { return static::SIG; }
    function __construct($qs=NULL) {
        $v=new NView('view-user_1.ixml');
        $this->iniForm(NULL,$v,false,"id",false);
            $this->key=NULL;	//this form only handles new users.
            $this->table="sio_user";
            $this->setfld('active',"'on'","'on'");
            $this->setfld('username');
            $this->setfld('email');
            $this->setfld('passwordn','','!skip');
            $this->setfld('passwordb','','!skip');
            $this->insert_qs=$qs; //query string for new records. id placeholder = [[ID]]
    }
    public function validate() {
        $sisig="sioreg_";
        $retval = true;
        //force lowercase.
        if (isset($this->fields['username'][0])) {
            $this->fields['username'][0]=mb_strtolower($this->fields['username'][0]);
        }
        $this->valUnique('username', Dict::get('errors_name_unique'));
        if (isset($this->fields['email'][0])) {
            $em=Settings::esc($this->fields['email'][0]);
            $qry="select count(id) as ok from " . $this->table . " where emailp='" . $em . "' or email='" . $em . "'";
            if ($rx = Settings::$sql->query($qry)) {
                if (strcmp($rx->fetch_row()[0],"0") !== 0) {
                    $retval = false;
                    $this->seterr("email",Dict::get($sisig.'errors_email_exists'));
                }
                $rx->close();
            }
            if (isset($this->fields['passwordn'][0]) && ($this->fields['passwordn'][0] === $this->fields['email'][0])) {
                $this->seterr("passwordn",Dict::get($sisig.'errors_new_pw_too_em_simple'));
                $retval = false;
            }
        } else {
            $this->seterr("email",Dict::get($sisig.'errors_no_email'));
            $retval = false;
        }
        if (isset($this->fields['passwordn'][0]) && isset($this->fields['passwordb'][0])) {
            $pwa=$this->fields['passwordn'][0];
            $pwb=$this->fields['passwordb'][0];
            if ($pwa !== $pwb ) {
                $this->seterr("passwordn",Dict::get($sisig.'errors_new_pw_different'));
                $retval = false;
            }
            if (strlen($pwa) < 7) {
                $this->seterr("passwordn",Dict::get($sisig.'errors_new_pw_too_short'));
                $retval = false;
            }
        } else {
            $this->seterr("passwordn",Dict::get($sisig.'errors_no_password'));
            $retval = false;
        }
        $this->valEmail('email',Dict::get($sisig .'errors_email_badformat'));
        if ($this->valid) {
            $this->valid = $retval;
        }
    }

    public function populate() {
        $this->vset('username');
        $this->vset('email');
    }

    public function postcommit() {
        $id=intval($this->newid);
        $pw=$this->fields['passwordn'][0];
        $unm=$this->fields['username'][0];
        $ph=SIOSetPW::enhash($unm,$this->fields['passwordn'][0]);
        $qry="update sio_user set password='".$ph."' where id=".$id;
        Settings::$sql->query($qry);
        $qry="insert into sio_userprofile set user=".$id.",school=".Settings::$usr['school'].",role=".Sec::ROLE_UNASSIGNED.",firstname='(new user)',familyname='".$this->fields['email'][0]."'";
        Settings::$sql->query($qry);
    }

    public static function listing($qs='u',$url='',$restricted=true) {
        $v = NULL;
        if (Sec::ok(Sec::USERMGMT)) {
            $v=new NView('view-userrole-userlistusr.ixml');
            $rt=$v->consume("//h:ul/h:li");
            if( $restricted ){
                $rlim=" and r.cat=1";
            } else {
                $rlim="";
            }
            $qry="select u.id,concat (p.firstname,' ',p.familyname,' (',r.name,')') as name from sio_user u,sio_userprofile p,sio_role r where ".Sec::schsql('school','p')." and p.user=u.id and p.role=r.id ".$rlim." and u.active='on' order by r.name,p.familyname";
            if ($rx = Settings::$sql->query($qry)) {
                while ($f = $rx->fetch_assoc()) {
                    $r=new NView($rt);
                    $r->set("//h:a/child-gap()",$f['name']);
                    $r->set("//h:a/@href/child-gap()",$url.'?'.$qs.'='.$f['id']);
                    $v->set("//h:ul/child-gap()",$r);
                }
                $rx->close();
            }
            $v->set("//*[@data-xp='new']/@href",$url.'?'.$qs.'=NULL');
            $v->set("//h:ul/child-gap()",$rt);
        }
        return $v;
    }

    public static function newuser($qs='u',$url='') {
        $v = NULL;
        if (Sec::ok(Sec::USERMGMT)) {
            $v=new NView('view-userrole-usernewusr.ixml');
            $v->set("//h:a[@data-xp='back']/@href",$url);
            $user=new User($qs);
            $v->set("//*[@data-xp='user']/child-gap()",$user->form(true));
            if ( $user->success() ) {
                $user->postcommit();
            }
        }
        return $v;
    }

}
