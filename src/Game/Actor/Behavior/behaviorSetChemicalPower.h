#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetChemicalPower : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetChemicalPower, ksys::act::ai::Behavior)
public:
    explicit SetChemicalPower(const InitArg& arg);
    ~SetChemicalPower() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual void m14(bool on) {}

    /* 0x28 */ const bool* mIsSetOn_s{};
    /* 0x30 */ const bool* mIsOnOffensive_s{};
};

}  // namespace uking::behavior
