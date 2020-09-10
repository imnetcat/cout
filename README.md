# **Email client | Cout lib**
Cout lib is a modular header-only library for networking using C ++
## List of modules features
#### SMTP Client
  Клиентский SMTP фреймворк для отправки емейлов на почтовые сервисы по протоколу SMTP.
- Поддерживаются протоколы шифрования с использованием OpenSSL, а так же аутентификации (1)(2)(3)(4)(5)
- Не создаёт временных файлов
- Поддержка прикриплённых файлов всех возможных форматов (читает файл по 54 байта и отправляет, не загружая файл в оперативную память целиком)
- Поддерживаемые почтовые сервера: gmail, hotmail, aol, yahoo, а так же любые ваши почтовые сервера, использующие SMTP
- Поддержка обычной, ВСС (Blind Carbon Copy) и СС (Carbon Copy) рассылки
- Использовать только символы 7-bit ASCII

## Features to be implemented in next release
- Поддержка 32-bit Windows 
- Поддержка Linux-based платформ
- Самописная часть библиотеки stl для уменьшения веса (если тесты покажут заметное отличие веса)
- Раздельная, автономная компиляция модулей библиотеки по вашему конфигу для уменьшения веса - вы будете компилировать только то чем будете пользоватся!
- Telegram API
- HTTP API

## Requirements
Language
- c++17 and higher
- c++ STL containers

Compilator
- MVSC++ 2017

External
- OpenSSL (for SMTP)

## Usage
[How to start](https://github.com/imnetcat/cout/wiki/How-to-start)

[Docs](https://github.com/imnetcat/cout/wiki)

## Demo
В файле [main.cpp](https://github.com/imnetcat/cout/blob/master/main.cpp) содержится демо-приложение для наглядной демонстрации возможностей фреймворка.

## **Platform**
Desktop Windows-based x64

## **Tests**
Я использовал [свой собственный](https://github.com/imnetcat/cout/tree/master/core/testing) фреймворк для тестирования

В файле [main.cpp](https://github.com/imnetcat/cout/blob/master/main.cpp) есть вызов тестов, сами же тесты определены в [соответсвующем файле](https://github.com/imnetcat/cout/blob/master/tests.cpp)

## License
Copyright (c) 2020 Radioactive lab

This software is [MIT licensed](./LICENSE).

## 

(1) Simple Mail Transfer Protocol (в соответствии с спецификацией [RFC 5321](https://tools.ietf.org/html/rfc5321 "Documentation"), [RFC 7504](https://tools.ietf.org/html/rfc7504 "Documentation"))

(2) Extended SMTP (в соответствии с спецификацией [RFC 5321](https://tools.ietf.org/html/rfc5321 "Documentation"), [RFC 7504](https://tools.ietf.org/html/rfc7504 "Documentation"))

(3) ESMTP with authentication plagin (в соответствии с спецификацией [RFC 4954](http://www.rfc-editor.org/rfc/rfc4954 "Documentation"))

(4) ESMTP with security plagin SSL/TLS (в соответствии с спецификацией [RFC 3207](https://tools.ietf.org/html/rfc3207 "Documentation"), [RFC 7817](https://tools.ietf.org/html/rfc7817 "Documentation"))

(5) ESMTP with authentication & security plagins

