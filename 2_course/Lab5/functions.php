<?php

function connect_db() {
    $link = mysqli_connect("localhost", "root", "", "sort_lab");
    mysqli_set_charset($link, "utf8");

    return $link;
}

function get_el($link, $index) {
    $sql = "SELECT * FROM `sort` WHERE `sort`.`array_index` = '$index';";
    $result = mysqli_query($link, $sql);
    $result = mysqli_fetch_all($result, MYSQLI_ASSOC);
    return $result[0]["value"];
}

function swap($link, $index1, $index2) {
    //echo "swap ".$index1." and ".$index2."\n";
    $val1 = get_el($link, $index1);
    $val2 = get_el($link, $index2);
    $sql = "UPDATE `sort` SET `value` = '$val2' WHERE `sort`.`array_index`='$index1';";
    $result = mysqli_query($link, $sql);
    $sql = "UPDATE `sort` SET `value` = '$val1' WHERE `sort`.`array_index`='$index2';";
    $result = mysqli_query($link, $sql);
}

function quicksort($link, $left, $right) {
    $index = partition($link, $left, $right);
    if ($left < $index - 1)
        quicksort($link, $left, $index - 1);
    if ($right > $index + 1)
        quicksort($link, $index + 1, $right);
}

function partition($link, $left, $right) {
    $i = $left;
    $j = $right;
    $pivot = get_el($link, $i);
    while (($i < $j) && get_el($link, $j) >= $pivot) $j--;

    $k = $j;

    while ($i < $j) {
        while (($i < $j) && get_el($link, $i) < $pivot) $i++;
        while (($i < $j) && get_el($link, $j) >= $pivot) $j--;

        if ($i < $j)
            swap($link, $i, $j);    // При следующих вызовах можем не рассматривать ключ, благодаря этой строке
    }

    if ($i != $k)
        swap($link, $i, $k);

    return $i;
}