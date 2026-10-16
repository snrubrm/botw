#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class PosControl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PosControl, ksys::act::ai::Behavior)
public:
    explicit PosControl(const InitArg& arg);
    ~PosControl() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const float* mImpulse_s{};
};
KSYS_CHECK_SIZE_NX150(PosControl, 0x30);

}  // namespace uking::behavior
