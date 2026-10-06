#include "Game/AI/AI/aiSiteBossSwordAttackRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

// NON_MATCHING: the original loads the address of Vector3f::zero after the SafeString stores (into the
// register it already used); ours loads it earlier into x10
SiteBossSwordAttackRoot::SiteBossSwordAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSwordAttackRoot::~SiteBossSwordAttackRoot() {
    if (auto* boss = sead::DynamicCast<act::Enemy>(mActor)) {
        if (mElectricCounterMax_s) {
            for (s32 i = 0; i < *mElectricCounterMax_s; ++i) {
                sead::FormatFixedSafeString<32> name("ElectricBall%d", i);
                if (boss->getActorPartsActor(name).hasProc()) {
                    ksys::act::ActorConstDataAccess accessor;
                    ksys::act::acquireActor(&boss->getActorPartsActor(name), &accessor);
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                }
                boss->sub_7100D3CFEC(name);
            }
        }
    }
}

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

// 0x7100596a4c
void SiteBossSwordAttackRoot::sub_7100596A4C(const sead::Vector3f& pos, bool attack_pattern_fixed) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addBool(attack_pattern_fixed, "IsAttackPatternFixed", -1);
    changeChild("盾突き", &pack);
}

// 0x7100596fa4
void SiteBossSwordAttackRoot::sub_7100596FA4(const sead::Vector3f& pos) {
    _108 |= 0x20;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(_fc, "OldTargetPos", -1);
    changeChild("退避", &pack);
}

// 0x71005955d4
void SiteBossSwordAttackRoot::sub_71005955D4(const sead::Vector3f& pos) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_14c8._30.set(0x80);
    const bool counted = _108 & 0x80;
    _108 &= ~0x220;
    _108 |= 0x40;
    if (counted)
        ++_10c;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addPointer(nullptr, "IgniteBaseProcHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    changeChild("遠距離攻撃", &pack);
}

// 0x7100596268
void SiteBossSwordAttackRoot::sub_7100596268(const sead::Vector3f& pos) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_14c8._30.set(0x80);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1))
        pack.addBool(false, "IsResetEndTime", -1);
    else
        pack.addBool(true, "IsResetEndTime", -1);
    changeChild("待機", &pack);
}

// 0x7100596b48
void SiteBossSwordAttackRoot::sub_7100596B48(const sead::Vector3f& pos) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_14c8._30.reset(0x80);
        boss->_14c8._30.set(0x800);
    }
    _108 |= 1;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("落雷攻撃", &pack);
}

// 0x7100596de4
void SiteBossSwordAttackRoot::sub_7100596DE4(const sead::Vector3f& pos) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_14c8._30.reset(0x80);
        boss->_14c8._30.set(0x800);
        boss->_1558.reset(0x40000);
    }
    _108 |= 1;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(_fc, "OldTargetPos", -1);
    pack.addBool(!(_108 & 0x10), "IsResetOldMoveIdx", -1);
    _108 |= 0x10;
    changeChild("落雷攻撃前移動", &pack);
}

}  // namespace uking::ai
