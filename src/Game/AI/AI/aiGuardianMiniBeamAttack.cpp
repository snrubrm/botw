#include "Game/AI/AI/aiGuardianMiniBeamAttack.h"
#include <cmath>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardianMini.h"

namespace uking::ai {

// NON_MATCHING: float register numbering of the four loads of the direction to the target (the original uses s0 / s2 and
// s1 / s3 for the two component pairs); same operations
bool GuardianMiniBeamAttack::sub_710041740C(const sead::Vector3f& target) {
    auto* actor = mActor;
    if (actor) {
        if (auto* model = actor->getModel()) {
            const auto key = model->searchBone(mHeadNodeName_s.cstr());
            if (key.isValid()) {
                sead::Matrix34f mtx;
                actor->getModel()
                    ->getUnits()
                    .unsafeAt(key.model_unit_index)
                    ->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
                sead::Vector3f dir;
                mtx.getBase(dir, 2);
                dir.y = 0.0f;
                dir.normalize();
                sead::Vector3f to_target;
                to_target.x = target.x - actor->getMtx().m[0][3];
                to_target.y = 0.0f;
                to_target.z = target.z - actor->getMtx().m[2][3];
                to_target.normalize();
                const f32 dot = sead::Mathf::clamp(dir.dot(to_target), -1.0f, 1.0f);
                const f32 angle = sead::Mathf::acos(dot);
                return angle >= -*mInDirAngle_s && angle <= *mInDirAngle_s;
            }
        }
    }
    return false;
}

// NON_MATCHING: same as sub_710041740C (the original has this copy with `_2b8` inlined)
bool GuardianMiniBeamAttack::sub_710041760C() {
    auto* actor = mActor;
    if (actor) {
        if (auto* model = actor->getModel()) {
            const auto key = model->searchBone(mHeadNodeName_s.cstr());
            if (key.isValid()) {
                sead::Matrix34f mtx;
                actor->getModel()
                    ->getUnits()
                    .unsafeAt(key.model_unit_index)
                    ->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
                sead::Vector3f dir;
                mtx.getBase(dir, 2);
                dir.y = 0.0f;
                dir.normalize();
                sead::Vector3f to_target;
                to_target.x = _2b8.x - actor->getMtx().m[0][3];
                to_target.y = 0.0f;
                to_target.z = _2b8.z - actor->getMtx().m[2][3];
                to_target.normalize();
                const f32 dot = sead::Mathf::clamp(dir.dot(to_target), -1.0f, 1.0f);
                const f32 angle = sead::Mathf::acos(dot);
                return angle >= -*mInDirAngle_s && angle <= *mInDirAngle_s;
            }
        }
    }
    return false;
}

// NON_MATCHING: the copy of *m35() goes through a 64-bit load with y kept in a register in the
// original; scheduling of the final stores differs.
void GuardianMiniBeamAttack::sub_7100417800() {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* model = actor->getModel();
    if (!model)
        return;
    const auto key = model->searchBone(mHeadNodeName_s.cstr());
    if (!key.isValid())
        return;
    sead::Matrix34f mtx;
    actor->getModel()
        ->getUnits()
        .unsafeAt(key.model_unit_index)
        ->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
    sead::Vector3f dir;
    mtx.getBase(dir, 2);
    dir.y = 0.0f;
    dir.normalize();
    const f32 head_x = mtx.m[0][3];
    const f32 head_z = mtx.m[2][3];
    sead::Vector3f pos = *m35();
    const f32 dx = pos.x - head_x;
    const f32 dz = pos.z - head_z;
    const f32 dist = std::sqrt(dx * dx + dz * dz);
    pos.x = head_x + dir.x * dist;
    pos.z = head_z + dir.z * dist;
    getCurrentChild()->setDynamicParam(pos, "TargetPos");
}

// NON_MATCHING: stack slot of `front` and the store order of the target direction differ; the
// calls and constants (0.15, 12 and 1 degree in radians) match.
void GuardianMiniBeamAttack::sub_71004179D4(const sead::Vector3f& target) {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* model = actor->getModel();
    if (!model)
        return;
    sead::Vector3f to_target = target;
    to_target.set(to_target.x - actor->getMtx().m[0][3], 0.0f,
                  to_target.z - actor->getMtx().m[2][3]);
    to_target.normalize();
    sead::Vector3f front;
    const auto key = model->searchBone("Neck");
    if (!key.isValid())
        return;
    sead::Matrix34f mtx;
    model->getUnits()
        .unsafeAt(key.model_unit_index)
        ->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
    mtx.getBase(front, 2);
    front.y = 0.0f;
    front.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    angle *= axis.y;
    angle = ksys::util::sub_71011EF0CC(angle);
    ksys::VFR::lerp(&_2d0, -angle, 0.15f, 0.20943952f, 0.017453292f);
    sub_71005DB44C(actor, _2d0, 0.0f);
}

GuardianMiniBeamAttack::GuardianMiniBeamAttack(const InitArg& arg) : MiniBeamAttack(arg) {}

// The SafeString members make the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
GuardianMiniBeamAttack::~GuardianMiniBeamAttack() { ; }

void GuardianMiniBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    MiniBeamAttack::enter_(params);
    _2c4 = ksys::Timer(*mAttackInterval_s, *mAttackInterval_s);
    if (*mAttackInterval_s >= 0)
        sub_710033F27C(0);
    if (isCurrentChild("戦闘準備")) {
        if (auto* as_list = mActor->getASList()) {
            if (!mLoopShaderASName_s.isEmpty())
                as_list->startAnimationMaybe(-1.0f, -1.0f, mLoopShaderASName_s.cstr(), 0, 1, true);
        }
    }
}

void GuardianMiniBeamAttack::leave_() {
    sub_71005DB498(mActor);
    MiniBeamAttack::leave_();
}

bool GuardianMiniBeamAttack::isChangeable() const {
    if (!*mIsChangeable_s)
        return false;
    return getCurrentChild()->isChangeable();
}

void GuardianMiniBeamAttack::loadParams_() {
    MiniBeamAttack::loadParams_();
    getStaticParam(&mHeadNodeName_s, "HeadNodeName");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mEndShaderASFrame_s, "EndShaderASFrame");
    getStaticParam(&mLoopShaderASName_s, "LoopShaderASName");
    getStaticParam(&mEndShaderASName_s, "EndShaderASName");
    getStaticParam(&mPreLaunchEffectName_s, "PreLaunchEffectName");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsFinalBattle_s, "IsFinalBattle");
    getStaticParam(&mInDirAngle_s, "InDirAngle");
}

// NON_MATCHING: the original tail-calls sub_71005D960C, so that function returns a pointer; our reference
// declaration (shared with ~12 users) makes clang keep a frame (return attribute mismatch, see MiniBeamAttack::m35)
const sead::Vector3f* GuardianMiniBeamAttack::m35() {
    if (*mIsFinalBattle_s)
        return &sub_71005D960C(mActor);
    return &_2b8;
}

// NON_MATCHING: same loads and offsets; clang selects the two parameter addresses (csel) where the original
// branches to two separate returns
const sead::SafeString& GuardianMiniBeamAttack::m36() {
    if (!mBreathName_s.isEmpty())
        return mBreathName_s;
    auto* params = mActor->getParam()->getRes().mGParamList;
    if (!params)
        return sead::SafeString::cEmptyString;
    auto* mini = params->getGuardianMini();
    if (!mini)
        return sead::SafeString::cEmptyString;
    if (*mIsFinalBattle_s)
        return mini->mFinalBeamName.ref();
    return mini->mBeamName.ref();
}

bool GuardianMiniBeamAttack::m38() {
    if (*mAttackInterval_s < 0)
        return BreathAttackEnemyBattle::m38();
    return _2c4.value <= sead::Mathf::epsilon();
}

void GuardianMiniBeamAttack::m41() {
    if (auto* beam = sead::DynamicCast<act::BeamBase>(_90.getProc())) {
        beam->sub_7100002DA8(mActor);
        beam->_c38.acquire(mActor, false);
    }
    MiniBeamAttack::m41();
}

bool GuardianMiniBeamAttack::m46(sead::Vector3f* out) {
    if (!out)
        return false;
    *out = sub_71005D9330(mActor);
    return true;
}

void GuardianMiniBeamAttack::m37() {
    _2c4 = ksys::Timer(*mAttackInterval_s, *mAttackInterval_s);
    m46(&_2b8);
    if (sub_710041760C()) {
        _2d0 = sub_71005DB4DC(mActor);
        if (!mPreLaunchEffectName_s.isEmpty())
            xlinkSearchAndEmit(mActor, mPreLaunchEffectName_s.cstr(), 2, nullptr);
        MiniBeamAttack::m37();
        return;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_2b8, "TargetPos", -1);
    changeChild("ビーム準備", &pack);
}

}  // namespace uking::ai
