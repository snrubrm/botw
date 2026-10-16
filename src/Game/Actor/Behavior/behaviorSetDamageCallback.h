#pragma once

#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetDamageCallback : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetDamageCallback, ksys::act::ai::Behavior)
public:
    explicit SetDamageCallback(const InitArg& arg);
    ~SetDamageCallback() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    virtual uking::act::DamageCallback* m14() = 0;

    /* 0x28 */ const int* mTiming_s{};
};

}  // namespace uking::behavior
