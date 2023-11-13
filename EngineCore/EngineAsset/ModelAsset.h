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
	//			//���񿡼��� assimp�� dll�� �ε��ϱ� ������ ���������� �������. matir
	//			//������ ��������
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
	//	* asset�� animation�� ������ ���� �� ����.
	//	* ������ �������� ���� �ִϸ��̼ǿ� ���� ���� �ִϸ��̼� ���� ����.
	//	* �׷��� �׷� ��� ¥�⿡�� �ʹ� �����ɸ�. �׳� �ּº��� �ε��ϴ°ɷ�.
	//	* ���� ������ �ִϸ��̼��̶� �޽� ���δ� ����Ʈ�ϴ� ����. ������ ���������� �ε��Ҽ��־���ϴµ�
	//	* �׷� ��� �����ϱ⿡�� ü���̾ȵ�
	//	* aiMesh�� aiMaterial�� �״�� ����Ҽ��� ����. Mesh�� dx/opengl ���ҽ��� �����ؾ���
	//	* material ���� ��������. aiMesh�� �����ͷ� ������ �ְų� 
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
	//		//Mesh, Material, Texture�� ���� ��ü���� �ɷ� ���εǾ���Ѵ�.
	//		//frame�� ��� aiNode�� �ᵵ�Ǵµ� �׷��ԵǸ� �ִϸ��̼� �������� �Ź� �ش� ������ �ܾ�ͼ� ī�����־���ϹǷ�
	//		//frame�� ���� ����°� ����.
	//		std::shared_ptr<Node> rootNode_;
	//		std::string directory_;

	//		void processNode(aiNode* node, const aiScene* scene);
	//		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	//		//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene);
	//		//ID3D11ShaderResourceView* loadEmbeddedTexture(const aiTexture* embeddedTexture);
	//	};
	}
}

