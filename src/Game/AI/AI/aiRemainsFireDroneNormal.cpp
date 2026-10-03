#include "Game/AI/AI/aiRemainsFireDroneNormal.h"
#include "Game/AI/aiXlinkHandle.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"

namespace uking::ai {


RemainsFireDroneNormal::RemainsFireDroneNormal(const InitArg& arg) : RailMove(arg) {}

RemainsFireDroneNormal::~RemainsFireDroneNormal() {
    if (_320) {
        delete _320;
        _320 = nullptr;
    }
}

bool RemainsFireDroneNormal::init_(sead::Heap* heap) {
    return RailMove::init_(heap);
}

void RemainsFireDroneNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMove::enter_(params);
}

void RemainsFireDroneNormal::leave_() {
    RailMove::leave_();
    mActor->sub_71011DA834(_320);
    uking::xlink::fade(_2f0, -1);
    uking::xlink::fade(_300, -1);
    uking::xlink::fade(_310, -1);
    sub_71007A2E04(mActor);
}

void RemainsFireDroneNormal::loadParams_() {
    RailMove::loadParams_();
    getStaticParam(&mLightLengthOffset_s, "LightLengthOffset");
    getStaticParam(&mAdjustRadius_s, "AdjustRadius");
    getMapUnitParam(&mSearchLightType_m, "SearchLightType");
    getMapUnitParam(&mLightRadius_m, "LightRadius");
    getMapUnitParam(&mLightLength_m, "LightLength");
    getAITreeVariable(&mTargetSpeed_a, "TargetSpeed");
}

void RemainsFireDroneNormal::m34() {}

// NON_MATCHING: the original reads the two distance limits (0.5, 0.1) from a data block at 0x7102419350
// (not constant-folded: the subtraction is done at run time) and computes the interpolation
// before the distance; the block is a global of the TU whose definition is unknown
f32 RemainsFireDroneNormal::m35() {
    if (!m36()) {
        *mTargetSpeed_a = 0.0f;
        return 0.0f;
    }

    const f32 progress = sub_710032C97C();
    const s32 prev = sead::Mathf::floor(progress);
    s32 next = sead::Mathf::ceil(progress);
    if (m36()->getNumPoints() <= next)
        next = 0;

    const f32 prev_speed = sub_7100EEF60C(m36(), prev);
    const f32 next_speed = sub_7100EEF60C(m36(), next);

    auto* actor = mActor;
    sead::Vector3f rail_pos;
    sub_710032C5BC(&rail_pos);
    const f32 dx = actor->getMtx().m[0][3] - rail_pos.x;
    const f32 dz = actor->getMtx().m[2][3] - rail_pos.z;
    const f32 dist = std::sqrt(dx * dx + dz * dz);

    const f32 speed = sead::lerp(prev_speed, next_speed, progress - prev);
    const f32 t = sead::Mathf::clamp(
        (0.5f - dist) / (0.5f - 0.1f), 0.0f, 1.0f);
    *mTargetSpeed_a = speed;
    return std::max(speed * t, 0.001f);
}

// NON_MATCHING: the original loads mActor before constructing the InlineParamPack (a local `auto* actor = mActor;`
// at the top matches)
void RemainsFireDroneNormal::stopAtHomeMaybe() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f home;
    mActor->getHomePos(&home);
    params.addVec3(home, "DynStopPos", -1);
    params.addFloat(120.0f, "DynStopTime", -1);
    changeChild("停止", &params);
}

// NON_MATCHING: regalloc only (the original keeps `this` in x20 and &_d0 in x19 across the lock and the
// link search; ours derives &_d0 at the end)
void RemainsFireDroneNormal::broadcastToLinkedActorMaybe() {
    _d0._18.y(mActor);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, mActor, "RegistedActorMessageBroadCastTag");
    if (accessor.hasProc())
        _d0.sub_710070DD78(accessor, true);
}

bool RemainsFireDroneNormal::handleMessage_(const ksys::Message* message) {
    if (isCurrentChild("警報")) {
        if (_1d0.m2(*message))
            return true;
    } else if (_158.m2(*message)) {
        return true;
    }
    return false;
}

bool RemainsFireDroneNormal::handleAck_(const ksys::MessageAck* ack) {
    if (!_d0.sub_710070E070(*ack))
        return false;
    if (_d0._14)
        _208 = true;
    return true;
}

}  // namespace uking::ai
