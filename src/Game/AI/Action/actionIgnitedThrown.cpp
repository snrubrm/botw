#include "Game/AI/Action/actionIgnitedThrown.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

IgnitedThrown::IgnitedThrown(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IgnitedThrown::~IgnitedThrown() = default;

bool IgnitedThrown::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IgnitedThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IgnitedThrown::leave_() {
    auto* actor = mActor;
    sub_71005DC02C(actor);
    if (auto* chemical = actor->getChemicalStuff())
        chemical->sub_7100D91098(_72);
    if (_71)
        sub_7100738DC8(actor);
    xlink::fade(_80, -1);
}

void IgnitedThrown::loadParams_() {
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mDamageScale_s, "DamageScale");
    getStaticParam(&mFinishWaterDepth_s, "FinishWaterDepth");
    getStaticParam(&mIsScaling_s, "IsScaling");
    getStaticParam(&mIsFinishedByOneHit_s, "IsFinishedByOneHit");
    getStaticParam(&mIsFadeIn_s, "IsFadeIn");
    getStaticParam(&mIsAbleGuard_s, "IsAbleGuard");
    getStaticParam(&mIsForceOnly_s, "IsForceOnly");
    getStaticParam(&mAS_s, "AS");
}

void IgnitedThrown::calc_() {
    ksys::act::ai::Action::calc_();
}

bool IgnitedThrown::isFinished() const {
    if (ksys::act::ai::Action::isFinished())
        return true;
    if (_70)
        return false;
    auto* actor = mActor;
    if (isLandedMaybe(actor, false) || isBgGroundHit(actor, false))
        return true;
    if (*mIsFinishedByOneHit_s && sub_71007A4178(mActor, false))
        return true;
    if (*mFinishWaterDepth_s >= 0.0f) {
        f32 depth;
        if (mActor->get68f()) {
            const f32 y = mActor->getMtx().m[1][3];
            depth = mActor->get6f0() - y;
        } else {
            depth = 0.0f;
        }
        return depth >= *mFinishWaterDepth_s;
    }
    return false;
}

}  // namespace uking::action
