#pragma once

#include <basis/seadTypes.h>
#include <container/seadListImpl.h>
#include <prim/seadSafeString.h>

namespace aal {

/// A block of memory that is attached to the audio hardware (through MemoryPoolManager::requestAttachMemoryPool): a
/// name, the memory and a node for the list of the pools of the manager (0x68 bytes).
struct MemoryPool {
    MemoryPool() : _38(0), memory(nullptr), size(0), _50(false) {}

    sead::FixedSafeString<32> name;
    u64 _38;
    void* memory;
    size_t size;
    bool _50;
    sead::ListNode node;
};
static_assert(sizeof(MemoryPool) == 0x68, "aal::MemoryPool size mismatch");

}  // namespace aal
