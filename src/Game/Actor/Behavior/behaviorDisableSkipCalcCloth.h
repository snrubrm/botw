#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class DisableSkipCalcCloth : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(DisableSkipCalcCloth, ksys::act::ai::Behavior)
public:
    explicit DisableSkipCalcCloth(const InitArg& arg);
    ~DisableSkipCalcCloth() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(DisableSkipCalcCloth, 0x28);

}  // namespace uking::behavior
