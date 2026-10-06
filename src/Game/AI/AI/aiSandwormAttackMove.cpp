#include "Game/AI/AI/aiSandwormAttackMove.h"
#include <math/seadVector.h>
#include <math/seadMathCalcCommon.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SandwormAttackMove::SandwormAttackMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormAttackMove::~SandwormAttackMove() = default;

bool SandwormAttackMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: scheduling of the two address computations for search()
void SandwormAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _70._30.search(_70._28, mDamageBaseNode_s);
    _70._68 = *mDamageAngle_s;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("攻撃移動", &pack);
}

void SandwormAttackMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("攻撃移動")) {
            sub_71005DA114(mActor, &_70);
            if (sub_710072E368(mActor))
                sub_71005570C4();
            else
                setFinished();
            return;
        }
        setFinished();
    } else if (child->isChangeable()) {
        if (isCurrentChild("離脱")) {
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
            if (diff.length() > *mSecessionDist_s || !sub_710072E368(mActor))
                setFinished();
        } else if (isCurrentChild("攻撃移動")) {
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
            if (diff.length() > *mLostDist_s)
                setFailed();
        }
    }

    if (isCurrentChild("攻撃移動"))
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void SandwormAttackMove::leave_() {
    sub_71005DA114(mActor, &_70);
}

void SandwormAttackMove::loadParams_() {
    getStaticParam(&mSecessionDist_s, "SecessionDist");
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mDamageAngle_s, "DamageAngle");
    getStaticParam(&mLostDist_s, "LostDist");
    getStaticParam(&mDamageBaseNode_s, "DamageBaseNode");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: operand order of the three fmul (v * t in the original)
void SandwormAttackMove::sub_71005570C4() {
    const auto& mtx = mActor->getMtx();
    sead::Vector3f pos;
    mtx.getBase(pos, 2);
    pos = pos * *mSecessionDist_s + mtx.getTranslation();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("離脱", &pack);
}

// NON_MATCHING: one fadd operand order: the original sums the flattened direction's squared length as
// z*z + (x*x + y*y), ours as (x*x + y*y) + z*z; everything else is identical
// 0x71005569cc
void Unk_710241b460::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (*a4 != 4)
        return;
    auto* manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
    if (!manager)
        return;
    auto* attacker = manager->m37();
    if (!attacker->hasProc())
        return;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(attacker, &accessor);
    const sead::Matrix34f& attacker_mtx = accessor.getActorMtx();
    f32 attacker_x = attacker_mtx.m[0][3];
    f32 attacker_z = attacker_mtx.m[2][3];

    f32 origin_x, origin_z;
    if (_30.isValid()) {
        const auto& key = _30.getKey();
        sead::Matrix34f bone_mtx;
        _28->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
            &bone_mtx, key.bone_index);
        origin_x = bone_mtx.m[0][3];
        origin_z = bone_mtx.m[2][3];
    } else {
        origin_x = _28->getMatrix().m[0][3];
        origin_z = _28->getMatrix().m[2][3];
    }
    sead::Vector3f dir(attacker_x - origin_x, 0, attacker_z - origin_z);
    dir.normalize();
    sead::Vector3f front;
    _28->getMatrix().getBase(front, 2);
    front.y = 0;
    front.normalize();
    if (dir.dot(front) >= std::cos(_68)) {
        *a1 = s32(f32(*a1) * 3.0f);
        *a5 = 19;
    }
}

}  // namespace uking::ai
