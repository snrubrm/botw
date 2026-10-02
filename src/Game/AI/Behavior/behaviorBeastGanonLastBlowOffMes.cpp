#include "Game/AI/Behavior/behaviorBeastGanonLastBlowOffMes.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

BeastGanonLastBlowOffMes::BeastGanonLastBlowOffMes(const InitArg& arg)
    : SimpleAtvUnitOpenDlgRnd3(arg) {}

BeastGanonLastBlowOffMes::~BeastGanonLastBlowOffMes() = default;

bool BeastGanonLastBlowOffMes::m6(sead::Heap* heap) {
    if (!SimpleAtvUnitOpenDlgRnd3::m6(heap))
        return false;
    _d8.search(mActor->getModel(), mXZBaseNode_s);
    return true;
}

void BeastGanonLastBlowOffMes::m8() {
    SimpleAtvUnitOpenDlgRnd3::m8();
}

void BeastGanonLastBlowOffMes::m9() {
    SimpleAtvUnitOpenDlgRnd3::m9();
}

void BeastGanonLastBlowOffMes::loadParams() {
    SimpleAtvUnitOpenDlgRnd3::loadParams();
    getStaticParam(&mDistXZ_s, "DistXZ");
    getStaticParam(&mSubsY_s, "SubsY");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mXZBaseNode_s, "XZBaseNode");
}

}  // namespace uking::behavior
