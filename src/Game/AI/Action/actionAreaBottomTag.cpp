#include "Game/AI/Action/actionAreaBottomTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

AreaBottomTag::AreaBottomTag(const InitArg& arg) : AreaTagAction(arg) {}

AreaBottomTag::~AreaBottomTag() {
    _38.freeBuffer();
}

bool AreaBottomTag::init_(sead::Heap* heap) {
    _38.tryAllocBuffer(7, heap);
    if (!_38.isBufferReady())
        return false;
    _38[0]._0 = ksys::phys::ContactLayer::SensorObject;
    _38[1]._0 = ksys::phys::ContactLayer::SensorSmallObject;
    _38[2]._0 = ksys::phys::ContactLayer::SensorPlayer;
    _38[3]._0 = ksys::phys::ContactLayer::SensorEnemy;
    _38[5]._0 = ksys::phys::ContactLayer::SensorHorse;
    _38[4]._0 = ksys::phys::ContactLayer::SensorNPC;
    _38[6]._0 = ksys::phys::ContactLayer::SensorQueryOnly;
    return true;
}

void AreaBottomTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void AreaBottomTag::leave_() {
    AreaTagAction::leave_();
}

void AreaBottomTag::loadParams_() {}

void AreaBottomTag::calc_() {
    AreaTagAction::calc_();
}

bool AreaBottomTag::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (accessor.hasProc()) {
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000007),
                            nullptr, true);
    }
    return false;
}

bool AreaBottomTag::m16(ksys::phys::RigidBody* body) {
    if (ActorObserver::m16(body))
        return true;
    if (!body)
        return true;

    switch (body->getContactLayer()) {
    case ksys::phys::ContactLayer::SensorQueryOnly:
        break;
    default:
        return false;
    }

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::getCollidedActorMaybe(&accessor, body);
    if (!accessor.hasProc())
        return true;
    return !accessor.isWeaponProfile();
}

}  // namespace uking::action
