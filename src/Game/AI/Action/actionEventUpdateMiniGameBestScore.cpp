#include "Game/AI/Action/actionEventUpdateMiniGameBestScore.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

EventUpdateMiniGameBestScore::EventUpdateMiniGameBestScore(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventUpdateMiniGameBestScore::~EventUpdateMiniGameBestScore() = default;

bool EventUpdateMiniGameBestScore::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventUpdateMiniGameBestScore::oneShot_() {
    if (*mType_d == 0) {
        const s32 score = ksys::gdt::getFlag_CurrentTotalGetRupeeInMiniGame();
        if (score > ksys::gdt::getFlag_GoronCamp_BestScore())
            ksys::gdt::setFlag_GoronCamp_BestScore(score);
    }
    return true;
}

void EventUpdateMiniGameBestScore::loadParams_() {
    getDynamicParam(&mType_d, "Type");
}

}  // namespace uking::action
