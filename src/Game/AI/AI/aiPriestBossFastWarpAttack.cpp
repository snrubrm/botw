#include "Game/AI/AI/aiPriestBossFastWarpAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710071E0D8.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

PriestBossFastWarpAttack::PriestBossFastWarpAttack(const InitArg& arg)
    : SiteBossSwordApproachRoot(arg) {}

PriestBossFastWarpAttack::~PriestBossFastWarpAttack() = default;

bool PriestBossFastWarpAttack::init_(sead::Heap* heap) {
    return SiteBossSwordApproachRoot::init_(heap);
}

void PriestBossFastWarpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _f0 = false;
    ksys::act::ActorConstDataAccess accessor;
    if (sub_71005D9050(mActor)) {
        if (ksys::act::acquireActor(sub_71005D9050(mActor), &accessor) && !accessor.isBgGroundHit())
            sub_710071E0D8(*mIsCloseMove_s, mActor);
    }
    SiteBossSwordApproachRoot::enter_(params);
}

void PriestBossFastWarpAttack::calc_() {
    SiteBossSwordApproachRoot::calc_();
}

void PriestBossFastWarpAttack::leave_() {
    SiteBossSwordApproachRoot::leave_();
    if (isFinished())
        return;
    sub_710071E0D8(false, mActor);
}

void PriestBossFastWarpAttack::loadParams_() {
    SiteBossSwordApproachRoot::loadParams_();
}

bool PriestBossFastWarpAttack::m35() {
    const bool ret = SiteBossSwordApproachRoot::m35();
    if (*mIsCloseMove_s)
        _a8.y += -0.5f;

    const auto& pos = sub_71005D9330(mActor);
    const f32 x = pos.x;
    const f32 y = pos.y;
    const f32 z = pos.z;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.setStartAndDisplacementScaled({x + 0.0f, y + 1.0f, z + 0.0f}, sead::Vector3f::ey, -75.0f);
    sead::Vector3f hit_pos{x, y, z};
    f32 ground_y = y;
    bool snap = false;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(&hit_pos);
        ground_y = hit_pos.y;
        snap = sead::Mathf::abs(y - ground_y) <= 1.0f;
    }
    if (snap) {
        _90.y = ground_y;
        _9c.y = ground_y;
        _a8.y = ground_y;
        _b4.y = ground_y;
    } else if (!*mIsCloseMove_s) {
        _90.y += (ground_y - _90.y) * 0.0f;
        _9c.y += (ground_y - _9c.y) * 1.0f;
        _a8.y += (ground_y - _a8.y) * 2.0f;
        _b4.y += (ground_y - _b4.y) * 3.0f;
    }

    if (!_f0) {
        _f0 = true;
        _c0.set(_90);
        _cc.set(_9c);
        _d8.set(_a8);
        _e4.set(_b4);
    }
    return ret;
}

void PriestBossFastWarpAttack::m36() {
    sub_71007A3540(mActor);
    m35();
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_90, "TargetPos", -1);
    changeChild("移動開始", &params);
}

void PriestBossFastWarpAttack::m38() {
    sub_71007A3540(mActor);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addVec3(_c0, "AfterImage0Pos", -1);
    params.addVec3(_cc, "AfterImage1Pos", -1);
    params.addVec3(_d8, "MoveDstPos", -1);
    params.addFloat(_78.value, "CurrentFrame", -1);
    changeChild("スロー時移動", &params);
}

bool PriestBossFastWarpAttack::m39() {
    return true;
}

}  // namespace uking::ai
