## Калькулятор

Программа разработана на NetBeans IDE, для unit-тестирования использовалась библиотека CppUnit (файлы тестов находятся в папке tests).

Для того чтобы собрать Release версию программы, необходимо воспользоваться командой:

`make -f Makefile CONF=Release`

Для запуска:

`dist/Release/GNU-Linux/calculator`

После запуска необходимо ввести выражение и нажать клавишу *Enter*. Для того чтобы остановить выполнение программы, необходимо ввести *exit*.

Для того чтобы собрать и запустить тесты, необходимо воспользоваться командами:

`make -f nbproject/Makefile-Release.mk SUBPROJECTS= .build-tests-conf`

`make -f nbproject/Makefile-Release.mk SUBPROJECTS= .test-conf`
