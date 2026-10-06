#include "Game/AI/AI/aiLynelAttackThroughMove.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

LynelAttackThroughMove::LynelAttackThroughMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelAttackThroughMove::~LynelAttackThroughMove() = default;

bool LynelAttackThroughMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelAttackThroughMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* nav = actor->m45()) {
        if (auto* link = sub_71005D9050(actor)) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            if (auto* other = accessor.sub_7100D0F57C())
                nav->sub_7100F7D1B4(other);
        }
    }
    _94 = _98 = *mParams.mCliffFailTime_s;
    actor->getMtx().getTranslation(_78);
    sub_710048BF14();
}

void LynelAttackThroughMove::sub_710048BF14() {
    s32 value = _94;
    if (_98 != _94)
        value = sead::GlobalRandom::instance()->getS32Range(_94, _98);
    _90 = value;

    const sead::Vector3f* pos = mParams.mTargetPos_d;
    const s32 type = *mParams.mSideOffsetDirType_s;
    sead::Vector3f target;
    if (type == 0) {
        target = *pos;
    } else {
        sead::Vector3f dir;
        mActor->getMtx().getBase(dir, 0);
        dir.normalize();
        if (type == 2)
            dir = -dir;
        const f32 offset = *mParams.mSideOffset_s;
        target.x = dir.x * offset + pos->x;
        target.y = dir.y * offset + pos->y;
        target.z = dir.z * offset + pos->z;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("近づき", &pack);
}

// NON_MATCHING: the original loads the actor position before the target position and stores the y component of
// the direction last (load / store order only).
bool LynelAttackThroughMove::sub_710048C58C(const sead::Vector3f& target) {
    sead::Vector3f to_target(target.x - mActor->getMtx().m[0][3], 0.0f,
                             target.z - mActor->getMtx().m[2][3]);
    const f32 dist = to_target.normalize();
    sead::Vector3f forward;
    mActor->getMtx().getBase(forward, 2);
    forward.y = 0;
    forward.normalize();
    const f32 reach = *mParams.mAcceptableRadius_s + sub_71007320F0(mActor, *mParams.mWeaponIdx_s);
    if (forward.dot(to_target) >= sead::Mathf::cos(*mParams.mFrontAngle_s))
        return !sub_710072FD28(mActor, to_target, nullptr, -1, dist, reach, -1.0f, -1.0f);
    return false;
}

// NON_MATCHING: the original loads the actor pointer before the first test and computes the position differences
// in another order (loads / register numbering only).
void LynelAttackThroughMove::sub_710048C958(sead::Vector3f* out) {
    const sead::Vector3f& target = *mParams.mTargetPos_d;
    sead::Vector3f dir;
    if (*mParams.mSideOffsetDirType_s != 0 &&
        sead::Vector2f(mActor->getMtx().m[0][3] - target.x, mActor->getMtx().m[2][3] - target.z)
                .length() > *mParams.mSideOffset_s) {
        dir = target - mActor->getMtx().getTranslation();
    } else {
        mActor->getMtx().getBase(dir, 2);
    }
    dir.normalize();
    const sead::Vector3f end = dir * *mParams.mThroughDist_s + target;
    sead::Vector3f reachable;
    *out = sub_710072E154(mActor, end, &reachable, -1) ? end : reachable;
}

bool LynelAttackThroughMove::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

void LynelAttackThroughMove::leave_() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F7D350();
}

void LynelAttackThroughMove::loadParams_() {
    getStaticParam(&mParams.mSideOffsetDirType_s, "SideOffsetDirType");
    getStaticParam(&mParams.mCliffFailTime_s, "CliffFailTime");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mSideOffset_s, "SideOffset");
    getStaticParam(&mParams.mThroughDist_s, "ThroughDist");
    getStaticParam(&mParams.mAcceptableRadius_s, "AcceptableRadius");
    getStaticParam(&mParams.mFrontAngle_s, "FrontAngle");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

bool LynelAttackThroughMove::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("通り過ぎ"))
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai
