#include "Game/Actor/Player/Action/actionPlayerDemoAirWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerDemoAirWait::PlayerDemoAirWait(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: the original hoists the mActor reload after m187() above the branch.
void PlayerDemoAirWait::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool had_paraglider = static_cast<ksys::act::Player*>(mActor)->m194();
    PlayerAction::enter_(params);
    if (had_paraglider)
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    }
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;

    if (!static_cast<ksys::act::Player*>(mActor)->isShootingBow()) {
        static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
        auto* player = static_cast<ksys::act::Player*>(mActor);
        if (player->_cec.isOnBit(31)) {
            player->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
            player->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
        } else if (player->m187()) {
            if (!(mActor->getASList()->x_1(0, 0) == "LadderWait")) {
                if (mActor->getASList()->x_1(0, 0) == "LadderMove") {
                    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderWait",
                                                                                       true, -1.0f);
                } else {
                    auto* actor = mActor;
                    actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
                    actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
                }
            }
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
        } else {
            auto* proc = static_cast<ksys::act::Player*>(mActor)->mResidentActors[0].getProc(nullptr, nullptr);
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
                actor->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
            if (!static_cast<ksys::act::Player*>(mActor)->m194()) {
                static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000);
                static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ParaEquipOn", true,
                                                                                   -1.0f);
            } else if (!(mActor->getASList()->x_1(0, 0) == "ParashawlGlide") &&
                       !(mActor->getASList()->x_1(0, 0) == "ParaEquipOn")) {
                static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ParashawlGlide",
                                                                                   true, -1.0f);
            }
        }
    }
    setFinished();
}

void PlayerDemoAirWait::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
}

void PlayerDemoAirWait::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (static_cast<ksys::act::Player*>(mActor)->_17f0)
        return;
    if (static_cast<ksys::act::Player*>(mActor)->isShootingBow()) {
        if (mActor->getASList()->x_4(1, 1)) {
            static_cast<ksys::act::Player*>(mActor)->x_18(true);
            auto* proc = static_cast<ksys::act::Player*>(mActor)->mResidentActors[0].getProc(nullptr, nullptr);
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
                actor->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ParaEquipOn", true,
                                                                               -1.0f);
            static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000);
        }
    } else if (mActor->getASList()->x_1(0, 0) == "ParaEquipOn") {
        if (mActor->getASList()->x_4(0, 0))
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ParashawlGlide", true,
                                                                               -1.0f);
    }
}

bool PlayerDemoAirWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
