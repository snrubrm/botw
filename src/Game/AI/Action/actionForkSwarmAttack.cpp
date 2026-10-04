#include "Game/AI/Action/actionForkSwarmAttack.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
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
    ksys::act::ai::Action::enter_(params);
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
