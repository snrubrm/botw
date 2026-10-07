#include "Game/AI/Action/actionPlayerSwimDash.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/gameUnk_710246d058.h"

namespace uking::action {

PlayerSwimDash::PlayerSwimDash(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimDash::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x800);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80000000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimDash", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->decreaseStaminaForActionMaybe(*mEnergyDash_s * player->x_67());
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f1 = false;
}

// NON_MATCHING: the original copies the velocity once more (element-wise self-copy of x/z after the call)
void PlayerSwimDash::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f vel;
        controller->sub_7100F5F598(&vel);
        if (vel.y > 0.0f) {
            vel.y = 0.0f;
            controller->sub_7100F5F6FC(vel);
        }
    }
}

void PlayerSwimDash::loadParams_() {
    getStaticParam(&mEnergyDash_s, "EnergyDash");
}

// NON_MATCHING: original velocity copying retains redundant component stores.
void PlayerSwimDash::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_710085C55C();
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        if (velocity.y > 0.0f) {
            velocity.y = 0.0f;
            controller->sub_7100F5F6FC(velocity);
        }
    }
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (mActor->getASList()->x_4(0, 0)) {
        setFinished();
    } else {
        if (mActor->getASList()->x(0, nullptr, 0, 0,
                                 &ksys::as::ASList::Unk2::sub_71011638DC, true) &&
            static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(2) &&
            !static_cast<ksys::act::Player*>(mActor)->x_44()) {
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
        }
        if (mActor->getASList()->x(0, nullptr, 0, 0,
                                 &ksys::as::ASList::Unk2::sub_71011638DC, true) &&
            static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(0x24) &&
            !static_cast<ksys::act::Player*>(mActor)->x_44()) {
            static_cast<ksys::act::Player*>(mActor)->_17f1 = true;
        }
        if (mActor->getASList()->x(2, nullptr, 0, 0,
                                 &ksys::as::ASList::Unk2::sub_710116383C, true)) {
            _1c = true;
        }
    }
}

bool PlayerSwimDash::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
