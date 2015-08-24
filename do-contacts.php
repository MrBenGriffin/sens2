<?php //Sec::USERMGMT
mb_internal_encoding('UTF-8');
require_once("basis.iphp");
require_once("sen.inc");
$v=new NView('view-do-contacts.ixml');
$pgfn= function() use (&$v) {
	$v->set("//*[@data-xp='list']",Contact::listing());
};
SEN::page($pgfn,$v,Sec::HOMEPAGE);
