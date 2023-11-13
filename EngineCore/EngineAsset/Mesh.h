#pragma once

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

namespace Engine
{
    namespace EngineAsset
    {
        struct VERTEX {
            FLOAT X, Y, Z;
            Vector2f coord;
        };

        struct Texture {
            std::string type;
            std::string path;
            ID3D11ShaderResourceView* texture;

            void Release() {
                SafeRelease(texture);
            }
        };

        class Mesh {
        public:
            std::vector<VERTEX> vertices_;
            std::vector<UINT> indices_;
            std::vector<Texture> textures_;
            ID3D11Device* dev_;

            Mesh(ID3D11Device* dev, const std::vector<VERTEX>& vertices, const std::vector<UINT>& indices, const std::vector<Texture>& textures) :
                vertices_(vertices),
                indices_(indices),
                textures_(textures),
                dev_(dev),
                VertexBuffer_(nullptr),
                IndexBuffer_(nullptr) {
                this->setupMesh(this->dev_);
            }
    }
}