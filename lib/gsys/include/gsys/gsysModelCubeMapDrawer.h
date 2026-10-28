#pragma once

#include <basis/seadTypes.h>
#include <cstddef>
#include <gfx/seadColor.h>
#include <environment/aglEnvCubeMapMgr.h>
#include "gsys/gsysModelRenderQueue.h"

namespace sead {
class Heap;
class LookAtCamera;
}

namespace agl {
class DrawContext;
}

namespace gsys {

class ShaderContext;

// The cube-map drawer owned by ModelSceneGI at +0x420 (0x1068 bytes; constructor
// 0x7100c7d198, initialize 0x7100c7d330). Only the members the ModelSceneGI getters
// and setter read are modelled.
class ModelCubeMapDrawer {
public:
    // 0x7100c7dcc8: the argument record's empty destructor.
    struct CreateArg {
        ~CreateArg();
    };

    // 0x7100c7d950: sorts the two render queues.
    void update();
    // 0x7100c7d404: ModelSceneGI::calcFrame draws the frame's cube maps.
    void calc(int frame);
    // 0x7100c7d978: draws one face of a cube map; the colour is the layer's clear colour.
    void draw(agl::DrawContext* draw_context, int view_index, const sead::LookAtCamera* camera,
              const sead::Color4f& clear_color);

private:
    u8 _0[0x348];

public:
    ShaderContext* mShaderContext;  // 348

private:
    u8 _350[0x3d8 - 0x350];

public:
    ModelRenderQueue mQueue0;  // 3d8
    ModelRenderQueue mQueue1;  // 418
    agl::env::CubeMapMgr mCubeMapMgr;  // 458

private:
    u8 _afterCubeMapMgr[0xec0 - 0x458 - sizeof(agl::env::CubeMapMgr)];

public:
    void* mCubeMap;  // ec0
};
static_assert(offsetof(ModelCubeMapDrawer, mShaderContext) == 0x348);
static_assert(offsetof(ModelCubeMapDrawer, mQueue0) == 0x3d8);
static_assert(offsetof(ModelCubeMapDrawer, mQueue1) == 0x418);
static_assert(offsetof(ModelCubeMapDrawer, mCubeMapMgr) == 0x458);
static_assert(offsetof(ModelCubeMapDrawer, mCubeMap) == 0xec0);

}  // namespace gsys
