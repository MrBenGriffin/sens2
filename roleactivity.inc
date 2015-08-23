<?php //Sec::ROLEMGMT ;SCHOOL INDEPENDENT
    mb_internal_encoding('UTF-8');
class RoleActivity {
        use Form;
        const SIG = "class-roleactivity";
        public static function sig() { return static::SIG; }
        function __construct($ra_key=array('role'=>NULL,'activity'=>NULL),$activity='unknown activity') {
            $v=new NView('view-roleactivity_1.ixml');
            $this->iniForm($ra_key['activity'],$v,false,$ra_key,false);
            $this->key=$ra_key['activity'];	//role changes across the formlet instances.
            $this->table="sio_roleactivities";
            $this->setsub('used');
            $this->rname=$activity;
        }

        public function populate() {
            $this->view->set("//*[@data-xp='label']/h:span",$this->rname);
            $this->vset('used','cb'); //
        }

        public static function listing($qs='role',$url='') {
            $v = NULL;
            if (Sec::ok(Sec::ROLEMGMT)) {
                $v=new NView('view-roleactivity-rolelist.ixml');
                $rt=$v->consume("//h:ul/h:li");
                if ($rx = Settings::$sql->query("select id,name from sio_role where active='on' order by name")) {
                    while ($f = $rx->fetch_assoc()) {
                        $r=new NView($rt);
                        $r->set("//h:a/child-gap()",$f['name']);
                        $r->set("//h:a/@href/child-gap()",$url.'?'.$qs.'='.$f['id']);
                        $v->set("//h:ul/child-gap()",$r);
                    }
                    $rx->close();
                }
            }
            return $v;
        }

    public static function edit($id=NULL,$url='') {
        $v = NULL;
        if (!is_null($id) && Sec::ok(Sec::ROLEMGMT)) {
            $v=new NView('view-roleactivity-activitylist.ixml');
            $v->set("//h:a[@data-xp='back']/@href",$url);
            $qry="select name from role where id=".$id;
            if ($rx = Settings::$sql->query($qry)) {
                while ($f = $rx->fetch_assoc()) {
                    $v->set("//*[@data-xp='role']/child-gap()",$f['name']);
                }
                $rx->close();
            }
            if ($rx = Settings::$sql->query("select id,name from sio_activity where active='on' order by name")) {
                while ($f = $rx->fetch_assoc()) {
                    $form=new RoleActivity(array('role'=>$id,'activity'=>$f['id']),$f['name']);
                    $v->set("//*[@data-xp='form']/child-gap()",$form->form(true));
                }
                $rx->close();
            }
        }
        return $v;
    }

}
