<?php
include_once ($_SERVER["DOCUMENT_ROOT"]."/functions.php");

$link = connect_db();
$data = get_chats($link);
$i = 0;

foreach ($data as $chat) {
    if ($i % 2 == 0)
        $color = "bg-white";
    else
        $color = "bg-gray";

    if (!check_chat_time($chat, $link))
        continue;

    if ($chat["type"] == "private") {
        if (!check_access_private(get_login(), $chat))
            continue;
        $type = "🔒";
    }
    else
        $type = "🔓";

    echo "<div class='row'>";
    echo "<div class='col-1 border-bottom ".$color."'><p class='fs-3 mt-3'>".$type."</p></div>";
    echo "<div class='col-8 border-bottom ".$color."'><p class='fs-3 mt-3'>".$chat["name"]."</p></div>";
    echo "<div class='col-1 border-bottom ".$color."'><button id='".$chat["id"]."' class='btn btn-success col-12 mt-3 enter_chat'> Войти </button></div>";
    echo "</div>";

    $i++;
}