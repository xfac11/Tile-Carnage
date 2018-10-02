#include "MenuState.h"
#include "GameHandler.h"
#include<crtdbg.h>
using namespace std;
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameHandler theGame;

	theGame.update();

	//system("pause");
	return 0;
}