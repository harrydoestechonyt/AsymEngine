#include <3ds.h>
#include "engine.h"

int main(int argc, char **argv)
{
	Engine engine;
	engine.init();
	engine.run();
	engine.shutdown();
	return 0;
}
