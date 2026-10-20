#pragma once

#include <basis/seadTypes.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::tera {

// Placeholder: the 0x530-byte vegetation terrain material used by the three manager helpers.
// Initializer 0x7101077330 and position update 0x7101077574 establish the trailing fields.
struct VegeTeraMat {
    u32 _0;
    u8 _4[0x4e0 - 0x4];
    sead::Vector2f mOrigin;
    sead::Vector2f mPosition;
    sead::Vector2f mDelta;
    sead::BoundBox2f mBounds;
    sead::Vector4f mTransform;
    u32 mDimension;
    f32 mSize;
    u32 mCellSize;
    f32 _524;
    u8 _528[8];

    void updatePosition(const sead::Vector3f& position);
};
static_assert(offsetof(VegeTeraMat, mBounds) == 0x4f8);
static_assert(offsetof(VegeTeraMat, mTransform) == 0x508);
static_assert(offsetof(VegeTeraMat, mDimension) == 0x518);
static_assert(sizeof(VegeTeraMat) == 0x530);

// Placeholder: the container at 0x7101078674 / 0x710107869c / 0x71010786f4. It holds three
// VegeTeraMat records at +8 / +0x538 / +0xa68 (stride 0x530).
class VegeTeraMatMgr {
public:
    // Placeholder: the 0x90-byte buffer entries and the item they point at.
    struct Item {
        u8 _0[0x20];
        u8 mFlags;
    };
    struct Entry {
        Item* mItem;
        u8 _8[8];
        u8 _10[0x80];
    };
    static_assert(sizeof(Entry) == 0x90);
    struct Buffer {
        u8 _0[0xd8];
        s32 mCount;
        u8 _dc[4];
        Entry* mArray;
    };
    static_assert(offsetof(Buffer, mCount) == 0xd8);
    static_assert(offsetof(Buffer, mArray) == 0xe0);

    // 0x7101078674: marks all three records dirty.
    void setDirty();
    // 0x710107869c: forwards `value` to each record unless the global gate is set.
    void sub_710107869C(u8 value);
    // 0x71010786f4: runs the no-argument update on each record unless the global gate is set.
    void sub_71010786F4();
    // 0x710107873c: forwards the selected buffer entry to each record unless the global gate is set.
    void sub_710107873C(void* arg);

    // Inline-only in the original; name is a guess. Native 12E6814 and 12D26E8
    // select these same records for terrain bounds and texture-coordinate transforms.
    const VegeTeraMat& getMaterial(s32 index) const { return mRecords[index]; }

private:
    u8 _0[8];
    VegeTeraMat mRecords[3];
    // Read by the per-record update 0x710107873c: an index and the buffer whose 0x90-byte
    // entries it indexes (count at +0xd8, array at +0xe0).
    // inline-only in the original: 0x710107873c reloads the selected entry before each call.
    Entry* getEntry() {
        const s32 index = _f9c;
        return u32(_fa0->mCount) > u32(index) ? &_fa0->mArray[index] : _fa0->mArray;
    }

    u8 _f98[4];
    s32 _f9c;
    Buffer* _fa0;
};
KSYS_CHECK_SIZE_NX150(VegeTeraMatMgr, 0xfa8);

}  // namespace ksys::tera
