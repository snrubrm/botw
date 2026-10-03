#include "Game/AI/Action/actionGuardianStopWait.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GuardianStopWait::GuardianStopWait(const InitArg& arg) : GuardianMoveTo(arg) {}

GuardianStopWait::~GuardianStopWait() = default;

bool GuardianStopWait::init_(sead::Heap* heap) {
    return GuardianMoveTo::init_(heap);
}

void GuardianStopWait::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMoveTo::enter_(params);
    if (auto* guardian = sub_7100192824())
        guardian->sub_7100035A90(1);
}

void GuardianStopWait::leave_() {
    GuardianMoveTo::leave_();
    if (auto* guardian = sub_7100192824())
        guardian->sub_7100035A90(0);
}

void GuardianStopWait::loadParams_() {
    GuardianMoveTo::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
    getDynamicParam(&mDynStopPos_d, "DynStopPos");
}

void GuardianStopWait::calc_() {
    GuardianMoveTo::calc_();
    auto* guardian = sub_7100192824();
    if (!guardian) {
        setFailed();
        return;
    }
    if (*mDynStopTime_d <= guardian->_14dc)
        setFinished();
}

// NON_MATCHING: regalloc only (the original keeps x/z of the direction in s10/s8; ours s8/s10).
void GuardianStopWait::m0(Data* data, ksys::act::Actor* actor) {
    sead::Vector3f dir = *mDynStopPos_d;
    dir -= mActor->getMtx().getTranslation();
    const f32 len = dir.normalize();
    data->_0 = dir;
    data->_c = dir;
    data->_18 = sead::Mathf::min(*mSpeed_s, len);
}

}  // namespace uking::action
