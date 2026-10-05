#include "Game/AI/Action/actionThrownSpear.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ThrownSpear::ThrownSpear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ThrownSpear::~ThrownSpear() = default;

void ThrownSpear::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ThrownSpear::leave_() {
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        if (auto* body = static_cast<ksys::phys::RigidBody*>(weapon->m221()))
            body->setAngularVelocity(sead::Vector3f::zero);
    }
}

void ThrownSpear::loadParams_() {
    getStaticParam(&mRotSpeedZ_s, "RotSpeedZ");
}

void ThrownSpear::calc_() {
    sub_7100297FC0();
}

}  // namespace uking::action
