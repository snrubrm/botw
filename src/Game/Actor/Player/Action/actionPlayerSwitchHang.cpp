#include "Game/Actor/Player/Action/actionPlayerSwitchHang.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerSwitchHang::PlayerSwitchHang(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: the angle-mask load is hoisted above the player load here (the original keeps it after
// the _1834 store); the rest of the body is identical.
void PlayerSwitchHang::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);

    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x40);
    static_cast<ksys::act::Player*>(mActor)->sub_71008697E4();
    {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        player->_20bc.value = 0;
        player->_20bc.prev_value = 0;
    }

    if (auto* controller = static_cast<ksys::act::Player*>(mActor)->getCharacterController())
        controller->sub_7100F5F6FC(sead::Vector3f::zero);

    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("RoofHangStart", true, -1.0f);

    auto* parent = sead::DynamicCast<ksys::act::Actor>(
        static_cast<ksys::act::Player*>(mActor)->get1520().getProc(nullptr, nullptr));
    const u32 angle = sead::Mathf::atan2Idx(parent->getMtx().m[0][2], parent->getMtx().m[2][2]);

    const auto base = static_cast<ksys::act::Player*>(mActor)->x_5();
    static_cast<ksys::act::Player*>(mActor)->_1834.value =
        ksys::util::sub_71011EE4C0(s64(base.value) - s64(angle)) > 0x40000000 ? 0x80000000 : 0;
    static_cast<ksys::act::Player*>(mActor)->_1c68.value =
        ksys::util::sUnk_7101EC6BA0 & (static_cast<ksys::act::Player*>(mActor)->_1834.value + angle);
    static_cast<ksys::act::Player*>(mActor)->sub_7100869634(ksys::util::angleDiff(
        static_cast<ksys::act::Player*>(mActor)->_1c68.value,
        static_cast<ksys::act::Player*>(mActor)->x_5()));
    static_cast<ksys::act::Player*>(mActor)->x_53(static_cast<ksys::act::Player*>(mActor)->_1c68);
}

void PlayerSwitchHang::leave_() {}

void PlayerSwitchHang::calc_() {
    PlayerAction::calc_();
}

bool PlayerSwitchHang::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
