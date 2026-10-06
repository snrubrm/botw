#include "Game/AI/Action/actionWarpPlayerToAnchorGimmickReset.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::action {

WarpPlayerToAnchorGimmickReset::WarpPlayerToAnchorGimmickReset(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WarpPlayerToAnchorGimmickReset::~WarpPlayerToAnchorGimmickReset() = default;

bool WarpPlayerToAnchorGimmickReset::init_(sead::Heap* heap) {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (player.hasProc())
        _48.set(player.getField418());
    else
        _48.set(1.0f, 1.0f, 1.0f);
    _54 = false;
    _58 = 0.0f;
    return true;
}

void WarpPlayerToAnchorGimmickReset::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpPlayerToAnchorGimmickReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPlayerToAnchorGimmickReset::loadParams_() {
    getStaticParam(&mWaitFrameAfterReset_s, "WaitFrameAfterReset");
    getMapUnitParam(&mAnchorName_m, "AnchorName");
    getMapUnitParam(&mAnchorUniqueName_m, "AnchorUniqueName");
}

void WarpPlayerToAnchorGimmickReset::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
