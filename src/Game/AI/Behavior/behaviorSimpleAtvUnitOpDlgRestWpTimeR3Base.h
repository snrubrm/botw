#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// CSV name: SimpleAtvUnitOpDlgRestWpTimeR3 (the base of that behavior).
class SimpleAtvUnitOpDlgRestWpTimeR3Base : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SimpleAtvUnitOpDlgRestWpTimeR3Base, ksys::act::ai::Behavior)
public:
    explicit SimpleAtvUnitOpDlgRestWpTimeR3Base(const InitArg& arg);
    ~SimpleAtvUnitOpDlgRestWpTimeR3Base() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual const sead::SafeString* m14();
    virtual void m15() {}
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x7100641100)
    void m7() override;  // not decompiled yet (0x7100641200)

    /* 0x28 */ const int* mCloseOption_s{};
    /* 0x30 */ const int* mTimer_s{};
    /* 0x38 */ const int* mType_s{};
    /* 0x40 */ const int* mRestTime_s{};
    /* 0x48 */ sead::SafeString mmstxtName_s{};
    /* 0x58 */ sead::SafeString mlabelName_s{};
    /* 0x68 */ bool* mIsWeakPointAppearMode_a{};
    /* 0x70 */ bool* mInBeastGanonVoiceSequence_a{};
    /* 0x78 */ void* mWeakPointCounter_a{};
    /* 0x80 */ void* mSimpleDialogUnit_a{};
    /* 0x88 */ Unk_71025afb58** _88 = nullptr;
    /* 0x90 */ bool _90 = false;
};

}  // namespace uking::behavior
