#include "Game/AI/Action/actionDragonChemicalBall.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

DragonChemicalBall::DragonChemicalBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DragonChemicalBall::~DragonChemicalBall() = default;

bool DragonChemicalBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original copies the actor matrix to the stack before each setTransform call
void DragonChemicalBall::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        body->setTransform(actor->getMtx());
        body->setGravityFactor(*mGravity_s);
    }
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        body->setTransform(actor->getMtx());
        body->setScale(*mHitScale_s);
        sub_71007A2B64(body, nullptr);
        sub_71007A2EB0(body, actor, nullptr);
    }
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(true);
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2c, true);
}

void DragonChemicalBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void DragonChemicalBall::loadParams_() {
    getStaticParam(&mLife_s, "Life");
    getStaticParam(&mHitScale_s, "HitScale");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mHomingPower_s, "HomingPower");
    getStaticParam(&mHomingDistance_s, "HomingDistance");
    getStaticParam(&mHomingTime_s, "HomingTime");
}

void DragonChemicalBall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
