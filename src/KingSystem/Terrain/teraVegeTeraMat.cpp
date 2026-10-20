#include "KingSystem/Terrain/teraVegeTeraMat.h"
#include "KingSystem/Utils/Types.h"
#include <math/seadMathCalcCommon.h>

namespace ksys::tera {

// 0x7102615910 (.bss): the gate byte the two update helpers test.
KSYS_VISIBILITY_HIDDEN u8 sUnk_7102615910;

// 0x7101077e30: per-record rendering helper (declaration only).
void sub_7101077E30(VegeTeraMat* record, void* arg, VegeTeraMatMgr::Item* item, void* data);

void VegeTeraMatMgr::setDirty() {
    mRecords[0]._0 |= 1;
    mRecords[1]._0 |= 1;
    mRecords[2]._0 |= 1;
}

void VegeTeraMatMgr::sub_710107869C(u8 value) {
    if (sUnk_7102615910)
        return;
    mRecords[0].setBufferIndex(value);
    mRecords[1].setBufferIndex(value);
    mRecords[2].setBufferIndex(value);
}

// NON_MATCHING: the two reloads of the entry use the other one of the x8/x9 pair; the
// instruction sequence and call order match.
void VegeTeraMatMgr::sub_710107873C(void* arg) {
    if (!_fa0 || sUnk_7102615910)
        return;
    Item* item = getEntry()->mItem;
    if (!item)
        return;
    if ((~item->mFlags & 3) != 0)
        return;
    sub_7101077E30(&mRecords[0], arg, item, getEntry()->_10);
    sub_7101077E30(&mRecords[1], arg, item, getEntry()->_10);
    sub_7101077E30(&mRecords[2], arg, item, getEntry()->_10);
}

void VegeTeraMatMgr::sub_71010786F4() {
    if (sUnk_7102615910)
        return;
    mRecords[0].upload();
    mRecords[1].upload();
    mRecords[2].upload();
}

// NON_MATCHING: position snapping and bounds stores differ in scheduling.
void VegeTeraMat::updatePosition(const sead::Vector3f& position) {
    mDelta = mPosition;
    const f32 cell_size = mSize / static_cast<f32>(mDimension) * static_cast<f32>(mCellSize);
    mPosition.x = cell_size * sead::Mathf::floor(position.x / cell_size);
    const f32 z = cell_size * sead::Mathf::floor(position.z / cell_size);
    const f32 x_origin = mSize * sead::Mathf::floor(mPosition.x / mSize + 0.5f);
    const f32 z_origin = mSize * sead::Mathf::floor(z / mSize + 0.5f);
    mDelta.x = mPosition.x - mDelta.x;
    mBounds.setMin({mPosition.x - mSize * 0.5f, z - mSize * 0.5f});
    mDelta.y = z - mPosition.y;
    mOrigin.x = x_origin;
    mOrigin.y = z_origin;
    const f32 scale = 1.0f / mSize;
    mTransform.z = 0.5f - scale * x_origin;
    mTransform.w = 0.5f - scale * z_origin;
    mTransform.x = scale;
    mTransform.y = scale;
    mPosition.y = z;
    mBounds.setMax({mPosition.x + mSize * 0.5f, mSize * 0.5f + z});
}

void VegeTeraMat::setBufferIndex(u8 index) {
    for (auto& packet : mPackets)
        packet.block.setBufferIndexMaybe(index);
}

// NON_MATCHING: dirty packet iteration and vector uploads differ in scheduling.
void VegeTeraMat::upload() {
    for (auto& packet : mPackets) {
        if (!(packet.flags & 1))
            continue;
        packet.block.dcbz(0);
        packet.block.setData(0, &packet.data[0], 0, 1);
        packet.block.setData(0, &packet.data[1], 1, 1);
        packet.block.setData(0, &packet.data[2], 2, 1);
        packet.block.setData(0, &packet.data[3], 3, 1);
        packet.block.setData(0, &packet.data[4], 4, 1);
        packet.block.flushCPUCache();
    }
}

// NON_MATCHING: region lookup and scalar vector stores differ in scheduling.
void VegeTeraMat::UniformPacket::setRegion(f32 x0, f32 z0, f32 x1, f32 z1, f32 size,
                                          const RegionList& regions,
                                          const sead::Vector2f& position,
                                          const sead::Vector2f& origin, bool alternate) {
    const f32 half_size = size * 0.5f;
    const f32 lower_x = position.x - half_size;
    const f32 lower_z = position.y - half_size;
    const f32 upper_x = half_size + position.x;
    const f32 upper_z = half_size + position.y;
    x0 = x0 > lower_x ? x0 : lower_x;
    z0 = z0 > lower_z ? z0 : lower_z;
    x1 = x1 < upper_x ? x1 : upper_x;
    z1 = z1 < upper_z ? z1 : upper_z;
    const f32 width = x1 - x0;
    const f32 height = z1 - z0;
    if (width <= 0.0f || height <= 0.0f || regions.count == 0)
        return;
    const f32 inverse_size = 1.0f / size;
    for (s32 i = regions.count - 1; i != -1; --i) {
        if (!(regions.min[i].x < x0 && regions.min[i].y < z0 &&
              x1 < regions.max[i].x && z1 < regions.max[i].y))
            continue;
        const s8 region_index = i;
        if (region_index < 0)
            return;
        flags = alternate ? flags | 3 : (flags & ~3) | 1;
        const f32 inverse_x = regions.inverseSize[region_index].x;
        const f32 inverse_z = regions.inverseSize[region_index].y;
        const f32 center_x = (x0 + x1) * 0.5f - origin.x;
        const f32 center_z = (z0 + z1) * 0.5f - origin.y;
        const f32 scale_x = inverse_size * (width + width);
        const f32 scale_z = inverse_size * (height + height);
        data[0].set(width * inverse_x, height * inverse_z,
                    inverse_x * (x0 - regions.min[region_index].x),
                    inverse_z * (z0 - regions.min[region_index].y));
        const f32 x = inverse_size * (center_x + center_x);
        const f32 z = inverse_size * (center_z + center_z);
        const f32 left = x < 0.0f ? 0.0f : -2.0f;
        const f32 right = x < 0.0f ? 2.0f : 0.0f;
        const f32 bottom = z < 0.0f ? 0.0f : -2.0f;
        const f32 top = z < 0.0f ? 2.0f : 0.0f;
        data[1].set(scale_x, scale_z, x + left, -(z + bottom));
        data[2].set(scale_x, scale_z, x + right, -(z + bottom));
        data[3].set(scale_x, scale_z, x + left, -(z + top));
        data[4].set(scale_x, scale_z, x + right, -(z + top));
        index = region_index;
        return;
    }
}

}  // namespace ksys::tera
