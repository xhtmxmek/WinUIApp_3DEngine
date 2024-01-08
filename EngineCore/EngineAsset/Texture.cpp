#include "pch.h"
#include "Renderer/Resource/DeviceResources.h"
#include "Texture.h"

namespace Engine
{
	namespace EngineAsset
	{
		bool Texture::Load(const wstring& textureName)
		{
			auto device = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();			
			/*
			리소스의 경로.
			1. 절대경로 지정으로 가능
			2. 상대경로 지정은 Assets 기준으로 됨.
			3. 패킹할떄는 Assets으로 복사 시키도록 해야할듯.
			*/						
			//path = L"Assets/Textures/cat.png";			
			wil::com_ptr_nothrow<ID3D11Resource> resource;
			HRESULT hr = DirectX::CreateWICTextureFromFile(device, textureName.c_str(),
				//CreateWICTextureFromFile(device, L"Assets/cat.png",
				resource.addressof(),
				shaderResourceView_.put());

			return SUCCEEDED(hr);
		}

		bool Texture::Load(const aiTexture* embeddedTexture)
		{
			HRESULT hr;
			ID3D11ShaderResourceView* texture = nullptr;

			if (embeddedTexture->mHeight != 0) {
				// Load an uncompressed ARGB8888 embedded texture
				D3D11_TEXTURE2D_DESC desc;
				desc.Width = embeddedTexture->mWidth;
				desc.Height = embeddedTexture->mHeight;
				desc.MipLevels = 1;
				desc.ArraySize = 1;
				desc.SampleDesc.Count = 1;
				desc.SampleDesc.Quality = 0;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
				desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				desc.CPUAccessFlags = 0;
				desc.MiscFlags = 0;

				D3D11_SUBRESOURCE_DATA subresourceData;
				subresourceData.pSysMem = embeddedTexture->pcData;
				subresourceData.SysMemPitch = embeddedTexture->mWidth * 4;
				subresourceData.SysMemSlicePitch = embeddedTexture->mWidth * embeddedTexture->mHeight * 4;

				ID3D11Texture2D* texture2D = nullptr;
				hr = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice()->CreateTexture2D(&desc, &subresourceData, &texture2D_);
				//if (FAILED(hr))
				//	MessageBox(hwnd_, "CreateTexture2D failed!", "Error!", MB_ICONERROR | MB_OK);

				hr = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice()->CreateShaderResourceView(texture2D, nullptr, &texture);
				//if (FAILED(hr))
				//	MessageBox(hwnd_, "CreateShaderResourceView failed!", "Error!", MB_ICONERROR | MB_OK);
			}

			return texture;
		}
		std::optional<weak_ptr<Texture>> TextureManager::LoadTexture(const wstring& textureName, const aiScene* scene)
		{
			wstring applicationPath = Path::EngineDir;
			wstring path = applicationPath + L"\\Assets\\" + textureName;

			auto loadedTexture = LoadTexture(textureName);
			if (loadedTexture == nullopt)
			{
				auto importedTexture = scene->GetEmbeddedTexture(Utility::WstrToStr(textureName).c_str());
				if (importedTexture)
				{
					auto newTexture = make_shared<Texture>();
					newTexture->Load(path);
					loadedTexture = newTexture;
				}
				else
				{
					loadedTexture = nullopt;
				}
			}

			return loadedTexture;
		}

		std::optional<weak_ptr<Texture>> TextureManager::LoadTexture(const wstring& textureName)
		{
			wstring applicationPath = Path::EngineDir;
			wstring path = applicationPath + L"\\Assets\\" + textureName;

			auto textureLoadPass = [this](shared_ptr<Texture> texture, const wstring& texturePath)->std::optional<weak_ptr<Texture>>
				{
					if (texture->Load(texturePath))
					{
						Textures[texturePath.c_str()] = texture;
						return texture;
					}
					return nullopt;
				};

			std::optional<weak_ptr<Texture>> loadedTexture;
			auto iter = Textures.find(path.c_str());
			if (iter != Textures.end())
			{
				loadedTexture = iter->second;
			}
			else
			{
				auto newTexture = make_shared<Texture>();
				loadedTexture = textureLoadPass(newTexture, path);
			}

			return loadedTexture;
		}

	}
}