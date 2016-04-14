<?php //
mb_internal_encoding('UTF-8');
require_once("basis.php");
require_once("sen.inc");
$v=new NView('view-do-rolecats_1.ixml');
$pgfn= function() use (&$v) {
    if(!empty(Settings::$qst['r'])) {
        $v->set("//*[@data-xp='rolecat']",Rolecat::edit(intval(Settings::$qst['r']),'/do-rolecats.php','/do-roles.php?r='));
    } else {
        $v->set("//*[@data-xp='rolecat']",Rolecat::listing('r','/do-rolecats.php'));
    }
};
SEN::page($pgfn,$v,Sec::ROLEMGMT);

