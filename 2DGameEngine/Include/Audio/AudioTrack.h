#ifndef AUDIO_TRACK_H
#define AUDIO_TRACK_H

#include <string>

#include "Asset/Object.h"

struct Mix_Chunk;

class AudioTrack : public Object{
public:
	AudioTrack();
	AudioTrack(const std::string& filePath);
	virtual ~AudioTrack();

	virtual void Save(File* file) override;
	virtual void Load(File* file) override;

	// Volume ranges from 0 to 1, fadeIn is in seconds, loop = -1 is endless
	void Play(float volume = 1.f, float fadeIn = 0.f, int loop = 0);

	void LoadFromFile(const std::string& filePath);
private:
	unsigned char* m_source = nullptr;
	size_t m_sourceLength = 0;

	Mix_Chunk* m_chunk;
};

#endif // !AUDIO_TRACK_H
