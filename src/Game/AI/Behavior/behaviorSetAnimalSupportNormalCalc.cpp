#include "Game/AI/Behavior/behaviorSetAnimalSupportNormalCalc.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

SetAnimalSupportNormalCalc::SetAnimalSupportNormalCalc(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetAnimalSupportNormalCalc::~SetAnimalSupportNormalCalc() = default;

bool SetAnimalSupportNormalCalc::m6(sead::Heap* heap) {
    return true;
}

void SetAnimalSupportNormalCalc::m7() {}

// NON_MATCHING: aggregate initialization omits overwritten defaults and copies vectors together.
void SetAnimalSupportNormalCalc::m8() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (auto* support = enemy->_1148._50) {
            act::Unk_7102357908::Unk50::CalcArg arg{
                *mPosteriorLimbOffset_s, *mRayCastLength_s,
                *mPriorLimbOffset_s, *mPriorRayCastLength_s, true};
            support->sub_71006F0800(arg);
            support->_28 |= 1;
        }
    }
}

void SetAnimalSupportNormalCalc::m9() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        if (auto* support = enemy->_1148._50)
            support->_28 &= ~1;
    }
}

void SetAnimalSupportNormalCalc::loadParams() {
    getStaticParam(&mRayCastLength_s, "RayCastLength");
    getStaticParam(&mPriorRayCastLength_s, "PriorRayCastLength");
    getStaticParam(&mPosteriorLimbOffset_s, "PosteriorLimbOffset");
    getStaticParam(&mPriorLimbOffset_s, "PriorLimbOffset");
}

}  // namespace uking::behavior
