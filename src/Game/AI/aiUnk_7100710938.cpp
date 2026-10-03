#include <cmath>
#include <heap/seadHeap.h>
#include <random/seadGlobalRandom.h>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007024d4.h"
#include "Game/UI/uiManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Event/evtManager.h"

bool Unk_71007024d4::sub_71007107CC(sead::Heap* heap, s32 count) {
    if (count < 1)
        return true;
    auto* entries = new (heap, 8, std::nothrow) Entry[count];
    if (entries) {
        mCount = count;
        mEntries = entries;
    }
    return mEntries != nullptr;
}

// NON_MATCHING: the original materialises the 0.5f constant before loading the GlobalRandom instance
// (one instruction order; `const s32 half = _14 * 0.5f;` as a separate local matches)
void Unk_71007024d4::sub_7100710890(s32 min, s32 max) {
    _14 = min;
    _18 = max;
    s32 time = min;
    if (max > min)
        time = sead::GlobalRandom::instance()->getS32Range(min, max);
    _8 = ksys::Timer(time, time);
    _8.value += -sead::GlobalRandom::instance()->getS32Range(0, static_cast<s32>(_14 * 0.5f));
}

void Unk_71007024d4::sub_7100710938() {
    if (uking::ui::Manager::instance()->isPausedMaybe())
        return;
    if (!ksys::evt::Manager::instance()->sub_7100DB19DC())
        return;

    sead::Vector3f pos;
    if (!m1(&pos))
        return;

    sub_7100710A5C(pos);
    _8.update();
    if (_8.value <= sead::Mathf::epsilon()) {
        sead::Vector3f spawn_pos;
        m0(&spawn_pos);
        sub_7100710C14(spawn_pos);
        s32 time = _14;
        if (_18 > _14)
            time = sead::GlobalRandom::instance()->getS32Range(_14, _18);
        _8 = ksys::Timer(time, time);
    }
}

void Unk_71007024d4::sub_7100710A5C(const sead::Vector3f& pos) {
    sead::FixedSafeString<64> name;
    m2(&name);
    if (name.isEmpty())
        return;

    ksys::act::InstParamPack pack;
    pack.getBuffer().addPosition(pos);
    auto* entry = mEntries;
    for (s32 i = 0; i != mCount; ++i, ++entry) {
        if (entry->link.hasProc())
            continue;
        if (entry->handle.isAllocatedOrFailed() && entry->handle.hasProcCreationFailed())
            entry->handle.deleteProcIfFailed();
        if (!entry->handle.isAllocatedOrFailed()) {
            ksys::act::ActorCreator::instance()->requestCreateActor(
                name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
                &entry->handle, &pack, nullptr, 1);
        }
    }
}

bool Unk_71007024d4::sub_7100710C14(const sead::Vector3f& pos) {
    auto* entry_ptr = mEntries;
    for (s32 i = 0; i != mCount; ++i, ++entry_ptr) {
        auto& entry = *entry_ptr;
        if (entry.link.hasProc())
            continue;
        if (!entry.handle.isAllocatedOrFailed() || !entry.handle.isProcReady())
            continue;
        auto* actor = sead::DynamicCast<ksys::act::Actor>(entry.handle.releaseAndWakeProc());
        if (!actor)
            continue;

        m3(actor);
        sead::Matrix34f mtx = sead::Matrix34f::ident;
        mtx.setTranslation(pos);
        actor->setMatrix(mtx, nullptr);
        const sead::Vector3f velocity = sead::Vector3f::zero;
        sead::Vector3f ang_velocity = sead::Vector3f::ey;
        ang_velocity *= _1c;
        actor->setVelocity(&velocity, &ang_velocity);
        entry.link.acquire(actor, false);
        return true;
    }
    return false;
}

void Unk_71007024d4::sub_7100710DE4() {
    auto* entry = mEntries;
    for (s32 i = 0; i != mCount; ++i, ++entry) {
        entry->link.reset();
        entry->handle.deleteProc();
    }
}

void Unk_71007024d4::sub_7100710E3C() {
    auto* entry = mEntries;
    for (s32 i = 0; i != mCount; ++i, ++entry) {
        entry->link.reset();
        entry->handle.deleteProc();
    }
}
