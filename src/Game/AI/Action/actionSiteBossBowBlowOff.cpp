#include "Game/AI/Action/actionSiteBossBowBlowOff.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

SiteBossBowBlowOff::SiteBossBowBlowOff(const InitArg& arg) : SiteBossBlowOff(arg) {}

SiteBossBowBlowOff::~SiteBossBowBlowOff() = default;

bool SiteBossBowBlowOff::init_(sead::Heap* heap) {
    return SiteBossBlowOff::init_(heap);
}

void SiteBossBowBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossBlowOff::enter_(params);
    if (auto* body = mActor->getMainBody()) {
        body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
        body->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
        body->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        body->enableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
    }
    if (auto* cc = mActor->getCharacterController()) {
        if (auto* physics = mActor->getPhysics()) {
            auto* handler = physics->get188(0);
            if (auto* body = cc->sub_7100F61A34())
                body->setContactLayerAndHandler(ksys::phys::ContactLayer::EntityNoHit, handler);
        }
    }
    playAS("DownWaitMaterial", false, 2, 0, -1.0f);
}

void SiteBossBowBlowOff::leave_() {
    SiteBossBlowOff::leave_();
}

void SiteBossBowBlowOff::loadParams_() {
    SiteBossBlowOff::loadParams_();
    getStaticParam(&mAddForceRecoverTime_s, "AddForceRecoverTime");
    getStaticParam(&mIsRemoveCharacterController_s, "IsRemoveCharacterController");
    getStaticParam(&mForceRecoverDist_s, "ForceRecoverDist");
    getStaticParam(&mForceRecoverOffset_s, "ForceRecoverOffset");
}

void SiteBossBowBlowOff::calc_() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (boss && boss->_1558.isOnBit(7))
        return;
    if (m36()) {
        _160 = ksys::Timer(0.0f, 0.0f);
        if (_ec == 1)
            setFinished();
    }
    SiteBossBlowOff::calc_();
}

s32 SiteBossBowBlowOff::m37() {
    const s32 time = SiteBossBlowOff::m37();
    int level = getNumberOfDeadBlights();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        const s32 kind = boss->_1534 & ~3;
        if (kind == 4)
            level = 3;
        else if (kind == 8)
            level = 4;
    }
    return time + *mAddForceRecoverTime_s * level;
}

}  // namespace uking::action
