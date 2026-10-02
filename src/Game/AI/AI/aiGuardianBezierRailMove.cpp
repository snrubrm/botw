#include "Game/AI/AI/aiGuardianBezierRailMove.h"
#include "Game/Actor/actGuardian.h"

namespace uking::ai {

GuardianBezierRailMove::GuardianBezierRailMove(const InitArg& arg) : RailMoveWithClose(arg) {}

GuardianBezierRailMove::~GuardianBezierRailMove() = default;

bool GuardianBezierRailMove::init_(sead::Heap* heap) {
    return RailMoveWithClose::init_(heap);
}

void GuardianBezierRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveWithClose::enter_(params);
    if (auto* guardian = sead::DynamicCast<act::Guardian>(mActor))
        guardian->_14c8.set(0x1000);
}

void GuardianBezierRailMove::calc_() {
    RailMoveWithClose::calc_();
}

void GuardianBezierRailMove::leave_() {
    RailMoveWithClose::leave_();
    if (auto* guardian = sead::DynamicCast<act::Guardian>(mActor))
        guardian->_14c8.reset(0x1000);
}

void GuardianBezierRailMove::loadParams_() {
    RailMoveWithClose::loadParams_();
}

}  // namespace uking::ai
