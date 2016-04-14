<?php //Sec::UTILITYS
mb_internal_encoding('UTF-8');
require_once("basis.php");
require_once("sen.inc");

$v = new NView();
$pgfn= function() use (&$v) {
    if (!Sec::ok(Sec::ACTIVITY)) {$v->set("//*[@data-xp='ACTIVITY']");}
    if (!Sec::ok(Sec::CLASSMGT)) {$v->set("//*[@data-xp='CLASSMGT']");}
    if (!Sec::ok(Sec::COHORTMG)) {$v->set("//*[@data-xp='COHORTMG']");}
    if (!Sec::ok(Sec::ROLEMGMT)) {$v->set("//*[@data-xp='ROLEMGMT']");}
    if (!Sec::ok(Sec::SCHOOLSM)) {$v->set("//*[@data-xp='SCHOOLSM']");}
    if (!Sec::ok(Sec::SETTINGS)) {$v->set("//*[@data-xp='SETTINGS']");}
    if (!Sec::ok(Sec::STATEMGR)) {$v->set("//*[@data-xp='STATEMGR']");}
    if (!Sec::ok(Sec::USERMGMT)) {$v->set("//*[@data-xp='USERMGMT']");}
};
SEN::page($pgfn,$v,Sec::UTILITYS);
