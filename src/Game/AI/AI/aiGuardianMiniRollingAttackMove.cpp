#include "Game/AI/AI/aiGuardianMiniRollingAttackMove.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// NON_MATCHING: the original compares the animation name with "PreSpin" without the two assureTermination virtual calls
// (inline loop over `mStringTop`)
void Unk_71023f9310::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (*_28->mAttackType_s != 1)
        return;
    if (!_28->isCurrentChild("回転予兆") && !_28->isCurrentChild("バックステップ") &&
        !_28->isCurrentChild("回転後退") && !_28->isCurrentChild("回転待機"))
        return;
    if (_28 && _28->isCurrentChild("回転予兆")) {
        if (auto* actor = _28->getActor()) {
            if (auto* as_list = actor->getASList()) {
                if (as_list->x_1(0, 0) != "PreSpin")
                    return;
            }
        }
    }
    if (*a5 == 22) {
        *a5 = 2;
        _28->_358 = true;
    }
}

GuardianMiniRollingAttackMove::GuardianMiniRollingAttackMove(const InitArg& arg)
    : EnemyRangeKeepMove(arg), _2a8() {}

GuardianMiniRollingAttackMove::~GuardianMiniRollingAttackMove() {
    if (_250) {
        delete _250;
        _250 = nullptr;
    }
}

bool GuardianMiniRollingAttackMove::init_(sead::Heap* heap) {
    if (!EnemyRangeKeepMove::init_(heap))
        return false;
    _250 = new (heap) Unk_71023f83e8(mActor, 0x8000021);
    return _250 != nullptr;
}

void GuardianMiniRollingAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
    _22a = false;
    _2c9 = 0;
    _2c8 = 0;
    _229 = 0;
    _228 = 0;
    _358 = false;
    _204.value = 0.0f;
    _204.previous_value = 0.0f;
    _204.rate = -1.0f;
    _210.value = 0.0f;
    _210.previous_value = 0.0f;
    _210.rate = -1.0f;
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        if (!_2f8.mDamageManager)
            damage_mgr->addDamageCallback(1, &_2f8);
    }
    sub_71004219B8();
    sub_7100421B50();
}

void GuardianMiniRollingAttackMove::sub_71004219B8() {
    setDamageCallbackTiming(mActor, 4, &_2d0);
    if (*mAttackType_s == 1) {
        if (auto* damage_mgr = mActor->getDamageMgr()) {
            if (!_328.mDamageManager)
                damage_mgr->addDamageCallback(4, &_328);
        }
    }
    auto* actor = mActor;
    if (actor && actor->getModel() && actor->getASList()) {
        actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
        actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163100, 0.0f);
        actor->getASList()->sub_710115C11C();
        actor->getASList()->sub_710115BED4(true);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("回転予兆", &pack);
}

void GuardianMiniRollingAttackMove::changeToBackStep() {
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
        _210.previous_value = _210.value = 5.0f;
        _210.rate = -1.0f;
    }

    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, mAttackASName_s.cstr(), 1, 0, true);
    _1e0.previous_value = _1e0.value = *mRollingWaitTime_s;
    _1e0.rate = -1.0f;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("回転待機", &pack);
}

// NON_MATCHING: the loads of mBackWalkRollingStartTime_s / mBackWalkMinTime_s are merged into one ldp and
// the constant stores are scheduled differently
void GuardianMiniRollingAttackMove::changeToRotateBack() {
    setDamageCallbackTiming(mActor, 4, &_2d0);
    _210.value = 5.0f;
    _1f8.rate = -1.0f;
    _1f8.previous_value = _1f8.value = *mBackWalkRollingStartTime_s;
    _210.previous_value = 5.0f;
    _210.rate = -1.0f;
    _244 = 0.0f;
    _248 = sead::Mathf::abs(*mBackWalkRotSpeedRatio_s / 60.0f);
    mActor->getMtx().getTranslation(_22c);
    _1ec.rate = -1.0f;
    _1ec.value = _1ec.previous_value = *mBackWalkMinTime_s;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("回転後退", &pack);
}

void GuardianMiniRollingAttackMove::sub_7100424080() {
    sub_71005DA114(mActor, &_2d0);
    _1e0.previous_value = _1e0.value = s32(f32(s32(_1ec.value)) + 30.0f);
    _1e0.rate = -1.0f;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("回転待機", &pack);
}

void GuardianMiniRollingAttackMove::sub_7100424554() {
    if (*mAttackType_s == 0 && !(_204.value <= sead::Mathf::epsilon()))
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

void GuardianMiniRollingAttackMove::changeToRotateEnd() {
    sub_71005DA114(mActor, &_2d0);
    auto* actor = mActor;
    _2c8 = 1;
    if (actor && actor->getModel() && actor->getASList()) {
        actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
        actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163100, 0.0f);
        actor->getASList()->sub_710115C11C();
        actor->getASList()->sub_710115BED4(true);
    }
    actor = mActor;
    if (actor && actor->getModel() && actor->getASList())
        actor->getASList()->sub_710115B01C(1, 0, true);
    sub_7100421B50();
    _2a8.fadeXLink();
    changeChild("回転終了", nullptr);
}

void GuardianMiniRollingAttackMove::changeToChance() {
    sub_71005DA114(mActor, &_2d0);
    auto* actor = mActor;
    _2c8 = 1;
    if (actor && actor->getModel() && actor->getASList()) {
        actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
        actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163100, 0.0f);
        actor->getASList()->sub_710115C11C();
        actor->getASList()->sub_710115BED4(true);
    }
    sub_7100421B50();
    _2a8.fadeXLink();

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("チャンス", &pack);
}

void GuardianMiniRollingAttackMove::leave_() {
    _2a8.fadeXLink();
    sub_7100421B50();
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        if (_2f8.mDamageManager)
            damage_mgr->removeDamageCallback(&_2f8);
    }
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        if (_328.mDamageManager)
            damage_mgr->removeDamageCallback(&_328);
    }
    sub_71005DA114(mActor, &_2d0);
    const sead::SafeString current = mActor->getASList()->x_1(0, 1);
    if (current == "ChanceWaitShader")
        mActor->getASList()->sub_710115B140("WaitBattleShader", 0, 0, 1, 1);
    EnemyRangeKeepMove::leave_();
}

bool GuardianMiniRollingAttackMove::handleMessage_(const ksys::Message* message) {
    if (!_258.m2(*message) || !_258._34._10)
        return false;

    _258.x();
    if (isCurrentChild("回転終了") || isCurrentChild("回転後退終了") || isCurrentChild("チャンス"))
        return true;

    if (isCurrentChild("戦闘待機") && *mAttackType_s == 1) {
        if (!_22a && *mIsValidChanceTime_s)
            changeToChance();
        else
            changeToRotateEnd();
        return true;
    }

    if (_2c9) {
        _2c9 = 0;
        if (auto* damage_mgr = mActor->getDamageMgr()) {
            if (_328.mDamageManager)
                damage_mgr->removeDamageCallback(&_328);
        }
        _2c8 = 1;
        sub_7100424554();
        sub_71005DA114(mActor, &_2d0);
        changeChild("回転後退終了", nullptr);
        return true;
    }

    if (_229 < _228) {
        _204.previous_value = _204.value = *mRollingIntervalTime_s;
        _204.rate = -1.0f;
        sub_7100421B50();
    } else {
        changeToRotateEnd();
    }
    return true;
}

int GuardianMiniRollingAttackMove::m35() {
    auto* actor = mActor;
    if (!sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return -1;

    static_cast<uking::act::Enemy*>(actor)->getWeapons();
    int best_idx = -1;
    f32 best = -1.0f;
    for (int i = 0; i < 6; ++i) {
        auto* weapon = static_cast<uking::act::Enemy*>(actor)->getWeapons()->getEquippedWeapon(i);
        if (!sead::IsDerivedFrom<uking::act::Weapon>(weapon))
            continue;
        if (weapon->getProfile() == "WeaponShield")
            continue;
        const f32 value = sub_71007320F0(actor, i);
        if (value > best) {
            best = value;
            best_idx = i;
        }
    }
    return best_idx;
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
            _21c.rate = -1.0f;
            _21c.previous_value = _21c.value = time_f;
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
