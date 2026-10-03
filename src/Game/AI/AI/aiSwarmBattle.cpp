#include "Game/AI/AI/aiSwarmBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SwarmBattle::SwarmBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmBattle::~SwarmBattle() = default;

bool SwarmBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwarmBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    _50 = 0;

    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        const s32 interval = enemy->_f28.sub_7100001AA4(*mAttackIntervalIntensity_s);
        enemy->_e68 = ksys::Timer(interval, interval);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘準備", &pack);
}

void SwarmBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwarmBattle::loadParams_() {
    getStaticParam(&mFailedRiseHeight_s, "FailedRiseHeight");
    getStaticParam(&mRiseFailedMoveDist_s, "RiseFailedMoveDist");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
}

bool SwarmBattle::isFailed() const {
    return ksys::act::ai::Ai::isFailed() ||
           (isCurrentChild("戦闘準備") && getCurrentChild()->isFailed());
}

}  // namespace uking::ai
