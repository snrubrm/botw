#include "Game/AI/Action/actionWarpPlayerToAnchorGimmickReset.h"
#include "Game/gameResetter.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"
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
    if (isFinished() || isFailed())
        return;
    const f32 time = _58;
    if (time > 0) {
        f32 current = time;
        if (time > *mWaitFrameAfterReset_s) {
            setFinished();
            current = _58;
        }
        _58 = current + 1.0f;
    } else if (_54) {
        if (ksys::world::Manager::instance()->getWeatherMgrUnchecked()->_24 >= 1.0f)
            _58 = time + 1.0f;
    } else {
        auto* resetter = Resetter::instance();
        if (!resetter) {
            setFailed();
            return;
        }
        if (resetter->finishedReset())
            _54 = true;
    }
}

}  // namespace uking::action
