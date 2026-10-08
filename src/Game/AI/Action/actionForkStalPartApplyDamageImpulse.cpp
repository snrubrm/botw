#include "Game/AI/Action/actionForkStalPartApplyDamageImpulse.h"

#include <cmath>

#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ForkStalPartApplyDamageImpulse::ForkStalPartApplyDamageImpulse(const InitArg& arg) : Fork(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkStalPartApplyDamageImpulse::~ForkStalPartApplyDamageImpulse() {
    ;
}

bool ForkStalPartApplyDamageImpulse::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkStalPartApplyDamageImpulse::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    _a8 = false;
    _ac.set(0.0f, 0.0f, 0.0f);
    sub_710073FA90(&_c4, mActor);
}

void ForkStalPartApplyDamageImpulse::leave_() {
    Fork::leave_();
}

void ForkStalPartApplyDamageImpulse::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mMaxAddSpeed_s, "MaxAddSpeed");
    getStaticParam(&mSwordRate_s, "SwordRate");
    getStaticParam(&mSpearRate_s, "SpearRate");
    getStaticParam(&mLswordRate_s, "LswordRate");
    getStaticParam(&mArrowRate_s, "ArrowRate");
    getStaticParam(&mBombRate_s, "BombRate");
    getStaticParam(&mGustRate_s, "GustRate");
    getStaticParam(&mLargeAttackAddRate_s, "LargeAttackAddRate");
    getStaticParam(&mMaxAddSpeedY_s, "MaxAddSpeedY");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mRotAccMaxSpeedRatio_s, "RotAccMaxSpeedRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsViewHitDir_s, "IsViewHitDir");
}

// NON_MATCHING: the original loads the matrix translation components before the _ac
// components in the two direction subtractions below (the s8/s9 assignment cascades from that
// order); this version is otherwise instruction-identical.
void ForkStalPartApplyDamageImpulse::calc_() {
    Fork::calc_();
    sub_7100165930();
    if (!_a8)
        return;
    sub_710073FA94(&_c4, mActor);
    _b8.lerp(*mRotSpd_s, *mRotAccRatio_s, (*mRotSpd_s) * (*mRotAccMaxSpeedRatio_s));
    _b8.updateStats();
    sead::Vector3f dir;
    dir.x = _ac.x - mActor->getMtx().m[0][3];
    dir.y = 0.0f;
    dir.z = _ac.z - mActor->getMtx().m[2][3];
    dir.normalize();
    sub_710074006C(&_c4, dir, sead::Vector3f::ey, false, *mBaseRotRatio_s, _b8.value,
                   _b8.value / 10.0f);
    sub_7100740F1C(_c4, mActor);
}

void ForkStalPartApplyDamageImpulse::sub_7100165930() {
    // NON_MATCHING: register allocation and load/store scheduling only — the original keeps more
    // values in callee-saved regs (x22, d11, vel.y via mov v8,v1, atk-mtx elements in w20-w22),
    // interleaves the forward loads/stores/squares differently, and stores _b8.value/prev_value
    // as two str instead of our merged stp. Calls, switch table, constants and branches identical.
    auto* dmg = sub_710072BA90(mActor);
    if (!dmg)
        return;
    if (!dmg->_216.isOn(2))
        return;
    sead::Vector3f dir1;
    if (!dmg->m30(&dir1))
        return;
    sead::Vector3f dir2;
    if (!dmg->m32(&dir2))
        return;
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    f32 rate;
    switch (dmg->getField50()) {
    case 0:
        rate = *mSwordRate_s;
        break;
    case 1:
        rate = *mLswordRate_s;
        break;
    case 2:
        rate = *mSpearRate_s;
        break;
    case 3:
    case 6:
        rate = *mArrowRate_s;
        break;
    case 4:
        rate = *mBombRate_s;
        break;
    default:
        rate = 0.1f;
        break;
    }
    const f32 v = dmg->sub_71006D8DE8();
    if (dmg->getField54() == 0x14)
        rate = *mGustRate_s;
    else
        rate *= v;
    if (sub_7100736B68(dmg->getField54()))
        rate += *mLargeAttackAddRate_s;
    const sead::Vector3f vel = body->getLinearVelocity();
    const f32 imp = body->getMass() * rate * *mMaxAddSpeed_s * 30.0f;
    body->applyLinearImpulse(dir1 * imp);
    if (*mMaxAddSpeedY_s > 0.0f) {
        f32 y = rate * *mMaxAddSpeedY_s * 30.0f;
        if (vel.y > 0.0f) {
            const f32 t = y * 0.05f;
            const f32 d = y - vel.y;
            y = t > d ? t : d;
        }
        const f32 s = y * body->getMass();
        body->applyLinearImpulse(sead::Vector3f::ey * s);
    }
    if (_a8 || !*mIsViewHitDir_s)
        return;
    _ac.x = mActor->getMtx().m[0][3] - dir1.x;
    _ac.y = mActor->getMtx().m[1][3] - dir1.y;
    _ac.z = mActor->getMtx().m[2][3] - dir1.z;
    sead::Matrix34f atk_mtx;
    if (!dmg->m35(&atk_mtx))
        return;
    const f32 dx = atk_mtx.m[0][3] - mActor->getMtx().m[0][3];
    const f32 dz = atk_mtx.m[2][3] - mActor->getMtx().m[2][3];
    if (std::sqrt(dx * dx + dz * dz) > 0.0f) {
        _ac.x = atk_mtx.m[0][3];
        _ac.y = atk_mtx.m[1][3];
        _ac.z = atk_mtx.m[2][3];
    }
    const auto& angvel = mActor->getAngVelocity();
    const f32 len =
        std::sqrt(angvel.x * angvel.x + angvel.y * angvel.y + angvel.z * angvel.z);
    _b8.value = len;
    _b8.prev_value = len;
    _a8 = true;
}

}  // namespace uking::action
