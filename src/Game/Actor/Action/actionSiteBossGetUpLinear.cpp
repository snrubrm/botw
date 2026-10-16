#include "Game/Actor/Action/actionSiteBossGetUpLinear.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physShapeCastWithInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"

namespace uking::action {

SiteBossGetUpLinear::SiteBossGetUpLinear(const InitArg& arg) : GetUpLinear(arg) {}

SiteBossGetUpLinear::~SiteBossGetUpLinear() = default;

bool SiteBossGetUpLinear::init_(sead::Heap* heap) {
    return GetUpLinear::init_(heap);
}

void SiteBossGetUpLinear::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUpLinear::enter_(params);
    if (*mIsRestoreRigidBody_s) {
        ksys::phys::SphereCast cast{ksys::phys::ContactLayer::EntityHitOnlyGround,
                                    ksys::phys::GroundHit::HitAll,
                                    nullptr,
                                    0x80,
                                    ksys::phys::ShapeCast::Mode::_0,
                                    sead::Vector3f::zero,
                                    0.5f,
                                    sead::SafeString::cEmptyString,
                                    ksys::phys::LowPriority::No};
        auto* info = cast.getContactPointInfo();
        info->subscribeLayer(ksys::phys::ContactLayer::EntityObject);
        info->subscribeLayer(ksys::phys::ContactLayer::EntityGround);
        info->subscribeLayer(ksys::phys::ContactLayer::EntityGroundObject);
        info->subscribeLayer(ksys::phys::ContactLayer::EntityAirWall);
        if (auto* body = mActor->findPhysicsBodyByName("Ragdoll", "Base")) {
            const sead::Matrix34f mtx = body->getTransform();
            sead::Vector3f pos = mtx.getTranslation();
            sead::Vector3f start = pos;
            start.y += 2.5f;
            cast.setStartAndDisplacementScaled(start, -sead::Vector3f::ey, 5.5f);
            // called through a pointer in the original (not devirtualised)
            if ((&cast)->executeQuery(ksys::phys::ShapeCast::WeldClosestPoints::Yes)) {
                sead::Vector3f hit;
                info->begin().getPointPosition(&hit,
                                               ksys::phys::ContactPointInfo::Iterator::Point::BodyB);
                // The original reads the first contact point in every iteration.
                for (auto it = info->begin(); it != info->end(); ++it) {
                    info->begin().getPointPosition(
                        &hit, ksys::phys::ContactPointInfo::Iterator::Point::BodyB);
                    if (pos.y <= hit.y)
                        pos = hit;
                }
            }
            if (auto* controller = mActor->getCharacterController()) {
                sead::Matrix34f controller_mtx;
                controller->physicsXXXGetMtx_1(&controller_mtx);
                controller_mtx.setTranslation(pos);
                controller->sub_7100F60500(controller_mtx);
            }
        }
    }
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1558.set(0x8000000);
}

void SiteBossGetUpLinear::leave_() {
    GetUpLinear::leave_();
    if (auto* body = mActor->getMainBody())
        body->setContactNone();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F60604();
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
        if (*mIsRestoreRigidBody_s) {
            if (auto* cc = mActor->getCharacterController()) {
                if (auto* physics = mActor->getPhysics()) {
                    auto* handler = physics->get188(0);
                    if (auto* body = cc->sub_7100F61A34())
                        body->setContactLayerAndHandler(
                            ksys::phys::ContactLayer::EntityHitOnlyGround, handler);
                }
            }
        }
    }
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_1558.reset(0x8000000);
        boss->sub_71002D28BC();
    }
    playAS("Wait_Battle", true, 2, 0, -1.0f);
}

void SiteBossGetUpLinear::loadParams_() {
    GetUpLinear::loadParams_();
    getStaticParam(&mIsRestoreRigidBody_s, "IsRestoreRigidBody");
    getStaticParam(&mForceRecoverOffset_s, "ForceRecoverOffset");
    getStaticParam(&mForceRecoverDist_s, "ForceRecoverDist");
}

void SiteBossGetUpLinear::calc_() {
    GetUpLinear::calc_();
}

}  // namespace uking::action
