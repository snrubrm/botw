#pragma once

#include <basis/seadTypes.h>
#include <cstddef>
#include "gsys/gsysModelSceneEnv.h"

namespace agl::pfx {
class DepthOfField;
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
    // 0x7100c0ff48 / 0x7100c0ffe4 (CSV names; declared only): attach / detach a model.
    void bind_(Model* model);
    void unbind_(Model* model);

    // OpenWorldStage::unload 0x71007c5d20 passes -1 to process every scene entry.
    // 0x7100c13cb4 releases each entry's +0x3a0 object and clears flag 0x10 at +0x391.
    void sub_7100C13CB4(s32 index);

    u8 _0[0x130];

    /* 0x130 */ ModelSceneEnv mEnv;  // constructed by the ModelScene constructor

    u8 _1288[0x3428 - 0x1288];

    // Null when the scene has no depth of field. 0x7100c2b674 / 0x7100c2b63c pass it to
    // DepthOfField::setIndirectTextureData; 0x7100c11a80 copies context parameters into it.
    /* 0x3428 */ agl::pfx::DepthOfField* mDepthOfField;

    u8 _3430[0x3758 - 0x3430];

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

    u8 _52e8[0x5d80 - 0x52e8];

    // Flags (0xa39 after construction). Game code sets bit 1 after it applied an env set (SystemApplyEnvSetAction)
    // and bit 13 when it creates the scene; ModelScene's own code reads bits 0, 1, 2, 5 and 8.
    /* 0x5d80 */ u32 mFlags;

    u8 _5d84[0x5f20 - 0x5d84];
};
static_assert(offsetof(ModelScene, mEnv) == 0x130);
static_assert(offsetof(ModelScene, mDepthOfField) == 0x3428);
static_assert(offsetof(ModelScene, _52e0) == 0x52e0);
static_assert(offsetof(ModelScene, mFlags) == 0x5d80);
static_assert(sizeof(ModelScene) == 0x5f20);

}  // namespace gsys
