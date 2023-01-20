$(document).ready(function (){
    $("#addFormModal").on("hidden.bs.modal", function (){
        $("#message_add_chat").text("")
        document.getElementById("add_chat").reset();
        $("#submit_add_chat").prop("disabled", false);
    })
})