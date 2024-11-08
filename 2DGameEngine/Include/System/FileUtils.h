#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

namespace file {
	std::string GetBasePath();
	std::string GetEditorPath(std::string localPath); //Absolute path from the editor location

	unsigned char* DumpToMemory(const std::string& path, size_t& length);

	std::string Read(const std::string& file);
	void Write(const std::string& file, const std::string& text);
}

#endif // FILE_UTILS_H