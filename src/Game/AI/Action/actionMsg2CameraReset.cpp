#include "Game/AI/Action/actionMsg2CameraReset.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

Msg2CameraReset::Msg2CameraReset(const InitArg& arg) : ksys::act::ai::Action(arg) {}

// NON_MATCHING: stack slot of the MessageType temporary (x29-8 vs the original's x29-4; known issue)
bool Msg2CameraReset::oneShot_() {
    ksys::act::ActorConstDataAccess accessor;
    getRoot6SomeActor(&accessor);
    if (accessor.hasProc())
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8800008), nullptr);
    return true;
}

}  // namespace uking::action
