#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetInfRotSpeedToSpineController : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetInfRotSpeedToSpineController, ksys::act::ai::Behavior)
public:
    explicit SetInfRotSpeedToSpineController(const InitArg& arg);
    ~SetInfRotSpeedToSpineController() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mRotSpeed_s{};
};
KSYS_CHECK_SIZE_NX150(SetInfRotSpeedToSpineController, 0x30);

}  // namespace uking::behavior
