#pragma once

namespace Engine
{
	namespace Asset
	{
		class Texture;

		enum TextureKey
		{
			DiffuseMap = 0,
			NormalMap,
			EmissiveMap,
			SpecularMap,
			BaseColorMap,
			MetalicMap,
			RoughnessMap,
			Texture_Max,

		};


		class Material
		{
		private:
			vector<weak_ptr<Texture>> textures_;
			Color4f baseColor_;
			Color4f diffuseColor_;
			Color4f specularColor_;
			Color4f ambientColor_;
			Color4f emissiveColor_;
			bool blendable;
			float opacity_;
			float specularFactor_;
			float glossinessFactor_;
			float shinessFactor_;

		public:
			Material();

			void SetTexture(TextureKey key, const std::weak_ptr<Texture>& textures)
			{
				int textureKey = static_cast<int>(key);
				textures_[textureKey] = textures;
			}

			std::optional<std::weak_ptr<Texture>> GetTexture(TextureKey key)
			{
				if ((int)key >= textures_.size() ||
					textures_[key].expired() == true)
					return nullopt;

				return textures_[key];
			}

#pragma region properties
			void SetOpacity(float value)
			{
				opacity_ = value;
			}
			float GetOpacity()
			{
				return opacity_;
			}

			void SetBlendable(bool blend)
			{
				blendable = blend;
			}

			bool GetBlendable()
			{
				return blendable;
			}

			void SetSpecularFactor(float value)
			{
				specularFactor_ = value;
			}

			float GetSpecularFactor()
			{
				return specularFactor_;
			}

			void SetGlossinessFactor(float value)
			{
				glossinessFactor_ = value;
			}

			float GetGlossinessFactor()
			{
				return glossinessFactor_;
			}

			void SetShinessFactor(float value)
			{
				shinessFactor_= value;
			}

			float GetShinessFactor()
			{
				return shinessFactor_;
			}

			void SetBaseColor(const Color4f& value)
			{
				baseColor_ = value;
			}

			Color4f& GetBaseColor()
			{
				return baseColor_;
			}

			void SetDiffuseColor(const Color4f& value)
			{
				diffuseColor_ = value;
			}

			Color4f& GetDiffuseColor()
			{
				return diffuseColor_;
			}

			void SetSpecularColor(const Color4f& value)
			{
				specularColor_ = value;
			}

			Color4f& GetSpecularColor()
			{
				return specularColor_;
			}

			void SetAmbientColor(const Color4f& value)
			{
				ambientColor_ = value;
			}

			Color4f& GetAmbientColor()
			{
				return ambientColor_;
			}

			void SetEmissiveColor(const Color4f& value)
			{
				emissiveColor_ = value;
			}

			Color4f& GetEmissiveColor()
			{
				return emissiveColor_;
			}
#pragma endregion
		};

		class MaterialManager
		{
		public:
			static MaterialManager& GetInstance()
			{
				static MaterialManager materialManager;
				return materialManager;
			}
			std::weak_ptr<Material> CreateMaterial(const std::string& name);
			std::optional<std::weak_ptr<Material>> GetMaterial(const std::string& name);
		private:
			MaterialManager()
			{
			}
			std::map<const char*, std::shared_ptr<Material>> Materials;			
		};
	}
}