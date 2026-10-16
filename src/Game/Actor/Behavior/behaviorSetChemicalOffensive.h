#pragma once

#include "Game/Actor/Behavior/behaviorSetChemicalPower.h"

namespace uking::behavior {

class SetChemicalOffensive : public SetChemicalPower {
    SEAD_RTTI_OVERRIDE(SetChemicalOffensive, SetChemicalPower)
public:
    explicit SetChemicalOffensive(const InitArg& arg);
    ~SetChemicalOffensive() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(SetChemicalOffensive, 0x38);

}  // namespace uking::behavior
