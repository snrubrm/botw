#include "Game/AI/Action/actionForkSwarmAttack.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/AI/aiUnk_710072A944.h"

namespace uking::action {

ForkSwarmAttack::ForkSwarmAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSwarmAttack::~ForkSwarmAttack() = default;

bool ForkSwarmAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSwarmAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* actor = mActor;
    auto* swarm = sead::DynamicCast<act::Swarm>(actor);
    if (!swarm) {
        setFailed();
        return;
    }
    _30 = false;
    sub_7100729EA8(swarm);
    auto* sensor = getActorAttackSensor(actor);
    static const u32 sAttackAttr[4] = {0, 1, 2, 4};
    const s32 intensity = *mAttackIntensity_s;
    const u32 attack_attr = u32(intensity) <= 3 ? sAttackAttr[intensity] : 0;
    const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
    sensor->activateAttackSensor(0x2000, attack_attr, attack->mPower.ref(), attack->mImpulse.ref(),
                                 0.0f, 0, 1, -1, false, 1, -1);
}

void ForkSwarmAttack::leave_() {
    if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor))
        sub_7100729F34(swarm);
}

void ForkSwarmAttack::loadParams_() {
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mIsAttackOnce_s, "IsAttackOnce");
}

void ForkSwarmAttack::calc_() {
    if (*mIsAttackOnce_s && !_30) {
        const int num = getNumAttackInfoMaybe(mActor);
        for (int i = 0; i < num; ++i) {
            if (ksys::act::isPlayerProfile(&getAttackInfo(mActor, i)->_50)) {
                if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor)) {
                    sub_7100729F34(swarm);
                    _30 = true;
                    return;
                }
            }
        }
    }
}

}  // namespace uking::action
