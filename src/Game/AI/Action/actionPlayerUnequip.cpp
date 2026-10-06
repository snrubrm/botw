#include "Game/AI/Action/actionPlayerUnequip.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

PlayerUnequip::PlayerUnequip(const InitArg& arg) : PlayerAction(arg) {}

PlayerUnequip::~PlayerUnequip() = default;

bool PlayerUnequip::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerUnequip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

// NON_MATCHING: same instructions; the original lays out the map-object flag test of the "in event" check
// out of line after the return.
void PlayerUnequip::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x80);
    static_cast<ksys::act::Player*>(mActor)->sub_71008550E4();
    auto* obj = mActor->getMapObject();
    if (mActor->get1a0() || (obj && obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
        if (!mActor->getWeapons()->mWeapons[0]._10) {
            ksys::evt::Manager::instance()->getActiveEvent();
            mActor->getWeapons()->mWeapons[0]._10 = true;
        }
        if (!mActor->getWeapons()->mWeapons[1]._10)
            mActor->getWeapons()->mWeapons[1]._10 = true;
        if (!mActor->getWeapons()->mWeapons[2]._10) {
            ksys::evt::Manager::instance()->getActiveEvent();
            mActor->getWeapons()->mWeapons[2]._10 = true;
        }
        if (!mActor->getWeapons()->mWeapons[3]._10)
            mActor->getWeapons()->mWeapons[3]._10 = true;
    }
    if (static_cast<ksys::act::Player*>(mActor)->isRidingHorse())
        static_cast<ksys::act::Player*>(mActor)->sub_710086FAAC();
}

void PlayerUnequip::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (!static_cast<ksys::act::Player*>(mActor)->x_35()) {
        if (static_cast<ksys::act::Player*>(mActor)->_c40.isOnBit(7)) {
            static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x80);
            static_cast<ksys::act::Player*>(mActor)->sub_71008550E4();
        }
        setFinished();
    }
    if (static_cast<ksys::act::Player*>(mActor)->isRidingHorse())
        static_cast<ksys::act::Player*>(mActor)->sub_710086FAAC();
}

bool PlayerUnequip::isChangeable() const {
    return false;
}

}  // namespace uking::action
