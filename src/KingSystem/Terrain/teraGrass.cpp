#include "KingSystem/Terrain/teraGrass.h"
#include <math/seadMathCalcCommon.h>

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
