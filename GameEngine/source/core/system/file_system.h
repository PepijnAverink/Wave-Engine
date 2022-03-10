#pragma once
#include <string>
#include <stdint.h>

class FileSystem
{
public:
	// Filesystem
	static bool MountFilesystem(const std::string& _contentpath);
	static bool	UnmountFileSystem(const std::string& _contentpath);

	static bool				OpenFile(std::string& _filepath);

	// Text files
	static std::string		ReadTextFile(const std::string& _filepath);
	static bool				WriteTextFile(const std::string& _filepath, const std::string& _text);

	// Binary files
	static bool				ReadFile(const std::string& _filepath, void** _data, size_t& _size);
	static bool				WriteFile(const std::string& _filepath, void* _data, size_t  _size);

	static std::string OpenFileDialog();
	static std::string SaveFileDialog();

	// General file operations
	static uint64_t			GetCreateionHash(const std::string& _filepath);
	static uint64_t			GetModificationHash(const std::string& _filepath);

	static bool				FileExists(const std::string& _filepath);
	static uint32_t			FileSize(const std::string& _filepath);

	static bool				MakeFile(const std::string& _filepath);
	static bool				RemoveFile(const std::string& _filepath);

	static bool HasFileChanged(const std::string& _filepath, uint64_t _hash)
	{
		uint64_t hash = GetModificationHash(_filepath);
		return (hash != _hash) && (hash != 0);
	}
};