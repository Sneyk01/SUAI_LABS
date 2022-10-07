<?php 
	include "data_base_functions.php";
	include "functions.php";
	

	$user = isset($_GET["login"]) ? $_GET["login"] : null;
	$password = isset($_GET["passw"]) ? $_GET["passw"] : null;
	$c_password = isset($_GET["c_passw"]) ? $_GET["c_passw"] : null;
	
	if ($user == null || $password == null || $c_password == null) {
		header("Location: http://localhost/SIGNUP.php?message=Wrong data");
		exit;
	}
	
	check_passwords($password, $c_password, "http://localhost/SIGNUP.php");
	valid_password($password, "http://localhost/SIGNUP.php");
	
	$db = open_data("data.json");
	
	foreach($db as $ac) {
		if ($ac["Login"] == $user) {
			header("Location: http://localhost/SIGNUP.php?message=This login is already in use");
			exit;
		}
	}
	
	[$hash, $salt] = hash_password($password);
	
	$new_user["Id"] = $db[count($db) - 1]["Id"] + 1;
	$new_user["Login"] = $user;
	$new_user["Password"] = $hash;
	$new_user["Salt"] = $salt;
	$new_user["Token"] = gen_str(20);
	$new_user["Time"] = time();
	$new_user["Time_p"] = time();

	
	setcookie("Token", $new_user["Token"]);
	array_push($db, $new_user);
	file_put_contents("data.json", json_encode($db));
	
	header("Location: http://localhost/main.php?login=".$user);
	
?>