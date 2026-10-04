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

u8 Context::sub_7101258D1C(int index) {
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

}  // namespace ksys::as
