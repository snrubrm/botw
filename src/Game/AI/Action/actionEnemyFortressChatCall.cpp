#include "Game/AI/Action/actionEnemyFortressChatCall.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::action {

EnemyFortressChatCall::EnemyFortressChatCall(const InitArg& arg)
    : EnemyFortressChatTalk(arg), _f0(mActor, 0x800009c) {}

EnemyFortressChatCall::~EnemyFortressChatCall() = default;

bool EnemyFortressChatCall::init_(sead::Heap* heap) {
    if (!EnemyFortressChatTalk::init_(heap))
        return false;
    _f0.x(mActor);
    return true;
}

void EnemyFortressChatCall::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyFortressChatTalk::enter_(params);
}

void EnemyFortressChatCall::leave_() {
    EnemyFortressChatTalk::leave_();
}

void EnemyFortressChatCall::loadParams_() {
    EnemyFortressChatTalk::loadParams_();
}

void EnemyFortressChatCall::calc_() {
    EnemyFortressChatTalk::calc_();
}

void EnemyFortressChatCall::m32() {
    auto& link = sub_7100108DA4();
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_f0._28);
        _f0._18 = link;
    }
    _f0.sub_710070DCC0(mTargetActor_d, true);
}

// NON_MATCHING: register allocation only (the original rematerialises &accessor, `mov w20, wzr` is hoisted
// above the type check).
bool EnemyFortressChatCall::m33(const ksys::MessageAck* ack) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    bool result = false;
    if (ack->getType() == 0x800009c) {
        const auto& dest = ack->getDestination();
        const auto* id = accessor.getMessageTransceiverId();
        result = dest.queue_id == id->queue_id && dest.id == id->id;
    }
    return result;
}

}  // namespace uking::action
