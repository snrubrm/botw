#include "Game/AI/Action/actionLastBossChemicalPillarAttack.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/AI/aiUnk_710072BA90.h"

namespace uking::action {

LastBossChemicalPillarAttack::LastBossChemicalPillarAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

LastBossChemicalPillarAttack::~LastBossChemicalPillarAttack() = default;

bool LastBossChemicalPillarAttack::sub_71001CF880() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        for (u32 i = 0; i < 16; ++i) {
            const sead::FormatFixedSafeString<64> name("IronPile%d", i);
            if (enemy->getActorPartsActor(name).hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                if (accessor.isStateCalc() && !accessor.sub_7100D13BB8())
                    return false;
            }
        }
    }
    return true;
}

void LastBossChemicalPillarAttack::sub_71001CFA48(s32 index, ksys::act::ActorConstDataAccess* accessor) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        const sead::FormatFixedSafeString<64> name("IronPile%d", index);
        if (enemy->getActorPartsActor(name).hasProc())
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), accessor);
    }
}

bool LastBossChemicalPillarAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossChemicalPillarAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0;
    const f32 interval = *mParams.mCreateInterval_s;
    _50 = ksys::Timer(interval, interval);
    playAS("Chemical_Attack", true, 0, 0, -1.0f);
    _48 = -1;
    _4c = false;
    _4e = false;
    _5c.rate = -1.0f;
    _5c.value = 300.0f;
    _5c.previous_value = 300.0f;
}

void LastBossChemicalPillarAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossChemicalPillarAttack::loadParams_() {
    getStaticParam(&mParams.mPillarNum_s, "PillarNum");
    getStaticParam(&mParams.mAttackEndWait_s, "AttackEndWait");
    getStaticParam(&mParams.mCreateInterval_s, "CreateInterval");
    getStaticParam(&mParams.mPillarYOffset_s, "PillarYOffset");
}

void LastBossChemicalPillarAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

void LastBossChemicalPillarAttack::m32() {}

bool LastBossChemicalPillarAttack::isChangeable() const {
    auto* damage_mgr = sub_710072BA90(mActor);
    if (damage_mgr && (damage_mgr->getField54() == 9 || damage_mgr->getField54() == 10 ||
                       damage_mgr->getField54() == 22)) {
        return true;
    }
    return false;
}

}  // namespace uking::action
