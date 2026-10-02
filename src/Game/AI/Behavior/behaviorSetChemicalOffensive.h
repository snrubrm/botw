#pragma once

#include "Game/AI/Behavior/behaviorSetChemicalPower.h"

namespace uking::behavior {

class SetChemicalOffensive : public SetChemicalPower {
    SEAD_RTTI_OVERRIDE(SetChemicalOffensive, SetChemicalPower)
public:
    explicit SetChemicalOffensive(const InitArg& arg);
    ~SetChemicalOffensive() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(SetChemicalOffensive, 0x38);

}  // namespace uking::behavior
