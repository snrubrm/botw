#include "Game/AI/Action/actionWarpPLToPosAndResetGimmick.h"
#include <prim/seadSafeString.h>
#include "Game/gameResetter.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

WarpPLToPosAndResetGimmick::WarpPLToPosAndResetGimmick(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WarpPLToPosAndResetGimmick::~WarpPLToPosAndResetGimmick() = default;

bool WarpPLToPosAndResetGimmick::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpPLToPosAndResetGimmick::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    const sead::Vector3f rotation(0.0f, *mRotationY_d, 0.0f);
    auto* resetter = Resetter::instance();
    if (!resetter->sub_71007D25A4(nullptr, ResetOption{*mSystemResetOption_d}, mDestination_d, &rotation,
                                  &player.getField418(), mAdditionalResetActor_d, false)) {
        sead::FixedSafeString<128> flow;
        sead::FixedSafeString<128> entry;
        getActiveEventFlowPath_0(mActor, &flow, &entry);
        setFailed();
    }
}

void WarpPLToPosAndResetGimmick::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPLToPosAndResetGimmick::loadParams_() {
    getDynamicParam(&mRotationY_d, "RotationY");
    getDynamicParam(&mDestination_d, "Destination");
    getDynamicParam(&mSystemResetOption_d, "SystemResetOption");
    getDynamicParam(&mAdditionalResetActor_d, "AdditionalResetActor");
}

void WarpPLToPosAndResetGimmick::calc_() {
    if (isFinished() || isFailed())
        return;
    if (Resetter::instance()->finishedReset())
        setFinished();
}

}  // namespace uking::action
