#include "Game/AI/AI/aiOnCliffViewWait.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

OnCliffViewWait::OnCliffViewWait(const InitArg& arg) : ViewWait(arg) {}

OnCliffViewWait::~OnCliffViewWait() = default;

bool OnCliffViewWait::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void OnCliffViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void OnCliffViewWait::calc_() {
    ViewWait::calc_();
}

void OnCliffViewWait::leave_() {
    ViewWait::leave_();
}

void OnCliffViewWait::loadParams_() {
    ViewWait::loadParams_();
    getMapUnitParam(&mOnCliffTurn_m, "OnCliffTurn");
}

// NON_MATCHING: register allocation only (the negated components land in s10 / s8 instead of s8 / s10
// and the first length add has its operands swapped); instruction-for-instruction otherwise
bool OnCliffViewWait::m38() {
    if (!*mOnCliffTurn_m)
        return true;

    auto* actor = mActor;
    sead::Vector3f dir;
    actor->getMtx().getTranslation(dir);
    dir -= *mTargetPos_d;
    dir.negate();
    dir.normalize();

    sead::Vector3f up;
    actor->getMtx().getBase(up, 1);
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.normalize();

    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    return front.dot(dir) >= std::cos(*mTurnStartAngle_s);
}

}  // namespace uking::ai
