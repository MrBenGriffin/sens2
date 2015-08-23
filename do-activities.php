<?php //activity sec::ACTIVITY
mb_internal_encoding('UTF-8');
require_once("basis.iphp");
require_once("sen.inc");

$v=new NView('view-do-activities_1.ixml');
$pgfn= function() use (&$v) {
	if(!empty(Settings::$qst['a'])) {
        $v->set("//*[@data-xp='activity']",Activity::edit(intval(Settings::$qst['a']),'/do-activities.php'));
    } else {
        $v->set("//*[@data-xp='activity']",Activity::listing('a','/do-activities.php'));
    }
};
SEN::page($pgfn,$v,Sec::ACTIVITY);
