#include "KingSystem/ActorSystem/AS/ASList.h"
#include <limits>
#include <prim/seadBitFlag.h>
#include <gsys/gsysModelNW.h>
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceModelList.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"
#include "KingSystem/Resource/Actor/resResourceASList.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"


namespace ksys::as {

// NON_MATCHING: the bank loop checks for count > 0 rather than count >= 1.
s32 ASList::sub_710115BED4(bool first_only) {
    const s32 count = mSlots.size();
    s32 result = 0;
    if (!(_163 & 2)) {
        _163 |= 2;
        gsys::BoneAccessKey key;
        key.model_unit_index = 0;
        key.bone_index = 0;
        s32 mode = 0;
        for (s32 i = 0; i < count; ++i) {
            if (mSlots[i].sub_71011653A4())
                continue;
            auto& slot = mSlots[i];
            if (slot._30) {
                slot.sub_7101164FF8();
                slot.sub_7101165008(key, mode, true);
                slot.sub_7101164E38(false);
            }
            if (first_only && mode == 3) {
                const s32 banks = slot._20.size();
                for (s32 bank = 0; bank < banks; ++bank) {
                    auto& entry = slot._20[bank];
                    if (entry._40 & 0x10)
                        entry.sub_7101162254(false);
                }
            } else {
                result = i;
            }
            mode = 3;
        }
    } else {
        for (s32 i = 0; i < count; ++i) {
            if (!mSlots[i].sub_71011653A4())
                return i;
        }
    }
    return result;
}

void ASList::x_0(const gsys::BoneAccessKey* key) {
    if (!_8)
        return;
    const sead::SafeString name = _8->getUnits().unsafeAt(key->model_unit_index)
                                     ->mModelUnit->getBoneName(key->bone_index);
    if (!_8)
        return;
    _18.copy(name);
    if (name.isEmpty())
        _14.reset();
    else
        _14 = _8->searchBone(name);
}


void ASList::startAnimationMaybe(f32 a2, f32 a3, const sead::SafeString& animation, int slot,
                               int bank, bool force) {
    if (!_d8 || mSlots.size() <= slot || mSlots[slot]._20.size() <= bank)
        return;

    AnimationRequest request;
    request.define = sub_710115AABC(animation, &request.name, &request.lookupFlag,
                                   &request.resource, false);
    request.slot = slot;
    request.bank = bank;
    request.value = a2;
    request.value2 = a3;
    request.force = force;
    if (request.define)
        sub_710115AE2C(request);
}

struct ASList::Unk2::InitArg {
    Unk1* slot;
    s32 index;
    const Context::Frame::Sizes* sizes;
};

static const char* const sUnk_710250FFE0[] = {"0Gear", "1Gear", "2Gear", "3Gear", "TopGear"};

ASList::Unk2::~Unk2() {
    if (_0) {
        delete _0;
        _0 = nullptr;
    }
}

bool ASList::Unk2::sub_71011617A8(const InitArg& arg, sead::Heap* heap) {
    _42 = arg.index;
    _8 = arg.slot;
    _0 = new (heap) Context;
    if (!_0)
        return false;
    return _0->sub_7101258AC8(*arg.sizes, heap);
}

void ASList::sub_7101160F10(gsys::ModelAnimation* animation, gsys::ModelNW* unit, s32 index,
                          nn::g3d::ICalculateBlendWeightCallback::CallbackArg& arg) {
    for (auto* entry : _c8) {
        if (entry->sub_7101163998(arg, unit, index))
            break;
    }
}

void ASList::Unk2::sub_710116173C() {
    _10 = 1.0f;
    mFlags = 1;
    _44[0] = 1;
    _48 = nullptr;
    for (auto& range : mBoneWeightRanges)
        range.params = nullptr;
    _18 = nullptr;
    _20 = nullptr;
    _28 = nullptr;
    if (_0->_d8) {
        _0->_d8 = nullptr;
        _0->sub_7101258C1C();
    }
    _0->mNumEvents2 = 0;
    _0->sub_710125923C();
}

// NON_MATCHING: the inlined reset swaps the flag-byte and linked-entry stores.
void ASList::Unk2::sub_7101162318() {
    if ((_40 & 4) && _18) {
        sub_7101161EE0(-1.0f, _18, true);
        sub_710116173C();
        mFlags |= 8;
        _0->_e0 = 1.0f;
        sub_7101161FDC();
    }
}

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

bool ASList::Unk2::sub_7101162FE8() {
    Element* element = _18;
    if (!element)
        return false;
    Context* context = _0;
    const res::ASResource* resource = context->sub_7101258CC0();
    if (auto* params = element->m25(context, resource))
        return params->sub_7101302878(0);
    return false;
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

const sead::SafeString& ASList::x_1(u32 slot, u32 seq_bank) {
    if (auto* entry = getEntry(slot, seq_bank))
        return *entry->sub_7101161CD8();
    return sead::SafeString::cEmptyString;
}

bool ASList::x_4(u32 slot, u32 seq_bank) {
    auto* entry = getEntry(slot, seq_bank);
    if (!entry)
        return true;
    return entry->_40 & 1;
}

bool ASList::Unk2::sub_71011637EC(Unk4* query, int a2, bool a3) {
    if (a3 && _10 <= 0)
        return false;
    return sub_7101259C78(_0, query, a2, 1, this);
}

bool ASList::Unk2::sub_710116383C(Unk4* query, int a2, bool a3) {
    if (a3 && _10 <= 0)
        return false;
    return sub_7101259C78(_0, query, a2, 2, this);
}

bool ASList::Unk2::sub_710116388C(Unk4* query, int a2, bool a3) {
    if (a3 && _10 <= 0)
        return false;
    return sub_7101259C78(_0, query, a2, 4, this);
}

bool ASList::Unk2::sub_71011638DC(Unk4* query, int a2, bool a3) {
    if (a3 && _10 <= 0)
        return false;
    return sub_7101259C78(_0, query, a2, 8, this);
}

bool ASList::Unk2::sub_7101163818(EventQueryResults* query, int type, bool a3) {
    if (a3 && _10 <= 0.0f)
        return false;
    return sub_7101259D04(_0, query, type, 1);
}

bool ASList::Unk2::sub_7101163868(EventQueryResults* query, int type, bool a3) {
    if (a3 && _10 <= 0.0f)
        return false;
    return sub_7101259D04(_0, query, type, 2);
}

bool ASList::Unk2::sub_71011638B8(EventQueryResults* query, int type, bool a3) {
    if (a3 && _10 <= 0.0f)
        return false;
    return sub_7101259D04(_0, query, type, 4);
}

bool ASList::Unk2::sub_7101163908(EventQueryResults* query, int type, bool a3) {
    if (a3 && _10 <= 0.0f)
        return false;
    return sub_7101259D04(_0, query, type, 8);
}

bool ASList::Unk2::sub_7101163950() {
    return _0->_921 & 1;
}

void ASList::Unk2::sub_710042BBEC() {
    mFlags |= 0x100;
}

void ASList::Unk2::sub_71011623DC(Unk2* other) {
    if (!_18 || !other->_18)
        return;
    const auto* resource = _0->sub_7101258CC0();
    if (resource == other->_0->sub_7101258CC0()) {
        mFlags = other->mFlags;
        _0->sub_710125A67C(*other->_0, true);
    }
}

// NON_MATCHING: compiler converts bit 7 to bool with a signed byte load and comparison.
bool ASList::Unk2::sub_7101163940() {
    return _0->_920 >> 7;
}

bool ASList::sub_710115AD68(const sead::SafeString& name) {
    sead::SafeString out_name;
    bool a3 = false;
    void* a4 = nullptr;
    const Unk8* define = sub_710115AABC(name, &out_name, &a3, &a4, false);
    return define && ((define->_10 >> 1) & 1);
}

bool ASList::sub_710115ADC0(const sead::SafeString& name) {
    sead::SafeString out_name;
    bool a3 = false;
    void* a4 = nullptr;
    const Unk8* define = sub_710115AABC(name, &out_name, &a3, &a4, false);
    auto* as = static_cast<res::AS*>(a4);
    return !define || !as || as->getForbidPartialDemoAs();
}

void ASList::sub_710115D4A4(f32 t, sead::Matrix34f* out, bool a3) {
    for (s32 i = 0; i < mSlots.size(); ++i) {
        if (mSlots[i].sub_71011650FC(t, out, a3, &_14))
            return;
    }
    out->makeIdentity();
}

void ASList::sub_710115CA28() {
    if (_b0)
        _b0->_21 = false;
    if (!_8 || _18.isEmpty())
        _14.reset();
    else
        _14 = _8->searchBone(_18);
    const s32 count = mSlots.size();
    for (s32 i = 0; i < count; ++i)
        mSlots[i].sub_7101164E38(false);
    _b0->sub_7100D68104(_8, nullptr, &_80, &_14);
}

void ASList::sub_710115C278(int slot) {
    Unk2* first = getEntry(slot, 0);
    const sead::SafeString* name = first ? first->sub_7101161CD8() : &sead::SafeString::cEmptyString;
    if (name->isEmpty())
        return;

    AnimationRequest request;
    request.define = sub_710115AABC(*name, &request.name, &request.lookupFlag, &request.resource, false);
    request.slot = 0;
    request.bank = 0;
    request.value = -1.0f;
    request.value2 = -1.0f;
    request.force = false;
    if (!request.define)
        return;
    if ((request.define->_10 & 3) == 2)
        return;

    const s32 count = mSlots.size();
    for (s32 i = 0; i < count; ++i) {
        if (i == slot)
            continue;
        auto& other = mSlots[i];
        if (!other.sub_71011653C4() && !other.sub_71011653B4())
            continue;
        request.slot = i;
        sub_710115AE2C(request);
        if (auto* entry = getEntry(i, 0))
            entry->sub_7101162E88(getEntry(slot, 0), i < slot);
    }
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

void ASList::sub_710115CD0C() {
    sub_710115BAF8(sead::SafeString::cEmptyString);
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

bool ASList::sub_710115EFD0(int kind, bool clamp, bool a3, f32 value) {
    const s8 idx = _f0[kind];
    if (idx < 0)
        return false;
    _e0[idx]._f32 = (clamp && value > 1) ? 1 : value;
    return true;
}

void ASList::sub_710115F444(int slot, int bank, void (Unk2::*fn)()) {
    if (auto* entry = getEntry(slot, bank))
        (entry->*fn)();
}

void ASList::sub_710115F4A0(bool value, s32 slot, s32 bank, void (Unk2::*fn)(bool)) {
    if (auto* entry = getEntry(slot, bank))
        (entry->*fn)(value);
}

void ASList::sub_710115F228(f32 value) {
    for (int i = 0; i < mSlots.size(); ++i) {
        for (int j = 0; j < mSlots[i]._20.size(); ++j)
            mSlots[i]._20[j].sub_71011631BC(value);
    }
}

void ASList::sub_710115C8D8(bool a1, bool a2) {
    if (_8) {
        if (a2) {
            _8->applyAnimationTo(_8, 2);
        } else {
            _8->applyAnimationTo(_8, 3);
            _163 |= 4;
        }
    }
}

void ASList::sub_710115C92C() {
    _10 = 0;
}

void ASList::sub_710115C634(bool a1) {
    bool restore = false;
    for (auto& slot : mSlots) {
        if (slot._4c) {
            restore = a1;
            slot._4c = 0;
        }
    }
    if (restore)
        _b0->sub_7100D68104(_8, nullptr, &_80, &_14);
}

// NON_MATCHING: the original reads both halves of the bone key through one base register (`ldrsh w3, [x19, #2]`); ours
// addresses the second half from `this`.
void ASList::sub_710115C934() {
    const gsys::BoneAccessKey& key = _14;
    if (key.isValid()) {
        sead::Vector3f scale;
        _8->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneLocalMatrix(&_80, &scale, key.bone_index);
        _8->setBoneLocalRTMatrix(key, sead::Matrix34f::ident);
    }
}

void ASList::sub_710115E1D4(s32* out_a, s32* out_b) {
    *out_a = 0;
    *out_b = 0;
    for (Unk6* node = _148; node; node = node->_30) {
        *out_a = sead::Mathi::max(*out_a, node->_11);
        *out_b = sead::Mathi::max(*out_b, node->_12);
    }
}

void ASList::Unk1::Fader::sub_71011598FC(f32 delta) {
    if (_c >= 1.0f)
        return;
    _0 += _8 * delta;
    f32 t = _0;
    if (t >= 1.0f) {
        _0 = 1.0f;
        _4 = 1.0f;
        _c = 1.0f;
        return;
    }
    if (!_11) {
        if (t < 0.5f) {
            t *= 2.0f;
            t = t * t * 0.5f;
        } else {
            t = (1.0f - t) * 2.0f;
            t = t * t * -0.5f + 1.0f;
        }
    }
    const f32 progress = 1.0f - (1.0f - t) / (1.0f - _4);
    _10 = true;
    _c = progress;
    _4 = t;
}

// NON_MATCHING: the original loads `_d8`, `_8` and `node->_28` once per node, before the loop over the elements.
void ASList::sub_710115E13C(sead::Heap* heap) {
    for (Unk6* node = _148; node; node = node->_30) {
        for (Element* element : node->_0)
            element->m5(_d8, _8, node->_18, heap, node->_28);
    }
}

// NON_MATCHING: the original ORs the results of the (bool) calls without normalising them (`orr w20, w20, w0`);
// we emit `and w, w0, #1` first.
void ASList::sub_710115C6F0() {
    if (!_b0)
        return;
    bool running = false;
    const s32 count = mSlots.size();
    if (count >= 1) {
        const f32 rate = *_d8->getParam()->getRes().mASList->getCommon().rate_all;
        for (s32 i = 0; i < count; ++i)
            running |= mSlots[i].sub_7101164CA4(rate);
    }
    if (!running && _b0)
        _b0->_21 = false;
}

void ASList::sub_710115C9AC(int slot) {
    mSlots[slot].sub_7101164900(_d8->getParam()->getRes().mModelList, slot, _d8);
}

void ASList::sub_710115C9E0(int slot) {
    _d8->getParam()->getRes().mModelList->isParticalEnable(slot);
    mSlots[slot].sub_7101164FF8();
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

// NON_MATCHING: normalized direction components remain in float registers instead of integer registers.
f32 ASList::sub_710115F8A0() {
    const ASList* list = _d8->getASList();
    const s8 index = list->_f0[0x15];
    const sead::Vector3f* normal_ptr = index >= 0 ? list->_e0[index]._vec3_ptr : nullptr;
    const sead::Vector3f& normal = normal_ptr ? *normal_ptr : sead::Vector3f::ey;
    const sead::Matrix34f& matrix = _d8->getMtx();
    sead::Vector3f direction(matrix.m[0][2], 0.0f, matrix.m[2][2]);
    direction.normalize();
    return sead::Mathf::rad2deg(
        sead::Mathf::atan2(normal.x * direction.x + direction.z * normal.z, normal.y));
}

// NON_MATCHING: normalized direction components remain in float registers instead of integer registers.
f32 ASList::sub_710115F98C() {
    const ASList* list = _d8->getASList();
    const s8 index = list->_f0[0x15];
    const sead::Vector3f* normal_ptr = index >= 0 ? list->_e0[index]._vec3_ptr : nullptr;
    const sead::Vector3f& normal = normal_ptr ? *normal_ptr : sead::Vector3f::ey;
    const sead::Matrix34f& matrix = _d8->getMtx();
    sead::Vector3f direction(matrix.m[0][2], 0.0f, matrix.m[2][2]);
    direction.normalize();
    return sead::Mathf::rad2deg(
        sead::Mathf::atan2(direction.z * normal.x - direction.x * normal.z, normal.y));
}

// NON_MATCHING: table selection and destination lookup are scheduled in a different order.
bool ASList::sub_710115EA64(int kind) {
    const s8 index = _f0[0x36];
    if (index < 0)
        return false;
    _e0[index]._str_ptr->copy(sUnk_710250FFE0[u32(kind) > 4 ? 0 : kind]);
    return true;
}

bool ASList::goLimpFromHeadShotMaybe(u32 kind, const sead::SafeString& value, u32 unused) {
    const s8 index = _f0[kind];
    if (index < 0)
        return false;
    _e0[index]._str_ptr->copy(sead::SafeString(value.cstr()));
    return true;
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

bool ASList::sub_710115EECC(int kind, s32 value, int a3) {
    if (value == std::numeric_limits<s32>::min())
        return false;
    const s8 index = _f0[kind];
    if (index < 0)
        return false;
    _e0[index]._s32 = value;
    return true;
}

// NON_MATCHING: switch lowering reorders the 0, 0x19 and 6 cases.
bool ASList::sub_710115EE14(int bit) {
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
        const s8 index = _f0[0x42];
        if (index < 0)
            return false;
        const u64* bits = _e0[index]._u64_ptr;
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

f32 ASList::sub_710115F3F0(int slot, int bank, bool a1) {
    if (auto* entry = getEntry(slot, bank))
        return entry->sub_7101163354(a1);
    return 0.0f;
}

bool ASList::sub_710115F0BC(int slot, int bank, f32 value) {
    if (auto* entry = getEntry(slot, bank))
        return entry->sub_7101162F7C(value);
    return false;
}

void ASList::sub_710115F10C(int slot, int bank) {
    if (auto* entry = getEntry(slot, bank))
        entry->sub_71011637D8();
}

void ASList::sub_710115F6F4(int key, int slot, int bank, f32 value) {
    if (auto* entry = getEntry(slot, bank))
        entry->sub_7101163AD4(value, key);
}

bool ASList::sub_710115F024(const sead::Vector3f& value, int a2) {
    const s8 index = _f0[0x15];
    if (index < 0)
        return false;
    sead::Vector3f* normal = _e0[index]._vec3_ptr;
    if (!normal)
        return false;
    *normal = value;
    return true;
}

const sead::Vector3f& ASList::sub_710115F078() {
    const s8 index = _f0[0x15];
    const sead::Vector3f* normal = index >= 0 ? _e0[index]._vec3_ptr : nullptr;
    return normal == nullptr ? sead::Vector3f::ey : *normal;
}

void ASList::sub_710115F5C0(f32 value, int slot, int bank) {
    Unk2* entry = getEntry(slot, bank);
    if (!entry)
        return;
    entry->sub_71011634C0(value);
    const s32 num_slots = mSlots.size();
    ++bank;
    for (; slot < num_slots; ++slot, bank = 0) {
        auto& entries = mSlots[slot]._20;
        const s32 num_banks = entries.size();
        for (; bank < num_banks; ++bank) {
            auto& other = entries[bank];
            if (other._48 == entry)
                other.sub_71011634C0(value);
        }
    }
}

void ASList::sub_710115F1D8(int slot, int bank, f32 value) {
    if (auto* entry = getEntry(slot, bank))
        entry->sub_7101161CF8(true, value);
}

void ASList::sub_710115F2EC(s32 slot, s32 bank, f32 value) {
    if (auto* entry = getEntry(slot, bank))
        entry->_10 = value;
    if (mSlots[slot].sub_7101164C24(_14))
        _163 &= ~1;
}

// NON_MATCHING: the BoneAccessKey output uses stack offset 0xc instead of 0x8.
f32 ASList::sub_710115CAFC(const sead::SafeString& bone_name) {
    const gsys::BoneAccessKey key = _8->searchBone(bone_name);
    const s32 num_slots = mSlots.size();
    for (s32 i = 0; i < num_slots; ++i) {
        if (mSlots[i].sub_7101164C24(key))
            return mSlots[i]._48;
    }
    return 0.0f;
}

bool ASList::sub_710115FBC8(int a1, Unk4* query,
                            bool (Unk2::*fn)(Unk4*, int, bool), bool a4) {
    const s32 num_slots = mSlots.size();
    for (s32 i = 0; i < num_slots; ++i) {
        auto& entries = mSlots[i]._20;
        const s32 num_banks = entries.size();
        for (s32 j = 0; j < num_banks; ++j) {
            if ((entries[j].*fn)(query, a1, a4))
                return true;
        }
    }
    return false;
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

bool ASList::sub_710115FB60(EventQueryResults* query, int a1, int slot, int bank,
                            bool (Unk2::*fn)(EventQueryResults*, int, bool), bool a6) {
    query->count = 0;
    if (auto* entry = getEntry(slot, bank))
        return (entry->*fn)(query, a1, a6);
    return false;
}

// Fallback getters of the float parameters (the actor's speed components; the controller's velocity is stored per
// frame (1/30 s) and is subtracted from / added to the actor's own velocity).
f32 ASList::sub_710115F740() {
    if (auto* cc = _d8->getCharacterController()) {
        sead::Vector3f velocity = sead::Vector3f::zero;
        if (cc->mFlags.isOn(0x100))
            cc->sub_7100F6353C(&velocity);
        const sead::Vector3f relative = _d8->getVelocity() - velocity * (1.0f / 30);
        return sead::Mathf::sqrt(relative.x * relative.x + relative.z * relative.z);
    }
    return sead::Mathf::sqrt(_d8->getVelocity().x * _d8->getVelocity().x + _d8->getVelocity().z * _d8->getVelocity().z);
}

f32 ASList::sub_710115F820() {
    if (auto* cc = _d8->getCharacterController()) {
        sead::Vector3f velocity = sead::Vector3f::zero;
        if (cc->mFlags.isOn(0x100))
            cc->sub_7100F6353C(&velocity);
        return (_d8->getVelocity() + velocity * (-1.0f / 30)).y;
    }
    return _d8->getVelocity().y;
}

f32 ASList::sub_710115FA78() {
    auto* chemical = _d8->sub_71011D8A34(0);
    if (!chemical)
        return 0.0f;
    const sead::Vector3f& vec = (chemical->_c & 0x1000000) ? sead::Vector3f::zero : chemical->_e4;
    return sead::Mathf::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// NON_MATCHING: register numbering (the original keeps the typeinfo static in x24 and the resource in x23) and the
// children loop uses a 64-bit zero-extended index / size compare (ours: 32-bit).
void ASList::sub_710115E218(u32* mask, const res::AS* as, u32 index) {
    for (;;) {
        const res::ASResource* resource = as->getElementResources()[index];
        auto* selector = sead::DynamicCast<const res::ASResourceWithChildren>(resource);
        if (index < 0x200)
            mask[index >> 5] |= 1u << (index & 0x1f);
        if (!selector)
            return;
        const s32 value = IntSelector::getValue(_d8, selector);
        const auto& children = selector->getChildren();
        const s32 count = children.size();
        if (value < 0) {
            if (count > 0) {
                sub_710115E218(mask, as, children[0]->getIndex());
                for (u32 i = 1; i < u32(count); ++i)
                    sub_710115E218(mask, as, children[i]->getIndex());
            }
            return;
        }
        index = children[value]->getIndex();
    }
}

s32 sub_710115E3A0(const u32* mask) {
    s32 count = 0;
    for (s32 i = 0; i < 16; ++i)
        count += sead::BitFlagUtil::countOnBit(mask[i]);
    return count;
}

}  // namespace ksys::as

// 0x710115f0b4 is the eight-byte size getter called on ASList's slot buffer.
// Emit the existing template method naturally; callers remain free to inline it.
template s32 sead::Buffer<ksys::as::ASList::Unk1>::size() const;
