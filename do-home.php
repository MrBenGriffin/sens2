<?php //sec::HOMEPAGE
mb_internal_encoding('UTF-8');
require_once("basis.php");
require_once("sen.inc");
$v=new NView('view-do-home_1.ixml');
$pgfn= function() use (&$v) {

    if(isset(Settings::$usr['role'])) {
        switch (Settings::$usr['role']) {
            case Sec::ROLE_UNASSIGNED:     {   header("Location: /do-sio.php"); } break;
            case Sec::ROLE_TEACHER:        {   header("Location: /cci/do.php"); } break;
            case Sec::ROLE_PROVIDER:       {   header("Location: /pve/do.php"); } break;
            case Sec::ROLE_SENCO:          {   header("Location: /sen/do.php"); } break;
            case Sec::ROLE_DEVELOPER:      {   header("Location: /dev/do.php"); } break;
        }
    } else {
        header("Location: /do-sio.php");
    }

};
SEN::page($pgfn,$v,Sec::HOMEPAGE);
