<?php //Sec::SENMANAG
mb_internal_encoding('UTF-8');
require_once("basis.iphp");
require_once("sen.inc");

$v = new NView();
$pgfn= function() use (&$v) {
    if (!empty(Settings::$req[0]) && !empty(Settings::$req[1])) {
        if (SENSDoc::exists(Settings::$req[0],Settings::$req[1])) {
            $v->set("//*[@data-xp='title']/child-gap()",CCI::title(Settings::$req[0],Settings::$req[1]));
            $v->set("//h:section[@data-xp='l']/child-gap()",CCI::listing(Settings::$req[0],Settings::$req[1]));
        }
    } else {
        $v->set("//*[@data-xp='title']/child-gap()","SEN Documents");
        $v->set("//h:section[@data-xp='l']/child-gap()",SENSDoc::listing());
    }
};
SEN::page($pgfn,$v,Sec::SENMANAG);
