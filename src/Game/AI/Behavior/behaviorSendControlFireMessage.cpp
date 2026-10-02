#include "Game/AI/Behavior/behaviorSendControlFireMessage.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::behavior {

SendControlFireMessage::SendControlFireMessage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SendControlFireMessage::~SendControlFireMessage() = default;

bool SendControlFireMessage::m6(sead::Heap* heap) {
    return true;
}

void SendControlFireMessage::m9() {}

void SendControlFireMessage::loadParams() {
    getStaticParam(&mIsIgnite_s, "IsIgnite");
}

void SendControlFireMessage::m8() {
    if (*mIsIgnite_s)
        return;
    auto* obj = mActor->getMapObject();
    if (!obj)
        return;
    auto* link_data = obj->getLinkData();
    if (!link_data)
        return;
    const int num = link_data->mObjects.size();
    for (int i = 0; i < num; ++i) {
        auto* linked = link_data->mObjects[i];
        if (!linked)
            continue;
        ksys::act::ActorConstDataAccess accessor;
        linked->getActorWithAccessor(accessor);
        if (accessor.hasProc()) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800002c),
                                nullptr, true);
        }
    }
}

// NON_MATCHING: the original keeps &_30 in a register for the value read after update()
void SendControlFireMessage::m7() {
    if (!*mIsIgnite_s)
        return;
    if (mActor->checkBasicSig()) {
        _30 = ksys::Timer(20, 20);
        return;
    }
    _30.update();
    if (!(_30.value <= sead::Mathf::epsilon()))
        return;
    auto* obj = mActor->getMapObject();
    if (!obj)
        return;
    auto* link_data = obj->getLinkData();
    if (!link_data)
        return;
    const int num = link_data->mObjects.size();
    for (int i = 0; i < num; ++i) {
        auto* linked = link_data->mObjects[i];
        if (!linked)
            continue;
        ksys::act::ActorConstDataAccess accessor;
        linked->getActorWithAccessor(accessor);
        if (accessor.hasProc()) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800002b),
                                nullptr, true);
        }
    }
}

}  // namespace uking::behavior
