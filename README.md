Cirno
=====

A template for building conventional "Arduino style" applications for the TiLDA MKe (specifically the version handed out at EMF 2014, probably won't work with earlier versions).

Whilst FreeRTOS is a much better way to develop complex applications (such as the default badge firmware) it can be overkill for more simple applications and intimidating for those who have not used an Arduino before. Cirno aims to be a more conventional alternative framework.

By default only the bare minimum hardware is supported, i.e. GLCD, RGB LEDs and buttons. This is partially to keep the binary size as low as possible and partially to keep the code down to the bare minimum.

Libraries
---------

The following libraries are used:

- [U8glib](https://code.google.com/p/u8glib/)
- [UniversalButtons](https://github.com/DanNixon/ArduinoUniversalButtons)
