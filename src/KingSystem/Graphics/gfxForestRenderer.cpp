#include "KingSystem/Graphics/gfxForestRenderer.h"
#include <cstring>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <gsys/gsysModelUnitDrawArray.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::gfx {

namespace {
// 0x710260a1cc / 0x710260a1d0 / 0x710260a1d4 / 0x710260a1d8 / 0x710260a1dc (placeholder names; read
// directly, no GOT entries).
bool sUnk_710260a1cc;
bool sUnk_710260a1d0;
bool sUnk_710260a1d4;
bool sUnk_710260a1d8;
u32 sUnk_710260a1dc;
}  // namespace

bool* ForestRenderer::sub_7100F00B94() {
    return &sUnk_710260a1cc;
}

bool* ForestRenderer::sub_7100F00BA0() {
    return &sUnk_710260a1d0;
}

bool* ForestRenderer::sub_7100F00BAC() {
    return &sUnk_710260a1d4;
}

bool* ForestRenderer::sub_7100F01AB4() {
    return &sUnk_710260a1d8;
}

u32* ForestRenderer::sub_7100F01AC0() {
    return &sUnk_710260a1dc;
}

ForestRenderer::ForestRenderer() = default;

void ForestRenderer::Entry::sub_7100F02C40() {
    mRecords.freeBuffer();
    mHeap = nullptr;
    for (auto& item : mItems)
        item.finalize();
    mItems.freeBuffer();
    _28.freeBuffer();
}

// NON_MATCHING: Clang duplicates the `_50 |= 8` store into the state 6 path (jump threading on bit 0)
// and biases the loop pointer at mModelUnit instead of the unit buffer.
void ForestRenderer::requestDraw() {
    auto* terrain = tera::Terrain::instance();
    if (terrain && terrain->_a50 && (terrain->_a50->_18 & 0x20))
        return;

    const bool stage = StageInfo::sIsNotDebugStageAndNotDungeon | StageInfo::sIsFinalTrial;
    if (!stage)
        return;
    if (_54 < 5 || _220 == 0)
        return;
    if (_54 == 6 && (_50 & 1) && _60 > 3)
        return;

    _50 |= 8;
    switch (_54) {
    case 10:
    case 16:
        mModelSet.mCurrent = 1 - mModelSet.mCurrent;
        for (auto& entry : mUnitEntries.mEntries) {
            if (entry.mState != 3)
                continue;
            entry.mModelUnit->getDrawArray()->setUnits(&entry.mUnits.data()[entry.mIndex * 0x400], entry.mCount);
            entry.mModelUnit->getDrawArray()->setSize(entry.mCount);
            const u32 count = entry.mCount;
            entry.mIndex = 1 - entry.mIndex;
            entry.mCount = 0;
            entry.mPrevCount = count;
        }
        ++_54;
        break;
    default:
        break;
    }

    if (_50 & 0x400)
        return;
    if (_50 & 1)
        return;
    if (sUnk_710260a1d8)
        return;

    auto& slot = mModelSet.mSlots[1 - mModelSet.mCurrent];
    if (slot.mState == 2)
        slot.mModel->requestDraw();
}

// NON_MATCHING: only the schedule of the two GOT loads (the original loads both addresses first, then both bytes).
// `sIsFinalTrial` is the byte at 0x2606855 (StageInfo statics are consecutive from 0x2606848).
bool ForestRenderer::x_9() {
    if (_54 >= 5 && _220 != 0) {
        const bool stage = StageInfo::sIsNotDebugStageAndNotDungeon | StageInfo::sIsFinalTrial;
        return _54 != 6 && stage;
    }
    return false;
}

// NON_MATCHING: the original copies this to x8 and sets the false result in w0 before the state 6 test.
bool ForestRenderer::stopped() {
    if (_54 >= 5 && _220 != 0) {
        const bool stage = StageInfo::sIsNotDebugStageAndNotDungeon | StageInfo::sIsFinalTrial;
        if (stage)
            return _54 == 6 && (_50 & 1) != 0 && _60 > 3;
    }
    return true;
}

void ForestRenderer::Entry::sub_7100F07060() {
    const s32 table_size = (_8 & 1) ? 80 : 1280;
    const s32 num_records = mNumRecords;
    if (num_records != 0) {
        mRecords.tryAllocBuffer(num_records, mHeap);
        std::memset(mRecords.getBufferPtr(), 0, mRecords.getByteSize());
    }
    _78.tryAllocBuffer(table_size, mHeap);
    std::memset(_78.getBufferPtr(), 0, _78.getByteSize());
}

void ForestRenderer::Unk_1b8::invoked1(TaskPostRunResult*, const TaskPostRunContext&) {
    mFlags &= ~1u;
}

ForestRenderer::Item::~Item() {
    finalize();
}

ForestRenderer::Entry::~Entry() {
    sub_7100F02C40();
}

ForestRenderer::TreeResMaybe::~TreeResMaybe() {
    mRes.unloadAndResetUnitFlag20000();
}

ForestRenderer::ModelSlot::~ModelSlot() {
    finalize();
}

ForestRenderer::UnitEntry::~UnitEntry() {
    if (mModelUnit) {
        delete mModelUnit;
        mModelUnit = nullptr;
    }
    _48 = -1;
    _4c = -1;
    _50 = 0;
    _40 = 0;
    mUnits.freeBuffer();
}

ForestRenderer::UnitEntryBuffer::~UnitEntryBuffer() {
    mEntries.freeBuffer();
}

ForestRenderer::ModelSet::~ModelSet() {
    for (auto& slot : mSlots)
        slot.finalize();
}

bool ForestRenderer::x_6(const sead::SafeString& name, const sead::Vector3f& pos,
                         const sead::Vector3f& rotate, f32 scale) {
    for (auto& entry : mEntries)
        entry.sub_7100F071C4(name, pos, rotate, scale);
    return true;
}

void ForestRenderer::sub_7100F03B68() {
    for (auto& entry : mEntries) {
        for (auto& item : entry.mItems)
            item._c.set(2);
    }
}

void ForestRenderer::x_1() {
    for (auto& entry : mEntries) {
        for (auto& record : entry.mRecords)
            record._4.reset(4);
        for (auto& item : entry.mItems)
            item._c.set(2);
    }
}

void ForestRenderer::sub_710F06904(map::PlacementMgr* mgr, bool a) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& entry : mUnitEntries.mEntries) {
        if (!entry.mModelUnit)
            continue;
        auto* draw_array = entry.mModelUnit->getDrawArray();
        const u32 num = draw_array->_18;
        for (u32 i = 0; i < num; ++i)
            draw_array->flushUBO(i);
    }
}

void ForestRenderer::x_2() {
    tera::Terrain::instance()->sub_710114DE70()->sub_71010827DC();
    for (auto& entry : mEntries) {
        const s32 size = (entry._8 & 1) ? 4960 : 79360;
        entry._78.tryAllocBuffer(size, entry.mHeap);
        std::memset(entry._78.getBufferPtr(), 0, entry._78.getByteSize());
    }
    _54 = 2;
}

bool ForestRenderer::x_3(const sead::SafeString& name, const sead::Vector3f& pos,
                         const sead::Vector3f& rotate, f32 scale) {
    bool found = false;
    for (auto& entry : mEntries)
        found |= entry.sub_7100F06CB0(name, pos, rotate, scale);
    if (!found)
        return false;
    tera::Terrain::instance()->sub_710114DE70()->sub_7101082824(name, pos);
    return true;
}

void ForestRenderer::x_5() {
    tera::Terrain::instance()->sub_710114DE70()->sub_7101083060();
    for (auto& entry : mEntries)
        entry.sub_7100F07060();
    _54 = 4;
}

s32 ForestRenderer::x_7(const sead::Vector3f& vec) {
    if (_54 >= 5) {
        u32 index = 0;
        for (auto& entry : mEntries) {
            const s32 item = entry.sub_7100F0663C(vec);
            if (item != -1)
                return item | index;
            index += 0x10000;
        }
    }
    return -1;
}

// NON_MATCHING: the order of the item pointer increment and the counter decrement in the loop.
void ForestRenderer::x_8(s32 idx, bool a, bool b) {
    const u32 entry_idx = u32(idx) >> 16;
    if (entry_idx > 1)
        return;
    auto& entry = mEntries[entry_idx];
    auto& record = entry.mRecords[idx & 0xffff];
    if (b) {
        record._4.reset(0x46);
        return;
    }
    if (a)
        record._4.reset(4);
    else
        record._4.set(4);
    for (auto& item : entry.mItems) {
        if (item.sub_7100F0914C(&record, a, false))
            break;
    }
}

}  // namespace ksys::gfx
