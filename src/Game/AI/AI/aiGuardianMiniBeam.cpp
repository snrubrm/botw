#include "Game/AI/AI/aiGuardianMiniBeam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianMiniBeam::GuardianMiniBeam(const InitArg& arg) : BeamExplodeBase(arg) {}

GuardianMiniBeam::~GuardianMiniBeam() = default;

void GuardianMiniBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamExplodeBase::enter_(params);
}

void GuardianMiniBeam::calc_() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("着弾前")) {
        m34();
        return;
    }

    if (isCurrentChild("後処理"))
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

void GuardianMiniBeam::leave_() {
    BeamExplodeBase::leave_();
}

void GuardianMiniBeam::loadParams_() {
    BeamExplodeBase::loadParams_();
}

void GuardianMiniBeam::m34() {
    changeChild("後処理");
}

}  // namespace uking::ai
