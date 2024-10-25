# Script-Server

Задание:
Написать плагинный сервер. Типов пользователей будет 2 - админ и обычный. Использовать авторизацию дайджест.
Если пользователь заходит под правами админа, ему доступна загрузка скриптов на сервер и возможность назначать права на запуск скрипта конкретным пользователям.
Обычный пользователь имеет одну возможность - запускать скрипты, разрешенные админом. Если же обычный пользователь выберет скрипт, в которому у него доступа нет, появится ошибка и скрипт не выполнится.
Скрипты разрешается писать на любом одном интерпретируемом языке. Рекомендуется Lua, так же можно JS или Python.
Рекомендуется сделать приложение кроссплатформенным

План выполнения:
1) Изучение возможностей работы c++ с сетями
2) Создание сервера, который может принимать запросы и отвечать на них
//3) Создание клиента, который может отправлять запросы серверу и получать ответы
4) Изучение lua
5) Добавление возможности хранения скрипта сервером
6) Добавление возможности выполнения сервером скрипта, запрошенного клиентом, и отправка результата работы клиенту
7) Добавление авторизации

