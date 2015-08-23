<?php //REPORTSM
mb_internal_encoding('UTF-8');
require_once("basis.iphp");
require_once("sen.inc");

$v = new NView();
$pgfn= function() use (&$v) {
    $ident=0; $drillA=0; $drillB=0;  $drillC=0;
    if (!empty(Settings::$req[0])) { $ident =  intval(Settings::$req[0]); }
    if (!empty(Settings::$req[1])) { $drillA = intval(Settings::$req[1]); }
    if (!empty(Settings::$req[2])) { $drillB = intval(Settings::$req[2]); }
    if (!empty(Settings::$req[3])) { $drillC = intval(Settings::$req[3]); }
    $v->set("//h:section[@data-xp='l']/child-gap()",Overview::listing($ident,$drillA,$drillB,$drillC));
    $v->set("//*[@data-xp='title']/text()",Overview::$title);
};
SEN::page($pgfn,$v,Sec::REPORTSM);
