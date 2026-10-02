#pragma once

#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpenSimpleDialog.h"

namespace uking::behavior {

class SimpleAtvUnitOpenDlg : public SimpleAtvUnitOpenSimpleDialog {
    SEAD_RTTI_OVERRIDE(SimpleAtvUnitOpenDlg, SimpleAtvUnitOpenSimpleDialog)
public:
    explicit SimpleAtvUnitOpenDlg(const InitArg& arg);
    ~SimpleAtvUnitOpenDlg() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual s32 m17() { return 1; }
    virtual s32 m18() { return 1; }
    void m16() override;  // not decompiled yet (0x71006418d0)

    /* 0x86 */ u16 _86 = 0;
    /* 0x88 */ u32 _88 = 0;
};

}  // namespace uking::behavior
