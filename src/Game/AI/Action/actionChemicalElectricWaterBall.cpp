#include "Game/AI/Action/actionChemicalElectricWaterBall.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

ChemicalElectricWaterBall::ChemicalElectricWaterBall(const InitArg& arg)
    : ChemicalAttackBall(arg) {}

ChemicalElectricWaterBall::~ChemicalElectricWaterBall() = default;

bool ChemicalElectricWaterBall::init_(sead::Heap* heap) {
    return ChemicalAttackBall::init_(heap);
}

void ChemicalElectricWaterBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttackBall::enter_(params);
}

void ChemicalElectricWaterBall::leave_() {
    mActor->sub_71011DA834(&_c0);
    ChemicalAttackBall::leave_();
}

void ChemicalElectricWaterBall::loadParams_() {
    ChemicalAttackBall::loadParams_();
    getStaticParam(&mDeleteTime_s, "DeleteTime");
    getStaticParam(&mTargetScale_s, "TargetScale");
    getStaticParam(&mScaleKeep_s, "ScaleKeep");
    getAITreeVariable(&mChemicalBulletBindActor_a, "ChemicalBulletBindActor");
}

void ChemicalElectricWaterBall::calc_() {
    ChemicalAttackBall::calc_();
}

int ChemicalElectricWaterBall::m36() {
    return ChemicalAttackBall::m36() | 8;
}

int ChemicalElectricWaterBall::m37() {
    return mActor->getParam()->getRes().mGParamList->getAttack()->mPower.ref();
}

int ChemicalElectricWaterBall::m38() {
    return mActor->getParam()->getRes().mGParamList->getAttack()->mPowerForPlayer.ref();
}

}  // namespace uking::action
