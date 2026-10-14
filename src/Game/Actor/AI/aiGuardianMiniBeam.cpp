#include "Game/Actor/AI/aiGuardianMiniBeam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianMiniBeam::GuardianMiniBeam(const InitArg& arg) : SimpleBeamExplode(arg) {}

GuardianMiniBeam::~GuardianMiniBeam() = default;

void GuardianMiniBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleBeamExplode::enter_(params);
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
    SimpleBeamExplode::leave_();
}

void GuardianMiniBeam::loadParams_() {
    SimpleBeamExplode::loadParams_();
}

void GuardianMiniBeam::m34() {
    changeChild("後処理");
}

}  // namespace uking::ai
