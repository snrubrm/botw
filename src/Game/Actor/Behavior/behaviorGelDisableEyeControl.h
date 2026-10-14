#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class GelDisableEyeControl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(GelDisableEyeControl, ksys::act::ai::Behavior)
public:
    explicit GelDisableEyeControl(const InitArg& arg);
    ~GelDisableEyeControl() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const bool* mIsImmediate_s{};
};
KSYS_CHECK_SIZE_NX150(GelDisableEyeControl, 0x30);

}  // namespace uking::behavior
