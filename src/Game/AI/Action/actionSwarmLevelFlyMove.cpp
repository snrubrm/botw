#include "Game/AI/Action/actionSwarmLevelFlyMove.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/AI/aiAddSwarmMove.h"
#include "Game/AI/aiUnk_710072A944.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

SwarmLevelFlyMove::SwarmLevelFlyMove(const InitArg& arg) : LevelFlyMoveBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SwarmLevelFlyMove::~SwarmLevelFlyMove() {
    ;
}

bool SwarmLevelFlyMove::init_(sead::Heap* heap) {
    return LevelFlyMoveBase::init_(heap);
}

void SwarmLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyMoveBase::enter_(params);
    auto* actor = mActor;
    auto* swarm = sead::DynamicCast<act::Swarm>(actor);
    if (!swarm || *mSubAccRateMin_s > *mSubAccRateMax_s) {
        setFailed();
        return;
    }

    _178 = sead::Vector3f::zero;
    _184.min = 5;
    _184.max = 5;
    _184.value = 5.0f;
    for (s32 i = 0; i < swarm->_14c8.size(); ++i) {
        if (auto* unit = swarm->_14c8[i])
            unit->_5c = sead::GlobalRandom::instance()->getF32Range(*mSubAccRateMin_s, *mSubAccRateMax_s);
    }
    _168 = ksys::Timer(0.0f, 0.0f, 1.0f);
    if (_174 && !mMaterialAnimName_s.isEmpty())
        sub_710072A778(swarm, mMaterialAnimName_s, *mMaterialAnimFrame_s);
}

void SwarmLevelFlyMove::leave_() {
    LevelFlyMoveBase::leave_();
}

void SwarmLevelFlyMove::loadParams_() {
    LevelFlyMoveBase::loadParams_();
    getStaticParam(&mIgnoreSensorTime_s, "IgnoreSensorTime");
    getStaticParam(&mSubAccRateMin_s, "SubAccRateMin");
    getStaticParam(&mSubAccRateMax_s, "SubAccRateMax");
    getStaticParam(&mMaterialAnimFrame_s, "MaterialAnimFrame");
    getStaticParam(&mMaterialAnimName_s, "MaterialAnimName");
}

// NON_MATCHING: same instructions and control flow; `this` and `actor` swap callee-saved registers (x19 / x20)
void SwarmLevelFlyMove::calc_() {
    LevelFlyMoveBase::calc_();
    auto* actor = mActor;
    s32 flag = 0;
    sead::Vector3f next;
    const bool ok = sub_7100729D18(actor, &next, _178, *mXZSpeed_s, &flag, false);
    if (flag)
        _184.reset();
    else
        _184.update();

    if (_184.value <= 0.0f)
        _178 = sead::Vector3f::zero;
    else
        _178 = next;

    const f32 x = actor->getMtx().m[0][3];
    const f32 z = actor->getMtx().m[2][3];
    sead::Vector3f target;
    m34(&target);
    sead::Vector3f dir(target.x - x, 0.0f, target.z - z);
    dir.normalize();
    sead::Vector3f front;
    sub_71000891C8(&front, actor);
    if (m33() || dir.dot(front) >= 0.70710677f) {
        if (!ok && _168.value >= f32(*mIgnoreSensorTime_s)) {
            setFailed();
        } else {
            _168.update();
            sub_7100729FAC(static_cast<act::Swarm*>(actor), sead::Vector3f::ey);
        }
    } else {
        _168.update();
        sub_7100729FAC(static_cast<act::Swarm*>(actor), sead::Vector3f::ey);
    }
}

// NON_MATCHING: same instructions; the original schedules the 0.1f constant load before the multiply and stores `target`
// to the stack after it (register naming differs)
void SwarmLevelFlyMove::m35(ksys::VFRValue* speed, const sead::Vector3f& from,
                            const sead::Vector3f& to, f32 limit) {
    if (!speed)
        return;

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, from, to, sead::Vector3f::ey);
    const f32 target = *mXZSpeed_s;
    speed->chase(target, target * 0.1f);
    speed->updateStats();
}

}  // namespace uking::action
