#include "Game/AI/Action/actionForkASTrgEmitShockWave.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
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

namespace {
// Attack attribute bits for AttackAttr 1/2/3 (0 otherwise).
const u32 sAttackAttrBits[] = {1, 2, 4};
}  // namespace

// Creates the shockwave actor with the attack params. The original makes a discarded cstr()
// call on the actor name (a real virtual call in the asm) before creating the actor with the
// name's raw top pointer (Balloon::sub_71000B70DC precedent).
// NON_MATCHING: load scheduling only — the original hoists the ScaleTime-bits word load into
// the guard-pierce ternary (between its orr and cmp); ours sinks it below the 0x40 csel, with
// cascading callee-saved register renames. All calls, branches, constants and the table match.
// NOTE: loadParams_ proves [0x58] holds "IsForceGuardBreak" and [0x60] "IsIniviciblePierce",
// yet both this function and sub_710014F780 read [0x60] for bit 0x40 and [0x58] for 0x100 —
// i.e. the "IsForceGuardBreak" param drives 0x100 and "IsIniviciblePierce" drives 0x40.
// Any other AttackAttr-masks must be verified against their own offsets, not assumed.
ksys::act::BaseProc* ForkASTrgEmitShockWave::sub_710014F4BC() {
    const s32 idx = *mAttackIntensity_s - 1;
    u32 mask = 0;
    if ((u32)idx <= 2)
        mask = sAttackAttrBits[idx];
    const f32 scale_time = *mMaxScale_s;
    mask = *mIsGuardPierce_s ? (mask | 0x8) : mask;
    mask = *mIsIniviciblePierce_s ? (mask | 0x40) : mask;
    mask = *mIsForceGuardBreak_s ? (mask | 0x100) : mask;
    mask = *mIsHeavy_s ? (mask | 0x8000) : mask;
    s32 power = *mPower_s;
    if (power < 0)
        power = static_cast<ksys::act::PlayerOrEnemy*>(mActor)->getEnemyAtkPower();
    const s32 min_damage = *mAtMinDamage_s;

    ksys::act::InstParamPack pack;
    pack->addMatrix(mActor->getMtx());
    pack->add(static_cast<s32>(mask), "AttackAttr");
    pack->add(scale_time, "ScaleTime");
    pack->add(true, "IsReuseActor");
    pack->add(power, "AttackPower");
    pack->add(min_damage, "AtMinDamage");

    auto* creator = ksys::act::ActorCreator::instance();
    mShockWaveActorName_s.cstr();
    auto* proc = creator->createActor(mShockWaveActorName_s.getStringTop(),
                                      ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
                                      &pack, true, false);
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(proc)) {
        bullet->sub_710000497C(mActor);
        bullet->_bd0._0.acquire(mActor, false);
    }
    return proc;
}

// NON_MATCHING: micro-diffs only — ours sign-extends the AttackIntensity load (ldrsw) and
// indexes the bits table with lsl (64-bit idx), keeps map_power in w8 not w22; the original
// uses ldr + sxtw and keeps map_power in w22. Structure, calls, branches and constants match.
// Bit mapping (verified against loadParams_ offsets, same as sub_710014F4BC): the
// "IsForceGuardBreak" param ([0x58]) drives 0x100 and "IsIniviciblePierce" ([0x60]) drives 0x40.
bool ForkASTrgEmitShockWave::sub_710014F780(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    auto* root = actor->getRootAi();
    if (!root)
        return false;
    const bool* reuse = nullptr;
    if (!root->getMapUnitParam(&reuse, "IsReuseActor"))
        return false;
    if (*reuse != true)
        return false;
    const s32* map_power = nullptr;
    if (!root->getMapUnitParam(&map_power, "AttackPower"))
        return false;
    s32 power = *mPower_s;
    if (power >= 0)
        power = static_cast<ksys::act::PlayerOrEnemy*>(mActor)->getEnemyAtkPower();
    if (*map_power != power)
        return false;
    const f32* map_time = nullptr;
    if (!root->getMapUnitParam(&map_time, "ScaleTime"))
        return false;
    if (*map_time != *mScaleTime_s)
        return false;
    const s32* map_attr = nullptr;
    if (!root->getMapUnitParam(&map_attr, "AttackAttr"))
        return false;
    const s32 attr = *mAttackIntensity_s;
    const s32 idx = attr - 1;
    u32 mask = 0;
    if ((u32)idx <= 2)
        mask = sAttackAttrBits[idx];
    mask = *mIsGuardPierce_s ? (mask | 0x8) : mask;
    mask = *mIsIniviciblePierce_s ? (mask | 0x40) : mask;
    mask = *mIsForceGuardBreak_s ? (mask | 0x100) : mask;
    mask = *mIsHeavy_s ? (mask | 0x8000) : mask;
    if (*map_attr != static_cast<s32>(mask))
        return false;
    const s32* map_min = nullptr;
    if (!root->getMapUnitParam(&map_min, "AtMinDamage"))
        return false;
    return *map_min == *mAtMinDamage_s;
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
