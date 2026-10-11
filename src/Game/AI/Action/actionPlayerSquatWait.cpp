#include "Game/AI/Action/actionPlayerSquatWait.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerSquatWait::PlayerSquatWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSquatWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x40000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x20);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x40);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x400000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x4000);

    f32 wait = 0;
    if (mActor->getASList()->x_1(0, 0) != "SquatMove" &&
        mActor->getASList()->x_1(0, 0) != "SquatBowWait" &&
        mActor->getASList()->x_1(0, 0) != "SquatBowMove" &&
        mActor->getASList()->x_1(0, 0) != "SquatAtnMove")
        wait = *mWaitTime_s;
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(wait, wait);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    const char* animation = "SquatWait";
    if ((!player->m359() && player->m179() && !player->_c40.isOnBit(30)) ||
        (static_cast<ksys::act::Player*>(mActor)->_c44.isOnBit(8) &&
         !static_cast<ksys::act::Player*>(mActor)->_d11))
        animation = "SquatBowWait";
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe(animation, true, -1.0f);

    player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    player = static_cast<ksys::act::Player*>(mActor);
    if (!player->_c44.isOnBit(8) || player->_d11)
        player->x_40();
    player = static_cast<ksys::act::Player*>(mActor);
    player->_17f0 = player->_c50.isOnBit(9);
    static_cast<ksys::act::Player*>(mActor)->_17f2 = 0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd8);
    mActor->get548()->m8()->m10(0, true);
    ui::showRuntimeTip(13);
    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_c40.isOnBit(3) && player->_d30 != player->getEquipmentTypeName(1))
        static_cast<ksys::act::Player*>(mActor)->sub_710088B2EC();
}

void PlayerSquatWait::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
    mActor->get548()->m8()->m10(0, false);
    static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
    if (mActor->getASList()->x_1(1, 1) == "SquatWaitUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

void PlayerSquatWait::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mAtnTurnDiffAng_s, "AtnTurnDiffAng");
}

void PlayerSquatWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerSquatWait::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
