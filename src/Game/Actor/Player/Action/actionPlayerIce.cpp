#include "Game/Actor/Player/Action/actionPlayerIce.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

PlayerIce::PlayerIce(const InitArg& arg) : PlayerAction(arg) {}

void PlayerIce::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerIce::leave_() {
    if (static_cast<ksys::act::Player*>(mActor)->stillAlive()) {
        static_cast<ksys::act::Player*>(mActor)->sub_710085AA70(0.0f);
        mActor->getPhysics()->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
        static_cast<ksys::act::Player*>(mActor)->sub_7100884578();
        auto* actor = mActor;
        actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
        actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
        actor->getASList()->x_3(0, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
        actor->getASList()->x_3(1, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
        actor->getASList()->x_3(2, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    }
    if (mActor->getASList()->x_7(1, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
    mActor->get548()->m8()->m10(0, false);
}

void PlayerIce::loadParams_() {
    getStaticParam(&mEnergyIce_s, "EnergyIce");
    getStaticParam(&mCountRate_s, "CountRate");
    getStaticParam(&mInputInterval_s, "InputInterval");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedFBlowOff_s, "JumpSpeedFBlowOff");
    getStaticParam(&mJumpHeightBlowOff_s, "JumpHeightBlowOff");
}

void PlayerIce::calc_() {
    PlayerAction::calc_();
}

bool PlayerIce::isChangeable() const {
    return false;
}

}  // namespace uking::action
