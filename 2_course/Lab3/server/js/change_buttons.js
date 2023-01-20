$(document).ready(function () {
    $(document).on("click", "#login_button", function () {
        $("#login_field").stop(true, false);
        $.ajax({
            url: "edit_table.php",
            type: "POST",
            dataType: "html",
            data: {
                login: $("#login_field").val(),
                method: "change_name"
            },
            success: function (data) {
                data = JSON.parse(data);
                if (data["result"] === "True") {
                    $("#cur_login").val($("#login_field").val());
                    $("#login_field").animate({
                        "background-color": "#8BEA00"
                    }, 300);
                    $("#login_field").animate({
                        "background-color": "#FFFFFF"
                    }, 300);
                }
                if (data["result"] === "False") {
                    $("#login_field").animate({
                        "background-color": "#FF0700"
                    }, 300);
                    $("#login_field").animate({
                        "background-color": "#FFFFFF"
                    }, 300);
                }
            }
        })
    })

    $(document).on("click", ".create_chat", function () {
        $("#login_add_chat").val($("#cur_login").val());
        if ($(this).attr("name") === "private") {
            $("#chat_type").val("private");
            $("#chat_access").attr("readonly", false);
        }
        else {
            $("#chat_type").val("public");
            $("#chat_access").attr("readonly", true);
        }

    })
})

$(document).ready(function (){
    $(document).on("submit", "#add_chat", function () {
        event.preventDefault();
        $.ajax({
            url: "edit_table.php",
            type: "POST",
            dataType: "html",
            data: $(this).serialize(),
            success: function (data) {
                let message = document.getElementById("message_add_chat");
                data = JSON.parse(data);
                if (data["result"] === "True") {
                    message.style.color = "green";
                    $(message).text(data["message"]);
                    $("#submit_add_chat").prop("disabled", true);
                    let chat = document.getElementsByClassName("btn-success")[1].id;
                    eval(chat)(); // Вызов функции с именем как в id активной кнопки
                }
                if (data["result"] === "False") {
                    message.style.color = "red";
                    $(message).text(data["message"]);
                }
            }
        })
    })

})