#include "SubtitleShaker.h"



int main(int argc, char *argv[]){
    SubtitleShaker subtitleShaker(argc, argv);
    auto state = subtitleShaker.start();
    #ifdef OS_WINDOWS
		system("pause");
	#endif
    return state;
}
