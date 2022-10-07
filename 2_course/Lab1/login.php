<?php 
	include "data_base_functions.php";
	
	
	$db = open_data("data.json");
	
	check_cookie($db);
	
	$user = isset($_GET["login"]) ? $_GET["login"] : null;
	$password = isset($_GET["passw"]) ? $_GET["passw"] : null;
	
	if ($user == null || $password == null) {
		header("Location: http://localhost/SIGNIN.php?message=Wrong data");
		exit;
	}
	
	foreach($db as &$ac) {							//Create link between db and ac
		if ($user == $ac["Login"]) {
			[$h_password, $h_salt] = hash_password($password, $ac["Salt"]);
			
			if ($h_password == $ac["Password"]) {
				$token = gen_str(20);
				$ac["Token"] = $token;
				$ac["Time"] = time();
				setcookie("Token", $token);
				file_put_contents("data.json", json_encode($db));	
				
				header("Location: http://localhost/main.php");
				exit;
			}
		}
	}
	
	unset($ac);										//Delete link

	header("Location: http://localhost/SIGNIN.php?message=Wrong login or password");
?>