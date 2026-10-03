#include "Game/AI/Action/actionPlayerLadderDownStart.h"
#include <cmath>
#include "Game/AI/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerLadderDownStart::PlayerLadderDownStart(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderDownStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->sub_71008697E4();
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderDownSt", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;

    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c = player->_1770;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1810 = player->_22f4;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1810.y = player->_1770.y;
    player = static_cast<ksys::act::Player*>(mActor);
    ksys::util::sub_71011EEEE0(&player->_1810, player->_1c84, 0.4f);

    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGround);

    player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed = player->_1c84 + 0x80000000u;
    const ksys::act::Player::Unk1 angle(ksys::util::sUnk_7101EC6BA0 & reversed);
    player->x_53(angle);
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1c68.value = player->_1c84;
}

void PlayerLadderDownStart::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
    static_cast<ksys::act::Player*>(mActor)->_1c70 = 0x80000000;
    static_cast<ksys::act::Player*>(mActor)->_d1c = 1;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed = player->_1c84 + 0x80000000u;
    player->_1c84 = ksys::util::sUnk_7101EC6BA0 & reversed;
    player = static_cast<ksys::act::Player*>(mActor);
    ksys::util::sub_71011EEEE0(&player->_22f4, player->_1c84, sUnk_7101e7c5d8);
}

// NON_MATCHING: same operations and layout as the original, only the order of a few independent fmul / fadd /
// store instructions inside the two position updates differs
void PlayerLadderDownStart::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_17f0) {
        sead::Vector3f direction;
        player->_1b18.getBase(direction, 2);
        direction.normalize();
        const f32 angle = sead::Mathf::atan2(direction.x, direction.z);
        sead::Vector3f velocity = mActor->getASList()->sub_710115D2D4();
        ksys::util::sub_71011EF010(&velocity, angle);
        player = static_cast<ksys::act::Player*>(mActor);
        ksys::VFR::add(&player->_181c, velocity);
    } else {
        const f32 step = ksys::VFR::instance()->getDeltaFrame() * 0.2f;
        const sead::Vector3f to_target = player->_1810 - player->_181c;
        const f32 length = to_target.length();
        if (length <= step) {
            player->_181c.set(player->_1810);
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
            player = static_cast<ksys::act::Player*>(mActor);
            player->_1810 = player->_22f4;
            ksys::util::sub_71011EEEE0(&static_cast<ksys::act::Player*>(mActor)->_1810,
                                       static_cast<ksys::act::Player*>(mActor)->_1c84,
                                       -(sUnk_7101e7c5d4 + sUnk_7101e7c5d8));
            static_cast<ksys::act::Player*>(mActor)->_1810.y += sUnk_7101e7c5d0 * -4.0f;
        } else {
            const sead::Vector3f direction = to_target * (1.0f / length);
            player->_181c += direction * step;
        }
    }
    static_cast<ksys::act::Player*>(mActor)->sub_7100892100(
        static_cast<ksys::act::Player*>(mActor)->_181c);
    const sead::Vector3f& anim_driven = mActor->getASList()->sub_710115D3B8();
    static_cast<ksys::act::Player*>(mActor)->sub_710086800C(anim_driven.y);
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    m32();
}

bool PlayerLadderDownStart::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
