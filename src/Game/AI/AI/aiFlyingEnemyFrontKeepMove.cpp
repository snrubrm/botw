#include "Game/AI/AI/aiFlyingEnemyFrontKeepMove.h"

namespace uking::ai {

FlyingEnemyFrontKeepMove::FlyingEnemyFrontKeepMove(const InitArg& arg) : FlyingEnemyKeepMove(arg) {}

FlyingEnemyFrontKeepMove::~FlyingEnemyFrontKeepMove() = default;

bool FlyingEnemyFrontKeepMove::init_(sead::Heap* heap) {
    return FlyingEnemyKeepMove::init_(heap);
}

void FlyingEnemyFrontKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemyKeepMove::enter_(params);
}

void FlyingEnemyFrontKeepMove::calc_() {
    FlyingEnemyKeepMove::calc_();
}

void FlyingEnemyFrontKeepMove::leave_() {
    FlyingEnemyKeepMove::leave_();
}

void FlyingEnemyFrontKeepMove::loadParams_() {
    FlyingEnemyKeepMove::loadParams_();
}

void FlyingEnemyFrontKeepMove::m34(sead::Vector3f* out) {
    *out = sead::Vector3f::ez;
}

}  // namespace uking::ai
