#include "Game/AI/Action/actionPlayerLadderJumpLand.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_7101e7c5d0.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerLadderJumpLand::PlayerLadderJumpLand(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: same control flow as the original except that the rung-snapping arms (offset against
// sUnk_7101e7c5d0) are folded into selects / a common fadd by the compiler, and the float registers of the
// final ladder-direction block are numbered differently
void PlayerLadderJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool a = static_cast<ksys::act::Player*>(mActor)->m188();
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->sub_71008697E4();

    auto* player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed = player->_1c84 ^ 0x80000000u;
    const ksys::act::Player::Unk1 angle(ksys::util::sUnk_7101EC6BA0 & reversed);
    player->x_53(angle);
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1c68.value = ksys::util::sUnk_7101EC6BA0 & (player->_1c84 ^ 0x80000000u);
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1810 = player->_22f4;
    player = static_cast<ksys::act::Player*>(mActor);
    ksys::util::sub_71011EEEE0(&player->_1810, player->_1c84, sUnk_7101e7c5d4);

    player = static_cast<ksys::act::Player*>(mActor);
    const f32 top = player->_22f4.y;
    const f32 base = player->_1770.y;
    if (top > base) {
        f32 offset = top - base;
        while (offset > sUnk_7101e7c5d0)
            offset -= sUnk_7101e7c5d0;
        if (a || offset < sUnk_7101e7c5d0 * 0.5f)
            player->_1810.y = offset + base;
        else
            player->_1810.y = base - (sUnk_7101e7c5d0 - offset);
    } else {
        f32 offset = base - top;
        while (offset > sUnk_7101e7c5d0)
            offset -= sUnk_7101e7c5d0;
        if (offset >= sUnk_7101e7c5d0 * 0.5f || a)
            player->_1810.y = (sUnk_7101e7c5d0 - offset) + base;
        else
            player->_1810.y = base - offset;
    }

    player = static_cast<ksys::act::Player*>(mActor);
    const f32 limit = player->_2100 + sUnk_7101e7c5d0 * -4.0f;
    if (player->_1810.y > limit) {
        player->_1810.y = limit;
        player = static_cast<ksys::act::Player*>(mActor);
    }
    player->_181c = player->_1770;
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;

    player = static_cast<ksys::act::Player*>(mActor);
    const f32 dx = player->_1810.x - player->_181c.x;
    const f32 dz = player->_1810.z - player->_181c.z;
    const f32 length = sead::Mathf::sqrt(dx * dx + dz * dz);
    const f32 min_length = sUnk_7101e7c5c4;
    player = static_cast<ksys::act::Player*>(mActor);
    if (length < min_length) {
        if (mActor->getVelocity().y < -0.1f && mActor->getASList()->x_1(0, 0) != "LadderDownSt")
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderLand", true,
                                                                               -1.0f);
        else
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderWait", true,
                                                                               -1.0f);
    } else {
        const f32 dy = player->_1810.y - player->_181c.y;
        sead::Vector3f axis;
        player->_1b18.getBase(axis, 0);
        axis.normalize();
        if (axis.dot(sead::Vector3f(dx, dy, dz)) > 0.0f)
            mActor->getASList()->x_6(9, 0, -90.0f);
        else
            mActor->getASList()->x_6(9, 0, 90.0f);
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderUpReadySt", true,
                                                                           -1.0f);
    }
    if (auto* controller = mActor->getCharacterController()) {
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGround);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    }
}

void PlayerLadderJumpLand::leave_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c = player->_1810;
    if (auto* controller = mActor->getCharacterController()) {
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    }
}

void PlayerLadderJumpLand::loadParams_() {
    getDynamicParam(&mMoveDir_d, "MoveDir");
}

// NON_MATCHING: register numbering of the two addresses of the Vector3f copy (x8 / x9 swapped)
void PlayerLadderJumpLand::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 step = ksys::VFR::instance()->getDeltaFrame() * 0.2f;
    const sead::Vector3f to_target = player->_1810 - player->_181c;
    const f32 length = to_target.length();
    if (length <= step) {
        sead::Vector3f& position = player->_181c;
        position.set(player->_1810);
    } else {
        player->_181c += (to_target * (1.0f / length)) * step;
    }
    static_cast<ksys::act::Player*>(mActor)->sub_7100892100(
        static_cast<ksys::act::Player*>(mActor)->_181c);

    if (mActor->getASList()->x_1(0, 0) != "LadderWait") {
        if (!mActor->getASList()->x_4(0, 0))
            return;
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderWait", true,
                                                                           -1.0f);
    }
    if (static_cast<ksys::act::Player*>(mActor)->_17f0)
        return;
    if (mActor->getASList()->sub_710115FBC8(22, nullptr,
                                            &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        return;
    }
    player = static_cast<ksys::act::Player*>(mActor);
    if ((player->_1770 - player->_1810).length() < 0.01f) {
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
        if (auto* controller = mActor->getCharacterController()) {
            controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
            controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
        }
        setFinished();
    }
}

bool PlayerLadderJumpLand::isChangeable() const {
    return true;
}

}  // namespace uking::action
