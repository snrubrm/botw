#include "Game/AI/AI/aiEnemySyncAttack.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include <random/seadGlobalRandom.h>

namespace uking::ai {

EnemySyncAttack::EnemySyncAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
EnemySyncAttack::~EnemySyncAttack() {
    ;
}

// NON_MATCHING: register allocation only (x8 / x9 and w8 / w9 swapped in the last add)
void EnemySyncAttack::sub_71003BF444() {
    auto* actor = mActor;
    if (!actor || !actor->getModel())
        return;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkEnemyBody");
    if (!body)
        return;
    if (!actor->getModel()->searchBone(mAtNodeName_s).isValid())
        return;

    sead::Matrix34f mtx;
    bool found = false;
    if (auto* actor2 = mActor) {
        if (auto* model = actor2->getModel()) {
            const auto key = model->searchBone(mAtNodeName_s);
            if (key.isValid()) {
                actor2->getModel()
                    ->getUnits()
                    .unsafeAt(key.model_unit_index)
                    ->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
                found = true;
            }
        }
    }
    if (!found)
        mtx = sead::Matrix34f::zero;
    body->setTransform(mtx);
    sub_71007A2B64(body, nullptr);
    sub_71007A3258(body, nullptr);
    getActorAttackSensor(mActor)->activateAttackSensor(
        0x2000, 0x4000, actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(),
        actor->getParam()->getRes().mGParamList->getAttack()->mImpulse.ref(), 0.0f, 0, 1, -1,
        false, 1, -1);
}

void EnemySyncAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _c8 = false;
    sub_71003BF444();
    changeChild("行動", params);
    const s32 interval = *mAttackInterval_s;
    const f32 interval_rand = *mAttackIntervalRand_s;
    const f32 r = sead::GlobalRandom::instance()->getF32();
    const s32 time = s32(f32(interval) + interval_rand * r * -0.5f) + *mAttackIntervalRand_s;
    _c9 = false;
    _cc = ksys::Timer(f32(time), f32(time));
}

void EnemySyncAttack::leave_() {
    auto* actor = mActor;
    if (actor && actor->getModel()) {
        actor->getASList()->sub_710115B01C(*mAttackASSlot_s, 0, true);
        actor->getASList()->sub_710115C11C();
    }
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkEnemyBody"))
        sub_71007A2D34(body);
}

void EnemySyncAttack::loadParams_() {
    getStaticParam(&mNormalASSlot_s, "NormalASSlot");
    getStaticParam(&mAttackASSlot_s, "AttackASSlot");
    getStaticParam(&mJustAvoidCheckLength_s, "JustAvoidCheckLength");
    getStaticParam(&mJustAvoidCheckAngle_s, "JustAvoidCheckAngle");
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mAttackNodeName_s, "AttackNodeName");
    getStaticParam(&mAttackNodeNameWait_s, "AttackNodeNameWait");
    getStaticParam(&mAttackASName_s, "AttackASName");
    getStaticParam(&mAtNodeName_s, "AtNodeName");
    getStaticParam(&mAttackDistMin_s, "AttackDistMin");
    getStaticParam(&mAttackDistMax_s, "AttackDistMax");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mAttackIntervalRand_s, "AttackIntervalRand");
}

bool EnemySyncAttack::isChangeable() const {
    if (_c8)
        return false;
    return getCurrentChild()->isChangeable();
}

bool EnemySyncAttack::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("行動") && getCurrentChild()->isFinished()) {
        auto* as_list = mActor->getASList();
        return as_list && as_list->x_4(*mAttackASSlot_s, 0);
    }
    return false;
}

bool EnemySyncAttack::isFailed() const {
    if (ActionBase::isFailed())
        return true;
    if (isCurrentChild("行動") && getCurrentChild()->isFailed()) {
        auto* as_list = mActor->getASList();
        return as_list && as_list->x_4(*mAttackASSlot_s, 0);
    }
    return false;
}

}  // namespace uking::ai
