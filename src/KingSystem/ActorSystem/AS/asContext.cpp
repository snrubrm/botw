#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"
#include "KingSystem/Resource/Actor/resResourceASList.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/System/VFR.h"

namespace ksys::as {

bool Context::sub_710125A924(const Context& other) {
    return mFrames[_f4 ? _f4 - 1 : 2].sub_71012580E0(
        other.mFrames[other._f4 ? other._f4 - 1 : 2]);
}

void BoneBlendState::sub_7101257884(const gsys::AnimationAccessKey<gsys::SkeletalAnmType>* key,
                                    Context::Record* record, bool partial, f32 frame) {
    if (mNumEntries >= 64)
        return;
    Entry& entry = mEntries[mNumEntries];
    ++mNumEntries;
    entry._0 = _10;
    entry.key = key;
    entry.record = record;
    entry.weight = weight * record->_4;
    entry.frame = frame;
    entry._24 = _18;
    entry._28 = _8;
    entry._30 = _28;
    entry.partial = partial;
    entry._3c = _20;
    if (_20 == 2) {
        entry._1c = _24;
        return;
    }
    entry._1c = entry.weight;
    if (_20 == 1)
        _24 = sead::Mathf::max(_24, entry.weight);
}

// NON_MATCHING: the separate mode/float stores are not combined with the pointer as a 64-bit pair.
void BoneBlendState::sub_7101257920(const res::ASSetting::BoneParams* params) {
    _20 = 1;
    _24 = 0.0f;
    _28 = params;
}

void BoneBlendState::sub_710125792C() {
    _20 = 0;
    _24 = 0.0f;
    _28 = nullptr;
}


f32 Context::sub_710125A9A8() {
    return VFR::instance()->getDeltaFrame() * _e0 * _e4 *
           *mList->_d8->getParam()->getRes().mASList->getCommon().rate_all;
}

// NON_MATCHING: the compiler saves the type before the weight instead of after it.
void Context::sub_7101259DE8(f32 weight, int type, const sead::SafeString& value) {
    if (u32(type) - 0x36 >= 0x22)
        return;
    for (s32 i = 0; i < mNumEvents2; ++i) {
        auto& event = mEvents2[i];
        if (event.mType == type && event.mName == value) {
            event._1c += weight;
            event.mName = value;
            return;
        }
    }
    if (mNumEvents2 >= mEvents2.size())
        return;
    auto& event = mEvents2[mNumEvents2];
    event.mType = type;
    event.mFlags = 1;
    event.mName = value;
    event._18 = 0.0f;
    event._1c = weight;
    ++mNumEvents2;
}

void Context::sub_7101259F94(f32 duration, f32 weight, int type,
                           const sead::SafeString& value) {
    if (u32(type) >= 0x36)
        return;
    for (s32 i = 0; i < mNumEvents2; ++i) {
        auto& event = mEvents2[i];
        if (event.mType == type && (event.mFlags & 8) && event.mName == value) {
            event.mFlags |= 0x10;
            event._18 = duration;
            event._1c += weight;
            event.mName = value;
            return;
        }
    }
    if (mNumEvents2 >= mEvents2.size())
        return;
    auto& event = mEvents2[mNumEvents2];
    event.mType = type;
    event.mFlags = 0x1a;
    event.mName = value;
    event._18 = duration;
    event._1c = weight;
    ++mNumEvents2;
}

// NON_MATCHING: compiler combines the range tests and return into conditional selects.
f32 sub_710125A978(f32 frame, f32 start, f32 end, bool hold) {
    if (frame < 0.0f || (hold && end < frame))
        return hold ? end + 0.01f : end;
    return frame;
}

void Context::sub_710125AAA0(u32 index, s16 value) {
    if (_f4 != _f5)
        return;
    for (s32 i = 0; i < _f9; ++i) {
        if (mPendingValues[i].index == index) {
            mPendingValues[i].value = value;
            return;
        }
    }
    if (_f9 >= mPendingValues.size()) {
        --_f9;
        for (s32 i = 0; i < _f9; ++i)
            mPendingValues[i] = mPendingValues[i + 1];
    }
    auto& pending = mPendingValues[_f9];
    pending.index = index;
    pending.value = value;
    ++_f9;
}

s32 Context::sub_710125AA38(u32 index) {
    if (_f4 != _f5)
        return -1;
    for (s32 i = 0; i < _f9; ++i) {
        if (mPendingValues[i].index == index)
            return mPendingValues[i].value;
    }
    return -1;
}

f32 Context::sub_710125A164(u32 key) {
    const s8 index = mList->_f0[key];
    return index >= 0 ? _930[index] : 0.0f;
}

void Context::sub_710125A1A4(f32 value, int key) {
    const s8 index = mList->_f0[key];
    if (index >= 0) {
        _928 |= 1u << index;
        _930[index] = value;
    }
}

void Context::sub_710125A1F0(f32 value, int key, Element* element,
                           const res::ASResource* resource) {
    const s8 index = mList->_f0[key];
    if (index >= 0) {
        const u32 mask = 1u << index;
        if (!(_928 & mask)) {
            _928 |= mask;
            _930[index] = value;
        }
        sub_710125A248(value, key, element, resource);
    }
}

void Context::sub_710125A248(f32 value, u32 key, Element* element,
                           const res::ASResource* resource) {
    const s8 index = mList->_f0[key];
    if (index < 0)
        return;
    const u32 mask = 1u << index;
    if (_924 & mask)
        return;
    _924 |= mask;
    f32* pending = &_930[index];
    const auto* blender_resource = static_cast<const res::ASBlenderResource*>(resource);
    if (!blender_resource || blender_resource->getInputLimit() < 0.0f) {
        *pending = value;
        return;
    }
    auto* blender = sead::DynamicCast<AngleBlender>(element);
    if (!blender) {
        sead::Mathf::chase(pending, value,
                          blender_resource->getInputLimit() *
                              VFR::instance()->getDeltaFrame());
        return;
    }
    const f32 period = blender->m41() - blender->m40();
    const f32 delta = value - *pending;
    if (delta > blender->m41()) {
        sead::Mathf::chase(pending, value - period,
                          blender_resource->getInputLimit() *
                              VFR::instance()->getDeltaFrame());
        if (*pending < blender->m40())
            *pending += period;
    } else if (delta < blender->m40()) {
        sead::Mathf::chase(pending, value + period,
                          blender_resource->getInputLimit() *
                              VFR::instance()->getDeltaFrame());
        if (*pending > blender->m41())
            *pending -= period;
    } else {
        sead::Mathf::chase(pending, value,
                          blender_resource->getInputLimit() *
                              VFR::instance()->getDeltaFrame());
    }
}

void Context::sub_710125A630() {
    if (!_928)
        return;
    const s32 size = _930.size();
    for (s32 i = 0; i < size; ++i) {
        const u32 mask = 1u << i;
        if ((_928 & mask) && !(_924 & mask))
            _928 &= ~mask;
    }
}

// NON_MATCHING: compiler branches directly on the bool instead of testing its inverted bit.
bool Context::sub_7101259990(bool a1) {
    if (_f4 != _f5)
        return false;
    if (!(mFlags & 0x20) && !a1) {
        if (!(mFlags & 4))
            return false;
    } else if (!(mFlags & 0x400)) {
        return true;
    }
    const s32 previous_bank = _f6 ^ 1;
    const s32 size = mBanksA[_f6].mCount;
    for (s32 i = 0; i < size; ++i) {
        const auto& current = mBanksA[_f6].mEvents[i];
        const s32 previous_size = mBanksA[previous_bank].mCount;
        for (s32 j = 0; j < previous_size; ++j) {
            const auto& previous = mBanksA[previous_bank].mEvents[j];
            if (current.mName == previous.mName &&
                (current._18 > 0.25f || previous._18 > 0.25f)) {
                return false;
            }
        }
    }
    return true;
}

// NON_MATCHING: event duration/value copies use separate stores and different registers.
bool Context::sub_710125A67C(const Context& other, bool reset_events) {
    if (!_d0->sub_71012580E0(*other._d0))
        return false;
    _f0 = other._f0;
    _e0 = other._e0;
    _e4 = other._e4;
    _f6 = other._f6;
    if (!reset_events) {
        for (s32 bank = 0; bank < 2; ++bank) {
            auto& dst = mBanksA[bank];
            const auto& src = other.mBanksA[bank];
            const s32 size = src.mCount;
            dst.mCount = size;
            for (s32 i = 0; i < size; ++i) {
                auto& dst_event = dst.mEvents[i];
                const auto& src_event = src.mEvents[i];
                dst_event.mDuration = src_event.mDuration;
                dst_event._4 = src_event._4;
                dst_event.mName = src_event.mName;
                dst_event._18 = src_event._18;
            }
        }
        for (s32 bank = 0; bank < 2; ++bank) {
            auto& dst = mBanksB[bank];
            const auto& src = other.mBanksB[bank];
            const s32 size = src.mCount;
            dst.mCount = size;
            for (s32 i = 0; i < size; ++i) {
                auto& dst_event = dst.mEvents[i];
                const auto& src_event = src.mEvents[i];
                dst_event.mDuration = src_event.mDuration;
                dst_event._4 = src_event._4;
                dst_event.mName = src_event.mName;
                dst_event._18 = src_event._18;
            }
        }
    }
    mFlags = other.mFlags;
    _924 = other._924;
    _928 = other._928;
    const s32 size = _930.size();
    for (s32 i = 0; i < size; ++i) {
        if (_928 & (1u << i))
            _930[i] = other._930[i];
    }
    if (reset_events) {
        mNumEvents2 = 0;
    } else {
        mNumEvents2 = other.mNumEvents2;
        for (s32 i = 0; i < mNumEvents2; ++i)
            mEvents2[i] = other.mEvents2[i];
    }
    return true;
}

res::ASResource* Context::sub_7101258CC0() {
    if (res::AS* as = _d0->mAS)
        return as->getFirstResource();
    return nullptr;
}

act::Actor* Context::sub_7101258ABC() {
    return mList->_d8;
}

ElementParams* Context::sub_7101258D4C(Record* record, bool a2) {
    return record->sub_7101257DF4(_d0, a2);
}

int Context::sub_7101258D1C(int index) {
    if (_921 & 2)
        return 0;
    return _d0->mIndexMap[index];
}

Context::Record* Context::sub_7101258CD4(int index) {
    Frame* frame = _d0;
    u8 record_index = 0;
    if (!(_921 & 2))
        record_index = frame->mIndexMap[index];
    return &frame->mRecords[record_index];
}

void Context::sub_7101258C1C() {
    _f4 = _f5;
    _d0 = _d8 ? _d8 : &mFrames[_f4];
}

// NON_MATCHING: the original decrements with a 32-bit `sub` and masks the stored byte afterwards (ours narrows to `add 0xff`)
void Context::sub_7101258C48() {
    _f4 = _f4 == 0 ? 2 : _f4 - 1;
    _d0 = &mFrames[_f4];
}

void Context::sub_7101258C80() {
    _f5 = _f5 + 1 == 3 ? 0 : _f5 + 1;
    _f4 = _f5;
    _d0 = _d8 ? _d8 : &mFrames[_f4];
}

int Context::sub_7101258E08() {
    return _d0->mRecords.size();
}

int Context::sub_7101258E14() {
    return _d0->mIndexMap.size();
}

int Context::sub_7101258E20() {
    return _d0->mEntries.size();
}

gsys::Model* Context::sub_7101258E2C() {
    return mList->_8;
}

void Context::sub_710125923C() {
    mUnk18 = sead::SafeString::cEmptyString;
    mUnk8 = sead::SafeString::cEmptyString;
}


void Context::sub_7101258D60(int element, int hint) {
    _d0->sub_710125848C(element, hint);
}

void Context::sub_7101258D68(int element) {
    _d0->sub_7101258570(element);
}

void Context::sub_7101258D70(int index) {
    Record* record = sub_7101258CD4(index);
    record->sub_7101257D90(_d0);
    _d0->mIndexMap[index] = 0xff;
}

// NON_MATCHING: only the compare of the `_930` size (`cmp #0; b.le` in the original, `cmp #1; b.lt` here)
bool Context::sub_7101258AC8(const Frame::Sizes& sizes, sead::Heap* heap) {
    mList = sizes.mList;
    if (!mFrames[0].sub_7101257F0C(sizes, heap) || !mFrames[1].sub_7101257F0C(sizes, heap) ||
        !mFrames[2].sub_7101257F0C(sizes, heap)) {
        return false;
    }
    if (sizes.mNum930 > 0) {
        const s32 size = sizes.mNum930 > 0x20 ? 0x20 : sizes.mNum930;
        if (!_930.tryAllocBuffer(size, heap))
            return false;
        _930.fill(0);
    }
    return true;
}

// NON_MATCHING: ours also stores `mEvents2[0].mFlags = 0` (the original stores the flags of events 1-31 only) and
// schedules zero initialization of the pending pairs differently; everything else is identical
Context::Context() : mFrames() {
    for (s32 i = 0; i < 2; ++i) {
        mBanksA[i].mCount = 0;
        mBanksB[i].mCount = 0;
    }
}

Context::~Context() {
    mFrames[0].finalize();
    mFrames[1].finalize();
    mFrames[2].finalize();
    _930.freeBuffer();
}

void Context::sub_7101259274(f32 a0, f32 duration, f32 a2, const sead::SafeString& name) {
    if (_f4 == _f5) {
        auto& bank = mBanksA[_f6];
        if (bank.mCount < 16) {
            auto& event = bank.mEvents[bank.mCount];
            event.mDuration = sead::Mathf::clampMin(duration, 1.0f);
            event._4 = a0;
            event.mName = name;
            ++bank.mCount;
            event._18 = a2;
        }
    }
}

void Context::sub_710125930C(f32 a0, f32 duration, const sead::SafeString& name, s32 a3) {
    if (_f4 == _f5) {
        auto& bank = mBanksB[_f6];
        if (bank.mCount < 16) {
            auto& event = bank.mEvents[bank.mCount];
            event.mDuration = sead::Mathf::clampMin(duration, 1.0f);
            event._4 = a0;
            event.mName = name;
            ++bank.mCount;
            event._18 = a3;
        }
    }
}

// 0x710250ff94 (GOT 0x25a2d80): a float constant of another TU (0.25f). Name is a guess.
extern const f32 sUnk_710250ff94;

// NON_MATCHING: only a zero-extension of the shift amount (`mov w15, w15`)
void Context::sub_7101259BD8() {
    for (s32 i = 0; i < mNumEvents2; ++i) {
        auto& event = mEvents2[i];
        const int type = event.mType - 12;
        if (u32(type) < 0x37 && ((1ull << type) & 0x60000000000001ull) && event._1c < sUnk_710250ff94)
            event.mFlags &= 0xffe8;
        if ((event.mFlags & 0x18) == 8)
            event.mFlags = (event.mFlags & 0xfff3) | 4;
    }
}

bool sub_7101259C78(Context* ctx, ASList::Unk4* query, int type, u16 mask, ASList::Unk2* entry) {
    for (s32 i = 0; i < ctx->mNumEvents2; ++i) {
        auto& event = ctx->mEvents2[i];
        if (event.mType == type && (event.mFlags & mask)) {
            if (query) {
                query->name = event.mName;
                query->_10 = event._18;
                query->_14 = event._1c;
            }
            return true;
        }
    }
    return false;
}

bool sub_7101259D04(Context* ctx, ASList::EventQueryResults* query, u32 type, u16 mask) {
    query->count = 0;
    for (s32 i = 0; i < ctx->mNumEvents2; ++i) {
        const auto& event = ctx->mEvents2[i];
        if (event.mType == type && (event.mFlags & mask) &&
            query->count < query->events.size()) {
            auto& result = query->events[query->count];
            result.name = event.mName;
            result._10 = event._18;
            result._14 = event._1c;
            ++query->count;
        }
    }
    return query->count > 0;
}


// NON_MATCHING: register allocation / block order of the event removal (the original keeps &mEvents2[i] pointers in
// different registers)
void Context::sub_71012590BC(bool a) {
    auto remove = [this](s32 i, Event2& event) {
        const s8 last_index = --mNumEvents2;
        if (i != last_index) {
            Event2& last = mEvents2[last_index];
            event.mFlags = last.mFlags;
            event.mType = last.mType;
            event.mName = last.mName;
            event._18 = last._18;
            event._1c = last._1c;
        }
    };
    if (mNumEvents2 < 1)
        return;
    if (!a) {
        for (s32 i = mNumEvents2 - 1; i >= 0; --i) {
            Event2& event = mEvents2[i];
            const u16 flags = event.mFlags;
            event._1c = 0;
            event.mFlags = flags & 0xffe8;
            if ((flags & 0xffe8) == 0)
                remove(i, event);
        }
    } else {
        for (s32 i = mNumEvents2 - 1; i >= 0; --i) {
            Event2& event = mEvents2[i];
            u16 flags = event.mFlags;
            event._1c = 0;
            if (flags & 2) {
                flags &= 0xffe7;
                event.mFlags = flags;
            }
            event.mFlags = flags & 0xffec;
            if ((flags & 0xffec) == 0)
                remove(i, event);
        }
    }
}

// NON_MATCHING: block layout of the `a5` / frame tests (same operations)
void Context::sub_7101258E38(f32 a0, const sead::SafeString& name, res::AS* as, Frame* frame, bool a4,
                             bool a5) {
    if (!a5) {
        mUnk18 = mUnk8;
        _fa = _f9;
    } else {
        mNumEvents2 = _f8;
        _f9 = _fa;
    }
    mUnk8 = name;
    _e0 = 1.0f;
    u8 index = _f5;
    mFlags = 0;
    _924 = 0;
    _e4 = a0;
    _d8 = frame;
    _f0 = -1.0f;
    _e8 = -1.0f;
    if (a5) {
        _f4 = index;
    } else {
        index = index + 1 == 3 ? 0 : index + 1;
        _f5 = index;
        _f4 = index;
    }
    if (!frame)
        frame = &mFrames[index];
    _d0 = frame;
    frame->sub_7101258398();
    _d0->mAS = as;
    if (a4)
        _f9 = 0;
}

// NON_MATCHING: register allocation (the original keeps `&mFlags` in a register)
void Context::sub_7101258F4C(u32 a, u32 b) {
    sub_71012590BC(a & 1);
    if (!(a & 1)) {
        const u32 old = mFlags;
        mFlags = 0;
        if (old & 0x40)
            mFlags = 0x40;
    } else {
        _f8 = mNumEvents2;
        const u32 had_40 = mFlags & 0x40;
        mFlags = 0x80;
        u32 flags = mFlags;
        if (!(mUnk18 == mUnk8)) {
            flags = mFlags | 0x100;
            mFlags = flags;
        }
        if (had_40)
            mFlags = flags | 0x40;
    }
    _924 = 0;
    _ec = 0;
    if (!(b & 1))
        _f6 ^= 1;
    mBanksA[_f6].mCount = 0;
    mBanksB[_f6].mCount = 0;
}

}  // namespace ksys::as
