<?php //Sec::SETTINGS
mb_internal_encoding('UTF-8');
require_once("basis.php");
require_once("../paths.inc");
require_once("sen.inc");

$v = new NView();
$pgfn= function() use (&$v) {
    if (!empty(Settings::$req[0])) {
        $key= Setting::exists(Settings::$req[0]) ? Settings::$req[0] : null;
        $tx=new Setting($key);
        $v->set("//h:section[@data-xp='l']");
        $v->set("//h:fieldset[@data-xp='f']",$tx->form());
    } else {
        $v->set("//h:section[@data-xp='l']/child-gap()",Setting::listing());
        $v->set("//h:section[@data-xp='e']");
    }
};
SEN::page($pgfn,$v,Sec::SETTINGS);

