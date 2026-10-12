#pragma once
#include "CollisionTypes.h"

namespace Layers {
    const CollisionLayer PLAYER = 1 << 0;
    const CollisionLayer SOLID  = 1 << 1;
    const CollisionLayer ENEMY  = 1 << 2;
}
