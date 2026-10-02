#include "Game/AI/AI/aiBeamExplodeBase.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

BeamExplodeBase::BeamExplodeBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BeamExplodeBase::~BeamExplodeBase() = default;

bool BeamExplodeBase::init_(sead::Heap* heap) {
    _48 = mActor->getMainBody();
    _50 = mActor->findPhysicsBodyByName("Atk", "AtkBody");
    return true;
}

void BeamExplodeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BeamExplodeBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BeamExplodeBase::loadParams_() {
    getStaticParam(&mMaxDistance_s, "MaxDistance");
    getStaticParam(&mIsDelete_s, "IsDelete");
}

void BeamExplodeBase::calc_() {
    sead::Vector3f home_pos = sead::Vector3f::zero;
    mActor->getHomePos(&home_pos);

    if (isCurrentChild("着弾前")) {
        getCurrentChild()->setDynamicParam(home_pos, "EyePos");
        if ((home_pos - mActor->getMtx().getTranslation()).squaredLength() >
            sead::Mathf::square(*mMaxDistance_s)) {
            m34();
            return;
        }
    }

    auto* child = getCurrentChild();
    if (!child)
        return;
    if (!child->isFinished() && !child->isFailed() && !child->isChangeable())
        return;

    if (isCurrentChild("着弾前")) {
        m34();
        return;
    }

    if (!isCurrentChild("後処理"))
        return;

    if (*mIsDelete_s)
        mActor->deleteAndEmit(0);
    else
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D90858(false, 3, false, true, false);
    setFinished();
}

}  // namespace uking::ai
