<?php //SCHOOL INDEPENDENT
mb_internal_encoding('UTF-8');

class Sec {

//Roles
    const ROLE_UNASSIGNED = 1;
    const ROLE_TEACHER = 2;
    const ROLE_PROVIDER = 3;
    const ROLE_SENCO = 4;
    const ROLE_DEVELOPER = 5;

//Activities
    const ROLEMGMT = 1;
    const USERMGMT = 2;
    const ACTIVITY = 3;
    const SETTINGS = 4;
    const COHORTMG = 5;
    const CLASSMGT = 6;
    const INTERVNS = 7;
    const SENMANAG = 8;
    const STATEMGR = 9;
    const UTILITYS = 10;
    const CLASSINT = 11; //no good for anything other than teacher..
    const REPORTSM = 12;
    const PROVIDER = 14;
    const HOMEPAGE = 18;
    const SCHOOLSM = 32;
    const SPROFILE = 33;
    const OVERRIDE = 34;
    const ALLREPTS = 35;
    const MYPROVIS = 36;
    const ATEACHER = 37;

/*
+----+----------------------+----------+-
| id | name                 | code     |
+----+----------------------+----------+-
|  1 | Roles Manager        | ROLEMGMT |
|  2 | User Manager         | USERMGMT |
|  3 | Activity Manager     | ACTIVITY |
|  4 | Settings Access      | SETTINGS |
|  5 | Cohort Manager       | COHORTMG |
|  6 | Class Management     | CLASSMGT |
|  7 | Interventions Editor | INTERVNS |
|  8 | SEN Support Manager  | SENMANAG |
|  9 | State Manager        | STATEMGR |
| 10 | Utility Access       | UTILITYS |
| 11 | Class Interventions  | CLASSINT |
| 12 | Reports Access       | REPORTSM |
| 14 | Provider Editing     | PROVIDER |
| 18 | Home Access          | HOMEPAGE |
| 32 | Schools Management   | SCHOOLSM |
| 33 | Self Profile Editing | SPROFILE |
| 34 | SEN Overide          | OVERRIDE |
| 35 | All reports access   | ALLREPTS |
+----+----------------------+----------+-
*/

//This is a special case, where role is a value stored in userprofile.
	public static function user() {
        Settings::$usr['sec']=array();
	    if(isset(Settings::$usr['role'])) {
            $qry="select a.id from sio_roleactivities ra,sio_activity a where a.id=ra.activity and ra.role='".Settings::$usr['role']."' group by a.id";
            if ($rs = Settings::$sql->query($qry)) {
                while ($f = $rs->fetch_assoc()) {
                    Settings::$usr['sec'][intval($f['id'])]=true;
                }
                $rs->close();
            }
        }
	}

	//return a partial sql query for filtering users that are tied to schools.
	//eg where school=".Settings::$usr['school'].";
	public static function schsql($field='school',$alias='') {
		$school=Settings::$usr['school'];
		if ($school === 0) {
			$retval=' true ';
		} else {
			if(!empty($alias)) {
				$retval=" ".$alias.".".$field."=".$school." ";
			} else {
				$retval=" ".$field."=".$school." ";
			}
		}
		return $retval;
	}

	//Returns true or false, based on user-activity
	public static function ok($activity=0) {
		$retval=false;
		if ( isset(Settings::$usr['sec'][$activity]) ) {
			$retval=true;
		}
		return $retval;
	}
}
