#include "KingSystem/Terrain/teraGrass.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Terrain/teraAreaEnv.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Utils/Types.h"

// NON_MATCHING: record iteration, address copies and the pool-null guard differ.
f32 Unk_7102503a50::sub_7101069760(const sead::Vector2f* position) {
    for (const auto& record : mRecords) {
        const auto& cache = record.mNear.mCaches[record.mNear._0 == 0];
        const f32 dx = position->x - cache.mCenter.x;
        const f32 dz = position->y - cache.mCenter.z;
        if (sead::Mathf::abs(dx) < mNearRadius &&
            sead::Mathf::abs(dz) < mNearRadius) {
            const u32 x = u32((dx / mNearRadius * 0.5f + 0.5f) * cache.mDimension);
            const u32 y = u32((0.5f - dz / mNearRadius * 0.5f) * cache.mDimension);
            const u32 pixelIndex = x + y * cache.mDimension;
            const auto& address = record.mNear.mCaches[2].mAddress;
            // Native adds unscaled pixelIndex to byte offset before flushing two bytes.
            const agl::GPUMemAddrBase pixelAddress(address, pixelIndex);
            pixelAddress.flushCPUCache(2);
            // Actual CPU storage is sixteen-bit texels; getAddress retains its null guard.
            const u16 texel = static_cast<const u16*>(address.getAddress())[pixelIndex];
            return static_cast<f32>(texel & 0xff) / 255.0f;
        }
        if (sead::Mathf::abs(position->x - record.mFarBoundsCenter.x) < record.mFarRadius &&
            sead::Mathf::abs(position->y - record.mFarBoundsCenter.z) < record.mFarRadius) {
            f32 u = (position->x - record.mFar.mCenter.x) / record.mFarRadius * 0.5f + 0.5f;
            f32 v = (position->y - record.mFar.mCenter.z) / record.mFarRadius * 0.5f + 0.5f;
            if (u < 0.0f)
                u += 1.0f;
            if (u > 1.0f)
                u -= 1.0f;
            if (v < 0.0f)
                v += 1.0f;
            if (v > 1.0f)
                v -= 1.0f;
            const u32 x = u32(u * record.mFar.mDimension);
            const u32 y = u32(v * record.mFar.mDimension);
            const u32 pixelIndex = x + y * record.mFar.mDimension;
            // Same native discrepancy: unscaled flush offset, scaled CPU read.
            const agl::GPUMemAddrBase pixelAddress(record.mFar.mAddress, pixelIndex);
            pixelAddress.flushCPUCache(4);
            const u32 texel = static_cast<const u32*>(record.mFar.mAddress.getAddress())[pixelIndex];
            return static_cast<f32>(texel & 0xff) / 255.0f;
        }
    }
    return 1.0f;
}

// NON_MATCHING: record iteration, address copies and the pool-null guard differ.
f32 Unk_7102503a50::sub_71010699D0(const sead::Vector2f* position) {
    for (const auto& record : mRecords) {
        const auto& cache = record.mNear.mCaches[record.mNear._0 == 0];
        const f32 dx = position->x - cache.mCenter.x;
        const f32 dz = position->y - cache.mCenter.z;
        if (sead::Mathf::abs(dx) < mNearRadius &&
            sead::Mathf::abs(dz) < mNearRadius) {
            const u32 x = u32((dx / mNearRadius * 0.5f + 0.5f) * cache.mDimension);
            const u32 y = u32((0.5f - dz / mNearRadius * 0.5f) * cache.mDimension);
            const u32 pixelIndex = x + y * cache.mDimension;
            const auto& address = record.mNear.mCaches[2].mAddress;
            // Native adds unscaled pixelIndex to byte offset before flushing two bytes.
            const agl::GPUMemAddrBase pixelAddress(address, pixelIndex);
            pixelAddress.flushCPUCache(2);
            // Actual CPU storage is sixteen-bit texels; getAddress retains its null guard.
            const u16 texel = static_cast<const u16*>(address.getAddress())[pixelIndex];
            return static_cast<f32>(texel >> 8) / 255.0f;
        }
        if (sead::Mathf::abs(position->x - record.mFarBoundsCenter.x) < record.mFarRadius &&
            sead::Mathf::abs(position->y - record.mFarBoundsCenter.z) < record.mFarRadius) {
            f32 u = (position->x - record.mFar.mCenter.x) / record.mFarRadius * 0.5f + 0.5f;
            f32 v = (position->y - record.mFar.mCenter.z) / record.mFarRadius * 0.5f + 0.5f;
            if (u < 0.0f)
                u += 1.0f;
            if (u > 1.0f)
                u -= 1.0f;
            if (v < 0.0f)
                v += 1.0f;
            if (v > 1.0f)
                v -= 1.0f;
            const u32 x = u32(u * record.mFar.mDimension);
            const u32 y = u32(v * record.mFar.mDimension);
            const u32 pixelIndex = x + y * record.mFar.mDimension;
            // Same native discrepancy: unscaled flush offset, scaled CPU read.
            const agl::GPUMemAddrBase pixelAddress(record.mFar.mAddress, pixelIndex);
            pixelAddress.flushCPUCache(4);
            const u32 texel = static_cast<const u32*>(record.mFar.mAddress.getAddress())[pixelIndex];
            return static_cast<f32>((texel >> 8) & 0xff) / 255.0f;
        }
    }
    return 1.0f;
}

// NON_MATCHING: address-copy scheduling and the pool-null guard differ.
f32 Unk_7102503a50::sub_7101069C44(const sead::Vector2f* position) {
    for (const auto& record : mRecords) {
        if (sead::Mathf::abs(position->x - record.mFarBoundsCenter.x) < record.mFarRadius &&
            sead::Mathf::abs(position->y - record.mFarBoundsCenter.z) < record.mFarRadius) {
            f32 u = (position->x - record.mFar.mCenter.x) / record.mFarRadius * 0.5f + 0.5f;
            f32 v = (position->y - record.mFar.mCenter.z) / record.mFarRadius * 0.5f + 0.5f;
            if (u < 0.0f)
                u += 1.0f;
            if (u > 1.0f)
                u -= 1.0f;
            if (v < 0.0f)
                v += 1.0f;
            if (v > 1.0f)
                v -= 1.0f;
            const u32 x = u32(u * record.mFar.mDimension);
            const u32 y = u32(v * record.mFar.mDimension);
            const u32 pixelIndex = x + y * record.mFar.mDimension;
            // The native flush uses the unscaled pixel index as a byte offset.
            const agl::GPUMemAddrBase pixelAddress(record.mFar.mAddress, pixelIndex);
            pixelAddress.flushCPUCache(4);
            const u32 texel = static_cast<const u32*>(record.mFar.mAddress.getAddress())[pixelIndex];
            return static_cast<f32>((texel >> 16) & 0xff) / 255.0f;
        }
    }
    return 1.0f;
}

// NON_MATCHING: register allocation in the volume loop differs.
u32 Unk_7102503a50::sub_7101069DB8(const sead::Vector2f* position, f32 radius) {
    for (const auto& record : mRecords) {
        const f32 limit = record.mFarRadius - radius;
        if (!(sead::Mathf::abs(position->x - record.mFarBoundsCenter.x) < limit &&
              sead::Mathf::abs(position->y - record.mFarBoundsCenter.z) < limit))
            return 0;
    }
    return 1;
}

void Unk_7102503a50::EventPool::sub_71010642AC(s32 count, sead::Heap* heap) {
    mEvents.tryAllocBuffer(count, heap);
    mFreeEvents.allocBuffer(count, heap);
    mActiveEvents.allocBuffer(count, heap);
    mRetiredEvents.allocBuffer(count, heap);
    for (s32 i = 0; i < count; ++i)
        mFreeEvents.pushBack(&mEvents[i]);
}

// NON_MATCHING: scan and count reloads differ; the restart after erasure is preserved.
void Unk_7102503a50::EventPool::process(Unk_7102503ac0* callback) {
    mCriticalSection.lock();
    for (auto& event : mActiveEvents)
        callback->update(&event);

    s32 index = 0;
    while (index < mActiveEvents.size()) {
        Event* event = mActiveEvents(index);
        if (callback->shouldRetire(event)) {
            mRetiredEvents.pushBack(event);
            mActiveEvents.erase(index);
            index = 0;
        } else if (callback->shouldDiscard(event)) {
            mFreeEvents.pushBack(event);
            mActiveEvents.erase(index);
            index = 0;
        } else {
            ++index;
        }
    }
    mCriticalSection.unlock();
}

void Unk_7102503ac0::update(Unk_7102503a50::Event* event) {
    ++event->mAge;
}

bool Unk_7102503ac0::shouldRetire(Unk_7102503a50::Event* event) {
    return (mCenter - event->mPosition).length() + event->mRadius < 256.0f;
}

bool Unk_7102503ac0::shouldDiscard(Unk_7102503a50::Event* event) {
    return (mCenter - event->mPosition).length() > 512.0f;
}

bool Unk_7102503a50::sub_710106A2C4() {
    for (const auto& record : mRecords) {
        if (record.mEventPool.mFreeEvents.size() < 128)
            return true;
    }
    return false;
}

// 0x7102615910 (placeholder name): the byte flag read and written through sub_7101076A98 by
// S7EventFlow::play / setup_1_1. It is defined in teraVegeTeraMat.cpp in the terrain namespace.
namespace ksys::tera {
KSYS_VISIBILITY_HIDDEN extern u8 sUnk_7102615910;
}

// 0x7101076a98 (placeholder name): address of the flag above.
u8* sub_7101076A98() {
    return &ksys::tera::sUnk_7102615910;
}

// The attribute limits read by the sampler 0x71010723c8 (0x7102503cf0). Only +0x10 (0.4) and
// +0x14 (0.3) are used here; the four leading values belong to the same static record.
namespace {
struct AttributeLimits {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _c;
    f32 mMax;
    f32 mMin;
};
AttributeLimits sAttributeLimits = {1.0f, 1.0f, -0.0672f, 0.277f, 0.4f, 0.3f};
}  // namespace

// NON_MATCHING: the cell index divisions are scheduled after the x floor correction in the original;
// ours hoists the z division and keeps one more float value live (frame 0x80 instead of 0x70).
f32 ksys::tera::Core::Grass::EntryPart::sub_71010723C8(s32 type, const Cell* cell, s32 index, u32* out) {
    ksys::tera::AreaEnvGetter* getter = ksys::tera::Terrain::instance()->sub_710114DE4C()->_38;
    if ((cell->mFlags & 3) != 1)
        return 0.0f;
    const Record* rec = cell->mRecord;
    f32 low = 0.0f;
    f32 high = 0.0f;
    f32 weight = 1.0f;
    f32 t = 0.0f;
    u32 value = 0;
    s32 t_index = 0;
    u32 override = 0;
    bool t_from_record = true;

    switch (type) {
    case 0:
    case 1: {
        if ((cell->mFlags & 0x420) == 0x20)
            return 0.0f;
        if ((cell->mFlags & 0x1c0) != 0 && (cell->mFlags & 0x2000000) == 0)
            return 0.0f;
        const s32 attr_index = rec->_35;
        if (attr_index == -1)
            return 0.0f;
        if (rec->_18 < 2)
            return 0.0f;
        ksys::tera::AreaEnvEntry0* entry = getter->sub_710107C9C4(attr_index);
        if (!entry)
            return 0.0f;
        if (type == 0) {
            if (f32(rec->_a) / 255.0f > 0.5f)
                return 0.0f;
            if (f32(rec->_3e) / 255.0f > 0.5f)
                return 0.0f;
        }
        if ((cell->mFlags & 0x200) != 0 || (cell->mFlags & 0x420) == 0x420) {
            if (type == 1) {
                low = entry->_1c8;
                high = entry->_1e8;
                value = entry->_208;
                t_index = s32(entry->_228);
                override = entry->_248;
            } else {
                const ksys::tera::AreaEnvAttribute* attr = entry->mAttributes1[index < 3 ? index : 0];
                low = attr->_98;
                high = attr->_b8;
                value = attr->_d8;
                t_index = s32(attr->_f8);
                override = attr->_118;
            }
            weight = f32(rec->_25) / 255.0f;
            if (weight <= 0.0f)
                return 0.0f;
        } else {
            const u16 mask = rec->_12 & rec->_14;
            if (type == 1) {
                if ((~mask & 0xffff) == 0)
                    return 0.0f;
                const f32 v = f32(rec->_24) / 255.0f;
                const s32 count = sead::BitFlagUtil::countOnBit(mask);
                const f32 a = v * (f32(count) * -0.0625f + 1.0f);
                high = sead::Mathf::min(sAttributeLimits.mMax, a);
                low = sead::Mathf::min(sAttributeLimits.mMin, high);
            } else {
                if (sead::BitFlagUtil::countOnBit(mask) < 8)
                    return 0.0f;
                const ksys::tera::AreaEnvAttribute* attr = entry->mAttributes0[index < 3 ? index : 0];
                low = attr->_98;
                high = attr->_b8;
                value = attr->_d8;
                t_index = s32(attr->_f8);
                override = attr->_118;
            }
        }
        break;
    }
    case 2: {
        ksys::tera::AreaEnvEntry1* entry = getter->sub_710107C9F4(rec->_36);
        if (!entry)
            return 0.0f;
        low = entry->_250;
        high = entry->_270;
        value = entry->_290;
        t_index = s32(entry->_2b0);
        override = entry->_2d0;
        weight = f32(rec->_26) / 255.0f;
        if (weight <= 0.0f)
            return 0.0f;
        break;
    }
    case 3: {
        const f32 v = f32(rec->_3e) / 255.0f;
        bool flag;
        if ((cell->mFlags & 0x220) == 0)
            flag = true;
        else
            flag = (cell->mFlags & 0x1c0) != 0 && (cell->mFlags & 0x2000000) == 0;
        if (v <= 0.5f) {
            if (flag)
                return 0.0f;
        } else if (flag && rec->_12 == -1) {
            return 0.0f;
        }
        if (rec->_19 != 0)
            return 0.0f;
        ksys::tera::AreaEnvEntry2* entry = getter->sub_710107CA24(rec->_37);
        if (!entry)
            return 0.0f;
        low = entry->_1e8;
        high = entry->_208;
        value = entry->_228;
        t_index = s32(entry->_248);
        override = entry->_268;
        if (v <= 0.5f) {
            weight = f32(rec->_27) / 255.0f;
            if (weight <= 0.0f)
                return 0.0f;
        }
        break;
    }
    case 4: {
        const f32 a = (rec->_7 & 0xfe) == 6 ? 1.0f : 0.0f;
        const f32 b = (rec->_8 & 0xfe) == 6 ? 1.0f : 0.0f;
        const f32 c = f32(rec->_9) / 255.0f;
        const f32 mix = a + (b - a) * c;
        const f32 d = sead::Mathf::clamp((f32(rec->_18) - 5.0f) / 10.0f, 0.0f, 1.0f);
        const f32 base = rec->_34 == 0x3e || rec->_34 == 0x1c ? 1.0f : 0.0f;
        low = 0.0f;
        high = base * mix * sead::Mathf::max(1.0f - d, 0.1f);
        break;
    }
    case 5: {
        const f32 a = rec->_8 == 0x52 ? 1.0f : 0.0f;
        const f32 b = rec->_7 == 0x52 || rec->_8 == 0x52 ? 1.0f : f32(rec->_3b) / 255.0f;
        const f32 c = f32(rec->_9) / 255.0f;
        const f32 d = rec->_7 == 0x52 ? 1.0f : 0.0f;
        const f32 mix = d + (a - d) * c;
        low = 0.0f;
        high = rec->_18 < 2 ? 0.0f : mix * 0.25f;
        t = b;
        t_from_record = false;
        break;
    }
    default:
        low = 0.0f;
        high = 1.0f;
        weight = 1.0f;
        break;
    }

    if (t_from_record) {
        t = f32(rec->_38[t_index]) / 255.0f;
        if ((override & 1) != 0 && (cell->mFlags & 0x1800) != 0) {
            t = 1.0f;
            value = 0;
        }
    }

    t = t * _38450 - _3844c;
    if (t < 0.0f)
        t = 0.0f;
    else if (t > 1.0f)
        t = 1.0f;

    if (out)
        *out = value;
    return weight * (low + (high - low) * t);
}

// NON_MATCHING: the shared cell index helper is scheduled differently (the z division is hoisted).
f32 ksys::tera::Core::Grass::EntryPart::sub_7101074D40(const sead::Vector2f& pos, s32* out_kind,
                                           u32* out_value) {
    mCS.lock();
    f32 best = 0.0f;
    Cell* cell = getCellMaybe(pos);
    if (cell) {
        const Record* rec = cell->mRecord;
        const s32 attr_index = rec->_35;
        if (attr_index >= 0) {
            for (u32 i = 0; i < 3; ++i) {
                u32 value = 0;
                const f32 weight = sub_71010723C8(0, cell, s32(i), &value);
                if (weight > best) {
                    ksys::tera::AreaEnvGetter* getter = ksys::tera::Terrain::instance()->sub_710114DE4C()->_38;
                    const ksys::tera::AreaEnvEntry0* entry = getter->sub_710107C9C4(attr_index);
                    const s32 index = entry->mAttributes0[i]->mIndices[0];
                    if (index != -1) {
                        *out_kind = s32(i);
                        *out_value = u32(getter->mData->mAttributes[i]->mIndices[index]);
                        best = weight;
                    }
                }
            }
        }
    }
    mCS.unlock();
    return best;
}

// NON_MATCHING: the shared cell index helper is scheduled differently (the z division is hoisted).
s32 ksys::tera::Core::Grass::EntryPart::sub_7101075038(const sead::Vector2f& pos, f32* out) {
    mCS.lock();
    s32 result = -1;
    Cell* cell = getCellMaybe(pos);
    if (cell) {
        const Record* rec = cell->mRecord;
        const s32 type = rec->_37;
        if (out)
            *out = sub_71010723C8(3, cell, 0, nullptr);
        result = type - 1;
    }
    mCS.unlock();
    return result;
}
