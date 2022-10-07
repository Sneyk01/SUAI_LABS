<?php
	$GLOBALS["symb_base"] = "0987654321=zxcvbnmasdfghjklqwertyuiopPOIUYTREWQLKJHGFDSAMNBVCXZ";
	
		
	function gen_str($count) {
		$str = "";
		for ($i = 0; $i < $count; $i++) {
			$num = rand(0,strlen($GLOBALS["symb_base"]) - 1);
			$rand_symb = $GLOBALS["symb_base"][$num];
			$str = $str.$rand_symb;
		}
		return $str;
	}
	
	
	function check_cookie($db){
		if (isset($_COOKIE["Token"])) {
			for ($i = 0; $i < count($db); $i++) {
				if ($_COOKIE["Token"] == $db[$i]["Token"]) {
					header("Location: http://localhost/main.php");
					exit;
				}
			}
		
			setcookie("Token", "", time() - 3600);					// Bad cookie
			header("Location: http://localhost/SIGNIN.php");
			exit;
		}
	}
	
	
	function open_data($data) {
		$db = file_get_contents($data);
		$db = json_decode($db, true);
		return $db;
	}
	
	
	function hash_password($password, $h_salt = null) {
		$h_salt = is_null($h_salt) ? gen_str(10) : $h_salt;
		$password = $password.$h_salt;
		$hash = hash("md5", $password);
		
		return array($hash, $h_salt);
	}


?>