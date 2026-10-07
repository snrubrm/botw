#include "KingSystem/World/worldChemicalMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::world {

void ChemicalMgr::initBeforeStageGen() {
    sead::ScopedLock<sead::CriticalSection> lock(&mChemicalPairLock);
    _cf8.sub_71010C9B48();
    _ae8->sub_7100D9AA84();
    mChemicalPairs.clear();
    sub_71010CB39C();
}

void ChemicalMgr::unload2() {
    sead::ScopedLock<sead::CriticalSection> lock(&mChemicalPairLock);
    act::ActorConstDataAccess accessor;
    act::acquireActor(&_d88, &accessor);
    if (accessor.isStateCalc())
        accessor.sleep(act::BaseProc::SleepWakeReason::_0);
    _cf8.sub_71010C9CFC();
    mChemicalPairs.clear();
    if (_ae8) {
        auto* terrain = ksys::tera::Terrain::instance();
        if (terrain && terrain->isGrassEnabled())
            ksys::tera::sub_71011501C8(terrain->sub_710114DE4C());
        sub_71010CB39C();
        _ae8->sub_7100D9AAE4();
    }
}


void ChemicalMgr::sub_71010CC5AC() {
    _cf8.sub_71010C9438();
}

bool ChemicalMgr::x_4() const {
    return _b10 < 10;
}

void ChemicalMgr::x_5(ksys::act::Actor* actor) {
    _cf8.sub_71010C9D00(actor);
}

void ChemicalMgr::x_7(ksys::act::Actor* actor) {
    _cf8.sub_71010C9E48(actor);
}

Unk_710250c698* ChemicalMgr::x_8() {
    sead::ScopedLock<sead::CriticalSection> lock(&_c10);
    auto* entry = _c60.popBack();
    if (entry)
        _c70.pushBack(entry);
    return entry;
}

// NON_MATCHING: indexOf uses a signed count loop rather than the original pointer countdown.
bool ChemicalMgr::x_9(Unk_710250c698* entry) {
    entry->_8 &= ~1u;
    sead::ScopedLock<sead::CriticalSection> lock(&_c10);
    const s32 index = _c70.indexOf(entry);
    if (index >= 0) {
        _c70.erase(index);
        _c60.pushBack(entry);
    }
    return true;
}

// NON_MATCHING: aggregate initialization clears the type byte separately.
void ChemicalMgr::sub_71010CBDCC(act::Chemical* first, act::Chemical* second, s32 type) {
    sead::ScopedLock<sead::CriticalSection> lock(&mChemicalPairLock);
    if (mChemicalPairs.isFull())
        return;
    // Original pair types are stored and compared as bytes, including the input truncation.
    const u8 pair_type = type;
    for (const auto& pair : mChemicalPairs) {
        if (pair.first == first && pair.second == second && pair.type == pair_type)
            return;
    }
    auto* pair = mChemicalPairs.emplaceBack();
    pair->type = pair_type;
    pair->first = first;
    pair->second = second;
}

// NON_MATCHING: iterator advancement uses the entry pointer rather than the node pointer.
void ChemicalMgr::sub_71010CBEAC(act::Chemical* chemical) {
    sead::ScopedLock<sead::CriticalSection> lock(&mChemicalPairLock);
    for (auto it = mChemicalPairs.begin(); it != mChemicalPairs.end();) {
        auto* pair = &*it;
        ++it;
        if (pair->first == chemical || pair->second == chemical)
            mChemicalPairs.erase(pair);
    }
}

}  // namespace ksys::world
