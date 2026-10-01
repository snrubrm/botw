#include "Game/AI/Action/actionWillBallParabolaAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

WillBallParabolaAttack::WillBallParabolaAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WillBallParabolaAttack::~WillBallParabolaAttack() = default;

bool WillBallParabolaAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WillBallParabolaAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WillBallParabolaAttack::leave_() {
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(_48);
}

void WillBallParabolaAttack::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mMaxHeight_s, "MaxHeight");
    getStaticParam(&mMinMoveXZ_s, "MinMoveXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mGravityScale_s, "GravityScale");
}

void WillBallParabolaAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
