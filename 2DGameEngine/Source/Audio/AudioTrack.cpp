#include "Audio/AudioTrack.h"

#include <unordered_map>

#include <SDL2/SDL_mixer.h>

#include "System/FileUtils.h"

AudioTrack::AudioTrack() {
}

AudioTrack::AudioTrack(const std::string& filePath) {
	LoadFromFile(filePath);
}

AudioTrack::~AudioTrack() {
	if (m_source) {
		delete[] m_source;
	}

	if (m_chunk) {
		Mix_FreeChunk(m_chunk);
	}
}

static std::unordered_map<int, bool> __finishedChannels;

void __ChannelDone(int channel) {
	__finishedChannels[channel] = true;
}

void AudioTrack::Play(float volume, float fadeIn, int loop) {
	int channel = -1;

	if (fadeIn <= 0.f) {
		channel = Mix_PlayChannel(-1, m_chunk, loop);
	}
	else {
		channel = Mix_FadeInChannel(-1, m_chunk, loop, int(fadeIn * 1000));
	}
}

void AudioTrack::LoadFromFile(const std::string& filePath) {
	m_source = file::DumpToMemory(filePath, m_sourceLength);

	if (m_chunk) {
		Mix_FreeChunk(m_chunk);
	}

	m_chunk = Mix_LoadWAV_RW(
		SDL_RWFromMem((void*)m_source, m_sourceLength),
		0
	);
}