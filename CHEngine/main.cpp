#include "Engine.h"

int main()
{
	Engine engine = Engine();

	if (!engine.init()) { return -1; }
	if (!engine.bufferModel()) { return -1; }

	engine.gameLoop();

	return 0;
}