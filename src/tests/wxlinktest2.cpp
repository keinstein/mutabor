#include "src/kernel/Defs.h"
#include <iostream>
#include "src/wxGUI/TestInitializer.h"

// Skip the GUI related checks from DebugRoute.cpp
#if 1
#define no_wxGUI 1
#include "src/wxGUI/Routing/DebugRoute.cpp"
#undef no_wxGUI
#endif

int main() {
#ifdef _GLIBCXX_DEBUG
	std::clog << "In case of segmentation faults assure that wxWidgets is compiled using -D_GLIBCXX_DEBUG" << std::endl;
#endif

	mutwxInitializer initializer;

	std::cout << "wxlinktest running" << std::endl;
}
