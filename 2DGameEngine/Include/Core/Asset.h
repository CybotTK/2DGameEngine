#ifndef ASSET_H
#define ASSET_H

#include <string>
#include <vector>
#include <unordered_map>

template <typename T>
class AssetContainer {
public:
	std::string name;
	T* asset;
};

size_t GenerateAssetID();

template <typename T>
class AssetMap : public std::unordered_map<size_t, AssetContainer<T>> {
public:

	void Reset() {
		for (auto it : *this) { 
			delete it.second.asset; 
		} 
		this->clear();
	}

	size_t Add(const std::string& name, T* newAsset) {
		size_t id = GenerateAssetID();
		(*this)[id] = { name, newAsset };
		return id;
	}
};

//#define AssetMap(T) AssetMapT<T>

template <typename T>
class AssetHandler {
public:
	//static size_t idGenerator;

	void Add(const std::string& name, T* newAsset) {
		auto& map = GetMap();
		m_id = GenerateAssetID();
		map[m_id] = { name, newAsset };
	}

	void Set(size_t id) {
		m_id = id;
	}

	void Set(T* asset) {
		AssetMap<T>& map = GetMap();
		for (auto it : map) {
			if (it.second.asset == asset) {
				m_id = it.first;
				return;
			}
		}
		m_id = 0;
	}
	void Set(const std::string& assetName) {
		AssetMap<T>& map = GetMap();
		for (auto it : map) {
			if (it.second.name == assetName) {
				m_id = it.first;
				return;
			}
		}
		m_id = 0;
	}

	T* Get() {
		auto& map = GetMap();
		auto it = map.find(m_id);
		if (it != map.end()){
			return it->second.asset;
		}
		return nullptr;
	}

	size_t GetID() const {
		return m_id;
	}

protected:
	AssetMap<T>& GetMap();

	size_t m_id = 0;

};

#endif // !ASSET_H