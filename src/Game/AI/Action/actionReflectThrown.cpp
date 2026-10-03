#include "Game/AI/Action/actionReflectThrown.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

ReflectThrown::ReflectThrown(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReflectThrown::~ReflectThrown() = default;

bool ReflectThrown::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReflectThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ReflectThrown::leave_() {
    sub_71005DC02C(mActor);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(_48);
    if (mIsReflectThrownBullet_a)
        *mIsReflectThrownBullet_a = false;
}

void ReflectThrown::loadParams_() {
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mFinishWaterDepth_s, "FinishWaterDepth");
    getDynamicParam(&mPower_d, "Power");
    getDynamicParam(&mTargetDir_d, "TargetDir");
    getAITreeVariable(&mIsReflectThrownBullet_a, "IsReflectThrownBullet");
}

void ReflectThrown::calc_() {
    if (isFinished()) {
        sub_71005DC02C(mActor);
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D91098(_48);
        setFinished();
    }
    _49 = false;
}

bool ReflectThrown::isFinished() const {
    if (_49)
        return false;
    auto* actor = mActor;
    if (isLandedMaybe(actor, false) || isBgGroundHit(actor, false) ||
        sub_71007A4178(mActor, false)) {
        return true;
    }
    if (*mFinishWaterDepth_s >= 0.0f) {
        f32 depth;
        if (mActor->get68f()) {
            const f32 y = mActor->getMtx().m[1][3];
            depth = mActor->get6f0() - y;
        } else {
            depth = 0.0f;
        }
        if (depth >= *mFinishWaterDepth_s)
            return true;
    }
    if (auto* manager = sub_710072BA90(mActor))
        return sub_7100736BBC(manager->getField54());
    return false;
}

}  // namespace uking::action
