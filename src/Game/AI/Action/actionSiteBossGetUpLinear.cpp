#include "Game/AI/Action/actionSiteBossGetUpLinear.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

SiteBossGetUpLinear::SiteBossGetUpLinear(const InitArg& arg) : GetUpLinear(arg) {}

SiteBossGetUpLinear::~SiteBossGetUpLinear() = default;

bool SiteBossGetUpLinear::init_(sead::Heap* heap) {
    return GetUpLinear::init_(heap);
}

void SiteBossGetUpLinear::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUpLinear::enter_(params);
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
