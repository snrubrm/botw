#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/Resource/resHandle.h"

namespace sead {
class Heap;
}

namespace ksys::tera {
class System;
}

namespace ksys::phys {

class Unk_71025158e8;

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

    struct HandleInfo {
        res::Handle handle;
        sead::Vector2i coordinates{-1, -1};
    };
    KSYS_CHECK_SIZE_NX150(HandleInfo, 0x58);

    static RigidBodyDividedMeshShapeMgr* makeInstance(const Config& config, sead::Heap* heap);
    RigidBodyDividedMeshShapeMgr(const Config& config, sead::Heap* heap);
    virtual ~RigidBodyDividedMeshShapeMgr();
    void addToWorld();
    void sub_7100FC6F00(res::Handle* handle);
    void loadTeraMeshRigidBody(HandleInfo* info);

private:
    // Complete lifetime and the two-slot table establish the owner extent.
    /* 0x008 */ sead::FixedSafeString<256> mName;
    /* 0x120 */ sead::Buffer<HandleInfo> mHandles;
    /* 0x130 */ Unk_71025158e8* mBoundaryBodies[4]{};
    /* 0x150 */ sead::Vector3f _150 = sead::Vector3f::zero;
    // From Config::origin, Config::tile_size and size / tile_size.
    /* 0x15c */ sead::Vector2i mOrigin;
    /* 0x164 */ sead::Vector2i mTileSize;
    /* 0x16c */ sead::Vector2i mGridSize;
    /* 0x174 */ sead::Vector2i _174{-1, -1};
    /* 0x17c */ sead::Vector2i _17c{-1, -1};
    /* 0x184 */ sead::Vector2i _184{-1, -1};
    /* 0x18c */ bool _18c = false;
};
KSYS_CHECK_SIZE_NX150(RigidBodyDividedMeshShapeMgr, 0x190);

}  // namespace ksys::phys
