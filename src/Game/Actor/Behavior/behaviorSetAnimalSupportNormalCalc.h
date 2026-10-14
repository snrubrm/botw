#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetAnimalSupportNormalCalc : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetAnimalSupportNormalCalc, ksys::act::ai::Behavior)
public:
    explicit SetAnimalSupportNormalCalc(const InitArg& arg);
    ~SetAnimalSupportNormalCalc() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mRayCastLength_s{};
    /* 0x30 */ const float* mPriorRayCastLength_s{};
    /* 0x38 */ const sead::Vector3f* mPosteriorLimbOffset_s{};
    /* 0x40 */ const sead::Vector3f* mPriorLimbOffset_s{};
};
KSYS_CHECK_SIZE_NX150(SetAnimalSupportNormalCalc, 0x48);

}  // namespace uking::behavior
