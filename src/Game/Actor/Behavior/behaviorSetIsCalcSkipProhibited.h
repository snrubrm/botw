#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetIsCalcSkipProhibited : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetIsCalcSkipProhibited, ksys::act::ai::Behavior)
public:
    explicit SetIsCalcSkipProhibited(const InitArg& arg);
    ~SetIsCalcSkipProhibited() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(SetIsCalcSkipProhibited, 0x28);

}  // namespace uking::behavior
