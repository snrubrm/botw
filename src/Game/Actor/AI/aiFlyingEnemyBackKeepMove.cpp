#include "Game/Actor/AI/aiFlyingEnemyBackKeepMove.h"

namespace uking::ai {

FlyingEnemyBackKeepMove::FlyingEnemyBackKeepMove(const InitArg& arg) : FlyingEnemyDistanceKeepMove(arg) {}

FlyingEnemyBackKeepMove::~FlyingEnemyBackKeepMove() = default;

bool FlyingEnemyBackKeepMove::init_(sead::Heap* heap) {
    return FlyingEnemyDistanceKeepMove::init_(heap);
}

void FlyingEnemyBackKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemyDistanceKeepMove::enter_(params);
}

void FlyingEnemyBackKeepMove::calc_() {
    FlyingEnemyDistanceKeepMove::calc_();
}

void FlyingEnemyBackKeepMove::leave_() {
    FlyingEnemyDistanceKeepMove::leave_();
}

void FlyingEnemyBackKeepMove::loadParams_() {
    FlyingEnemyDistanceKeepMove::loadParams_();
}

void FlyingEnemyBackKeepMove::m34(sead::Vector3f* out) {
    *out = -sead::Vector3f::ez;
}

}  // namespace uking::ai
