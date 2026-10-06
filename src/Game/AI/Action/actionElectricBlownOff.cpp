#include "Game/AI/Action/actionElectricBlownOff.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiActorLink.h"
#include "Game/AI/aiUnk_710073D258.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"

namespace uking::action {

ElectricBlownOff::ElectricBlownOff(const InitArg& arg) : BlownOff(arg) {}

ElectricBlownOff::~ElectricBlownOff() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(sead::SafeString(mElectricActorKey_s.cstr()));
}

bool ElectricBlownOff::init_(sead::Heap* heap) {
    return BlownOff::init_(heap) && sub_7100103E00(heap);
}

// NON_MATCHING: the byte reset and the timer's current/previous stores are scheduled differently.
void ElectricBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
    if (auto* manager = sub_710072BA90(mActor)) {
        if (manager->checkDamageFlags(0)) {
            _1a8 = 0;
            _19c.reset(sead::Mathi::max(1, *mMaxKeepTimer_s));
            sub_710010441C();
            return;
        }
    }
    _1a8 = 0xff;
}

void ElectricBlownOff::leave_() {
    BlownOff::leave_();
    if (!_1a8) {
        _1a8 = true;
        sub_710010451C();
    }
}

void ElectricBlownOff::loadParams_() {
    BlownOff::loadParams_();
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mMaxTimer_s, "MaxTimer");
    getStaticParam(&mMaxKeepTimer_s, "MaxKeepTimer");
    getStaticParam(&mElectricActorName_s, "ElectricActorName");
    getStaticParam(&mElectricActorKey_s, "ElectricActorKey");
}

void ElectricBlownOff::calc_() {
    BlownOff::calc_();
    if (_1a8)
        return;
    if (_19c.value <= sead::Mathf::epsilon()) {
        _1a8 = 1;
        sub_710010451C();
    } else {
        _19c.update();
    }
}

bool ElectricBlownOff::sub_7100103E00(sead::Heap* heap) {
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

void ElectricBlownOff::sub_710010441C() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->getActorPartsActor(sead::SafeString(mElectricActorKey_s.cstr()));
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.setProperties(enemy->getMtx(), nullptr, nullptr, nullptr, false, 0, -1);
    }
}

void ElectricBlownOff::sub_710010451C() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->getActorPartsActor(sead::SafeString(mElectricActorKey_s.cstr()));
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

}  // namespace uking::action
