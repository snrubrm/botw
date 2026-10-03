#include "Game/AI/Action/actionShelterFromRain.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::action {

ShelterFromRain::ShelterFromRain(const InitArg& arg) : AreaTagAction(arg) {}

ShelterFromRain::~ShelterFromRain() {
    _40.freeBuffer();
}

bool ShelterFromRain::init_(sead::Heap* heap) {
    _40.tryAllocBuffer(1, heap);
    _40[0]._0 = ksys::phys::ContactLayer::SensorNPC;
    return true;
}

void ShelterFromRain::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void ShelterFromRain::leave_() {
    AreaTagAction::leave_();
}

void ShelterFromRain::loadParams_() {
    getMapUnitParam(&mShelterFromRainTagType_m, "ShelterFromRainTagType");
}

void ShelterFromRain::calc_() {
    AreaTagAction::calc_();
    _51 = false;
}

// NON_MATCHING: the original checks the message reference for null
bool ShelterFromRain::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x8000076) {
        _50 = false;
        return true;
    }
    return false;
}

// NON_MATCHING: the original checks the ack reference for null
bool ShelterFromRain::handleAck_(const ksys::MessageAck* ack) {
    if (ack->getType() == 0x8000075 && ack->isDestinationValid() && ack->isSuccess()) {
        _50 = true;
        return true;
    }
    return false;
}

bool ShelterFromRain::m15(const ksys::act::ActorConstDataAccess& accessor) {
    ksys::act::BaseProcLink link;
    ksys::act::ActorConstDataAccess npc;
    if (!accessor.linkAcquire(&link) || !ksys::act::acquireActor(&link, &npc))
        return false;

    if (_50 || _51 || !npc.isNPCProfile() || npc.sub_7100023358())
        return false;

    const bool flag = npc.sub_7100D12E64();
    switch (*mShelterFromRainTagType_m) {
    case 0:
        break;
    case 1:
        if (flag)
            return false;
        break;
    case 2:
        if (!flag)
            return false;
        break;
    default:
        return false;
    }

    _51 = true;
    _54 = mActor->getMtx();
    sendMessage(*npc.getMessageTransceiverId(), ksys::MessageType(0x8000075), &_54);
    return false;
}

}  // namespace uking::action
