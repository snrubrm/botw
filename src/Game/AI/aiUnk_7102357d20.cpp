#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

bool Unk_7102357d20::sub_710070DC38(ksys::act::Actor* actor, bool ack) {
    const auto* dest = actor->getMesTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessage(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DCC0(ksys::act::BaseProcLink* link, bool ack) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return sub_710070DD78(accessor, ack);
}

bool Unk_7102357d20::sub_710070DD78(const ksys::act::ActorLinkConstDataAccess& accessor,
                                    bool ack) {
    const auto* dest = accessor.getMessageTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessage(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DE10(const ksys::MesTransceiverId& dest, bool ack) {
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessageOnProcessingThread(dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DE98(ksys::act::Actor* actor, bool ack) {
    const auto* dest = actor->getMesTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessageOnProcessingThread(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DF20(ksys::act::BaseProcLink* link, bool ack) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return sub_710070DFD8(accessor, ack);
}

bool Unk_7102357d20::sub_710070DFD8(const ksys::act::ActorLinkConstDataAccess& accessor,
                                    bool ack) {
    const auto* dest = accessor.getMessageTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessageOnProcessingThread(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070E070(const ksys::MessageAck& ack) {
    if (ack.getType().value != _10.value || ack.getUserData() != m2())
        return false;
    _14 = ack.isDestinationValid() && ack.isSuccess();
    return true;
}
