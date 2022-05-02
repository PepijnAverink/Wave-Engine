#pragma once
#include <string>
#include <sstream>

inline std::string  WStringToString(std::wstring _str) { return std::string(_str.begin(), _str.end()); }
inline std::wstring StringToWString(std::string _str) { return std::wstring(_str.begin(), _str.end()); }

template<typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}


inline void CopyString(const std::string& _string, char** _buffer)
{
	*_buffer = new char[_string.length()+1];
	strcpy(*_buffer, _string.c_str());
}

inline std::string GetFileExtension(const std::string& _str)
{
	std::string result = _str.substr(_str.find_last_of(".") + 1);
	return result;
}

inline std::string ReplaceFileExtension(const std::string& _filepath, const std::string& _ext)
{
	std::string result = _filepath.substr(0, _filepath.find_last_of('.')) + _ext;
	return result;
}

inline std::string GetNameFromFilepath(const std::string& _filepath)
{
	std::string result = _filepath;

	const size_t last_slash_idx = result.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		result.erase(0, last_slash_idx + 1);
	}

	// Remove extension if present.
	const size_t period_idx = result.rfind('.');
	if (std::string::npos != period_idx)
	{
		result.erase(period_idx);
	}

	return result;
}

inline std::string GetDirectoryFromFilepath(const std::string& _filepath)
{
	std::string result = _filepath;
	const size_t last_slash_idx = result.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		result = result.substr(0, last_slash_idx);
	}

	return result;
}