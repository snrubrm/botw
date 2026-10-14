#include "Game/Actor/Player/Action/actionPlayerDrown.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerDrown::PlayerDrown(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDrown::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(10);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(31);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(7);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(8);
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
    if (!static_cast<ksys::act::Player*>(mActor)->x_2())
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimDead", true, -1.0f);
    ksys::eft::searchAndEmitSLink(mActor, "warp", false);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
}

void PlayerDrown::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F6059C();
        controller->sub_7100F5EEB8(1.0f);
    }
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(0x400000);
    static_cast<ksys::act::Player*>(mActor)->_d18 = -1;
}

void PlayerDrown::loadParams_() {}

// NON_MATCHING: argument register setup order of the first ASList::x_3 call.
void PlayerDrown::calc_() {
    if (!static_cast<ksys::act::Player*>(mActor)->x_2())
        static_cast<ksys::act::Player*>(mActor)->actionCommon();

    if (static_cast<ksys::act::Player*>(mActor)->_17f0) {
        setFinished();
        return;
    }

    auto* controller = mActor->getCharacterController();
    if (!sead::DynamicCast<ui::ScreenFadeDemo>(
             eui::ScreenMgr::instance()->getScreen(ui::ScreenId::FadeDemo))
             ->isOpened()) {
        return;
    }

    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(10);
    if (static_cast<ksys::act::Player*>(mActor)->x_2()) {
        static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->sub_7100EB51E0();
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        return;
    }

    static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
    static_cast<ksys::act::Player*>(mActor)->_cec.resetBit(10);
    static_cast<ksys::act::Player*>(mActor)->_c50.setBit(33);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DamageLStand", true, 0.0f);
    auto* actor = mActor;
    actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    static_cast<ksys::act::Player*>(mActor)->sub_710084AE78();
    static_cast<ksys::act::Player*>(mActor)->sub_710086D5B8();
    controller->sub_7100F5EEB8(0.0f);
    setFinished();
}

bool PlayerDrown::isChangeable() const {
    return false;
}

}  // namespace uking::action
