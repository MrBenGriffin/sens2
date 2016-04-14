<?php //Sec::USERMGMT
mb_internal_encoding('UTF-8');
require_once("basis.php");
require_once("sen.inc");
$v=new NView('view-do-users_1.ixml');
$pgfn= function() use (&$v) {
    if(!empty(Settings::$qst['u'])) {
        $user=intval(Settings::$qst['u']);
        if( $user !== 0) {
            $view=UserProfile::edit($user,'/do-users.php',Settings::$usr['role'] != Sec::ROLE_DEVELOPER);
        } else {
            $view=User::newuser('u=[[ID]]','/do-users.php');
        }
    } else {
        $view=User::listing('u','/do-users.php',Settings::$usr['role'] != Sec::ROLE_DEVELOPER);
    }
    $v->set("//*[@data-xp='user']",$view);
};
SEN::page($pgfn,$v,Sec::USERMGMT);
