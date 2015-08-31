<?php //Sec::INTERVNS
mb_internal_encoding('UTF-8');
require_once("basis.iphp");
require_once("sen.inc");

$v = new NView();
$pgfn= function() use (&$v) {
    if (!empty(Settings::$req[0])) {
        $key= Intervention::exists(Settings::$req[0]) ? Settings::$req[0] : null;
        $tx=new Intervention($key);
        $v->set("//h:section[@data-xp='l']");
        $v->set("//h:fieldset[@data-xp='f']",$tx->form());
        if (! is_null($key)) {
            if ($rx = Settings::$sql->query("select user from userv where locate('Provider',rname) > 0 and school=".Settings::$usr['school']." order by name")) {
                while ($f = $rx->fetch_assoc()) {
                    $tx=new IntPro($f['user'],$key);
                    $v->set("//*[@data-xp='fa']/child-gap()",$tx->form());
                }
                $rx->close();
            }
        } else {
            $v->set("//*[@data-xp='fa']");
        }
    } else {
        $v->set("//h:section[@data-xp='l']/child-gap()",Intervention::listing());
        $v->set("//h:section[@data-xp='e']");
    }
};
SEN::page($pgfn,$v,Sec::INTERVNS);
