#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOffBase.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SwimEnemyAnmBackBlownOffBase::SwimEnemyAnmBackBlownOffBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SwimEnemyAnmBackBlownOffBase::~SwimEnemyAnmBackBlownOffBase() = default;

bool SwimEnemyAnmBackBlownOffBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the owned queries are naturally inlined into the completion predicate.
bool SwimEnemyAnmBackBlownOffBase::isFinished() const {
    if (_68)
        return false;
    return sub_7100289410() || sub_7100289460();
}

// NON_MATCHING: the established Actor depth API remains an out-of-line call.
bool SwimEnemyAnmBackBlownOffBase::sub_7100289410() const {
    auto* actor = mActor;
    return actor->getDepthInWater() >= *mInWaterDepth_s + *mFloatDepth_s &&
           actor->getVelocity().y < 0.0f;
}

// NON_MATCHING: the controller predicate naturally becomes a tail call.
bool SwimEnemyAnmBackBlownOffBase::sub_7100289460() const {
    if (auto* controller = mActor->getCharacterController())
        return controller->sub_7100F5F14C();
    return false;
}

void SwimEnemyAnmBackBlownOffBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwimEnemyAnmBackBlownOffBase::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62CA8(true);
}

void SwimEnemyAnmBackBlownOffBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mBlownHeight_s, "BlownHeight");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mUseKnockbackDir_s, "UseKnockbackDir");
    getStaticParam(&mAS_s, "AS");
}

void SwimEnemyAnmBackBlownOffBase::calc_() {
    if (_68) {
        _68 = false;
        return;
    }
    m33();
}

void SwimEnemyAnmBackBlownOffBase::m32(sead::Vector3f* out) {
    if (auto* manager = sub_710072BA90(mActor)) {
        if (*mUseKnockbackDir_s)
            manager->m30(out);
        else
            manager->m29(out);
    } else {
        out->set(sead::Vector3f::ez);
    }
}

void SwimEnemyAnmBackBlownOffBase::m33() {
    if (auto* controller = mActor->getCharacterController()) {
        sub_7100737C0C(controller, *mPosReduceRatio_s, -sead::Vector3f::ey);
        sub_7100738660(controller, *mRotReduceRatio_s);
    }
}

}  // namespace uking::action
