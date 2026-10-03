#include "Game/AI/Action/actionPlayerSwimJump.h"
#include <xlink2/xlink2HandleELink.h>
#include "Game/AI/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

PlayerSwimJump::PlayerSwimJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x100000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x800000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimJumpSt", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->decreaseStaminaForActionMaybe(*mEnergyJump_s * player->x_67());
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

void PlayerSwimJump::leave_() {}

void PlayerSwimJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mEnergyJump_s, "EnergyJump");
}

// NON_MATCHING: (1) the original compares `fcmp water, sum; b.le` (ogt), ours `fcmp sum, water; b.pl` (the same
// load order is only reachable with `water > sum`, which loads the water height first); (2) HandleELink::setPosition
// stores the (1,1,1) scale as two stp pairs interleaved with the position z, ours merges the constants into one
// 64-bit store (the same libwork finding as Unk_71012419b4::sub_71012419B4).
void PlayerSwimJump::calc_() {
    if (mActor->getASList()->x_1(0, 0) == "SwimJumpSt") {
        if (mActor->getASList()->x_4(0, 0)) {
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimJump", true,
                                                                               -1.0f);
            static_cast<ksys::act::Player*>(mActor)->_cec.set(2);
            static_cast<ksys::act::Player*>(mActor)->_cfc.reset(1);
            if (auto* cc = mActor->getCharacterController()) {
                cc->sub_7100F5EF08(true);
                cc->sub_7100F62B70(*mJumpHeight_s);
            }
            auto* player = static_cast<ksys::act::Player*>(mActor);
            const f32& speed = *mJumpSpeedF_s;
            player->_20bc.value = speed;
            player->_20bc.prev_value = speed;
            static_cast<ksys::act::Player*>(mActor)->actionCommon();
            static_cast<ksys::act::Player*>(mActor)->_cec.reset(0x400);
            auto handle = ksys::eft::searchAndEmitELink(mActor, "ReactionWater_Out");
            player = static_cast<ksys::act::Player*>(mActor);
            handle.setPosition({player->_1770.x, player->_20d4, player->_1770.z});
        }
    } else {
        if (auto* cc = mActor->getCharacterController()) {
            if (cc->_116 & 4)
                static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
        }
        auto* player = static_cast<ksys::act::Player*>(mActor);
        if (player->_1770.y + sUnk_7101e7c5c8 < player->_20d4)
            setFinished();
    }
}

bool PlayerSwimJump::isChangeable() const {
    return true;
}

}  // namespace uking::action
