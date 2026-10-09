#include "Game/AI/Action/actionForkSetSwarmMaterialAnimByDist.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

ForkSetSwarmMaterialAnimByDist::ForkSetSwarmMaterialAnimByDist(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkSetSwarmMaterialAnimByDist::~ForkSetSwarmMaterialAnimByDist() = default;

bool ForkSetSwarmMaterialAnimByDist::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSetSwarmMaterialAnimByDist::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkSetSwarmMaterialAnimByDist::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSetSwarmMaterialAnimByDist::loadParams_() {
    getStaticParam(&mApplyMaterialAnimNumPerFrame_s, "ApplyMaterialAnimNumPerFrame");
    getStaticParam(&mSetState_s, "SetState");
    getStaticParam(&mApplyMaterialAnimDist_s, "ApplyMaterialAnimDist");
    getStaticParam(&mMaterialAnimFrame_s, "MaterialAnimFrame");
    getStaticParam(&mMaterialAnimName_s, "MaterialAnimName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: parameter loads and loop/budget branch lowering differ.
void ForkSetSwarmMaterialAnimByDist::sub_7100163718() {
    if (mMaterialAnimName_s.isEmpty())
        return;
    auto* swarm = static_cast<act::Swarm*>(mActor);
    const auto* target = mTargetPos_d;
    const f32 distance = (swarm->getMtx().getTranslation() - *target).length();
    if (*mSetState_s != 0) {
        if (distance <= *mApplyMaterialAnimDist_s)
            return;
    } else if (distance >= *mApplyMaterialAnimDist_s) {
        return;
    }

    const s32 num_units = swarm->_14c8.size();
    s32 remaining = s32(f32(*mApplyMaterialAnimNumPerFrame_s) *
                        ksys::VFR::instance()->getDeltaFrame());
    if (num_units < 1)
        return;
    if (remaining < 1)
        remaining = 1;
    for (s32 i = 0; i < num_units; ++i) {
        auto* unit = swarm->_14c8[i];
        if (!unit)
            continue;
        if (!((unit->_8.getTranslation() - *target).length() <= *mApplyMaterialAnimDist_s))
            continue;
        if (unit->sub_71002DA3A0(*mMaterialAnimFrame_s, mMaterialAnimName_s)) {
            if (remaining <= 1)
                return;
            --remaining;
        }
    }
}

void ForkSetSwarmMaterialAnimByDist::calc_() {
    sub_7100163718();
}

}  // namespace uking::action
