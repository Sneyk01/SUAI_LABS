$(document).on("click", "#create", function () {
    let size = (prompt("Размер нового массива:"));
    if (!(/^\d+$/.test(size)) || size < 1 || size > 500) {
        alert("Введите корректный размер массива! (Число от 1 до 500)");
        return
    }
    $.ajax({
        url: "edit_db.php",
        type: "POST",
        dataType: "html",
        data: {
            method: "create",
            size: size
        },
        success: function (data) {
            show_array(data);
        }
    })
})

$(document).on("click", "#show", function () {
    $.ajax({
        url: "edit_db.php",
        type: "POST",
        dataType: "html",
        data: {
            method: "show"
        },
        success: function (data) {
            show_array(data);
        }
    })
})

$(document).on("click", "#sort", function () {
    $.ajax({
        url: "edit_db.php",
        type: "POST",
        dataType: "html",
        data: {
            method: "sort"
        },
        success: function (data) {
            show_array(data);
        }
    })
})

function show_array(data) {
    $("#data").text("");
    data = JSON.parse(data);
    $("#data").append("<p class='fw-bold'>"+data.array+"</p>");
}