# For programmers

## [Contents](README.md)

## ENGLISH; [НА РУССКОМ](For_programmers.ru.md);
<!---
full line:
[ENGLISH](For_programmers.md); [НА РУССКОМ](For_programmers.ru.md);
-->

---

Version at the time of writing 2.2.0  
## Standart
### Usage arguments
* The latter argument overwrites the past arguments
* First argument -i it's always input file (--input_file) and ALL next arguments always are intensity (--intensity)  
* Argument -m (--mode) made push_back in current settingsToProcess
* ALL not standart argument also insert in end (standart it's -i, -t, -ix, -iy and etc; not standart it's all others, they used for modes), all not standart arguments process in parseArg(),
* Not standart arguments process in SubtitleShaker::startProccesing()
* Short arguments must start with letter (-i, -t, -i000)
* Short arguments mustn't start with deigt ~~(-0i, -123o)~~, because programm think that it exclusion (-5, -1-20)
