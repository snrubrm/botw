#include "KingSystem/Sound/Actor/Action/actionEventBgmCtrlAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"

namespace ksys::snd {

EventBgmCtrlAction::EventBgmCtrlAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBgmCtrlAction::~EventBgmCtrlAction() = default;

bool EventBgmCtrlAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBgmCtrlAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

bool EventBgmCtrlAction::oneShot_() {
    if (mCtrlType_d == "RemainsWindBattleBgm_Jump") {
        if (auto* bgm = sub_7100FFE204()) {
            bgm->sub_7101009040();
            return true;
        }
    } else if (mCtrlType_d == "RemainsFireBattleBgm_Alert") {
        if (auto* bgm = sub_7100FFE39C()) {
            bgm->sub_71010084B4(true);
            return true;
        }
    } else if (mCtrlType_d == "RemainsFireBattleBgm_Alert2") {
        if (auto* bgm = sub_7100FFE39C()) {
            bgm->sub_71010084B4(false);
            return true;
        }
    }
    return false;
}

}  // namespace ksys::snd
