#include "Game/AI/Action/actionRegistedActorBroadCastMessage.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

RegistedActorBroadCastMessage::RegistedActorBroadCastMessage(const InitArg& arg)
    : RegistedActorSetActionBase(arg) {}

RegistedActorBroadCastMessage::~RegistedActorBroadCastMessage() = default;

bool RegistedActorBroadCastMessage::init_(sead::Heap* heap) {
    return RegistedActorSetActionBase::init_(heap);
}

void RegistedActorBroadCastMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorSetActionBase::enter_(params);
}

void RegistedActorBroadCastMessage::leave_() {
    RegistedActorSetActionBase::leave_();
}

void RegistedActorBroadCastMessage::loadParams_() {
    RegistedActorSetActionBase::loadParams_();
}

void RegistedActorBroadCastMessage::calc_() {
    RegistedActorSetActionBase::calc_();
}

bool RegistedActorBroadCastMessage::handleMessage_(const ksys::Message* message) {
    if (RegistedActorSetActionBase::handleMessage_(message))
        return true;

    for (auto& entry : _20.mEntries) {
        if (!entry.link.hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
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
