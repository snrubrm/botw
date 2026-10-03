#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <gsys/gsysModelAccessKey.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys {

namespace res {
class BoneControl;
}

namespace act {

class Actor;

// Unnamed classes of the actor bone control code (0x7100d82b74 - 0x7100d8bxxx). The class names are
// placeholders (Unk_<ctor address>); Actor::mBoneControl -> BoneControl::_0 -> Unk_7100d8557c, which
// holds two controllers (Unk_7100d860d8 at 0x10, initialised from res::BoneControl's spine data, and
// Unk_7100d83054 at 0xe8).

// Size 0xd8. ctor 0x7100d860d8. The spine controller: rotates a chain of bones towards a target
// position (_8) within per-bone angle limits.
class Unk_7100d860d8 {
public:
    explicit Unk_7100d860d8(Actor* actor);

    // An element of `_18` (0x180 bytes; built by 0x7100d86170 from the res::BoneControl data). The
    // limits come in pairs {base value, current value}: the current value is the base value
    // scaled by the controller's ratios (_a8 - _cc).
    struct Node {
        /* 0x000 */ BoneHandle _0;
        /* 0x0a8 */ gsys::BoneAccessKeyEx _a8;
        /* 0x0e0 */ bool _e0;
        /* 0x0e1 */ u8 _e1[0xf4 - 0xe1];
        /* 0x0f4 */ f32 _f4;  // base L limit (negative)
        /* 0x0f8 */ f32 _f8;  // base R limit
        /* 0x0fc */ f32 _fc;  // base U limit
        /* 0x100 */ f32 _100;  // base D limit (negative)
        /* 0x104 */ f32 _104;  // current L limit
        /* 0x108 */ f32 _108;  // current R limit
        /* 0x10c */ f32 _10c;  // current U limit
        /* 0x110 */ f32 _110;  // current D limit
        /* 0x114 */ u8 _114[0x124 - 0x114];
        /* 0x124 */ f32 _124;
        /* 0x128 */ f32 _128;
        /* 0x12c */ f32 _12c;
        /* 0x130 */ f32 _130;
        /* 0x134 */ f32 _134;
        /* 0x138 */ f32 _138;
        /* 0x13c */ f32 _13c;
        /* 0x140 */ f32 _140;
        /* 0x144 */ f32 _144;
        /* 0x148 */ f32 _148;
        /* 0x14c */ u8 _14c[0x158 - 0x14c];
        /* 0x158 */ f32 _158;
        /* 0x15c */ f32 _15c;
        /* 0x160 */ f32 _160;
        /* 0x164 */ f32 _164;
        /* 0x168 */ u8 _168[0x180 - 0x168];
    };
    KSYS_CHECK_SIZE_NX150(Node, 0x180);

    // 0x7100d87be4: _8c bit 4 (set by the BoneControl "active" requests: sub_7100D85794 / D857B0).
    bool sub_7100D87BE4() const;

    // 0x7100d89618 / 969c / 971c / 977c: set the L / R / U / D limit ratio (the current limits of all
    // nodes are `value / ratio * base`; D and L are negated).
    void sub_7100D89618(const f32& value);
    void sub_7100D8969C(const f32& value);
    void sub_7100D8971C(const f32& value);
    void sub_7100D8977C(const f32& value);
    // 0x7100d8a9d0 / 9ec: set _9c / _a4 unless the value is above 1.
    void sub_7100D8A9D0(const f32& value);
    void sub_7100D8A9EC(const f32& value);
    // 0x7100d8aa08 / aa60: set the 0x144 / 0x148 values of all nodes from the 0x13c / 0x140 base
    // values and the ratios _c8 / _cc; 0x7100d8aab8 / ab00: copy the base values.
    void sub_7100D8AA08(const f32& value);
    void sub_7100D8AA60(const f32& value);
    void sub_7100D8AAB8();
    void sub_7100D8AB00();
    // Sums of one current value over the first _28 nodes (0x7100d8a25c ... 0x7100d8a64c: 0x104, 0x108,
    // 0x10c, 0x110, 0x124, 0x128, 0x12c, 0x130).
    f32 sub_7100D8A25C() const;
    f32 sub_7100D8A2EC() const;
    f32 sub_7100D8A37C() const;
    f32 sub_7100D8A40C() const;
    f32 sub_7100D8A49C() const;
    f32 sub_7100D8A52C() const;
    f32 sub_7100D8A5BC() const;
    f32 sub_7100D8A64C() const;
    // 0x7100d8a7fc: the 0x138 value of node `idx` (0 if out of range).
    f32 sub_7100D8A7FC(const s32& idx) const;

    // 0x7100d86af0 / 86bd8 (called by Unk_7100d8557c::sub_7100D8561C / sub_7100D85644; not decompiled).
    void sub_7100D86AF0();
    void sub_7100D86BD8();
    // 0x7100d86170 (not decompiled): builds the nodes from the res::BoneControl data.
    bool sub_7100D86170(res::BoneControl* res, sead::Heap* heap);
    // 0x7100d87bf0 / 0x7100d87264 (not decompiled): compute the controller's current weight.
    void sub_7100D87BF0(f32* weight);
    void sub_7100D87264(f32* weight);

    // 0x7100d88ec8 (not decompiled): the actor's riding-related offset + _94.
    f32 sub_7100D88EC8() const;
    void sub_7100D88CF4(sead::Vector3f* out) const;
    void sub_7100D892C4(sead::Vector3f* out) const;
    void sub_7100D89348(const f32& a1, const f32& a2);
    f32 sub_7100D8A6DC() const;
    f32 sub_7100D8A76C() const;
    void sub_7100D8A830(const f32& value, bool a2);
    void sub_7100D8A904(const f32& value, bool a2);

    /* 0x00 */ Actor* mActor;
    /* 0x08 */ sead::Vector3f _8;
    /* 0x14 */ u32 _14;
    // The nodes (`_18.size()` of them) and the number of active nodes (_28).
    /* 0x18 */ sead::Buffer<Node> _18;
    /* 0x28 */ s32 _28;
    /* 0x30 */ gsys::BoneAccessKeyEx _30;
    /* 0x68 */ sead::Vector3f _68;
    /* 0x74 */ sead::Vector3f _74;
    /* 0x80 */ sead::Vector3f _80;
    /* 0x8c */ u16 _8c;
    /* 0x90 */ f32 _90;
    /* 0x94 */ f32 _94;
    /* 0x98 */ f32 _98;
    /* 0x9c */ f32 _9c;
    /* 0xa0 */ f32 _a0;
    /* 0xa4 */ f32 _a4;
    // Ratios the limits are scaled by: _a8 (L), _ac (R), _b0 (U), _b4 (D), _c8 / _cc (the 0x13c / 0x140
    // pairs); _a8 / _ac / _b0 are also the sums of the current L / R / U limits.
    /* 0xa8 */ f32 _a8;
    /* 0xac */ f32 _ac;
    /* 0xb0 */ f32 _b0;
    /* 0xb4 */ f32 _b4;
    /* 0xb8 */ f32 _b8;
    /* 0xbc */ f32 _bc;
    /* 0xc0 */ f32 _c0;
    /* 0xc4 */ f32 _c4;
    /* 0xc8 */ f32 _c8;
    /* 0xcc */ f32 _cc;
    /* 0xd0 */ f32 _d0;
    /* 0xd4 */ u32 _d4;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d860d8, 0xd8);

// Size 0x48. ctor 0x7100d83054.
class Unk_7100d83054 {
public:
    explicit Unk_7100d83054(Actor* actor);

    // Not decompiled (0x7100d83090 builds the controller; the others are called by Unk_7100d8557c).
    bool sub_7100D83090(res::BoneControl* res, sead::Heap* heap);
    void sub_7100D838A8();
    void sub_7100D839A8();
    void sub_7100D83A0C(const f32& weight);
    void sub_7100D84C2C(const f32& weight);
    void sub_7100D84E14();

    /* 0x00 */ Actor* mActor;
    /* 0x08 */ sead::Vector3f _8;
    /* 0x14 */ f32 _14;
    /* 0x18 */ f32 _18;
    /* 0x1c */ f32 _1c;
    /* 0x20 */ f32 _20;
    /* 0x24 */ u32 _24;
    /* 0x28 */ f32 _28;
    /* 0x2c */ u32 _2c;  // not initialised by the ctor
    /* 0x30 */ s32 _30;
    /* 0x38 */ void* _38;
    /* 0x40 */ s32 _40;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d83054, 0x48);

// Size 0x130 (BoneControl::init: new(0x130)). ctor 0x7100d8557c.
class Unk_7100d8557c {
public:
    explicit Unk_7100d8557c(Actor* actor);

    /// Sets _10._8 and _e8._8.
    void sub_7100D8571C(const sead::Vector3f& pos);
    void sub_7100D85750();
    void sub_7100D85774();
    void sub_7100D85794();
    void sub_7100D857B0();
    // 0x7100d855b4 / 0x7100d85600: sets the weight _8 (and _c) if both controllers are active.
    void sub_7100D855B4(const f32& value);
    void sub_7100D85600(const f32& value);
    // 0x7100d855f0 / 0x7100d855f8: forward to the controllers' builders.
    bool sub_7100D855F0(res::BoneControl* res, sead::Heap* heap);
    bool sub_7100D855F8(res::BoneControl* res, sead::Heap* heap);
    void sub_7100D8561C();
    void sub_7100D85644();
    void sub_7100D8566C();
    void sub_7100D856C4();
    // 0x7100d85ef4: sets / clears bit 0x20 of both controllers' flag words.
    void sub_7100D85EF4(bool on);

    /* 0x000 */ Actor* mActor;
    /* 0x008 */ f32 _8 = 1.0f;
    /* 0x00c */ f32 _c = 1.0f;
    /* 0x010 */ Unk_7100d860d8 _10;
    /* 0x0e8 */ Unk_7100d83054 _e8;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d8557c, 0x130);

// Actor::mBoneControl (CSV: ActorBoneControl). Size 8 (Actor::init: new(8)).
class BoneControl {
public:
    BoneControl();

    bool init(Actor* actor, res::BoneControl* res, sead::Heap* heap);
    // 0x7100d82f50: destroys _0 (not decompiled).
    void sub_7100D82F50();
    // Forwarders to _0 (if it is set).
    void sub_7100D82F94();  // _0->sub_7100D85644()
    void sub_7100D82FA4();  // _0->sub_7100D8566C()
    void sub_7100D82FB4();  // _0->sub_7100D85794()
    // 0x7100d82fc4: _0->sub_7100D857B0() if _0 is set (declaration only).
    void sub_7100D82FC4();
    void sub_7100D82FD4(bool a1);  // _0->_10 / _e8 (sub_7100D860AC; not decompiled)
    // Sets _0->_10._d0 and _0->_e8._28.
    void sub_7100D82FE8(f32 value);

    /* 0x0 */ Unk_7100d8557c* _0 = nullptr;
};
KSYS_CHECK_SIZE_NX150(BoneControl, 0x8);

bool sub_7100D83014(sead::Vector3f* out, const BoneControl* bone_control);
// 0x7100d82ffc: the spine controller (BoneControl::_0->_10) or nullptr (`bone_control` may be null).
Unk_7100d860d8* sub_7100D82FFC(BoneControl* bone_control);

}  // namespace act

}  // namespace ksys
