#include <TotkToolkit/TotkToolkit.h>

#include <iostream>
#if SWITCH
#include <switch.h>
#endif

int main()
{
#if SWITCH
	consoleInit(NULL);

	std::cout << "Hello world!" << std::endl;

	while (appletMainLoop()) {      // while the application hasn't received an exit request...
		consoleUpdate(NULL);        // Update the screen
	}

	consoleExit(NULL);

#endif

	std::cout << "Hello world!" << std::endl;

	return 0;
}
