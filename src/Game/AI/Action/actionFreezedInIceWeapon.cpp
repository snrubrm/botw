#include "Game/AI/Action/actionFreezedInIceWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

FreezedInIceWeapon::FreezedInIceWeapon(const InitArg& arg) : FreezedInIce(arg) {}

FreezedInIceWeapon::~FreezedInIceWeapon() = default;

void FreezedInIceWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    FreezedInIce::enter_(params);
}

void FreezedInIceWeapon::leave_() {
    if (auto* physics = mActor->getPhysics())
        physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
    if (auto* body = mActor->getMainBody())
        body->addToWorld();
    ksys::act::sub_7100EE544C(mActor);
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.reset(0x800);
}

void FreezedInIceWeapon::loadParams_() {
    FreezedInIce::loadParams_();
}

}  // namespace uking::action
