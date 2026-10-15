#include "Game/Actor/AI/aiNavMoveTargetWithJumpWater.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Utils/MathUtil.h"
#include <limits>

namespace uking::ai {

NavMoveTargetWithJumpWater::NavMoveTargetWithJumpWater(const InitArg& arg) : NavMoveTarget(arg) {}

NavMoveTargetWithJumpWater::~NavMoveTargetWithJumpWater() = default;

bool NavMoveTargetWithJumpWater::init_(sead::Heap* heap) {
    return NavMoveTarget::init_(heap);
}

void NavMoveTargetWithJumpWater::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMoveTarget::enter_(params);
}

void NavMoveTargetWithJumpWater::leave_() {
    NavMoveTarget::leave_();
}

bool NavMoveTargetWithJumpWater::m36() {
    auto* actor = mActor;
    if (!actor)
        return false;
    f32 depth = 0.0f;
    if (actor->get68f()) {
        const f32 y = actor->getMtx().getTranslation().y;
        depth = actor->get6f0() - y;
    }
    if (depth >= *mInWaterDepth_s)
        return sub_710072F8E4(actor, *m34(), nullptr, 3.0f);
    return NavMoveTarget::m36();
}

void NavMoveTargetWithJumpWater::loadParams_() {
    NavMoveTarget::loadParams_();
    getStaticParam(&mJumpDist_s, "JumpDist");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mWaterCheckDist_s, "WaterCheckDist");
    getStaticParam(&mIsCheckDamage_s, "IsCheckDamage");
}

// 0x71004ba408
// NON_MATCHING: initial position components use float registers and merged stores.
void NavMoveTargetWithJumpWater::sub_71004BA408(sead::Vector3f* out, f32 distance) {
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    *out = position;
    sead::Vector3f direction;
    auto* nav = isCurrentChild("直進") ? nullptr : mActor->m45();
    if (nav) {
        sead::ScopedLock<sead::CriticalSection> lock(&nav->_1e0);
        direction = nav->_23c;
    } else {
        direction = *m34() - position;
    }
    const sead::Vector3f up = getUpDir(getGravity(mActor));
    ksys::util::sub_71011EFA00(&direction, direction, up);
    direction.normalize();
    *out = direction * distance + *out;
}

// 0x71004ba6e4
bool NavMoveTargetWithJumpWater::sub_71004BA6E4(f32* depth_out, const sead::Vector3f& position) {
    if (mActor->sub_71011DB30C()) {
        f32 water_height;
        f32 ground_height;
        const u32 water_result = sub_710072C494(&water_height, &position);
        const u32 ground_result = sub_710072C21C(&ground_height, &position);
        if (water_result == 2 && ground_result == 2) {
            *depth_out = water_height - ground_height;
            return true;
        }
        *depth_out = 0.0f;
        return false;
    }
    const f32 depth = *mInWaterDepth_s;
    f32 water_height;
    sub_710072C494(&water_height, &position);
    sead::Vector3f from = position;
    from.y = water_height;
    sead::Vector3f to = from;
    to.y -= depth;
    sead::Vector3f hit;
    if (sub_710072EA18(from, to, 0, &hit, nullptr, nullptr, 0.0f))
        *depth_out = from.y - hit.y;
    else
        *depth_out = std::numeric_limits<f32>::infinity();
    return !(sead::Mathf::abs(*depth_out) > std::numeric_limits<f32>::max());
}

// 0x71004ba1f8
// NON_MATCHING: query setup and result branches share one natural lifetime.
bool NavMoveTargetWithJumpWater::sub_71004BA1F8(const sead::Vector3f& position) {
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    const u32 mode = nav->_2a4.load() & 0xffff;
    bool leaving_water = false;
    f32 query_height = 1.0f;
    if (mode == 6) {
        auto* actor = mActor;
        const f32 depth = actor->get68f() ?
            actor->get6f0() - actor->getMtx().getTranslation().y : 0.0f;
        leaving_water = depth >= *mInWaterDepth_s;
    } else if (mode == 7 && *mIsCheckDamage_s) {
        auto* actor = mActor;
        const f32 depth = actor->get68f() ?
            actor->get6f0() - actor->getMtx().getTranslation().y : 0.0f;
        if (depth >= *mInWaterDepth_s) {
            if (!actor)
                return false;
            leaving_water = true;
            query_height = actor->get6f0() + 0.5f;
        }
    }
    f32 depth;
    f32 border;
    {
        const auto result = ksys::phys::HavokAI::instance()->sub_7100F87ED0(
            nullptr, position, query_height);
        if (!result.sub_7100F7EB40())
            return false;
        const s32 target_mode = result.sub_7100F7EEE4();
        if (leaving_water) {
            if (target_mode != s32(mode))
                return true;
            if (!sub_71004BA6E4(&depth, position))
                return false;
        } else {
            if (target_mode != 6)
                return false;
            if (!sub_71004BA6E4(&depth, position))
                return true;
        }
        border = *mInWaterDepth_s;
    }
    return leaving_water ? !(depth >= border) : depth >= border;
}

// NON_MATCHING: the parameter pack and vector/string temporaries use different stack slots.
void NavMoveTargetWithJumpWater::calc_() {
    NavMoveTarget::calc_();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;
    if (!isCurrentChild("移動") && !isCurrentChild("直進"))
        return;
    const f32 check_dist = *mWaterCheckDist_s;
    sead::Vector3f check_position;
    sub_71004BA408(&check_position, check_dist < 0.0f ? *mJumpDist_s : check_dist);
    if (!sub_71004BA1F8(check_position))
        return;
    sead::Vector3f jump_position;
    sub_71004BA408(&jump_position, *mJumpDist_s);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(jump_position, "TargetPos", -1);
    changeChild("ジャンプ", &pack);
}

}  // namespace uking::ai
