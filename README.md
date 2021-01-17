# **Cout**
Cout lib is a header-only library for SMTP client + example of SMTP client used this lib included
## List of modules features
#### SMTP Client
  Клиентский SMTP фреймворк для отправки емейлов на почтовые сервисы по протоколу SMTP.
- Поддерживаются протоколы аутентификации, шифрования с использованием OpenSSL (1)(2)(3)(4)(5)
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
- Переход на noexcept версии функций по максимуму, избавление от исключений из core проекта

## Requirements
Language
- c++17 and higher

Compilator
- MVSC++ 2017 and higher

External
- OpenSSL (1.1.1d)

## Usage
[How to start](https://github.com/imnetcat/cout/wiki/How-to-start)

[Docs](https://github.com/imnetcat/cout/wiki)

## Demo
В [файлах](https://github.com/imnetcat/cout/tree/master/examples) содержится несколько пример демо-приложения smtp клиента для наглядной демонстрации.

## **Platform**
Desktop Windows-based x64

## **Tests**
Я использовал [свой собственный](https://github.com/imnetcat/cout/tree/master/core/testing) фреймворк для тестирования

## License
Copyright (c) 2020 Radioactive lab

This software is [MIT licensed](./LICENSE).

## 

(1) Simple Mail Transfer Protocol (в соответствии с спецификацией [RFC 5321](https://tools.ietf.org/html/rfc5321 "Documentation"), [RFC 7504](https://tools.ietf.org/html/rfc7504 "Documentation"))

(2) Extended SMTP (в соответствии с спецификацией [RFC 5321](https://tools.ietf.org/html/rfc5321 "Documentation"), [RFC 7504](https://tools.ietf.org/html/rfc7504 "Documentation"))

(3) ESMTP with authentication plagin (в соответствии с спецификацией [RFC 4954](http://www.rfc-editor.org/rfc/rfc4954 "Documentation"))

(4) ESMTP with security plagin SSL/TLS (в соответствии с спецификацией [RFC 3207](https://tools.ietf.org/html/rfc3207 "Documentation"), [RFC 7817](https://tools.ietf.org/html/rfc7817 "Documentation"))

(5) ESMTP with authentication & security plagins

