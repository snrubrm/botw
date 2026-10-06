#include <random/seadGlobalRandom.h>
#include "Game/AI/Action/actionSlippedCircleWalkBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SlippedCircleWalkBase::SlippedCircleWalkBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SlippedCircleWalkBase::~SlippedCircleWalkBase() = default;

bool SlippedCircleWalkBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the random sign (bit 1 of getU32() -> +1 / -1 in s8) is lowered through shifts by 24
// in the original; here through and/add/sxtb.
void SlippedCircleWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sub_710073FA90(&_50, actor);
    _78 = actor->getAngVelocity().length();
    s8 dir = *mRotDir_d;
    _74 = dir;
    if (dir == 0) {
        dir = sead::GlobalRandom::instance()->getU32() & 2 ? 1 : -1;
        _74 = dir;
    }
    actor->getASList()->x_6(9, 0, f32(dir) * 90.0f);
    mFlags.set(Flag::Changeable);
}

void SlippedCircleWalkBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SlippedCircleWalkBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mRotDist_s, "RotDist");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getDynamicParam(&mRotDir_d, "RotDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SlippedCircleWalkBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
