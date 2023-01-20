$(document).ready(function (){
    auto_update = setInterval(all_chats, time_update)
    $(document).on("click", ".chat_list", function (){
        if (!$(this).hasClass("btn-success")) {
            $(".btn-success").eq(1).removeClass("btn-success").addClass("btn-light border");
            $(this).removeClass("border").removeClass("btn-light").addClass("btn-success");
        }
    })

    $(document).on("click", "#all_chats", function (){
        clearInterval(auto_update);
        all_chats();
        auto_update = setInterval(all_chats, time_update)
    })
    $(document).on("click", "#public_chats", function (){
        clearInterval(auto_update);
        public_chats();
        auto_update = setInterval(public_chats, time_update)
    })
    $(document).on("click", "#private_chats", function (){
        clearInterval(auto_update);
        private_chats();
        auto_update = setInterval(private_chats, time_update)
    })
})

function all_chats() {
    $.get("template/all_chats.php", function (data) {
        $("#chats").html(data);
    })
}
function public_chats() {
    $.get("template/public_chats.php", function (data) {
        $("#chats").html(data);
    })
}
function private_chats() {
    $.get("template/private_chats.php", function (data) {
        $("#chats").html(data);
    })
}