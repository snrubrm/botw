#include "Game/AI/Action/actionSiteBossBowChildDeviceBreak.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossBowChildDeviceBreak::SiteBossBowChildDeviceBreak(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossBowChildDeviceBreak::~SiteBossBowChildDeviceBreak() = default;

bool SiteBossBowChildDeviceBreak::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: float register allocation of the normalized offset / sum (the original stores the x component of the
// position first and the y / z pair afterwards).
void SiteBossBowChildDeviceBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = ksys::Timer(*mReactionTime_s, *mReactionTime_s, -1.0f);
    sead::Vector3f offset{0.0f, 2.0f, 0.0f};
    if (auto* manager = sub_710072BA90(mActor)) {
        manager->getAttackPos(&offset);
        offset.normalize();
        offset.y *= 1.1f;
    }
    const sead::Vector3f pos = mActor->getMtx().getTranslation() + offset;
    if (auto* body = mActor->getMainBody()) {
        body->changePosition(pos, ksys::phys::KeepAngularVelocity{false});
        body->setAngularVelocity({0.0f, 2.5f, 2.5f});
        body->setGravityFactor(1.0f);
    }
}

void SiteBossBowChildDeviceBreak::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossBowChildDeviceBreak::loadParams_() {
    getStaticParam(&mReactionTime_s, "ReactionTime");
    getStaticParam(&mIsDelete_s, "IsDelete");
}

void SiteBossBowChildDeviceBreak::calc_() {
    _30.update();
    if (_30.value <= sead::Mathf::epsilon()) {
        if (auto* body = mActor->getMainBody())
            body->removeFromWorld();
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        setFinished();
    } else if (_30.value <= 5.0f) {
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D909A4();
    }
}

}  // namespace uking::action
