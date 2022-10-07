<?php
	if(isset($_GET["action"]) && ($_GET["action"] == "del_cookie"))
		setcookie("Token", "", time() - 3600);
	
	header("Location: http://localhost/SIGNIN.php");
?>