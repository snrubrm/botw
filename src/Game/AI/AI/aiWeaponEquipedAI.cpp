#include "Game/AI/AI/aiWeaponEquipedAI.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiXlinkHandle.h"

namespace uking::ai {

WeaponEquipedAI::WeaponEquipedAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponEquipedAI::~WeaponEquipedAI() {
    sub_7100E1DC50();
}

void WeaponEquipedAI::sub_7100E1DC50() {
    if (_40.getEvent() && _40.getEvent()->getCreateId() == u32(_40.getCreateId()) &&
        !_40.getEvent()->getBitFlag().isOnBit(4)) {
        xlink::fade(_40, -1);
    }
}

void WeaponEquipedAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponEquipedAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

// 0x7100e1e024
void WeaponEquipedAI::sub_7100E1E024() {
    if (_50.getEvent() && _50.getEvent()->getCreateId() == u32(_50.getCreateId()) &&
        !_50.getEvent()->getBitFlag().isOnBit(4)) {
        xlink::fade(_50, -1);
    }
}

// 0x7100e1e104
void WeaponEquipedAI::sub_7100E1E104() {
    sead::SafeString name;
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (weapon && weapon->m233()) {
        name = "SpearAttack";
        _50 = ksys::eft::searchAndEmitELink(mActor, name.cstr());
    }
}

// 0x7100e1d7a8
void WeaponEquipedAI::sub_7100E1D7A8() {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (weapon && weapon->m213())
        return;
    if (auto* chemical = mActor->sub_71011D8A44(0)) {
        chemical->sub_7100D8EEE0();
        mActor->getRootAi()->setChemicalFlags3cMaybe(1, false);
        chemical->sub_7100D90C2C(true);
    }
}

// 0x7100e1db34
void WeaponEquipedAI::sub_7100E1DB34(ksys::phys::ContactLayer main_layer, ksys::phys::ContactLayer chemical_layer) {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (weapon && weapon->m213())
        return;
    if (auto* body = mActor->getMainBody())
        body->setContactLayerAndGroundHit(main_layer, ksys::phys::GroundHit::HitAll);
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName("Chemical")) {
            if (auto* chemical_body = set->getRigidBodies().at(0))
                chemical_body->setContactLayerAndGroundHit(chemical_layer, ksys::phys::GroundHit::HitAll);
        }
    }
}

}  // namespace uking::ai
