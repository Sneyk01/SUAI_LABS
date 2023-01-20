<?php
$GLOBALS["symb_base"] = "0987654321zxcvbnmasdfghjklqwertyuiopPOIUYTREWQLKJHGFDSAMNBVCXZ";


function connect_db() {
    $link = mysqli_connect("localhost", "root", "", "vchat");
    mysqli_set_charset($link, "utf8");

    return $link;
}


function check_cookie() {   // Если токен подходит - true, иначе просто отпраавляем на login.php
    $link = connect_db();
    $token = isset($_COOKIE["Token"]) ? $_COOKIE["Token"] : null;

    if($token == null) {
        if ($_SERVER["REQUEST_URI"] == "/login.php")    // Если мы уже на login.php (иначе постоянная пересылка)
            return false;
        header("location: login.php");
        exit();
    }

    $data = get_users($link);

    foreach ($data as $user) {
        if ($user["token"] === $token) {
            if (($user["time"] + get_token_time()) >= time())
                return true;
            else {  // Удаляем старую запись
                $sql = "DELETE FROM `users_table` WHERE `users_table`.`token` = '".$token."';";
                $result = mysqli_query($link, $sql);
                header("location: login.php?s");
                exit();
            }
        }
    }

    if ($_SERVER["REQUEST_URI"] == "/login.php" || $_SERVER["REQUEST_URI"] == "/login.php?s") // Сообщение о сессии
        return false;
    header("location: login.php");
    exit();
}


function get_login() {
    $link = connect_db();
    $sql = "SELECT * FROM `users_table` WHERE `users_table`.`token` = '".$_COOKIE["Token"]."';";
    $data = mysqli_query($link, $sql);
    $data = mysqli_fetch_all($data, MYSQLI_ASSOC);
    return $data[0]["login"];
}


function check_access_private($login, $chat): bool
{
    $logins = explode(";", $chat["access_names"]);
    if (in_array($login, $logins))
        return true;
    return false;
}

function get_chat_time() {
    return 172800;
}


function check_chat_time($chat, $link): bool
{
    if(($chat["last_message"] + get_chat_time()) < time()) {
        $sql = "DELETE FROM `chats_table` WHERE `chats_table`.`id` = '".$chat["id"]."';";
        $result = mysqli_query($link, $sql);
        return false;
    }
    return true;
}


function check_messages_time($link): bool
{
    $messages = get_messages($link);
    foreach ($messages as $message) {
        if ($message["delete_time"] != 0) {
            if (($message["time"] + $message["delete_time"]) < time()) {
                $sql = "DELETE FROM `messages_table` WHERE `messages_table`.`id` = '" . $message["id"] . "';";
                $result = mysqli_query($link, $sql);
                return false;
            }
        }
    }
    return true;
}


function get_users($link) {
    $sql = "SELECT * FROM users_table";
    return mysqli_query($link, $sql);
}


function get_chats($link): array
{
    $sql = "SELECT * FROM chats_table ORDER BY last_message DESC";
    $result = mysqli_query($link, $sql);
    return mysqli_fetch_all($result, MYSQLI_ASSOC);
}


function check_users($link) {
    $sql = "SELECT * FROM users_table";
    $result = mysqli_query($link, $sql);
    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);
    foreach ($data as $user) {
        if (($user["time"] + get_token_time()) >= time())
            continue;
        else {  // Удаляем старую запись
            $sql = "DELETE FROM `users_table` WHERE `users_table`.`id` = '" . $user["id"] . "';";
            $result = mysqli_query($link, $sql);
        }
    }
}

function get_messages($link): array
{
    $sql = "SELECT * FROM messages_table ORDER BY id";
    $result = mysqli_query($link, $sql);
    return mysqli_fetch_all($result, MYSQLI_ASSOC);
}


function gen_str($count): string
{
    $str = "";
    for ($i = 0; $i < $count; $i++) {
        $num = rand(0, (strlen($GLOBALS["symb_base"]) - 1));
        $rand_symb = $GLOBALS["symb_base"][$num];
        $str = $str.$rand_symb;
    }
    return $str;
}


function check_chat_duplicate($name, $link): bool
{
    $data = get_chats($link);

    foreach ($data as $chat) {
        if ($chat["name"] == $name)
            return false;
    }

    return true;
}


function get_token_time() {
    return 84600;
}


function message() {
    if (isset($_GET["s"]))
        echo "Ваша сессия устарела. Повторите вход";
}


function words_filter($data) {
    $filter = array("/\bсу(к|чк)(а|и|е)\b/iu", "/\b(наху|ху|ниху)(и|й|ем|я|есо(с|са|су))\b/iu",
                    "/\bбл(я|ять)\b/iu", "/\bпизд(ец|еж|ёж|ить|ил|ся)\b/iu",
                    "/\b(еб|заеб)(ал|у|т|ёт|ет)\b/iu", "/\bдерьм(о|а)\b/iu",
                    "/\bуро(д|ды|да|ду)\b/iu");
    return preg_replace($filter, '&#128056', $data);
}