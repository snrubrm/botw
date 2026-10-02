#include "Game/AI/Action/actionChemicalAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ChemicalAttack::ChemicalAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChemicalAttack::~ChemicalAttack() = default;

bool ChemicalAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChemicalAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _7c = actor->getScale().x;
    if (*mScaleTime_m > 1.0f) {
        _78 = 1.0f / *mScaleTime_m;
        actor->setScale(sead::Vector3f::ones * _78);
    } else {
        _78 = 1.0f;
    }

    if (auto* sensor = getActorAttackSensor(actor)) {
        sensor->activateAttackSensor(m35(), m36(), m37(), 0, 0.0f, 0, 1, m39(), false,
                                     *mAttackMinPower_s, m38());
    }

    if (auto* body = actor->getMainBody())
        body->setTransform(actor->getMtx(), ksys::phys::PropagateToLinkedMotions{true});

    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        body->setTransform(actor->getMtx(), ksys::phys::PropagateToLinkedMotions{true});
        sub_71007A2B64(body, nullptr);
        sub_71007A2EB0(body, actor, nullptr);
    }

    if (!mRigidBodyName_m.isEmpty()) {
        if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(),
                                                       mRigidBodyName_m.cstr())) {
            body->setTransform(actor->getMtx(), ksys::phys::PropagateToLinkedMotions{true});
            sub_71007A2B64(body, nullptr);
            sub_71007A2EB0(body, actor, nullptr);
        }
    }

    _6c = actor->getVelocity();
    actor->getMtx().getTranslation(_60);

    if (auto* chemical = mActor->getChemicalStuff()) {
        chemical->_c |= 0x20;
        if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor)) {
            if (ksys::act::isPlayerProfile(&bullet->_ba0)) {
                chemical->_c |= 0x8000;
                chemical->_a0 |= 4;
            }
        }
    }
}

void ChemicalAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChemicalAttack::loadParams_() {
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mAttackMinPower_s, "AttackMinPower");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mRange_m, "Range");
    getMapUnitParam(&mRigidBodyName_m, "RigidBodyName");
}

void ChemicalAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

void ChemicalAttack::m32() {
    ksys::act::sub_7100EE5980(mActor, _6c);
}

float ChemicalAttack::m34() {
    return *mRange_m;
}

int ChemicalAttack::m35() {
    return 8192;
}

int ChemicalAttack::m37() {
    return *mAttackPower_m;
}

int ChemicalAttack::m38() {
    return *mAttackPowerForPlayer_m;
}

int ChemicalAttack::m36() {
    switch (*mAttackIntensity_s) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 4;
    default:
        return 0;
    }
}

int ChemicalAttack::m39() {
    return -1;
}

bool ChemicalAttack::m33() {
    auto* actor = mActor;
    if (isLandedMaybe(actor, false))
        return true;
    return (actor->getMtx().getTranslation() - _60).length() > m34();
}

}  // namespace uking::action
