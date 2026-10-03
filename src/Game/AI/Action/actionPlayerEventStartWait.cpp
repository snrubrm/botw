#include "Game/AI/Action/actionPlayerEventStartWait.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtEvent.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerEventStartWait::PlayerEventStartWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerEventStartWait::~PlayerEventStartWait() = default;

void PlayerEventStartWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
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

void PlayerEventStartWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerEventStartWait::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
