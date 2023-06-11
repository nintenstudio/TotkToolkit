#pragma once

#include <string>

namespace TotkToolkit::Configuration {
	class Settings {
	public:
		static std::string GetRomfsDir();
		static void SetRomfsDir(std::string romfsDir);

	protected:
		static std::string sRomfsDir;
	};
}