#include "Game/AI/AI/aiPriestBossShadowCloneThrow.h"
#include <cmath>
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

namespace {
// inline-only in the original; name is a guess. Evidence: m35 and m39 inline the same locked payload write
// (the actor and the target link are computed before the lock; the vector is zero in m35 and the m38 position
// in m39).
void setPayload(Unk_7102415df0& sender, ksys::act::Actor* actor, u32 command,
                const ksys::act::BaseProcLink& target, const sead::Vector3f& pos) {
    sead::ScopedLock<sead::JobQueueLock> lock(&sender._18.mLock);
    sender._18._0 = command;
    sender._18._8.acquire(actor, false);
    sender._18._18 = target;
    sender._18._28 = pos;
}

// inline-only in the original; name is a guess (same sequence as setPayload above: the actor is loaded before the
// lock).
void setPayload(Unk_71023b1860& sender, ksys::act::Actor* actor, u32 command) {
    sead::ScopedLock<sead::JobQueueLock> lock(&sender._18.mLock);
    sender._18._0 = command;
    sender._18._18 = false;
    sender._18.mLink.acquire(actor, false);
}
}  // namespace

PriestBossShadowCloneThrow::PriestBossShadowCloneThrow(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (SafeString members); written
// like upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
PriestBossShadowCloneThrow::~PriestBossShadowCloneThrow() {
    ;
}

bool PriestBossShadowCloneThrow::init_(sead::Heap* heap) {
    for (auto& sender : _b8)
        sender._8 = &mActor->getMessageTransceiver();
    return true;
}

void PriestBossShadowCloneThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("準備完了待ち", params);
    _80 = ksys::Timer(*mPrepareTimer_s, *mPrepareTimer_s);
    _8c = 0;
    _90 = 2;
    _3ea = false;
    _3e8 = true;
    _3e9 = false;
}

void PriestBossShadowCloneThrow::m35() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = _8c; i < 8; ++i) {
        const s32 idx = _94[i];
        if (idx < 0 || !unit->sub_71007194D4(25 + idx, &accessor) || !accessor.isStateCalc())
            continue;

        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        auto& sender = _b8[idx];
        setPayload(sender, mActor, 1, enemy->_c48._8, sead::Vector3f::zero);
        sender.sub_710070DD78(accessor, true);
        ++_8c;
        break;
    }
}

// NON_MATCHING: instruction-identical except the loop guard (`cmp w25, #7; b.gt` in the original, `cmp #8; b.ge` here)
void PriestBossShadowCloneThrow::m39() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = _8c; i < 8; ++i) {
        const s32 idx = _94[i];
        if (idx < 0 || !unit->sub_71007194D4(25 + idx, &accessor) || !accessor.isStateCalc())
            continue;

        sead::Vector3f pos;
        m38(&pos, idx);
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        setPayload(_b8[idx], mActor, 0, enemy->_c48._8, pos);
        _b8[idx].sub_710070DD78(accessor, true);
    }
}

void PriestBossShadowCloneThrow::m34() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    for (auto& value : _94)
        value = -1;

    ksys::act::ActorConstDataAccess accessor;
    s32 count = 0;
    if (unit->sub_71007194D4(25, &accessor)) {
        sead::Vector3f pos;
        m38(&pos, false);
        if (accessor.isStateSleep()) {
            sead::Matrix34f mtx;
            mtx.makeIdentity();
            mtx.setTranslation(pos);
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
            count = 1;
            _94[0] = 0;
        }
    }
    if (unit->sub_71007194D4(26, &accessor)) {
        sead::Vector3f pos;
        m38(&pos, true);
        if (accessor.isStateSleep()) {
            sead::Matrix34f mtx;
            mtx.makeIdentity();
            mtx.setTranslation(pos);
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
            _94[count] = 1;
        }
    }
}

bool PriestBossShadowCloneThrow::m36() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return false;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = 25; i < 33; ++i) {
        if (unit->sub_71007194D4(i, &accessor) && accessor.isStateCalc())
            return false;
    }
    return true;
}

// NON_MATCHING: the original selects each of the three bone translation components separately (three csel of the
// row pointers of left / right); ours selects the matrix once. The identity matrices are `makeIdentity()` (TU-local
// literal pool, as in the original)
void PriestBossShadowCloneThrow::m38(sead::Vector3f* out, s32 which) {
    const bool a2 = which & 1;
    sead::Matrix34f left;
    left.makeIdentity();
    sead::Matrix34f right;
    right.makeIdentity();
    mActor->sub_71011D57F8(&left, mShadowCloneLefeBoneName_s);
    mActor->sub_71011D57F8(&right, mShadowCloneRightBoneName_s);

    const f32 offset_y = *mShadowCloneOffsetY_s;
    f32 angle_offset = *mShadowCloneAngleOffset_s;
    const sead::Matrix34f& bone = a2 ? left : right;
    const f32 base_x = mActor->getMtx().m[0][0];
    const f32 base_z = mActor->getMtx().m[2][0];
    out->x = bone(0, 3);
    out->y = bone(1, 3);
    if (a2)
        angle_offset = -angle_offset;
    out->z = bone(2, 3);
    const f32 angle = sead::Mathf::deg2rad(angle_offset + 90.0f);
    const f32 c = std::cos(angle) * *mShadowCloneRadius_s;
    const f32 s = std::sin(angle);
    const f32 radius = *mShadowCloneRadius_s;
    out->x += base_x * c;
    out->y += offset_y + (s * radius - radius);
    out->z += base_z * c;
}

bool PriestBossShadowCloneThrow::m37() {
    return mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                  true);
}

// NON_MATCHING: instruction-identical except the last accessor: the original recomputes `sp + 8` for the destructor,
// ours keeps it in x19 (the dead `unit` register)
void PriestBossShadowCloneThrow::leave_() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    for (s32 i = 25; i < 33; ++i) {
        ksys::act::ActorConstDataAccess accessor;
        if (unit->sub_71007194D4(i, &accessor))
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason(0));
    }

    setPayload(_3b0, mActor, 5);
    ksys::act::ActorConstDataAccess accessor;
    if (unit->sub_71007194CC(&accessor))
        _3b0.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
}

void PriestBossShadowCloneThrow::loadParams_() {
    getStaticParam(&mShadowCloneOffsetY_s, "ShadowCloneOffsetY");
    getStaticParam(&mShadowCloneRadius_s, "ShadowCloneRadius");
    getStaticParam(&mShadowCloneAngleOffset_s, "ShadowCloneAngleOffset");
    getStaticParam(&mPrepareTimer_s, "PrepareTimer");
    getStaticParam(&mShadowCloneLefeBoneName_s, "ShadowCloneLefeBoneName");
    getStaticParam(&mShadowCloneRightBoneName_s, "ShadowCloneRightBoneName");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
