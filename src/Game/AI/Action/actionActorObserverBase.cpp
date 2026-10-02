#include "Game/AI/Action/actionActorObserverBase.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/Utils/Thread/Message.h"

ActorObserverBase::ActorObserverBase(ksys::act::ai::ActionBase* owner) : mOwner(owner) {}

void ActorObserverBase::sub_7100E28168() {
    enter();
    _10 = false;
}

void ActorObserverBase::enter() {
    ksys::act::ActorConstDataAccess accessor;
    if (getAreaCol(&accessor, -1) < 0 && mOwner) {
        auto* actor = mOwner->getActor();
        if (actor) {
            sead::FixedSafeString<64> name;
            sead::FixedSafeString<64> unique_name;
            ksys::act::getPlacementNameAndUniqueName(mOwner->getActor(), &name, &unique_name);
            const auto& mtx = actor->getMtx();
            sead::FormatFixedSafeString<128> message("このアクタの座標(%f,%f,%f)", mtx(0, 3),
                                                     mtx(1, 3), mtx(2, 3));
        }
    }
}

void ActorObserverBase::sub_7100E282AC() {
    calc();
    m2();
    calc2();
    m5();
}

// NON_MATCHING: stack layout (the MessageType temporary sits above the accessor in the original) and
// register allocation of the accessor address / payload loop counter.
void ActorObserverBase::calc() {
    if (_10 && !_11)
        return;

    if (!mOwner)
        return;

    ksys::act::ActorConstDataAccess accessor;
    for (int idx = getAreaCol(&accessor, -1); idx >= 0; idx = getAreaCol(&accessor, idx)) {
        if (!accessor.hasProc())
            continue;

        auto* payloads = m6();
        if (!payloads)
            continue;

        const auto* id = accessor.getMessageTransceiverId();
        for (auto& payload : *payloads)
            mOwner->sendMessage(*id, ksys::MessageType(0x4800001), &payload);
    }
    _10 = true;
    _11 = false;
}

bool ActorObserverBase::sub_7100E289C0(const ksys::Message* message) {
    if (!message)
        return true;

    if (message->getType() == 0x4800002) {
        _11 = true;
        return true;
    }
    return false;
}

bool ActorObserverBase::m3(const CollisionIterator& it) {
    return false;
}

bool ActorObserverBase::m4(const ContactIterator& it) {
    return false;
}

bool ActorObserverBase::m7(const CollisionIterator& it) {
    return true;
}

bool ActorObserverBase::m8(const ContactIterator& it) {
    return true;
}
