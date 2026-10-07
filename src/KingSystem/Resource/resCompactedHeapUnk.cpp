#include "KingSystem/Resource/resCompactedHeap.h"

namespace ksys::res {

// Separate TU: in the original these are defined after the other CompactedHeap functions and are not inlined
// into CompactedHeap::Unk1::setPointer / Unk3::setPointer.
void CompactedHeap::Unk2::setPointer(void* const& ptr) {
    for (auto& entry : _0)
        entry = ptr;
}

void CompactedHeap::Unk4::setPointer(void* const& ptr) {
    for (auto& entry : _0)
        entry = ptr;
}

}  // namespace ksys::res
