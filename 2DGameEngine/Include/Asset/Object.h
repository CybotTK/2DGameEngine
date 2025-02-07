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

	//Returns true if it's been drawn
	bool DrawIcon();

	struct _Debug {
		std::string name = "Object";
		std::string description = "...";
	} debug;
};

#endif // !OBJECT_H
