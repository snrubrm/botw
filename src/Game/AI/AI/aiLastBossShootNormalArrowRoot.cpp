#include "Game/AI/AI/aiLastBossShootNormalArrowRoot.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::ai {

LastBossShootNormalArrowRoot::LastBossShootNormalArrowRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LastBossShootNormalArrowRoot::~LastBossShootNormalArrowRoot() {
    if (!mArrowNum_s)
        return;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;
    for (u32 i = 0; i < u32(*mArrowNum_s); ++i) {
        sead::FormatFixedSafeString<32> name("%s%d", mPartsName_s.cstr(), i);
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->_1128.getActorPartsActor(name), &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->_1128.sub_7100D3CFEC(name);
    }
}

bool LastBossShootNormalArrowRoot::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel())
        _228.search(model, "Wrist_ML");
    else
        _228.getKey().reset();

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    if (!sub_71005D6D10()) {
        for (u32 i = 0; i < u32(*mArrowNum_s); ++i) {
            sead::FormatFixedSafeString<32> name("%s%d", mPartsName_s.cstr(), i);
            if (enemy->_1128.getActorPartsActor(name).hasProc())
                continue;
            enemy->_1128.sub_7100D3CED8(name, heap);
            if (auto* arrow = m40())
                enemy->_1128.sub_7100D3D108(name, arrow);
        }
    }
    return true;
}

void LastBossShootNormalArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _a0 = 0;
    m34();
    _a4 = 100.0f;
    _a8 = 100.0f;
    _ac = -1.0f;
    _d8.setName("Arm_1_ML");
    _180.setName("Arm_2_ML");
    _180._68 = sead::Matrix34f::ident;
    _d8._68 = sead::Matrix34f::ident;
    mActor->boneHandleStuff(&_180, false);
    mActor->boneHandleStuff(&_d8, false);
    _b0.set(1, 0, 0, 0);
    _c0.set(1, 0, 0, 0);
    _d0 = 0.1f;
    mFlags.set(Flag::Changeable);
}

void LastBossShootNormalArrowRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child)
        return;

    child->setDynamicParam(*mTargetPos_d, "TargetPos");
    sub_71005D7444(mActor, *mTargetPos_d, true, true);
    sub_71005DB51C(mActor, *mBattleNodeOffsetLR_s, false);
    sub_71005DB558(mActor, *mBattleNodeOffsetUD_s, false);

    if (isCurrentChild("準備")) {
        if (sub_71005DD798(mActor, 44, nullptr, 0, 0))
            sub_710047CA1C(*mTargetPos_d);
        if (child->isFinished() || child->isFailed())
            m35();
    } else if (isCurrentChild("弾発射")) {
        if (sub_71005DD798(mActor, 44, nullptr, 0, 0))
            sub_710047CA1C(*mTargetPos_d);
        if (child->isFinished() || child->isFailed()) {
            if (m38())
                m36();
            else if (*mIsPrepreNextArrow_s)
                m34();
            else
                m35();
        }
    }
}

void LastBossShootNormalArrowRoot::leave_() {
    mActor->sub_71011DA868(&_180);
    mActor->sub_71011DA868(&_d8);
    sub_71005D74E8(mActor);
    sub_71005DB51C(mActor, 0.0f, false);
    sub_71005DB558(mActor, 0.0f, false);
}

void LastBossShootNormalArrowRoot::loadParams_() {
    getStaticParam(&mArrowNum_s, "ArrowNum");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mBattleNodeOffsetLR_s, "BattleNodeOffsetLR");
    getStaticParam(&mBattleNodeOffsetUD_s, "BattleNodeOffsetUD");
    getStaticParam(&mIsPrepreNextArrow_s, "IsPrepreNextArrow");
    getStaticParam(&mArrowName_s, "ArrowName");
    getStaticParam(&mPartsName_s, "PartsName");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool LastBossShootNormalArrowRoot::isFinished() const {
    if (!isCurrentChild("終了"))
        return false;
    auto* child = getCurrentChild();
    return child->isFinished() || child->isFailed();
}

void LastBossShootNormalArrowRoot::m34() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    m37(&pos);
    params.addVec3(pos, "TargetPos", -1);
    changeChild("準備", &params);
}

void LastBossShootNormalArrowRoot::m35() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    m37(&pos);
    params.addVec3(pos, "TargetPos", -1);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FormatFixedSafeString<32> name("%s%d", mPartsName_s.cstr(), _a0);
        params.addActor(enemy->_1128.getActorPartsActor(name), "IgniteActor", -1);
    }
    params.addPointer(nullptr, "ArrowHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    params.addInt(_a0, "Index", -1);
    params.addInt(m39(), "AtAttr", -1);
    changeChild("弾発射", &params);
    ++_a0;
}

void LastBossShootNormalArrowRoot::m36() {
    sub_71005D74E8(mActor);
    sub_71005DB51C(mActor, 0.0f, false);
    sub_71005DB558(mActor, 0.0f, false);
    changeChild("終了");
}

void LastBossShootNormalArrowRoot::m37(sead::Vector3f* pos) {
    *pos = *mTargetPos_d;
}

bool LastBossShootNormalArrowRoot::m38() {
    return _a0 >= u32(*mArrowNum_s);
}

s32 LastBossShootNormalArrowRoot::m39() {
    return 10;
}

ksys::act::Actor* LastBossShootNormalArrowRoot::m40() {
    ksys::act::InstParamPack pack;
    pack->add(*mAttackPower_s, "AttackPower");
    pack->add(*mAtMinDamage_s, "AtMinDamage");
    pack->add(*mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    pack->add(*mReflectOffset_s, "PosOffset");
    return sead::DynamicCast<ksys::act::Actor>(ksys::act::ActorCreator::instance()->createActor(
        mArrowName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true,
        false));
}

}  // namespace uking::ai
