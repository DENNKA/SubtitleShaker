# SubtitleShaker
[![](https://tokei.rs/b1/github/DENNKA/SubtitleShaker/?category=code)](https://github.com/XAMPPRocky/tokei)
  
---

# Work example (subtitles in the video below) / Пример работы (субтитры снизу видео)
![Work example](example.gif)

## [НА РУССКОМ](https://github.com/DENNKA/subtitleShaker/tree/master#на-русском-1)  
## [ENGLISH](https://github.com/DENNKA/subtitleShaker/tree/master#english-1)

---
# Uses
* Original Makefile: https://github.com/mbcrawfo/GenericMakefile  
* Translator: https://mymemory.translated.net/
* Boost 1.66+
---

# НА РУССКОМ
Программа позволяет трясти .ass субтитры, добавлять теги во множество фраз, переводить (но пока плохо и только на русский)

## Как работает
Создает множество фраз с тегом \move что создает ощущение тряски  
**ВАЖНО:** из-за разделения на фразы ломаются теги связаные со временем (например: \k(все теги караоке), \move, \t, \fad, \fade)

## Быстрый старт
 * Скачиваем для своей платформы --> https://github.com/DENNKA/subtitleShaker/releases/latest
 * Распаковываем в папку с субтитрами (лучше чтобы других файлов не было)
 * Дальше нужно настроить: создаем файл setting.txt (в нашей папке), в него пишем 1 -s 50 -i 5 это заставит первый субтитр трястись, -s 50 это скорость тряски чем ниже тем быстрее, но не ниже 10. -i 5 это интенсивность в пикселях чем больше тем более размашистая тряска, если нужно несколько строк то вместо 1 указываем диапозон, например 10-20, если нужно обработать еще диалогов просто переходим на следующую строчку
 * Сохраняем и запускаем SubtitleShaker.exe
 * Возможно он спросит какой именно файл нужно обработать просто пишем цифру в консоль
 * Если все прошло успешно появится файл начинающийся на MOD_
 * Файл готов
 * Если не работает пишите [СЮДА](https://github.com/DENNKA/SubtitleShaker/issues/new) или [СЮДА под любое видео](https://www.youtube.com/channel/UCm9PVOWO_FVnEhh3tYxQ2fw) **обязательно** прикладывайте свои файлы

## Опции  
```
==============================================================
SubtitleShaker [опции]
  -h          --help   Помощь
  -i         --input   Исходный файл
  -o        --output   Файл для вывода
 -sf --settings_file   Файл настроек
  -v       --verbose   Более подробный вывод
  -s          --seed   Семя для генерации случайных чисел
==============================================================
Опции обработки строк:
  -s         --shake   Трясти каждые n миллисекунд
  -i     --intensity   Интенсивность в пикселях
 -ix   --intensity_x   Интенсивность в пикселях по x
 -iy   --intensity_y   Интенсивность в пикселях по y
  -m          --mode   Выбор режима
   Режимы:
        add_str          Добавить строку в начало или конец фразы
           -b  --begin            В начало
           -e  --end              В конец

        translate        Перевод диалогов
           -f  --from             С языка
           -t0 --to               На язык РАБОТАЕТ ТОЛЬКО ru

  -q         --quiet   Удален
==============================================================
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
  Обработка первой фразы (тряска каждые 50 миллисекунд, в 5 пикселей)  
    * **1 -s 50 -i 5**  
  Диапозон:  
  Обработка диапозона фраз (с первой по десятую включительно)  
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
  Добавление тегов (**в тегах пробелов быть не должно!**):
    * **1-100 -m add_str -b {\fad(100,100)}**  
  Добавление в конец:
    * **1-100 -m add_str -e addInEnd**  
  Перевод:
    * **1-100 -m translate -f en --too ru**  
  **Перевод работает только на русский язык**
* Запустите программу:
  1. ВИНДА
      * Shift + ПКМ по пустому месту в текущей папке
      * Жмем "открыть окно PowerShell здесь" (может быть немного по другому). Вводим в консоль следующую строчку с изменением параметров на свои:
      * .\SubtitleShaker.exe -i вашисубтитры.ass -o вывод.ass -sf settings.txt
      * вывод.ass - будет нужным нам файлом
      * PROFIT!!!
  1. ПИНГВИН
      * Пишем в командной строке:
      * ./SubtitleShaker -i subtitle.ass -o output.ass -sf settings.txt
 
# ENGLISH
subtitleShaker it's a program that make .ass subtitles shaking, add tags in multiple phrases~~, and translate~~ (only on russian)

## How does it work
Program add many phrases with tag \move that makes subtitles shaking.  
**IMPORTANT:** due to division into phrases, programm break time-related tags (for example: \k(all karaoke tags), \move, \t, \fad, \fade)

## Fast start
 * Download for your OC --> https://github.com/DENNKA/subtitleShaker/releases/latest
 * Unzip in folder with subtitles (better if there no other files)
 * And setup: create file setting.txt (in your folder), write in file 1 -s 50 -i 5 it's make first subtitle shaking, -s 50 it is speed of shaking, lower value the faster but not lower 10. -i 5 it's intensity in pixel bigger value the more sweeping the shaking, if you need several lines instead of 1 write range, for example 10-20, if you need to process more dialogs just go to the next line
 * Save and execute SubtitleShaker.exe
 * It may ask you which file you need to process just write a number to the console
 * If everything is successful appears file starting with MOD_
 * The file is ready
 * If doesn't work write issue [here](https://github.com/DENNKA/SubtitleShaker/issues/new) or [here in comments to any video](https://www.youtube.com/channel/UCm9PVOWO_FVnEhh3tYxQ2fw) **be sure** to attach your files

## Options
```
==============================================================
SubtitleShaker [options]
  -h          --help   Help
  -i         --input   Input file
  -o        --output   Output file
 -sf --settings_file   Settings file
  -v       --verbose   More verbose output
  -s          --seed   Seed for random
==============================================================
Strings process options:
  -s         --shake   Shake every n ms
  -i     --intensity   Intensity in pixels
 -ix   --intensity_x   Intensity in pixels at x
 -iy   --intensity_y   Intensity in pixels at y
  -t          --time   Time between two phrases (need to division)
  -m          --mode   Select mode
   Modes:
        add_str          Add string in begin or end phrase
           -b  --begin            Add in begin
           -e  --end              Add in end

        translate        Translate dialogues
           -f  --from             Source language
           -t0 --to               End language WORK ONLY ru

  -q         --quiet   Deleted
==============================================================
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
  Processing the first phrase (shaking every 50 milliseconds, at 5 pixels)  
    * **1 -s 50 -i 5**  
  Range:  
  Processing range of phrases (first to tenth inclusive)  
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
    Add tags (**No spaces in tags!**):
    * **1-100 -m add_str -b {\fad(100,100)}**  
    Add in end:
    * **1-100 -m add_str -e addInEnd**  
    Translate:
    * **1-100 -m translate -f en --too ru**  
    **Translate work only to russian language!!!**
* Run program:
  1. WINDOWS
      * Shift + Right click in folder
      * Click "open PowerShell window here" or "open command window here" and type with replacement for your parameters:
      * .\SubtitleShaker.exe -i yoursubtitle.ass -o output.ass -sf settings.txt
      * Open output.ass
      * PROFIT!!!
  1. LINUX
      * In command line:
      * ./SubtitleShaker -i subtitle.ass -o output.ass -sf settings.txt
