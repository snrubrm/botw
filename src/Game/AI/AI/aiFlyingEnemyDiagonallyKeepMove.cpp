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

// NON_MATCHING: instruction scheduling of the unrolled sin / cos products of the rotation (the
// original applies R = Rz * Ry * Rx with a different association of the products)
void FlyingEnemyDiagonallyKeepMove::m37(sead::Vector3f* out) {
    *out = sead::Vector3f::ex;
    sead::Matrix33f mtx;
    sead::Vector3f rot = sead::Vector3f::ey;
    rot *= -*mDiagAngle_s;
    mtx.makeR(rot);
    *out = mtx * *out;
}

// NON_MATCHING: as m37
void FlyingEnemyDiagonallyKeepMove::m38(sead::Vector3f* out) {
    *out = -sead::Vector3f::ex;
    sead::Matrix33f mtx;
    sead::Vector3f rot = sead::Vector3f::ey;
    rot *= *mDiagAngle_s;
    mtx.makeR(rot);
    *out = mtx * *out;
}

void FlyingEnemyDiagonallyKeepMove::loadParams_() {
    FlyingEnemySideKeepMove::loadParams_();
    getStaticParam(&mDiagAngle_s, "DiagAngle");
}

}  // namespace uking::ai
