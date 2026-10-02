#include "Game/AI/AI/aiWizzrobeFindPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

WizzrobeFindPlayer::WizzrobeFindPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeFindPlayer::~WizzrobeFindPlayer() = default;

bool WizzrobeFindPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    *mIsWizzrobeInBattleAreaFlag_a = true;
    auto* actor = mActor;
    sub_71005D7444(actor, sub_71005D960C(actor), true, true);
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000))
        wizzrobeFindPlayer();
    else
        sub_71005FDD14();
}

void WizzrobeFindPlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeFindPlayer::loadParams_() {
    getStaticParam(&mHomeTerritoryWidth_s, "HomeTerritoryWidth");
    getStaticParam(&mHomeTerritoryHeight_s, "HomeTerritoryHeight");
    getStaticParam(&mBattleTerritoryWidth_s, "BattleTerritoryWidth");
    getAITreeVariable(&mIsWizzrobeInBattleAreaFlag_a, "IsWizzrobeInBattleAreaFlag");
}

void WizzrobeFindPlayer::calc_() {
    auto* actor = mActor;
    sub_71005DB068(actor, sub_71005D960C(actor));
    auto* child = getCurrentChild();
    *mIsWizzrobeInBattleAreaFlag_a = sub_71005FDF08();

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("気づき")) {
            wizzrobeFindPlayer();
        } else if (isCurrentChild("戦闘")) {
            if (child->isFinished())
                wizzrobeFindPlayer();
            else
                setFailed();
        }
    }
    wizzrobeFindPlayer_0();
}

}  // namespace uking::ai
