#include "Game/Actor/Action/actionSwarmFlyMove.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_710072A944.h"
#include "Game/Actor/AI/aiAddSwarmMove.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/Utils/MathUtil.h"

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

// NON_MATCHING: the original stores the three lerped components one by one (no stp) in a different order.
bool SwarmFlyMove::sub_7100285AD8() {
    auto* actor = mActor;
    sead::Vector3f next;
    s32 flag = 0;
    const bool ok = sub_7100729D18(actor, &next, _11c, *mParams.mSpeed_s, &flag, false);
    if (flag)
        _128.reset();
    else
        _128.update();

    if (_128.value <= 0.0f)
        _11c = sead::Vector3f::zero;
    else
        _11c = next;

    if (!ok && _10c.value >= f32(*mIgnoreSensorTime_s))
        return false;

    _10c.update();
    sub_710072A108(static_cast<act::Swarm*>(actor), sead::Vector3f::ey);

    sead::Vector3f target;
    FlyMoveBase::m32(&target);
    target += next;
    _f0 = ksys::util::lerp(_f0, target, 0.2f);

    f32 dist;
    sead::Vector3f dir;
    FlyMoveBase::m33(&dir, &dist);
    _108 = dist;
    if (next.x <= 0.001f && next.x >= -0.001f && next.y <= 0.001f && next.y >= -0.001f &&
        next.z <= 0.001f && next.z >= -0.001f) {
        _fc = ksys::util::lerp(_fc, dir, 1.0f);
    } else {
        dir += next;
        dir.normalize();
        _fc = ksys::util::lerp(_fc, dir, 0.01f);
    }
    return true;
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
