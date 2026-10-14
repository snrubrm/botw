#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class OnAnimalSupportNrmCalcFrontRay : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OnAnimalSupportNrmCalcFrontRay, ksys::act::ai::Behavior)
public:
    explicit OnAnimalSupportNrmCalcFrontRay(const InitArg& arg);
    ~OnAnimalSupportNrmCalcFrontRay() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(OnAnimalSupportNrmCalcFrontRay, 0x28);

}  // namespace uking::behavior
