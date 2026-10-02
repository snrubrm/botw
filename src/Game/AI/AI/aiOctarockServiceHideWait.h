#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class OctarockServiceHideWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OctarockServiceHideWait, ksys::act::ai::Ai)
public:
    explicit OctarockServiceHideWait(const InitArg& arg);
    ~OctarockServiceHideWait() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_71004EF670();

    // static_param at offset 0x38
    const float* mSafeAreaDist_s{};
    // static_param at offset 0x40
    const float* mSafeAreaDistRange_s{};
    // static_param at offset 0x48
    const float* mMinWaitTime_s{};
    // static_param at offset 0x50
    const float* mMinWaitTimeRand_s{};
    // static_param at offset 0x58
    const float* mNoticeTerrorLevel_s{};
    // static_param at offset 0x60
    const float* mNoticeWorryRange_s{};
    bool _68 = false;  // "AutoAim" att client enabled on enter
    bool _69 = false;  // "AutoAimHidden" att client enabled on enter
    ksys::Timer _6c;
};
KSYS_CHECK_SIZE_NX150(OctarockServiceHideWait, 0x78);

}  // namespace uking::ai
