#include "Game/AI/AI/aiSiteBossSwordAttackRoot.h"

namespace uking::ai {

// NON_MATCHING: the original loads the address of Vector3f::zero after the SafeString stores (into the
// register it already used); ours loads it earlier into x10
SiteBossSwordAttackRoot::SiteBossSwordAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSwordAttackRoot::~SiteBossSwordAttackRoot() = default;

bool SiteBossSwordAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSwordAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSwordAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSwordAttackRoot::loadParams_() {
    getStaticParam(&mCloseAttackRate_s, "CloseAttackRate");
    getStaticParam(&mChemicalPlusRate_s, "ChemicalPlusRate");
    getStaticParam(&mThrowAttackPower_s, "ThrowAttackPower");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mThrowMinDamage_s, "ThrowMinDamage");
    getStaticParam(&mThrowRate_s, "ThrowRate");
    getStaticParam(&mPillarMax_s, "PillarMax");
    getStaticParam(&mElectricCounterMax_s, "ElectricCounterMax");
    getStaticParam(&mChemicalPlusHPRate_s, "ChemicalPlusHPRate");
    getStaticParam(&mShieldRepairTime_s, "ShieldRepairTime");
    getStaticParam(&mFirstAttackHPRate_s, "FirstAttackHPRate");
    getStaticParam(&mSecondAttackHPRate_s, "SecondAttackHPRate");
    getStaticParam(&mBeamAttackHPRate_s, "BeamAttackHPRate");
    getStaticParam(&mElectricBallScaleTime_s, "ElectricBallScaleTime");
    getStaticParam(&mElectricBallScale_s, "ElectricBallScale");
    getStaticParam(&mElectricBallRange_s, "ElectricBallRange");
    getStaticParam(&mThrowDist_s, "ThrowDist");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mEntryPointName_s, "EntryPointName");
    getStaticParam(&mThrowActorName_s, "ThrowActorName");
    getDynamicParam(&mIsCancelAttack_d, "IsCancelAttack");
}

bool SiteBossSwordAttackRoot::isChangeable() const {
    if (isCurrentChild("待機"))
        return true;
    if (getCurrentChild()->isChangeable())
        return true;
    return ksys::act::ai::Ai::isChangeable();
}

}  // namespace uking::ai
