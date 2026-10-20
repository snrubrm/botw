#include "KingSystem/Terrain/teraVegeTeraMat.h"
#include "KingSystem/Utils/Types.h"
#include <math/seadMathCalcCommon.h>
#include <g3d/aglTextureUtilG3D.h>
#include <cstring>
#include <gsys/gsysModelScene.h>
#include "Game/gameGraphics.h"

namespace ksys::tera {

// 0x7102615910 (.bss): the gate byte the two update helpers test.
KSYS_VISIBILITY_HIDDEN u8 sUnk_7102615910;


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

void VegeTeraMatMgr::sub_710107873C(agl::DrawContext* context) {
    if (!_fa0 || sUnk_7102615910)
        return;
    Item* item = getEntry()->collector;
    if (!item)
        return;
    if ((~item->_0[0]._20._0 & 3) != 0)
        return;
    mRecords[0].draw(context, *item, getEntry()->block);
    mRecords[1].draw(context, *item, getEntry()->block);
    mRecords[2].draw(context, *item, getEntry()->block);
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

// Inline-only in the original; native 1077330 constructs every 3b8-byte
// texture entry and clears its resource image both before and after target construction.
inline VegeTeraMat::Texture::Texture() : mResTexture{}, mImageSize(0) {
    std::memset(&mResTexture, 0, sizeof(mResTexture));
}

// NON_MATCHING: TextureData destruction stays out of line instead of inlining its driver destructor.
VegeTeraMat::Texture::~Texture() {
    if (mTextureData) {
        delete mTextureData;
        mTextureData = nullptr;
    }
    if (mAddress.isValid())
        mAddress.deleteGPUMemBlock();
    mImageSize = 0;
}

// NON_MATCHING: GPU address copies and texture-state writes differ in scheduling.
void VegeTeraMat::Texture::initialize(u32 dimension, agl::TextureFormat format, sead::Heap* heap) {
    mTextureData = new (heap, 8) agl::TextureData;
    mTextureData->initialize_(agl::TextureType::cTextureType_2D, format, dimension, dimension,
                             1, 1, agl::TextureAttribute{}, agl::MultiSampleType{}, true);
    mImageSize = mTextureData->getImageByteSize();
    const u32 alignment = mTextureData->getImageAlignment();
    auto* memory = new (heap, 8) agl::GPUMemBlock<u8>;
    memory->allocBuffer_(mImageSize, heap, alignment, agl::MemoryAttribute::Default);
    mAddress = agl::GPUMemVoidAddr(agl::GPUMemAddrBase(*memory, 0));
    if (!mAddress.isValid())
        return;
    mTextureData->setImagePtr(mAddress, 0);
    mAddress.flushCPUCache(mImageSize);
    agl::g3d::TextureUtilG3D::convertToResTexture(&mResTexture, *mTextureData, nullptr);
    mSampler.applyTextureData(*mTextureData);
    mSampler.setFilter(1, 1, 1);
    mSampler.setWrap(1, 1, 1);
    mRenderTarget.applyTextureData(*mTextureData, mRenderTarget.getMipLevel(),
                                  mRenderTarget.getLayer());
}

void VegeTeraMat::initialize(f32 size, u32 dimension, u32 cell_size, s32 num_textures,
                             sead::Heap* heap) {
    mTextures.tryAllocBuffer(num_textures, heap, 8);
    mSize = size;
    mDimension = dimension;
    mCellSize = cell_size;
    _524 = (static_cast<f32>(cell_size) * size) / static_cast<f32>(dimension);
    mRenderBuffer.setRenderTargetColorNullAll();
    mRenderBuffer.setRenderTargetDepth(nullptr);
    mRenderBuffer.setVirtualSize(sead::Vector2f(dimension, dimension));
    mRenderBuffer.setPhysicalArea(0.0f, 0.0f, f32(dimension), f32(dimension));
    mViewport.setByFrameBuffer(mRenderBuffer);
    mPackets[0].block.startDeclare(1, heap);
    mPackets[0].block.declare_(static_cast<agl::UniformBlock::Type>(6), 5, 0, 1);
    mPackets[0].block.create(heap, 2, 1);
    for (s32 i = 1; i < 5; ++i) {
        mPackets[i].block.declare(mPackets[0].block);
        mPackets[i].block.create(heap, 2, 1);
    }
}

void VegeTeraMatMgr::initialize(sead::Heap* heap) {
    mRecords[0].initialize(48.0f, 128, 8, 2, heap);
    auto& near0 = mRecords[0].mTextures[0];
    near0.initialize(mRecords[0].mDimension, agl::TextureFormat::cTextureFormat_R16_G16_B16_A16_uNorm, heap);
    mRecords[0].mRenderBuffer.setRenderTargetColor(&near0.mRenderTarget, 0);
    auto& near1 = mRecords[0].mTextures[1];
    near1.initialize(mRecords[0].mDimension, agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm, heap);
    mRecords[0].mRenderBuffer.setRenderTargetColor(&near1.mRenderTarget, 1);
    mRecords[1].initialize(160.0f, 160, 8, 2, heap);
    auto& middle0 = mRecords[1].mTextures[0];
    middle0.initialize(mRecords[1].mDimension, agl::TextureFormat::cTextureFormat_R16_G16_B16_A16_uNorm, heap);
    mRecords[1].mRenderBuffer.setRenderTargetColor(&middle0.mRenderTarget, 0);
    auto& middle1 = mRecords[1].mTextures[1];
    middle1.initialize(mRecords[1].mDimension, agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm, heap);
    mRecords[1].mRenderBuffer.setRenderTargetColor(&middle1.mRenderTarget, 1);
    mRecords[2].initialize(660.0f, 192, 8, 2, heap);
    auto& far0 = mRecords[2].mTextures[0];
    far0.initialize(mRecords[2].mDimension, agl::TextureFormat::cTextureFormat_R16_G16_B16_A16_uNorm, heap);
    mRecords[2].mRenderBuffer.setRenderTargetColor(&far0.mRenderTarget, 0);
    auto& far1 = mRecords[2].mTextures[1];
    far1.initialize(mRecords[2].mDimension, agl::TextureFormat::cTextureFormat_R8_G8_B8_A8_uNorm, heap);
    mRecords[2].mRenderBuffer.setRenderTargetColor(&far1.mRenderTarget, 1);
}

// NON_MATCHING: bounded region scanning, strip updates and ring iteration differ in scheduling.
void VegeTeraMat::updateRegions(const RegionList& regions) {
    if (mDelta.x != 0.0f || mDelta.y != 0.0f) {
        mUpdateIndex = 0;
        _52c = -1;
    }
    for (auto& packet : mPackets)
        packet.flags &= ~1;
    const f32 delta_x = mDelta.x > 0.0f ? mDelta.x : -mDelta.x;
    const f32 delta_z = mDelta.y > 0.0f ? mDelta.y : -mDelta.y;
    if (!(_0 & 1) && !(delta_x > _524 + _524) && !(delta_z > _524 + _524)) {
        const f32 rain = Graphics::instance()->mModelScenes[0]->mRainRatio;
        if (mDelta.x != 0.0f) {
            const f32 x = mDelta.x > 0.0f ? mBounds.getMax().x - mDelta.x : mBounds.getMin().x;
            mPackets[0].setRegion(x, mBounds.getMin().y, x + delta_x,
                                  mBounds.getMin().y + mSize, mSize, regions,
                                  mPosition, mOrigin, false);
        }
        if (mDelta.y != 0.0f) {
            const f32 z = mDelta.y > 0.0f ? mBounds.getMax().y - mDelta.y : mBounds.getMin().y;
            const f32 width = mDelta.y > 0.0f ? mDelta.y : -mDelta.y;
            mPackets[1].setRegion(mBounds.getMin().x, z, mBounds.getMin().x + mSize,
                                  z + width, mSize, regions, mPosition, mOrigin, false);
        }
        if (!(rain > 0.0f) || mDelta.x != 0.0f || mDelta.y != 0.0f)
            return;
        const s32 dimension = mDimension / (mCellSize * 2);
        s32 remaining = mUpdateIndex;
        for (s32 ring = 1; ring <= dimension / 2; ++ring) {
            const s32 count = ring * 2 - 1;
            if (remaining >= count) {
                remaining -= count;
                continue;
            }
            const s32 offset = remaining - (ring - 1);
            for (s32 i = 0; i < 4; ++i) {
                s32 x;
                s32 z;
                switch (i) {
                case 1:
                    x = -ring;
                    z = -offset;
                    break;
                case 2:
                    x = ~offset;
                    z = -ring;
                    break;
                case 3:
                    x = ring - 1;
                    z = offset - 1;
                    break;
                default:
                    x = offset;
                    z = ring - 1;
                    break;
                }
                const f32 size = (mSize * static_cast<f32>(mCellSize * 2)) /
                                 static_cast<f32>(mDimension);
                const f32 x0 = mPosition.x + static_cast<f32>(x) * size;
                const f32 z0 = mPosition.y + static_cast<f32>(z) * size;
                mPackets[i].setRegion(x0, z0, size + x0, size + z0, mSize, regions,
                                      mPosition, mOrigin, true);
            }
            ++mUpdateIndex;
            return;
        }
        mUpdateIndex = 0;
        return;
    }
    for (s32 i = regions.count - 1; i != -1; --i) {
        if (!(regions.min[i].x < mBounds.getMin().x &&
              regions.min[i].y < mBounds.getMin().y &&
              mBounds.getMax().x < regions.max[i].x &&
              mBounds.getMax().y < regions.max[i].y))
            continue;
        const s8 first = i;
        if (first < 0 || first >= regions.count)
            break;
        for (s32 j = 0; j < 5 && first + j < regions.count; ++j) {
            const s32 index = first + j;
            const f32 x0 = _524 * sead::Mathf::floor((regions.min[index].x + 1.0f) / _524 + 1.0f);
            const f32 z0 = _524 * sead::Mathf::floor((regions.min[index].y + 1.0f) / _524 + 1.0f);
            const f32 x1 = _524 * sead::Mathf::floor((regions.max[index].x - 1.0f) / _524 + 0.0f);
            const f32 z1 = _524 * sead::Mathf::floor((regions.max[index].y - 1.0f) / _524 + 0.0f);
            mPackets[j].setRegion(x0, z0, x1, z1, mSize, regions, mPosition, mOrigin, false);
        }
        break;
    }
    _0 &= ~1;
}


// Original BSS state read and written by10784E0 across the three material updates.
KSYS_VISIBILITY_HIDDEN s32 sUnk_7102615914;

// NON_MATCHING: position updates inline here; patcher traversal and table construction also differ.
void VegeTeraMatMgr::update(s32 index, GrassEntry* entry) {
    _f9c = index;
    _fa0 = entry->mSystem;
    if (sUnk_7102615910)
        return;
    for (auto it = _fa0->mPatchers.begin(); it != _fa0->mPatchers.end(); ++it)
        setDirty();
    const auto* collector = getEntry()->collector;
    const s32 count = collector->_2942;
    VegeTeraMat::RegionList regions;
    regions.count = count;
    const auto* positions = collector->_0[0]._0;
    for (s32 i = 0; i < 16; ++i) {
        const f32 half_size = positions[i]._18 * 0.5f;
        regions.min[i].set(positions[i].pos.x - half_size, positions[i].pos.y - half_size);
        regions.max[i].set(positions[i].pos.x + half_size, half_size + positions[i].pos.y);
        regions.inverseSize[i].set(1.0f / (regions.max[i].x - regions.min[i].x),
                                   1.0f / (regions.max[i].y - regions.min[i].y));
    }
    if (sUnk_7102615914 < 0)
        sUnk_7102615914 = count;
    mRecords[0].updatePosition(entry->mPosition);
    mRecords[0].updateRegions(regions);
    mRecords[1].updatePosition(entry->mPosition);
    mRecords[1].updateRegions(regions);
    mRecords[2].updatePosition(entry->mPosition);
    mRecords[2].updateRegions(regions);
    sUnk_7102615914 = count;
}

}  // namespace ksys::tera
