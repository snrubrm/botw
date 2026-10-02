#include "Game/AI/AI/aiAmbushableWeaponShoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::ai {

AmbushableWeaponShoot::AmbushableWeaponShoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AmbushableWeaponShoot::~AmbushableWeaponShoot() = default;

bool AmbushableWeaponShoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AmbushableWeaponShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("投擲", &pack);
}

void AmbushableWeaponShoot::leave_() {
    if (auto* body = mActor->getRigidBodyByName(sub_71007A24D0()->cstr()))
        body->setScale(mActor->getScale().x);
}

void AmbushableWeaponShoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool AmbushableWeaponShoot::isFinished() const {
    return getCurrentChild()->isFinished() || ActionBase::isFinished();
}

bool AmbushableWeaponShoot::isFailed() const {
    return getCurrentChild()->isFailed() || ActionBase::isFailed();
}

}  // namespace uking::ai
