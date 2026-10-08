#include "Game/AI/Action/actionForkASTrgEmitShockWave.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkASTrgEmitShockWave::ForkASTrgEmitShockWave(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgEmitShockWave::~ForkASTrgEmitShockWave() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(mShockWavePartsKey_s);
    if (_98.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_98, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool ForkASTrgEmitShockWave::init_(sead::Heap* heap) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->sub_7100D3CED8(mShockWavePartsKey_s, heap);
        if (!enemy->getActorPartsActor(mShockWavePartsKey_s).hasProc()) {
            if (auto* proc = sub_710014F4BC())
                enemy->sub_7100D3D108(mShockWavePartsKey_s, proc);
            return true;
        } else {
            auto* link = &enemy->getActorPartsActor(mShockWavePartsKey_s);
            auto* actor =
                sead::DynamicCast<ksys::act::Actor>(link->getProc(nullptr, mActor));
            if (sub_710014F780(actor))
                return true;
        }
    }
    auto* proc = sub_710014F4BC();
    _98.acquire(proc, false);
    return true;
}

void ForkASTrgEmitShockWave::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _90 = false;
    _a8.reset(0.0f);
}

void ForkASTrgEmitShockWave::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgEmitShockWave::loadParams_() {
    getStaticParam(&mPower_s, "Power");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mEmitIntervalTime_s, "EmitIntervalTime");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mMaxScale_s, "MaxScale");
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
    getStaticParam(&mIsIniviciblePierce_s, "IsIniviciblePierce");
    getStaticParam(&mIsHeavy_s, "IsHeavy");
    getStaticParam(&mShockWaveActorName_s, "ShockWaveActorName");
    getStaticParam(&mShockWavePartsKey_s, "ShockWavePartsKey");
}

void ForkASTrgEmitShockWave::calc_() {
    if (*mEmitIntervalTime_s >= 0 && !(_a8.value <= std::numeric_limits<f32>::epsilon()))
        _a8.update();
    sead::Matrix34f mtx;
    if (m32() && m33(&mtx))
        sub_710014FA28(mtx);
}

bool ForkASTrgEmitShockWave::m32() {
    if (*mEmitIntervalTime_s < 0) {
        if (_90)
            return false;
    } else if (!(_a8.value <= sead::Mathf::epsilon())) {
        return false;
    }

    if (!sub_71005DD7B0(mActor, nullptr, 0, 0) && !sub_71005DD74C(mActor, nullptr, 0, 0))
        return false;

    ksys::act::BaseProcLink* link = &_98;
    if (!link->hasProc()) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            link = &enemy->getActorPartsActor(mShockWavePartsKey_s);
        else
            link = &ksys::act::sUnk_71026505e0;
    }
    if (link->hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (accessor.isStateSleep())
            return true;
    }
    return false;
}

void ForkASTrgEmitShockWave::sub_710014FA28(const sead::Matrix34f& mtx) {
    const f32 scale_value = *mMaxScale_s;
    sead::Vector3f scale{scale_value, scale_value, scale_value};
    ksys::act::BaseProcLink* link = &_98;
    if (!link->hasProc()) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            link = &enemy->getActorPartsActor(mShockWavePartsKey_s);
        else
            link = &ksys::act::sUnk_71026505e0;
    }
    if (!link->hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (accessor.isStateSleep()) {
        accessor.setProperties(mtx, nullptr, nullptr, &scale, false, 0, -1);
        _90 = true;
        _a8.reset(*mEmitIntervalTime_s);
    }
}

}  // namespace uking::action
