#include "Game/Actor/Action/actionJumpTackle.h"
#include <algorithm>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

// NON_MATCHING: store scheduling (param zeroing is sunk below the vtable store)
JumpTackle::JumpTackle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool JumpTackle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original loads TargetPos while copying the position and keeps &_78 in a register only
// around the speed clamp (load / register scheduling).
void JumpTackle::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    playAS("JumpAttack", false, 0, 0, -1.0f);
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    const sead::Vector3f* target = mParams.mTargetPos_d;
    f32 height = *mParams.mJumpHeight_s;
    const f32 height_diff = target->y - pos.y;
    if (height_diff > height * 0.5f)
        height += sead::Mathf::clampMax(height_diff - height * 0.5f, *mParams.mJumpHeightMaxOffset_s);

    sead::Vector3f dir = *target;
    dir -= pos;
    ksys::util::sub_71011EFA00(&dir, dir, getUpDir(controller->get70()));
    if (dir.normalize() < 1.0f) {
        _78.value = *mParams.mMinSpeed_s;
        _78.prev_value = *mParams.mMinSpeed_s;
    } else {
        f32 time = 0;
        f32 speed = 0;
        sead::Vector3f gravity = getGravity(mActor);
        gravity *= 1.0f / 900.0f;
        if (sub_710072CD88(height, &speed, &time, &pos, target, &gravity)) {
            _78.value = _78.prev_value = speed;
            _78.clamp(*mParams.mMinSpeed_s, *mParams.mMaxSpeed_s);
        } else {
            _78.value = *mParams.mMaxSpeed_s;
            _78.prev_value = *mParams.mMaxSpeed_s;
        }
    }
    _78.updateStats();
    controller->sub_7100F5EDD8(1.0f);
    controller->sub_7100F5E7F0(_78.value * 30.0f);
    sub_710072C1B4(controller, mActor->getMtx().getBase(2));
    controller->sub_7100F62B70(height);
    controller->sub_7100F5EF08(true);
    _90 = false;
    m32();
    setDamageCallbackTiming(mActor, 4, &_50);
}

void JumpTackle::leave_() {
    m33();
    sub_71005DA114(mActor, &_50);
}

void JumpTackle::loadParams_() {
    getStaticParam(&mParams.mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mParams.mMinSpeed_s, "MinSpeed");
    getStaticParam(&mParams.mJumpHeight_s, "JumpHeight");
    getStaticParam(&mParams.mJumpHeightMaxOffset_s, "JumpHeightMaxOffset");
    getStaticParam(&mParams.mIsFinishedAtPreLandFrame_s, "IsFinishedAtPreLandFrame");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void JumpTackle::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    _78 *= 0.978f;
    _78.updateStats();
    controller->sub_7100F5E7F0(_78.value * 30.0f);
    const sead::Vector3f axis = mActor->getMtx().getBase(2);
    sub_710072C1B4(controller, axis);
    sub_7100738660(controller, 0.75f);
    if (_90 && m34())
        setFinished();
    _90 = true;
}

bool JumpTackle::m34() const {
    return isBgGroundHit(mActor, false);
}

void JumpTackle::m33() {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkEnemyBody"))
        sub_71007A2D34(body);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(_91);
}

void JumpTackle::m32() {
    auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkEnemyBody");
    if (!body)
        return;
    body->setTransform(mActor->getMtx());
    sub_71007A2B64(body, nullptr);
    sub_71007A2EB0(body, mActor, nullptr);
    getActorAttackSensor(mActor)->activateAttackSensor(
        0x2000, 0x4001, mActor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(),
        mActor->getParam()->getRes().mGParamList->getAttack()->mImpulse.ref(), 0.0f, 0, 1, -1,
        false, 1, -1);
    if (auto* chemical = mActor->getChemicalStuff()) {
        _91 = chemical->_c >> 6 & 1;
        chemical->sub_7100D91098(true);
    }
}

bool JumpTackle::isFinished() const {
    if (ksys::act::ai::Action::isFinished())
        return true;
    if (_90 && m34())
        return true;
    if (*mParams.mIsFinishedAtPreLandFrame_s)
        return sub_71005E1064(mActor);
    return false;
}

}  // namespace uking::action
