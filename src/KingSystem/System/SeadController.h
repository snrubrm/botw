#pragma once

#include <basis/seadTypes.h>
#include <container/seadTreeNode.h>
#include <controller/seadController.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// CSV name (ctor 0x7100d9d628, dtor 0x7100d9d6f0; vtable 0x71024dd518). A sead::Controller with
// KingSystem calc (0x7100d9db20) / calcImpl_ (0x7100d9ddf4). Size from the subclass ctor
// 0x71008bf5dc, whose first member is at 0x1f0. Not decompiled: the ctor takes one 4-byte value
// passed in a 64-bit register (SEAD_ENUM-like, stored at 0x19c) and gets the sead::ControllerMgr
// from a global; the members (a sead::TreeNode at 0x1a8, ...) are not declared yet.
class SeadController : public sead::Controller {
    SEAD_RTTI_OVERRIDE(SeadController, sead::Controller)
public:
    // 0x71011f931c / 0x71011f9328 (CSV SeadController::getInstance / setInstance; the instance pointer is a file-local
    // global at 0x7102652558)
    static SeadController* getInstance();
    static void setInstance(SeadController* controller);

    // Unnamed accessors (lane4 s47; placeholder names): the flag word at +0x188 and the values at +0x190 / 0x194 / 0x1a4.
    u32 sub_7100D9D874() const;
    void sub_7100D9D8C0(bool on);   // flag 0x80
    void sub_7100D9D8DC(u32 value);  // _190
    void sub_7100D9D8E4();  // accumulates controller masks, then applies them
    void sub_7100D9DAC8(u32 value);  // _194
    void sub_7100D9DAD8();           // clears flag 0x1
    void sub_7100D9DAE8();           // clears flag 0x2
    void sub_7100D9DB04(bool on);   // flag 0x10
    void sub_7100D9DF60();           // clears flag 0x20
    // Vtable 0x71024dd518 slots 9 - 11, after sead::Controller's setIdle_ (placeholder names; argument lists from
    // the bodies: slot 9 returns a SafeString by value, slot 10 is empty).
    virtual sead::SafeString sub_7100D9DF34() const;
    virtual void sub_7100D9DF54();
    virtual bool sub_7100D9DF58();

    // 0x7100d9daf8: appends the tree node of `child` (+0x1a8) to this controller's.
    void sub_7100D9DAF8(SeadController* child);

private:
    u8 _178[0x188 - 0x178];
    u32 _188;
    u8 _18c[4];
    u32 _190;
    u32 _194;
    u8 _198[0x1a4 - 0x198];
    u32 _1a4;
    sead::TTreeNode<SeadController*> mTreeNode;
    u8 _1d0[0x1f0 - 0x1d0];
};
KSYS_CHECK_SIZE_NX150(SeadController, 0x1f0);

}  // namespace ksys
