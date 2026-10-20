#include "KingSystem/Terrain/teraVegeTeraMat.h"
#include "KingSystem/Utils/Types.h"
#include <math/seadMathCalcCommon.h>

namespace ksys::tera {

// 0x7102615910 (.bss): the gate byte the two update helpers test.
KSYS_VISIBILITY_HIDDEN u8 sUnk_7102615910;

// 0x7101077bb8 / 0x7101077cfc / 0x7101077e30: the per-record helpers (declaration only).
void sub_7101077BB8(VegeTeraMat* record, u8 value);
void sub_7101077CFC(VegeTeraMat* record);
void sub_7101077E30(VegeTeraMat* record, void* arg, VegeTeraMatMgr::Item* item, void* data);

void VegeTeraMatMgr::setDirty() {
    mRecords[0]._0 |= 1;
    mRecords[1]._0 |= 1;
    mRecords[2]._0 |= 1;
}

void VegeTeraMatMgr::sub_710107869C(u8 value) {
    if (sUnk_7102615910)
        return;
    sub_7101077BB8(&mRecords[0], value);
    sub_7101077BB8(&mRecords[1], value);
    sub_7101077BB8(&mRecords[2], value);
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
    sub_7101077CFC(&mRecords[0]);
    sub_7101077CFC(&mRecords[1]);
    sub_7101077CFC(&mRecords[2]);
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

}  // namespace ksys::tera
