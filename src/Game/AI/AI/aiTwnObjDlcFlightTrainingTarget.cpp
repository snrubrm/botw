#include "Game/AI/AI/aiTwnObjDlcFlightTrainingTarget.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

TwnObjDlcFlightTrainingTarget::TwnObjDlcFlightTrainingTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

TwnObjDlcFlightTrainingTarget::~TwnObjDlcFlightTrainingTarget() = default;

bool TwnObjDlcFlightTrainingTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TwnObjDlcFlightTrainingTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("待機");
    mActor->getModel()->x(true, 0);
    sub_71007A3540(mActor);
    mActor->emitBasicSigOff();
    if (ksys::gdt::getFlag_BalladOfHeroRito_TargetEffect(false))
        xlinkSearchAndEmit(mActor, "FlightTrainingTarget_Open", 2, nullptr);
}

void TwnObjDlcFlightTrainingTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TwnObjDlcFlightTrainingTarget::loadParams_() {
    getStaticParam(&mLimitTime_s, "LimitTime");
}

}  // namespace uking::ai
