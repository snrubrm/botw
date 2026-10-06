#include "Game/AI/Action/actionElectricAttack.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiActorLink.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "Game/AI/aiUnk_710073D258.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include <algorithm>

namespace uking::action {

ElectricAttack::ElectricAttack(const InitArg& arg) : TimeredASPlay(arg) {}

ElectricAttack::~ElectricAttack() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(sead::SafeString(mElectricActorKey_s.cstr()));
}

bool ElectricAttack::init_(sead::Heap* heap) {
    return TimeredASPlay::init_(heap) && sub_7100103040(heap);
}

void ElectricAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
    const f32 max_keep_time = static_cast<f32>(std::max(*mMaxKeepTimer_s, 1));
    _a4 = ksys::Timer(max_keep_time, max_keep_time);
    const f32 hit_after_time = static_cast<f32>(*mHitAfterTime_s);
    _b0 = ksys::Timer(hit_after_time, hit_after_time);
    _bc = false;
    sub_71001034E0();
}

void ElectricAttack::leave_() {
    sub_7100103830();
    TimeredASPlay::leave_();
}

void ElectricAttack::loadParams_() {
    TimeredASPlay::loadParams_();
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mMaxTimer_s, "MaxTimer");
    getStaticParam(&mMaxKeepTimer_s, "MaxKeepTimer");
    getStaticParam(&mHitAfterTime_s, "HitAfterTime");
    getStaticParam(&mElectricActorName_s, "ElectricActorName");
    getStaticParam(&mElectricActorKey_s, "ElectricActorKey");
}

void ElectricAttack::calc_() {
    TimeredASPlay::calc_();
    if (sub_7100103684()) {
        if (!_bc)
            _bc = true;
        _b0.update();
    } else if (_bc) {
        _b0.update();
    }
    _a4.update();
    if (_a4.value <= sead::Mathf::epsilon() || _b0.value <= sead::Mathf::epsilon()) {
        sub_7100103830();
        setFinished();
    }
}

bool ElectricAttack::sub_7100103040(sead::Heap* heap) {
    auto* creator = ksys::act::ActorCreator::instance();
    if (creator && creator->isBlockSpawns())
        return true;

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy) {
        if (enemy->getActorPartsActor(sead::SafeString(mElectricActorKey_s.cstr())).hasProc())
            return true;
    }

    ksys::act::InstParamPack params;
    params->addMatrix(enemy->getMtx());
    params->add(0, "AttackPower");
    params->add(static_cast<f32>(*mMaxTimer_s), "ScaleTime");
    params->add(0.0f, "Range");
    ksys::act::ActorCreator::addScale(params, 1.0f);

    auto* actor = sead::DynamicCast<ksys::act::Actor>(ksys::act::ActorCreator::instance()->createActor(
        mElectricActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        &params, true, false));
    if (enemy && actor) {
        if (enemy->sub_7100D3CED8(sead::SafeString(mElectricActorKey_s.cstr()), heap)) {
            enemy->sub_7100D3D108(sead::SafeString(mElectricActorKey_s.cstr()), actor);
            auto* bind = static_cast<Unk_71025afb58*>(
                sub_710073D4D4(actor, "ChemicalBulletBindActor"));
            if (auto* link = sead::DynamicCast<Unk_7102370e70>(bind))
                link->mLink.acquire(enemy, false);
            if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor)) {
                bullet->sub_71000048BC(enemy);
                bullet->sub_710000497C(enemy);
            }
            return true;
        }
    }
    return false;
}

void ElectricAttack::sub_71001034E0() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->getActorPartsActor(sead::SafeString(mElectricActorKey_s.cstr()));
        ksys::act::acc::Bullet accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.setScaleTime(static_cast<f32>(*mMaxTimer_s), enemy);
        accessor.setProperties(enemy->getMtx(), nullptr, nullptr, nullptr, false, 0, -1);
    }
}

void ElectricAttack::sub_7100103830() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->getActorPartsActor(sead::SafeString(mElectricActorKey_s.cstr()));
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

bool ElectricAttack::sub_7100103684() {
    bool result = false;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto* proc = enemy->getActorPartsActor(sead::SafeString(mElectricActorKey_s.cstr()))
                         .getProc(nullptr, nullptr);
        auto* actor = sead::DynamicCast<ksys::act::Actor>(proc);
        if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor))
            result = (bullet->_cf4 >> 5) & 1;
    }
    return result;
}

}  // namespace uking::action
