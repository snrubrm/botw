#include "Game/AI/Action/actionAreaHorseSpeedLimitAction.h"
#include "Game/Actor/actHorseBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

AreaHorseSpeedLimitAction::AreaHorseSpeedLimitAction(const InitArg& arg) : AreaTagAction(arg) {}

AreaHorseSpeedLimitAction::~AreaHorseSpeedLimitAction() {
    _38.freeBuffer();
}

bool AreaHorseSpeedLimitAction::init_(sead::Heap* heap) {
    _38.tryAllocBuffer(2, heap);
    if (!_38.isBufferReady())
        return false;
    _38[0]._0 = ksys::phys::ContactLayer::SensorEnemy;
    _38[1]._0 = ksys::phys::ContactLayer::SensorHorse;
    return true;
}

// NON_MATCHING: stack slot of the MessageType temporary
bool AreaHorseSpeedLimitAction::m15(const ksys::act::ActorConstDataAccess& accessor) {
    ksys::act::ActorConstDataAccess horse;
    horse.acquireActor(accessor);
    if (act::sub_7100E6DC50(horse))
        sendMessage(*horse.getMessageTransceiverId(), ksys::MessageType(0x3800014), nullptr);
    return false;
}

}  // namespace uking::action
