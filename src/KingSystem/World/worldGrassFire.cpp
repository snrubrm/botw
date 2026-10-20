#include "KingSystem/World/worldGrassFire.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Terrain/teraVegeTeraMat.h"
#include "Game/gameStatisticsMgr.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <cstring>
#include <algorithm>
#include <limits>

namespace ksys::world {

// Mutable shader coefficients read by 12E6814; original initialized data.
KSYS_VISIBILITY_HIDDEN f32 sUnk_710251CF10 = 0.3f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710251CF14 = 0.4f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710251CF18 = 0.22f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710251CF1C = 0.215f;

// Constructor 0x71012e1d5c computes these four mutable distance coefficients.
KSYS_VISIBILITY_HIDDEN f32 sUnk_710251CF30 = 0.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710251CF34 = 0.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710251CF38 = 0.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710251CF3C = 0.0f;

Unk_710251cea8::~Unk_710251cea8() {
    _50.freeBuffer();
}

// NON_MATCHING: bounded cell iteration and floor arithmetic differ in scheduling.
void Unk_710251cea8::sub_71012E7990(f32 diameter, f32,
                                          const sead::Vector2f* position) {
    sead::ScopedLock<sead::CriticalSection> lock(&_10);
    f32 radius = diameter * 0.5f;
    if (radius > 10.0f)
        radius = 10.0f;
    const s32 min_x = sead::Mathi::max(29 - mGridPosition.x +
        sead::Mathf::floor((position->x - radius) / 10.0f), 0);
    const s32 min_y = sead::Mathi::max(29 - mGridPosition.y +
        sead::Mathf::floor((position->y - radius) / 10.0f), 0);
    const s32 max_x = sead::Mathi::min(29 - mGridPosition.x +
        sead::Mathf::floor((position->x + radius) / 10.0f), 58);
    const s32 max_y = sead::Mathi::min(29 - mGridPosition.y +
        sead::Mathf::floor((position->y + radius) / 10.0f), 58);
    for (s32 y = min_y; y <= max_y; ++y) {
        for (s32 x = min_x; x <= max_x; ++x) {
            auto& cell = mCells[(y + mCellIndices.y) % 59][(x + mCellIndices.x) % 59];
            if (cell.mFlags & 1)
                cell.mFlags |= 8;
        }
    }
}


// NON_MATCHING: record clearing and two-dimensional loops differ in store grouping and unrolling.
void Unk_710251cea8::resetCells() {
    sead::ScopedLock<sead::CriticalSection> lock(&_10);
    mCellSortLists[0].count = 0;
    mCellSortLists[1].count = 0;
    for (auto& row : mCells) {
        for (auto& cell : row) {
            auto& record = *cell.mRecord;
            cell._14 = 0;
            cell.mFlags = 0;
            cell._11[0] = 0;
            cell._11[1] = 0;
            cell._11[2] = 0;
            cell._16 = 0xff;
            record._0 = 0;
            std::memset(record._4, 0, sizeof(record._4));
            record._1a = 0;
            record._18 = 0;
            std::memset(record._14, 0, sizeof(record._14));
            std::memset(record._1c, 0, sizeof(record._1c));
            cell.mRecord->_4[0] = 0;
            cell.mRecord->_4[4] = 0;
            cell.mRecord->_4[8] = 0;
            cell.mRecord->_4[12] = 0;
            cell.mRecord->_3f = 0;
            cell.mRecord->_3c = 0;
            cell.mRecord->_3d = 0;
            cell.mRecord->_3e = 0;
        }
    }
    for (auto& row : mCellStates) {
        for (auto& state : row) {
            state._0 = 0;
            state._2 = 0;
        }
    }
    _4fdc4 = -1;
}

// NON_MATCHING: record pointer assignment, buffer allocation and declaration loops differ in scheduling.
void Unk_710251cea8::initialize(sead::Heap* heap, tera::GrassEntry* entry) {
    _8 = entry;
    for (s32 y = 0; y < 59; ++y)
        for (s32 x = 0; x < 59; ++x)
            mCells[y][x].mRecord = &mRecords[y][x];
    resetCells();
    _50.tryAllocBuffer(0x300, heap);
    const s32 count = _50.size();
    for (s32 i = 0; i < count; ++i) {
        auto& block = _50[i];
        if (i == 0) {
            block.startDeclare(1, heap);
            block.declare_(agl::UniformBlock::cType_17, 1, 0xd0, 0x10);
        } else {
            block.declare(_50[0]);
        }
        block.create(heap, 2, 1);
    }
    _60.tryAllocBuffer(0xe0, heap, 0x20);
    _70.mBuffer.tryAllocBuffer(0x20, heap, 0x20);
    _88.mBuffer.tryAllocBuffer(0x20, heap, 0x20);
    _a0.mBuffer.tryAllocBuffer(0x20, heap, 0x20);
    mWaterDistanceStat = uking::StatisticsMgr::instance()->getStatsPointer("water_distance");
    mEmbeddedEdgeStat = uking::StatisticsMgr::instance()->getStatsPointer("terrain_embedded_edge");
    mIndoorStat = uking::StatisticsMgr::instance()->getStatsPointer("terrain_is_in_door");
    mHiddenStat = uking::StatisticsMgr::instance()->getStatsPointer("terrain_hidden");
}


// NON_MATCHING: heap construction and key moves differ in loop scheduling.
void Unk_710251cea8::CellSortList::sort() {
    if (count <= 1)
        return;
    for (s32 parent = count / 2; parent > 0; --parent) {
        const auto value = entries[parent - 1];
        s32 hole = parent;
        while (hole * 2 <= count) {
            s32 child = hole * 2;
            if (child < count && entries[child - 1].key < entries[child].key)
                ++child;
            if (entries[child - 1].key <= value.key)
                break;
            entries[hole - 1] = entries[child - 1];
            hole = child;
        }
        entries[hole - 1] = value;
    }
    for (s32 remaining = count; remaining > 1; --remaining) {
        const auto value = entries[remaining - 1];
        entries[remaining - 1] = entries[0];
        s32 hole = 1;
        while (hole * 2 < remaining) {
            s32 child = hole * 2;
            if (child < remaining - 1 && entries[child - 1].key < entries[child].key)
                ++child;
            if (entries[child - 1].key <= value.key)
                break;
            entries[hole - 1] = entries[child - 1];
            hole = child;
        }
        entries[hole - 1] = value;
    }
}

// NON_MATCHING: grid address calculations differ in scheduling and register allocation.
void shiftSecondGrassCellGrid(Unk_710251cea8::Cell (*cells)[59], sead::Vector2i* indices,
                              sead::Vector2i* previous, sead::Vector2i position,
                              Unk_710251cea8::CellState (*states)[59]) {
    const auto reset = [](Unk_710251cea8::Cell& cell) {
        auto& record = *cell.mRecord;
        cell._14 = 0;
        cell.mFlags = 0;
        cell._11[0] = 0;
        cell._11[1] = 0;
        cell._11[2] = 0;
        cell._16 = 0xff;
        record._0 = 0;
        std::memset(record._4, 0, sizeof(record._4));
        auto& current_record = *cell.mRecord;
        current_record._1a = 0;
        current_record._18 = 0;
        std::memset(current_record._14, 0, sizeof(current_record._14));
        std::memset(current_record._1c, 0, sizeof(current_record._1c));
        cell.mRecord->_4[0] = 0;
        cell.mRecord->_4[4] = 0;
        cell.mRecord->_4[8] = 0;
        cell.mRecord->_4[12] = 0;
        cell.mRecord->_3f = 0;
        cell.mRecord->_3c = 0;
        cell.mRecord->_3d = 0;
        cell.mRecord->_3e = 0;
    };
    const s32 dx = position.x - previous->x;
    if (dx > 0) {
        for (s32 i = 0; i < dx; ++i) {
            const s32 x = (indices->x + i) % 59;
            for (s32 y = 0; y < 59; ++y) {
                reset(cells[y][x]);
                states[y][x]._0 = 0;
                states[y][x]._2 = 0;
            }
        }
    }
    if (dx < 0) {
        for (s32 i = -1; i >= dx; --i) {
            s32 x = (indices->x + i) % 59;
            if (x < 0)
                x += 59;
            for (s32 y = 0; y < 59; ++y) {
                reset(cells[y][x]);
                states[y][x]._0 = 0;
                states[y][x]._2 = 0;
            }
        }
    }
    if (dx != 0) {
        previous->x += dx;
        indices->x = (indices->x + dx) % 59;
        if (indices->x < 0)
            indices->x += 59;
    }
    const s32 dy = position.y - previous->y;
    if (dy > 0) {
        for (s32 i = 0; i < dy; ++i) {
            const s32 y = (indices->y + i) % 59;
            for (s32 x = 0; x < 59; ++x) {
                reset(cells[y][x]);
                states[y][x]._0 = 0;
                states[y][x]._2 = 0;
            }
        }
    }
    if (dy < 0) {
        for (s32 i = -1; i >= dy; --i) {
            s32 y = (indices->y + i) % 59;
            if (y < 0)
                y += 59;
            for (s32 x = 0; x < 59; ++x) {
                reset(cells[y][x]);
                states[y][x]._0 = 0;
                states[y][x]._2 = 0;
            }
        }
    }
    if (dy != 0) {
        previous->y += dy;
        indices->y = (indices->y + dy) % 59;
        if (indices->y < 0)
            indices->y += 59;
    }
}

// NON_MATCHING: mutable coefficient addressing and arithmetic scheduling differ.
f32 Unk_710251cea8::sub_71012E7864(s32 kind, const Cell* cell, u32, u32* result) const {
    if (kind != 1 || !(cell->mFlags & 0xc) || cell->mRecord->_3e < 2)
        return 0.0f;

    const f32 view_scale = mViewScale;
    f32 near = std::numeric_limits<f32>::max();
    if (!(sUnk_710251CF30 <= 0.0f)) {
        if (sUnk_710251CF30 == std::numeric_limits<f32>::max())
            near = 0.0f;
        else
            near = 1.0f / (view_scale * sUnk_710251CF30);
    }
    f32 far = std::numeric_limits<f32>::max();
    if (!(sUnk_710251CF38 <= 0.0f)) {
        if (sUnk_710251CF38 == std::numeric_limits<f32>::max())
            far = 0.0f;
        else
            far = 1.0f / (view_scale * sUnk_710251CF38);
    }
    const f32 range = std::max(near - far, 0.1f);
    f32 value = near / range + (static_cast<f32>(cell->_14) / -65535.0f * 1000.0f) / range;
    if (value < 0.0f)
        value = 0.0f;
    else if (value > 1.0f)
        value = 1.0f;
    *result = static_cast<f32>(cell->mRecord->_14[1]) / 255.0f > 0.5f;
    return value;
}

// NON_MATCHING: the bounded uniform-buffer loop differs in scheduling.
void Unk_710251cea8::setBufferIndex(u32 index) {
    const u32 count = mCellSortLists[0].count;
    for (u32 i = 0; i < count && i < 768; ++i)
        _50[i].setBufferIndexMaybe(u8(index));
}

// NON_MATCHING: color conversion loops remain compact; distance arithmetic and stores differ in scheduling.
void Unk_710251cea8::uploadCellData() {
    sead::ScopedLock<sead::CriticalSection> lock(&_10);
    const f32 scale = mViewScale;
    f32 near = std::numeric_limits<f32>::max();
    if (!(sUnk_710251CF30 <= 0.0f)) {
        if (sUnk_710251CF30 == std::numeric_limits<f32>::max())
            near = 0.0f;
        else
            near = 1.0f / (scale * sUnk_710251CF30);
    }
    f32 near2 = std::numeric_limits<f32>::max();
    if (!(sUnk_710251CF34 <= 0.0f)) {
        if (sUnk_710251CF34 == std::numeric_limits<f32>::max())
            near2 = 0.0f;
        else
            near2 = 1.0f / (scale * sUnk_710251CF34);
    }
    f32 far = std::numeric_limits<f32>::max();
    if (!(sUnk_710251CF38 <= 0.0f)) {
        if (sUnk_710251CF38 == std::numeric_limits<f32>::max())
            far = 0.0f;
        else
            far = 1.0f / (scale * sUnk_710251CF38);
    }
    f32 far2 = std::numeric_limits<f32>::max();
    if (!(sUnk_710251CF3C <= 0.0f)) {
        if (sUnk_710251CF3C == std::numeric_limits<f32>::max())
            far2 = 0.0f;
        else
            far2 = 1.0f / (scale * sUnk_710251CF3C);
    }
    const u32 count = mCellSortLists[0].count;
    if (count == 0)
        return;
    const f32 inverse_range = 1.0f / std::max(near - far, 0.1f);
    const f32 inverse_range2 = 1.0f / std::max(far2 - near2, 0.1f);
    for (u32 i = 0; i < count && i < 768; ++i) {
        const u16 index = mCellSortLists[0].entries[i].index;
        const Cell& cell = mCellSortLists[0].cells[index / 59][index % 59];
        const Record& record = *cell.mRecord;
        f32 weight = near * inverse_range +
                     inverse_range * (static_cast<f32>(cell._14) / -65535.0f * 1000.0f);
        if (weight < 0.0f)
            weight = 0.0f;
        else if (weight > 1.0f)
            weight = 1.0f;
        const f32 offset = sUnk_710251CF10 *
                           (static_cast<f32>(record._14[1]) / 255.0f > 0.5f ? 0.0f : 1.0f);
        const f32 inverse_scale = 1.0f / (sUnk_710251CF14 - offset);
        u8* data = _60.getBufferPtr();
        // Inline-only in the original; name is a guess. Native 12E6814 serializes
        // floats into this 0xe0-byte buffer before uploading its first 0xd0 bytes.
        // Copy only the written spans; texture coordinates 4..7 stay unchanged
        // when neither material contains the cell.
        const auto write = [data](u32 index, f32 value) {
            std::memcpy(data + index * sizeof(f32), &value, sizeof(value));
        };
        const f32 x = cell.mX;
        const f32 z = cell.mZ;
        write(0, static_cast<f32>(cell.mX + 10) - x);
        write(1, static_cast<f32>(cell.mZ + 10) - z);
        write(2, x);
        write(3, z);
        const f32 lower_x = cell.mX - 5.0f;
        const f32 lower_z = cell.mZ - 5.0f;
        const f32 upper_x = static_cast<f32>(cell.mX + 15);
        const f32 upper_z = static_cast<f32>(cell.mZ + 15);
        const auto& materials = *_8->_10;
        s32 material_index = -1;
        for (s32 j = 1; j < 3; ++j) {
            const auto& bounds = materials.getMaterial(j).mBounds;
            if (bounds.getMin().x < lower_x && upper_x < bounds.getMax().x &&
                bounds.getMin().y < lower_z && upper_z < bounds.getMax().y) {
                material_index = j;
                break;
            }
        }
        if (material_index != -1) {
            const auto& transform = materials.getMaterial(material_index).mTransform;
            const f32 u = x * transform.x + transform.z;
            const f32 v = z * transform.y + transform.w;
            write(4, (transform.z + transform.x * static_cast<f32>(cell.mX + 10)) - u);
            write(5, (transform.y * static_cast<f32>(cell.mZ + 10) + transform.w) - v);
            write(6, u);
            write(7, v);
        }
        write(8, (cell.mFlags & 0x40) ? 1.0f : 0.0f);
        write(9, 0.0f);
        write(10, near2 * inverse_range);
        write(11, inverse_range2);
        write(12, sUnk_710251CF18);
        write(13, sUnk_710251CF1C);
        write(14, weight);
        write(15, inverse_scale * (static_cast<f32>(record._1a) / 255.0f - offset));
        write(16, inverse_scale * (static_cast<f32>(record._14[2]) / 255.0f - offset));
        write(17, inverse_scale * (static_cast<f32>(record._14[3]) / 255.0f - offset));
        write(18, inverse_scale * (static_cast<f32>(record._18 & 0xff) / 255.0f - offset));
        write(19, inverse_scale * (static_cast<f32>(record._18 >> 8) / 255.0f - offset));
        for (u32 group = 0; group < 8; ++group)
            for (u32 component = 0; component < 4; ++component)
                write(20 + group * 4 + component,
                      static_cast<f32>(record._1c[group * 4 + 3 - component]) / 255.0f);
        auto& block = _50[i];
        block.dcbz(0);
        block.setDataStruct(0, data, 0xd0);
        block.flushCPUCache();
    }
}

}  // namespace ksys::world
