#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"


namespace ksys::as {

// NON_MATCHING: block layout (the original shares the "return true" block)
bool ASList::Unk2::sub_7101163AF4() {
    if ((_20 && !(_43 & 1)) || (_28 && !(_43 & 2)))
        return true;
    return false;
}

bool ASList::Unk2::sub_7101162F2C() {
    Element* element = _18;
    if (!element)
        return false;
    Context* context = _0;
    const res::ASResource* resource = context->sub_7101258CC0();
    return element->m27(context, resource);
}

void ASList::Unk2::sub_7101163044(f32 value) {
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        element->m20(context, resource, value);
    }
}

f32 ASList::Unk2::sub_71011630A4() {
    f32 result = 0;
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        if (auto* params = element->m25(context, resource))
            result = params->_10;
    }
    return result;
}

void ASList::Unk2::sub_7101163100(f32 value) {
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        element->m19(context, resource, value);
    }
}

f32 ASList::Unk2::sub_7101163160() {
    f32 result = 0;
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        if (auto* params = element->m25(context, resource))
            result = params->_c;
    }
    return result;
}

void ASList::Unk2::sub_71011631BC(f32 value) {
    if (value < 0)
        return;
    _0->_e0 = value;
}

f32 ASList::Unk2::sub_71011631D0() {
    return _0->_e0;
}

void ASList::Unk2::sub_71011631DC(f32 value) {
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        element->m21(context, resource, value);
    }
}

f32 ASList::Unk2::sub_710116323C() {
    f32 result = 0;
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        if (auto* params = element->m25(context, resource))
            result = params->_14;
    }
    return result;
}

void ASList::Unk2::sub_7101163298(f32 value) {
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        element->m16(context, resource, value);
    }
}

f32 ASList::Unk2::sub_71011632F8() {
    f32 result = 0;
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        if (auto* params = element->m25(context, resource))
            result = params->_4;
    }
    return result;
}

f32 ASList::Unk2::sub_7101163564() {
    f32 result = 0;
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        if (auto* params = element->m25(context, resource))
            result = params->_8;
    }
    return result;
}

bool ASList::sub_710115AA68(const sead::SafeString& name) {
    sead::SafeString out_name;
    bool a3 = false;
    void* a4 = nullptr;
    return sub_710115AABC(name, &out_name, &a3, &a4, true) != nullptr;
}

// NON_MATCHING: the original reloads _163 after zeroing _68/_74 (its stores may alias the flag byte there,
// e.g. if the flag is not a plain member) and allocates the zero vector in different registers
const sead::Vector3f& ASList::sub_710115D2D4() {
    if (!(_163 & 1)) {
        _68 = sead::Vector3f::zero;
        _74 = sead::Vector3f::zero;
        for (int i = 0, n = mSlots.size(); i < n; ++i)
            mSlots[i].sub_7101164F3C(&_68, &_74, &_14);
        _163 |= 1;
    }
    return _68;
}

void ASList::sub_710115BAF8(const sead::SafeString& bone_name) {
    if (!_8)
        return;
    _18.copy(bone_name);
    if (bone_name.isEmpty())
        _14.reset();
    else
        _14 = _8->searchBone(bone_name);
}

void ASList::sub_710115CE44(const sead::SafeString& bone_name) {
    if (!_d8)
        return;
    if (_13 == 0xff)
        return;
    if (_13 == 0) {
        _40.copy(_18);
    } else if (_14.isValid()) {
        static_cast<void>(bone_name == _18);
    }
    sub_710115BAF8(bone_name);
    ++_13;
}

void ASList::sub_710115D0AC() {
    if (!_d8)
        return;
    if (_13 == 0)
        return;
    if (--_13 != 0)
        return;
    sub_710115BAF8(_40);
    _40.copy(sead::SafeString::cEmptyString);
}

bool ASList::sub_710115B01C(int slot, int bank, bool a3) {
    if (auto* entry = getEntry(slot, bank))
        return entry->sub_7101162254(a3);
    return false;
}

bool ASList::sub_710115C11C() {
    const bool ret = _163 & 2;
    _163 &= ~2;
    for (int i = 0, n = mSlots.size(); i < n; ++i)
        mSlots[i].sub_7101164900(_d8->getParam()->getRes().mModelList, i, _d8);
    return ret;
}

// NON_MATCHING: see sub_710115D2D4
const sead::Vector3f& ASList::sub_710115D3B8() {
    if (!(_163 & 1)) {
        _68 = sead::Vector3f::zero;
        _74 = sead::Vector3f::zero;
        for (int i = 0, n = mSlots.size(); i < n; ++i)
            mSlots[i].sub_7101164F3C(&_68, &_74, &_14);
        _163 |= 1;
    }
    return _74;
}

bool ASList::x_6(int kind, int a2, f32 value) {
    const s8 idx = _f0[kind];
    if (idx < 0)
        return false;
    _e0[idx]._f32 = value;
    return true;
}

bool ASList::x_2(int a1, int bit, bool on, bool a4) {
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

int ASList::sub_710115EC5C(int kind, int a2) {
    const s8 idx = _f0[kind];
    if (idx < 0)
        return 0;
    return _e0[idx]._s32;
}

f32 ASList::sub_710115EC98(int kind, f32 (ASList::*fn)(), int a4) {
    if (fn)
        return (this->*fn)();
    const s8 idx = _f0[kind];
    if (idx < 0)
        return 0;
    return _e0[idx]._f32;
}

const char* ASList::sub_710115ECF4(int kind, int a2) {
    const s8 idx = _f0[kind];
    if (idx < 0)
        return "";
    return _e0[idx]._str_ptr->cstr();
}

// NON_MATCHING: the original tests 0, 0x19 and then 6 (our switch lowering tests 0x19, 6, then 0)
bool ASList::sub_710115ED5C(int a1, int bit) {
    if (bit < 0)
        return false;

    switch (bit) {
    case 0:
        return _d8 && _d8->checkBasicSig();
    case 0x19:
        return _d8 && _d8->checkRemainsSignal();
    case 6:
        if (_d8) {
            if (auto* lod = _d8->getLodState()) {
                if (!lod->mFlags8.isOnBit(1))
                    return true;
            }
        }
        return false;
    default: {
        const s8 idx = _f0[0x42];
        if (idx < 0)
            return false;
        const u64* bits = _e0[idx]._u64_ptr;
        if (!bits)
            return false;
        return *bits & (1ul << bit);
    }
    }
}

void ASList::sub_710115F158(ASList* other, int slot, int other_slot, int bank, int other_bank) {
    auto* entry = getEntry(slot, bank);
    if (!entry)
        return;
    auto* other_entry = other->getEntry(other_slot, other_bank);
    if (!other_entry)
        return;
    entry->sub_71011633C0(other_entry);
}

void ASList::sub_710115F1D8(int slot, int bank, f32 value) {
    if (auto* entry = getEntry(slot, bank))
        entry->sub_7101161CF8(true, value);
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

bool ASList::x(int a1, Unk4* query, int slot, int bank, bool (Unk2::*fn)(Unk4*, int, bool),
               bool a6) {
    if (auto* entry = getEntry(slot, bank))
        return (entry->*fn)(query, a1, a6);
    return false;
}

}  // namespace ksys::as
