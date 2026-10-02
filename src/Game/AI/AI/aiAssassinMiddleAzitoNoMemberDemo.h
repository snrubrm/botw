#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMiddleAzitoNoMemberDemo : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AssassinMiddleAzitoNoMemberDemo, ksys::act::ai::Ai)
public:
    explicit AssassinMiddleAzitoNoMemberDemo(const InitArg& arg);
    ~AssassinMiddleAzitoNoMemberDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // static_param at offset 0x38
    const int* mDelayTimeMin_s{};
    // static_param at offset 0x40
    const int* mDelayTimeMax_s{};
    Unk_7102450528 _48;
    sead::JobQueueLock _b8;
    u8 _bc[4];
    f32 _c0 = 0;
    u32 _c4 = 0;
    u32 _c8 = 0;
    bool _cc = false;
    f32 _d0 = 0;
};
KSYS_CHECK_SIZE_NX150(AssassinMiddleAzitoNoMemberDemo, 0xd8);

}  // namespace uking::ai
