#include "Game/Actor/Player/Action/actionPlayerHangWallCatch.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerHangWallCatch::PlayerHangWallCatch(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: angle-mask loads and operands are scheduled differently.
void PlayerHangWallCatch::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x40);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(2);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    f32 height = player->_2160.y - player->_1770.y - sUnk_7101e7c5c8;
    if (height < 0.0f)
        height = 0.0f;
    else if (height > 0.5f)
        height = 0.5f;
    player->getASList()->x_6(16, 0, height);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimHangClimb", true, -1.0f);
    player = static_cast<ksys::act::Player*>(mActor);
    const u32 mask = ksys::util::sUnk_7101EC6BA0;
    const ksys::act::Player::Unk1 angle(mask & (player->_1c84 ^ 0x80000000u));
    player->x_53(angle);
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1c68.value = mask & (player->_1c84 ^ 0x80000000u);
    player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    if (!static_cast<ksys::act::Player*>(mActor)->sub_7100888C40())
        static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
}

void PlayerHangWallCatch::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
}

void PlayerHangWallCatch::calc_() {
    PlayerAction::calc_();
}

bool PlayerHangWallCatch::isChangeable() const {
    return false;
}

}  // namespace uking::action
