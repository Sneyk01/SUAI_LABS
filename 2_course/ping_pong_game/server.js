const WebSocket = require("ws");
const express = require("express");
const http = require("http");

const app = express();
const server = http.createServer(app);
const wsServer = new WebSocket.Server({server});

const path = require("path");

const hostname = "127.0.0.1";
const port = 8999;


let top = [];

top[0] = {
    login: "Bob",
    rating: 0
}

top[1] = {
    login: "Bob",
    rating: 0
};
top[2] = {
    login: "Bob",
    rating: 0
};

let players = [];
let players_count = 0;
let game = {
    w: 800,
    h: 400
};
let balls = [];
let type_hit = 0;
let block_hit = true;
wsServer.on("connection", onConnect);

function onConnect(wsClient, req) {
    let id = Math.floor(Math.random()*1000);
    players[id] = {
        ws: wsClient,
        login: "",
        status: 0,  // 0 - поиск простой игры, 1 - в игре, 2 - в лобби, 3 - поиск легкой игры, 4 - поиск средней игры, 5 - поиск тяжелой игры
        score: 0,
        x: 0,
        y: 180,
        size_x: 8,
        size_y: 40,
        rating: 0,
        interval: null
    };

    console.log("Кто-то пришел "+id);

    wsClient.on("message", function (message){
        message = JSON.parse(message);

        if (message.type === "start_search") {
            console.log(message.login + " начал поиск с id: " +message.level);
            players[id].status = message.level;
            players[id].login = message.login;
            players_count++;
            for (let key in players) {
                    if (players[key].status == players[id].status && key != id && check_rating(players[id], players[key])) {
                        console.log("Игрок найден");
                        players[key].enemy = id;
                        players[id].enemy = key;
                        start_game(id, key);
                    }
            }
        }
        if (message.type === "stop_search") {
            players[id].status = 2;
            console.log(players[id].login + " закончил поиск")
        }
        if (message.type === "pos") {
            players[id].x = message.x;
            players[id].y = message.y;
            players[id].vy = message.vy;

        }
        if (message.type === "ready") {
            let id1 = id;
            let id2 = players[id].enemy;

            if (players[id2].interval == null) { // Чтобы не ставилось два интервала
                init_game(id1, id2);
                play_game(id1, id2);
                players[id1].interval = setInterval(function () {
                    play_game(id1, id2);
                }, 1000/60);
                players[id2].interval = players[id1].interval;
            }
            else
                players[id1].interval = players[id2].interval;
        }
        if (message.type === "ping" && (players[id].status === 0 || players[id].status === 2))
            players[id].ws.send(JSON.stringify({type: "score",player_score: players[id].rating, login: players[id].login, top1: top[0], top2: top[1], top3: top[2]}));
    })

    wsClient.on("close", function(){
        clearInterval(players[id].interval);
        console.log("Кто-то ушел " + id);

        if ("enemy" in players[id]) {
            let id_enemy = players[id].enemy;
            players[id_enemy].ws.send(JSON.stringify({type: "close_game"}));
            delete players[id_enemy].enemy;
            delete players[id_enemy].interval;
            players[id_enemy].status = 2;
            players[id_enemy].rating += 20;
            console.log("Закрыли игру для " + id_enemy);
            check_best_score(players[id_enemy]);
        }

        delete players[id];
        players_count--;
        console.log("На сервере: " + players_count);
    });
}

app.use(express.static(__dirname));
app.get("/", function (request, response) {
    response.sendFile(path.join(__dirname, "index.html"));
});
server.listen(port, () => console.log("Server started"));

function start_game(id1, id2) {
    console.log("ID: ", id1, id2);

    if (players[id1].status == 0) {
        players[id1].mod = 0.7;
        players[id2].mod = 0.7;
    }
    if (players[id1].status == 3) {
        players[id1].mod = 1;
        players[id2].mod = 1;

        create_block(game.block1, game.block2, 10);
    }
    if (players[id1].status == 4) {
        players[id1].mod = 1.5;
        players[id2].mod = 1.5;

        create_block(game.block1, game.block2, 5);
    }
    if (players[id1].status == 5) {
        players[id1].mod = 2;
        players[id2].mod = 2;

        create_block(game.block1, game.block2, 3);
    }

    players[id1].x = 40;
    players[id2].x = 760;

    players[id1].y = 180;
    players[id2].y = 180;

    players[id1].score = 0;
    players[id2].score = 0;

    players[id1].r = Math.floor(players[id1].size_x / 2);
    players[id2].r = Math.floor(players[id2].size_x / 2);

    let ball_id = Math.floor(Math.random()*1000);

    players[id1].ball_id = ball_id;
    players[id2].ball_id = ball_id;

    balls[ball_id] = reset_ball();

    players[id1].ws.send(JSON.stringify({type: "start"}));
    players[id2].ws.send(JSON.stringify({type: "start"}));
}

function init_game(id1, id2) {
    players[id1].ws.send(JSON.stringify({type: "init_game", x: players[id1].x, y: players[id1].y, size_x: players[id1].size_x, size_y: players[id1].size_y, level: players[id1].status}));
    players[id2].ws.send(JSON.stringify({type: "init_game", x: players[id2].x, y: players[id2].y, size_x: players[id2].size_x, size_y: players[id2].size_y, level: players[id1].status}));

    players[id1].status = 1;
    players[id2].status = 1;
}
function play_game(id1, id2) {
    if (players[id1].x > players[id2].x) { // id1 слева, id2 справа
        id1 = id2;
        id2 = players[id1].enemy;
    }
    let ball_id = players[id1].ball_id;

    if (balls[ball_id].vx > balls[ball_id].max_vx)
        balls[ball_id].vx = balls[ball_id].max_vx;

    if (balls[ball_id].vy > balls[ball_id].max_vy)
        balls[ball_id].vy = balls[ball_id].max_vy;

    balls[ball_id].x += balls[ball_id].vx;
    balls[ball_id].y += balls[ball_id].vy;

    phantom_platform(players[id1]);
    phantom_platform(players[id2]);

    check_platform_zone(balls[ball_id], players[id1]);
    platform_collision(balls[ball_id], players[id1]);

    check_platform_zone(balls[ball_id], players[id2]);
    platform_collision(balls[ball_id], players[id2]);

    if (players[id1].mod >= 1) { // Не 0-ой уровень
        //console.log(game.block1.x);
        block_collision(balls[ball_id], game.block1);
        block_collision(balls[ball_id], game.block2);
    }

    if ((balls[ball_id].x - balls[ball_id].r) <= 0 || (balls[ball_id].x + balls[ball_id].r ) >= game.w) {
        balls[ball_id].vx *= -1;

        if ((balls[ball_id].x - balls[ball_id].r ) <= 0)
            players[id2].score += 1;

        if ((balls[ball_id].x + balls[ball_id].r ) >= game.w)
            players[id1].score += 1;

        console.log(players[id1].score, players[id2].score);

        if (players[id1].score > 9) {
            players[id1].rating += 100 * players[id2].mod;
            players[id1].ws.send(JSON.stringify({type: "You win", change_score: 100 * players[id2].mod}));

            players[id2].ws.send(JSON.stringify({type: "You lose"}));
            if (players[id2].rating > 10)
                players[id2].rating -= 10;

            clearInterval(players[id1].interval);

            delete players[id1].enemy;
            delete players[id2].enemy;
            delete players[id1].interval;
            delete players[id2].interval;
            players[id1].status = 2;
            players[id2].status = 2;
            console.log("Игра кончилась для " + id1 + " "+ id2);
            check_best_score(players[id1]);
            check_best_score(players[id2]);

            return;
        }
        if (players[id2].score > 9) {
            players[id2].rating += 100*players[id2].mod;
            players[id2].ws.send(JSON.stringify({type: "You win", change_score: 100 * players[id2].mod}));
            players[id1].ws.send(JSON.stringify({type: "You lose"}));
            if (players[id1].rating > 10)
                players[id1].rating -= 10;

            clearInterval(players[id2].interval);

            delete players[id1].enemy;
            delete players[id2].enemy;
            delete players[id1].interval;
            delete players[id2].interval;
            players[id1].status = 2;
            players[id2].status = 2;
            console.log("Игра кончилась для " + id1 + " "+ id2);
            check_best_score(players[id1]);
            check_best_score(players[id2]);

            return;
        }

        balls[ball_id] = reset_ball();
    }

    if ((balls[ball_id].y - balls[ball_id].r) <= 0 || (balls[ball_id].y + balls[ball_id].r) >= game.h) {
        balls[ball_id].vy *= -1;

        if ((balls[ball_id].y - balls[ball_id].r) <= 0) {
            balls[ball_id].y = 0 + balls[ball_id].r;
            balls[ball_id].vy += 1.8;
        }

        if ((balls[ball_id].y + balls[ball_id].r) >= game.w) {
            balls[ball_id].y = game.h - balls[ball_id].r;
            balls[ball_id].vy -= 1.8;
        }
    }

    //console.log(id1);
    //console.log(JSON.stringify({from: "server", x: players[id1].x, y: players[id1].y, size_x: players[id1].size_x, size_y: players[id1].size_y, x2: players[id2].x, y2: players[id2].y, size_x2: players[id2].size_x, size_y2: players[id2].size_y}));
    players[id1].ws.send(JSON.stringify({type: "pos", x: players[id1].x, y: players[id1].y, size_x: players[id1].size_x, size_y: players[id1].size_y, x2: players[id2].x, y2: players[id2].y, size_x2: players[id2].size_x, size_y2: players[id2].size_y, ball_x: balls[ball_id].x, ball_y: balls[ball_id].y, score1: players[id1].score, score2: players[id2].score}));
    players[id2].ws.send(JSON.stringify({type: "pos", x: players[id2].x, y: players[id2].y, size_x: players[id2].size_x, size_y: players[id2].size_y, x2: players[id1].x, y2: players[id1].y, size_x2: players[id1].size_x, size_y2: players[id1].size_y, ball_x: balls[ball_id].x, ball_y: balls[ball_id].y, score1: players[id1].score, score2: players[id2].score}));

}

function reset_ball() {
    return {
        x: 400,
        y: 200,
        r: 6,
        vx: Math.pow((-((Math.random()) * (6 - 2) + 2)), Math.round(Math.random())),
        vy: Math.pow((-((Math.random()) * (6 - 2) + 2)), Math.round(Math.random())),
        max_vx: 11,
        max_vy: 11,
        platform_zone: false,
        hit: true
    };
}

function platform_collision(ball, platform) {

    let hit_distance = Math.sqrt(Math.pow((platform.x + platform.r - ball.x), 2));    // platform center
    let rad_sum = ball.r + platform.r;

    let up_edge_distance = Math.sqrt(Math.pow((platform.x + platform.r - ball.x), 2) + Math.pow((platform.y - platform.phantom_up - ball.y), 2));
    let down_edge_distance = Math.sqrt(Math.pow((platform.x + platform.r - ball.x), 2) + Math.pow((platform.y + platform.size_y + platform.phantom_down - ball.y), 2));

    if (!ball.hit && ball.platform_zone && (hit_distance <= rad_sum)) { // Если шарик оказывается внутри платформы
            if (type_hit === 2) {
                if (up_edge_distance < down_edge_distance)
                    ball.y = platform.y - platform.phantom_up - ball.r;
                else
                    ball.y = platform.y + platform.phantom_down + platform.size_y + ball.r;
            }

            if (type_hit === 1) {
                if(ball.x < game.h/2)
                    ball.x = platform.x + platform.size_x + ball.r;
                else
                    ball.x = platform.x - ball.r;
            }
            console.log("COLLISION! Type:" + type_hit);
    }

    if (hit_distance <= rad_sum && ball.platform_zone && ball.hit) {    // Удар о плоскость
        console.log("hit ", platform.x+platform.size_x, ball.x+ball.r, hit_distance, platform.phantom_down);
        ball.vx *= -1;
        ball.vx += 0.8;

        if (ball.vx > 0)
            ball.vx += 1.2;
        else
            ball.vx -= 1.2;

        if (ball.vy < 0)
            ball.vy -= platform.vy * 0.4;
        else
            ball.vy -= platform.vy * 0.4;

        one_hit(ball);
        type_hit = 1;
    }

    if ((up_edge_distance <= rad_sum || down_edge_distance <= rad_sum) && !ball.platform_zone && ball.hit) { // Удар о край
        console.log("edge ", platform.y+platform.r, ball.y+ball.r, up_edge_distance, down_edge_distance, platform.phantom_down);
        ball.vx *= -1;
        ball.vy *= -1;

        if (ball.vx > 0)
            ball.vx += 0.8;
        else
            ball.vx -= 0.8;

        one_hit(ball);
        type_hit = 2;
    }

}

function check_platform_zone(ball, platform) { // Чтобы знать, что шар напротив платформы
    ball.platform_zone = (ball.y > platform.y) && (ball.y < platform.y + platform.size_y);
}

function phantom_platform(platform) { //Чуть расширяем платформу, чтобы шар не попадал в нее
    if (platform.vy < 0) {
        platform.phantom_up = platform.vy * 2;
        platform.phantom_down = 0;
    }
    else if (platform.vy > 0) {
        platform.phantom_down = platform.vy * 2;
        platform.phantom_up = 0;
    }
    else {
        platform.phantom_up = 0;
        platform.phantom_down = 0;
    }

}

function one_hit(ball) {    // Чтобы шар не бился внутри платформы, если попал туда
    ball.hit = false;
    setTimeout(() => {
        ball.hit = true
    },1000);
}

function friction_force() {
    /*
    if (balls[ball_id].vx > 0.3)
        balls[ball_id].vx -= 0.0001;
    if (balls[ball_id].vx < -0.3)
        balls[ball_id].vx += 0.0001;

    if (balls[ball_id].vy > 0.3)
        balls[ball_id].vy -= 0.0001;
    if (balls[ball_id].vy < -0.3)
        balls[ball_id].vy += 0.0001;
    */
} // Старый неиспользуемый код силы трения для мячика

function check_best_score(player) {
    for(let key = 0; key<3; key++) {
        console.log(key);
        if (top[key].rating < player.rating) {
            console.log("yes");
            if (key !== 2) {
                top[key + 1].login = top[key].login;
                top[key + 1].rating = top[key].rating;
            }
            top[key].login = player.login;
            top[key].rating = player.rating;
            //console.log(key, ": ",top[key], key+1, ": ", top[key+1]);
            return;
        }
    }
}

function check_rating(player1, player2) {
    let rating1 = Math.max(player1.rating, player2.rating);
    let rating2 = Math.min(player1.rating, player2.rating);

    return (rating2 + 500 >= rating1);
}


function block_collision(ball, block) {
    let hit_y_distance1 = Math.sqrt(Math.pow((ball.x-(block.x+block.size_x/2)),2) + Math.pow((ball.y-(block.y+block.size_x/2)),2));
    let hit_y_distance2 = Math.sqrt(Math.pow((ball.x-(block.x+block.size_x/2)),2) + Math.pow((ball.y-(block.y+block.size_y-block.size_x/2)),2));
    if ((hit_y_distance1 <= (ball.r+block.size_x/2) || hit_y_distance2 <= (ball.r+block.size_x/2)) && block_hit) {
        ball.vy *= -1;
        if (ball.vy > 0)
            ball.vy += 0.8;
        else
            ball.vy -= 0.8;
        ball.vx += 0.05;
        console.log("yy");
        block_hit = false;
        setTimeout(() => block_hit = true, 100);
    }
    if(ball.x+ball.r >= block.x && ball.x-ball.r <= block.x+block.size_x && ball.y+ball.r>block.y && ball.y-ball.r < block.y + block.size_y && block_hit) {
        ball.vx *= -1;
        console.log("x");
    }

}

function create_block(block1, block2, h) {
    game.block1 = {
        x: game.w/2-5,
        y: 0,
        size_x: 10,
        size_y: game.h/h
    }
    game.block2 = {
        x: game.w/2-5,
        y: game.h-game.h/h,
        size_x: 10,
        size_y: game.h
    }
}
