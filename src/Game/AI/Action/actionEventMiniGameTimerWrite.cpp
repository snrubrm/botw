#include "Game/AI/Action/actionEventMiniGameTimerWrite.h"
#include "KingSystem/GameData/gdtManager.h"
#include "Game/gameEventMgrMiniGame.h"

namespace uking::action {

EventMiniGameTimerWrite::EventMiniGameTimerWrite(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameTimerWrite::~EventMiniGameTimerWrite() = default;

bool EventMiniGameTimerWrite::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameTimerWrite::loadParams_() {
    getDynamicParam(&mGameDataIntNameMintues_d, "GameDataIntNameMintues");
    getDynamicParam(&mGameDataIntNameSeconds_d, "GameDataIntNameSeconds");
    getDynamicParam(&mGameDataIntNameMiliseconds_d, "GameDataIntNameMiliseconds");
}

// NON_MATCHING: the failure path sets the return value (mov w0, wzr) between the flag byte's orr and strb
bool EventMiniGameTimerWrite::oneShot_() {
    auto* mini_game = EventMgrMiniGame::instance();
    if (mini_game) {
        if (auto* gdm = ksys::gdt::Manager::instance()) {
            const s32 minutes = mini_game->getTimerMs() / 60000;
            const s32 seconds = mini_game->getTimerMs() / 1000 % 60;
            const s32 centiseconds = mini_game->getTimerMs() % 1000 / 10;
            gdm->setS32(s16(minutes), mGameDataIntNameMintues_d);
            gdm->setS32(seconds, mGameDataIntNameSeconds_d);
            gdm->setS32(centiseconds, mGameDataIntNameMiliseconds_d);
            return true;
        }
    }
    setFailed();
    mFlags.set(Flag::Changeable);
    return false;
}

}  // namespace uking::action
