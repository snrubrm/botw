#pragma once

#include <prim/seadBitFlag.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
enum class MotionType;
}

namespace ksys::phys {

class RigidBody;

// TODO: incomplete (0x2a8 bytes; ctor 0x7100f5d8b8)
class CharacterController {
public:
    virtual ~CharacterController();

    void sub_7100F5EC30();
    void sub_7100F60604();
    void enableContactLayer(ContactLayer);
    void disableContactLayer(ContactLayer);
    void sub_7100F605F0();

    act::MotionType sub_7100F5F0E4() const;
    void sub_7100F5F458(act::MotionType type);

    bool sub_7100F636EC() const;
    void sub_7100F636B0(bool clear);
    bool sub_7100F63590() const;
    void sub_7100F63554(bool clear);
    bool sub_7100F62D34() const;
    void sub_7100F62CA8(bool clear);

    RigidBody* mRigidBody;
    u8 _10[0x118 - 0x10];
    sead::BitFlag32 mFlags;
};

}  // namespace ksys::phys
