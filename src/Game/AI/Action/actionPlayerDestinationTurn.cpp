#include "Game/AI/Action/actionPlayerDestinationTurn.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerDestinationTurn::PlayerDestinationTurn(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDestinationTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    const f32 x = *mDestPosX_d;
    const f32 z = *mDestPosZ_d;
    _38 = ksys::util::Unk_7101EC6BAC(
        sead::Mathf::atan2Idx(x - static_cast<ksys::act::Player*>(mActor)->_1770.x,
                              z - static_cast<ksys::act::Player*>(mActor)->_1770.z));
    if (static_cast<ksys::act::Player*>(mActor)->isRidingHorse())
        setFinished();
}

void PlayerDestinationTurn::leave_() {}

void PlayerDestinationTurn::loadParams_() {
    getDynamicParam(&mDestPosX_d, "DestPosX");
    getDynamicParam(&mDestPosY_d, "DestPosY");
    getDynamicParam(&mDestPosZ_d, "DestPosZ");
}

void PlayerDestinationTurn::calc_() {
    m33();
    if (static_cast<ksys::act::Player*>(mActor)->sub_7100857014(-1.0f, &_38, -1, -1) && m34())
        setFinished();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

// NON_MATCHING: the original loads `_38` and the angle mask after the x_5() call (ours before it)
void PlayerDestinationTurn::m33() {
    const bool turned = static_cast<ksys::act::Player*>(mActor)->sub_7100857014(-1.0f, &_38, -1, -1);
    const auto& name = mActor->getASList()->x_1(0, 0);
    if (turned) {
        if (name != "DemoWait")
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true, -1.0f);
    } else if (name != "DemoTurn") {
        auto* as_list = static_cast<ksys::act::Player*>(mActor)->getASList();
        as_list->x_6(6, 0,
                     ksys::util::sub_71011EE4B8(ksys::util::Unk_7101EC6BAC(
                         ksys::util::sUnk_7101EC6BA0 &
                         (_38.value - static_cast<ksys::act::Player*>(mActor)->x_5().value))) *
                         ksys::util::sUnk_7101EC6BA4);
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoTurn", true, -1.0f);
    }
}

bool PlayerDestinationTurn::isChangeable() const {
    return false;
}

bool PlayerDestinationTurn::m34() {
    return true;
}

bool PlayerDestinationTurn::m35() {
    return true;
}

}  // namespace uking::action
