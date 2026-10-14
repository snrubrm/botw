#include "Game/Actor/Action/actionMsg2CameraResetNoConnect.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

Msg2CameraResetNoConnect::Msg2CameraResetNoConnect(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

bool Msg2CameraResetNoConnect::oneShot_() {
    ksys::act::ActorLinkConstDataAccess accessor;
    getRoot6SomeActor(&accessor);
    sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8800009), nullptr);
    return true;
}

}  // namespace uking::action
