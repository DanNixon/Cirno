Cirno
=====

A "ready to go" library for building conventional "Arduino style" applications for the TiLDA MKe.

Whilst FreeRTOS is a much better way to develop complex applications (such as the default badge firmware) it can be overkill for more simple applications and intimidating for those who have not used an Arduino before. Cirno aims to be a more conventional alternative framework by wrapping the interfaces to the essential pieces of hardware on the board in a single interface.

On the other hand there is a strong argument against use of FreeRTOS with Arduino libraries, since thread safety is pretty non existent.

By default only the bare minimum hardware is supported, i.e. GLCD, RGB LEDs and buttons. This is partially to keep the binary size as low as possible and partially to keep the code down to the bare minimum.

Libraries
---------

The following libraries are used:

- [U8glib](https://code.google.com/p/u8glib/)
- [UniversalButtons](https://github.com/DanNixon/ArduinoUniversalButtons)

To Do
-----

Add support for more hardware:

- Radio
- MPU
- IR
- Piezo speaker
