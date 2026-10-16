#pragma once

#include <limits>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include <heap/seadExpHeap.h>
#include "KingSystem/Chemical/chmChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
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
// Copies of the chemical world parameters (chm::SystemConfig::World), kept in a static by 0x7100d9a384.
struct WorldParams {
    f32 heatTransferSpeedRate;
    f32 fireHeatTransferSpeedRate;
    f32 conductionSpeedRateLog;
    f32 fireExtraRadius;
    f32 playerFireMargin;
    f32 electricityExtraRadiusRate;
    f32 electricWaterExtraRadiusRate;
    f32 minIceSize;
    f32 burnSpeedRate;
    f32 evaporationSpeedRate;
    f32 iceHeatCheatThreshold;
    f32 iceHeatCheatRate;
    f32 iceMeltRatioEnvTemp;
    f32 iceMeltRatioWarmAir;
    f32 iceMeltRatioFire;
    f32 iceMeltRatioFire2;
    f32 windLiftRate;
    f32 characterIgnitionCount;
    f32 objectIgnitionCount;
    f32 offensiveRigidRadius;
    f32 lightningDistance;
};

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

    Unk_71024dd490();
    // Removes the holder from the chemical system and deletes it (pairs with sub_7100D9A1D0).
    static void sub_7100D9A8F8(Unk_71024dd490* holder);
    virtual ~Unk_71024dd490();
    void sub_7100D9A384(const CreateArg& arg, sead::Heap* heap);
    void sub_7100D9AA84();
    void sub_7100D9AAE4();
    s32 sub_7100D9A1C4() const;
    // 0x7100d99fd0..0x7100d9a1b8: getters for the world parameters in sWorldParams (0x71024dd4c0); the getters of the floats at 0x71024dd450..0x71024dd488 are not decompiled.
    f32 sub_7100D99FD0() const;
    f32 sub_7100D99FDC() const;
    f32 sub_7100D99FF8() const;
    f32 sub_7100D9A00C() const;
    f32 sub_7100D9A01C() const;
    f32 sub_7100D9A038() const;
    f32 sub_7100D9A048() const;
    f32 sub_7100D9A058() const;
    f32 sub_7100D9A080() const;
    f32 sub_7100D9A090() const;
    f32 sub_7100D9A0AC() const;
    f32 sub_7100D9A0BC() const;
    f32 sub_7100D9A0CC() const;
    f32 sub_7100D9A0DC() const;
    f32 sub_7100D9A0EC() const;
    f32 sub_7100D9A0FC() const;
    f32 sub_7100D9A118() const;
    f32 sub_7100D9A17C() const;
    f32 sub_7100D9A18C() const;
    f32 sub_7100D9A19C() const;
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

    sead::CriticalSection _8;
    sead::CriticalSection _48;
    sead::CriticalSection _88;
    u32 _c8 = 0;
    u32 _cc = 0;
    const chm::SystemConfig::World* mWorld = nullptr;
    // D9A384 allocates this Chemical array; D9AA84/D9AAE4 dispatch Chemical methods on it.
    sead::PtrArray<Chemical> mChemicals;
    sead::PtrArrayImpl _e8;
    sead::PtrArrayImpl _f8;
    sead::PtrArrayImpl _108;
    // D9A384 allocates these with CreateArg::_0 entries and clears them.
    struct PtrBuffer {
        // inline-only in the original; name is a guess (D9A384 repeats it for _118 / _130 / _148)
        void init(s32 size, sead::Heap* heap) {
            buffer.tryAllocBuffer(size, heap);
            buffer.fill(nullptr);
            clear();
        }
        void clear() {
            _10 = 0;
            _14 = 0;
            if (buffer.getBufferPtr())
                buffer.fill(nullptr);
        }
        sead::Buffer<void*> buffer;
        s32 _10 = 0;
        s32 _14 = 0;
    };
    PtrBuffer _118;
    PtrBuffer _130;
    PtrBuffer _148;
    s32 _160 = 0;
    s32 _164 = 2;
    void* _168 = nullptr;
    void* _170 = nullptr;
    void* _178 = nullptr;
    void* _180 = nullptr;
    u8 _188[0x194 - 0x188];
    s32 _194 = 0;
    // D9A1D0 clears these; D9C0CC selects a Chemical and activates the request.
    bool _198 = false;
    s32 _19c = 0;
    f32 _1a0 = std::numeric_limits<f32>::quiet_NaN();
    u8 _1a4[0x1b0 - 0x1a4];
    Chemical* _1b0 = nullptr;
    u8 _1b8[0x1cc - 0x1b8];
    // Full D9B8C8 fills up to ten positions and flags; D9A1D0 clears them.
    struct PositionEntry {
        sead::Vector3f position = {0, 0, 0};
        bool _c = false;
    };
    KSYS_CHECK_SIZE_NX150(PositionEntry, 0x10);
    sead::SafeArray<PositionEntry, 10> _1cc;
    s32 _26c = 0;
    s32 _270 = 0;
    f32 _274 = 10.0f;
    f32 _278 = 0.75f;
    u16 _27c = 0xffff;
    u8 _27e[0x28c - 0x27e];
    // lane1 s91: the largest element heap size seen by the element factories.
    u32 mMaxElementHeapSize = 0;

    // 0x7100d9cef8 (CSV elementEmitMaybe; declared only): prints the holder status once.
    void elementEmitMaybe();

    // The element factories (0x71010c74a0, 0x71010ea040, 0x71010f1bb0, 0x71012fe4b4, 0x71012fe6e0 and
    // ksys::world::sub_71010CBF7C) each repeat the same body: an "ElementHolder" ExpHeap from the chemical
    // system heap, the element constructed in it, and cleanup when the element got no holder.
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
