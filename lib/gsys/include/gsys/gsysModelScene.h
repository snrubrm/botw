#pragma once

#include <basis/seadTypes.h>
#include <cstddef>
#include "gsys/gsysModelSceneEnv.h"

namespace gsys {

// A scene that model units are bound to and drawn in. The object is 0x5f20 bytes (the function at 0x7100c0d920
// allocates it, runs the constructor 0x7100c0f7b8 and then the initialization 0x7100c0d9fc).
// TODO: incomplete. Only what game code reads and writes is modeled; the bases (a polymorphic base at +0x0, a
// sead::IDisposer at +0xe0 and a polymorphic base at +0x100) and the other members are not.
class Model;

class ModelScene {
public:
    // 0x7100c0ff48 / 0x7100c0ffe4 (CSV names; declared only): attach / detach a model.
    void bind_(Model* model);
    void unbind_(Model* model);

    u8 _0[0x130];

    /* 0x130 */ ModelSceneEnv mEnv;  // constructed by the ModelScene constructor

    u8 _1288[0x5d80 - 0x1288];

    // Flags (0xa39 after construction). Game code sets bit 1 after it applied an env set (SystemApplyEnvSetAction)
    // and bit 13 when it creates the scene; ModelScene's own code reads bits 0, 1, 2, 5 and 8.
    /* 0x5d80 */ u32 mFlags;

    u8 _5d84[0x5f20 - 0x5d84];
};
static_assert(offsetof(ModelScene, mEnv) == 0x130);
static_assert(offsetof(ModelScene, mFlags) == 0x5d80);
static_assert(sizeof(ModelScene) == 0x5f20);

}  // namespace gsys
