#include "KingSystem/Physics/Ragdoll/physUnk_7102519b90.h"
#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

Unk_7102519a98::Unk_7102519a98(s32 value) : _48(value) {}

Unk_7102519a98::~Unk_7102519a98() {
    // The pending pointer carries two tag bits, as in NavMeshObj2Maybe::sub_7100F8B538.
    auto* pending = reinterpret_cast<HavokAI*>(reinterpret_cast<uintptr_t>(_58.load()) & ~uintptr_t(3));
    if (pending)
        pending->sub_7100F81EE0(this, false);
    if (_60.load() & 0x3c00)
        _50->sub_7100F81EE0(this, false);
    sub_71012A7738();
    // The original also performs these discarded atomic loads at the end.
    _58.load();
    _60.load();
}

}  // namespace ksys::phys
