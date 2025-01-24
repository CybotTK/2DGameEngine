#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class File;

class Object {
public:
	Object();
	virtual ~Object();

	virtual void Save(File* file);
	virtual void Load(File* file);

	virtual void DrawUI();
	virtual void DrawIcon();

	struct _Debug {
		std::string name;
		std::string description;
	} debug;
};

#endif // !OBJECT_H
