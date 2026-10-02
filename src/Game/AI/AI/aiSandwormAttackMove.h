#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace gsys {
class Model;
}

namespace uking::ai {

// vtable 0x710241b460 (no RTTI of its own): damage callback embedded in SandwormAttackMove.
// call() (0x71005569cc) triples the damage when the attacker is in front of the bone `_30`.
class Unk_710241b460 : public dmg::DamageCallback {
public:
    explicit Unk_710241b460(gsys::Model* model) : _28(model) {}

    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    gsys::Model* _28;
    gsys::BoneAccessKeyEx _30;
    f32 _68 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710241b460, 0x70);

class SandwormAttackMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormAttackMove, ksys::act::ai::Ai)
public:
    explicit SandwormAttackMove(const InitArg& arg);
    ~SandwormAttackMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_71005570C4();

protected:
    // static_param at offset 0x38
    const float* mSecessionDist_s{};
    // static_param at offset 0x40
    const float* mAttackAngle_s{};
    // static_param at offset 0x48
    const float* mDamageAngle_s{};
    // static_param at offset 0x50
    const float* mLostDist_s{};
    // static_param at offset 0x58
    sead::SafeString mDamageBaseNode_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    Unk_710241b460 _70{mActor->getModel()};
};
KSYS_CHECK_SIZE_NX150(SandwormAttackMove, 0xe0);

}  // namespace uking::ai
