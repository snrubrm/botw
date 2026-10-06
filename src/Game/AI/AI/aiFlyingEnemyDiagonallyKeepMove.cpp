#include "Game/AI/AI/aiFlyingEnemyDiagonallyKeepMove.h"
#include <math/seadMatrix.h>

namespace uking::ai {

FlyingEnemyDiagonallyKeepMove::FlyingEnemyDiagonallyKeepMove(const InitArg& arg)
    : FlyingEnemySideKeepMove(arg) {}

FlyingEnemyDiagonallyKeepMove::~FlyingEnemyDiagonallyKeepMove() = default;

void FlyingEnemyDiagonallyKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemySideKeepMove::enter_(params);
}

void FlyingEnemyDiagonallyKeepMove::calc_() {
    FlyingEnemySideKeepMove::calc_();
}

void FlyingEnemyDiagonallyKeepMove::leave_() {
    FlyingEnemySideKeepMove::leave_();
}

void FlyingEnemyDiagonallyKeepMove::m37(sead::Vector3f* out) {
    *out = sead::Vector3f::ex;
    sead::Matrix34f mtx;
    sead::Vector3f rot = sead::Vector3f::ey;
    rot *= -*mDiagAngle_s;
    mtx.makeR(rot);
    out->rotate(mtx);
}

void FlyingEnemyDiagonallyKeepMove::m38(sead::Vector3f* out) {
    *out = -sead::Vector3f::ex;
    sead::Matrix34f mtx;
    sead::Vector3f rot = sead::Vector3f::ey;
    rot *= *mDiagAngle_s;
    mtx.makeR(rot);
    out->rotate(mtx);
}

void FlyingEnemyDiagonallyKeepMove::loadParams_() {
    FlyingEnemySideKeepMove::loadParams_();
    getStaticParam(&mDiagAngle_s, "DiagAngle");
}

}  // namespace uking::ai
