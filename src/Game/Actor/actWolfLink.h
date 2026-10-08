#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <prim/seadEnum.h>
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/System/Timer.h"

// 2026-10-07: WolfLink's factory installs these two message senders at 0x1620 / 0x1638.
// Both have the original shared base D1 (0x710001bfec) and a null message payload; m2 is
// defined out of line in actWolfLink.cpp (its TU also emits the 4-byte D0s, which only delete).
class Unk_71023d2f68 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override;
};
class Unk_71023d2f90 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override;
};

namespace ksys::res {
class GParamListObjectWolfLink;
}

namespace uking::act {

// Name from the CSV (WolfLink::*); vtable 0x71023d2948 (181 slots, no new virtuals over Enemy).
// TODO: incomplete. Factory size 0x16a0 (WolfLink::construct, which inlines the ctor).
class WolfLink : public Enemy {
    SEAD_RTTI_OVERRIDE(WolfLink, Enemy)
public:
    explicit WolfLink(const CreateArg& arg);
    ~WolfLink() override;

protected:
    InitResult init_() override;
    bool startPreparingForPreDelete_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override { Enemy::onPreDeleteStart_(arg); }
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    s32 getMaxLife() override { return _1690; }
    bool shouldUnload(s32* a1) override;
    void calcMaybe() override;
    bool m81(const ksys::Message& message) override;
    void m156() override;
    s32 getBaseAtkPower() override;

    // Index type of _14f8 (19 values; no text in the executable, names unknown).
    SEAD_ENUM(Idx14f8, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,
              _17, _18)

    // 0x71002f2e78 (not decompiled; 720 bytes, switch on idx). Placeholder name; return type unknown
    // (WolfLinkWarp::leave_ tail-calls it with Idx14f8::_10).
    void sub_71002F2E78(Idx14f8 idx);
    // 0x71002f4428 (not decompiled): `s32(p->_850 + p->_870 * (getMaxLife-like virtual 0xf0 / 4))` from the
    // parameter object _1680.
    s32 sub_71002F4428();
    bool sub_71002F420C();
    u32 sub_71002F440C();
    // 0x71002f3234 / 0x71002f4b3c / 0x71002f493c / 0x71002f4a40 / 0x71002f4008 (not decompiled;
    // placeholder names and guessed signatures, from WolfLinkNormalRoot's calls).
    bool sub_71002F3234(f32 range, s32 a, s32 b, s32 c);
    void sub_71002F4B3C();
    void sub_71002F493C();
    void sub_71002F4A40(const sead::Vector3f* pos, f32 a, f32 b);
    void sub_71002F4008(ksys::act::BaseProcLink* link, s32 a);

    // Fields are accessed directly by AI classes.
    /* 0x14c8 */ u8 _14c8[0x14f8 - 0x14c8];  // ctor 0x710071edf8(this + 0x14c8, this)
    /* 0x14f8 */ sead::SafeArray<ksys::Timer, 19> _14f8;  // zero-initialised (memset)
    /* 0x15dc */ u32 _15dc;
    /* 0x15e0 */ u8 _15e0[0x1608 - 0x15e0];  // object with vtable (GOT 0x7102584a68)
    // 2026-10-07: preDelete2_ destroys the link in each 0x28-byte array entry.
    struct Entry1608 {
        // 2026-10-07: sub_71002F420C searches this unsigned actor id.
        u8 _0[0xc];
        u32 mActorId;
        ksys::act::BaseProcLink _10;
        u8 _20[8];
    };
    /* 0x1608 */ sead::Buffer<Entry1608> _1608;
    /* 0x1618 */ u32 _1618;
    /* 0x1620 */ Unk_71023d2f68 _1620{this, 0x80000af};
    /* 0x1638 */ Unk_71023d2f90 _1638{this, 0x80000b0};
    /* 0x1650 */ u8 _1650[0x1680 - 0x1650];
    /* 0x1680 */ const ksys::res::GParamListObjectWolfLink* _1680;  // the WolfLink GParam object
    /* 0x1688 */ u32 _1688;
    /* 0x168c */ s32 _168c;
    /* 0x1690 */ s32 _1690;
    /* 0x1694 */ u32 _1694;
    /* 0x1698 */ u16 _1698;
    /* 0x169a */ u8 _169a;
};
KSYS_CHECK_SIZE_NX150(WolfLink, 0x16a0);

}  // namespace uking::act

// 0x7100742e30 (CSV name; namespace unknown): true if the Wolf Link amiibo cannot be used right now.
bool cannotUseWolfLinkAmiibo();
