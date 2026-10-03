#include "Game/AI/Action/actionHorseRandomMoveAction.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

HorseRandomMoveAction::HorseRandomMoveAction(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

void HorseRandomMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);

    auto* rideable = mActor->m132();
    const sead::Vector3f* pos = &sead::Vector3f::zero;
    if (rideable)
        pos = &rideable->_148;

    if (auto* nav = mActor->m45()) {
        if (*mIsCancelRequestedPathFirst_s)
            nav->inlineReset();
    }

    if (!uking::act::sub_7100E816E4(sead::Mathf::deg2rad(*mDirRangeDegree_s), *mRadiusLimit_s,
                                    *mDirRandomValue_s, *mForwardDirDistCoefficient_s,
                                    *mRejectDistRatioByNavMeshQuery_s, mActor, *pos)) {
        setFailed();
    }
}

void HorseRandomMoveAction::loadParams_() {
    AnimalMoveGuidedBase::loadParams_();
    getStaticParam(&mRadiusLimit_s, "RadiusLimit");
    getStaticParam(&mForwardDirDistCoefficient_s, "ForwardDirDistCoefficient");
    getStaticParam(&mDirRandomValue_s, "DirRandomValue");
    getStaticParam(&mDirRangeDegree_s, "DirRangeDegree");
    getStaticParam(&mRejectDistRatioByNavMeshQuery_s, "RejectDistRatioByNavMeshQuery");
    getStaticParam(&mIsCancelRequestedPathFirst_s, "IsCancelRequestedPathFirst");
}

}  // namespace uking::action
