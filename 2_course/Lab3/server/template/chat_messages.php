<?php
include_once ($_SERVER["DOCUMENT_ROOT"]."/functions.php");

$link = connect_db();
check_messages_time($link);
/*
$answer = "";
$last_id = (isset($_POST["last_id"])) ? $_POST["last_id"] : 0;

$sql = "SELECT * FROM messages_table WHERE `messages_table`.`chat_id`= '".$_POST["chat_id"]."' AND `id` > ".$last_id." ORDER BY id;";

$messages = mysqli_query($link, $sql);
$messages = mysqli_fetch_all($messages, MYSQLI_ASSOC);

echo json_encode(["result" => "True", "messages" => $messages]);
*/

$sql = "SELECT * FROM messages_table WHERE `messages_table`.`chat_id`= '".$_GET["chat_id"]."' ORDER BY id;";
$messages = mysqli_query($link, $sql);
$messages = mysqli_fetch_all($messages, MYSQLI_ASSOC);

if (empty($messages))
    echo "Этот чат пуст, напиши сообщение первым!";

foreach ($messages as $message) {
    echo "<div class='row mb-0'>";
    echo "<div class='col'><p class='fs-6 mb-0'>".$message["sender_name"].":</p></div>";
    echo "</div>";
    echo "<div class='row mb-3 border-bottom'>";
    echo "<div class='col'><p class='fs-4 float-start'>".$message["text"]."</p></div>";
    echo "</div>";
}
?>
