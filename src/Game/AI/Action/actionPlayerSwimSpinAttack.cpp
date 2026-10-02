#include "Game/AI/Action/actionPlayerSwimSpinAttack.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSwimSpinAttack::PlayerSwimSpinAttack(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimSpinAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwimSpinAttack::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
        if (auto* body = set->findBodyByHavokName("AtkPlayerBody"))
            body->removeFromWorld();
    }
}

void PlayerSwimSpinAttack::loadParams_() {
    getStaticParam(&mEnergyDash_s, "EnergyDash");
}

void PlayerSwimSpinAttack::calc_() {
    PlayerAction::calc_();
}

bool PlayerSwimSpinAttack::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
