#include "Game/AI/AI/aiEternalPlayerTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::ai {

EternalPlayerTarget::EternalPlayerTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EternalPlayerTarget::~EternalPlayerTarget() = default;

bool EternalPlayerTarget::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EternalPlayerTarget::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool EternalPlayerTarget::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool EternalPlayerTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EternalPlayerTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71003C9AAC(true);
}

void EternalPlayerTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EternalPlayerTarget::loadParams_() {}

void EternalPlayerTarget::calc_() {
    if (getCurrentChild()->isChangeable())
        sub_71003C9AAC(false);
}

void EternalPlayerTarget::sub_71003C9AAC(bool force) {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    sub_71005D8DE8(mActor, ksys::act::PlayerInfo::getSomeProcLink(), &player.getActorMtx(),
                   &player.getPreviousPos());
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_c48._7c = 5;

    if (sub_710072B660()) {
        if (force || !isCurrentChild("プレイヤー死亡"))
            changeChild("プレイヤー死亡");
    } else {
        if (force || !isCurrentChild("プレイヤー生存"))
            changeChild("プレイヤー生存");
    }
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
}

}  // namespace uking::ai
