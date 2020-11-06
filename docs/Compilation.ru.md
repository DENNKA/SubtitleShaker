# Компиляция

## [Contents](README.ru.md)

## [ENGLISH](Compilation.md); НА РУССКОМ;
<!---
full line:
[ENGLISH](Compilation.md); [НА РУССКОМ](Compilation.ru.md);
-->

---
## Линукс
### Установка пакетов
Нужно установить: c++, git, make, boost
#### На основе Убунту
`sudo apt-get install git build-essential`  
`sudo apt-get install libboost-all-dev`  
ВНИМАНИЕ: версия boost должна быть не ниже 1.66  
Проверить версию:  
`apt-cache policy libboost-all-dev`  
Если версия мешьше ищем подходящую:  
`apt-cache search libboost1`  
и устанавливаеи, например:  
`sudo apt-get install libboost1.71-all-dev`  
### Make
`git clone git@github.com:DENNKA/SubtitleShaker.git`  
`cd SubtitleShaker/`  
`make debug`  
### Execute:
`./SubtitleShaker`  
Это ссылка, исполнительные файлы находятся в bin/debug и bin/release  

## Windows
### Visual Studio
 * Качаем буст https://www.boost.org
 * Распаковываем в C:\ (либо в другую директорию)
 * В меню пуск в папке Visual Studio открываем command promt
 * В командрую строку пишем:  
`cd C:\boost_X_XX_X`
 * Запускаем  
`.\boostrap.bat`  
 * Ждем и запускаем  
`.\b2 toolset=msvc --build-type=complete address-model=32 -j4`  
-j4 означает что будет использоваться 4 ядра подстовляем свое значение ядер  
компиляция займет 5гб места на диске  
 * Ждем
 * Когда скомпилировалось можно удалить папку bin.v2
 * Поздравляю если у тебя нет ошибок
 * Открываем SubtitleShaker.sln
 * Переходим в свойста и проверяем директории буста в C/C++ - Дополнительные катологи включаемых файлов (path_to_boost/) и В компоновщике - Дополнительные катологи библиотек (path_to_boost/stage/lib)
 * Компилируем x86
 * Радуемся жизни  
