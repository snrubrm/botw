#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class OnAnimalSupportNrmCalcFrontRay : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OnAnimalSupportNrmCalcFrontRay, ksys::act::ai::Behavior)
public:
    explicit OnAnimalSupportNrmCalcFrontRay(const InitArg& arg);
    ~OnAnimalSupportNrmCalcFrontRay() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(OnAnimalSupportNrmCalcFrontRay, 0x28);

}  // namespace uking::behavior
