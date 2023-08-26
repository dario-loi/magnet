#include "CmakeEmitter.h"

#include "Core.h"

namespace MG
{
	CmakeEmitter::CmakeEmitter(const std::filesystem::path& path)
	{
		m_Stream.open(path);
	}

	void CmakeEmitter::Add_Header()
	{
		m_Stream << "# Generated by Magnet v" << MG_VERSION;
		Add_Newline(1);
		m_Stream
				<< "# Do not edit this file since any changes will be overwritten next time the project files are regenerated.";
		Add_Newline(2);
	}

	void CmakeEmitter::Add_Literal(const std::string& literal)
	{
		m_Stream << literal;
	}

	void CmakeEmitter::Add_Indentation(int amount)
	{
		for (int i = 0; i < amount; i++)
		{
			m_Stream << "\t";
		}
	}

	void CmakeEmitter::Add_Newline(int amount)
	{
		for (int i = 0; i < amount; i++)
		{
			m_Stream << End();
		}
	}

	void CmakeEmitter::Add_Comment(const std::string& comment)
	{
		m_Stream << "# " << comment << End();
	}

	void CmakeEmitter::Add_If(const std::string& condition, const std::function<void()>& lambda)
	{
		m_Stream << "if(" << condition << ")" << End();

		lambda();

		m_Stream << "endif()" << End();
	}

	void CmakeEmitter::Add_IfElse(const std::string& condition, const std::function<void()>& ifTrue,
	                              const std::function<void()>& ifFalse)
	{
		m_Stream << "if(" << condition << ")" << End();

		ifTrue();

		m_Stream << "else()" << End();

		ifFalse();

		m_Stream << "endif()" << End();
	}

	void CmakeEmitter::Add_CmakeMinimumRequired(const std::string& version)
	{
		m_Stream << "cmake_minimum_required(VERSION " << version << ")" << End();
	}

	void CmakeEmitter::Add_Project(const std::string& target)
	{
		m_Stream << "project(" << target << ")" << End();
	}

	void CmakeEmitter::Add_SetCmakeCxxStandard(int value)
	{
		m_Stream << "set(CMAKE_CXX_STANDARD " << value << ")" << End();
	}

	void CmakeEmitter::Add_SetCmakeArchiveOutputDirectory(const std::string& value)
	{
		m_Stream << "set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY " << value << ")" << End();
	}

	void CmakeEmitter::Add_SetCmakeLibraryOutputDirectory(const std::string& value)
	{
		m_Stream << "set(CMAKE_LIBRARY_OUTPUT_DIRECTORY " << value << ")" << End();
	}

	void CmakeEmitter::Add_SetCmakeRuntimeOutputDirectory(const std::string& value)
	{
		m_Stream << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY " << value << ")" << End();
	}

	void CmakeEmitter::Add_SetTargetProperties(const std::string& target, const std::string& property,
	                                           const std::string& value)
	{
		m_Stream << "set_target_properties(" << target << " PROPERTIES " << property << " " << value << ")"
		         << End();
	}

	void CmakeEmitter::Add_AddSubdirectory(const std::string& source)
	{
		m_Stream << "add_subdirectory(" << source << ")" << End();
	}

	void CmakeEmitter::Add_AddSubdirectory(const std::vector<std::string>& sources)
	{
		for (const auto& source : sources)
		{
			Add_AddSubdirectory(source);
		}
	}

	void CmakeEmitter::Add_TargetIncludeDirectories(const std::string& target, const std::string& mode,
	                                                const std::string& directory)
	{
		m_Stream << "target_include_directories(" << target << " " << mode << " " << directory << ")"
		         << End();
	}

	void CmakeEmitter::Begin_TargetIncludeDirectories(const std::string& target, const std::string& mode)
	{
		m_Stream << "target_include_directories(" << target << " " << mode << End();
	}

	void CmakeEmitter::End_TargetIncludeDirectories()
	{
		m_Stream << ")" << End();
	}

	void CmakeEmitter::Add_TargetLinkLibraries(const std::string& target,
	                                           const std::vector<std::string>& libraries)
	{
		m_Stream << "target_link_libraries(" << target;

		for (const auto& library : libraries)
		{
			m_Stream << " " << library;
		}

		m_Stream << ")" << End();
	}

	void CmakeEmitter::Add_AddExecutable(const std::string& target, const std::vector<std::string>& sources)
	{
		m_Stream << "add_executable(" << target;

		for (const auto& source : sources)
		{
			m_Stream << " " << source;
		}

		m_Stream << ")" << End();
	}

	void CmakeEmitter::Add_AddLibrary(const std::string& target, const std::string& type,
	                                  const std::vector<std::string>& sources)
	{
		m_Stream << "add_library(" << target << " " << type;

		for (const auto& source : sources)
		{
			m_Stream << " " << source;
		}

		m_Stream << ")" << End();
	}

	char CmakeEmitter::End()
	{
		return '\n';
	}
}