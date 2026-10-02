#include "Game/AI/Action/actionGiantPunchWithAddEntitySensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GiantPunchWithAddEntitySensor::GiantPunchWithAddEntitySensor(const InitArg& arg)
    : GiantPunchAttack(arg) {}

GiantPunchWithAddEntitySensor::~GiantPunchWithAddEntitySensor() = default;

bool GiantPunchWithAddEntitySensor::init_(sead::Heap* heap) {
    return GiantPunchAttack::init_(heap);
}

void GiantPunchWithAddEntitySensor::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantPunchAttack::enter_(params);
}

void GiantPunchWithAddEntitySensor::leave_() {
    if (auto* body = mActor->findPhysicsBodyByName(ksys::act::getStr_EntitySensor().cstr(),
                                                   mCoBodyName_s.cstr())) {
        body->removeFromWorld();
    }
    GiantPunchAttack::leave_();
}

void GiantPunchWithAddEntitySensor::loadParams_() {
    GiantPunchAttack::loadParams_();
}

void GiantPunchWithAddEntitySensor::calc_() {
    GiantPunchAttack::calc_();
}

}  // namespace uking::action
