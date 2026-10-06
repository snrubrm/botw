#pragma once

#include "Game/AI/Action/actionOctarockBalloonBase.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class SphereRigidBody;
}

namespace uking::action {

class OctarockBalloon : public OctarockBalloonBase {
    SEAD_RTTI_OVERRIDE(OctarockBalloon, OctarockBalloonBase)
public:
    explicit OctarockBalloon(const InitArg& arg);
    ~OctarockBalloon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32() override;

    // 0x710020ecb0 (placeholder name): swaps the main body for the "SwapBody" sensor body and relinks the Tgt body.
    void sub_710020ECB0();
    // inline-only in the original; name is a guess: the same translate / radius / reset sequence is inlined three
    // times (twice in enter_, once in calc_).
    void applyScale_(ksys::phys::SphereRigidBody* body, f32 scale);

    // static_param at offset 0x138
    const float* mTargetScale_s{};
    // static_param at offset 0x140
    const float* mStartSignTimer_s{};
    // static_param at offset 0x148
    sead::SafeString mStartASName_s{};
    // static_param at offset 0x158
    sead::SafeString mSignASName_s{};
    /* 0x168 */ ksys::act::Unk_7100d3bce4 _168{mActor};  // the timer is at 0x170
    /* 0x180 */ f32 _180 = -1.0f;
    /* 0x184 */ sead::Vector3f _184 = {0, 0, 0};
    u32 _190 = 0;
};
KSYS_CHECK_SIZE_NX150(OctarockBalloon, 0x198);

}  // namespace uking::action
