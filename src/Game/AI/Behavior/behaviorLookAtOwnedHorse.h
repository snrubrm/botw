#pragma once

#include "Game/AI/Behavior/behaviorInterestNeckControl.h"
#include "Game/Actor/actNPC.h"

namespace uking::behavior {

class LookAtOwnedHorse : public InterestNeckControl {
    SEAD_RTTI_OVERRIDE(LookAtOwnedHorse, InterestNeckControl)
public:
    explicit LookAtOwnedHorse(const InitArg& arg);
    ~LookAtOwnedHorse() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;  // not decompiled yet (0x710062acd0)

    /* 0x58 */ const float* mDistance_s{};
    /* 0x60 */ void* _60 = nullptr;
};
KSYS_CHECK_SIZE_NX150(LookAtOwnedHorse, 0x68);

}  // namespace uking::behavior
