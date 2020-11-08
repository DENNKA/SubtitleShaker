# SubtitleShaker
![](https://img.shields.io/github/v/release/DENNKA/SubtitleShaker)
![](https://img.shields.io/github/release-date/DENNKA/SubtitleShaker)
[![](https://tokei.rs/b1/github/DENNKA/SubtitleShaker/?category=code)](https://github.com/XAMPPRocky/tokei)

## ENGLISH; [НА РУССКОМ](README.ru.md);
<!---
full line:
[ENGLISH](README.md); [НА РУССКОМ](README.ru.md);
-->

---

# Work example (on site gif have lags but you can download)
![Work example](shaking_example.gif)

---
# Uses
* Original Makefile: https://github.com/mbcrawfo/GenericMakefile  
* Translator: https://mymemory.translated.net/
* Boost 1.66+
---

## [Documentation](docs/README.md)
## [Contributing](CONTRIBUTING.md)

# Description
subtitleShaker it's a program that make .ass subtitles shaking, add tags in multiple phrases, and translate (can translate from almost any language, but full compatibility only with translation into english, russian and ukrainian)

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
           -f  --from             from language
           -to --to               to language

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
    * **1-100 -m translate -f ru -to en**  
    [list of language codes](docs/Language_codes.md)

* Run program:  
 **This is old method, new in fast start section**
  1. WINDOWS
      * Shift + Right click in folder
      * Click "open PowerShell window here" or "open command window here" and type with replacement for your parameters:
      * .\SubtitleShaker.exe -i yoursubtitle.ass -o output.ass -sf settings.txt
      * Open output.ass
      * PROFIT!!!
  1. LINUX
      * In command line:
      * ./SubtitleShaker -i subtitle.ass -o output.ass -sf settings.txt
