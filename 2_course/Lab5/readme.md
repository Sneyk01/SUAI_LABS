# Лабораторная работа №5
------

## Основное задание
Разработать и реализовать алгоритм внешней сортировки. Данные хранятся на сервере в массиве, сервер предоставляет доступ к отдельным элементам. Клиент поочередно запрашивая отдельные ячейки сортирует массив.

## Ход работы

### 1. Разработка пользовательского интерфейса

Для демонстрации работы программы был написан простой пользовательский интерфейс

- Основная страница:
<p align = "center"><img src="https://github.com/Sneyk01/SUAI_LABS/blob/master/2_course/Lab5/images/main.png"></p>

### 2. Описание пользовательских сценариев работы

После того, как пользователь зашел на сайт он может:
 - Сгенерировать новый массив случайных чисел заданной длины
 - Посмотреть массив, который хранится в базе данных на данный момент
 - Отсортировать массив, который хранится в базе данных на данный момент

Если в базе данных нет массива, при попытке отобразить или отсортировать массив, будет выедено сообщение о том, что массив отсутствует.

### 3. Описание API сервера и хореографии

Для отображения, генерации и сортировки массива, со страницы index.php отправляются ajax запросы на страницу edit_db.php. С примерами запросов можно ознакомится ниже:

<p align = "center"><img src="https://github.com/Sneyk01/SUAI_LABS/blob/master/2_course/Lab5/images/create.svg"/width = 30%></p>
<p align = "center"><img src="https://github.com/Sneyk01/SUAI_LABS/blob/master/2_course/Lab5/images/show.svg"/width = 30%></p>
<p align = "center"><img src="https://github.com/Sneyk01/SUAI_LABS/blob/master/2_course/Lab5/images/sort.svg"/width = 30%></p>

### 4. Описание структуры базы данных

Для хранения массива используется база данных MySQL. Таблица содержит в себе индивидуальный номер элемента, его индекс в массиве и значение.

Структура таблицы в базе данных:
   | Название | Тип | Длина | По умолчанию | Описание |
| :------: | :------: | :------: | :------: | :------: |
| **id** | int  | 11 | NO | Автоматический идентификатор пользователя |
| **array_index** | id | 11 | NO | Индекс элемента в массиве |
| **value** | id| 20 | 11 | Значение элемента |

### 5. Описание алгоритмов

Для сортировки массива используется алгоритм быстрой сортировки.

### 6. Значимые фрагменты кода

Функции используемые для сортировки массива:
```sh
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
```

