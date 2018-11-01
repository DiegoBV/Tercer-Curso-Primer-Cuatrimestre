#ifndef __CORE_HPP__
#define __CORE_HPP__

#include "../common/Common/Print.h"
#include "../common/Common/PVD.h"
#include "../common/Utils/Utils.h"
#include "json.hpp"

#include "Render/Render.h"
#include "Render/Camera.h"

#include <vector>
#include <fstream>
#include <iostream>

using namespace Snippets;
using json = nlohmann::json;

typedef physx::PxVec3 Vector3;
typedef physx::PxVec4 Vector4;


#endif