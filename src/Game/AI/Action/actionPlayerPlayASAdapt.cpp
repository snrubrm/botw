#include "Game/AI/Action/actionPlayerPlayASAdapt.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

PlayerPlayASAdapt::PlayerPlayASAdapt(const InitArg& arg) : PlayASForDemo(arg) {}

PlayerPlayASAdapt::~PlayerPlayASAdapt() = default;

void PlayerPlayASAdapt::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool is_swimming = static_cast<ksys::act::Player*>(mActor)->m188();
    const bool is_m186 = static_cast<ksys::act::Player*>(mActor)->m186();
    auto* actor = mActor;
    const bool had_cf4_bit1 = static_cast<ksys::act::Player*>(actor)->_cf4.isOnBit(1);
    bool is_special = false;
    bool in_event = actor->get1a0() != nullptr;
    if (!in_event) {
        auto* obj = actor->getMapObject();
        in_event = obj && obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000);
    }
    if (in_event)
        is_special = static_cast<ksys::act::Player*>(mActor)->m199();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_cf4.makeAllZero();
    player->_cf8.makeAllZero();
    player->_cec.makeAllZero();
    player->_cf0.makeAllZero();
    static_cast<ksys::act::Player*>(mActor)->_ce8 = 0;
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(0);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(2);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(9);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(6);
    if (is_swimming)
        static_cast<ksys::act::Player*>(mActor)->_cec.setBit(10);
    if (is_m186)
        static_cast<ksys::act::Player*>(mActor)->_cec.setBit(7);
    if (had_cf4_bit1)
        static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(1);
    if (is_special)
        static_cast<ksys::act::Player*>(mActor)->_cec.setBit(2);
    player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f1 = false;
    static_cast<ksys::act::Player*>(mActor)->_1800 = 0;
    mActor->getASList()->x_6(12, 0, static_cast<ksys::act::Player*>(mActor)->_1fbc);
    PlayASForDemo::enter_(params);
}

void PlayerPlayASAdapt::leave_() {
    PlayASForDemo::leave_();
}

void PlayerPlayASAdapt::loadParams_() {
    PlayASForDemo::loadParams_();
    getDynamicParam(&mIsOneTimeEndKeep_d, "IsOneTimeEndKeep");
    getDynamicParam(&mNoErrorCheck_d, "NoErrorCheck");
}

void PlayerPlayASAdapt::calc_() {
    PlayASForDemo::calc_();
}

bool PlayerPlayASAdapt::isChangeable() const {
    return false;
}

}  // namespace uking::action
