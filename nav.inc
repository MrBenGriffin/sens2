<?php //SCHOOL INDEPENDENT
mb_internal_encoding('UTF-8');
class Nav {
    static function view() {
        $n = new NView("view-secnav_1.ixml");
        if (!Sec::ok(Sec::HOMEPAGE)) {$n->set("//*[@data-xp='HOMEPAGE']");}
        if (!Sec::ok(Sec::UTILITYS)) {$n->set("//*[@data-xp='UTILITYS']");}
        if (!Sec::ok(Sec::INTERVNS)) {$n->set("//*[@data-xp='INTERVNS']");}
        if (!Sec::ok(Sec::CLASSINT)) {$n->set("//*[@data-xp='CLASSINT']");}
        if (!Sec::ok(Sec::PROVIDER)) {$n->set("//*[@data-xp='PROVIDER']");}
        if (!Sec::ok(Sec::ALLREPTS)) {$n->set("//*[@data-xp='ALLREPTS']");}
        if (!Sec::ok(Sec::SENMANAG)) {$n->set("//*[@data-xp='SENMANAG']");}
        if (!Sec::ok(Sec::SPROFILE)) {$n->set("//*[@data-xp='SPROFILE']");}
       return $n;
    }
}
