#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOffBase.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

SwimEnemyAnmBackBlownOffBase::SwimEnemyAnmBackBlownOffBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SwimEnemyAnmBackBlownOffBase::~SwimEnemyAnmBackBlownOffBase() = default;

bool SwimEnemyAnmBackBlownOffBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SwimEnemyAnmBackBlownOffBase::sub_7100289410() const {
    auto* actor = mActor;
    f32 depth = 0.0f;
    if (actor->get68f().load()) {
        const f32 y = actor->getMtx().m[1][3];
        depth = actor->get6f0() - y;
    }
    return depth >= *mInWaterDepth_s + *mFloatDepth_s && actor->getVelocity().y < 0.0f;
}

// NON_MATCHING: the controller predicate naturally becomes a tail call.
bool SwimEnemyAnmBackBlownOffBase::sub_7100289460() const {
    auto* controller = mActor->getCharacterController();
    if (controller && controller->sub_7100F5F14C())
        return true;
    return false;
}

void SwimEnemyAnmBackBlownOffBase::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mAS_s.cstr(), false, 0, 0, -1.0f);
    sead::Vector3f dir;
    m32(&dir);
    f32 scale = 1.0f;
    if (auto* manager = sub_710072BA90(mActor))
        scale = manager->sub_71006D8DE8();
    if (auto* controller = mActor->getCharacterController()) {
        if (controller->sub_7100F5F0E4() == ksys::act::MotionType::_0) {
            controller->sub_7100F5EF08(true);
            controller->sub_7100F62B70(*mBlownHeight_s);
            sub_710072C1B4(controller, dir);
            sub_7100737708(controller, scale * *mSpeed_s);
        } else {
            controller->sub_7100F5F458(ksys::act::MotionType::_1);
            const f32 height = *mBlownHeight_s;
            sead::Vector3f velocity = getGravity(mActor);
            velocity *= 1.0f / 900;
            const f32 up_speed = sub_710072D068(&velocity, height);
            const sead::Vector3f up = controller->get7c();
            velocity = dir * *mSpeed_s * scale - up * up_speed;
            sub_7100737710(controller, velocity);
        }
        controller->sub_7100F62CA8(false);
    }
    _68 = true;
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
