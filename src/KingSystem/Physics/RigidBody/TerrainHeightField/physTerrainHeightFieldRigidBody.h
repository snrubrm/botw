#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

// Complete factory 1223864 allocates 18 bytes. Its two-slot table is 25158E8;
// independent divided-mesh and map-patcher lifetimes own and delete these wrappers.
class Unk_71025158e8 {
public:
    virtual ~Unk_71025158e8();
    void sub_7101223EC4();
    void sub_7101223F80();
    void sub_7101223F90();
    void sub_7101223FA0();
    bool sub_7101223FB4() const;
    void sub_7101223FC4(SystemGroupHandler* handler);

private:
    /* 0x08 */ RigidBody* mRigidBody = nullptr;
    // The full producer stores a Havok shape here; its concrete interface stays opaque.
    u8 _10[8];
};
KSYS_CHECK_SIZE_NX150(Unk_71025158e8, 0x18);

class TerrainHeightFieldRigidBody : public RigidBody {
    SEAD_RTTI_OVERRIDE(TerrainHeightFieldRigidBody, RigidBody)
public:
    bool getD8() const { return _d8; }

private:
    void* _d0{};
    bool _d8 = false;
};

}  // namespace ksys::phys
