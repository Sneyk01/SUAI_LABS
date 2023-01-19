# Лабораторная работа №4
------

## Основное задание
Разработать и реализовать многопользовательскую игру пинг-понг. Хранение и обработка модели происходит на сервере. Общение сервера и клиентов происходит по websocket. Для отрисовки вида используется canvas. Игра завершается при достижении нужного счета одним из игроков.
 
## Дополнительные задания

В качестве дополнительного функционала можно реализовать следующие задачи:

 - [x] Лобби ожидания
 - [x] Таблица лучших игроков
 - [x] Matchmaking
 - [x] дополнительные правила игры (препятствия)
 
## Ход работы

### 1. Разработка пользовательского интерфейса

В редакторе Figma был разработан прототип пользовательского интерфейса для лобби и самой игры.

- Дизайн лобби:
<p align = "center"><img src="https://github.com/Sneyk01/SUAI_LABS/blob/master/2_course/ping_pong_game/images/lobby.svg"/width = 50%></p>

- Игровое поле:
<p align = "center"><img src="https://github.com/Sneyk01/SUAI_LABS/blob/master/2_course/ping_pong_game/images/main.png"/width = 50%></p>

- Игровое поле с использованием одного из модификатора сложности:
<p align = "center"><img src="https://github.com/Sneyk01/SUAI_LABS/blob/master/2_course/ping_pong_game/images/main_mod.png"/width = 50%></p>

### 2. Описание пользовательских сценариев работы
При переходе на страничку игры перед пользователем поялвляется локальное лобби, где он может изменить свой ник, в случае если ему не нравится вариант, автоматически сгенерированный сервером.

После того, как пользователь нажмет на кнопку "Играть" или мерцающую надпись, будет осуществлена попытка подключения к серверу по технологии webSocket. 

В случае успешного подключения, пользователь сразу встанет в очередь на поиск игры в выбранном режиме. На страницу лобби автоматически подгрузится таблица с лучшими игроками. Пользователь может отменить поиск и выбрать другой режим игры, либо дождаться соперника.

Для игроков доступны 4 варианта игры с разными сложностями:
 - Стандартный уровень пинг-понга без препятствий
 - Легкий уровень, с небольшими препятствиями в центре карты
 - Средний уровень, со средними препятствиями в центре карты
 - Сложный уровень, с большими препятствиями в центре карты
 
 В игре реализована система рейтинга. За победу в игре игрок будет получать 100 очков, умноженных на модификатор уровня (0.7, 1, 1.5, 2 в зависимости от сложности). За поражение у пользователя отнимется 10 очков рейтинга. Если соперник выйдет во время матча, игрок получит 20 очков рейтинга.
 
 В зависимости от рейтинга, пользователь может попасть в таблицу лучших игроков. Также от рейтинга зависят соперники пользователя. Игроки, у которых рейтинг отличается больше, чем на 500 очков не смогут играть против друг друга.
 
 После того, как соперник будет найден, перед игроками появится игровое поле. Один пользователь будет управлять правой платформой, а другой - левой. Управление осуществляется при помощи стрелок вверх и вниз. За каждый пропущенный игроком мяч, соперник будет получать очко. Игра завершается, когда один из игроков наберет 10 очков.

### 3. Описание API сервера и хореографии

Взаимодействие клиента и сервера осуществляется при помощи webSoket-ов. 

Находяся в лобби, клиент раз в 55 секунд получает обновление данных для лобби - таблицу рейтинга, счет игрока и его ник.

Когда пользователь запускает поиск игры, на сервер отправляется сообщение, чтобы он начал искать соперника. После того, как игра найдена, клиент получает уведомление и заменяет часть элементов на сайте на canvas. Когда клиент завершит все изменения, он отправит сообщение о готовности и игра начнется.

Клиент обновляет изображение с частотой 60 кадров в секунду. С каждым обновлением страницы он отправляет координаты платформы игрока на сервер.

Во время игры сервер 60 раз в секунду отправляет клиентам информацию об игре: последние принятые координаты платформы игрока, последние принятые координаты платформы противника и координаты шара.

И клиент и сервер принимают сообщения по мере их поступления. (Таймер для этих действий не используется)

Движение платформы игрока, для плавности, вычисляется на стороне клиента. С целью предотвратить рассинхронизацию, раз в пять секунд координаты платформы игрока обновляются на те, что пришли с сервера.

Движение платформы противника осуществляется только по полученным с сервера координатам.

Расчет координат шарика и его столкновения с поверхностями, для избегания нечестной игры, осуществляется на стороне сервера. Клиенты отрисовывают шарик по полученным координатам.

После заврешения игры, сервер записывает результаты, пересчитывает таблицу рейтинга и отправляет клиентам сообщения о возвращении в лобби.

### 4. Описание структуры базы данных

В игре не используются базы данных и хранение информации в файлах. Вся собранная информация о счете игроков хранится в оперативной памяти и при перезагрузке сервера будет сброшена.

### 5. Описание алгоритмов


### 6. Значимые фрагменты кода
Фрагмент кода, реализующий коллизию шарика и платформы (серверная часть):
```sh
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
```

Фрагмент кода, реализующий движение платформы (клиентская часть):
```sh
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
```
Фрагмент кода первичной инициализации пользователя при подключении (серверная часть):
```sh
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

```
