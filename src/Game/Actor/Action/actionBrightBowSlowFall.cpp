#include "Game/Actor/Action/actionBrightBowSlowFall.h"
#include <cmath>
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

BrightBowSlowFall::BrightBowSlowFall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BrightBowSlowFall::~BrightBowSlowFall() = default;

bool BrightBowSlowFall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BrightBowSlowFall::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* body = actor->getMainBody();
    if (!body)
        return;
    sead::Matrix34f matrix = sead::Matrix34f::ident;
    ksys::util::sub_71011EFCA8(&matrix, *mInitRotate_s);
    matrix.setTranslation(actor->getMtx().getTranslation());
    actor->mMtx = matrix;
    actor->nullsub_4648();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EF51C(&axis, &angle, mActor->getMainBody()->getTransform(), matrix,
                             sead::Vector3f::ey);
    if (angle > 0.1f)
        body->setTransform(matrix);
    _c8 = false;
    _c9 = false;
    _cc = 0.0f;
    _d0 = 0.0f;
    _bc = actor->getMtx().getTranslation();
}

void BrightBowSlowFall::leave_() {
    _90.fadeXLink();
}

void BrightBowSlowFall::loadParams_() {
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mFloatWaveCycle_s, "FloatWaveCycle");
    getStaticParam(&mFloatWaveWidth_s, "FloatWaveWidth");
    getStaticParam(&mFloatHeight_s, "FloatHeight");
    getStaticParam(&mFloatSpring_s, "FloatSpring");
    getStaticParam(&mFloatDamper_s, "FloatDamper");
    getStaticParam(&mFallBrakeHeight_s, "FallBrakeHeight");
    getStaticParam(&mFallBrake_s, "FallBrake");
    getStaticParam(&mAttractionRange_s, "AttractionRange");
    getStaticParam(&mAttractionRate_s, "AttractionRate");
    getStaticParam(&mTailEffectKeyName_s, "TailEffectKeyName");
    getStaticParam(&mInitRotate_s, "InitRotate");
    getStaticParam(&mRotateSpeed_s, "RotateSpeed");
}

// NON_MATCHING: operand order of the spring / damper impulse products and the clamp registers.
void BrightBowSlowFall::calc_() {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* body = actor->getMainBody();
    if (!body)
        return;

    flyingObjectEmitXlink(actor, mTailEffectKeyName_s.cstr(), 2, &_90);
    if (_c8) {
        if (_c9) {
            _cc = *mAttractionRate_s + _cc;
            if (_cc < 0.0f)
                _cc = 0.0f;
            else if (_cc > 1.0f)
                _cc = 1.0f;
            const sead::Vector3f& player_pos = getPlayerPosition();
            const sead::Vector3f target_pos = sead::Vector3f::ey * 0.5f + player_pos;
            const sead::Vector3f target =
                target_pos + sub_710072BB4C()->getVelocity() * 2.0f;
            const f32 t = _cc * _cc;
            body->changePosition(_b0 + (target - _b0) * t, ksys::phys::KeepAngularVelocity(false));
        } else {
            const sead::Vector3f& player_pos = getPlayerPosition();
            const sead::Vector2f to_player(player_pos.x - mActor->getMtx()(0, 3),
                                           player_pos.z - mActor->getMtx()(2, 3));
            const sead::Vector3f float_pos =
                _b0 + sead::Vector3f(0, *mFloatWaveWidth_s * std::sin(_d0), 0);
            body->setGravityFactor(0.0f);
            const f32 player_distance = to_player.length();
            body->applyLinearImpulse((float_pos - actor->getMtx().getTranslation()) *
                                     *mFloatSpring_s);
            body->applyLinearImpulse((_bc - actor->getMtx().getTranslation()) * *mFloatDamper_s);
            _d0 += *mFloatWaveCycle_s;
            if (player_distance < *mAttractionRange_s) {
                _cc = 0;
                _c9 = true;
                _b0 = actor->getMtx().getTranslation();
                _d0 = 0;
            }
        }
    } else {
        body->setGravityFactor(*mGravity_s);
        sead::Vector3f hit_pos;
        if (somePositionCalc(&hit_pos, actor->getMtx().getTranslation(), -sead::Vector3f::ey,
                             *mFloatHeight_s)) {
            _c8 = true;
            _b0 = hit_pos + sead::Vector3f(0, *mFloatHeight_s, 0);
        } else if (somePositionCalc(&hit_pos, actor->getMtx().getTranslation(), -sead::Vector3f::ey,
                                    *mFallBrakeHeight_s)) {
            body->applyLinearImpulse(actor->getVelocity() * -*mFallBrake_s);
        }
    }
    _bc = actor->getMtx().getTranslation();
    body->setAngularVelocity(*mRotateSpeed_s);
}

}  // namespace uking::action
