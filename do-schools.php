<?php //Sec::SCHOOLSM
mb_internal_encoding('UTF-8');
require_once("basis.php");
require_once("sen.inc");
$v=new NView('view-do-schools_1.ixml');
$pgfn= function() use (&$v) {
    if(!empty(Settings::$qst['s'])) {
        $v->set("//*[@data-xp='school']",School::edit(intval(Settings::$qst['s']),'/do-schools.php'));
    } else {
        $v->set("//*[@data-xp='school']",School::listing('s','/do-schools.php'));
    }
};
SEN::page($pgfn,$v,Sec::SCHOOLSM);
