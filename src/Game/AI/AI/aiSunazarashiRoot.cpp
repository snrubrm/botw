#include "Game/AI/AI/aiSunazarashiRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

SunazarashiRoot::SunazarashiRoot(const InitArg& arg) : PreyRoot(arg) {}

SunazarashiRoot::~SunazarashiRoot() = default;

bool SunazarashiRoot::init_(sead::Heap* heap) {
    if (!PreyRoot::init_(heap))
        return false;

    if (auto* physics = mActor->getPhysics()) {
        if (auto* cloth = physics->getClothSet())
            cloth->_70 |= 0x10000;
    }
    if (*mForbidSystemDeleteDistance_m)
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    return true;
}

void SunazarashiRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (*mEnableHangAlways_s)
        ksys::act::enableAttClient(actor, "Hang");
    else
        ksys::act::disableAttClient(actor, "Hang");

    if (auto* controller = mActor->getCharacterController())
        controller->mFlags.set(0x10);

    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    *mSunazarashiReturnPos_a = pos;
    _290 = 0.0f;
    _294 = 0.0f;
    _298 = 1.0f;
    _29c = 150.0f;
    _2a0 = 10.0f;
    PreyRoot::enter_(params);
}

void SunazarashiRoot::leave_() {
    PreyRoot::leave_();
}

void SunazarashiRoot::loadParams_() {
    PreyRoot::loadParams_();
    getStaticParam(&mStunNoiseLevel_s, "StunNoiseLevel");
    getStaticParam(&mClashSpeed_s, "ClashSpeed");
    getStaticParam(&mClashAngle_s, "ClashAngle");
    getStaticParam(&mEnableHangAlways_s, "EnableHangAlways");
    getMapUnitParam(&mForbidSystemDeleteDistance_m, "ForbidSystemDeleteDistance");
    getAITreeVariable(&mSunazarashiReturnPos_a, "SunazarashiReturnPos");
}

bool SunazarashiRoot::handleMessage_(const ksys::Message& message) {
    if (!isCurrentChild("牽引")) {
        if (_238._30)
            return false;
        if (_238.m2(message))
            return true;
    }
    return PreyRoot::handleMessage_(message);
}

}  // namespace uking::ai
