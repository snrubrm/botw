#include "Game/AI/AI/aiAncientNecklaceBall.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

AncientNecklaceBall::AncientNecklaceBall(const InitArg& arg) : AncientNecklaceBallBase(arg) {}

AncientNecklaceBall::~AncientNecklaceBall() = default;

bool AncientNecklaceBall::init_(sead::Heap* heap) {
    if (!AncientNecklaceBallBase::init_(heap))
        return false;

    if (auto* body = mActor->getMainBody())
        _12c = body->getMaxAngularVelocity();
    _140._18.y(mActor);
    return true;
}

void AncientNecklaceBall::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mGiantNecklaceActiveSaveFlag_m.isEmpty())
        ksys::gdt::setBoolByKey(true, mGiantNecklaceActiveSaveFlag_m);
    _120 = ksys::Timer(1.0f, 1.0f, 0.0f);
    AncientNecklaceBallBase::enter_(params);
}

void AncientNecklaceBall::leave_() {
    AncientNecklaceBallBase::leave_();
}

void AncientNecklaceBall::loadParams_() {
    AncientNecklaceBallBase::loadParams_();
    getStaticParam(&mLandNoiseLevel_s, "LandNoiseLevel");
    getMapUnitParam(&mGrabNodeIndex_m, "GrabNodeIndex");
    getMapUnitParam(&mGiantNecklaceActiveSaveFlag_m, "GiantNecklaceActiveSaveFlag");
}

bool AncientNecklaceBall::handleMessage_(const ksys::Message* message) {
    if (_170.m2(*message))
        return true;
    return AncientNecklaceBallBase::handleMessage_(message);
}

bool AncientNecklaceBall::m36() {
    if (SimpleLiftable::m36())
        return true;
    return isCurrentChild("吊るす");
}

}  // namespace uking::ai

// Defined in this TU in the original (inlined into AncientNecklaceBall::handleMessage_).
bool Unk_71023d4c08::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000ab)
        return false;

    auto* payload = static_cast<Unk_71023d4bb0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}
