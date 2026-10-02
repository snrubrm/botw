#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class CreateBgm : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CreateBgm, ksys::act::ai::Behavior)
public:
    explicit CreateBgm(const InitArg& arg);
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x710061d0c8)
    ~CreateBgm() override;  // not decompiled yet

    /* 0x28 */ sead::SafeString mBgmName_s{};
    /* 0x38 */ u32 _38 = 41;
};
KSYS_CHECK_SIZE_NX150(CreateBgm, 0x40);

}  // namespace uking::behavior
