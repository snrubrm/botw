#include "Game/AI/Action/actionPlayerSwimMove.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSwimMove::PlayerSwimMove(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: the `mActor` member address is kept in a register (pre-indexed load) instead of reloading from `this`,
// and the sin/cos arithmetic of the inlined Matrix33f::makeRIdx is scheduled differently
void PlayerSwimMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (!player->_17d0->playerCheckController(13) || player->m202() || player->_c44.isOnBit(13) ||
        player->m178()) {
        static_cast<ksys::act::Player*>(mActor)->_1c68 =
            static_cast<ksys::act::Player*>(mActor)->x_5();
    }

    player = static_cast<ksys::act::Player*>(mActor);
    player->_1b6c.makeRIdx(0, player->x_5().value, 0);
}

void PlayerSwimMove::leave_() {}

void PlayerSwimMove::loadParams_() {
    getStaticParam(&mMaxSpeedF_s, "MaxSpeedF");
    getStaticParam(&mMaxSpeedS_s, "MaxSpeedS");
    getStaticParam(&mMaxSpeedB_s, "MaxSpeedB");
    getStaticParam(&mMaxSpeedDash_s, "MaxSpeedDash");
    getStaticParam(&mEnergyMove_s, "EnergyMove");
    getStaticParam(&mEnergyDash_s, "EnergyDash");
    getStaticParam(&mDecSpeedRate_s, "DecSpeedRate");
}

void PlayerSwimMove::calc_() {
    PlayerAction::calc_();
}

bool PlayerSwimMove::isChangeable() const {
    return true;
}

}  // namespace uking::action
