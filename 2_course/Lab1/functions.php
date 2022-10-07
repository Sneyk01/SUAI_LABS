<?php
	function print_message() {											// For html pages
		if (isset($_GET["message"])) {
			
			$color = isset($_GET["color"]) ? $_GET["color"] : "red";
			$mes = $_GET["message"];
			
			echo '<p style="color: '.$color.'">'.$mes.'</p>' ;
			//print($mes);
		}
	}
	
	
	function check_passwords($password, $c_password, $source) {
		if ($c_password != $password) { 
			header("Location: ".$source."?message=Passwords do not match");
			exit;		
		}
		
		if ($password == null) {
			header("Location: ".$source."?message=Data error");
			exit;
		}
	}
	
	
	function valid_password($password, $source) {
		$p_len = 5;
		
		if (strlen($password) < $p_len) {
			header("Location: ".$source."?message=Minimum password length - ".$p_len." characters");
			exit;
		}
	}
	
	
	function check_time_p($db) {
		$token = $_COOKIE["Token"];
		
		foreach($db as &$ac) {
			if ($ac["Token"] == $token) {
				if ($ac["Time_p"] + 604800 < time()) {											// 1 week
					header("Location: http://localhost/main.php?message=Password expired, please, change it&color=brown");
					exit;
				}
			}
		}
	}
	
	
	function check_token($db) {
		if (isset($_COOKIE["Token"])) {
			$token = $_COOKIE["Token"];
			
			foreach($db as &$ac) {
				if ($ac["Token"] == $token) {
					if ($ac["Time"] + 3600 < time()) {
						$ac["Token"] = null;
						setcookie("Token", "", time() - 3600);
						file_put_contents("data.json", json_encode($db));
						
						header("Location: http://localhost/SIGNIN.php?message=Session expired");
						exit;
					}
					else	return $ac["Login"];
				}
			}
			
			header("Location: http://localhost/SIGNUP.php");										// Bad cookie
			setcookie("Token", "", time() - 3600);
			exit;
		}
	}
?>