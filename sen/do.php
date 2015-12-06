<?php //Sec::SENMANAG
mb_internal_encoding('UTF-8');
require_once("basis.iphp");
require_once("sen.inc");

$v = new NView();
$pgfn= function() use (&$v) {
    if (!empty(Settings::$req[0]) && !empty(Settings::$req[1])) {
 //this is a cci instance generated from 'new'.
        if (!empty(Settings::$req[2])) {
         	$cal = Settings::$req[0];
         	$cci = Settings::$req[1];
         	$coh = Settings::$req[2];
			if (SENSDoc::exists($cal,$coh) && CCI::exists($cci)) {
				$v->set("//*[@data-xp='title']/child-gap()",CCI::title($cal,$coh));
				$tx=new CCI($cci,$coh,$cal);
				$v->set("//*[@data-xp='l']",$tx->form());
			}
        } else {
         	$cal = Settings::$req[0];
         	$coh = Settings::$req[1];
        	//0: $cal=NULL,$coh= 1
			if (SENSDoc::exists($cal,$coh)) {
				$v->set("//*[@data-xp='title']/child-gap()",CCI::title($cal,$coh));
				$v->set("//h:section[@data-xp='l']/child-gap()",CCI::listing($cal,$coh));
			}
        }
    } else {
        $v->set("//*[@data-xp='title']/child-gap()","SEN Documents");
        $v->set("//h:section[@data-xp='l']/child-gap()",SENSDoc::listing());
    }
};
SEN::page($pgfn,$v,Sec::SENMANAG);
