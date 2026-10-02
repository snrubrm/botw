#include "Game/AI/Action/actionLynelMove.h"
#include "KingSystem/System/VFR.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

LynelMove::LynelMove(const InitArg& arg) : AnimalMove(arg) {}

LynelMove::~LynelMove() = default;

bool LynelMove::init_(sead::Heap* heap) {
    return AnimalMove::init_(heap);
}

void LynelMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMove::enter_(params);
}

void LynelMove::leave_() {
    AnimalMove::leave_();
}

void LynelMove::loadParams_() {
    AnimalMove::loadParams_();
    getStaticParam(&mTimeForCalcCheckCliffDist_s, "TimeForCalcCheckCliffDist");
    // FIXME: CALL sub_710070F984 @ 0x710070f984
}

void LynelMove::calc_() {
    AnimalMove::calc_();
}

bool LynelMove::m34(const sead::Vector3f& pos, float x) {
    const f32 dist = *mTimeForCalcCheckCliffDist_s * (ksys::VFR::instance()->getDeltaFrame() * x);
    if (dist > 0.0f && sub_710072FEC4(mActor, pos, dist, nullptr, true, nullptr))
        return false;
    return true;
}

}  // namespace uking::action
