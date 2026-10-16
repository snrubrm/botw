#pragma once

#include "Game/Actor/Behavior/behaviorInterestNeckControl.h"
#include "Game/Actor/actNPC.h"

namespace uking::behavior {

class LookAtOwnedHorse : public InterestNeckControl {
    SEAD_RTTI_OVERRIDE(LookAtOwnedHorse, InterestNeckControl)
public:
    explicit LookAtOwnedHorse(const InitArg& arg);
    ~LookAtOwnedHorse() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;

    /* 0x58 */ const float* mDistance_s{};
    /* 0x60 */ act::NPC* _60 = nullptr;
};
KSYS_CHECK_SIZE_NX150(LookAtOwnedHorse, 0x68);

}  // namespace uking::behavior
