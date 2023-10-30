#pragma once

#include <string>

namespace TotkToolkit::Configuration {
	class Settings {
	public:
		static std::string GetDumpDir();
		static void SetDumpDir(std::string romfsDir);

		static std::string GetBfresDir();
		static void SetBfresDir(std::string bfresDir);

		static std::string GetWriteDir();
		static void SetWriteDir(std::string writeDir);

	protected:
		static std::string sDumpDir;
		static std::string sBfresDir; // Unfortunately MeshCodec isn't fully reverse-engineered yet.
		static std::string sWriteDir;
	};
}