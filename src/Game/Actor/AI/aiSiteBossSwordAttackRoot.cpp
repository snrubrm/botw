#include "Game/Actor/AI/aiSiteBossSwordAttackRoot.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

void SiteBossSwordAttackRoot::sub_7100594BB8() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss)
        return;
    for (s32 i = 0; i < 10; ++i) {
        if (boss->_1560._1e0[i].hasProc() || boss->_1560._a0[i].isAllocatedOrFailed())
            continue;
        const sead::Matrix34f matrix = mActor->getMtx();
        ksys::act::InstParamPack params;
        params->addMatrix(matrix);
        params->add(i, "Count");
        params->add(i, "PatternID");
        boss->_1560.sub_710066BFEC(i, "Enemy_SiteBoss_Sword_AfterImage", &params, false);
    }
}

void SiteBossSwordAttackRoot::sub_710059616C() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy || *mElectricCounterMax_s < 1)
        return;
    for (s32 i = 0; i < *mElectricCounterMax_s; ++i) {
        sead::FormatFixedSafeString<32> name("ElectricBall%d", i);
        if (!enemy->getActorPartsActor(name).hasProc())
            sub_71005947AC(i);
    }
}

// NON_MATCHING: the original loads the address of Vector3f::zero after the SafeString stores (into the
// register it already used); ours loads it earlier into x10
SiteBossSwordAttackRoot::SiteBossSwordAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSwordAttackRoot::~SiteBossSwordAttackRoot() {
    if (auto* boss = sead::DynamicCast<act::Enemy>(mActor)) {
        if (mElectricCounterMax_s) {
            for (s32 i = 0; i < *mElectricCounterMax_s; ++i) {
                sead::FormatFixedSafeString<32> name("ElectricBall%d", i);
                if (boss->getActorPartsActor(name).hasProc()) {
                    ksys::act::ActorLinkConstDataAccess accessor;
                    ksys::act::acquireActor(&boss->getActorPartsActor(name), &accessor);
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                }
                boss->sub_7100D3CFEC(name);
            }
        }
    }
}

bool SiteBossSwordAttackRoot::init_(sead::Heap* heap) {
    _108 &= ~0x10;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        for (s32 i = 0; i < *mElectricCounterMax_s; ++i) {
            sead::FormatFixedSafeString<32> name("ElectricBall%d", i);
            enemy->sub_7100D3CED8(name, heap);
            sub_71005947AC(i);
        }
    }
    sub_7100594BB8();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_14c8._30.set(0x40);
    return true;
}

void SiteBossSwordAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSwordAttackRoot::leave_() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_14c8._30.reset(0x880);
        boss->_14c8._30.set(0x80);
        for (s32 i = 0; i < 16; ++i) {
            sead::FormatFixedSafeString<64> name("IronPile%d", i);
            act::SiteBoss::sub_71002D3624(boss, name);
        }
    }
    _108 &= ~0x10;
    _10c = *mElectricCounterMax_s + 1;
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

// 0x7100596400
bool SiteBossSwordAttackRoot::sub_7100596400() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_14c8._30.isOnAll(6) && (_108 & 4)) {
            if (auto* boss2 = sead::DynamicCast<act::SiteBoss>(mActor)) {
                if (boss2->_1548 <= sead::Mathf::epsilon())
                    return true;
            }
        }
    }
    return false;
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

// 0x7100595768
void SiteBossSwordAttackRoot::sub_7100595768() {
    sead::Vector3f pos;
    if (auto* actor = mActor) {
        auto* link = sub_71005D9050(actor);
        if (link && link->hasProc() && ksys::act::isPlayerProfile(link))
            pos = sub_71005D9330(actor);
        else
            pos = getPlayerPosition();
    }
    _108 |= 3;
    sub_7100596A4C(pos, true);
}

// 0x7100595808
void SiteBossSwordAttackRoot::sub_7100595808(const sead::Vector3f& pos, s32 attack) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_14c8._30.set(0x80);
    _108 &= 0xfd9f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(_fc, "OldTargetPos", -1);
    pack.addBool(false, "IsNoCharge", -1);
    pack.addBool(false, "IsAttackPatternFixed", -1);
    pack.addBool(true, "IsResetEndTime", -1);
    pack.addBool(_108 & 1, "IsRestart", -1);
    switch (attack) {
    case 0:
        changeChild("近接攻撃", &pack);
        break;
    case 1:
        changeChild("近接攻撃2", &pack);
        break;
    case 2:
        changeChild("近接攻撃3", &pack);
        break;
    default:
        break;
    }
    if (checkHpRate(mActor, *mSecondAttackHPRate_s))
        changeChild("近接攻撃3", &pack);
    else if (checkHpRate(mActor, *mFirstAttackHPRate_s))
        changeChild("近接攻撃2", &pack);
    else
        changeChild("近接攻撃", &pack);
}

}  // namespace uking::ai
