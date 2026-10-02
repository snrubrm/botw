#include "Game/AI/Action/actionHoverPredictVacuumShoot.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

HoverPredictVacuumShoot::HoverPredictVacuumShoot(const InitArg& arg) : PredictVacuumShoot(arg) {}

HoverPredictVacuumShoot::~HoverPredictVacuumShoot() = default;

bool HoverPredictVacuumShoot::init_(sead::Heap* heap) {
    return PredictVacuumShoot::init_(heap);
}

void HoverPredictVacuumShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PredictVacuumShoot::enter_(params);
}

void HoverPredictVacuumShoot::leave_() {
    PredictVacuumShoot::leave_();
}

void HoverPredictVacuumShoot::loadParams_() {
    PredictVacuumShoot::loadParams_();
}

void HoverPredictVacuumShoot::calc_() {
    PredictVacuumShoot::calc_();
}

void HoverPredictVacuumShoot::m32() {
    sub_7100738428(mActor, *mPosReduceRatio_s);
}

}  // namespace uking::action
