<?php
include_once "functions.php";

if (empty($_POST["login"])) {
    echo "Укажите логин";
    exit();
}

if (preg_match("|\s|", $_POST["login"])) {
    echo "Логин не должен содержать пробелы";
    exit();
}

$login = $_POST["login"];

$link = connect_db();
$result = get_users($link);

foreach ($result as $user) {
    if ($login == $user["login"]) {
        echo "Это имя уже занято";
        exit();
    }
}

$token = gen_str(20);
$sql = "INSERT INTO `users_table` (`id`, `login`, `token`, `time`) VALUES (NULL, '".$login."', '".$token."', '".time()."');";
$send = mysqli_query($link, $sql);
setcookie("Token", $token);

echo "True";
exit();





