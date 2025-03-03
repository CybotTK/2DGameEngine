#pragma warning(disable:4996) // disables warning fopen

#include "System/File.h"

#include <stdexcept>
#include <assert.h>

File::File(const std::string& fileName,  FileMode mode) {
	m_mode = mode;
	m_path = fileName;

	m_file = fopen(fileName.c_str(),
		mode == FileMode::READ ? "rb" : "w+b"
	);

	assert(m_file != NULL);
}

File::~File() {
	fclose(m_file);
}

std::string File::GetPath() {
	return m_path;
}

bool File::Read(void* buffer, size_t elementSize, size_t elements) {
	return fread(buffer, elementSize, elements, m_file) == elements;
}

bool File::Write(void* buffer, size_t elementSize, size_t elements) {
	return fwrite(buffer, elementSize, elements, m_file) == elements;
}

bool File::ReadStr(std::string& buffer) {
	size_t size;

	auto out1 = Read(size);

	try {
		buffer.resize(size);
	}
	catch (std::bad_alloc e) {
		// It read something but it was trash.
		return false;
	}
	catch (std::length_error e) {
		return false;
	}

	auto out2 = Read(buffer[0], size);

	return out1 && out2;
}

bool File::WriteStr(const std::string& buffer) {
	auto out1 = Write(buffer.size());
	auto out2 = Write(&buffer[0], buffer.size());

	return out1 && out2;
}
