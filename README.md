# **Email client**
Реализация фреймворка для отправки емейлов на почтовые сервисы (список поддерживаемых ниже) по протоколу SMTP. Поддерживаются протоколы SMTP (Simple Mail Transfer Protocol), ESMTP (Extended SMTP), ESMTPA (ESMTP with authentication plagin) и SMTPS (ESMTP with security plagin: SSL/TLS с помощью OpenSSL), а так же ESMTPSA (ESMTP with authentication & security plagins)
## **Platform**
Desktop Windows-based x32-64

## tested
- Desktop Windows 7 x64
## not tested (но должно работать:/)
- Desktop Windows XP x64
- Desktop Windows XP x32
- Desktop Windows 7 x32
- Desktop Windows 8 x64
- Desktop Windows 8 x32
- Desktop Windows 8.1 x64
- Desktop Windows 8.1 x32
- Desktop Windows 10 x64
- Desktop Windows 10 x32

## **Dependencies**
- c++17 и выше
- STL
- OpenSSL

## **Functional**
Поддерживаемые почтовые сервисы:
- gmail 
- hotmail
- aol
- yahoo

Поддержка обычной, ВСС (Blind Carbon Copy) и СС (Carbon Copy) рассылки

Поддержка прикриплённых файлов всех возможных форматов

## **Docs**
Необходимый заголовочный файл
```
#include "email-client/email.h"
```

*Ремарочка: компилировать с помощью MVSC++ 2017 или выше

