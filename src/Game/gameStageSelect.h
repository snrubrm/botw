#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace uking {

// The debug stage select menu (CSV uking::StageSelect, ctor 0x7ccff0, vtable 0x710245bf40; its RTTI functions are
// 0x7d0230 / 0x7d02a0). Placeholder: only the virtuals that its two states (active / move) call through member
// function pointers are declared, in vtable order.
class StageSelect {
public:
    virtual ~StageSelect();

    // 0x7cf2f4 / 0x7cf2f8 / 0x7d0218 / 0x7d02fc
    virtual void activeEnter();
    virtual void activeRun();
    virtual void activeLeave();
    virtual bool activeReenter(void* arg);
    // 0x7d021c / 0x7d0220 / 0x7d022c / 0x7d0304
    virtual void moveEnter();
    virtual void moveRun();
    virtual void moveLeave();
    virtual bool moveReenter(void* arg);

private:
    u8 _8[0x10 - 0x8];
    /* 0x010 */ sead::SafeString _10;
    u8 _20[0x4f0 - 0x20];
    /* 0x4f0 */ sead::FixedSafeString<0x100> _4f0;
};

}  // namespace uking
