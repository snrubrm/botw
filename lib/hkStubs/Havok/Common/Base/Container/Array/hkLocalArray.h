#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>

/// An array whose initial storage comes from the thread-local stack allocator.
/// Growth uses the ordinary array allocator; the initial block is released separately.
template <typename T>
class hkLocalArray : public hkArray<T> {
public:
    HK_FORCE_INLINE explicit hkLocalArray(int initialCapacity) {
        m_initialCapacity = initialCapacity;
        m_localMemory = nullptr;
        // F694C4 skips the TLS lookup and allocation for an empty local array.
        if (initialCapacity > 0) {
            const int bytes = (initialCapacity * int(sizeof(T)) + 127) & ~127;
            m_localMemory =
                static_cast<T*>(hkMemoryRouter::getInstance().stack().fastBlockAlloc(bytes));
        }
        this->m_data = m_localMemory;
        this->m_capacityAndFlags = initialCapacity | hkArrayBase<T>::DONT_DEALLOCATE_FLAG;
    }

    HK_FORCE_INLINE ~hkLocalArray() {
        if (this->m_data == m_localMemory)
            this->clear();
        const int bytes = (m_initialCapacity * int(sizeof(T)) + 127) & ~127;
        hkMemoryRouter::getInstance().stack().fastBlockFree(m_localMemory, bytes);
    }

    hkLocalArray(const hkLocalArray&) = delete;
    hkLocalArray& operator=(const hkLocalArray&) = delete;

private:
    T* m_localMemory;
    int m_initialCapacity;
};
