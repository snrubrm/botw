#include "Game/Actor/Player/Action/actionPlayerElectric.h"
#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Damage/dmgDamageMgrPlayer.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerElectric::PlayerElectric(const InitArg& arg) : PlayerAction(arg) {}

void PlayerElectric::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerElectric::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(0x100000);
    if (static_cast<ksys::act::Player*>(mActor)->stillAlive()) {
        // called through a pointer in the original (not devirtualised)
        (&static_cast<ksys::act::Player*>(mActor)->_2550)->m13(4);
    }
    if (static_cast<ksys::act::Player*>(mActor)->stillAlive()) {
        static_cast<ksys::act::Player*>(mActor)->sub_7100884578();
        xlink::fade(static_cast<ksys::act::Player*>(mActor)->_2390, -1);
    }
    if (auto* manager = sead::DynamicCast<uking::act::DamageMgrPlayer>(mActor->getDamageMgr()))
        manager->_231 = false;
    if (mActor->getASList()->x_7(1, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
    mActor->get548()->m8()->m10(0, false);
}

void PlayerElectric::loadParams_() {
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

// NON_MATCHING: the original reloads `mActor` separately in both arms after stillAlive() (ours hoists the load).
void PlayerElectric::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_17f0) {
        if (player->isSurfingOnGround())
            // called through a pointer in the original (not devirtualised)
            (&static_cast<ksys::act::Player*>(mActor)->_2550)->m13(4);
    } else {
        player->_20bc.value = 0;
        player->_20bc.prev_value = 0;
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (static_cast<ksys::act::Player*>(mActor)->stillAlive()) {
        if (!static_cast<ksys::act::Player*>(mActor)->_2550._8.isOnBit(4))
            setFinished();
    } else {
        uking::callPlayerGameOverDemo(mActor);
    }
}

bool PlayerElectric::isChangeable() const {
    return false;
}

}  // namespace uking::action
