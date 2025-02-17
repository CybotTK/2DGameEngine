#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class File;
class Texture;

class Object {
public:
	Object();
	virtual ~Object();

	virtual void Save(File* file);
	virtual void Load(File* file);

	virtual void DrawUI();

	//Returns true if it's been drawn
	virtual bool DrawIcon(bool* isHovered=nullptr, Texture* thumbnail = nullptr);

	struct _Debug {
		std::string name = "Object";
		std::string description = "...";
		Texture* thumbnail = nullptr;
	} debug;
};

#endif // !OBJECT_H
