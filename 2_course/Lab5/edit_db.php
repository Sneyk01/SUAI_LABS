<?php
include_once "functions.php";

$link = connect_db();

if ($_POST["method"] == "create") {
    $str = "";
    $sql = "DELETE FROM `sort`;";
    mysqli_query($link, $sql);

    for ($i = 0; $i < $_POST["size"]; $i++) {
        $num = rand(0, 1000);
        $sql = "INSERT INTO `sort` (`id`, `array_index`, `value`) VALUES (NULL, '$i', '$num')";
        mysqli_query($link, $sql);
        $str .= $num."; ";
    }
    echo json_encode(["array" => $str]);
}

if ($_POST["method"] == "show") {
    send_data($link);
}

if ($_POST["method"] == "sort") {
    $sql = "SELECT COUNT(*) FROM `sort`";
    $count = mysqli_query($link, $sql);
    $count = mysqli_fetch_all($count, MYSQLI_ASSOC);
    if ($count[0]["COUNT(*)"] == 0) {
        echo json_encode(["array" => "Массив пуст!"]);
        return;
    }
    quicksort($link, 0, $count[0]["COUNT(*)"]-1);
    send_data($link);
}

function send_data($link) {
    $str = "";
    $sql = "SELECT * FROM `sort`";
    $data = mysqli_query($link, $sql);
    $data = mysqli_fetch_all($data, MYSQLI_ASSOC);
    foreach ($data as $elem)
        $str .= $elem["value"]."; ";

    //$str .= $elem["array_index"].": ".$elem["value"]."; ";
    if ($str == "")
        echo json_encode(["array" => "Массив пуст!"]);
    else
        echo json_encode(["array" => $str]);
}