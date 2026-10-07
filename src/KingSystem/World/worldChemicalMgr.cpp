#include "KingSystem/World/worldChemicalMgr.h"
#include <prim/seadScopedLock.h>

namespace ksys::world {

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

}  // namespace ksys::world
