#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class NPCTebaApproachPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTebaApproachPlayer, ksys::act::ai::Action)
public:
    explicit NPCTebaApproachPlayer(const InitArg& arg);
    ~NPCTebaApproachPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const int* mUpdateTargetFrame_s{};
        // static_param at offset 0x28
        const float* mPlayerMaxHeight_s{};
        // static_param at offset 0x30
        const float* mMaxMoveSpeed_s{};
        // static_param at offset 0x38
        const float* mTurnSpeed_s{};
        // static_param at offset 0x40
        const float* mTurnRadius_s{};
        // static_param at offset 0x48
        const float* mReduceMaxSpeedChasePlayer_s{};
    } mParams;

    // Local listener subclass (own vtable in this TU: D0 0x710020802c); message 0x1800019.
    class Listener : public Unk_7102450648 {
    public:
        Listener() : Unk_7102450648(0x1800019) {}
    };

    f32 _50;
    f32 _54;
    f32 _58;
    s32 _5c = 0;
    ksys::VFRValue _60;
    sead::Vector3f _6c{0, 0, 0};
    sead::Matrix33f _78;
    Listener _a0;
};

}  // namespace uking::action
