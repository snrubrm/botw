#include "Game/AI/Action/actionAtkTackleMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"

namespace uking::action {

AtkTackleMove::AtkTackleMove(const InitArg& arg) : TackleMove(arg) {}

AtkTackleMove::~AtkTackleMove() = default;

bool AtkTackleMove::init_(sead::Heap* heap) {
    return TackleMove::init_(heap);
}

void AtkTackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    TackleMove::enter_(params);
    mFlags.reset(Flag::Changeable);
    setDamageCallbackTiming(mActor, 4, &_98);
    m36();
}

void AtkTackleMove::leave_() {
    m37();
    sub_71005DA114(mActor, &_98);
    TackleMove::leave_();
}

void AtkTackleMove::loadParams_() {
    TackleMove::loadParams_();
    getStaticParam(&mAtkSensorName_s, "AtkSensorName");
}

void AtkTackleMove::calc_() {
    TackleMove::calc_();
    if (!isFinished() && !isFailed() && m38())
        setFinished();
}

bool AtkTackleMove::m38() {
    return hasAttackInfo(mActor);
}

void AtkTackleMove::m37() {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtkSensorName_s.cstr())) {
        sub_71007A2D34(body);
        sub_71007A3258(body, nullptr);
    }
}

void AtkTackleMove::m36() {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtkSensorName_s.cstr());
    if (!body)
        return;
    sub_71007A2B64(body, nullptr);
    sub_71007A2EB0(body, actor, nullptr);
    getActorAttackSensor(actor)->activateAttackSensor(
        0x2000, 2, actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(),
        actor->getParam()->getRes().mGParamList->getAttack()->mImpulseLarge.ref(), 0.0f,
        actor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref() * 6, 1, -1,
        false, 1, -1);
}

}  // namespace uking::action
