#include "Game/AI/Action/actionRemainsWaterBulletExplode.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

RemainsWaterBulletExplode::RemainsWaterBulletExplode(const InitArg& arg) : Explode(arg) {}

RemainsWaterBulletExplode::~RemainsWaterBulletExplode() = default;

bool RemainsWaterBulletExplode::init_(sead::Heap* heap) {
    return Explode::init_(heap);
}

void RemainsWaterBulletExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    Explode::enter_(params);
}

void RemainsWaterBulletExplode::leave_() {
    Explode::leave_();
    auto* actor = mActor;
    if (auto* model = actor->getModel())
        model->getUnits().unsafeAt(0)->_1e |= 0x20;
    ksys::act::enableAllAttClients(actor);
}

void RemainsWaterBulletExplode::loadParams_() {
    Explode::loadParams_();
    getStaticParam(&mMaxDamage_s, "MaxDamage");
    getStaticParam(&mMinDamage_s, "MinDamage");
}

void RemainsWaterBulletExplode::calc_() {
    Explode::calc_();
}

void RemainsWaterBulletExplode::m34(ksys::act::AttackSensor* sensor) {
    if (!sensor)
        return;
    sensor->activateAttackSensor(
        0x10, sub_710012B058(), *mMaxDamage_s,
        mActor->getParam()->getRes().mGParamList->getAttack()->mImpulseLarge.ref(), 0.0f,
        mActor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref(), 0x1e, -1,
        false, *mMinDamage_s, -1);
}

}  // namespace uking::action
