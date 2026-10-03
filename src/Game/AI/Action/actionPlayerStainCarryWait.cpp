#include "Game/AI/Action/actionPlayerStainCarryWait.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

PlayerStainCarryWait::PlayerStainCarryWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerStainCarryWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    if (mActor->getASList()->x_1(0, 0) != "DemoWait")
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true, -1.0f);
    _1d = false;
}

void PlayerStainCarryWait::leave_() {
    if (auto* mgr = ui::PauseMenuDataMgr::instance())
        mgr->removeGrabbedItems();
}

bool PlayerStainCarryWait::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x8000003) {
        _1d = true;
        return true;
    }
    return false;
}

void PlayerStainCarryWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerStainCarryWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
