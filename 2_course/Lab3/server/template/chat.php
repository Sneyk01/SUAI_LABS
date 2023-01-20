<?php
include_once ($_SERVER["DOCUMENT_ROOT"]."/functions.php");
check_cookie();

$link = connect_db();

$sql = "SELECT * FROM chats_table WHERE `chats_table`.`id`= '".$_GET["chat_id"]."';";
$chat = mysqli_query($link, $sql);
$chat = mysqli_fetch_all($chat, MYSQLI_ASSOC);

echo "<input type='hidden' id='chat_id', value='".$_GET["chat_id"]."'>";

$sql = "SELECT * FROM users_table WHERE `users_table`.`token`= '".$_COOKIE["Token"]."';";
$user = mysqli_query($link, $sql);
$user = mysqli_fetch_all($user, MYSQLI_ASSOC);

if ($chat[0]["type"] == "private")
    if (!check_access_private($user[0]["login"], $chat[0])) {
        echo "У вас нет доступа!";
        exit();
    }

echo "<input type='hidden' id='user_id', value='".$user[0]["id"]."'>";
echo "<input type='hidden' id='user_name', value='".$user[0]["login"]."'>";

echo "<div class='row'>";
echo "<div class='col-12'><p class='float-start fs-3 fw-bold'>".$chat[0]["name"].":</p></div>";
echo "</div>";

echo "<div class='container scrollable_chat col-12 ms-1'>";
    include "chat_messages.php";
echo "</div>";


echo "<div class='container ms-1'>";
echo "<div class='row'>";
echo "<div class='col-10'><input type='text' id='message_input' class='form-control col-12'></div>";
echo "<div class='col-1'><button type='submit' id='message_button' class='ps-1 btn btn-success col-12'>Отправить</button></div>";
echo "<div class='col-1'> 
<div class='btn-group dropup'>
    <button class='float-end btn btn-success ms-0 me-0 col-12 dropdown-toggle' data-bs-toggle='dropdown' aria-expanded='false'>🗑</button>
    <ul class='dropdown-menu dropdown-menu-end'>
        <li><div class='form-check'><input name='flexRadioDefault' class='form-check-input ms-0 me-0 check' value='0' type='radio' id='null_radio' checked> Не удалять</div></li>
        <li><div class='form-check'><input name='flexRadioDefault' class='form-check-input ms-0 me-0 check' value='10' type='radio' id='ten_sec_radio'> 10 секунд</div></li>
        <li><div class='form-check'><input name='flexRadioDefault' class='form-check-input ms-0 me-0 check' value='300' type='radio' id='five_min_radio'> 5 минут</div></li>
        <li><div class='form-check'><input name='flexRadioDefault' class='form-check-input ms-0 me-0 check' value='1800' type='radio' id='thirty_min_radio'> 30 минут</div></li>
        <li><div class='form-check'><input name='flexRadioDefault' class='form-check-input ms-0 me-0 check' value='3600' type='radio' id='hour_radio'> 1 час</div></li>
    </ul>
 </div></div>";
echo "</div>";
echo "</div>";

?>
<script>$(".scrollable_chat").scrollTop($(".scrollable_chat")[0].scrollHeight);</script>