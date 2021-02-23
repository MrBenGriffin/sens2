<?php //Sec::PROVIDER || Sec::MYPROVIS
mb_internal_encoding('UTF-8');
require_once("basis.php");
require_once("../paths.inc");
require_once("sen.inc");

$v = new NView();
$pgfn= function() use (&$v) {
    $cal = (!empty(Settings::$req[0]) && is_int(intval(Settings::$req[0])) ) ? Settings::$req[0] : Settings::$usr['ccid'];
    $cci = (!empty(Settings::$req[1]) && is_int(intval(Settings::$req[1])) ) ? Settings::$req[1] : 0;
    $coh = (!empty(Settings::$req[2]) && is_int(intval(Settings::$req[2])) ) ? Settings::$req[2] : 0;
    $prv = (!empty(Settings::$req[3]) && is_int(intval(Settings::$req[3])) ) ? Settings::$req[3] : 0;
    switch(count(Settings::$req)) {
        case 2: {
        } break;
        case 3: {
            if(SEN::calendar_exists($cal) && Cohort::exists($coh) && CCI::exists($cci)) {
                $v->set("//*[@data-xp='legend']/child-gap()",CCI::title($cal,$coh));
                $v->set("//*[@data-xp='l']");
                $tx=new Provisions($cal,$cci,$coh);
                $v->set("//*[@data-xp='f']",$tx->form());
            }
        } break;
        case 4: {
            $v->set("//h:section[@data-xp='e']");
            if ( Settings::$usr['PRV'] != 0) { $prv = Settings::$usr['ID']; }
            $v->set("//h:section[@data-xp='l']/child-gap()",Provisions::list_provider_provisions($prv));
            $v->set("//*[@data-xp='title']/child-gap()",SEN::name($prv) .": Provisions");
        } break;
        default:
        case 0: {
            if(Sec::ok(Sec::PROVIDER)) {
                $v->set("//*[@data-xp='title']/child-gap()","Providers");
                $v->set("//h:section[@data-xp='l']/child-gap()",Provisions::listing());
            } elseif (Sec::ok(Sec::MYPROVIS) && Settings::$usr['PRV']) {
                $v->set("//h:section[@data-xp='e']");
                $prv = Settings::$usr['ID'];
                $v->set("//h:section[@data-xp='l']/child-gap()",Provisions::list_provider_provisions($prv));
                $v->set("//*[@data-xp='title']/child-gap()",SEN::name($prv) .": Provisions");
            }
        } break;
    }
};
SEN::page($pgfn,$v,Sec::MYPROVIS);

