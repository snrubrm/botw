#pragma once

#include <basis/seadTypes.h>
#include <thread/seadAtomic.h>
#include <cstddef>
#include <environment/aglEnvObjBuffer.h>
#include "gsys/gsysModelJobQueue.h"
#include "gsys/gsysModelSceneEnv.h"

namespace agl::pfx {
class DepthOfField;
}

namespace agl::fx {
class OccludedEffectMgr;
}

namespace sead {
class WorkerMgr;
}

namespace gsys {

// A scene that model units are bound to and drawn in. The object is 0x5f20 bytes (the function at 0x7100c0d920
// allocates it, runs the constructor 0x7100c0f7b8 and then the initialization 0x7100c0d9fc).
// TODO: incomplete. Only what game code reads and writes is modeled; the bases (a polymorphic base at +0x0, a
// sead::IDisposer at +0xe0 and a polymorphic base at +0x100) and the other members are not.
class Model;

class EffectModelDrawMgr;

class ModelScene {
public:
    // Constructor 0x7100c0d8f0: one, an empty name, a zero at +0x18 and an
    // agl::env::EnvObjBuffer::AllocateArg at +0x20.
    struct CreateArg {
        CreateArg();
        s32 _0;
        sead::SafeString mName;
        u64 _18;
        agl::env::EnvObjBuffer::AllocateArg mAllocateArg;
    };
    // 0x7100c0ff48 / 0x7100c0ffe4 (CSV names; declared only): attach / detach a model.
    void bind_(Model* model);
    void unbind_(Model* model);

    // OpenWorldStage::unload 0x71007c5d20 passes -1 to process every scene entry.
    // 0x7100c13cb4 releases each entry's +0x3a0 object and clears flag 0x10 at +0x391.
    void sub_7100C13CB4(s32 index);

    // 0x7100c1016c / 0x7100c10c88.
    void skipDraw();
    void calcModelUnit_(sead::WorkerMgr* wm);
    // 0x7100c10ccc / 0x7100c10f28: the world / render-view passes of calc.
    void calcWorld_(sead::WorkerMgr* wm);
    void calcRenderView_(sead::WorkerMgr* wm);

    // 0x7100c10a5c (the three int arguments' meanings are unrecovered).
    void calc(sead::WorkerMgr* wm, int, int, int);

    u8 _0[0x108];
    // 0x7100d9f8ac reads this word from Graphics' first scene and passes it as
    // EffectModelDrawUnit::CreateArg::_0, which createModel 0x7100c555f0 forwards to
    // Model::CreateArg::_4 (one of the two model counts). The array it counts is not modelled.
    /* 0x108 */ s32 mContextNum;
    u8 _10c[0x130 - 0x10c];

    /* 0x130 */ ModelSceneEnv mEnv;  // constructed by the ModelScene constructor

    u8 _1288[0x3428 - 0x1288];

    // Null when the scene has no depth of field. 0x7100c2b674 / 0x7100c2b63c pass it to
    // DepthOfField::setIndirectTextureData; 0x7100c11a80 copies context parameters into it.
    /* 0x3428 */ agl::pfx::DepthOfField* mDepthOfField;

    u8 _3430[0x3700 - 0x3430];

    // Ofx preset manager. Graphics 0x7100f2ddf0 looks up a preset through it (the manager is the
    // pointer it passes to OccludedEffectMgr::getOfx) and calls agl::fx::OfxBase::loadPresetByIndex;
    // ModelScene 0x7100c2c840 / 0x7100c2c854 also dispatch through it.
    /* 0x3700 */ agl::fx::OccludedEffectMgr* mOfxManager;

    u8 _3708[0x3758 - 0x3708];

    // Effect-model draw manager of the scene. EffectModelData::addEffectModel 0x7100d9f8ac reads it from
    // the first Graphics model scene (`**(Graphics + 0x158)` = mModelScenes[0]) and calls
    // EffectModelDrawMgr::requestDeleteModel / execDeleteModel on it (0x7100d9fcfc / 0x7100d9fde4).
    /* 0x3758 */ EffectModelDrawMgr* mEffectModelDrawMgr;

    u8 _3760[0x52e0 - 0x3760];

    // Placeholder type: the object at +0x52e0 (read by the accessor 0x7100c2ca78). Graphics::setRainRatio
    // 0x7100f2fcdc picks shader variation 2 when its byte at +0x230 is set.
    struct Unk_52e0 {
        u8 _0[0x230];
        bool _230;
    };
    /* 0x52e0 */ Unk_52e0* _52e0;

    u8 _52e8[0x5550 - 0x52e8];
    ModelJobQueue mJobQueue;  // +0x5550
    // Model::requestDraw 0x7100bf9b88 appends to this counter/array pair.
    sead::Atomic<s32> mDrawRequestCount;
    u8 _5634[4];
    Model** mDrawRequestModels;
    u8 _5640[0x56d0 - 0x5640];
    // Owned scene-pass model: initialize 0x7100c0d9fc stores postCreateModel_
    // here, binds the scene/procedural units, then binds the model to this scene.
    // ItemFilter 0x7101293d68 searches its named units; calc requests its draw.
    /* 0x56d0 */ Model* mSceneModel;
    u8 _56d8[0x5d80 - 0x56d8];

    // Flags (0xa39 after construction). Game code sets bit 1 after it applied an env set (SystemApplyEnvSetAction)
    // and bit 13 when it creates the scene; ModelScene's own code reads bits 0, 1, 2, 5 and 8.
    // The byte at +0x5d81 is the high byte of this word (bits 8..15): MassRenderer::requestDraw
    // 0x71011e3cd0 tests bit 8 and ModelScene's own code tests bits 12 and 13. A u32 test such as
    // (mFlags & 0x100) is narrowed by the compiler to the original ldrb [x8, #0x5d81].
    /* 0x5d80 */ u32 mFlags;

    u8 _5d84[0x5da0 - 0x5d84];
    // Rain/snow intensity. ModelScene 0x7100c1020c computes it from +0x5da0 and a scale and stores it
    // here; MassRenderer::requestDraw 0x71011e3cd0 compares it with 0.0f.
    /* 0x5da0 */ f32 _5da0;
    /* 0x5da4 */ f32 mRainRatio;

    u8 _5da8[0x5f20 - 0x5da8];
};
static_assert(offsetof(ModelScene, mEnv) == 0x130);
static_assert(offsetof(ModelScene, mDepthOfField) == 0x3428);
static_assert(offsetof(ModelScene, _52e0) == 0x52e0);
static_assert(offsetof(ModelScene, mSceneModel) == 0x56d0);
static_assert(offsetof(ModelScene, mFlags) == 0x5d80);
static_assert(sizeof(ModelScene) == 0x5f20);

}  // namespace gsys
