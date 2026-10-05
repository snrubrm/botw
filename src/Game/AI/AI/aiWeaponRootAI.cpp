#include "Game/AI/AI/aiWeaponRootAI.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

WeaponRootAI::WeaponRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg), _c8() {}

WeaponRootAI::~WeaponRootAI() = default;

bool WeaponRootAI::init_(sead::Heap* heap) {
    if (auto* body = mActor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(), "Body"))
        _b0 = body->getMaxAngularVelocity();
    return true;
}

void WeaponRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponRootAI::calc_() {
    if (_c4) {
        if (auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor)) {
            weapon->masterSwordReturnToForest();
            return;
        }
    }
    if (auto* awareness = mActor->get548())
        awareness->m8()->m9(1, 0.0f);
    sub_7100E1FC5C();
    sub_7100E20C2C();
}

void WeaponRootAI::leave_() {
    _c8.fadeXLink();
}

void WeaponRootAI::loadParams_() {
    getStaticParam(&mBlinkFrame_s, "BlinkFrame");
    getStaticParam(&mFallOutSpeed_s, "FallOutSpeed");
    getStaticParam(&mLandNoiseLevel_s, "LandNoiseLevel");
    getMapUnitParam(&mIsFixedPlace_m, "IsFixedPlace");
    getMapUnitParam(&mIsEmitLandNoise_m, "IsEmitLandNoise");
}

void WeaponRootAI::m36() {}

void WeaponRootAI::m37() {}

void WeaponRootAI::m38() {}

void WeaponRootAI::m39() {}

void WeaponRootAI::m40() {}

void WeaponRootAI::m45() {
    ksys::act::enableAllAttClients(mActor);
    ksys::act::disableAttClient(mActor, "CatchBoomerang");
}

void WeaponRootAI::m43() {
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(true);
}

void WeaponRootAI::m44() {
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(false);
}

void WeaponRootAI::sub_7100E21228() {
    _a8 = false;
    _aa = false;
    _ab = false;
    ksys::act::disableAllAttClients(mActor);
    m35();
    if (auto* body = mActor->getMainBody()) {
        body->disableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
        body->disableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
        body->disableContactLayer(ksys::phys::ContactLayer::EntityTree);
    }
    _c8.fadeXLink();
    m36();
    if (mActor) {
        if (auto* as_list = mActor->getASList()) {
            if (as_list->sub_710115AA68("ChangeColor")) {
                as_list->startAnimationMaybe(-1.0f, -1.0f, "ChangeColor", 0, 1, true);
                as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_7101163298, 0);
                as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_7101163100, 0);
            }
        }
    }
    changeChild("装備");
}

// NON_MATCHING: only the last lookup differs: the original builds the first "Body" SafeString before the
// physics null check (frame 0x50 vs 0x40); every other instruction matches
void WeaponRootAI::m34() {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (weapon && weapon->m213())
        return;
    if (!_39)
        return;
    _39 = false;
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName("Body")) {
            if (auto* body = set->findBodyByHavokName("Body")) {
                physics->sub_7100FBAF18(body);
                if (!body->isAddedToWorld()) {
                    body->addToWorld();
                    physics->sub_7100FC012C(nullptr);
                }
                body->setMaxAngularVelocity(_b0);
                body->resetFlag1000000();
            }
        }
        if (auto* set = physics->findBodyByName("Chemical")) {
            if (auto* body = set->getRigidBodies()[0]) {
                physics->sub_7100FBAF18(body);
                if (!body->isAddedToWorld())
                    body->addToWorld();
            }
        }
    }
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName("Body")) {
            if (auto* body = set->findBodyByHavokName("Body"))
                body->changeMotionType(ksys::phys::MotionType::Dynamic);
        }
    }
}

// NON_MATCHING: same as m34, the original builds the first "Body" SafeString before the physics null check
void WeaponRootAI::m35() {
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (weapon && weapon->m213())
        return;
    if (_39)
        return;
    _39 = true;
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName("Body")) {
            if (auto* body = set->findBodyByHavokName("Body")) {
                body->setContactLayerAndGroundHit(ksys::phys::ContactLayer::EntityHitOnlyWater,
                                                  ksys::phys::GroundHit::HitAll);
                if (!body->isAddedToWorld() || body->isRemovingBodyFromWorld()) {
                    body->addToWorld();
                    physics->sub_7100FC01B0();
                }
                body->setMaxAngularVelocity(6283.1855f);
                body->setFlag1000000();
            }
        }
        if (auto* set = physics->findBodyByName("Chemical")) {
            if (auto* body = set->getRigidBodies()[0]) {
                if (!body->isAddedToWorld())
                    body->addToWorld();
            }
        }
    }
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName("Body")) {
            if (auto* body = set->findBodyByHavokName("Body"))
                body->changeMotionType(ksys::phys::MotionType::Keyframed);
        }
    }
}

bool WeaponRootAI::m41() {
    if (auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor))
        return weapon->m183();
    return false;
}

bool WeaponRootAI::m42() {
    if (auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor))
        return !weapon->m183();
    return true;
}

}  // namespace uking::ai
