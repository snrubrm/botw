#pragma once

#include "Game/AI/Behavior/behaviorSetChemicalPower.h"

namespace uking::behavior {

class SetEnemyChemicalPower : public SetChemicalPower {
    SEAD_RTTI_OVERRIDE(SetEnemyChemicalPower, SetChemicalPower)
public:
    explicit SetEnemyChemicalPower(const InitArg& arg);
    ~SetEnemyChemicalPower() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m14(bool on) override;

};
KSYS_CHECK_SIZE_NX150(SetEnemyChemicalPower, 0x38);

}  // namespace uking::behavior
