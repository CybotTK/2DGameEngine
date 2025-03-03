#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

class File {
public:
	enum FileMode {
		READ, 
		WRITE
	};

	File(const std::string& fileName, FileMode mode);
	virtual ~File();

	std::string GetPath();

	virtual bool Read(void* buffer, size_t elementSize, size_t elements);
	virtual bool Write(void* buffer, size_t elementSize, size_t elements);

	template<typename T>
	bool Read(T* buffer, size_t elements = 1) {
		return Read((void*)buffer, sizeof(T), elements);
	}
	template<typename T>
	bool Write(T* buffer, size_t elements = 1) {
		return Write((void*)buffer, sizeof(T), elements);
	}

	template<typename T>
	bool Read(T& buffer, size_t elements = 1) {
		return Read((void*)&buffer, sizeof(T), elements);
	}
	template<typename T>
	bool Write(const T& buffer, size_t elements = 1) {
		return Write((void*)&buffer, sizeof(T), elements);
	}

	bool ReadStr(std::string& buffer);
	bool WriteStr(const std::string& buffer);

protected:
	std::string m_path;
	FileMode m_mode;

	FILE* m_file;
};

#endif // !FILE_H
