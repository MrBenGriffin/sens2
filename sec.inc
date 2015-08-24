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
+----+----------------------+----------+--------+
| id | name                 | code     | active |
+----+----------------------+----------+--------+
|  1 | Roles Manager        | ROLEMGMT | on     |
|  2 | User Manager         | USERMGMT | on     |
|  3 | Activity Manager     | ACTIVITY | on     |
|  4 | Settings Access      | SETTINGS | on     |
|  5 | Cohort Manager       | COHORTMG | on     |
|  6 | Class Management     | CLASSMGT | on     |
|  7 | Interventions Editor | INTERVNS | on     |
|  8 | SEN Support Manager  | SENMANAG | on     |
|  9 | State Manager        | STATEMGR | on     |
| 10 | Utility Access       | UTILITYS | on     |
| 11 | Class Interventions  | CLASSINT | on     |
| 12 | Reports Access       | REPORTSM | on     | Allows access to non-specific reports.
| 14 | Provider Editing     | PROVIDER | on     |
| 18 | Home Access          | HOMEPAGE | on     |
| 32 | Schools Management   | SCHOOLSM | on     |
| 33 | Self Profile Editing | SPROFILE | on     |
| 34 | Sen Process Override | OVERRIDE | on     |
| 35 | Reports (All)        | ALLREPTS | on     | Allows access to reports in general.
| 36 | Own Provisions       | SLFPROVI | on     |
| 37 | I am a Teacher       | ATEACHER | on     |
+----+----------------------+----------+--------+
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
