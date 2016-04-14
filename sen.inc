<?php //
mb_internal_encoding('UTF-8');
ini_set('error_reporting',0x7FFF);

require_once("cci/c.ixml");
require_once("cla/c.ixml");
require_once("coh/c.ixml");
require_once("int/c.ixml");
require_once("int/ca.ixml"); //additional class.
require_once("ovr/c.ixml");
require_once("pve/c.ixml");
require_once("sen/c.ixml");
require_once("set/c.ixml");
require_once("stt/c.ixml");

//VIEW TABLE DEFINITIONS ARE AT THE BOTTOM OF THIS FILE.

SEN::init();
class SEN {
    static function init() {
        Dict::setln(array('en'));
    }
    static function name($id) {
        $name='unknown';
        if ($rx = Settings::$sql->query("select name from userv where school=".Settings::$usr['school']." and user='". intval($id) ."'")) {
            while ($f = $rx->fetch_assoc()) {
                $name=$f['name'];
            }
            $rx->close();
        }
        return $name;
    }
    static function user() {
        if(isset(Settings::$usr['role'])) {
        	$uid = intval(Settings::$usr['ID']); //for local query injection.
			$rol = intval(Settings::$usr['role']); //for local query injection.
			$sch = intval(Settings::$usr['school']); //for local query injection.

            Settings::$usr['ccid']=0;
            Settings::$usr['ccst']=0;
            Settings::$usr['CLA']=0;
            Settings::$usr['COH']=0;
            Settings::$usr['PRV']=0;
            if ($rx = Settings::$sql->query("select class,cohort from classv where active='on' and school='$sch' and teacher='$uid'")) {
                while ($row = $rx->fetch_assoc()) {
                    Settings::$usr['CLA']=$row['class'];
                    Settings::$usr['COH']=$row['cohort'];
                }
                $rx->close();
            }
            if ($rx = Settings::$sql->query("select role from sio_roleactivities r where r.role='$rol' and r.activity=".Sec::CANPROVI)) {
                while ($row = $rx->fetch_assoc()) {
                    Settings::$usr['PRV'] = 1; //ie, this is someone who can offer provisions (beyond their own class).
                }
                $rx->close();
            }
            if ($rx = Settings::$sql->query("select c.id,v.name as calendar,term from calendar c,calv v,setting s where s.name='current_cal' and s.school='$sch' and s.value=c.id and c.id=v.cal")) {
                while ($row = $rx->fetch_assoc()) {
                    Settings::$usr['ccid'] = $row['id'];
                    Settings::$usr['ccst'] = $row['calendar'];
                    Settings::$usr['term'] = $row['term'];
                }
                $rx->close();
            }
        }
    }
    static function fnFooter() {
        $n = new NView("view-common-footer.ixml");
        $n->set("//*[@data-xp='usr']/child-gap()",Settings::$usr['username']);
        $n->set("//*[@data-xp='cal']/child-gap()",Settings::$usr['ccst']);
        return $n;
    }
    static function page(&$fn,$v,$activity=0,$sio=false) {
     	ini_set('error_reporting',0x7FFF);
        $mv = new NView("view-common.ixml");
        $sio_views=array();
        $sio_views['sioreg_']=__DIR__ .'/sio-reg.ixml';
        if($sio) {
            $sio_views['sioreg_success']=__DIR__ .'/sio-regsuccess.ixml';
            $sio_views['sio_']= __DIR__ . '/sio-form.ixml';
        } else {
            $sio_views['siosignin_']= __DIR__ .'/sio-signin.ixml';
            $sio_views['siosignout_']= __DIR__ .'/sio-signout.ixml';
        }
        $sio_translations = array("en"=>array('download'=>"Download",'view'=>"View",));
        Sio::initialise(true,$sio_views,$sio_translations);
        if (!$sio) {
            $mv->set("//*[@data-xp='sio']",Sio::run());
        }
        if($sio || Session::has('username')) {
            Sec::user(); //set user activities.
            self::user(); //set additional user data.
            if (isset(Settings::$usr['school'])) {
                if ($rx = Settings::$sql->query("select name from school where id=".Settings::$usr['school'])) {
                    while ($f = $rx->fetch_assoc()) {
                        $mv->set("//*[@data-xp='site_title']/child-gap()",": " . $f['name']);
                   }
                   $rx->close();
                }
                $mv->set("//h:footer/child-gap()",SEN::fnFooter());
            }
            if ($sio || Sec::ok($activity)) { //
                $fn();
                $mv->set("//*[@data-xp='disallowed']");
                $mv->set("//*[@data-xp='main_view']",$v);
            } else {
                 $mv->set("//*[@data-xp='allowed']");
            }
            if ($sio) {
                Sec::user(); //set user activities again, to drive Nav.
            }
            $mv->set("//*[@data-xp='sio_user']/child-gap()",Session::get('username'));
            $mv->set("//*[@data-xp='sio_user']/@href",'/do-sio.php');
            $mv->set("//*[@data-xp='visitor']");
            $mv->set("//*[@data-xp='sec_nav']/child-gap()",Nav::view());
        } else {
            $mv->set("//*[@data-xp='SecNav']");
            $mv->set("//*[@data-xp='user']");
        }
        echo $mv->show();
        Settings::close();
    }

	public static function calendar_exists($cal=NULL) {
		$retval=false;
		if (is_int(intval($cal)) && ($rr=Settings::$sql->query("select id from calendar where id=" . $cal ))) {
			if ($rr->num_rows == 1) {
				$retval = true;
			}
			$rr->close();
		}
		return $retval;
	}

	public static function calendar_preceding($cal=NULL) {
		$retval=0;
		if (is_int(intval($cal)) && ($rr=Settings::$sql->query("select id from calendar where id < '$cal' order by id desc limit 1"))) {
			if ($rr->num_rows == 1) {
				$retval = $rr->fetch_row()[0];
			}
			$rr->close();
		}
		return $retval;
	}

}

/*
School-aware view definitions for this application
create view classv as select c.id as class,c.school,v.cohort as cohort,u.user as teacher,c.active as active,c.name as name,v.name as cname,v.xname as cxname,v.sort as sort,u.name as tname from class c,cohv v,userv u where c.school=u.school and v.school=c.school and u.user=c.teacher and c.cohort=v.cohort;
create view cohv as select c.id as cohort,c.school,concat(y.name,' ',g.name) as name,concat(y.name,' ',g.name,' (',c.comments,')') as xname,concat(y.id,'.',g.id) as sort from cohort c,year y,gang g where y.id=c.year and g.id=c.gang;
*/
