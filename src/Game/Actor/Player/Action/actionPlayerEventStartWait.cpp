#include "Game/Actor/Player/Action/actionPlayerEventStartWait.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtEvent.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerEventStartWait::PlayerEventStartWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerEventStartWait::~PlayerEventStartWait() = default;

void PlayerEventStartWait::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool was_squat_wait = static_cast<ksys::act::Player*>(mActor)->_cec.isOnBit(2);
    const bool was_swim_wait = static_cast<ksys::act::Player*>(mActor)->_cec.isOnBit(10);
    PlayerAction::enter_(params);

    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x40);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f1 =
        static_cast<ksys::act::Player*>(mActor)->_1cb0 == 0x12;
    _1c = false;

    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F6FC(sead::Vector3f::zero);

    if (was_squat_wait) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SquatWait", true, -1.0f);
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x4);
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd8);
        mActor->get548()->m8()->m10(0, true);
    } else if (was_swim_wait) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWait", true, -1.0f);
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
        static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);
    } else if (static_cast<ksys::act::Player*>(mActor)->x_48()) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("MotorcycleWait", true,
                                                                          -1.0f);
    } else if (static_cast<ksys::act::Player*>(mActor)->isRidingHorse()) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("HorseWait", true, -1.0f);
    } else if (static_cast<ksys::act::Player*>(mActor)->x_44()) {
        if (!(mActor->getASList()->x_1(0, 0) == "StaminaOut"))
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("StaminaOut", true,
                                                                              -1.0f);
    } else {
        static_cast<ksys::act::Player*>(mActor)->sub_7100878110();
    }

    _20 = 0.0f;
    ksys::evt::Manager::instance()->_1d2f4 |= 1u;
}
void PlayerEventStartWait::leave_() {
    if (static_cast<ksys::act::Player*>(mActor)->m199()) {
        auto* event = ksys::evt::Manager::instance()->getActiveEvent();
        if (!event || !event->hasFlag(ksys::evt::Event::Flag::_100000000)) {
            if (auto* controller = mActor->getCharacterController())
                controller->sub_7100F5F270(static_cast<ksys::act::Player*>(mActor)->_1cd4);
            mActor->get548()->m8()->m10(0, false);
        }
    }
    ksys::evt::Manager::instance()->_1d2f4 &= ~1u;
}

// NON_MATCHING: the original loads _17f0 before testing _1a0 / the map object flag and keeps the result in
// branches
void PlayerEventStartWait::calc_() {
    static_cast<ksys::act::Player*>(mActor)->setCE0Locked(0x4000);
    static_cast<ksys::act::Player*>(mActor)->actionCommon();

    if (mActor->get1a0() || (mActor->getMapObject() &&
                             mActor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
        if (!(mActor->getASList()->x_1(0, 0) == "DemoWait") &&
            !static_cast<ksys::act::Player*>(mActor)->isRidingHorse() &&
            !static_cast<ksys::act::Player*>(mActor)->m199()) {
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true, -1.0f);
        }
    }

    if (mActor->getASList()->x_1(0, 0) == "StaminaOut" &&
        !static_cast<ksys::act::Player*>(mActor)->x_44()) {
        if (static_cast<ksys::act::Player*>(mActor)->m199())
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SquatWait", true, -1.0f);
        else
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Wait", true, -1.0f);
    }

    if (_20 >= 3.0f && !ksys::evt::Manager::instance()->_1d2b8) {
        setFailed();
        _1c = true;
    }
    _20 += 1.0f;

    auto* player = static_cast<ksys::act::Player*>(mActor);
    const bool in_event =
        player->get1a0() || (player->getMapObject() &&
                             player->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000));
    if (!player->_17f0) {
        if (in_event)
            player->_17f0 = true;
    } else if (!in_event) {
        setFailed();
        _1c = true;
    }
}

bool PlayerEventStartWait::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
