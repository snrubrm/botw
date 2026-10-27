#pragma once

#include <basis/seadTypes.h>
#include <cstddef>
#include <environment/aglEnvCubeMapMgr.h>

namespace sead {
class Heap;
}

namespace gsys {

class ShaderContext;

// The cube-map drawer owned by ModelSceneGI at +0x420 (0x1068 bytes; constructor
// 0x7100c7d198, initialize 0x7100c7d330). Only the members the ModelSceneGI getters
// and setter read are modelled.
class ModelCubeMapDrawer {
private:
    u8 _0[0x348];

public:
    ShaderContext* mShaderContext;  // 348

private:
    u8 _350[0x430 - 0x350];
    s32 _430;
    u8 _434[0x458 - 0x434];

public:
    agl::env::CubeMapMgr mCubeMapMgr;  // 458

private:
    u8 _afterCubeMapMgr[0xec0 - 0x458 - sizeof(agl::env::CubeMapMgr)];

public:
    void* mCubeMap;  // ec0
};
static_assert(offsetof(ModelCubeMapDrawer, mShaderContext) == 0x348);
static_assert(offsetof(ModelCubeMapDrawer, mCubeMapMgr) == 0x458);
static_assert(offsetof(ModelCubeMapDrawer, mCubeMap) == 0xec0);

}  // namespace gsys
