#include "Game/AI/Action/actionGanonAttackWithEmitChemical.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

GanonAttackWithEmitChemical::GanonAttackWithEmitChemical(const InitArg& arg)
    : GanonWeaponNearAttack(arg) {}

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

void GanonAttackWithEmitChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonWeaponNearAttack::enter_(params);
}

void GanonAttackWithEmitChemical::leave_() {
    GanonWeaponNearAttack::leave_();
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
