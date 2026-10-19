#include "aal/aalAssetType.h"

#include <container/seadSafeArray.h>
#include <prim/seadEnum.h>
#include <prim/seadScopedLock.h>
#include <thread/seadCriticalSection.h>

namespace aal
{
// The value array of the original SEAD_ENUM_EX(AssetType, Wave = 0, Stream = 1, Unknown = 0xFF).
// 0x7100b7906c initialises it under EnumUtil::getInitValueArrayCS_ (the array is 0, 1, 0xff) and
// then looks the value up. This is SEAD_ENUM_EX_VALUES spelled out, because the class is hand-written.
struct ValueArray
{
    ValueArray();

    s32 size() const { return mSize; }
    int& operator[](s32 idx) { return *get(idx); }
    const int& operator[](s32 idx) const { return *get(idx); }

    int* get(s32 idx)
    {
        if (u32(mSize) <= u32(idx))
        {
            SEAD_ASSERT_MSG(false, "index exceeded [%d/%d]", idx, mSize);
            return mBuffer;
        }
        return &mBuffer[idx];
    }

    const int* get(s32 idx) const
    {
        if (u32(mSize) <= u32(idx))
        {
            SEAD_ASSERT_MSG(false, "index exceeded [%d/%d]", idx, mSize);
            return mBuffer;
        }
        return &mBuffer[idx];
    }

private:
    s32 mSize = 0;
    int* mBuffer = nullptr;
};

inline ValueArray::ValueArray()
{
    sead::ScopedLock<sead::CriticalSection> lock(sead::EnumUtil::getInitValueArrayCS_());
    if (mBuffer)
        return;
    struct Array : sead::SafeArray<int, 3>
    {
        Array() : sead::SafeArray<int, 3>{0, 1, 0xff} {}
    };
    static Array sArray{};
    mSize = sArray.size();
    mBuffer = sArray.getBufferPtr();
}

inline ValueArray& getArray()
{
    static ValueArray sBuffer;
    return sBuffer;
}
// 0x7100b7906c
int AssetType::findRelativeIndex_(ValueType value)
{
    const ValueArray& array = getArray();
    for (int i = 0, n = array.size(); i < n; ++i)
    {
        if (array[i] == value)
            return i;
    }
    return -1;
}
}  // namespace aal
