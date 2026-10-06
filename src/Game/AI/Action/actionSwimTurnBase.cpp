#include "Game/AI/Action/actionSwimTurnBase.h"
#include <cmath>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

SwimTurnBase::SwimTurnBase(const InitArg& arg) : SwimRotateBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SwimTurnBase::~SwimTurnBase() {
    ;
}

bool SwimTurnBase::init_(sead::Heap* heap) {
    return SwimRotateBase::init_(heap);
}

void SwimTurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimRotateBase::enter_(params);
}

void SwimTurnBase::leave_() {
    SwimRotateBase::leave_();
}

void SwimTurnBase::loadParams_() {
    SwimRotateBase::loadParams_();
    getStaticParam(&mFinRotate_s, "FinRotate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: natural vector temporaries and register scheduling differ.
void SwimTurnBase::calc_() {
    SwimRotateBase::calc_();
    auto* actor = mActor;
    const sead::Vector3f up = getUpDir(getGravity(actor) * (1.0f / 900.0f));
    const sead::Vector3f position = actor->getMtx().getTranslation();
    sead::Vector3f target;
    m32(&target);
    target -= position;
    ksys::util::sub_71011EFA00(&target, target, up);
    target.normalize();
    sead::Vector3f facing;
    actor->getMtx().getBase(facing, 0);
    ksys::util::sub_71011EFA00(&facing, facing, up);
    facing.normalize();
    if (!(facing.dot(target) < std::cos(*mFinRotate_s)))
        setFinished();
}

void SwimTurnBase::m32(sead::Vector3f* out) {
    if (out)
        out->set(*mTargetPos_d);
}

}  // namespace uking::action
