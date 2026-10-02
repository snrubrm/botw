#include "Game/AI/AI/aiElectricBall.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

ElectricBall::ElectricBall(const InitArg& arg) : SimpleLiftable(arg) {}

bool ElectricBall::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void ElectricBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
}

void ElectricBall::leave_() {
    SimpleLiftable::leave_();
}

void ElectricBall::loadParams_() {
    getStaticParam(&mTargetVol_s, "TargetVol");
}

void ElectricBall::calc_() {
    SimpleLiftable::calc_();
    auto* actor = mActor;
    const f32 max = actor->getASList()->x_5(0, 0, &ksys::as::ASList::Unk2::sub_710116323C);
    f32 value = 0.0f;
    if (auto* chemical = actor->getChemicalStuff())
        value = max * (chemical->_1b4 / (*mTargetVol_s / chemical->_58));
    value = sead::Mathf::clamp(value, 0.0f, max);
    actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, value);
}

}  // namespace uking::ai
