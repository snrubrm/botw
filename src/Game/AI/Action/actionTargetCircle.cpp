#include "Game/AI/Action/actionTargetCircle.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

TargetCircle::TargetCircle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool TargetCircle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TargetCircle::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sead::Vector3f velocity;
    ksys::util::sub_71011EFA00(&velocity, actor->getVelocity(), getUpDir(actor));
    const f32 speed = velocity.length();
    _48.value = speed;
    _48.prev_value = speed;
    _78 = actor->getAngVelocity().length();
    sub_710073FA90(&_54, actor);

    _7c = *mRotDir_d;
    if (_7c == 0)
        _7c = (sead::GlobalRandom::instance()->getU32() & 2) - 1;
    actor->getASList()->x_6(9, 0, -_7c * 90.0f);
    mFlags.set(Flag::Changeable);
}

void TargetCircle::leave_() {
    ksys::act::ai::Action::leave_();
}

void TargetCircle::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mRotDist_s, "RotDist");
    getDynamicParam(&mRotDir_d, "RotDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TargetCircle::calc_() {
    ksys::act::ai::Action::calc_();
}

float TargetCircle::m32() {
    return *mRotDist_s;
}

void TargetCircle::m33(ksys::phys::CharacterController* controller, f32 speed,
                       const sead::Vector3f& dir) {
    sub_710073770C(controller, speed, dir);
}

}  // namespace uking::action
