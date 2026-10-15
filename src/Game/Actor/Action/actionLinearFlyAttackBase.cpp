#include "Game/Actor/Action/actionLinearFlyAttackBase.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
LinearFlyAttackBase::LinearFlyAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LinearFlyAttackBase::~LinearFlyAttackBase() = default;

bool LinearFlyAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: target direction normalization and attack setup scheduling.
void LinearFlyAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller)
        return;
    controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    sub_710073FA90(&_78, actor);
    _a8 = actor->getMtx().getTranslation();
    sead::Vector3f direction = *mParams.mTargetPos_d;
    direction.y += *mParams.mTargetHeightOffset_s;
    direction -= _a8;
    _b4 = direction.normalize();
    _b8 = direction;
    _b4 += *mParams.mThroughDist_s;
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    _c4.value = velocity.length() / 30.0f;
    _c4.prev_value = _c4.value;
    sub_7100737710(controller, direction * _c4.value);
    actor = mActor;
    auto* sensor = getActorAttackSensor(actor);
    const s32 kind = m32();
    const s32 power = static_cast<ksys::act::PlayerOrEnemy*>(actor)->getEnemyAtkPower();
    const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
    sensor->activateAttackSensor(kind, 0x4001, std::max(power, 1), attack->mImpulse.ref(),
                                0.0f, 0, 1, -1, false, 1, -1);
    sub_71007A2C30(actor, "AtkBody", &actor->getMtx());
    auto* chemical = mActor->getChemicalStuff();
    _d0 = chemical && (chemical->_c & 0x40) != 0;
    if (auto* chemicals = mActor->getChemicalContainer())
        chemicals->sub_7100E39614(true);
    if (auto* chemical2 = mActor->getChemicalStuff())
        chemical2->_c |= 0x20;
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
    setDamageCallbackTiming(mActor, 4, &_50);
    _9c.reset(static_cast<f32>(*mParams.mTime_s));
}

void LinearFlyAttackBase::leave_() {
    if (auto* chemicals = mActor->getChemicalContainer())
        chemicals->sub_7100E39614(_d0);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->_c &= ~0x20;
    sub_71007A2D7C(mActor, "AtkBody");
    auto* actor = mActor;
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F60604();
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FBADDC();
    sub_71005DA114(mActor, &_50);
}

void LinearFlyAttackBase::loadParams_() {
    getStaticParam(&mParams.mTime_s, "Time");
    getStaticParam(&mParams.mAttackSpeed_s, "AttackSpeed");
    getStaticParam(&mParams.mAttackSlowDownRatio_s, "AttackSlowDownRatio");
    getStaticParam(&mParams.mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mParams.mThroughDist_s, "ThroughDist");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

// NON_MATCHING: forward-vector normalization and movement scheduling.
void LinearFlyAttackBase::calc_() {
    _9c.update();
    if (_9c.value <= sead::Mathf::epsilon()) {
        setFinished();
        return;
    }
    auto* actor = mActor;
    if ((_a8 - actor->getMtx().getTranslation()).length() >= _b4) {
        setFinished();
        return;
    }
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    sub_71007377D4(controller, *mParams.mAttackSlowDownRatio_s);
    auto* attack_actor = mActor;
    if (auto* body = attack_actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        if (body->isAddedToWorld())
            body->changePositionAndRotation(attack_actor->getMtx(), sead::Mathf::epsilon());
    }
    _c4.lerp(*mParams.mAttackSpeed_s, 0.2f);
    _c4.updateStats();
    sead::Vector3f forward = actor->getMtx().getBase(2);
    forward.normalize();
    sub_71005E2540(controller, actor, forward * _c4.value, 0.5f);
    sead::Vector3f up;
    m33(&up);
    sub_7100740884(&_78, up, m34());
    sub_710074018C(&_78, _b8, 0.3f, sead::Mathf::pi2(), 0.0f);
    sub_7100740E04(_78, controller);
}

int LinearFlyAttackBase::m32() {
    return 8192;
}

f32 LinearFlyAttackBase::m34() {
    return 30.0f;
}

void LinearFlyAttackBase::m33(sead::Vector3f* dir) {
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, mActor);
    sead::Vector3f up = -gravity;
    if (up.normalize() < sead::Mathf::epsilon())
        up.set(sead::Vector3f::ey);
    dir->set(up);
}

}  // namespace uking::action
