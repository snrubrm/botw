#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <thread/seadAtomic.h>
#include <cstddef>
#include <effect/aglFxCloud.h>
#include <environment/aglEnvObjBuffer.h>
#include "gsys/gsysModelJobQueue.h"
#include "gsys/gsysModelSceneContext.h"
#include "gsys/gsysModelSceneEnv.h"
#include "gsys/gsysModelSceneShadow.h"
#include "gsys/gsysModelSceneBuffer.h"

namespace agl::pfx {
class ColorCorrection;
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

class ModelNW;

class Layer3D;

class ModelScene {
public:
    // 0x7100c0fe14: re-registers this scene with the model manager.
    void bindEnv_();

    // 0x7100c0fe2c / 0x7100c0fedc (declared only): register a 3D layer and return its index,
    // and unregister it (Layer3D::setModelScene).
    s8 add_(Layer3D* layer);
    void remove_(Layer3D* layer);

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

    // 0x7100c13bfc / 0x7100c13cb4: add a particle group to / clear the particle groups of the context `index`
    // (all contexts for a negative index). OpenWorldStage::unload 0x71007c5d20 passes -1.
    void addParticleGroup(int group, int index);
    void clearParticleGroup(int index);

    // 0x7100c1016c / 0x7100c10c88.
    void skipDraw();
    void calcModelUnit_(sead::WorkerMgr* wm);
    // 0x7100c10ccc / 0x7100c10f28: the world / render-view passes of calc.
    void calcWorld_(sead::WorkerMgr* wm);
    void calcRenderView_(sead::WorkerMgr* wm);
    // 0x7100c10c94 / 0x7100c12114 / 0x7100c12264: the remaining calc steps.
    void sortQueue_(sead::WorkerMgr* wm);
    void calcDrawBackGround_(sead::WorkerMgr* wm);
    void calcGPU_(sead::WorkerMgr* wm);
    // 0x7100c13d40
    bool isForceZPrePassEnabled(int index) const;
    // 0x7100c10148
    bool isSnapshotMgrEnabled() const;

    // 0x7100c10a5c (the three int arguments' meanings are unrecovered).
    void calc(sead::WorkerMgr* wm, int, int, int);
    // 0x7100c10a0c: one scene step followed by the job queue's model update.
    void update(sead::WorkerMgr* wm);

    // Inline in the original; ksys::world::EnvMgr::calcEntryJob 0x71010db0d4 reads the first scene's.
    agl::pfx::ColorCorrection* getColorCorrection() const { return mColorCorrection; }

    u8 _0[0x108];
    // The render contexts (initialize 0x7100c0d9fc). 0x7100d9f8ac reads their number from Graphics' first scene
    // and passes it as EffectModelDrawUnit::CreateArg::_0, which createModel 0x7100c555f0 forwards to
    // Model::CreateArg::_4 (one of the two model counts).
    /* 0x108 */ sead::Buffer<ModelSceneContext> mContexts;
    // isSnapshotMgrEnabled 0x7100c10148 and isForceZPrePassEnabled 0x7100c13d40 read it.
    /* 0x118 */ ModelSceneConfig* mConfig;
    u8 _120[0x130 - 0x120];

    /* 0x130 */ ModelSceneEnv mEnv;  // constructed by the ModelScene constructor

    u8 _1288[0x19c8 - 0x1288];
    // sortQueue_ 0x7100c10c94 calls calc on the shadow object at +0x19c8.
    /* 0x19c8 */ ModelSceneShadow mShadow;
    u8 _afterShadow[0x3428 - 0x19c8 - sizeof(ModelSceneShadow)];

    // Null when the scene has no depth of field. 0x7100c2b674 / 0x7100c2b63c pass it to
    // DepthOfField::setIndirectTextureData; 0x7100c11a80 copies context parameters into it.
    /* 0x3428 */ agl::pfx::DepthOfField* mDepthOfField;

    u8 _3430[0x3438 - 0x3430];

    // Read by ksys::world::EnvMgr::calcEntryJob 0x71010db0d4 through the first scene.
    /* 0x3438 */ agl::pfx::ColorCorrection* mColorCorrection;

    u8 _3440[0x3700 - 0x3440];

    // Ofx preset manager. Graphics 0x7100f2ddf0 looks up a preset through it (the manager is the
    // pointer it passes to OccludedEffectMgr::getOfx) and calls agl::fx::OfxBase::loadPresetByIndex;
    // ModelScene 0x7100c2c840 / 0x7100c2c854 also dispatch through it.
    /* 0x3700 */ agl::fx::OccludedEffectMgr* mOfxManager;

    u8 _3708[0x3740 - 0x3708];

    // Pointer at ModelSceneFx + 0x2c8 (ModelSceneFx is the sub-object at +0x3478, not modelled
    // separately). ModelSceneFx::initialize 0x7100c2e284 allocates the 0x7758-byte agl::fx::Cloud
    // and stores it here; Graphics 0x7100f2dda0 clears its flag byte +0x460, and ModelSceneFx
    // calcOccludedEffect 0x7100c2eea0 / isCloudEnabled 0x7100c2ee6c / drawCloud 0x7100c2fb7c
    // test it.
    /* 0x3740 */ agl::fx::Cloud* mCloud;

    u8 _3748[0x3758 - 0x3748];

    // Effect-model draw manager of the scene. EffectModelData::addEffectModel 0x7100d9f8ac reads it from
    // the first Graphics model scene (`**(Graphics + 0x158)` = mModelScenes[0]) and calls
    // EffectModelDrawMgr::requestDeleteModel / execDeleteModel on it (0x7100d9fcfc / 0x7100d9fde4).
    /* 0x3758 */ EffectModelDrawMgr* mEffectModelDrawMgr;

    u8 _3760[0x3778 - 0x3760];
    /* 0x3778 */ ModelSceneBuffer mBuffer;
    u8 _4ea0[0x52e0 - 0x4ea0];

    // Placeholder type: the object at +0x52e0 (read by the accessor 0x7100c2ca78). Graphics::setRainRatio
    // 0x7100f2fcdc picks shader variation 2 when its byte at +0x230 is set.
    struct Unk_52e0 {
        u8 _0[0x230];
        bool _230;
    };
    /* 0x52e0 */ Unk_52e0* _52e0;

    u8 _52e8[0x5550 - 0x52e8];
    ModelJobQueue mJobQueue;  // +0x5550
    u8 _56c0[0x56d0 - 0x56c0];
    // Owned scene-pass model: initialize 0x7100c0d9fc stores postCreateModel_
    // here, binds the scene/procedural units, then binds the model to this scene.
    // ItemFilter 0x7101293d68 searches its named units; calc requests its draw.
    /* 0x56d0 */ Model* mSceneModel;
    // The first unit of the scene model as a ModelNW (initialize 0x7100c0d9fc stores the
    // 0x308-byte ModelNW created by 0x7100c0334c; ksys::gfx 0x7100f19a2c dynamic-casts it).
    /* 0x56d8 */ ModelNW* mSceneModelNW;
    u8 _56e0[0x5d80 - 0x56e0];

    // Flags (0xa39 after construction). Game code sets bit 1 after it applied an env set (SystemApplyEnvSetAction)
    // and bit 13 when it creates the scene; ModelScene's own code reads bits 0, 1, 2, 5 and 8.
    // The byte at +0x5d81 is the high byte of this word (bits 8..15): MassRenderer::requestDraw
    // 0x71011e3cd0 tests bit 8 and ModelScene's own code tests bits 12 and 13. A u32 test such as
    // (mFlags & 0x100) is narrowed by the compiler to the original ldrb [x8, #0x5d81].
    /* 0x5d80 */ u32 mFlags;

    /// Bits 6 and 7 gate the job queue's model update; both must be set.
    u32 mFlags5d84;
    u8 _5d88[0x5da0 - 0x5d88];
    // Rain/snow intensity. ModelScene 0x7100c1020c computes it from +0x5da0 and a scale and stores it
    // here; MassRenderer::requestDraw 0x71011e3cd0 compares it with 0.0f.
    /* 0x5da0 */ f32 _5da0;
    /* 0x5da4 */ f32 mRainRatio;

    u8 _5da8[0x5db0 - 0x5da8];
    // isSnapshotMgrEnabled 0x7100c10148 null-tests this pointer.
    /* 0x5db0 */ void* mSnapshotMgr;
    u8 _5db8[0x5f20 - 0x5db8];
};
static_assert(offsetof(ModelScene, mEnv) == 0x130);
static_assert(offsetof(ModelScene, mDepthOfField) == 0x3428);
static_assert(offsetof(ModelScene, mCloud) == 0x3740);
static_assert(offsetof(ModelScene, mBuffer) == 0x3778);
static_assert(offsetof(ModelScene, _52e0) == 0x52e0);
static_assert(offsetof(ModelScene, mSceneModel) == 0x56d0);
static_assert(offsetof(ModelScene, mSceneModelNW) == 0x56d8);
static_assert(offsetof(ModelScene, mFlags) == 0x5d80);
static_assert(sizeof(ModelScene) == 0x5f20);

}  // namespace gsys
