#include "Game/AI/Action/actionSwarmDamagedBase.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_710072A944.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SwarmDamagedBase::SwarmDamagedBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwarmDamagedBase::~SwarmDamagedBase() = default;

bool SwarmDamagedBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwarmDamagedBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm) {
        setFailed();
        return;
    }
    if (auto* controller = swarm->getCharacterController()) {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        const f32 min_speed = *mRiseSpeedMin_s * 30.0f;
        if (velocity.y < min_speed)
            velocity.y = min_speed;
        controller->sub_7100F5F6FC(velocity);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    for (int i = 0; i < swarm->_14c8.size(); ++i) {
        if (auto* unit = swarm->_14c8[i])
            unit->_5c = sead::GlobalRandom::instance()->getF32Range(*mSubAccRateMin_s,
                                                                    *mSubAccRateMax_s);
    }
    _68 = sead::Vector3f(0.0f, 0.0f, 1.0f);
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
