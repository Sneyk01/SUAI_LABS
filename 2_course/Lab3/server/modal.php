<div class="modal fade" id="addFormModal" tabindex="-1" aria-labelledby="addFormModalLabel" aria-hidden="true">
    <div class="modal-dialog">
        <div class="modal-content">
            <div class="modal-header">
                <h1 class="modal-title fs-5" id="addFormModalLabel">Новый чат</h1>
                <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Закрыть"></button>
            </div>
            <div class="modal-body">

                <div class="mb-2 text-center" style="color: red; height: 15px" id="message_add_chat"></div>

                <form id="add_chat">
                    <div class="mb-2">
                        <label for="chat_name" class="col-form-label">Название чата:</label>
                        <input type="text" class="form-control" id="chat_name" name="chat_name">
                        <div class="form-text">Максимум 80 символов</div>
                    </div>
                    <div class="mb-2">
                        <label for="chat_type" class="col-form-label">Тип чата:</label>
                        <input type="text" class="form-control" id="chat_type" name="chat_type" readonly>
                    </div>
                    <div class="mb-2">
                        <label for="chat_access" class="col-form-label">Доступ:</label>
                        <input type="" class="form-control" id="chat_access" name="chat_access">
                        <div class="form-text">Введите через ';' имена тех, у кого будет доступ к этому чату</div>
                    </div>
                    <input type="hidden" name="method" value="add_chat">
                    <input type="hidden" name="login" id="login_add_chat" value=>
                </form>

            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Закрыть</button>
                <button type="submit" id="submit_add_chat" form="add_chat" class="btn btn-success">Создать запись</button>
            </div>
        </div>
    </div>
</div>
