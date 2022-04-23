#include "core/stdafx.h"


// No system mounting nessecary on windows
bool  FileSystem::MountFilesystem(const std::string& _contentpath) { return true; }
bool FileSystem::UnmountFileSystem(const std::string& _contentpath) { return true; }

bool FileSystem::OpenFile(std::string& _filepath)
{
	char szFile[100];

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetActiveWindow();
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

	GetOpenFileName(&ofn);

	_filepath = std::string(szFile);
	return true;
}

std::string FileSystem::ReadTextFile(const std::string& _filepath)
{
	std::string result = "";
	std::string line;

	std::ifstream file(_filepath);
	if (file.is_open())
	{
		while (std::getline(file, line))
			result += line + "\n";

		file.close();
		file.clear();
		return result;
	}

	printf("[ERROR] Unable to open file: %s\n", _filepath.c_str());
	return "";
}

bool FileSystem::WriteTextFile(const std::string& _filepath, const std::string& _text)
{
	std::ofstream file(_filepath);
	if (file.is_open())
	{
		file << _text.c_str();
		file.close();
		return true;
	}

	printf("[ERROR] Unable to open file: %s\n", _filepath.c_str());
	return false;
}

bool FileSystem::ReadFile(const std::string& _filepath, void** _data, size_t& _size)
{
	_size = FileSize(_filepath);
	char* buffer = new char[_size];

	std::ifstream rf(_filepath.c_str(), std::ios::out | std::ios::binary);
	rf.read(buffer, _size);

	*_data = buffer;
	return true;
}

bool FileSystem::WriteFile(const std::string& _filepath, void* _data, size_t _size)
{
	std::ofstream file;
	file.open(_filepath.c_str(), std::ios::out | std::ios::binary);

	file.write((char*)_data, _size);

	file.close();
	return true;
}

uint64_t FileSystem::GetCreateionHash(const std::string& _filepath)
{
	HANDLE hr = CreateFile(_filepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hr != INVALID_HANDLE_VALUE)
	{
		FILETIME ftCreate;
		GetFileTime(hr, &ftCreate, NULL, NULL);
		CloseHandle(hr);
		return SimpleHashULong(ftCreate.dwHighDateTime, ftCreate.dwLowDateTime);
	}

	printf("[ERROR] Couldnt get CreationHash from: %s\n", _filepath.c_str());
	return 0;
}

uint64_t FileSystem::GetModificationHash(const std::string& _filepath)
{
	HANDLE hr = CreateFile(_filepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hr != INVALID_HANDLE_VALUE)
	{
		FILETIME ftChange;
		GetFileTime(hr, NULL, NULL, &ftChange);
		CloseHandle(hr);
		return SimpleHashULong(ftChange.dwHighDateTime, ftChange.dwLowDateTime);
	}

	//	printf("[ERROR] Couldnt get modificationHash from: %s\n", _filepath.c_str());
	return 0;
}

bool FileSystem::FileExists(const std::string& _filepath)
{
	std::ifstream file(_filepath.c_str());
	file.failbit;
	return file.good();
}

uint32_t FileSystem::FileSize(const std::string& _filepath)
{
	std::ifstream file(_filepath.c_str(), std::ios::in);
	file.seekg(0, std::ios::end);

	return (unsigned int)file.tellg();
}

bool FileSystem::MakeFile(const std::string& _filepath)
{
	return CreateFile(_filepath.c_str(), GENERIC_ALL, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
}

bool FileSystem::RemoveFile(const std::string& _filepath)
{
	return DeleteFile(_filepath.c_str());
}