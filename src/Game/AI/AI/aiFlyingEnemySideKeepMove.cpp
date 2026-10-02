#include "Game/AI/AI/aiFlyingEnemySideKeepMove.h"

namespace uking::ai {

FlyingEnemySideKeepMove::FlyingEnemySideKeepMove(const InitArg& arg) : FlyingEnemyKeepMove(arg) {}

FlyingEnemySideKeepMove::~FlyingEnemySideKeepMove() = default;

bool FlyingEnemySideKeepMove::init_(sead::Heap* heap) {
    return FlyingEnemyKeepMove::init_(heap);
}

void FlyingEnemySideKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemyKeepMove::enter_(params);
}

void FlyingEnemySideKeepMove::leave_() {
    FlyingEnemyKeepMove::leave_();
}

void FlyingEnemySideKeepMove::loadParams_() {
    FlyingEnemyKeepMove::loadParams_();
    getStaticParam(&mSideDirType_s, "SideDirType");
}

void FlyingEnemySideKeepMove::m34(sead::Vector3f* out) {
    *out = _88;
}

void FlyingEnemySideKeepMove::m37(sead::Vector3f* out) {
    *out = sead::Vector3f::ex;
}

void FlyingEnemySideKeepMove::m38(sead::Vector3f* out) {
    *out = -sead::Vector3f::ex;
}

}  // namespace uking::ai
