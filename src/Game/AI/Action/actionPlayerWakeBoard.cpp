#include "Game/AI/Action/actionPlayerWakeBoard.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtEventFlow.h"

namespace uking::action {

PlayerWakeBoard::PlayerWakeBoard(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWakeBoard::enter_(ksys::act::ai::InlineParamPack* params) {
    const u32 previous_cec = static_cast<ksys::act::Player*>(mActor)->_cec.getDirect();
    const bool previous_cf0 = static_cast<ksys::act::Player*>(mActor)->_cf0.isOn(0x800000);
    PlayerAction::enter_(params);
    if (previous_cec & 0x20000)
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20000);
    if (previous_cf0)
        static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x800000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80000000);
    if (mActor->getASList()->x_7(1, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    if (!mActor->getConnectedCalcChild()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&static_cast<ksys::act::Player*>(mActor)->_2c38, &accessor);
        accessor.setThisActorAsChild(mActor, false);
        static_cast<ksys::act::Player*>(mActor)->_1870->_c0->_8 = mActor;
    }
    if (auto* controller = mActor->getCharacterController()) {
        sead::Matrix34f unused;
        controller->physicsXXXGetMtx_1(&unused);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    _1d = false;
    auto* surfing = static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->_c0;
    if (surfing && !surfing->_60.isOn(1))
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("WakeBoardOn", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
}

void PlayerWakeBoard::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    if (auto* event = ksys::evt::Manager::instance()->getActiveEvent()) {
        if (s32(event->_340) < 0 && mActor->getASList()->x_1(0, 0) != "WakeBoardingNG")
            return;
    }
    auto* surfing = static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->_c0;
    if (surfing)
        surfing->sub_7100EBB518();
    mActor->resetConnectedCalcChild(false);
    static_cast<ksys::act::Player*>(mActor)->someFloatCalc(2.0f, {0, 1, 0});
    static_cast<ksys::act::Player*>(mActor)->sub_710088A854();
}

void PlayerWakeBoard::loadParams_() {}

bool PlayerWakeBoard::handleMessage_(const ksys::Message* message) {
    const auto type = message->getType();
    if (type == 0x8000025 || type == 0x8000026) {
        _1d = true;
        return true;
    }
    return false;
}

void PlayerWakeBoard::calc_() {
    PlayerAction::calc_();
}

bool PlayerWakeBoard::isChangeable() const {
    return false;
}

}  // namespace uking::action
