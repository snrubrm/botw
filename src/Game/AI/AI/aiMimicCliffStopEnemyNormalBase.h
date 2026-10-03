#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace uking::ai {

class MimicCliffStopEnemyNormalBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MimicCliffStopEnemyNormalBase, ksys::act::ai::Ai)
public:
    explicit MimicCliffStopEnemyNormalBase(const InitArg& arg);
    ~MimicCliffStopEnemyNormalBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100352994: turns the hand bone (_88) towards the ground below OffsetHand.
    void sub_7100352994();
    // 0x7100352b60: turns the tail bone (_130) towards the ground below OffsetTail.
    void sub_7100352B60();
    // 0x7100352d14: switches to 気づき when the awareness sensor 1 notices a target.
    bool sub_7100352D14();
    // 0x710035307c: ground hit position below the point `offset` ahead of the actor.
    void sub_710035307C(sead::Vector3f* out, f32 offset);

protected:
    // Inline-only in the original (name guess; evidence: the param pack sits above sub_7100352D14's filter).
    void changeToNotice();

    // static_param at offset 0x38
    const int* mNoticeSoundTime_s{};
    // static_param at offset 0x40
    const float* mOffsetHand_s{};
    // static_param at offset 0x48
    const float* mOffsetTail_s{};
    // static_param at offset 0x50
    const float* mOffsetHandRotBase_s{};
    // aitree_variable at offset 0x58
    int* mMimicryMaterial_a{};
    // aitree_variable at offset 0x60
    bool* mIsStartResetMimicry_a{};
    // aitree_variable at offset 0x68
    bool* mIsCliffFreeze_a{};
    sead::Vector3f _70;
    f32 _7c = 0;
    s32 _80 = 0;
    ksys::act::BoneHandle _88;
    ksys::act::BoneHandle _130;
    f32 _1d8 = 0;
    u8 _1dc = 0xff;
};
KSYS_CHECK_SIZE_NX150(MimicCliffStopEnemyNormalBase, 0x1e0);

}  // namespace uking::ai
