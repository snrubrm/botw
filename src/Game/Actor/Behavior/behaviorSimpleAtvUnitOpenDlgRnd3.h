#pragma once

#include <prim/seadSafeString.h>
#include "Game/Actor/Behavior/behaviorSimpleAtvUnitOpenDlg.h"

namespace uking::behavior {

class SimpleAtvUnitOpenDlgRnd3 : public SimpleAtvUnitOpenDlg {
    SEAD_RTTI_OVERRIDE(SimpleAtvUnitOpenDlgRnd3, SimpleAtvUnitOpenDlg)
public:
    explicit SimpleAtvUnitOpenDlgRnd3(const InitArg& arg);
    ~SimpleAtvUnitOpenDlgRnd3() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    const sead::SafeString* m14() override;
    s32 m17() override { return 3; }
    s32 m18() override { return 7; }

    /* 0x90 */ sead::SafeString mlabelName2_s{};
    /* 0xa0 */ sead::SafeString mlabelName3_s{};
};
KSYS_CHECK_SIZE_NX150(SimpleAtvUnitOpenDlgRnd3, 0xb0);

}  // namespace uking::behavior
