#include "KingSystem/Map/mapPlacementTree.h"
#include "KingSystem/Map/mapObject.h"
#include <basis/seadRawPrint.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadBitFlag.h>
#include <prim/seadMemUtil.h>

namespace ksys::map {

PlacementTree::PlacementTree() = default;

PlacementTree::~PlacementTree() {
    mBuffer.freeBuffer();
    mObjects.freeBuffer();
    delete[] static_cast<u8*>(mFreeList.work());
}

// NON_MATCHING: level setup and buffer indexing use different reload and store scheduling.
void PlacementTree::sub_71011ED47C(const InitArg& arg) {
    _34 = arg.min_x;
    _38 = arg.min_z;
    _3c = arg.max_x;
    _40 = arg.max_z;
    f32 cell_size = arg.cell_size;
    const f32 extent = sead::Mathf::max(arg.max_x - arg.min_x, arg.max_z - arg.min_z);
    u32 num_levels = 1;
    for (f32 size = cell_size; size < extent; size += size)
        ++num_levels;
    const sead::Vector2f center((arg.min_x + arg.max_x) * 0.5f,
                               (arg.min_z + arg.max_z) * 0.5f);
    mBuffer.tryAllocBuffer(num_levels, arg.heap);
    s32 num_cells = 1;
    for (s32 i = num_levels - 1; i > 0; --i) {
        auto& level = mBuffer[i];
        const sead::Vector2f first(
            cell_size * s32(_34 / cell_size + (_34 > 0.0f ? 0.99999f : -0.99999f)),
            cell_size * s32(_38 / cell_size + (_38 > 0.0f ? 0.99999f : -0.99999f)));
        const sead::Vector2f last(
            cell_size * s32(_3c / cell_size + (_3c > 0.0f ? 0.99999f : -0.99999f)),
            cell_size * s32(_40 / cell_size + (_40 > 0.0f ? 0.99999f : -0.99999f)));
        const sead::Vector2f min(sead::Mathf::min(first.x, last.x),
                                sead::Mathf::min(first.y, last.y));
        const sead::Vector2f max(sead::Mathf::max(last.x, first.x),
                                sead::Mathf::max(last.y, first.y));
        level._4 = sead::Mathf::ceil((max.x - min.x) / cell_size);
        level._8 = sead::Mathf::ceil((max.y - min.y) / cell_size);
        level._10 = min.y - center.y;
        level._14 = cell_size;
        cell_size += cell_size;
        num_cells += level._4 * level._8;
        level._0 = u32(-1);
        level._c = min.x - center.x;
    }
    mBuffer[0]._0 = u32(-1);
    mBuffer[0]._4 = 1;
    mBuffer[0]._8 = 1;
    mBuffer[0]._14 = cell_size;
    mBuffer[0]._c = mBuffer[1]._c;
    mBuffer[0]._10 = mBuffer[1]._10;
    mObjects.tryAllocBuffer(num_cells, arg.heap);
    sead::MemUtil::fillZero(mObjects.getBufferPtr(), sizeof(Node*) * num_cells);
    u32 offset = 0;
    for (u32 i = 0; i < num_levels; ++i) {
        mBuffer[i]._0 = offset;
        offset += mBuffer[i]._4 * mBuffer[i]._8;
    }
    _30 = arg.num_nodes;
    auto* work = new (arg.heap, 8) u8[_30 * sizeof(Node)];
    mFreeList.setWork(work, sizeof(Node), _30);
}

void PlacementTree::resetPlacementObjPtrs() {
    sead::MemUtil::fillZero(mObjects.getBufferPtr(), sizeof(Node*) * mObjects.size());
    mFreeList.setWork(mFreeList.work(), 0x10, _30);
}

void PlacementTree::calledForPlaceActor1(Object* object) {
    sead::Vector3f position;
    f32 distance;
    object->getTraversePosAndLoadDistance(&position, &distance);
    if (distance <= 0.0f)
        return;
    auto* node = static_cast<Node*>(mFreeList.alloc());
    node->object = object;
    node->next = nullptr;
    const s32 level = sub_71011ED960(distance);
    auto** tail = &mObjects[x_1(position, level)];
    while (*tail)
        tail = &(*tail)->next;
    *tail = node;
}

// NON_MATCHING: the loop bounds check is simplified and vector operations use different registers.
u32 PlacementTree::sub_71011EDB78(sead::Vector2f* min, sead::Vector2f* max, u32 cell,
                                f32 distance) const {
    u32 level_index = 0;
    for (u32 i = 0; i < mBuffer.size(); ++i) {
        if (mBuffer[i]._0 >= cell)
            break;
        level_index = i;
    }
    const auto& level = mBuffer[level_index];
    min->x = f32((cell - level._0) % level._4) * level._14;
    min->y = f32((cell - level._0) / level._4) * level._14;
    max->x = min->x + level._14;
    max->y = min->y + level._14;
    min->x += level._c;
    min->y += level._10;
    max->x += level._c;
    max->y += level._10;
    min->x -= distance;
    min->y -= distance;
    max->x += distance;
    max->y += distance;
    min->x = sead::Mathf::clamp(min->x, _34, _3c);
    min->y = sead::Mathf::clamp(min->y, _38, _40);
    max->x = sead::Mathf::clamp(max->x, _34, _3c);
    max->y = sead::Mathf::clamp(max->y, _38, _40);
    return level_index;
}

u32 PlacementTree::x_1(const sead::Vector3f& pos, int level) const {
    const auto& obj = mBuffer[level];
    const sead::Vector2f coordinates =
        (sead::Vector2f(pos.x, pos.z) - sead::Vector2f(obj._c, obj._10)) / obj._14;

    int x = 0;
    if (obj._4 != 0) {
        const int i = coordinates.x;
        if (i >= 0)
            x = i > int(obj._4 - 1) ? int(obj._4 - 1) : i;
    }

    int z = 0;
    if (obj._8 != 0) {
        const int i = coordinates.y;
        if (i >= 0)
            z = i > int(obj._8 - 1) ? int(obj._8 - 1) : i;
    }

    return obj._0 + x + z * obj._4;
}

int PlacementTree::sub_71011ED960(f32 distance) const {
    if (mBuffer[0]._14 > distance) {
        const int last = mBuffer.size() - 1;
        u32 x = sead::Mathf::floor(distance / mBuffer[last]._14);
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return last - sead::BitFlagUtil::countOnBit(x);
    }
    return 0;
}

}  // namespace ksys::map
