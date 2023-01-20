<?php
include_once "functions.php";
check_cookie();

$link = connect_db();
$data = get_users($link);

if ($_POST["method"] == "change_name") {
    $new_login = $_POST["login"];

    if (preg_match("|\s|", $new_login)) {
        echo json_encode(["result" => "False"]);
        exit();
    }

    foreach ($data as $user) {
        if ($user["login"] == $new_login) {
            echo json_encode(["result" => "False"]);
            exit();
        }
    }

    $sql = "UPDATE `users_table` SET `login` = '".$new_login."'WHERE `users_table`.`token` = '".$_COOKIE["Token"]."';";
    $data = mysqli_query($link, $sql);
    echo json_encode(["result" => "True"]);
    exit();
}

if ($_POST["method"] == "add_chat") {
    if (empty($_POST["chat_name"])) {
        echo json_encode(["result" => "False", "message" => "Укажите название чата"]);
        exit();
    }

    $_POST["chat_name"] = words_filter($_POST["chat_name"]);

    if (!check_chat_duplicate($_POST["chat_name"], $link)) {
        echo json_encode(["result" => "False", "message" => "Чат с таким именем уже существует"]);
        exit();
    }

    if ($_POST["chat_type"] == "private") {
        $_POST["chat_access"] = $_POST["login"] . ";" . $_POST["chat_access"];
        $_POST["chat_access"] = str_replace(" ", "", $_POST["chat_access"]);
    }
    $sql = "INSERT INTO `chats_table` (`id`, `name`, `type`, `last_message`, `access_names`) VALUES (NULL, '".$_POST["chat_name"]."', '".$_POST["chat_type"]."', '".time()."', '".$_POST["chat_access"]."');";
    $result = mysqli_query($link, $sql);

    echo json_encode(["result" => "True", "message" => "Чат создан"]);
    exit();
}

if ($_POST["method"] == "add_message") { // Не забудь потом про пробелы
    if (empty($_POST["message"])) {
        echo json_encode(["result" => "False", "message" => "Укажите сообщение"]);
        exit();
    }
    $_POST["message"] = words_filter($_POST["message"]);
    $sql = "INSERT INTO `messages_table` (`id`, `chat_id`, `sender_id`, `time`, `sender_name`, `delete_time`, `text`) VALUES (NULL, '".$_POST["chat_id"]."', '".$_POST["sender_id"]."', '".time()."', '".$_POST["sender_name"]."', '".$_POST["delete_time"]."', '".$_POST["message"]."');";
    $result = mysqli_query($link, $sql);

    $sql = "UPDATE `chats_table` SET `last_message` = '".time()."' WHERE `chats_table`.`id` = ".$_POST["chat_id"].";";
    $result = mysqli_query($link, $sql);
    //echo words_filter($_POST["message"]);
    echo json_encode(["result" => "True", "message" => "Сообщение создано"]);
    exit();
}
