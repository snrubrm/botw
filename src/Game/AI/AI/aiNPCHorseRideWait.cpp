#include "Game/AI/AI/aiNPCHorseRideWait.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

NPCHorseRideWait::NPCHorseRideWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCHorseRideWait::~NPCHorseRideWait() = default;

bool NPCHorseRideWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCHorseRideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: same control flow; stack layout / register allocation only (the original keeps the
// MessageType temporary at sp+4 below the accessor and rematerialises &accessor for the destructor)
void NPCHorseRideWait::leave_() {
    auto* actor = mActor;
    if (!actor->get1a0()) {
        auto* object = actor->getMapObject();
        if (!(object && object->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) &&
            !testRootAiFlag(ksys::act::ai::RootAiFlag::_5)) {
            if (auto* schedule = actor->getSchedule())
                schedule->_88 = "";
            return;
        }
    }

    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&actor->getPlayerRideInfo()->_18, &accessor)) {
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800007),
                            mActor, true);
    }
}

bool NPCHorseRideWait::handleMessage_(const ksys::Message* message) {
    if (message && isCurrentChild("移動")) {
        if (message->getType() == 0x3800023) {
            _d8 = true;
            return true;
        }
        if (message->getType() == 0x3800027) {
            _d9 = true;
            return false;
        }
        if (message->getType() == 0x3800028) {
            _d9 = false;
            sub_71004CC76C();
            return true;
        }
    }
    return false;
}

// NON_MATCHING: same as leave_ (the original rematerialises &accessor for each accessor destructor
// instead of keeping it in a callee-saved register; regalloc only)
void NPCHorseRideWait::sub_71004CC76C() {
    if (auto* schedule = mActor->getSchedule())
        schedule->_88 = "";
    _dc = 1;

    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&mActor->getPlayerRideInfo()->_18, &accessor)) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x380000b),
                                reinterpret_cast<void*>(_dc), true);
        }
    }
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&mActor->getPlayerRideInfo()->_18, &accessor)) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800004),
                                &_38, true);
        }
    }

    ksys::act::ai::InlineParamPack params;
    params.addFloat(f32(_dc), "GearSpeed", -1);
    changeChild("移動", &params);
}

void NPCHorseRideWait::loadParams_() {}

}  // namespace uking::ai
