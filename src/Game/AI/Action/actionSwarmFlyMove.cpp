#include "Game/AI/Action/actionSwarmFlyMove.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_710072A944.h"
#include "Game/Actor/actSwarm.h"

namespace uking::action {

SwarmFlyMove::SwarmFlyMove(const InitArg& arg) : FlyMoveBase(arg) {}

SwarmFlyMove::~SwarmFlyMove() = default;

bool SwarmFlyMove::init_(sead::Heap* heap) {
    return FlyMoveBase::init_(heap);
}

void SwarmFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyMoveBase::enter_(params);
    auto* actor = mActor;
    auto* swarm = sead::DynamicCast<act::Swarm>(actor);
    if (!swarm || *mSubAccRateMin_s > *mSubAccRateMax_s) {
        setFailed();
        return;
    }

    _11c = sead::Vector3f::zero;
    _128.min = 5;
    _128.max = 5;
    _128.value = 5.0f;
    FlyMoveBase::m32(&_f0);
    FlyMoveBase::m33(&_fc, &_108);
    sub_710072A944(swarm, *mSubAccRateMin_s, *mSubAccRateMax_s);
    for (s32 i = 0; i < swarm->_14c8.size(); ++i) {
        if (auto* unit = swarm->_14c8[i])
            unit->_5c = sead::GlobalRandom::instance()->getF32Range(*mSubAccRateMin_s, *mSubAccRateMax_s);
    }
    _10c = ksys::Timer(0.0f, 0.0f, 1.0f);
    if (_118 && !mMaterialAnimName_s.isEmpty())
        sub_710072A778(swarm, mMaterialAnimName_s, *mMaterialAnimFrame_s);
}

void SwarmFlyMove::leave_() {
    FlyMoveBase::leave_();
}

void SwarmFlyMove::loadParams_() {
    FlyMoveBase::loadParams_();
    getStaticParam(&mIgnoreSensorTime_s, "IgnoreSensorTime");
    getStaticParam(&mSubAccRateMin_s, "SubAccRateMin");
    getStaticParam(&mSubAccRateMax_s, "SubAccRateMax");
    getStaticParam(&mMaterialAnimFrame_s, "MaterialAnimFrame");
    getStaticParam(&mMaterialAnimName_s, "MaterialAnimName");
}

void SwarmFlyMove::calc_() {
    FlyMoveBase::calc_();
    if (!sub_7100285AD8())
        setFailed();
}

void SwarmFlyMove::m33(sead::Vector3f* dir, f32* dist) {
    if (dir)
        dir->set(_fc);
    if (dist)
        *dist = _108;
}

}  // namespace uking::action
