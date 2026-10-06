#include "Game/AI/Action/actionSwarmFlyAttack.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/System/VFR.h"
#include "Game/AI/aiUnk_710072A944.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

SwarmFlyAttack::SwarmFlyAttack(const InitArg& arg) : SwarmFlyMove(arg) {}

SwarmFlyAttack::~SwarmFlyAttack() = default;

bool SwarmFlyAttack::init_(sead::Heap* heap) {
    return SwarmFlyMove::init_(heap);
}

void SwarmFlyAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _118 = false;
    SwarmFlyMove::enter_(params);
    auto* actor = mActor;
    auto* swarm = sead::DynamicCast<act::Swarm>(actor);
    if (!swarm) {
        setFailed();
        return;
    }
    sub_7100729EA8(swarm);
    auto* sensor = getActorAttackSensor(actor);
    const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
    sensor->activateAttackSensor(0x2000, 0x4001, attack->mPower.ref(), attack->mImpulse.ref(), 0.0f,
                                 0, 1, -1, false, 1, -1);
    _150 = ksys::Timer(0.0f, 0.0f, 1.0f);
    _15c = false;
    sub_710028508C();
}

// NON_MATCHING: the budget decrement: the original branches (`cmp #2; b.lt exit; sub 1`), ours turns it into
// `cset; sub` (the counter is dead after the loop)
void SwarmFlyAttack::sub_710028508C() {
    if (mMaterialAnimName_s.isEmpty())
        return;
    auto* swarm = static_cast<act::Swarm*>(mActor);
    const sead::Vector3f pos = swarm->getMtx().getTranslation();
    sead::Vector3f target;
    m32(&target);
    if ((pos - target).length() >= *mApplyMaterialAnimDist_s)
        return;
    const s32 num_units = swarm->_14c8.size();
    s32 remaining = s32(f32(*mApplyMaterialAnimNumPerFrame_s) * ksys::VFR::instance()->getDeltaFrame());
    if (num_units < 1)
        return;
    if (remaining < 1)
        remaining = 1;
    for (s32 i = 0; i < num_units; ++i) {
        auto* unit = swarm->_14c8[i];
        if (!unit)
            continue;
        if ((unit->_8.getTranslation() - target).length() > *mApplyMaterialAnimDist_s)
            continue;
        if (unit->sub_71002DA3A0(*mMaterialAnimFrame_s, mMaterialAnimName_s)) {
            if (remaining <= 1)
                break;
            --remaining;
        }
    }
}

void SwarmFlyAttack::leave_() {
    if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor))
        sub_7100729F34(swarm);
    SwarmFlyMove::leave_();
}

void SwarmFlyAttack::loadParams_() {
    SwarmFlyMove::loadParams_();
    getStaticParam(&mFailTimeInClosePos_s, "FailTimeInClosePos");
    getStaticParam(&mApplyMaterialAnimNumPerFrame_s, "ApplyMaterialAnimNumPerFrame");
    getStaticParam(&mApplyMaterialAnimDist_s, "ApplyMaterialAnimDist");
}

// NON_MATCHING: the original tests the masked copy (`and w20, w0, #1; tbz w20`), clang tests w0 directly
void SwarmFlyAttack::calc_() {
    if (isFinishedOrFailed())
        return;
    sub_710028508C();
    const bool is_close = sub_7100134380();
    f32 time;
    if (is_close) {
        _15c = is_close;
        _150.update();
        mFlags.reset(Flag::Changeable);
        time = _150.value;
    } else {
        if (_15c) {
            setFinished();
            return;
        }
        time = 0.0f;
        _15c = is_close;
        _150 = ksys::Timer(0.0f, 0.0f, 1.0f);
    }
    if (time > *mFailTimeInClosePos_s) {
        setFailed();
        return;
    }
    if (!is_close && !sub_710013443C())
        setFailed();
    if (sub_7100285AD8())
        return;
    setFailed();
}

}  // namespace uking::action
