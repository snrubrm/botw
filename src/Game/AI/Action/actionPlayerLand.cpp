#include "Game/AI/Action/actionPlayerLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerLand::PlayerLand(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: the stack slots of the x_5() result and of the angle index passed to sub_71011EE4B8 are
// swapped (the original keeps the x_5() result in the lower slot and reads _1c74 after the call)
void PlayerLand::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool a = static_cast<ksys::act::Player*>(mActor)->m194();
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    if (a)
        static_cast<ksys::act::Player*>(mActor)->_cf8.set(0x10);
    if (mActor->getASList()->x_1(1, 1) == "ParaEquipOff")
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000);
    if (static_cast<ksys::act::Player*>(mActor)->_c98.isOnBit(17))
        static_cast<ksys::act::Player*>(mActor)->_c4c.set(0x4);
    mActor->getASList()->sub_710115EFD0(
        0, true, false, static_cast<ksys::act::Player*>(mActor)->get17d0()->getLeftStick().length());

    auto* player = static_cast<ksys::act::Player*>(mActor);
    if ((player->_c44.isOnBit(8) && !player->_d11) ||
        ksys::act::playerIsReloadingOrChargingOrShootingBow(player)) {
        player->getASList()->x_6(6, 0, 0.0f);
    } else {
        auto* as_list = player->getASList();
        const u32 current = player->x_5().value;
        const ksys::util::Unk_7101EC6BAC diff(ksys::util::sUnk_7101EC6BA0 & (player->_1c74 - current));
        as_list->x_6(6, 0, ksys::util::sub_71011EE4B8(diff) * ksys::util::sUnk_7101EC6BA4);
    }
    mActor->getASList()->x_6(16, 0,
                             static_cast<ksys::act::Player*>(mActor)->_1770.y -
                                 static_cast<ksys::act::Player*>(mActor)->_20d0);
    if (mActor->getASList()->x_1(0, 0) != "Land")
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Land", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_c50.setBit(0);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_211c = 0;
    if (static_cast<ksys::act::Player*>(mActor)->m194()) {
        auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
            actor->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void PlayerLand::leave_() {
    if (static_cast<ksys::act::Player*>(mActor)->m194()) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        auto* proc = player->_2c28.getProc(nullptr, nullptr);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
            actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void PlayerLand::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->m194()) {
        if (mActor->getASList()->x(84, nullptr, 1, 1, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true) ||
            mActor->getASList()->x_1(1, 1) != "ParaEquipOff") {
            static_cast<ksys::act::Player*>(mActor)->_cec.reset(0x8000);
            auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
                actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }

    static_cast<ksys::act::Player*>(mActor)->sub_71008931C4();
    if (static_cast<ksys::act::Player*>(mActor)->_c44.isOnBit(8) &&
        !static_cast<ksys::act::Player*>(mActor)->_d11) {
        static_cast<ksys::act::Player*>(mActor)->x_37();
    }
    static_cast<ksys::act::Player*>(mActor)->sub_71008893B8(false);
    if (static_cast<ksys::act::Player*>(mActor)->m179()) {
        static_cast<ksys::act::Player*>(mActor)->sub_71008824AC(false);
        if (ksys::act::playerIsReloadingOrChargingOrShootingBow(
                static_cast<ksys::act::Player*>(mActor))) {
            static_cast<ksys::act::Player*>(mActor)->x_37();
        }
    }
    if (!ksys::act::playerIsReloadingOrChargingOrShootingBow(static_cast<ksys::act::Player*>(mActor))) {
        if (!(static_cast<ksys::act::Player*>(mActor)->_c44.isOnBit(8) &&
              !static_cast<ksys::act::Player*>(mActor)->_d11)) {
            const sead::Vector3f& anim_driven = mActor->getASList()->sub_710115D3B8();
            static_cast<ksys::act::Player*>(mActor)->sub_710086800C(anim_driven.y);
            if (!static_cast<ksys::act::Player*>(mActor)->m224() &&
                !mActor->getASList()->x(11, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                        true)) {
                static_cast<ksys::act::Player*>(mActor)->_1c68 =
                    static_cast<ksys::act::Player*>(mActor)->x_5();
            }
        }
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const sead::Vector3f& velocity = player->getASList()->sub_710115D2D4();
    const f32 speed = sead::Mathf::sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
    player->_20bc.value = speed;
    player->_20bc.prev_value = speed;
    if (static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(2))
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
    m32();
    static_cast<ksys::act::Player*>(mActor)->sub_71008B5B8();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
