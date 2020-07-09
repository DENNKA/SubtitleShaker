# subtitleShaker
---
# Work example (subtitles in the video below) / Пример работы (субтитры снизу видео)
![Work example](example.gif)

# ENGLISH
subtitleShaker it's a program that make .ass subtitles shaking.

## How does it work
Program add many phrases with tag \move that makes subtitles shaking.

## Options
```
subtitleShaker [options]
  -h          --help   Help
  -i         --input   Input file
  -o        --output   Output file
 -sf --settings_file   Settings file
  -s          --seed   Seed for random
Option in settings file:
  -s         --shake   Shake every n ms
  -i     --intensity   Intensity in pixels
 -ix   --intensity_x   Intensity in pixels at x
 -iy   --intensity_y   Intensity in pixels at y
  -q         --quiet   Quiet mode
  -m          --mode   Select mode
   Modes:
       use_pos   use \pos() instead of \move()
```

## How to use
* Download latest version https://github.com/DENNKA/subtitleShaker/releases/latest
* Put in one folder executable file (downloaded earlier) and your subtitles (.ass)
* Create settings file (for example setting.txt)
* Setup setting file

  #### How to setup
  How to setup i translate with google translator :)
  - We write the number (or range) of the phrase we need, write the -s option and the number, the number will show how many milliseconds the next phrase will be created
  (if we write -s 50 then each new phrase will appear after 50 milliseconds),
  the smaller the faster the subtitle will shake, at least 10, the last digit means nothing (the program sets zero instead (159 = 150, 19 = 10)),
  then we write -i and a number, the number will show how many pixels the subtitle needs to be shifted (for example, -i 5 - the subtitle will shake 5 pixels in each
  side), also separately for the horizontal -ix and vertical -iy.  
  - To process more phrases you just need to go to the next line (options will
   write absolutely also).
  - If you write a minus before the number (diazone) of the phrase, this will exclude it for processing
   (e.g. -11 or -15-45), lines starting with # are ignored
  - The -q option removes output
  
  What should it be like:
    * **Processing the first phrase (shaking every 50 milliseconds, at 5 pixels)**  
    * **1 -s 50 -i 5**  
  Range:
    * **Processing range of phrases (first to tenth inclusive)**  
    * **1-10 -s 50 -i 5**  
  Several phrases with different settings: 
    * **3 -s 20 -i 5**
    * **4-20 -s 100 -ix 3**  
    * **21-100 -s 40 -i 5**  
    * **2 -s 40 -i 5**  
  Exclusion:
    * **1-100 -s 50 -i 5**
    * **-44**  
    * **-60-70**  
  Magic tricks (intersection of options):
    * **1-100 -s 50 -q**
    * **1-20 -i 5**
    * **1-10 -iy 0**
    * **21-100 -iy 5**
* Run program:
  1. WINDOWS
      * Shift + Right click in folder
      * Click "open PowerShell window here" or "open command window here" and type with replacement for your parameters:
      * .\subtitleShaker.exe -i yoursubtitle.ass -o output.ass -sf settings.txt
      * Open output.ass
      * PROFIT!!!
  1. LINUX
      * In command line:
      * ./subtitleShaker -i subtitle.ass -o output.ass -sf settings.txt
  
# НА РУССКОМ
Программа позволяет трясти .ass субтитры

## Как работает
Создает множество фраз с тегом \move что создает ощущение тряски

## Опции  
```
subtitleShaker [опции]  
  -h          --help   Помощь  
  -i         --input   Исходный файл  
  -o        --output   Файл для вывода  
 -sf --settings_file   Файл настроек  
  -s          --seed   Семя для генерации случайных чисел  
Опции в файле настроек:  
  -s         --shake   Трясти каждые n миллисекунд  
  -i     --intensity   Интенсивность в пикселях  
 -ix   --intensity_x   Интенсивность в пикселях по x  
 -iy   --intensity_y   Интенсивность в пикселях по y  
  -q         --quiet   Тихий режим  
  -m          --mode   Выбор режима  
   Режим:  
       use_pos   использовать \pos() вместо \move()  
```

## Как использовать
* Скачайте последнюю версию (скачиваем .rar для своей платформы: windows или linux) https://github.com/DENNKA/subtitleShaker/releases/latest
* Поместите в одну папку скачаный ранее исполнительный файл и свои субтитры (.ass)
* Создайте файл настроек (например settings.txt)
* Пропишите нужные параметры в этом файле настроек
  #### Как прописать параметры
  
  - Пишем номер (или диапозон) нужной нам фразы, пишем опцию -s и число, число будет показывать через сколько миллисекунд будет создаваться следуящая фраза
  (если напишем -s 50 то каждая новая фраза будет появлятся через 50 миллисекунд),
  чем меньше тем быстрее субтитр будет трястись, минимум 10, последняя цифра ничего не значит (программа ставит вместо нее ноль (159 = 150, 19 = 10)),
  дальше пишем -i и число, число будет показывать на сколько пикселей нужно сдвигать субтитр (например -i 5 - субтитр будет трястись на 5 пикселей в каждую
  сторону), также есть отдельно для горизонтали -ix и вертикали -iy.  
  - Чтобы обработать еще фраз нужно просто перейти на следующую строку (опции будут
  писаться обсолютно также).  
  - Если написать перед номером (диаозоном) фразы минус, то это исключит ее для обработки
  (например -11 или -15-45), строчки начинающиеся на # игнорируются
  - Опция -q убирает вывод
  
  Что примерно должно получится:
  Обработка первой фразы (тряска каждые 50 миллисекунд, в 5 пикселей)**  
      * **1 -s 50 -i 5**  
  Диапозон:
  Обработка диапозона фраз (с первой по десятую включительно)**  
    * **1-10 -s 50 -i 5**  
  Несколько фраз с разными настройками: 
    * **3 -s 20 -i 5**
    * **4-20 -s 100 -ix 3**  
    * **21-100 -s 40 -i 5**  
    * **2 -s 40 -i 5**  
  Исключение:
    * **1-100 -s 50 -i 5**
    * **-44**  
    * **-60-70**  
  Фокусы (пересечение опций):
    * **1-100 -s 50 -q**
    * **1-20 -i 5**
    * **1-10 -iy 0**
    * **21-100 -iy 5**  
* Запустите программу:
  1. ВИНДА
      * Shift + ПКМ по текущей папке
      * Жмем "открыть окно PowerShell здесь" (может быть немного по другому). Вводим в консоль следующую строчку с изменением параметров на свои:
      * .\subtitleShaker.exe -i вашисубтитры.ass -o вывод.ass -sf settings.txt
      * вывод.ass - будет нужным нам файлом
      * PROFIT!!!
  1. LINUX
      * Пишем в командной строке:
      * ./subtitleShaker -i subtitle.ass -o output.ass -sf settings.txt
 
