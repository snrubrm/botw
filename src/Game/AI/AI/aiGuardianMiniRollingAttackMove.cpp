#include "Game/AI/AI/aiGuardianMiniRollingAttackMove.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianMiniRollingAttackMove::GuardianMiniRollingAttackMove(const InitArg& arg)
    : EnemyRangeKeepMove(arg) {}

GuardianMiniRollingAttackMove::~GuardianMiniRollingAttackMove() = default;

bool GuardianMiniRollingAttackMove::init_(sead::Heap* heap) {
    return EnemyRangeKeepMove::init_(heap);
}

void GuardianMiniRollingAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
}

void GuardianMiniRollingAttackMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void GuardianMiniRollingAttackMove::sub_71004238F0() {
    setDamageCallbackTiming(mActor, 4, &_2d0);
    if (*mAttackType_s == 1) {
        if (auto* damage_mgr = mActor->getDamageMgr()) {
            if (!_328.mDamageManager)
                damage_mgr->addDamageCallback(4, &_328);
        }
    }
    sub_7100423A1C();

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("バックステップ", &pack);
}

// NON_MATCHING: stack slots of the BoneAccessKey temporaries (the original uses a separate slot per inlined
// group: frame 0x70 instead of 0x60)
void GuardianMiniRollingAttackMove::sub_7100423A1C() {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* model = actor->getModel();
    if (!model)
        return;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;

    const auto root = model->searchBone(mRootNodeName_s.cstr());
    const auto attack = actor->getModel()->searchBone(mAttackNodeName_s.cstr());
    if (!root.isValid() || !attack.isValid())
        return;

    as_list->sub_710115C9E0(0);
    as_list->mSlots[0].sub_7101165008(root, 0, true);
    as_list->mSlots[0].sub_7101165008(attack, 3, true);
    as_list->mSlots[0].sub_7101164E38(false);
    as_list->sub_710115C9E0(1);
    as_list->mSlots[1].sub_7101165008(root, 3, true);
    as_list->mSlots[1].sub_7101165008(attack, 0, true);
    as_list->mSlots[1].sub_7101164E38(false);
    as_list->startAnimationMaybe(-1.0f, -1.0f, mAttackASName_s.cstr(), 1, 0, true);
}

void GuardianMiniRollingAttackMove::sub_7100423D68() {
    if (*mAttackType_s == 1) {
        sub_71005DA114(mActor, &_2d0);
        if (auto* damage_mgr = mActor->getDamageMgr()) {
            if (_328.mDamageManager)
                damage_mgr->removeDamageCallback(&_328);
        }
        sub_7100424554();
    } else {
        _210 = 5.0f;
        _214 = 5.0f;
        _218 = -1.0f;
    }

    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, mAttackASName_s.cstr(), 1, 0, true);
    _1e4 = _1e0 = *mRollingWaitTime_s;
    _1e8 = -1.0f;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("回転待機", &pack);
}

// NON_MATCHING: the loads of mBackWalkRollingStartTime_s / mBackWalkMinTime_s are merged into one ldp and
// the constant stores are scheduled differently
void GuardianMiniRollingAttackMove::sub_7100423F0C() {
    setDamageCallbackTiming(mActor, 4, &_2d0);
    _210 = 5.0f;
    _200 = -1.0f;
    _1fc = _1f8 = *mBackWalkRollingStartTime_s;
    _214 = 5.0f;
    _218 = -1.0f;
    _244 = 0.0f;
    _248 = sead::Mathf::abs(*mBackWalkRotSpeedRatio_s / 60.0f);
    mActor->getMtx().getTranslation(_22c);
    _1f4 = -1.0f;
    _1f0 = _1ec = *mBackWalkMinTime_s;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("回転後退", &pack);
}

void GuardianMiniRollingAttackMove::sub_7100424080() {
    sub_71005DA114(mActor, &_2d0);
    _1e4 = _1e0 = s32(f32(s32(_1ec)) + 30.0f);
    _1e8 = -1.0f;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("回転待機", &pack);
}

void GuardianMiniRollingAttackMove::sub_7100424554() {
    if (*mAttackType_s == 0 && !(_204 <= sead::Mathf::epsilon()))
        return;
    auto* actor = mActor;
    if (!actor)
        return;
    for (int i = 0; i < 3; ++i) {
        sead::SafeString name = "Left";
        sub_71005D7ADC(actor, i, 0x102, &name, nullptr, 1, 1, 0, 1, 1.0f, 1.0f);
    }
}

void GuardianMiniRollingAttackMove::sub_7100424670() {
    auto* actor = mActor;
    if (!actor)
        return;
    for (int i = 0; i < 3; ++i) {
        sead::SafeString name = "Right";
        sub_71005D7ADC(actor, i, 1, &name, nullptr, 1, 1, 0, 1, 1.0f, 1.0f);
    }
}

void GuardianMiniRollingAttackMove::sub_7100424A3C() {
    auto* actor = mActor;
    if (!actor)
        return;
    for (int i = 0; i < 3; ++i) {
        sead::BitFlag8 flags(4);
        sead::SafeString name = "Left";
        sub_71005D7ADC(actor, i, 0x1102, &name, &flags, 1, *mRushAttackImpulse_s, 0, 1, 1.0f, 1.0f);
    }
}

void GuardianMiniRollingAttackMove::m36() {
    sub_7100424554();
    sub_71005DA114(mActor, &_2d0);
}

void GuardianMiniRollingAttackMove::m37() {
    if (*mAttackType_s == 1) {
        const s32 time = *mBreakPillarTime_s;
        if (time <= 0) {
            sub_7100424A3C();
        } else {
            const f32 time_f = time;
            _224 = -1.0f;
            _220 = _21c = time_f;
            sub_7100424554();
        }
    } else {
        sub_7100424554();
    }
    sub_71005DA114(mActor, &_2d0);
}

void GuardianMiniRollingAttackMove::m38() {
    sub_7100424554();
    sub_71005DA114(mActor, &_2d0);
}

void GuardianMiniRollingAttackMove::m40() {
    sub_7100424554();
    sub_71005DA114(mActor, &_2d0);
}

void GuardianMiniRollingAttackMove::sub_7100421B50() {
    auto* actor = mActor;
    if (!actor)
        return;
    for (int i = 0; i < 3; ++i)
        sub_71005D79AC(actor, i, act::Unk_71002edaec(1));
}

void GuardianMiniRollingAttackMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mAttackNodeName_s, "AttackNodeName");
    getStaticParam(&mAttackASName_s, "AttackASName");
    getStaticParam(&mRollingNumMin_s, "RollingNumMin");
    getStaticParam(&mRollingNumMax_s, "RollingNumMax");
    getStaticParam(&mRollingWaitTime_s, "RollingWaitTime");
    getStaticParam(&mRollingIntervalTime_s, "RollingIntervalTime");
    getStaticParam(&mStopRollingNum_s, "StopRollingNum");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mBackWalkRotSpeedRatio_s, "BackWalkRotSpeedRatio");
    getStaticParam(&mRushRotSpeedRatio_s, "RushRotSpeedRatio");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mBackWalkMinTime_s, "BackWalkMinTime");
    getStaticParam(&mBackWalkRollingStartTime_s, "BackWalkRollingStartTime");
    getStaticParam(&mBackWalkDist_s, "BackWalkDist");
    getStaticParam(&mRushAttackImpulse_s, "RushAttackImpulse");
    getStaticParam(&mRollingStopTime_s, "RollingStopTime");
    getStaticParam(&mIsValidChanceTime_s, "IsValidChanceTime");
    getStaticParam(&mCrashDamage_s, "CrashDamage");
    getStaticParam(&mBreakPillarTime_s, "BreakPillarTime");
}

}  // namespace uking::ai
