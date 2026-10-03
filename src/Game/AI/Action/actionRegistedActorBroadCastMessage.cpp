#include "Game/AI/Action/actionRegistedActorBroadCastMessage.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

RegistedActorBroadCastMessage::RegistedActorBroadCastMessage(const InitArg& arg)
    : RegistedActorActionBase(arg) {}

RegistedActorBroadCastMessage::~RegistedActorBroadCastMessage() = default;

bool RegistedActorBroadCastMessage::init_(sead::Heap* heap) {
    return RegistedActorActionBase::init_(heap);
}

void RegistedActorBroadCastMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorActionBase::enter_(params);
}

void RegistedActorBroadCastMessage::leave_() {
    RegistedActorActionBase::leave_();
}

void RegistedActorBroadCastMessage::loadParams_() {
    RegistedActorActionBase::loadParams_();
}

void RegistedActorBroadCastMessage::calc_() {
    RegistedActorActionBase::calc_();
}

bool RegistedActorBroadCastMessage::handleMessage_(const ksys::Message* message) {
    if (RegistedActorActionBase::handleMessage_(message))
        return true;

    for (auto& entry : _20.mEntries) {
        if (!entry.link.hasProc())
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&entry.link, &accessor);
        const auto& source = message->getSource();
        const auto* id = accessor.getMessageTransceiverId();
        if (source.queue_id != id->queue_id || source.id != id->id) {
            ksys::MessageTransceiverBase& transceiver = mActor->getMessageTransceiver();
            transceiver.sendMessageOnProcessingThread(*accessor.getMessageTransceiverId(),
                                                      message->getType(), message->getUserData(),
                                                      true);
        }
    }
    return true;
}

}  // namespace uking::action
