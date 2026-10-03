#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkLodNoCountTimer : public Fork {
    SEAD_RTTI_OVERRIDE(ForkLodNoCountTimer, Fork)
public:
    explicit ForkLodNoCountTimer(const InitArg& arg);
    ~ForkLodNoCountTimer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWaitFrame_s{};
    // static_param at offset 0x38
    const int* mWaitFrameRand_s{};
    // static_param at offset 0x40
    const float* mCamDist_s{};
    // static_param at offset 0x48
    const bool* mIsTrgStart_s{};
    /* 0x50 */ s32 _50 = -1;  // 2 = ?, set to !IsTrgStart in init_
    /* 0x58 */ ksys::act::Actor* _58 = mActor;
    /* 0x60 */ f32 _60 = 0.0f;  // wait frames
    /* 0x64 */ f32 _64 = -1.0f;  // CamDist
    /* 0x68 */ s32 _68 = 0;  // WaitFrame range
    /* 0x6c */ s32 _6c = 0;
};
KSYS_CHECK_SIZE_NX150(ForkLodNoCountTimer, 0x70);

}  // namespace uking::action
