#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class HorseSwitchAttRideBehavior : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(HorseSwitchAttRideBehavior, ksys::act::ai::Behavior)
public:
    explicit HorseSwitchAttRideBehavior(const InitArg& arg);
    ~HorseSwitchAttRideBehavior() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(HorseSwitchAttRideBehavior, 0x28);

}  // namespace uking::behavior
