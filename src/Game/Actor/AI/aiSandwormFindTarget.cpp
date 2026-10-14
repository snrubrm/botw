#include "Game/Actor/AI/aiSandwormFindTarget.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <cmath>

namespace uking::ai {

SandwormFindTarget::SandwormFindTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormFindTarget::~SandwormFindTarget() = default;

bool SandwormFindTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormFindTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const u32 lost_timer = *mLostTimer_s;
    _64 = lost_timer;
    _68 = lost_timer;

    const sead::Vector3f my_pos = mActor->getMtx().getTranslation();
    const sead::Vector3f& target = sub_71005D9330(mActor);
    const f32 dx = target.x - my_pos.x;
    const f32 dz = target.z - my_pos.z;
    if (dx * dx + dz * dz > *mAttackRange_s * *mAttackRange_s || !isTargetReachable())
        sub_710055A3DC();
    else if (isTargetLost())
        sub_710055A530();
    else
        sub_710055A614();
    sub_71007A3800(mActor);
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

// 0x710055a614 (CSV sandwormFindTarget)
void SandwormFindTarget::sub_710055A614() {
    const sead::Vector3f pos = sub_71005D9330(mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("戦闘", &pack);
}

}  // namespace uking::ai
