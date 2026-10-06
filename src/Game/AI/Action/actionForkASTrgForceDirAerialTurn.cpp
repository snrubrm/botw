#include "Game/AI/Action/actionForkASTrgForceDirAerialTurn.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

ForkASTrgForceDirAerialTurn::ForkASTrgForceDirAerialTurn(const InitArg& arg)
    : ForkASTrgAerialTurn(arg) {}

ForkASTrgForceDirAerialTurn::~ForkASTrgForceDirAerialTurn() = default;

bool ForkASTrgForceDirAerialTurn::init_(sead::Heap* heap) {
    return ForkASTrgAerialTurn::init_(heap);
}

void ForkASTrgForceDirAerialTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgAerialTurn::enter_(params);
}

void ForkASTrgForceDirAerialTurn::leave_() {
    ForkASTrgAerialTurn::leave_();
}

void ForkASTrgForceDirAerialTurn::loadParams_() {
    ForkASTrgAerialTurn::loadParams_();
    getStaticParam(&mDir_s, "Dir");
}

// NON_MATCHING: the original inlines ForkASTrgAerialTurn::m32 here; ours (clang 4 -O3) emits a call to it.
void ForkASTrgForceDirAerialTurn::m32(sead::Vector3f* axis, f32* angle) {
    ForkASTrgAerialTurn::m32(axis, angle);
    if (axis->y * *angle * f32(*mDir_s) < 0.0f) {
        *angle = sead::Mathf::abs(sead::Mathf::pi2() - sead::Mathf::abs(*angle));
        axis->y = f32(*mDir_s) * sead::Mathf::abs(axis->y);
    }
}

void ForkASTrgForceDirAerialTurn::calc_() {
    ForkASTrgAerialTurn::calc_();
}

}  // namespace uking::action
