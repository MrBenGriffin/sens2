<?php //Sec::SETTINGS
mb_internal_encoding('UTF-8');
require_once("basis.php");
require_once("sen.inc");
$v=new NView('view-do-terms_1.ixml');
$pgfn= function() use (&$v) {
    if(!empty(Settings::$qst['t'])) {
        $v->set("//*[@data-xp='term']",Term::edit(intval(Settings::$qst['t']),'/do-terms.php'));
    } else {
        $v->set("//*[@data-xp='term']",Term::listing('t','/do-terms.php'));
    }
}; //does nothing.
SEN::page($pgfn,$v,Sec::SETTINGS);
