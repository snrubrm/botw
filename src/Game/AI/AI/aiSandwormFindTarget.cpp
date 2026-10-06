#include "Game/AI/AI/aiSandwormFindTarget.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

SandwormFindTarget::SandwormFindTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormFindTarget::~SandwormFindTarget() = default;

bool SandwormFindTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormFindTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandwormFindTarget::leave_() {
    sub_71007A397C(mActor);
}

void SandwormFindTarget::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mAttackRange_s, "AttackRange");
}

// 0x710055a530
void SandwormFindTarget::sub_710055A530() {
    const sead::Vector3f pos = sub_71005D9330(mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("威嚇", &pack);
}

// 0x710055a3dc
void SandwormFindTarget::sub_710055A3DC() {
    auto* actor = mActor;
    const sead::Vector3f pos = sub_71005D9330(actor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    if (auto* sensor = getActorAttackSensor(actor)) {
        sensor->activateAttackSensor(
            0x2000, 0xc, actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(),
            actor->getParam()->getRes().mGParamList->getAttack()->mImpulseLarge.ref(), 0.0f, 0,
            actor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref(), -1, false,
            1, -1);
    }
    changeChild("移動", &pack);
}

}  // namespace uking::ai
