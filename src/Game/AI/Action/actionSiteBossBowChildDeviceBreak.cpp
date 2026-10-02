#include "Game/AI/Action/actionSiteBossBowChildDeviceBreak.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossBowChildDeviceBreak::SiteBossBowChildDeviceBreak(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossBowChildDeviceBreak::~SiteBossBowChildDeviceBreak() = default;

bool SiteBossBowChildDeviceBreak::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossBowChildDeviceBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossBowChildDeviceBreak::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossBowChildDeviceBreak::loadParams_() {
    getStaticParam(&mReactionTime_s, "ReactionTime");
    getStaticParam(&mIsDelete_s, "IsDelete");
}

void SiteBossBowChildDeviceBreak::calc_() {
    _30.update();
    if (_30.value <= sead::Mathf::epsilon()) {
        if (auto* body = mActor->getMainBody())
            body->removeFromWorld();
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        setFinished();
    } else if (_30.value <= 5.0f) {
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D909A4();
    }
}

}  // namespace uking::action
