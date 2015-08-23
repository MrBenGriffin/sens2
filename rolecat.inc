<?php //SCHOOL INDEPENDENT
mb_internal_encoding('UTF-8');
class Rolecat {
    use Form;
    const SIG = "class-rolecat";
    public static function sig() { return static::SIG; }
    function __construct($key=NULL) {
        $v=new NView('view-rolecat_1.ixml');
        $this->iniForm($key,$v,false,"id",false);
        $this->key=$key;	//role changes across the formlet instances.
        $this->table="sio_rolecat";
        $this->setfld('name');
        $this->setfld('active');
    }
    public function validate() {
        $this->valSignificant('name',Dict::get('errors_name_significant'));
            $this->valUnique('name',Dict::get('errors_name_unique'));
    }
    public function populate() {
        $this->vset('name');
        $this->vset('active','cb');
    }

    public static function listing($qs='a',$url='') {
        $v = NULL;
        if (Sec::ok(Sec::ROLEMGMT)) {
            $v=new NView('view-rolecat-list.ixml');
            $rt=new NView($v->consume("//h:ul/h:li"));
            if ($rx = Settings::$sql->query("select id,name,active from sio_rolecat order by active desc,name")) {
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

    public static function edit($id=NULL,$url='',$rurl='') {
        $v = NULL;
        if (!is_null($id) && Sec::ok(Sec::ROLEMGMT)) {
            $v=new NView('view-rolecat-edit.ixml');
            $r=$v->consume("//*[@data-xp='rolelist']/h:li");
            $form=new Rolecat(intval($id));
            $v->set("//*[@data-xp='form']",$form->form(true));
            $v->set("//*[@data-xp='back']/@href",$url);
            if ($rx = Settings::$sql->query("select id,name from sio_role where cat='".$id."' and active='on' order by name")) {
                while ($f = $rx->fetch_assoc()) {
                    $rv=new NView($r);
                    $rv->set("/h:li/h:a/child-gap()",$f['name']);
                    $rv->set("/h:li/h:a/@href",$rurl.$f['id']);
                    $v->set("//*[@data-xp='rolelist']/child-gap()",$rv);
                }
                $rx->close();
            }
        }
        return $v;
    }

}
