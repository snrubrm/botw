#include "Game/AI/Action/actionEventDisableContactIdle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

EventDisableContactIdle::EventDisableContactIdle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventDisableContactIdle::~EventDisableContactIdle() {
    if (mContactPointInfo) {
        ksys::phys::ContactPointInfo::free(mContactPointInfo);
        mContactPointInfo = nullptr;
    }
}

bool EventDisableContactIdle::init_(sead::Heap* heap) {
    mContactPointInfo =
        ksys::phys::ContactPointInfo::make(heap, 1, sead::SafeString::cEmptyString, 1, 0, 0);
    if (mContactPointInfo) {
        mContactPointInfo->setContactCallback(&mCallback);
        mContactPointInfo->subscribeAllLayers();
        return true;
    }
    return false;
}

bool EventDisableContactIdle::DisableContactCallback::invoke(
    ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
    const ksys::phys::ContactPointInfo::Event& event) {
    if (event.body) {
        const u32 layer = u32(event.body->getContactLayer());
        if ((1 << (layer & 0x1f)) & mLayerMask) {
            *disable = ksys::phys::ContactPointInfo::ShouldDisableContact::Yes;
            return false;
        }
    }
    return true;
}

void EventDisableContactIdle::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        mOriginalContactPointInfo = body->getContactPointInfo();
        body->setContactPointInfo(mContactPointInfo);
    }
}

void EventDisableContactIdle::leave_() {
    if (auto* body = mActor->getMainBody()) {
        body->setContactPointInfo(mOriginalContactPointInfo);
        mOriginalContactPointInfo = nullptr;
    }
}

void EventDisableContactIdle::loadParams_() {
    getDynamicParam(&mContactType_d, "ContactType");
}

void EventDisableContactIdle::calc_() {
    mFlags.set(Flag::Changeable);
    setFinished();
}

}  // namespace uking::action
