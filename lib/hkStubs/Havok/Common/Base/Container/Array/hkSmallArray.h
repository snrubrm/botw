#pragma once

#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>
#include <Havok/Common/Base/Container/Array/hkArrayUtil.h>
#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

// 0x710177EEDC grows erased small-array storage using its element size.
// Complete native callers 0x71016163EC, 0x71015FDF04 and 0x71015FE09C pass this array.
void sub_710177EEDC(void* array, int elementSize);

template <typename T>
class hkSmallArray {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkSmallArray)

    enum : int {
        CAPACITY_MASK = hkUint16(0x3fff),
        FLAG_MASK = hkUint16(0xC000),
        DONT_DEALLOCATE_FLAG = hkUint16(0x8000),
        LOCKED_FLAG = hkUint16(0x4000),
    };

    HK_FORCE_INLINE hkSmallArray();
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    explicit hkSmallArray(hkFinishLoadedObjectFlag f) {}

    hkSmallArray(const hkSmallArray&) = delete;
    auto operator=(const hkSmallArray&) = delete;

    HK_FORCE_INLINE ~hkSmallArray();

    HK_FORCE_INLINE int getSize() const;
    HK_FORCE_INLINE int getCapacity() const;
    HK_FORCE_INLINE int indexOf(const T& value) const;
    HK_FORCE_INLINE void pushBack(const T& value);

    HK_FORCE_INLINE T& operator[](int i);
    HK_FORCE_INLINE const T& operator[](int i) const;

protected:
    void releaseMemory();

    T* m_data;
    hkUint16 m_size;
    hkUint16 m_capacityAndFlags;
};

template <typename T>
inline hkSmallArray<T>::hkSmallArray()
    : m_data(nullptr), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}

template <typename T>
inline hkSmallArray<T>::~hkSmallArray() {
    releaseMemory();
}

template <typename T>
inline int hkSmallArray<T>::getSize() const {
    return m_size;
}

template <typename T>
inline int hkSmallArray<T>::getCapacity() const {
    return m_capacityAndFlags & CAPACITY_MASK;
}

template <typename T>
inline T& hkSmallArray<T>::operator[](int i) {
    return m_data[i];
}

template <typename T>
inline const T& hkSmallArray<T>::operator[](int i) const {
    return m_data[i];
}

template <typename T>
inline void hkSmallArray<T>::releaseMemory() {
    if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
        hkDeallocateChunk(m_data, getCapacity());
}

// inline-only in the original; name is a guess following the hkArray search API.
// Complete native 0x71016163EC and 0x71015FE09C search for an empty slot.
template <typename T>
inline int hkSmallArray<T>::indexOf(const T& value) const {
    for (int i = 0; i < getSize(); ++i) {
        if (m_data[i] == value)
            return i;
    }
    return -1;
}

// inline-only in the original; name is a guess following the hkArray append API.
// Native 0x71016163EC, 0x71015FDF04 and 0x71015FE09C share this growth and append sequence.
template <typename T>
inline void hkSmallArray<T>::pushBack(const T& value) {
    if (getSize() == getCapacity())
        sub_710177EEDC(this, sizeof(T));
    hkArrayUtil::constructWithCopy(m_data + m_size, 1, value);
    ++m_size;
}
