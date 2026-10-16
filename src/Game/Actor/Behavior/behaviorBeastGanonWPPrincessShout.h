#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/Behavior/behaviorSimpleAtvUnitOpenSimpleDialog.h"

namespace uking::behavior {

class BeastGanonWPPrincessShout : public SimpleAtvUnitOpenSimpleDialog {
    SEAD_RTTI_OVERRIDE(BeastGanonWPPrincessShout, SimpleAtvUnitOpenSimpleDialog)
public:
    explicit BeastGanonWPPrincessShout(const InitArg& arg);
    ~BeastGanonWPPrincessShout() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    const sead::SafeString* m14() override;
    void m16() override;

    /* 0x88 */ u32 _88 = 0;
    /* 0x8c */ sead::BitFlag16 _8c;
    /* 0x90 */ const int* mSingleIdx_s{};
    /* 0x98 */ sead::SafeString mlabelName2_s{};
    /* 0xa8 */ sead::SafeString mlabelName3_s{};
    /* 0xb8 */ sead::SafeString mlabelName4_s{};
    /* 0xc8 */ sead::SafeString mlabelName5_s{};
    /* 0xd8 */ sead::SafeString mlabelName6_s{};
    /* 0xe8 */ sead::SafeString mlabelName7_s{};
    /* 0xf8 */ sead::SafeString mlabelName8_s{};
    /* 0x108 */ sead::SafeString mlabelName9_s{};
    /* 0x118 */ sead::SafeString mlabelName10_s{};
    /* 0x128 */ void* mWeakPointActiveFlag_a{};
};
KSYS_CHECK_SIZE_NX150(BeastGanonWPPrincessShout, 0x130);

}  // namespace uking::behavior
