#pragma once

namespace uking {

// Third base of the IHandler-based manager singletons (IceBlockMgr, AmiiboMgr): its secondary
// vtable only holds the two destructor thunks; the base's own type is unknown (placeholder name =
// IceBlockMgr's secondary vtable 0x710243c330). The destructor is inline (the derived destructors
// only store the vtable).
class Unk_710243c330 {
public:
    virtual ~Unk_710243c330() = default;
};

}  // namespace uking
