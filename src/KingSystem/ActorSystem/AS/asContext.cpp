#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"

namespace ksys::as {


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
// emits the stores to 0xd40 / 0xd48 in the other order; everything else is identical
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
