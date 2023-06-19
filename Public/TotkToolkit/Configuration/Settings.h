#pragma once

#include <string>

namespace TotkToolkit::Configuration {
	class Settings {
	public:
		static std::string GetDumpDir();
		static void SetDumpDir(std::string romfsDir);

		static std::string GetWriteDir();
		static void SetWriteDir(std::string writeDir);

	protected:
		static std::string sDumpDir;
		static std::string sWriteDir;
	};
}