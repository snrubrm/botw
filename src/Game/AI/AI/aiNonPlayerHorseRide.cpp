#include "Game/AI/AI/aiNonPlayerHorseRide.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

NonPlayerHorseRide::NonPlayerHorseRide(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NonPlayerHorseRide::~NonPlayerHorseRide() = default;

bool NonPlayerHorseRide::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NonPlayerHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NonPlayerHorseRide::leave_() {
    auto* actor = mActor;
    auto* map_object = actor->getMapObject();
    if (actor->get1a0() ||
        (map_object && map_object->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) ||
        testRootAiFlag(ksys::act::ai::RootAiFlag::_5)) {
        if (auto* ride_actor = act::getRideActor(actor)) {
            if (auto* rideable = ride_actor->getMotorcyclePriorityStuffMaybe())
                rideable->_10.setBitOn(Bit(Bit::_1));
        }
        return;
    }
    m34();
}

void NonPlayerHorseRide::m34() {
    auto* actor = mActor;
    if (auto* info = actor->getPlayerRideInfo())
        info->sub_7100E7C0EC();
    if (m35())
        actor->sub_71011DA834(&_38);
}

void NonPlayerHorseRide::calc_() {
    if (++_d8 < 2)
        return;
    auto* ride_actor = act::getRideActor(mActor);
    if (!ride_actor)
        return;
    if (int(act::Unk_7100e8b2b8::Unk8(ride_actor->getMotorcyclePriorityStuffMaybe()->_8 & 0xff)) ==
        act::Unk_7100e8b2b8::Unk8::_0) {
        setFailed();
        return;
    }
    auto* child = getCurrentChild();
    if (child->isFinished()) {
        setFinished();
        return;
    }
    if (child->isFailed())
        setFailed();
}

void NonPlayerHorseRide::loadParams_() {}

bool NonPlayerHorseRide::m35() {
    return true;
}

void NonPlayerHorseRide::m36() {
    changeChild("乗る");
}

}  // namespace uking::ai
