#include "Game/Actor/Action/actionEventMiniGameTime.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameEventMgrMiniGame.h"

namespace uking::action {

EventMiniGameTime::EventMiniGameTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameTime::~EventMiniGameTime() = default;

bool EventMiniGameTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameTime::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mini_game = Unk_71024e80e0::instance();
    const s32 mode = *mCountMode_d;
    if (mode == 0) {
        mini_game->startCountup(*mMaxTime_d >= 0 ? *mMaxTime_d * 1000 : 5999999);
        if (*mIsShowTimeUI_d)
            ui::openMinigameScreenForTimer(false);
    } else if (mode == 1) {
        mini_game->startCountdown(*mCountStartTime_d * 1000);
        if (*mIsShowTimeUI_d)
            ui::openMinigameScreenForTimer(true);
    } else if (mode == 2) {
    } else {
        setFailed();
        mFlags.set(Flag::Changeable);
        return;
    }
    ui::minigameScreenUpdateTimer(mini_game->getTimerMs());
    setFinished();
}

void EventMiniGameTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventMiniGameTime::loadParams_() {
    getDynamicParam(&mCountMode_d, "CountMode");
    getDynamicParam(&mCountStartTime_d, "CountStartTime");
    getDynamicParam(&mMaxTime_d, "MaxTime");
    getDynamicParam(&mIsShowTimeUI_d, "IsShowTimeUI");
}

void EventMiniGameTime::calc_() {
    ui::minigameScreenUpdateTimer(Unk_71024e80e0::instance()->getTimerMs());
}

}  // namespace uking::action
