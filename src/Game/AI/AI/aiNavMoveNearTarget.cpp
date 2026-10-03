#include "Game/AI/AI/aiNavMoveNearTarget.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

NavMoveNearTarget::NavMoveNearTarget(const InitArg& arg) : NavMoveTarget(arg) {}

NavMoveNearTarget::~NavMoveNearTarget() = default;

bool NavMoveNearTarget::init_(sead::Heap* heap) {
    return NavMoveTarget::init_(heap);
}

void NavMoveNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _390 = *mTargetPos_d;
    m35(nullptr);
    NavMoveTarget::enter_(params);
}

// NON_MATCHING: the original copies the vector into *out as one 8 + 4 byte block (ldr x / ldr w) while
// `_390 = pos` stays member-wise; ours assigns *out member-wise too (sead::Vector3f::operator=)
void NavMoveNearTarget::m35(sead::Vector3f* out) {
    f32 radius = 0;
    if (!m38(&radius))
        return;

    sead::Vector3f pos;
    bool found;
    {
        ksys::phys::Unk_7100f7e9f0 result =
            ksys::phys::HavokAI::instance()->sub_7100F87ED0(&pos, *mTargetPos_d, radius);
        found = result.sub_7100F7EB40();
    }

    const f32 dy = mTargetPos_d->y - pos.y;
    if (*mTargetVMin_s <= dy && dy < *mTargetVMax_s && found) {
        _390 = pos;
        if (out)
            *out = pos;
    } else if (out) {
        *out = _390;
    }
}

void NavMoveNearTarget::leave_() {
    NavMoveTarget::leave_();
}

void NavMoveNearTarget::loadParams_() {
    NavMoveTarget::loadParams_();
    getStaticParam(&mTargetVMax_s, "TargetVMax");
    getStaticParam(&mTargetVMin_s, "TargetVMin");
}

bool NavMoveNearTarget::m38(f32* out) {
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    *out = sead::Mathf::max(sub_71007320F0(mActor, *mWeaponIdx_s), nav->getRadiusMaybe()) +
           *mReachTargetArea_s;
    return true;
}

}  // namespace uking::ai
