#include "Game/AI/Action/actionAreaActorObserve.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

AreaActorObserve::AreaActorObserve(const InitArg& arg) : AreaTagAction(arg) {}

AreaActorObserve::~AreaActorObserve() {
    _50.freeBuffer();
}

bool AreaActorObserve::init_(sead::Heap* heap) {
    _50.tryAllocBuffer(7, heap);
    if (!_50.isBufferReady())
        return false;
    _50[0]._0 = 32;
    _50[1]._0 = 33;
    _50[2]._0 = 35;
    _50[4]._0 = 37;
    _50[3]._0 = 36;
    _50[5]._0 = 41;
    _50[6]._0 = 39;
    return true;
}

void AreaActorObserve::loadParams_() {
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mIsSendMessage_m, "IsSendMessage");
    getMapUnitParam(&mDefaultBasicSignal_m, "DefaultBasicSignal");
    m32();
}

void AreaActorObserve::m32() {}

// NON_MATCHING: stack slot of the MessageType temporary
bool AreaActorObserve::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    if (m37(accessor)) {
        ++_34;
        if (*mIsSendMessage_m)
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000009), nullptr);
    }

    if (*mIsSendMessage_m)
        return false;
    return *mCount_m <= _34;
}

bool AreaActorObserve::m37(const ksys::act::ActorConstDataAccess& accessor) {
    return false;
}

}  // namespace uking::action
