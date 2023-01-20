function pong() {
    //setInterval(fps, 1000);
    let key = 0;
    let timer = 0;
    let p_timer = 0;
    let frame = 0;
    let level = 0;
    let message;

    let field = {
        size_x: 800,
        size_y: 400
    };

    let keys = [];
    keys[38] = 0;
    keys[40] = 0;

    let ball = {
        x: 200,
        y: 400,
        r: 6
    }

    let platform1 = {
        x: 40,
        y: 180,
        speed_key_y: 4,
        vy: 0,
        size_x: 8,
        size_y: 40,
        max_speed: 12,
        score: 0
    };
    let platform2 = {};

    let game = document.getElementById("canvas");
    let ctx = game.getContext('2d');
    console.log(1);

    ctx.font = "22px system-ui, sans-serif";

    ws.send(JSON.stringify({type: "ready"})); // Файл отображен, можно начинать

    ws.addEventListener("message", game_message);

    function game_message (data) {
        message = JSON.parse(data.data)

        if (message.type === "init_game") {

            window.addEventListener("keydown", function (e) {keyDown(e);});
            window.addEventListener("keyup", function (e) {keyUp(e);});

            console.log("Initialization complete");
            player_sync();
            p_timer = setInterval(player_sync, 5000);
            level = message.level;
            console.log(level);
            console.log("level");
            start();
        }

        if (message.type === "pos") {
            //player_sync();

            platform2.x = message.x2;
            platform2.y = message.y2;
            platform2.size_x = message.size_x2;
            platform2.size_y = message.size_y2;
            ball.x = message.ball_x;
            ball.y = message.ball_y;

            platform1.score = message.score1;
            platform2.score = message.score2;

            platform1.radius = Math.floor(platform1.size_x/2);
            platform2.radius = Math.floor(platform2.size_x/2);
        }

        if (message.type === "You win") {
            stop("Вы победили! Плюс " + message.change_score + " очков");
            ws.send(JSON.stringify({type: "ping"}));
        }
        if (message.type === "You lose") {
            stop("Вы проиграли");
            ws.send(JSON.stringify({type: "ping"}));
        }

        if (message.type === "close_game") {
            stop("Противник вышел из игры, вам начислено 20 очков");
            ws.send(JSON.stringify({type: "ping"}));
        }
    }

    ws.onclose = function () {
        stop("Потеряно соединение с сервером");
    }

    function keyUp(e) {
        keys[e.keyCode] = 0;
    }

    function keyDown(e) {
        keys[e.keyCode] = 1;
    }

    function start() {
        timer = setInterval(update, 1000/60);
    }

    function stop(message) {
        ctx.clearRect(0, 0, game.width, game.height);
        game.style.zIndex = "-10";
        clearInterval(timer);
        clearInterval(p_timer);
        ws.removeEventListener("message", game_message);
        $("#main_container").load("lobby.html");
        alert(message);
    }

    function update() {
        if (keys[38] === 1 && keys[40] === 0) {
            if (Math.abs(platform1.vy) < platform1.max_speed) {
                if (key !== 38)
                    platform1.vy = -1 * platform1.speed_key_y;
                platform1.vy -= 0.4;
            }
            key = 38;
        } // Вверх

        if (keys[40] === 1 && keys[38] === 0) {
            if (Math.abs(platform1.vy) < platform1.max_speed) {
                if (key !== 40)
                    platform1.vy = platform1.speed_key_y;
                platform1.vy += 0.4;
            }
            key = 40;
        } // Вниз

        if (keys[38] === 1 && keys[40] === 1) {
            platform1.vy = 0;
            key = 0;
        }

        if (keys[38] === 0 && keys[40] === 0) {

            if (platform1.vy > 0.) {
                //console.log(platform1.vy);
                platform1.vy -= 0.4;
                if (platform1.vy < 0.)
                    platform1.vy = 0;
            }

            if (platform1.vy < 0.) {
                platform1.vy += 0.4;
                if (platform1.vy > 0.) // -0.2 + 0.4 = 0.2 и так бесконечно
                    platform1.vy = 0;
            }
            key = 0;
        }

        platform1.vy = Math.round(platform1.vy*10)/10;
        platform1.y += platform1.vy;

        if (platform1.y + platform1.size_y + platform1.radius >= field.size_y) {
            platform1.y = field.size_y - platform1.size_y - platform1.radius;
            platform1.vy = (Math.round(platform1.vy*6)/10) * -1;
        }
        if (platform1.y - platform1.radius <= 0) {
            platform1.y = platform1.radius;
            platform1.vy = (Math.round(platform1.vy*6)/10) * -1;
        }

        ws.send(JSON.stringify({type: "pos", x: platform1.x, y: platform1.y, vy: platform1.vy}));
        //console.log(JSON.stringify({type: "pos", x: platform1.x, y: platform1.y, vy: platform1.vy}));
        draw();
    }

    function draw() {

        ctx.clearRect(0, 0, game.width, game.height);
        let x_score, y_score = 30;

        if(platform1.x < field.size_x/2)
            ctx.fillStyle = "#FF073A";
        else
            ctx.fillStyle = "#FFEA19";

        x_score = 360;


        ctx.fillRect(platform1.x, Math.round(platform1.y), platform1.size_x, platform1.size_y);

        ctx.beginPath(); // Тут рисуем закругления у платформ
        ctx.arc(platform1.x+ platform1.radius, Math.round(platform1.y), platform1.radius, 0, Math.PI*2, false);
        ctx.closePath();
        ctx.fill();
        ctx.beginPath();
        ctx.arc(platform1.x + platform1.radius, Math.round(platform1.y)+platform1.size_y, platform1.radius, 0, Math.PI*2, false);
        ctx.closePath();
        ctx.fill();

        ctx.fillStyle = "#FF073A";
        ctx.fillText(platform1.score, x_score, y_score);

        if(platform2.x < field.size_x/2)
            ctx.fillStyle = "#FF073A";
        else
            ctx.fillStyle = "#FFEA19";

        x_score = 440;

        ctx.fillRect(platform2.x, Math.round(platform2.y), platform2.size_x, platform2.size_y);

        ctx.beginPath();
        ctx.arc(platform2.x+platform2.radius, Math.round(platform2.y), platform2.radius, 0, Math.PI*2, false);
        ctx.closePath();
        ctx.fill();
        ctx.beginPath();
        ctx.arc(platform2.x+platform2.radius, Math.round(platform2.y)+platform2.size_y, platform2.radius, 0, Math.PI*2, false);
        ctx.closePath();
        ctx.fill();

        ctx.fillStyle = "#FFEA19";
        ctx.fillText(platform2.score, x_score, y_score);

        ctx.fillStyle = "#FFF";

        ctx.beginPath();
        ctx.arc(Math.round(ball.x), Math.round(ball.y), ball.r, 0, Math.PI*2, false);
        ctx.closePath();
        ctx.fill();

        if (level == 3) {
            draw_wall(10);
        }
        if (level == 4) {
            draw_wall(5);
        }
        if (level == 5) {
            draw_wall(3);
        }

        frame++;
    }

    function fps() {
        console.log(frame);
        frame = 0
    }

    function player_sync() {
        platform1.x = message.x;
        platform1.y = message.y;
        platform1.size_x = message.size_x;
        platform1.size_y = message.size_y;
    }

    function draw_wall(h) {
        ctx.fillStyle = "#FFF";
        ctx.fillRect(field.size_x/2-5, 0, 10, Math.round(field.size_y/h));
        ctx.fillRect(field.size_x/2-5, field.size_y, 10, Math.round(-field.size_y/h));
    }

}