#include "KingSystem/Resource/resCompactedHeap.h"
#include <prim/seadScopedLock.h>

namespace ksys::res {

CompactedHeap::~CompactedHeap() = default;

void CompactedHeap::Unk3::setPointer(void* const& ptr) {
    for (auto& entry : _0)
        entry.setPointer(ptr);
}

void CompactedHeap::Unk1::setPointer(void* const& ptr) {
    for (auto& entry : _0)
        entry.setPointer(ptr);
}

CompactedHeap* CompactedHeap::create(const sead::SafeString& name, void* buffer,
                                     size_t buffer_size, u32 x) {
    return new (buffer) CompactedHeap(name, buffer, buffer_size, x);
}

void CompactedHeap::destroy() {
    auto lock = sead::makeScopedLock(_5cf8);
    auto lock2 = sead::makeScopedLock(_5d78);
    this->~CompactedHeap();
}

void CompactedHeap::incrementCompactionCount() {
    mCompactionCount.increment();
}

bool CompactedHeap::setBuffer(void* buffer, size_t size) {
    auto lock = sead::makeScopedLock(_5d38);
    if (_5c90 != 3)
        return false;

    _5cb8 = 0;
    mCompactionCount.exchange(0);
    _5c98 = buffer;
    _5ca0 = size;
    return true;
}

bool CompactedHeap::compact() {
    auto lock = sead::makeScopedLock(_5d38);
    switch (_5c90) {
    case 0:
        x_5();
        break;
    case 1:
        x_2();
        break;
    case 2:
        x_3();
        break;
    case 3:
        if (!_5c98 || !x_4())
            return false;
        x_5();
        break;
    }
    return true;
}

}  // namespace ksys::res
