#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"
#include <gsys/gsysModelAccessKey.h>

namespace ksys::act {
class Actor;
class BaseProcLink;
namespace ai {
class ActionBase;
}  // namespace ai
}  // namespace ksys::act

namespace uking::act {
class Enemy;
}

// 0x710073e9a8 (declared only; lane3 s20): the parts link `name` of the DynamicCast<Enemy> of `actor`
// (Enemy::getActorPartsActor), the dummy link if the actor is not an enemy. Free function in the TU before
// Unk_710073ebd4.
ksys::act::BaseProcLink& sub_710073E9A8(ksys::act::Actor* actor, const sead::SafeString& name);

// Placeholder name = constructor address (0x710073ebd4; no real name known). Parameter / state object of
// the "vacuum shoot" actions (an enemy shoots a vacuumed item at a target): embedded in
// ForkVacuumShootToTarget (+0x20), PredictVacuumShoot (+0x78) and VacuumedItemShootToTarget (+0x48).
// The actions' loadParams_ forward to sub_710073ED20 (which reads the params through ActionBase's
// protected getStaticParam: friend of ActionBase).
class Unk_710073ebd4 {
public:
    explicit Unk_710073ebd4(ksys::act::Actor* actor);
    // 0x710073ecbc: out-of-line, empty.
    ~Unk_710073ebd4();

    // 0x710073ecc0: searches the bone `mBaseNode_s` in the enemy's model (if the name is not empty); returns true.
    bool sub_710073ECC0();
    // 0x710073ed20: reads all the static params and the dynamic "TargetPos" through `action`.
    void sub_710073ED20(const ksys::act::ai::ActionBase* action);
    // 0x710073eee4: reads the dynamic "TargetVel" through `action`.
    void sub_710073EEE4(const ksys::act::ai::ActionBase* action);
    // 0x710073ef50: copies the "PartsKey" name to the work string, returns whether the enemy's parts actor
    // of that name is asleep.
    bool sub_710073EF50(const ksys::act::ai::ActionBase* action);
    // 0x710073fa54: starts the shoot AS (ASList::x(0x47, ...)).
    bool sub_710073FA54();
    // 0x710073f040: the shoot step of the actions' m32 (declared only).
    void sub_710073F040();
    // 0x710073f14c (declared only).
    void sub_710073F14C(const sead::Vector3f* a1);

    /* 0x00 */ const s32* mSeqBank_s{};
    /* 0x08 */ const s32* mTargetBone_s{};
    /* 0x10 */ const f32* mShootSpeed_s{};
    /* 0x18 */ const f32* mMaxNoiseDist_s{};
    /* 0x20 */ const f32* mOffsetHeight_s{};
    /* 0x28 */ sead::SafeString mPartsKey_s;
    /* 0x38 */ sead::SafeString mBaseNode_s;
    /* 0x48 */ const sead::Vector3f* mShootOffset_s{};
    /* 0x50 */ const sead::Vector3f* mShootRotate_s{};
    /* 0x58 */ const sead::Vector3f* mShootRotSpeed_s{};
    /* 0x60 */ const sead::Vector3f* mDirMinAngle_s{};
    /* 0x68 */ const sead::Vector3f* mDirMaxAngle_s{};
    /* 0x70 */ sead::Vector3f* mDynTargetPos_d{};
    /* 0x78 */ sead::Vector3f* mDynTargetVel_d{};
    /* 0x80 */ ksys::act::Actor* mActor;  // the DynamicCast<Enemy> of the owner's actor
    /* 0x88 */ gsys::BoneAccessKey mBone;
    /* 0x90 */ sead::SafeString mWork;
    /* 0xa0 */ bool mIsReuseBullet = false;  // copy of the action's IsReuseBullet (set in enter_)
};
KSYS_CHECK_SIZE_NX150(Unk_710073ebd4, 0xa8);
