#include <TotkToolkit/TotkToolkit.h>


#include <iostream>
#ifdef SWITCH
#include <switch.h>
#else
#include <iostream>
#endif

int main()
{
#ifdef SWITCH
	consoleInit(NULL);

	printf("test");
	//std::cout << "Hello world!" << std::endl;

	while (appletMainLoop()) {      // while the application hasn't received an exit request...
		consoleUpdate(NULL);        // Update the screen
	}

	consoleExit(NULL);

#endif

	//std::cout << "Hello world!" << std::endl;

	return 0;
}
