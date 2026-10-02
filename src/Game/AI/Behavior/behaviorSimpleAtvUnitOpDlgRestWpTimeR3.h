#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpDlgRestWpTimeR3Base.h"

namespace uking::behavior {

class SimpleAtvUnitOpDlgRestWpTimeR3 : public SimpleAtvUnitOpDlgRestWpTimeR3Base {
    SEAD_RTTI_OVERRIDE(SimpleAtvUnitOpDlgRestWpTimeR3, SimpleAtvUnitOpDlgRestWpTimeR3Base)
public:
    explicit SimpleAtvUnitOpDlgRestWpTimeR3(const InitArg& arg);
    ~SimpleAtvUnitOpDlgRestWpTimeR3() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    const sead::SafeString* m14() override;  // not decompiled yet (0x7100640e54)
    void m15() override;  // not decompiled yet (0x7100640b8c)

    /* 0x98 */ sead::SafeString mlabelName3_s{};
    /* 0xa8 */ sead::SafeString mlabelName2_s{};
    /* 0xb8 */ bool _b8 = false;
    /* 0xbc */ u32 _bc = 0;
};
KSYS_CHECK_SIZE_NX150(SimpleAtvUnitOpDlgRestWpTimeR3, 0xc0);

}  // namespace uking::behavior
