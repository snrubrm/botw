#include "KingSystem/ActorSystem/AS/ASList.h"


namespace ksys::as {

// NON_MATCHING: block layout (the original shares the "return true" block)
bool ASList::Unk2::sub_7101163AF4() {
    if ((_20 && !(_43 & 1)) || (_28 && !(_43 & 2)))
        return true;
    return false;
}

bool ASList::x_6(int kind, int a2, f32 value) {
    const s8 idx = _f0[kind];
    if (idx < 0)
        return false;
    _e0[idx]._f32 = value;
    return true;
}

bool ASList::x_2(int a1, int bit, bool on) {
    if (bit < 0)
        return false;
    const s8 idx = _f0[0x42];
    if (idx < 0)
        return false;
    u64* bits = _e0[idx]._u64_ptr;
    if (!bits)
        return false;
    if (on)
        *bits |= 1ul << bit;
    else
        *bits &= ~(1ul << bit);
    return true;
}

void ASList::x_3(int slot, int bank, void (Unk2::*fn)(f32), f32 value) {
    if (auto* entry = getEntry(slot, bank))
        (entry->*fn)(value);
}

f32 ASList::x_5(int slot, int bank, f32 (Unk2::*fn)()) {
    if (auto* entry = getEntry(slot, bank))
        return (entry->*fn)();
    return 0.0f;
}

bool ASList::x_7(int slot, int bank, bool (Unk2::*fn)()) {
    if (auto* entry = getEntry(slot, bank))
        return (entry->*fn)();
    return false;
}

bool ASList::x(int a1, const sead::SafeString& a2, int slot, int bank,
               bool (Unk2::*fn)(const sead::SafeString&, int, bool), bool a6) {
    if (auto* entry = getEntry(slot, bank))
        return (entry->*fn)(a2, a1, a6);
    return false;
}

}  // namespace ksys::as
