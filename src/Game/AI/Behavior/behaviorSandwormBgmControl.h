#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SandwormBgmControl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SandwormBgmControl, ksys::act::ai::Behavior)
public:
    explicit SandwormBgmControl(const InitArg& arg);
    ~SandwormBgmControl() override;
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void loadParams() override;

    /* 0x28 */ const int* mType_s{};
    /* 0x30 */ const bool* mIsEnable_s{};
};
KSYS_CHECK_SIZE_NX150(SandwormBgmControl, 0x38);

}  // namespace uking::behavior
