#include "SubtitleShaker.h"



int main(int argc, char *argv[]){
    SubtitleShaker subtitleShaker;
    int state = 1;
    try{
        subtitleShaker.parseSettings(argc, argv);
        subtitleShaker.tryFindFiles();
        subtitleShaker.startProccesing();

        state = 0;
    }
    catch(int& e){
        if (e == 1){
            std::wcout<<L"Abort\n";
        }
        else{
            if (e == 0){
                state = 0;
            }
            else{
                std::wcout << L"Unexpected error\n";
            }
        }
    }
    catch(std::exception& e){
        std::wcout << L"Unexpected error\n";
    }

    #ifdef OS_WINDOWS
		system("pause");
	#endif
    return state;
}
