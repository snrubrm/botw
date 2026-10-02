#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpenSimpleDialog.h"

namespace uking::behavior {

class BeastGanonWPPrincessShout : public SimpleAtvUnitOpenSimpleDialog {
    SEAD_RTTI_OVERRIDE(BeastGanonWPPrincessShout, SimpleAtvUnitOpenSimpleDialog)
public:
    explicit BeastGanonWPPrincessShout(const InitArg& arg);
    ~BeastGanonWPPrincessShout() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    const sead::SafeString* m14() override;
    void m16() override;  // not decompiled yet (0x710061a35c)

    /* 0x88 */ u32 _88 = 0;
    /* 0x8c */ u16 _8c = 0;
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
