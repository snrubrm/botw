#include "Game/AI/Action/actionWarpPlayerToReferenceAnchor.h"
#include "Game/gameResetter.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::action {

WarpPlayerToReferenceAnchor::WarpPlayerToReferenceAnchor(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WarpPlayerToReferenceAnchor::~WarpPlayerToReferenceAnchor() = default;

bool WarpPlayerToReferenceAnchor::init_(sead::Heap* heap) {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (player.hasProc())
        _1c.set(player.getField418());
    else
        _1c.set(1.0f, 1.0f, 1.0f);
    return true;
}

void WarpPlayerToReferenceAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpPlayerToReferenceAnchor::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPlayerToReferenceAnchor::loadParams_() {}

void WarpPlayerToReferenceAnchor::calc_() {
    if (isFinished() || isFailed())
        return;
    if (auto* resetter = Resetter::instance()) {
        if (resetter->finishedReset())
            setFinished();
    } else {
        setFailed();
    }
}

}  // namespace uking::action
