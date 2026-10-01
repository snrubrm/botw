#include "Game/AI/Action/actionAtkTackleMove.h"

namespace uking::action {

AtkTackleMove::AtkTackleMove(const InitArg& arg) : TackleMove(arg) {}

bool AtkTackleMove::init_(sead::Heap* heap) {
    return TackleMove::init_(heap);
}

void AtkTackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    TackleMove::enter_(params);
}

void AtkTackleMove::leave_() {
    TackleMove::leave_();
}

void AtkTackleMove::loadParams_() {
    TackleMove::loadParams_();
    getStaticParam(&mAtkSensorName_s, "AtkSensorName");
}

void AtkTackleMove::calc_() {
    TackleMove::calc_();
}

}  // namespace uking::action
