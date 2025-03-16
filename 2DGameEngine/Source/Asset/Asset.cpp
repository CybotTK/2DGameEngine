#include "Asset/Asset.h"

#include "Engine.h"
#include "Graphics/Textures/ImageTexture.h"

#include <time.h> // time()

static size_t __idGenerator = 0; // 0 Means not initialized

size_t GenerateAssetID() {
	if (__idGenerator == 0) {
		// If I set the generator to 1, but it will mean that
		// the generator gets reseted every time you run the application.
		// That will lead to eventuual ID duplications when you start working
		// with an Editor. A very simple and efficient fix is to initialize
		// it with the system time.

		time_t seconds = time(NULL);
		// Multiplying it by 10k because there is still risk of 
		// duplication of the prev application created more IDs than
		// seconds passed between a new app open.
		__idGenerator = (size_t)seconds * 10000;
	}
	return __idGenerator++;
}

template<>
AssetMap<ImageTexture>& AssetHandler<ImageTexture>::GetMap() {
	return App::Get()->data.images;
}

template<>
AssetMap<Mesh>& AssetHandler<Mesh>::GetMap() {
	return App::Get()->data.meshes;
}

template<>
AssetMap<Scene>& AssetHandler<Scene>::GetMap() {
	return App::Get()->data.scenes;
}

template<>
AssetMap<AudioTrack>& AssetHandler<AudioTrack>::GetMap() {
	return App::Get()->data.audios;
}

template<>
AssetMap<PythonScript>& AssetHandler<PythonScript>::GetMap() {
	return App::Get()->data.scripts;
}