#include "Program.h"

int main(int argc, int argv)

{
	sf::err().rdbuf(NULL);
	Program p(800, 800);
	return p.mainLoop();
}