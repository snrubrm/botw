#include "Game/AI/Action/actionPlayerStainCarryWait.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/gameSceneSubsys12.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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

// NON_MATCHING: the original reloads mActor from [this + 8] at every use; ours forms `this + 8` once (pre-indexed load,
// one more callee-saved register)
void PlayerStainCarryWait::calc_() {
    if (auto* scene = GameSceneSubsys12::instance()) {
        if (scene->sub_71006652C8()) {
            if (mActor->getASList()->x_1(1, 1) != "GrabPouchUpper") {
                mActor->getASList()->goLimpFromHeadShotMaybe(0x31, "Pouch", 0);
                static_cast<ksys::act::Player*>(mActor)->x_23("GrabPouchUpper", false, -1.0f);
            }
            if (_1d) {
                static_cast<ksys::act::Player*>(mActor)->sub_7100855F80("FaceDemo046_0GrabPouchUpper");
                _1d = false;
            }
        } else {
            static_cast<ksys::act::Player*>(mActor)->x_18(true);
        }
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    setFinished();
}

bool PlayerStainCarryWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
