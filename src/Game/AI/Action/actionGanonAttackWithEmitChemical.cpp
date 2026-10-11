#include "Game/AI/Action/actionGanonAttackWithEmitChemical.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include <math/seadMathCalcCommon.h>
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
// even with the native Timer and separate integer counter modeled.
void GanonAttackWithEmitChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonWeaponNearAttack::enter_(params);
    const f32 start_frame = *mEmitStartFrame_s;
    _168.rate = 0.0f;
    _174 = 0;
    _178 = false;
    _179 = false;
    _17a = false;
    _168.value = start_frame;
    _168.previous_value = start_frame;
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

// NON_MATCHING: the stop-query/attack loop joins and Timer reset store grouping
// differ from the original.
void GanonAttackWithEmitChemical::calc_() {
    GanonWeaponNearAttack::calc_();
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (!boss || !boss->_14e8.isOnBit(8))
        return;
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0) && !_178) {
        _178 = true;
        _168.reset(*mEmitStartFrame_s);
        if (!mCallSEKeyAtAtOn_s.isEmpty()) {
            xlinkSearchAndEmit(mActor, mCallSEKeyAtAtOn_s.cstr(), 1, &mEffectHandle);
            _17a = true;
        }
    }
    bool stop = sub_710072B7C4();
    if (!stop) {
        const s32 count = getNumAttackInfoMaybe(mActor);
        for (s32 i = 0; i < count; ++i) {
            auto* info = getAttackInfo(mActor, i);
            if (info && (info->_18 & 2)) {
                stop = true;
                break;
            }
        }
    }
    if (stop) {
        _179 = true;
        sub_7100172FA8();
    }
    if (!_178)
        return;
    _168.update();
    if (_168.value <= sead::Mathf::epsilon()) {
        if (*mEmitInterval_s >= 1 && *mEmitNum_s > _174) {
            sub_7100173138(_174);
            _168.reset(*mEmitInterval_s);
            ++_174;
        } else if (_174 < *mEmitNum_s && *mEmitNum_s != 0) {
            for (s32 i = 0; i < *mEmitNum_s; ++i)
                sub_7100173138(i);
        }
    }
}

}  // namespace uking::action
