#include "global_includes.h"
#include "objMeshBuilder.h"
#include "window.h"
#include "shader.h"


int main(int argc, char** argv) {
	setenv("MESA_DEBUG","",0);
	try {
		Window window(800, 600);
		window.run();
	} catch (std::string& error) {
		std::cerr << error << std::endl;
	}
	return 0;
}
