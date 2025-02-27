#ifndef ASSET_H
#define ASSET_H

#include <string>
#include <vector>
#include <unordered_map>

#include "Editor/UI/Elements.h"
#include "Editor/ImGui/imgui.h"

template <typename T>
class AssetContainer {
public:
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
		newAsset->debug.name = name;
		(*this)[id] = { newAsset };
		return id;
	}

	void Remove(size_t id) {
		auto it = this->find(id);
		if (it != this->end()) {
			delete it->second.asset;
			this->erase(it);
		}
	}
};

template <typename T>
class AssetHandler {
public:
	void DrawUI(const std::string& name, bool allowUnselect = true) {
		auto& assetMap = GetMap();

		std::string assetName = "";
		auto it = assetMap.find(m_id);
		if (it != assetMap.end()) {
			assetName = it->second.asset->debug.name;
		}

		uiInternal::DrawPropPrefix(name, "");

		if (ImGui::BeginCombo(("##" + name).c_str(), assetName.c_str())) {
			for (auto obj : assetMap) {
				if (ImGui::Selectable(obj.second.asset->debug.name.c_str(), obj.first == m_id)) {
					m_id = obj.first;
				}
			}
			ImGui::EndCombo();
		}

		if (allowUnselect) {
			if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
				m_id = 0;
			}
		}
	}

	void Add(const std::string& name, T* newAsset) {
		auto& map = GetMap();
		m_id = GenerateAssetID();
		newAsset->debug.name = name;
		map[m_id] = { newAsset };
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
			if (it.second.asset->debug.name == assetName) {
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