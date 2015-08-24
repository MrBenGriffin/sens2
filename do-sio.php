<?php //activity 0: anyone can come here.
mb_internal_encoding('UTF-8');
require_once("basis.iphp");
require_once("sen.inc");
$v=new NView("view-do-sio_1.ixml");
$err = $v->messages(); if (!empty($err)) { print_r($err); }
$pgfn= function() use (&$v) { //profile editing.
	$logged_in=Sec::ok();
    $v->set("//*[@data-xp='sio']/child-gap()",SIO::run());
    Sec::user(); //set user activities.
    SEN::user(); //set additional user data.
	if ($logged_in==Sec::ok()) { //ie, nothing changed..
		//  header("Location: " . Settings::$url . "?" . $this->cal . '&L&' . $this->coh );
		if (Sec::ok(Sec::SPROFILE)) { //
			$v->set("//*[@data-xp='title']/child-gap()","Profile");
			$view=UserProfile::edit(Settings::$usr['ID'],NULL,true); //true=restricted
			$view->set("//h:h2/child-gap()","– using email address: " . Settings::$usr['email']);
			$v->set("//*[@data-xp='profile']",$view);
		} else {
			if (isset(Settings::$qst[SioReg::SIG])) {
				$v->set("//*[@data-xp='title']/child-gap()","Register as a new user");
			} else {
				$v->set("//*[@data-xp='title']/child-gap()","Sign In/Sign Out");
			}
			$v->set("//*[@data-xp='profile']");
		}
	} else {
		header("Location: /do-home.php");
	}
};
SEN::page($pgfn,$v,0,true);

