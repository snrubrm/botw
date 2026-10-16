#include "Game/Actor/AI/aiSiteBossLswordAttackRoot.h"
#include "math/seadMathCalcCommon.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_71007377D4.h"

// 0x71002d2a80 (declared only; SiteBoss TU).
bool sub_71002D2A80();

namespace uking::ai {

SiteBossLswordAttackRoot::SiteBossLswordAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossLswordAttackRoot::~SiteBossLswordAttackRoot() = default;

bool SiteBossLswordAttackRoot::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel())
        _b8.search(model, "Head");
    else
        _b8.getKey().reset();
    _9a = false;
    _a0 = *mHighSlashRate_s;
    _a4 = *mCrossSlashRate_s;
    _a8 = *mWhirlSlashRate_s;
    _ac = 0;
    _b0 = 0;
    return true;
}

void SiteBossLswordAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _98 = false;
    _99 = false;
    _f0 = ksys::Timer(0, 0);
    _fc = ksys::Timer(0, 0);

    sead::Vector3f pos;
    if (auto* actor = mActor) {
        auto* link = sub_71005D9050(actor);
        if (link && link->hasProc() && ksys::act::isPlayerProfile(link))
            pos = sub_71005D9330(actor);
        else
            pos = getPlayerPosition();
    }

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_1558.reset(8);
        if (boss->_1558.isOn(0x200000)) {
            sub_7100579E30(pos, true);
            boss->_1558.reset(0x400000);
            return;
        }
    }

    if (act::SiteBoss::sub_71002D3804(mActor, "WearFlame"))
        sub_7100579FA4();
    else
        sub_710057A348(pos, false);
}

void SiteBossLswordAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossLswordAttackRoot::loadParams_() {
    getStaticParam(&mHighSlashRate_s, "HighSlashRate");
    getStaticParam(&mWhirlSlashRate_s, "WhirlSlashRate");
    getStaticParam(&mFireBallRate_s, "FireBallRate");
    getStaticParam(&mCrossSlashRate_s, "CrossSlashRate");
    getStaticParam(&mTornadoAttackRate_s, "TornadoAttackRate");
    getStaticParam(&mChemicalPlusHPRate_s, "ChemicalPlusHPRate");
    getStaticParam(&mIsFarDist_s, "IsFarDist");
    getStaticParam(&mPatternShiftFirstLifeRate_s, "PatternShiftFirstLifeRate");
    getStaticParam(&mReturnWaitCount_s, "ReturnWaitCount");
    getStaticParam(&mForceApproachCount_s, "ForceApproachCount");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
    getDynamicParam(&mIsCancelAttack_d, "IsCancelAttack");
}

bool SiteBossLswordAttackRoot::isChangeable() const {
    if (isCurrentChild("待機") || isCurrentChild("攻撃前待機"))
        return true;
    return ksys::act::ai::Ai::isChangeable();
}

void SiteBossLswordAttackRoot::sub_7100579E30(const sead::Vector3f& pos, bool a2) {
    ksys::act::ai::InlineParamPack params;
    params.addString("", "ThrowActorName", -1);
    params.addVec3(pos, "TargetPos", -1);
    auto* link = sub_71005D9050(mActor);
    if (!link) {
        setFailed();
        return;
    }
    params.addActor(*link, "TargetActor", -1);
    if (a2) {
        changeChild("火球投げカウンター", &params);
    } else {
        _a0 = *mHighSlashRate_s;
        _a4 = *mCrossSlashRate_s;
        _a8 = *mWhirlSlashRate_s;
        _ac = 0;
        _b0 = 0;
        changeChild("火球投げ", &params);
    }
}

// 0x7100579fa4
// NON_MATCHING: &_f0 kept in a register differently; the position copies are paired; scheduling of `_9c = 0`.
void SiteBossLswordAttackRoot::sub_7100579FA4() {
    sead::Vector3f pos;
    if (auto* actor = mActor) {
        auto* link = sub_71005D9050(actor);
        if (link && link->hasProc() && ksys::act::isPlayerProfile(link))
            pos = sub_71005D9330(actor);
        else
            pos = getPlayerPosition();
    }

    if (!sub_71002D2A80())
        _f0 = ksys::Timer(*mReturnWaitCount_s, *mReturnWaitCount_s);
    if (!(_f0.value <= sead::Mathf::epsilon())) {
        _f0.update();
        return;
    }

    if (act::SiteBoss::sub_71002D3804(mActor, "WearFlame")) {
        sub_710057AEB8(pos, mActor->getMtx().getTranslation());
        return;
    }

    const sead::Vector3f actor_pos = mActor->getMtx().getTranslation();
    if (sub_710072EB10(actor_pos, pos, ksys::phys::RayCast::NormalCheckingMode(0), mActor, nullptr,
                       nullptr, nullptr, 1.0f)) {
        if (sead::GlobalRandom::instance()->getU32(100) > 50) {
            if (_9c >= 5) {
                _9c = 0;
                setFailed();
            } else {
                ++_9c;
                sub_710057A348(pos, true);
            }
        }
        return;
    }

    s32 high = _a0;
    s32 cross = _a4;
    s32 whirl = _a8;
    _9c = 0;
    s32 fire = _ac < 30 ? 0 : _ac;
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (boss && boss->_1510 == 3) {
        high = 0;
        cross = 0;
        whirl = 0;
        fire = 100;
        boss->_1510 = -1;
    }

    s32 beam;
    if (!checkHpRate(mActor, *mPatternShiftFirstLifeRate_s)) {
        beam = 0;
    } else if (!_9a) {
        high = 0;
        cross = 0;
        whirl = 0;
        fire = 0;
        _9a = true;
        beam = 100;
    } else {
        beam = _b0;
    }

    const s32 value = sead::GlobalRandom::instance()->getU32(100);
    if (value < beam) {
        _a0 = *mHighSlashRate_s;
        _a4 = *mCrossSlashRate_s;
        _a8 = *mWhirlSlashRate_s;
        _ac = 0;
        _b0 = 0;
        changeChild("ビーム攻撃");
        return;
    }

    s32 limit = beam + high;
    if (value >= limit) {
        limit += whirl;
        if (value < limit) {
            sub_710057B120(pos);
            return;
        }
        limit += cross;
        if (value < limit) {
            sub_710057B254(pos);
            return;
        }
        if (value < limit + fire) {
            if (checkHpRate(mActor, *mChemicalPlusHPRate_s))
                sub_710057A908(pos);
            else
                sub_7100579E30(pos, false);
            return;
        }
    }
    sub_710057AFF0(pos);
}

void SiteBossLswordAttackRoot::sub_710057A348(const sead::Vector3f& pos, bool a2) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    params.addBool(a2, "IsMoveSide", -1);
    changeChild("攻撃前待機", &params);
}

// 0x710057a810
void SiteBossLswordAttackRoot::sub_710057A810(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addBool(false, "IsResetEndTime", -1);
    changeChild("待機", &pack);
}

// 0x710057aff0
void SiteBossLswordAttackRoot::sub_710057AFF0(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("縦斬り", &pack);
    _a0 = sead::Mathi::max(_a0 - 22, 0);
    _a4 = sead::Mathi::min(_a4 + 3, 100);
    _a8 = sead::Mathi::min(_a8 + 3, 100);
    _ac = sead::Mathi::min(_ac + 10, 100);
    _b0 = sead::Mathi::min(_b0 + 3, 100);
}

// 0x710057b120
void SiteBossLswordAttackRoot::sub_710057B120(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("回転斬り", &pack);
    _a0 = sead::Mathi::min(_a0 + 3, 100);
    _a4 = sead::Mathi::min(_a4 + 3, 100);
    _a8 = sead::Mathi::max(_a8 - 22, 0);
    _ac = sead::Mathi::min(_ac + 10, 100);
    _b0 = sead::Mathi::min(_b0 + 3, 100);
}

// 0x710057b254
void SiteBossLswordAttackRoot::sub_710057B254(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("横斬り", &pack);
    _a0 = sead::Mathi::min(_a0 + 3, 100);
    _a4 = sead::Mathi::max(_a4 - 22, 0);
    _a8 = sead::Mathi::min(_a8 + 3, 100);
    _ac = sead::Mathi::min(_ac + 10, 100);
    _b0 = sead::Mathi::min(_b0 + 3, 100);
}

// 0x710057ab3c
void SiteBossLswordAttackRoot::sub_710057AB3C(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addString("SiteBossFlameBall", "ThrowActorName", -1);
    pack.addVec3(pos, "TargetPos", -1);
    if (auto* target = sub_71005D9050(mActor)) {
        pack.addActor(*target, "TargetActor", -1);
        changeChild("火球投げ", &pack);
    } else {
        setFailed();
    }
}

// 0x710057aeb8
void SiteBossLswordAttackRoot::sub_710057AEB8(const sead::Vector3f& pos, const sead::Vector3f& dest_pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(dest_pos, "DestPos", -1);
    if (auto* target = sub_71005D9050(mActor)) {
        pack.addActor(*target, "TargetActor", -1);
        changeChild("火炎渦", &pack);
    } else {
        setFailed();
    }
}

// 0x710057a908
void SiteBossLswordAttackRoot::sub_710057A908(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addString("SiteBossBigFlameBall1", "ThrowActorName", -1);
    pack.addVec3(pos, "TargetPos", -1);
    pack.addInt(0, "RailIndex", -1);
    pack.addBool(false, "IsReturnHome", -1);
    pack.addBool(false, "IsForceWarp", -1);
    pack.addBool(!act::SiteBoss::sub_71002D3804(mActor, "WearFlame"), "IsPartsActorTgOn", -1);
    if (auto* target = sub_71005D9050(mActor)) {
        pack.addActor(*target, "TargetActor", -1);
        pack.addBool(false, "IsPartsWarpEffectSync", -1);
        changeChild("大火球投げ", &pack);
        _a0 = *mHighSlashRate_s;
        _a4 = *mCrossSlashRate_s;
        _a8 = *mWhirlSlashRate_s;
        _ac = 0;
        _b0 = 0;
        _fc = ksys::Timer(*mForceApproachCount_s, *mForceApproachCount_s);
    } else {
        setFailed();
    }
}

}  // namespace uking::ai
