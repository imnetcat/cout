# **Email client**
## Concept
  Клиентский SMTP фреймворк, а так же простое консольное клиентское приложение на его основе, для отправки емейлов на почтовые сервисы (список поддерживаемых ниже) по протоколу SMTP.
  Поддерживаются протоколы SMTP(1), ESMTP (2), ESMTPA (3) и ESMTPS (4) с использованием OpenSSL, а так же ESMTPSA (5)
  
(1) Simple Mail Transfer Protocol (в соответствии с спецификацией [RFC 5321](https://tools.ietf.org/html/rfc5321 "Documentation"), [RFC 7504](https://tools.ietf.org/html/rfc7504 "Documentation"))

(2) Extended SMTP (в соответствии с спецификацией [RFC 5321](https://tools.ietf.org/html/rfc5321 "Documentation"), [RFC 7504](https://tools.ietf.org/html/rfc7504 "Documentation"))

(3) ESMTP with authentication plagin (в соответствии с спецификацией [RFC 4954](http://www.rfc-editor.org/rfc/rfc4954 "Documentation"))

(4) ESMTP with security plagin SSL/TLS (в соответствии с спецификацией [RFC 3207](https://tools.ietf.org/html/rfc3207 "Documentation"), [RFC 7817](https://tools.ietf.org/html/rfc7817 "Documentation"))

(5) ESMTP with authentication & security plagins

## **Platform**
Desktop Windows-based x32-64

## **Tests**
Я использовал свой собственный фреймворк для юнит-тестирования который отдельно можно найти по [ссылке](https://github.com/imnetcat/utest)

В файле [main.cpp](https://github.com/imnetcat/email-client/blob/master/main.cpp) есть вызовы тестов, сами же тесты определены в [соответсвующем файле](https://github.com/imnetcat/email-client/blob/master/tests.cpp)

## Requirements
Language
- c++17 and higher
- c++ STL containers

Compilator
- MVSC++ 2017

External
- OpenSSL

## Feature list
Не создаёт временных файлов

Поддержка прикриплённых файлов всех возможных форматов (читает файл по 54 байта и отправляет, не загружая файл в оперативную память целиком)

Поддерживаемые почтовые сервера:
- gmail 
- hotmail
- aol
- yahoo
- любые ваши почтовые сервера, использующие SMTP

Поддержка обычной, ВСС (Blind Carbon Copy) и СС (Carbon Copy) рассылки

Использовать только символы 7-bit ASCII
## Features to be implemented in next release
Поддержка Linux-based платформ

## Demo
В файле [main.cpp](https://github.com/imnetcat/email-client/blob/master/main.cpp) содержится демо-приложение для наглядной демонстрации возможностей фреймворка.

## Usage
[How to start](https://github.com/imnetcat/email-client/wiki/How-to-start)

[Docs](https://github.com/imnetcat/email-client/wiki)

## License
Copyright (c) 2020 Radioactive lab

This software is [MIT licensed](./LICENSE).
