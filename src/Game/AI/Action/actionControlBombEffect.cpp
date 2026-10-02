#include "Game/AI/Action/actionControlBombEffect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

ControlBombEffect::ControlBombEffect(const InitArg& arg) : AreaTagAction(arg) {}

ControlBombEffect::~ControlBombEffect() {
    _38.freeBuffer();
}

bool ControlBombEffect::init_(sead::Heap* heap) {
    _38.tryAllocBuffer(1, heap);
    if (!_38.isBufferReady())
        return false;
    _38[0]._0 = 32;
    return true;
}

void ControlBombEffect::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void ControlBombEffect::leave_() {
    AreaTagAction::leave_();
}

void ControlBombEffect::loadParams_() {}

void ControlBombEffect::calc_() {
    AreaTagAction::calc_();
}

// NON_MATCHING: stack slot of the MessageType temporary
bool ControlBombEffect::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (accessor.hasProc())
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800000b), nullptr,
                            true);
    return false;
}

}  // namespace uking::action
