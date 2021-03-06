<?php //Sec::CLASSINT
mb_internal_encoding('UTF-8');
require_once("basis.php");
require_once("../paths.inc");
require_once("sen.inc");
$v = new NView();
$pgfn= function() use (&$v) {
    if (!empty(Settings::$req[0]) && (Settings::$req[0] == 'C')) {
        $cal = Settings::$usr['ccid'];
        $coh = Settings::$usr['COH'];
   		if (!empty(Settings::$req[1]) && Sec::ok(Sec::OVERRIDE)) {
       		$coh = Settings::$req[1];
		}
        $cci = 0;
 		//need to check term also. term 1 (Autumn) must not support copyover..
 		$may_copyover = (CCI::outstanding($cal,$coh) === 0) && (((int)Settings::$usr['term']) !== 1);
 		if ($may_copyover) {
            $v->set("//*[@data-xp='copyover']","Copyover should have happened!");
			CCI::copyover($cal,$coh);
		} else {
			$v->set("//*[@data-xp='allowed']","Copyover didn't happen for some reason!");
		}
    } else {
        $cal = (!empty(Settings::$req[0]) && is_int(intval(Settings::$req[0])) ) ? Settings::$req[0] : Settings::$usr['ccid'];
        $cci = (!empty(Settings::$req[1]) && is_int(intval(Settings::$req[1])) ) ? Settings::$req[1] : 0;
        $coh = (!empty(Settings::$req[2]) && is_int(intval(Settings::$req[2])) ) ? Settings::$req[2] : 0;
        if (Settings::$usr['COH'] != 0) { $coh=Settings::$usr['COH']; }
    }
    if(SEN::calendar_exists($cal) && Cohort::exists($coh)) {
		$may_copyover = (CCI::outstanding($cal,$coh) === 0) && (((int)Settings::$usr['term']) !== 1);
		if (Settings::$usr['COH'] === 0) {
 			if (Sec::ok(Sec::OVERRIDE) && $may_copyover) {
				$v->set("//*[@data-xp='copyover']/@href",Settings::$url .="?C&$coh");
			} else {
				$v->set("//*[@data-xp='copyover']");
			}
		}
       	if(Sec::ok(Sec::OVERRIDE) && Settings::$req[1] === 'C' && $may_copyover ) {
			CCI::copyover($cal,$coh);
			$url = str_replace("C","0",$_SERVER["REQUEST_URI"]);
			header("Location: $url");
    	} else {
			$v->set("//*[@data-xp='title']/child-gap()",CCI::title($cal,$coh));
			$v->set("//*[@data-xp='x']");
			if ( CCI::exists($cci) ) { //This is an intervention instance (cci)
				$v->set("//*[@data-xp='l']");
				$tx=new CCI($cci,$coh,$cal);
				$v->set("//*[@data-xp='f']",$tx->form());
			} else {
				$v->set("//*[@data-xp='e']");
				//This may need to offer a copy-over from the previous half-term.
				if ($cal == Settings::$usr['ccid']) { //the current term is valid and in view.
					$c_outstanding=CCI::outstanding($cal,$coh);
					$c_count=CCI::ccicount($cal,$coh);
					if ((!is_null($c_outstanding)) && (!is_null($c_count))) {
						if ($c_outstanding !== 0) { //There are outstanding interventions in it.
					 		$v->set("//*[@data-xp='copyover']"); //remove the 'copyover' option while outstanding.
							$v->set("//*[@data-xp='outlist']/child-gap()",CCI::outlist($cal,$coh));
						} else {
							$v->set("//*[@data-xp='outlist']"); //remove the 'outstanding' error msg.
							if (CCI::ccicount($cal,$coh) !== 0 || !$may_copyover) { //There are some existing interventions
								$v->set("//*[@data-xp='copyover']"); //remove the 'copyover' option
							}
							$v->set("//*[@data-xp='l']/child-gap()",CCI::listing($cal,$coh));
						}
					} else { //odd error
						$v->set("//*[@data-xp='e']");
						$v->set("//*[@data-xp='l']");
					}
				} else {
					 $v->set("//*[@data-xp='copyover']"); //remove the 'copyover' option
					 $v->set("//*[@data-xp='outlist']"); //remove the 'outstanding' error msg.
					 $v->set("//*[@data-xp='l']/child-gap()",CCI::listing($cal,$coh));
				}
			}
        }
    } else { //unrecognised term
    	if (SEN::calendar_exists($cal)) {
    		$ccilink = Settings::$url . "?$cal&amp;0";
    		$cohlist = Cohort::list_as_class($ccilink,"Select class to look at CCIs");
			$v->set("//*[@data-xp='l']",$cohlist);
    	//list cohorts for links to their cci with current calendar..
    	} else {
			$v->set("//*[@data-xp='e']");
			$v->set("//*[@data-xp='l']");
        }
    }
};
SEN::page($pgfn,$v,Sec::CLASSINT);


