#pragma once

#include <container/seadBuffer.h>
#include "Game/Actor/actEnemy.h"

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
    void m81() override;
    void m156() override;
    void getBaseAtkPower() override;

    // Fields are accessed directly by AI classes.
    /* 0x14c8 */ u8 _14c8[0x14f8 - 0x14c8];  // ctor 0x710071edf8(this + 0x14c8, this)
    /* 0x14f8 */ u8 _14f8[0x15e0 - 0x14f8];  // zero-initialised (memset)
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
