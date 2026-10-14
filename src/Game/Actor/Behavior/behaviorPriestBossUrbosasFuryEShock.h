#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class PriestBossUrbosasFuryEShock : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PriestBossUrbosasFuryEShock, ksys::act::ai::Behavior)
public:
    explicit PriestBossUrbosasFuryEShock(const InitArg& arg);
    ~PriestBossUrbosasFuryEShock() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const bool* mElectricShock_s{};
    /* 0x30 */ bool* mPriestBossUrbosasFuryEShock_a{};
};
KSYS_CHECK_SIZE_NX150(PriestBossUrbosasFuryEShock, 0x38);

}  // namespace uking::behavior
