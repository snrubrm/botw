#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

PlayerAction::PlayerAction(const InitArg& arg) : ActionEx(arg) {}

void PlayerAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
    auto* actor = mActor;
    bool in_event = actor->get1a0() != nullptr;
    if (!in_event) {
        auto* obj = actor->getMapObject();
        in_event = obj && obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000);
    }
    if (in_event) {
        const bool is_special = static_cast<ksys::act::Player*>(actor)->m199();
        auto* player = static_cast<ksys::act::Player*>(mActor);
        player->_cf4.makeAllZero();
        player->_cf8.makeAllZero();
        player->_cec.makeAllZero();
        player->_cf0.makeAllZero();
        static_cast<ksys::act::Player*>(mActor)->_ce8 = 0;
        if (is_special)
            static_cast<ksys::act::Player*>(mActor)->_cec.set(4);
    } else {
        static_cast<ksys::act::Player*>(actor)->_cf4.makeAllZero();
        static_cast<ksys::act::Player*>(actor)->_cf8.makeAllZero();
        static_cast<ksys::act::Player*>(actor)->_cec.makeAllZero();
        static_cast<ksys::act::Player*>(actor)->_cf0.makeAllZero();
        static_cast<ksys::act::Player*>(mActor)->_ce8 = 0;
    }
    static_cast<ksys::act::Player*>(mActor)->sub_710085ECF4();
}

void PlayerAction::leave_() {
    ActionEx::leave_();
}

void PlayerAction::calc_() {
    ActionEx::calc_();
}

bool PlayerAction::m32() {
    if (mActor->getASList()->x_4(0, 0)) {
        setFinished();
        return true;
    }
    if (mActor->getASList()->x(2, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
        _1c = true;
        return true;
    }
    return false;
}

}  // namespace uking::action
