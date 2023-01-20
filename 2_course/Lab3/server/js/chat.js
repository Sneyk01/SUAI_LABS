let message_count = 0;
$(document).ready(function (){
    $(document).on("click", ".enter_chat", function (){
        let chat_id = ($(this).attr("id"));
        window.history.replaceState({chat_id: chat_id}, "", "index.php?chat_id="+chat_id);

        $.get("template/chat.php?chat_id="+chat_id, function (data) {
            $(".container-fluid").html(data);
        })

        clearInterval(auto_update);
        auto_update = setInterval(function() {insert_chat(chat_id)}, 1000);

        $("#login_field").attr("readonly", true);
        $("#login_button").attr("disabled", true);

    })

    $(document).on("click", "#message_button", function (){
        let message = $("#message_input").val();
        let chat_id = $("#chat_id").val();
        if (message_count > 10) {
            alert("Эй, помедленнее!")
            return;
        }
        $.ajax({
            url: "edit_table.php",
            type: "POST",
            dataType: "html",
            data: {
                method: "add_message",
                message: message,
                chat_id: chat_id,
                delete_time: $("input:checked").val(),
                sender_id: $("#user_id").val(),
                sender_name: $("#user_name").val()
            },
            success: function (data) {
                message_count++;
                data = JSON.parse(data);
                if (data["result"] === "True") {
                    insert_chat(chat_id);
                    $("#message_input").val("");
                    $("input:checked").attr("checked", false);
                    $("#null_radio").prop("checked", true);
                    setTimeout(function (){
                        $(".scrollable_chat").scrollTop($(".scrollable_chat")[0].scrollHeight);
                    }, 100);
                }
            }
        })
    })
    clearTimeout(flood);
    flood = setTimeout(reset_count, 60000);
})

function insert_chat(chat_id){

    $.get("template/chat_messages.php?chat_id="+chat_id, function (data) {
        $(".scrollable_chat").html(data);
    })
}

function check_chat(chat_id, last_id=0){
    $.ajax({
        url: "template/chat_messages.php",
        type: "POST",
        dataType: "html",
        data: {
            last_id: last_id,
            chat_id: chat_id,
        },
        success: function (data) {
            data = JSON.parse(data);
            if (data["result"] === "True") {

            }
        }
    })
}

function reset_count(){
    message_count = 0;
}