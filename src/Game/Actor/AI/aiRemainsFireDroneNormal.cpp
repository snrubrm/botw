#include "Game/Actor/AI/aiRemainsFireDroneNormal.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "Game/Actor/aiUnk_71024f15c0.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyPolytope.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::ai {

// 0x7100544394
bool Unk_71024192e0::m5(ksys::act::BaseProc* proc) {
    return mOwner->sub_7100543C18(static_cast<ksys::act::Actor*>(proc));
}



RemainsFireDroneNormal::RemainsFireDroneNormal(const InitArg& arg) : BezierRailMove(arg) {}

RemainsFireDroneNormal::~RemainsFireDroneNormal() {
    if (_320) {
        delete _320;
        _320 = nullptr;
    }
}

bool RemainsFireDroneNormal::init_(sead::Heap* heap) {
    if (!BezierRailMove::init_(heap))
        return false;
    auto* actor = mActor;
    mPropellerTop.search(actor->getModel(), "Propeller_Top");
    mPropellerBottom.search(actor->getModel(), "Propeller_Bottom");
    mSearchlight.search(actor->getModel(), "Searchlight");
    mBody.search(actor->getModel(), "Body");
    _320 = new (heap, 8) Unk_71024192e0(this);
    _209 = sub_7100EEF034(mActor, 0) != nullptr;
    if (auto* physics = mActor->getPhysics()) {
        if (auto* body = sead::DynamicCast<ksys::phys::PolytopeRigidBody>(
                physics->findX("Body", "Barrier"))) {
            body->setFlag1000000();
            body->setRestitutionScale(0.0f);
            body->setFrictionScale(0.0f);
            body->setColImpulseScale(0.0f);
            auto mask = body->getMaterialMask();
            mask.getData().flag30 = 1;
            body->setMaterialMask(mask);
        }
    }
    return true;
}

// NON_MATCHING: awareness request construction and copied sensor-field stores.
void RemainsFireDroneNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _20a = false;
    if (_209) {
        sub_710032BCAC(0.0f);
        sub_710032C088();
    } else {
        stopAtHomeMaybe();
    }
    if (auto* awareness = actor->getAwareness()) {
        awareness->sub_7100D7E9BC(0);
        Unk_71023e26d8 request;
        request.params.sight.angle = 0.0f;
        if (auto* sensor = awareness->_260[0])
            sensor->m5(&request);
        request.params.sight.radius = *mLightRadius_m;
        const f32 length = -*mLightLength_m;
        request.params.sight.height_max = length;
        request.params.sight.height_min = length;
        request.params.sight.height_near_min = length;
        awareness->sub_7100D7E6F4(&request, 0);
    }
    _334 = 0.0f;
    mActor->sub_71011DA824(_320);
    _208 = false;
    broadcastToLinkedActorMaybe();
    sub_71007A2C9C(mActor);
    auto* sensor = getActorAttackSensor(mActor);
    const auto* attack = mActor->getParam()->getRes().mGParamList->getAttack();
    sensor->activateAttackSensor(0x2000, 0x11, attack->mPower.ref(), attack->mImpulseLarge.ref(),
                                 0.0f, 0, 1, -1, false, 1, -1);
    actor->getASList()->startAnimationMaybe(-1.0f, -1.0f, "MaterialDefault", 0, 0, true);
    auto* physics = mActor->getPhysics();
    auto* handler = ksys::phys::System::instance()->sub_7101216894(ksys::phys::ContactLayerType::Entity, 2);
    if (physics)
        physics->sub_7100FBDFA4(handler);
}

void RemainsFireDroneNormal::leave_() {
    BezierRailMove::leave_();
    mActor->sub_71011DA834(_320);
    uking::xlink::fade(_2f0, -1);
    uking::xlink::fade(_300, -1);
    uking::xlink::fade(_310, -1);
    sub_71007A2E04(mActor);
}

void RemainsFireDroneNormal::loadParams_() {
    BezierRailMove::loadParams_();
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
    ksys::act::ActorLinkConstDataAccess accessor;
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
