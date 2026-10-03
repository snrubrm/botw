#include "Game/AI/AI/aiLynelRodeo.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::ai {

LynelRodeo::LynelRodeo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRodeo::~LynelRodeo() = default;

bool LynelRodeo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelRodeo::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.setBit(1);
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    sub_71005D8DE8(mActor, ksys::act::PlayerInfo::getSomeProcLink(), &player.getActorMtx(),
                   &player.getPreviousPos());
    changeChild("暴れる");
}

void LynelRodeo::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_80000000);
    *mLynelRodeoAttackHitNum_a = 0;
}

void LynelRodeo::loadParams_() {
    getAITreeVariable(&mLynelRodeoAttackHitNum_a, "LynelRodeoAttackHitNum");
}

}  // namespace uking::ai
