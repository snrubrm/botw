#pragma once

#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

class ElementSpark;
struct ElementSparkCreateArg;
class ElementWater;
class ElementDirectionalWindOrGust;
struct ElementDirectionalWindCreateArg;
struct ElementWaterCreateArg;
class ElementLightningFire;
class ElementLightningShockwave;

// Weather 10ED67C / 10ED894 build this trivial record. Both complete element
// factories 12FE4B4 / 12FE6E0 copy xyz and the byte at C into their objects.
struct ElementLightningCreateArg {
    sead::Vector3f position;
    u8 flags;
};
KSYS_CHECK_SIZE_NX150(ElementLightningCreateArg, 0x10);

namespace sead {
class Heap;
}

namespace ksys::act {
class Chemical;
class Unk_71024dd1c8;

// 2026-10-07: D9A1D0 constructs a 0x290-byte Node with vtable24DD490; D9A970/D9AA0C
// are its original own D1/D0. Only the used prefix is recovered; do not allocate it.
class Unk_71024dd490 : public sead::hostio::Node {
public:
    struct CreateArg {
        CreateArg();
        s32 _0;
        s32 _4;
        sead::SafeString worldName;
        void* _18;
    };
    static_assert(sizeof(CreateArg) == 0x20);

    virtual ~Unk_71024dd490();
    void sub_7100D9AA84();
    void sub_7100D9AAE4();
    s32 sub_7100D9A1C4() const;
    f32 sub_7100D9A17C() const;
    f32 sub_7100D9A18C() const;
    // 10C74A0 constructs a 0x90-byte ElementSpark with this holder and the request.
    ElementSpark* sub_71010C74A0(const ElementSparkCreateArg* arg);
    // lane1 s91 (declared only): 10EA040, the same factory for a 0x1b0-byte ElementWater.
    ElementWater* sub_71010EA040(const ElementWaterCreateArg* arg);
    // lane1 s91 (declared only): 10F1BB0, the same factory for ElementDirectionalWindOrGust.
    ElementDirectionalWindOrGust* sub_71010F1BB0(const ElementDirectionalWindCreateArg* arg);
    // Full factories 12FE4B4 / 12FE6E0 return the allocated lightning element.
    ElementLightningShockwave* sub_71012FE4B4(const ElementLightningCreateArg* arg);
    ElementLightningFire* sub_71012FE6E0(const ElementLightningCreateArg* arg);
    // lane1 s90 (declared only): 0x7100d9afd8 queues a chemical holder (sets its flag 0x20).
    bool sub_7100D9AFD8(Unk_71024dd1c8* holder);

    u8 _8[0x48 - 0x8];
    sead::CriticalSection _48;
    u8 _88[0xc8 - 0x88];
    u32 _c8;
    u8 _cc[0xd8 - 0xcc];
    // D9A384 allocates this Chemical array; D9AA84/D9AAE4 dispatch Chemical methods on it.
    sead::PtrArray<Chemical> mChemicals;
    u8 _e8[0x198 - 0xe8];
    // D9A1D0 clears these; D9C0CC selects a Chemical and activates the request.
    bool _198;
    u8 _199[0x1b0 - 0x199];
    Chemical* _1b0;
    u8 _1b8[0x1cc - 0x1b8];
    // Full D9B8C8 fills up to ten positions and flags; D9A1D0 clears them.
    struct PositionEntry {
        sead::Vector3f position;
        bool _c;
    };
    KSYS_CHECK_SIZE_NX150(PositionEntry, 0x10);
    sead::SafeArray<PositionEntry, 10> _1cc;
    s32 _26c;
};

Unk_71024dd490* sub_7100D9A1D0(const Unk_71024dd490::CreateArg& arg, sead::Heap* heap);

}  // namespace ksys::act

namespace ksys::world {

// Full 12FDA7C receives the record in x0/x1 and bool in w2, then forwards the
// local record's address to the Shockwave factory. The return pointer follows
// the child allocation result and the null-holder path.
ElementLightningShockwave* sub_71012FDA7C(ElementLightningCreateArg arg, bool check_collision);
// CSV label ElementLightningFire::create. The source owner is still unknown;
// this narrow wrapper follows the existing Spark dispatch spelling. Native
// 12FDF24 forwards an address to 12FE6E0, with a null allocation result when no holder exists.
ElementLightningFire* sub_71012FDF24(const ElementLightningCreateArg* arg);

}  // namespace ksys::world
