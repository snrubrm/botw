#include "Game/AI/AI/aiMetalObjectBuried.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

MetalObjectBuried::MetalObjectBuried(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MetalObjectBuried::~MetalObjectBuried() = default;

bool MetalObjectBuried::init_(sead::Heap* heap) {
    _72 = false;
    return true;
}

void MetalObjectBuried::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _74 = 0;
    if (!actor->getMapObject())
        _72 = false;

    if (*mIsInGround_m && !_72) {
        sub_71004A5514();
        return;
    }

    ksys::act::enableAllAttClients(actor);
    if (*mIsInGround_m) {
        if (auto* physics = actor->getPhysics())
            physics->sub_7100FBADDC();
    }
    _70 = true;
    _71 = false;
    _72 = true;
    changeChild("地上");
}

void MetalObjectBuried::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MetalObjectBuried::loadParams_() {
    getStaticParam(&mPullOutSpeed_s, "PullOutSpeed");
    getStaticParam(&mCheckGroundRadiusScale_s, "CheckGroundRadiusScale");
    getStaticParam(&mIsIgnoreResistanceArea_s, "IsIgnoreResistanceArea");
    getStaticParam(&mIsCheckGrabYPosFix_s, "IsCheckGrabYPosFix");
    getStaticParam(&mIsCheckSelfY_s, "IsCheckSelfY");
    getMapUnitParam(&mIsInGround_m, "IsInGround");
    getMapUnitParam(&mEnableRevival_m, "EnableRevival");
}

bool MetalObjectBuried::handleMessage_(const ksys::Message& message) {
    if (message.getType().value != 0x3000007)
        return false;

    auto* actor = mActor;
    if (*mEnableRevival_m)
        actor->becomePreActor(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
    else
        actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    return true;
}

void MetalObjectBuried::sub_71004A5514() {
    auto* actor = mActor;
    ksys::act::disableAllAttClients(actor);
    if (auto* body = actor->getMainBody()) {
        body->changeMotionType(ksys::phys::MotionType::Keyframed);
        sead::BoundBox3f box;
        body->getAabbInLocal(&box);
        _74 = (box.getMax() - box.getMin()).length() * 0.5f;
    }
    _70 = false;
    _71 = false;
    changeChild("地中");
}

}  // namespace uking::ai
