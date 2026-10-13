#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::tera {
class System;
}

namespace ksys::phys {

class RigidBodyDividedMeshShapeMgr {
public:
    // OpenWorldStage 7C4854 constructs this record; the full manager constructor
    // consumes its name, grid, translation, scale and terrain system.
    struct Config {
        /* 0x000 */ sead::FixedSafeString<256> name;
        /* 0x118 */ sead::Vector2i size;
        /* 0x120 */ sead::Vector2i origin;
        /* 0x128 */ sead::Vector2i tile_size;
        /* 0x130 */ sead::Vector2f translation;
        /* 0x138 */ f32 scale;
        /* 0x140 */ tera::System* terrain_system;
    };
    KSYS_CHECK_SIZE_NX150(Config, 0x148);

    static RigidBodyDividedMeshShapeMgr* makeInstance(const Config& config, sead::Heap* heap);
    RigidBodyDividedMeshShapeMgr(const Config& config, sead::Heap* heap);
    virtual ~RigidBodyDividedMeshShapeMgr();

private:
    // Complete lifetime and the two-slot table establish the owner extent.
    u8 _8[0x188];
};
KSYS_CHECK_SIZE_NX150(RigidBodyDividedMeshShapeMgr, 0x190);

}  // namespace ksys::phys
