#pragma once

namespace MG
{
	class Platform
	{
	public:
		static void Initialize();

		// Returns the real path to the executable. Does not include the executable name.
		static std::filesystem::path GetExecutablePath();

		// Returns the CMake generator command for the current platform.
		static std::string GetGenerateCommand(const std::string& configuration);

		static std::string GetGoCommand(const std::string& appPath);
	};
}