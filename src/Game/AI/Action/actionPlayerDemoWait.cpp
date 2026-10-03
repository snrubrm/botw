#include "Game/AI/Action/actionPlayerDemoWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerDemoWait::PlayerDemoWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDemoWait::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool is_swimming = static_cast<ksys::act::Player*>(mActor)->m188();
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(0);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(9);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(6);
    if (is_swimming)
        static_cast<ksys::act::Player*>(mActor)->_cec.setBit(10);
    if (static_cast<ksys::act::Player*>(mActor)->x_48()) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("MotorcycleWait", true, -1.0f);
    } else if (static_cast<ksys::act::Player*>(mActor)->isRidingHorse()) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("HorseWait", true, -1.0f);
    } else if (static_cast<ksys::act::Player*>(mActor)->m188()) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWait", false, -1.0f);
    } else {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", false, -1.0f);
    }
    setFinished();
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
