#include "Game/AI/Action/actionPlayerDemoWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerDemoWait::PlayerDemoWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDemoWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDemoWait::leave_() {}

void PlayerDemoWait::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;

    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround()) {
        if (mActor->getASList()->x_1(0, 0) == "Fall") {
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Land", true, -1.0f);
        } else if (mActor->getASList()->x_1(0, 0) == "Land") {
            if (mActor->getASList()->x_4(0, 0)) {
                static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true,
                                                                                   -1.0f);
            }
        }
    } else if (mActor->getASList()->x_1(0, 0) == "DemoWait") {
        player = static_cast<ksys::act::Player*>(mActor);
        sead::Vector3f start = player->_1770;
        start.y += 0.5f;
        sead::Vector3f end = player->_1770;
        end.y -= 0.5f;
        if (!player->sub_710087F360(start, end, nullptr, nullptr))
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Fall", true, -1.0f);
    }

    if (mActor->getASList()->x_1(0, 0) == "SwimWait" &&
        !static_cast<ksys::act::Player*>(mActor)->m188()) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true, -1.0f);
    }

    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerDemoWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
