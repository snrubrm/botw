#include "Game/AI/Action/actionSiteBossLswordAtkWithChemical.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossLswordAtkWithChemical::SiteBossLswordAtkWithChemical(const InitArg& arg)
    : SiteBossLswordAtk(arg) {}

SiteBossLswordAtkWithChemical::~SiteBossLswordAtkWithChemical() = default;

bool SiteBossLswordAtkWithChemical::init_(sead::Heap* heap) {
    return SiteBossLswordAtk::init_(heap);
}

void SiteBossLswordAtkWithChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossLswordAtk::enter_(params);
}

void SiteBossLswordAtkWithChemical::leave_() {
    SiteBossLswordAtk::leave_();
}

void SiteBossLswordAtkWithChemical::loadParams_() {
    SiteBossLswordAtk::loadParams_();
    getStaticParam(&mEmitNum_s, "EmitNum");
    getStaticParam(&mEmitInterval_s, "EmitInterval");
    getStaticParam(&mEmitAttackDamage_s, "EmitAttackDamage");
    getStaticParam(&mEmitActorMinDamage_s, "EmitActorMinDamage");
    getStaticParam(&mEmitOffsetFromParent_s, "EmitOffsetFromParent");
    getStaticParam(&mEmitIntervalDist_s, "EmitIntervalDist");
    getStaticParam(&mEmitIntervalRotate_s, "EmitIntervalRotate");
    getStaticParam(&mEmitScale_s, "EmitScale");
    getStaticParam(&mEmitMaxScale_s, "EmitMaxScale");
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mEmitStartFrame_s, "EmitStartFrame");
    getStaticParam(&mEmitAngleFromParent_s, "EmitAngleFromParent");
    getStaticParam(&mEmitActorSpeedRotate_s, "EmitActorSpeedRotate");
    getStaticParam(&mEmitActorName_s, "EmitActorName");
    getStaticParam(&mEmitPartsName_s, "EmitPartsName");
    getStaticParam(&mCallSEKeyAtAtOn_s, "CallSEKeyAtAtOn");
    getStaticParam(&mEmitActorSpeed_s, "EmitActorSpeed");
}

void SiteBossLswordAtkWithChemical::calc_() {
    SiteBossLswordAtk::calc_();
}

void SiteBossLswordAtkWithChemical::m37(sead::Vector3f* pos) {
    mActor->getMtx().getTranslation(*pos);
}

f32 SiteBossLswordAtkWithChemical::m38() {
    return *mEmitOffsetFromParent_s;
}

int SiteBossLswordAtkWithChemical::m39() {
    return 2;
}

}  // namespace uking::action
