#pragma once

#include "KingSystem/Utils/Types.h"

namespace ksys::res {

// Placeholder classes of the res TU at 0x7100fdc2a4 - 0x7100fddb70 (CSV StructB / StructA); layouts are not recovered.
// They are the members at ActorData + 0x58 and ActorData + 0x20 (constructed by PlacementActors' ctor, destroyed
// by its D1 and by PlacementActors::deleteActorData).

// Vtable 0x71024f9938 (GOT 0x259eb88): ctor 0x7100fdce2c, D1 0x7100fdce48, D0 0x7100fdcfe8.
class Unk_71024f9938 {
public:
    Unk_71024f9938();
    virtual ~Unk_71024f9938();
    // 0x7100fdcf20 (CSV StructB::x)
    void sub_7100FDCF20();

private:
    u8 _8[0x30 - 0x8];
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9938, 0x30);

// Vtable 0x71024f9958 (GOT 0x259eb90): ctor 0x7100fdd21c, D1 0x7100fdd250, D0 0x7100fdd474.
class Unk_71024f9958 {
public:
    Unk_71024f9958();
    virtual ~Unk_71024f9958();
    // 0x7100fdd264 (CSV StructA::x)
    void sub_7100FDD264();

private:
    u8 _8[0x38 - 0x8];
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9958, 0x38);

}  // namespace ksys::res
