#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class PosControl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PosControl, ksys::act::ai::Behavior)
public:
    explicit PosControl(const InitArg& arg);
    ~PosControl() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mImpulse_s{};
};
KSYS_CHECK_SIZE_NX150(PosControl, 0x30);

}  // namespace uking::behavior
