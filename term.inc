<?php //SCHOOL INDEPENDENT
mb_internal_encoding('UTF-8');
class Term {
    use Form;
    const SIG = "_term";
    public static function sig() {
        return static::SIG;
    }
    function __construct($key = NULL) {
        $v = new NView('view-term_1.ixml');
        $this->iniForm($key, $v, false, "id", false);
        $this->key   = $key; //role changes across the formlet instances.
        $this->table = "halft";
        $this->setfld('ref');	//the listing..
        $this->setfld('name');	//what appears on the front-end.
    }
    public function validate() {
        $this->valUnique('ref', Dict::get('errors_name_unique'));
        $this->valSignificant('ref', Dict::get('errors_name_significant'));
    }
    public function populate() {
        $this->vset('ref');
        $this->vset('name');
    }
    public static function listing($qs = 't', $url = '') {
        $v = NULL;
        if (Sec::ok(Sec::SETTINGS)) {
            $v  = new NView('view-term-list.ixml');
            $rt = new NView($v->consume("//h:ul/h:li"));
            if ($rx = Settings::$sql->query("select id,ref,name from halft order by id")) {
                while ($f = $rx->fetch_assoc()) {
                    $r = new NView($rt);
                    $r->set("//h:a/child-gap()", $f['ref'] ." prompt: [".$f['name']."] ");
                    $r->set("//h:a/@href/child-gap()", $url . '?' . $qs . '=' . $f['id']);
                    $v->set("//h:ul/child-gap()", $r);
                }
                $rx->close();
            }
            $v->set("//*[@data-xp='new']/@href", $url . '?' . $qs . '=NULL');
            $v->set("//h:ul/child-gap()", $rt);
        }
        return $v;
    }
    public static function edit($id = NULL, $url = '') {
        $v = NULL;
        if (!is_null($id) && Sec::ok(Sec::SETTINGS)) {
            $v    = new NView('view-term-edit.ixml');
            $form = new Term(intval($id));
            $v->set("//*[@data-xp='form']", $form->form(true));
            $v->set("//*[@data-xp='back']/@href", $url);
        }
        return $v;
    }
}
