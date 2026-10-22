#include "Game/Actor/Player/Action/actionPlayerClimbRest.h"
#include "Game/Actor/aiUnk_710087CE34.h"
#include "Game/Actor/actWeapon.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

PlayerClimbRest::PlayerClimbRest(const InitArg& arg) : PlayerAction(arg) {}

PlayerClimbRest::~PlayerClimbRest() = default;

void PlayerClimbRest::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x80);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const int weapon_idx = player->playerWeapons_return0();
    if (auto* weapon = sead::DynamicCast<act::Weapon>(player->getWeapons()->getEquippedWeapon(weapon_idx))) {
        auto* as_list = mActor->getASList();
        as_list->goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(), 0);
        _28.acquire(weapon, false);
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_28, &accessor);
        if (sub_71002EFC98(accessor)) {
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ClimbPegNG", true, -1.0f);
            ui::showInfoOverlay(0x2f);
        } else {
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ClimbPegSt", true, -1.0f);
        }
    }
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    sub_710087CE34(mActor);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f1 = false;
}

// NON_MATCHING: the Weapon typeinfo guard is emitted after the null test here; the original initialises it
// first (DynamicCast's inline order). The rest of the body matches.
void PlayerClimbRest::leave_() {
    if (_28.hasProc()) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(_28.getProc(nullptr, nullptr));
        if (weapon) {
            if (static_cast<ksys::act::Player*>(mActor)->sub_71008921A8()) {
                static_cast<ksys::act::Player*>(mActor)->m164(3, weapon, false, false);
                static_cast<ksys::act::Player*>(mActor)->getWeapons()->mWeapons[3]._10 = false;
                static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
            } else {
                static_cast<ksys::act::Player*>(mActor)->m164(
                    static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), weapon, false,
                    false);
                static_cast<ksys::act::Player*>(mActor)
                    ->getWeapons()
                    ->mWeapons[static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0()]
                    ._10 = false;
                static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
            }
        }
        sub_71007DC3FC();
    } else {
        static_cast<ksys::act::Player*>(mActor)
            ->getWeapons()
            ->mWeapons[static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0()]
            ._10 = true;
    }

    sub_710087CE90(mActor);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
}

void PlayerClimbRest::loadParams_() {
    getStaticParam(&mEnergyClimb_s, "EnergyClimb");
}

void PlayerClimbRest::calc_() {
    PlayerAction::calc_();
}

bool PlayerClimbRest::handleMessage_(const ksys::Message* message) {
    return message->getType() == 0x7800005;
}

bool PlayerClimbRest::isChangeable() const {
    return false;
}

}  // namespace uking::action
