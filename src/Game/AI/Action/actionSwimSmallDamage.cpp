#include "Game/AI/Action/actionSwimSmallDamage.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

void sub_71006F54EC(ksys::phys::CharacterController* controller);
void sub_71006F5538(ksys::phys::CharacterController* controller);
bool sub_71006F562C(ksys::phys::CharacterController* controller);
bool sub_71006F564C(ksys::phys::CharacterController* controller);
// Name and signature are inferred from the call sites (also used by SwimGetUp and others).
void sub_71005DF820(f32* out, f32 velY, f32 depth, f32 floatDepth, f32 inWaterDepth,
                    f32 floatRadius, f32 floatCycleTime, f32 changeDepthSpeed);

namespace uking::action {

SwimSmallDamage::SwimSmallDamage(const InitArg& arg) : SmallDamage(arg) {}

SwimSmallDamage::~SwimSmallDamage() = default;

void SwimSmallDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamage::enter_(params);
    _b8.sub_710072AD1C(mActor->getCharacterController());
}

void SwimSmallDamage::leave_() {
    _b8.resetMotionType(mActor->getCharacterController());
    sub_710028BE2C(false);
}

void SwimSmallDamage::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mASName_s, "ASName");
}

void SwimSmallDamage::sub_710028BE2C(bool invalidate_burn) {
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* unit = sead::DynamicCast<uking::act::Unk_710244dd20>(actor->m159())) {
            unit->_138 = invalidate_burn ? (unit->_138 | 1) : (unit->_138 & ~1);
        }
    }
}

void SwimSmallDamage::m35() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    if (depth + *mFloatRadius_s >= *mInWaterDepth_s + *mFloatDepth_s) {
        sub_71006F54EC(controller);
        f32 out = 0.0f;
        const f32 velY = mActor->getVelocity().y;
        f32 depth2 = 0.0f;
        if (mActor->get68f().load()) {
            const f32 y = mActor->getMtx().m[1][3];
            depth2 = mActor->get6f0() - y;
        }
        sub_71005DF820(&out, velY, depth2, *mFloatDepth_s, *mInWaterDepth_s, 0.1f, 30.0f, -1.0f);
        sead::Vector3f vel = _68.value;
        vel.y = out;
        if (sub_71006F564C(controller)) {
            sead::Vector3f dir = _68.value;
            const f32 len = dir.normalize();
            sub_710073770C(controller, len, dir);
        } else {
            sub_7100737710(controller, vel);
        }
        sub_710028BE2C(true);
    } else {
        if (sub_71006F562C(controller))
            sub_71006F5538(controller);
        TakeHitImpactForce::m35();
        sub_710028BE2C(false);
    }
}

void SwimSmallDamage::m38() {
    f32 depth = 0.0f;
    if (mActor->get68f()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    if (depth + *mFloatRadius_s >= *mInWaterDepth_s + *mFloatDepth_s)
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    else
        SmallDamage::m38();
}

}  // namespace uking::action
