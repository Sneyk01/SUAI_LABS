<?php
include "data_base_functions.php";
include "functions.php";


$db = open_data("data.json");

$user = isset($_GET["login"]) ? $_GET["login"] : null;
$password = isset($_GET["npass"]) ? $_GET["npass"] : null;
$c_password = isset($_GET["c_npass"]) ? $_GET["c_npass"] : null;

if ($user == "token") {
	
	check_passwords($password, $c_password, "http://localhost/main.php");
	valid_password($password, "http://localhost/main.php");
		
	$token = $_COOKIE["Token"];
	
	foreach($db as &$ac) {
		if ($token == $ac["Token"]) {
				if ($ac["Time"] + 3600 < time()) {												//Check token time
					$ac["Token"] = null;
					setcookie("Token", "", time() - 3600);
					file_put_contents("data.json", json_encode($db));
					
					header("Location: http://localhost/SIGNIN.php?message=Session expired");
					exit;
				}
				else {
					[$hash, $salt] = hash_password($password);
					$ac["Password"] = $hash;
					$ac["Salt"] = $salt;
					$ac["Time_p"] = time();
		
					file_put_contents("data.json", json_encode($db));
					header("Location: http://localhost/main.php?message=Password has been changed&color=green");
					exit;
				}
		}
	}
	
	header("Location: http://localhost/main.php?message=Wrong data");
	exit;
}

else {
	if ($user == null || $password == null || $c_password == null) {
			header("Location: http://localhost/restore.php?message=Wrong data");
			exit;
		}
	
	check_passwords($password, $c_password, "http://localhost/restore.php");
	valid_password($password, "http://localhost/restore.php");

	foreach($db as &$ac) {
		if ($user == $ac["Login"]) {
			[$hash, $salt] = hash_password($password);
			$ac["Password"] = $hash;
			$ac["Salt"] = $salt;
			$ac["Time_p"] = time();
		
			file_put_contents("data.json", json_encode($db));
			header("Location: http://localhost/SIGNIN.php?message=Password has been changed&color=green");
			exit;
		}
	}

	header("Location: http://localhost/restore.php?message=Wrong data");
	exit;
}

?>