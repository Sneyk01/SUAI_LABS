<?php

include_once "functions.php";
if (check_cookie())
    header("location: index.php");

?>

<!DOCTYPE html>
<html lang="ru" xmlns="http://www.w3.org/1999/html">

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


    <!--<link href="css/bootstrap.min.css" rel="stylesheet"> Для локального использования
    <script defer src="js/bootstrap.bundle.min.js"></script>
    -->
</head>

<body>
<div class="header_div mb-5" > <h1 class="text-white mb-3" style="margin-left: 1%"> ВЧАТЕ  </h1> </div>

<div class="container">
    <div class="row justify-content-center align-items-center row_h">
        <div class="col-1"> </div>
        <div class="col-lg-4" align="center">
            <figure class="figure bg-blue rounded-3">
                <form id = "login">
                    <ul class="me-3 padding">
                        <li class="text-white mt-4 float-start">Имя пользователя</li>
                        <li> <input class="form-control col-12" type="text" name="login" value="<?php echo "user_".gen_str(5)?>" </li>
                        <li class="mb-5"> <p class="float-start text-white mb-0" id="login_message"> <?php message();?></p> </li>
                        <li> <button type="submit" class="btn btn-light col-12 shadow-none"> Войти </button> </li>
                    </ul>
                </form>
            </figure>
        </div>
        <div class="col-1"> </div>
    </div>
</div>
</body>
</html>

<script>
    $("document").ready(function () {
        $("#login").on("submit", function(){
            event.preventDefault();
            $.ajax({
                url: 'handler.php',
                type: 'POST',
                dataType: 'html',
                data: $(this).serialize(),
                success: function (data){
                    if (data === "True") {
                        location.href = "index.php"
                    }
                    else
                        $("#login_message").html(data);
                }
            })
        })

        if (window.location.search !== "")  // Если есть get параметры, то удаляем их. (Для сообщения об окончании сессии и чтобы было красиво)
            window.history.pushState({}, document.title, "login.php");
    })
</script>


