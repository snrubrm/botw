#include "Game/AI/Action/actionSwarmDamagedBase.h"
#include "Game/AI/aiUnk_710072A944.h"

namespace uking::action {

SwarmDamagedBase::SwarmDamagedBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwarmDamagedBase::~SwarmDamagedBase() = default;

bool SwarmDamagedBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwarmDamagedBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwarmDamagedBase::leave_() {
    ksys::act::ai::Action::leave_();
}

bool SwarmDamagedBase::sub_7100284D00(void* ptr) const {
    for (const Entry& entry : _78) {
        if (entry.mPtr == ptr)
            return true;
    }
    return false;
}

void SwarmDamagedBase::loadParams_() {
    getStaticParam(&mIgnoreHitGroundTime_s, "IgnoreHitGroundTime");
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mRiseSpeedMin_s, "RiseSpeedMin");
    getStaticParam(&mSubAccRateMin_s, "SubAccRateMin");
    getStaticParam(&mSubAccRateMax_s, "SubAccRateMax");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mIsCreateDeadActor_s, "IsCreateDeadActor");
    getMapUnitParam(&mSubUnitNum_m, "SubUnitNum");
    getMapUnitParam(&mPatternID_m, "PatternID");
}

void SwarmDamagedBase::calc_() {
    ksys::act::ai::Action::calc_();
}

void SwarmDamagedBase::m32(act::Swarm* swarm) {
    // The result is discarded.
    sub_7100729D5C(*mSpeed_s, swarm, nullptr, nullptr, nullptr, false);
    sub_710072A108(swarm, sead::Vector3f::ey);
}

}  // namespace uking::action
