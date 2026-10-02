#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SimpleAtvUnitOpenSimpleDialog : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SimpleAtvUnitOpenSimpleDialog, ksys::act::ai::Behavior)
public:
    explicit SimpleAtvUnitOpenSimpleDialog(const InitArg& arg);
    ~SimpleAtvUnitOpenSimpleDialog() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual const sead::SafeString* m14();
    virtual bool m15() { return false; }
    virtual void m16();  // not decompiled yet (0x710064214c)
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x7100641d34)
    void m7() override;  // not decompiled yet (0x7100641e4c)
    bool updateForPreDelete() override;  // not decompiled yet (0x7100619d1c)

    /* 0x28 */ const int* mCloseOption_s{};
    /* 0x30 */ const int* mTimer_s{};
    /* 0x38 */ const int* mDelayTimer_s{};
    /* 0x40 */ const int* mType_s{};
    /* 0x48 */ const bool* mOnce_s{};
    /* 0x50 */ sead::SafeString mmstxtName_s{};
    /* 0x60 */ sead::SafeString mlabelName_s{};
    /* 0x70 */ void* mSimpleDialogUnit_a{};
    /* 0x78 */ Unk_71025afb58** _78 = nullptr;
    /* 0x80 */ u32 _80 = 0;
    /* 0x84 */ bool _84 = false;
    /* 0x85 */ bool _85 = false;
};
KSYS_CHECK_SIZE_NX150(SimpleAtvUnitOpenSimpleDialog, 0x88);

}  // namespace uking::behavior
