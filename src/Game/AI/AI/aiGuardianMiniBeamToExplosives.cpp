#include "Game/AI/AI/aiGuardianMiniBeamToExplosives.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

GuardianMiniBeamToExplosives::GuardianMiniBeamToExplosives(const InitArg& arg)
    : GuardianMiniBeamAttack(arg) {}

GuardianMiniBeamToExplosives::~GuardianMiniBeamToExplosives() = default;

void GuardianMiniBeamToExplosives::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMiniBeamAttack::enter_(params);
}

void GuardianMiniBeamToExplosives::loadParams_() {
    GuardianMiniBeamAttack::loadParams_();
    getStaticParam(&mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool GuardianMiniBeamToExplosives::m39() {
    return m40();
}

void GuardianMiniBeamToExplosives::m42() {}

bool GuardianMiniBeamToExplosives::m46(sead::Vector3f* out) {
    if (!out)
        return false;
    if (!mTargetActor_d)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(*out);
    return true;
}

}  // namespace uking::ai
