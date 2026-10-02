#pragma once

#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetDamageCallback : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetDamageCallback, ksys::act::ai::Behavior)
public:
    explicit SetDamageCallback(const InitArg& arg);
    ~SetDamageCallback() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual uking::dmg::DamageCallback* m14() = 0;

    /* 0x28 */ const int* mTiming_s{};
};

}  // namespace uking::behavior
