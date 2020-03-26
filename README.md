# **Email client**
Реализация почтового клиента для отправки емейлов на почтовые сервисы (список поддерживаемых ниже). Используется протокол SMTPS (SMTP и шифрованием SSL/TLS с помощью OpenSSL)
## **Platform**
Desktop

Windows-based

x32-64

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
## **Docs**
Поддерживаемые почтовые сервисы:
- gmail 
- hotmail
- aol
- yahoo

Необходимый заголовочный файл
```
#include "email-client/email.h"
```

*Ремарочка: компилировать с помощью MVSC++ 2017 или выше

