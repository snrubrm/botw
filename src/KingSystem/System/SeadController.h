#pragma once

#include <basis/seadTypes.h>
#include <controller/seadController.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// CSV name (ctor 0x7100d9d628, dtor 0x7100d9d6f0; vtable 0x71024dd518). A sead::Controller with
// KingSystem calc (0x7100d9db20) / calcImpl_ (0x7100d9ddf4). Size from the subclass ctor
// 0x71008bf5dc, whose first member is at 0x1f0. Not decompiled: the ctor takes one 4-byte value
// passed in a 64-bit register (SEAD_ENUM-like, stored at 0x19c) and gets the sead::ControllerMgr
// from a global; the members (a sead::TreeNode at 0x1a8, ...) are not declared yet.
class SeadController : public sead::Controller {
public:
    // 0x71011f931c / 0x71011f9328 (CSV SeadController::getInstance / setInstance; the instance pointer is a file-local
    // global at 0x7102652558)
    static SeadController* getInstance();
    static void setInstance(SeadController* controller);

private:
    u8 _178[0x1f0 - 0x178];
};
KSYS_CHECK_SIZE_NX150(SeadController, 0x1f0);

}  // namespace ksys
