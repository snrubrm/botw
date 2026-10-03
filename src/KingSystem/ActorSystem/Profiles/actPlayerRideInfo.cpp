#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

Player::RideInfo::RideInfo(Actor* actor) : Unk_710244eaa0(actor) {}

Player::RideInfo::~RideInfo() {
    x_0();
}

void Player::RideInfo::init(sead::Heap* heap) {
    phys::FixedCs::Param param;
    param._19 = true;
    param._1c = 1000000.0f;
    _2d8 = phys::FixedCs::make(param, heap);
}

void Player::RideInfo::x_0() {
    if (_2d8) {
        phys::Constraint::destroy(_2d8);
        _2d8 = nullptr;
    }
}

void Player::RideInfo::m8() {
    Unk_710244eaa0::m8();
    _2e0 = mActor->findPhysicsBodyByName("Player", "Riding");
    if (_2e0 && _2d8)
        _2e0->setGravityFactor(0.0f);
    _2f0 = false;
}

}  // namespace ksys::act
