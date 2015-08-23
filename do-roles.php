<?php //Sec::ROLEMGMT
mb_internal_encoding('UTF-8');
require_once("basis.iphp");
require_once("sen.inc");
$v=new NView('view-do-roles_1.ixml');
$pgfn= function() use (&$v) {
    if(!empty(Settings::$qst['r'])) {
        $v->set("//*[@data-xp='role']",Role::edit(intval(Settings::$qst['r']),'/do-roles.php'));
    } else {
        $v->set("//*[@data-xp='role']",Role::listing('r','/do-roles.php'));
    }
}; //does nothing.
SEN::page($pgfn,$v,Sec::ROLEMGMT);
