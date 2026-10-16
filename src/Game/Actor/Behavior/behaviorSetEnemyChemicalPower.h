#pragma once

#include "Game/Actor/Behavior/behaviorSetChemicalPower.h"

namespace uking::behavior {

class SetEnemyChemicalPower : public SetChemicalPower {
    SEAD_RTTI_OVERRIDE(SetEnemyChemicalPower, SetChemicalPower)
public:
    explicit SetEnemyChemicalPower(const InitArg& arg);
    ~SetEnemyChemicalPower() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m14(bool on) override;

};
KSYS_CHECK_SIZE_NX150(SetEnemyChemicalPower, 0x38);

}  // namespace uking::behavior
