#pragma once
#ifndef __ENGINE_INCLUDE_H__

#pragma warning(disable : 4251)

#pragma region Standard Headers
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <string>
#include <random>
#include <ctime>
#include <map>

using namespace std;
#pragma endregion

#pragma region dx9 headers
#include <d3d9.h>
#include <d3dx9.h>
#pragma endregion

#pragma region User Headers
#include "Engine_Define.h"
#include "Engine_Typedef.h"
#include "Engine_Enum.h"
#include "Engine_Struct.h"
#include "Engine_Function.h"
#include "../../Protocol.h"

// 사운드
#include <io.h>
#include "fmod.h"
#pragma comment (lib, "fmodex_vc.lib")

// 동영상
#include <Vfw.h>
#pragma comment (lib, "vfw32.lib")
#pragma endregion

#define __ENGINE_INCLUDE_H__
#endif