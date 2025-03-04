#pragma warning(disable:4996) // Gets rid of fopen error (from MSVC)

#include "System/FileUtils.h"

#include <fstream>
#include <streambuf>

#include <iostream>

#include <SDL2/SDL.h>

std::string file::GetBasePath()
{
	//std::cout << SDL_GetBasePath();
	return SDL_GetBasePath();
}

std::string file::GetEditorPath(std::string localPath)
{
	return GetBasePath() + localPath;
}

unsigned char* file::DumpToMemory(const std::string& path, size_t& length)
{
	FILE* f = fopen(path.c_str(), "rb");

	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);

	unsigned char* source = new unsigned char[length];

	int bRead = (int)fread(source, sizeof(unsigned char), length, f);

	fclose(f);

	return source;
}

std::string file::Read(const std::string& file)
{
	std::ifstream t(file);
	std::string script = std::string(
		(std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>()
	);

	t.close(); //ensure it is closed as soon as reading is done

	return script;
}

void file::Write(const std::string& file, const std::string& text)
{
	std::ofstream t(file, std::ofstream::out);
	t << text;
	t.close();
}
