#include "Game/AI/Action/actionPlayerLadderToClimb.h"
#include <cmath>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

PlayerLadderToClimb::PlayerLadderToClimb(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: stack slot order of the x_5() result and the second angle argument (the original allocates the
// second argument before the x_5() temporary)
void PlayerLadderToClimb::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->sub_71008697E4();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const u8 turn = player->sub_7100869814(ksys::util::angleDiff(player->_1c74, player->x_5()),
                                           ksys::util::Unk_7101EC6BAC(ksys::util::sUnk_7101EC6BA0 & 0x20000000));
    auto* as_list = mActor->getASList();
    if (turn == 2)
        as_list->x_6(1, 0, -1.0f);
    else
        as_list->x_6(1, 0, 1.0f);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderToClimb", true, -1.0f);
}

void PlayerLadderToClimb::leave_() {}

void PlayerLadderToClimb::calc_() {
    const auto& mtx = static_cast<ksys::act::Player*>(mActor)->_1b18;
    sead::Vector3f dir;
    mtx.getBase(dir, 2);
    dir.normalize();
    const f32 angle = std::atan2(dir.x, dir.z);
    sead::Vector3f move = mActor->getASList()->sub_710115D2D4();
    ksys::util::sub_71011EF010(&move, angle);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F6FC(move * 30.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c += move * ksys::VFR::instance()->getDeltaFrame();
    m32();
}

bool PlayerLadderToClimb::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
