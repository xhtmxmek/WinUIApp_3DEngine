/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2022, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

#pragma once

#include <assimp\Importer.hpp>
//#include <assimp\postprocess.h>

//#include "Mesh.h"
//#include "TextureLoader.h"

using namespace DirectX;

namespace Engine
{
	namespace EngineAsset
	{
	//	class Mesh;
	//	class Material;

	//	class Node
	//	{
	//	public:
	//		Node(const aiNode&& srcNode)
	//		{
	//			//나딕에서는 assimp를 dll로 로드하긴 했으나 엔진에서만 사용했음. matir
	//			//문제가 됬을것임
	//			//aiMatrix4x4
	//			mName = srcNode.mName.C_Str();
	//			//mTransformation = Matrix4x4f(srcNode.mTransformation.a1, );
	//		}
	//	private:
	//		string mName;

	//		/** The transformation relative to the node's parent. */
	//		Matrix4x4f mTransformation;

	//		/** Parent node. nullptr if this node is the root node. */
	//		Node* mParent;

	//		/** The number of child nodes of this node. */
	//		unsigned int mNumChildren;

	//		/** The child nodes of this node. nullptr if mNumChildren is 0. */
	//		Node** mChildren;

	//		/** The number of meshes of this node. */
	//		unsigned int mNumMeshes;

	//		/** The meshes of this node. Each entry is an index into the
	//		  * mesh list of the #aiScene.
	//		  */
	//		unsigned int* mMeshes;

	//		/** Metadata associated with this node or nullptr if there is no metadata.
	//		  *  Whether any metadata is generated depends on the source file format. See the
	//		  * @link importer_notes @endlink page for more information on every source file
	//		  * format. Importers that don't document any metadata don't write any.
	//		  */
	//		C_STRUCT aiMetadata* mMetaData;
	//	};

	//	/*
	//	* asset이 animation을 가지고 있을 수 있음.
	//	* 동일한 본구조를 가진 애니메이션에 대해 여러 애니메이션 매핑 가능.
	//	* 그러나 그런 기능 짜기에는 너무 오래걸림. 그냥 애셋별로 로드하는걸로.
	//	* 지금 구조는 애니메이션이랑 메쉬 전부다 임포트하는 구조. 원래는 선택적으로 로드할수있어야하는데
	//	* 그런 기능 구현하기에는 체력이안됨
	//	* aiMesh와 aiMaterial을 그대로 사용할수는 없음. Mesh는 dx/opengl 리소스를 포함해야함
	//	* material 역시 마찬가지. aiMesh를 포인터로 가지고 있거나 
	//	*/
	//	class ModelAsset
	//	{
	//	public:
	//		ModelAsset();
	//		~ModelAsset();

	//		bool Load(HWND hwnd, ID3D11Device* dev, ID3D11DeviceContext* devcon, std::string filename);
	//		//void Draw(ID3D11DeviceContext* devcon);

	//		void Close();
	//	private:
	//		//Mesh, Material, Texture는 엔진 자체적인 걸로 매핑되어야한다.
	//		//frame은 사실 aiNode를 써도되는데 그렇게되면 애니메이션 돌리고나서 매번 해당 정보를 긁어와서 카피해주어야하므로
	//		//frame도 새로 만드는게 맞음.
	//		std::shared_ptr<Node> rootNode_;
	//		std::string directory_;

	//		void processNode(aiNode* node, const aiScene* scene);
	//		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	//		//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene);
	//		//ID3D11ShaderResourceView* loadEmbeddedTexture(const aiTexture* embeddedTexture);
	//	};
	}
}

