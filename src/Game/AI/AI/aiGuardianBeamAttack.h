#pragma once

#include <math/seadVector.h>
#include <xlink2/xlink2Handle.h>
#include "Game/AI/AI/aiGuardianBeamAttackBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::ai {

class GuardianBeamAttack;

// Placeholder name (vtable 0x71023f6f80, size 0xa8): the ModelBindInfo subclass created by
// GuardianBeamAttack::init_ (it has no RTTI of its own); it keeps its owner at +0xa0.
class Unk_71023f6f80 : public ksys::act::ModelBindInfo {
public:
    explicit Unk_71023f6f80(GuardianBeamAttack* owner) : _a0(owner) {}
    ~Unk_71023f6f80() override = default;
    bool m5(ksys::act::Actor* actor) override;

    /* 0xa0 */ GuardianBeamAttack* _a0;
};
KSYS_CHECK_SIZE_NX150(Unk_71023f6f80, 0xa8);

class GuardianBeamAttack : public GuardianBeamAttackBase {
    SEAD_RTTI_OVERRIDE(GuardianBeamAttack, GuardianBeamAttackBase)
public:
    explicit GuardianBeamAttack(const InitArg& arg);
    ~GuardianBeamAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x710040fc24 (not decompiled): the light update (called by Unk_71023f6f80::m5).
    void sub_710040FC24(ksys::act::Actor* actor);

protected:
    sead::Vector3f _38 = sead::Vector3f::ey;
    xlink2::Handle _48;
    xlink2::Handle _58;
    sead::Vector3f _68{5.0f, 30.0f, 0.0f};
    Unk_71023f6f80* _78{};
    // static_param at offset 0x80
    const float* mLightRadius_s{};
    // static_param at offset 0x88
    const float* mLightLength_s{};
    // static_param at offset 0x90
    const float* mLightLengthOffset_s{};
    // static_param at offset 0x98
    const float* mEarSpeed_s{};
    // static_param at offset 0xa0
    const bool* mAdjustRadius_s{};
};

}  // namespace uking::ai
