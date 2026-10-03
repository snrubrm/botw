#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <prim/seadEnum.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/System/Timer.h"

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
    bool shouldUnload() override;
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
    /* 0x1608 */ u8 _1608[0x1618 - 0x1608];  // buffer (count, pointer) of 0x28-byte entries
                                             // with a BaseProcLink at +0x10; freed in preDelete2_
    /* 0x1618 */ u32 _1618;
    /* 0x1620 */ u8 _1620[0x1650 - 0x1620];  // two message listeners (base vtable 0x7102357d20)
    /* 0x1650 */ u8 _1650[0x1680 - 0x1650];
    /* 0x1680 */ void* _1680;                 // parameter object (floats at 0x810/0x830)
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
