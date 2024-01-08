#include "pch.h"
#include "Texture.h"
#include "Material.h"
#include "Renderer/Resource/DeviceResources.h"

namespace Engine
{
	namespace EngineAsset
	{
		Material::Material()
		{			
			textures_.reserve(TextureKey::Texture_Max);
			textures_.resize(TextureKey::Texture_Max);
		}

		std::weak_ptr<Material> MaterialManager::CreateMaterial(const std::string& name)
		{
			auto iter = Materials.find(name.c_str());
			if (iter != Materials.end())
			{
				return iter->second;
			}
			
			return std::weak_ptr<Material>(make_shared<Material>());
		}
		std::optional<std::weak_ptr<Material>> MaterialManager::GetMaterial(const std::string& name)
		{
			auto iter = Materials.find(name.c_str());
			if(iter != Materials.end())
			{
				return iter->second;
			}
			return nullopt;
		}
	}
}
