#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class StalGiantSleepNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalGiantSleepNormal, ksys::act::ai::Ai)
public:
    explicit StalGiantSleepNormal(const InitArg& arg);
    ~StalGiantSleepNormal() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    // Unnamed in the binary (0x71005a5464 / 0x71005a5e58): switch the actor into / out of the sleeping state.
    void sub_71005A5464();
    void sub_71005A5E58();

protected:
    // static_param at offset 0x38
    const float* mAwakeDelayTime_s{};
    // static_param at offset 0x40
    const bool* mIsAwakenByHearing_s{};
    // static_param at offset 0x48
    const bool* mIsWaitAfterAwaken_s{};
    sead::Vector3f _50 = sead::Vector3f::zero;
    Unk_7102424730 _60;
    u32 _b0 = 0;
    bool _b4 = false;
    bool _b5 = false;
    bool _b6 = false;
    ksys::act::Actor* _b8 = mActor;
    ksys::Timer _c0;
};
KSYS_CHECK_SIZE_NX150(StalGiantSleepNormal, 0xd0);

}  // namespace uking::ai
