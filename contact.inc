<?php //
mb_internal_encoding('UTF-8');
class Contact {
    public static function listing($qs = 'a', $url = '') {
        $v = NULL;
        if (Sec::ok(Sec::HOMEPAGE)) {
            $v  = new NView('view-contact-list.ixml');
			$rt = $v->consume("//h:li");
			$qry="select concat (p.firstname,' ',p.familyname) as name,u.email,r.id from sio_user u,sio_userprofile p,sio_role r where ".Sec::schsql('school','p')." and p.user=u.id and p.role=r.id and u.active='on' order by r.name,p.familyname";
			if ($rx = Settings::$sql->query($qry)) {
				while ($f = $rx->fetch_assoc()) {
					$r=new NView($rt);
					$r->set("//h:span[@data-xp='name']/child-gap()",$f['name']);
					if(empty($f['email'])) {
						$r->set("//h:a"," -- no email available -- ");
					} else {
						$r->set("//h:a/@href/child-gap()",$f['email']);
						$r->set("//h:a/child-gap()",$f['email']);
					}
					$v->set("//h:ul[@data-xp='".$f['id']."']/child-gap()",$r);
				}
				$rx->close();
			}
        }
        return $v;
    }
}
