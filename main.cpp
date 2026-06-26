#include "Engine.h"
int main()
{
	Engine* engine = Engine::getEngine();
	engine->command("Start");
	return 0;
}