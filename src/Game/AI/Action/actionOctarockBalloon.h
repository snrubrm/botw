#pragma once

#include "Game/AI/Action/actionOctarockBalloonBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

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

    // static_param at offset 0x138
    const float* mTargetScale_s{};
    // static_param at offset 0x140
    const float* mStartSignTimer_s{};
    // static_param at offset 0x148
    sead::SafeString mStartASName_s{};
    // static_param at offset 0x158
    sead::SafeString mSignASName_s{};
    /* 0x168 */ ksys::act::Actor* _168 = mActor;
    /* 0x170 */ void* _170 = nullptr;
    /* 0x178 */ u32 _178 = 0;
    u32 _17c;
    /* 0x180 */ f32 _180 = -1.0f;
    /* 0x184 */ f32 _184 = 0;
    f32 _188 = 0;
    f32 _18c = 0;
    u32 _190 = 0;
};
KSYS_CHECK_SIZE_NX150(OctarockBalloon, 0x198);

}  // namespace uking::action
