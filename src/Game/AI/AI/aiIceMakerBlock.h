#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::ai {

// vtable 0x71023fd228: damage callback without RTTI of its own (functions in the IceMakerBlock TU:
// call 0x7100448720 — attackers with the CanBreakIceMakerBlock or AncientWeapon tag; it reads the
// attacker link from DamageManagerBase slot 37, which is still declared as `s64 m37()`). Placeholder.
class Unk_71023fd228 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

class IceMakerBlock : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(IceMakerBlock, ksys::act::ai::Ai)
public:
    explicit IceMakerBlock(const InitArg& arg);
    ~IceMakerBlock() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    Unk_71023fd228 _38;
    // static_param at offset 0x60
    const float* mSubRigidStartOffset_s{};
    // static_param at offset 0x68
    const float* mSubRigidEndOffset_s{};
    // static_param at offset 0x70
    const float* mSubRigidExOffset_s{};
    ksys::phys::RigidBody* _78[2];
    ksys::phys::RigidBody* _88;
    ksys::phys::RigidBody* _90;
    ksys::phys::RigidBody* _98;
    s32 _a0 = 0;
    bool _a4 = false;
    bool _a5 = true;
    bool _a6 = false;
    bool _a7 = false;
    bool _a8 = false;
    gsys::BoneAccessKeyEx _b0;
    gsys::BoneAccessKeyEx _e8;
    f32 _120 = 0.0f;
    f32 _124 = -0.1f;
    f32 _128 = 0.0f;
    f32 _12c = 3.0f;
    f32 _130 = 0.5f;
    f32 _134 = 3.0f;
    sead::Vector3f _138 = {3.0f, 4.0f, 3.0f};
    f32 _144 = 1.0f;
    f32 _148 = 1.0f;
    f32 _14c = 30.0f;
    Unk_71023b0898 _150{mActor, 0x8000083};
};
KSYS_CHECK_SIZE_NX150(IceMakerBlock, 0x190);

}  // namespace uking::ai
