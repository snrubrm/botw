#include "Game/AI/AI/aiSiteBossApproachRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

namespace uking::ai {

SiteBossApproachRoot::SiteBossApproachRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    for (auto& ray_cast : mRayCasts)
        ray_cast = nullptr;
    for (auto& pos : _c8)
        pos.set(0, 0, 0);
}

SiteBossApproachRoot::~SiteBossApproachRoot() = default;

bool SiteBossApproachRoot::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel())
        _1f8.search(model, "Head");
    else
        _1f8.getKey().reset();
    return true;
}

void SiteBossApproachRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossApproachRoot::leave_() {
    for (auto*& ray_cast : mRayCasts) {
        if (ray_cast && !ray_cast->isRequestFinished()) {
            ray_cast->release();
            ray_cast = nullptr;
        }
    }
}

void SiteBossApproachRoot::loadParams_() {
    getStaticParam(&mCheckWallDist_s, "CheckWallDist");
    getStaticParam(&mApproachTime_s, "ApproachTime");
    getStaticParam(&mEndDist_s, "EndDist");
    getStaticParam(&mEndFarDist_s, "EndFarDist");
    getStaticParam(&mAttackStartDist_s, "AttackStartDist");
    getStaticParam(&mDoAttack_s, "DoAttack");
    getDynamicParam(&mIsMoveSide_d, "IsMoveSide");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
