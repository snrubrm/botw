#include "Game/AI/AI/aiSiteBossSwordRailApproach.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"

namespace uking::ai {

SiteBossSwordRailApproach::SiteBossSwordRailApproach(const InitArg& arg)
    : SiteBossSwordApproachRoot(arg) {}

SiteBossSwordRailApproach::~SiteBossSwordRailApproach() = default;

bool SiteBossSwordRailApproach::init_(sead::Heap* heap) {
    if (!SiteBossSwordApproachRoot::init_(heap))
        return false;
    _c8 = -1;
    _cc = false;
    return true;
}

void SiteBossSwordRailApproach::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossSwordApproachRoot::enter_(params);
    if (*mIsResetOldMoveIdx_d)
        _c8 = -1;
    _cc = false;
}

void SiteBossSwordRailApproach::calc_() {
    SiteBossSwordApproachRoot::calc_();
}

void SiteBossSwordRailApproach::leave_() {
    SiteBossSwordApproachRoot::leave_();
}

void SiteBossSwordRailApproach::loadParams_() {
    SiteBossSwordApproachRoot::loadParams_();
    getDynamicParam(&mIsResetOldMoveIdx_d, "IsResetOldMoveIdx");
}

// NON_MATCHING: the original computes the getU32 argument before loading the GlobalRandom instance
// (C++14 evaluation order, see SiteBossRecognizeRootBase::enter_) and register allocation
void SiteBossSwordRailApproach::m34(sead::Vector3f* out) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    auto* object = mActor->getMapObject();
    ksys::map::Rail* rail;
    if (object && object->getRails_0() &&
        (rail = static_cast<ksys::map::Rail**>(object->getRails_0())[0])) {
        if (_cc) {
            *out = rail->getPointTranslate(_c8);
            return;
        }
        const s32 num_points = rail->getNumPoints();
        s32 idx = sead::GlobalRandom::instance()->getU32(num_points - (_c8 != -1));
        if (idx >= _c8)
            ++idx;
        if (idx >= num_points)
            idx -= num_points;
        *out = rail->getPointTranslate(idx);
        _c8 = idx;
        _cc = true;
        return;
    }
    *out = pos;
}

}  // namespace uking::ai
