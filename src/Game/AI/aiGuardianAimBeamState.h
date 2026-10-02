#pragma once

#include <container/seadBuffer.h>
#include <gsys/gsysModelAccessKey.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace uking::ai {

// Name from the CSV (GuardianAimBeamState::ctor 0x71006f1ea0, init, update, end; destructor
// 0x71006f1f58). Embedded in GuardianAimBeam (+0x68), PriestBossAimBeam and MiniBeamAttack.
// TODO: incomplete (init / update / end not decompiled; member types partly guessed from the
// constructor: four {s32, pointer} pairs are taken to be sead::Buffers).
class GuardianAimBeamState {
public:
    GuardianAimBeamState();
    ~GuardianAimBeamState();

    void* _0 = nullptr;
    sead::SafeString _8;
    sead::SafeString _18;
    void* _28 = nullptr;
    sead::Buffer<void*> _30;
    sead::Buffer<void*> _40;
    sead::Buffer<void*> _50;
    sead::Buffer<void*> _60;
    u32 _70 = 0;
    u32 _74;
    sead::Vector3f _78 = sead::Vector3f::zero;
    u32 _84 = 0;
    sead::Vector3f _88 = sead::Vector3f::zero;
    u32 _94 = 0;
    u32 _98 = 0;
    u32 _9c = 0;
    gsys::BoneAccessKeyEx _a0;
    u32 _d8 = 0;
    sead::Vector3f _dc = sead::Vector3f::zero;
    u8 _e8[0xf4 - 0xe8];
    f32 _f4 = 150.0;
};
KSYS_CHECK_SIZE_NX150(GuardianAimBeamState, 0xf8);

}  // namespace uking::ai
