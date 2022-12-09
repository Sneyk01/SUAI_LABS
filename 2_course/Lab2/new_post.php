<?php

$GLOBALS["symb_base"] = "0987654321zxcvbnmasdfghjklqwertyuiopPOIUYTREWQLKJHGFDSAMNBVCXZ";
	
		
function gen_str($count) {
	$str = "";
	for ($i = 0; $i < $count; $i++) {
		$num = rand(0,strlen($GLOBALS["symb_base"]) - 1);
		$rand_symb = $GLOBALS["symb_base"][$num];
		$str = $str.$rand_symb;
	}
	return $str;
}


if (isset($_POST["text"])) {
	$text = $_POST["text"];
	$text = trim($text);
	$time = time();
	
	if (strlen($text) > 900) {
		header("Location: http://localhost/forum.php?message=Слишком длинный текст");
		exit;
	}
	if (strlen($text) < 4) {
		header("Location: http://localhost/forum.php?message=Слишком короткий текст");
		exit;
	}

		$img_name = "";
		//print_r($_FILES["img"]);
		
		$file = $_FILES["img"];
			
		if ($file["name"] != "") {
			
			if ($file["error"] != 0) {
				header("Location: http://localhost/forum.php?message=С файлом что-то не так!");
				exit;
			}
			
			$types = array("image/jpeg", "image/jpg");
			if (!in_array($file["type"], $types)) {
				header("Location: http://localhost/forum.php?message=Недопустимый формат файла!");
				exit;
			}
			
			$img_name = gen_str(5).".jpeg";
			if (!@copy($file["tmp_name"], 'img/'.$img_name)) {
				header("Location: http://localhost/forum.php?message=С картинкой что-то не так!");
				exit;
			}
		}
		
		$sql = "INSERT INTO `posts` (`id`, `text`, `like_count`, `fun_count`, `dislike_count`, `time`, `img_id`) VALUES (NULL, '".$text."', '0', '0', '0', '".$time."', '".$img_name."');";
	
		$link = mysqli_connect("localhost", "forum_db", "12345", "posts");
		mysqli_set_charset($link, "utf8");
		$res = mysqli_query($link, $sql);
	
		header("Location: http://localhost/forum.php");
	}
	
else {
	header("Location: http://localhost/forum.php?message=С файлом что-то не так!");
	exit;
}
?>
