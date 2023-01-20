<?php
include_once "functions.php";
check_cookie();
check_users(connect_db());
?>

<!DOCTYPE html>
<html lang="ru">

<head>
    <!-- Кодировка веб-страницы -->
    <meta charset="utf-8">
    <!-- Настройка viewport -->
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title> ВЧАТЕ </title>

    <link rel="stylesheet" href="css/styles.css">

    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
    <script defer src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
    <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.9.0/jquery.min.js"></script>
    <script type="text/javascript" src="http://code.jquery.com/color/jquery.color-2.1.2.js"></script>   <!-- Для анимаций цвета -->
</head>

<body>
<div class="row header_div mb-3">
    <div class="col-1"><a href="index.php" style="text-decoration: none"><h1 class="text-white mb-3" style="margin-left: 2%">  ВЧАТЕ </h1></a></div>
    <div class="col-5"></div>
    <div class="col-2"></div>
    <div class="col-2"> <p class="mb-0 mt-2 float-end fs-5 text-white"> Имя пользователя:</p> </div>
    <div class="col-1"> <input id="login_field" type="text" class="form-control mt-2 col-12" value="<?php echo get_login()?>"> </div>
    <div class="col-1"> <button type="submit" id="login_button" class="col-10 me-2 float-end btn btn-light border mt-2 ps-1">Изменить</button></div>
    <input type="hidden" id="cur_login" value="<?php echo get_login()?>"> <!-- Чтобы знать текущий логин (в верхнем поле может быть не принятый) -->
    <!--<div class="col-1"> <button type="submit" class="col-10 me-3 btn btn-light border mt-2">Выход</button></div>-->
</div>

<div class="container-fluid">
    <div class="row mb-3">
        <div class="col-10"> <p class="fs-4 fw-bold mb-0"> Список чатов:</p> </div>
        <div class="col-2"> <button name="public" class="create_chat btn btn-success col-12" data-bs-toggle="modal" data-bs-target="#addFormModal"> Создать чат</button></div>
    </div>
    <div class="row mb-5">
        <div class="col-2"> <button id="all_chats" class="btn btn-success col-12 chat_list"> Все чаты</button> </div>
        <div class="col-2"> <button id="public_chats" class="btn btn-light border col-12 chat_list"> Публичные чаты</button> </div>
        <div class="col-2"> <button id="private_chats" class="btn btn-light border col-12 chat_list"> Приватные чаты</button> </div>
        <div class="col-4"></div>
        <div class="col-2"> <button name="private" class="create_chat btn btn-success col-12 float-end" data-bs-toggle="modal" data-bs-target="#addFormModal"> Создать приватный чат</button></div>
    </div>
    <div id="chats" class="scrollable col-12">
        <?php include("template/all_chats.php"); ?>
    </div>
</div>
</body>

<script>
    let auto_update;
    let time_update = 10000;
    let flood;
</script>

<script src="js/change_buttons.js"></script>
<script src="js/chats_list_buttons.js"></script>
<script src="js/reset_modal_windows.js"></script>
<script src="js/chat.js"></script>

</html>
<?php
include_once "modal.php";
?>