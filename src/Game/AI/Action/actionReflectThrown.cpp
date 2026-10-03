#include "Game/AI/Action/actionReflectThrown.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"

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

}  // namespace uking::action
