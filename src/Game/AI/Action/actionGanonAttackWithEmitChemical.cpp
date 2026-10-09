#include "Game/AI/Action/actionGanonAttackWithEmitChemical.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actEnemy.h"
#include <cstring>

namespace uking::action {

void GanonAttackWithEmitChemical::m32(sead::Vector3f* pos) {
    mActor->getMtx().getTranslation(*pos);
}

float GanonAttackWithEmitChemical::m33() {
    return *mEmitOffsetFromParent_s;
}

int GanonAttackWithEmitChemical::m34() {
    return 2;
}

GanonAttackWithEmitChemical::GanonAttackWithEmitChemical(const InitArg& arg)
    : GanonWeaponNearAttack(arg) {
    // 1727FC clears all 32 bytes of the paired effect handles, including their padding.
    std::memset(&mEffectHandle, 0, sizeof(mEffectHandle));
}

GanonAttackWithEmitChemical::~GanonAttackWithEmitChemical() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (mEmitNum_s) {
            for (s32 i = 0; i < *mEmitNum_s * 2; ++i) {
                const sead::FormatFixedSafeString<32> name("%s%d", mEmitPartsName_s.cstr(), i);
                if (enemy->getActorPartsActor(name).hasProc()) {
                    ksys::act::ActorConstDataAccess accessor;
                    ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                }
                enemy->sub_7100D3CFEC(name);
            }
        }
    }
}

bool GanonAttackWithEmitChemical::init_(sead::Heap* heap) {
    return GanonWeaponNearAttack::init_(heap);
}

// NON_MATCHING: the stores of 0x170..0x17a are merged (str xzr / strh) in ours; the original stores them one by one
// (probably members of a type whose stores LLVM does not combine)
void GanonAttackWithEmitChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonWeaponNearAttack::enter_(params);
    const f32 start_frame = *mEmitStartFrame_s;
    _170 = _174 = 0.0f;
    _178 = false;
    _179 = false;
    _17a = false;
    _168 = start_frame;
    _16c = start_frame;
    _17c.makeIdentity();
}

void GanonAttackWithEmitChemical::leave_() {
    GanonWeaponNearAttack::leave_();
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor);
    if (!enemy)
        return;
    if (!enemy->m172()) {
        const auto* life = enemy->getLife();
        if ((!life || *life != 0) && !isActorGoingBackToRootAi())
            return;
    }
    sub_7100172FA8();
}

void GanonAttackWithEmitChemical::sub_7100172FA8() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor)) {
        for (s32 i = 0; i < *mEmitNum_s * 2; ++i) {
            const sead::FormatFixedSafeString<32> name("%s%d", mEmitPartsName_s.cstr(), i);
            if (enemy->getActorPartsActor(name).hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                if (accessor.isStateCalc())
                    accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
            }
        }
    }
    if (!mCallSEKeyAtAtOn_s.isEmpty() && _17a && mEffectHandle.sub_7101241AD8(1))
        mEffectHandle.fadeXLink();
}

void GanonAttackWithEmitChemical::loadParams_() {
    GanonWeaponNearAttack::loadParams_();
    getStaticParam(&mEmitNum_s, "EmitNum");
    getStaticParam(&mEmitInterval_s, "EmitInterval");
    getStaticParam(&mEmitAttackPower_s, "EmitAttackPower");
    getStaticParam(&mEmitMinDamage_s, "EmitMinDamage");
    getStaticParam(&mChildCreateLimit_s, "ChildCreateLimit");
    getStaticParam(&mEmitOffsetFromParent_s, "EmitOffsetFromParent");
    getStaticParam(&mEmitIntervalDist_s, "EmitIntervalDist");
    getStaticParam(&mEmitIntervalRotate_s, "EmitIntervalRotate");
    getStaticParam(&mEmitScale_s, "EmitScale");
    getStaticParam(&mEmitMaxScale_s, "EmitMaxScale");
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mEmitStartFrame_s, "EmitStartFrame");
    getStaticParam(&mEmitAngleFromParent_s, "EmitAngleFromParent");
    getStaticParam(&mEmitActorSpeedRotate_s, "EmitActorSpeedRotate");
    getStaticParam(&mEmitActorName_s, "EmitActorName");
    getStaticParam(&mEmitBaseBoneName_s, "EmitBaseBoneName");
    getStaticParam(&mEmitPartsName_s, "EmitPartsName");
    getStaticParam(&mCallSEKeyAtAtOn_s, "CallSEKeyAtAtOn");
    getStaticParam(&mEmitActorSpeed_s, "EmitActorSpeed");
    getStaticParam(&mEmitBoneRotateOffset_s, "EmitBoneRotateOffset");
}

void GanonAttackWithEmitChemical::calc_() {
    GanonWeaponNearAttack::calc_();
}

}  // namespace uking::action
