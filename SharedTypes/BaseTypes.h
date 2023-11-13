#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <exception>
#include <future>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <concrt.h>
#include <wincodec.h>

#include <string>
#include <memory>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include <assimp/types.h>

typedef aiVector2t<float> Vector2f;
typedef aiVector2t<int> Vector2i;
typedef aiVector3t<float> Vector3f;
typedef aiColor4t<float> Vector4f;
typedef aiColor4t<float> Color4f;
typedef aiColor4t<int> Vector4i;
typedef aiMatrix4x4t<float> Matrix4x4f;
typedef aiQuaterniont<float> Quaternionf;


#include "Math/EngineMath.h"
#include "CommonTypes.h"
#include "UIInfoParams.h"
#include "CommonDefine.h"

using namespace SharedTypes;
using namespace std;