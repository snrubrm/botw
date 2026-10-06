#include "Game/AI/Action/actionSiteBossLswordAtkWithChemical.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

SiteBossLswordAtkWithChemical::SiteBossLswordAtkWithChemical(const InitArg& arg)
    : SiteBossLswordAtk(arg), _1c8() {}

SiteBossLswordAtkWithChemical::~SiteBossLswordAtkWithChemical() {
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
    _1a0 = 0;
    _1a8.freeBuffer();
    _1b8.freeBuffer();
}

bool SiteBossLswordAtkWithChemical::init_(sead::Heap* heap) {
    return SiteBossLswordAtk::init_(heap);
}

void SiteBossLswordAtkWithChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossLswordAtk::enter_(params);
    _188 = false;
    _189 = false;
    _18a = false;
    _198 = 0;
    _18c = ksys::Timer(*mEmitStartFrame_s, *mEmitStartFrame_s, 0.0f);
    for (s32 i = 0, n = _1a8.size(); i < n; ++i)
        _1a8(i) = false;
    for (s32 i = 0, n = _1b8.size(); i < n; ++i)
        _1b8(i) = sead::Vector3f::zero;
}

void SiteBossLswordAtkWithChemical::leave_() {
    SiteBossLswordAtk::leave_();
    if (sub_710072B7C4() || _189)
        sub_710025B7CC();
}

void SiteBossLswordAtkWithChemical::loadParams_() {
    SiteBossLswordAtk::loadParams_();
    getStaticParam(&mEmitNum_s, "EmitNum");
    getStaticParam(&mEmitInterval_s, "EmitInterval");
    getStaticParam(&mEmitAttackDamage_s, "EmitAttackDamage");
    getStaticParam(&mEmitActorMinDamage_s, "EmitActorMinDamage");
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
    getStaticParam(&mEmitPartsName_s, "EmitPartsName");
    getStaticParam(&mCallSEKeyAtAtOn_s, "CallSEKeyAtAtOn");
    getStaticParam(&mEmitActorSpeed_s, "EmitActorSpeed");
}

void SiteBossLswordAtkWithChemical::calc_() {
    SiteBossLswordAtk::calc_();
}

void SiteBossLswordAtkWithChemical::m37(sead::Vector3f* pos) {
    mActor->getMtx().getTranslation(*pos);
}

f32 SiteBossLswordAtkWithChemical::m38() {
    return *mEmitOffsetFromParent_s;
}

int SiteBossLswordAtkWithChemical::m39() {
    return 2;
}

}  // namespace uking::action

namespace uking::action {

// Sleeps the emitted parts actors and fades the held xlink event.
void SiteBossLswordAtkWithChemical::sub_710025B7CC() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (*mEmitNum_s >= 1) {
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
    }
    if (!mCallSEKeyAtAtOn_s.isEmpty() && _18a) {
        if (_1c8.sub_7101241AD8(1))
            _1c8.fadeXLink();
    }
}

}  // namespace uking::action
