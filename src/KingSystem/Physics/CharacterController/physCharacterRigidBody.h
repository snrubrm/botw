#pragma once

#include <Havok/Physics2012/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Constructor 0x7100f69018 and vtable 0x71024f6098 identify the native bases.
class CharacterRigidBody : public hkpCharacterRigidBody {
public:
    HK_DECLARE_CLASS_ALLOCATOR(CharacterRigidBody)
    explicit CharacterRigidBody(const hkpCharacterRigidBodyCinfo& info);
    ~CharacterRigidBody() override;
    void getSupportInfo(const hkStepInfo& step, hkArray<SupportInfo>& support) override;
    void getGround(const hkArray<SupportInfo>& support, hkBool use_dynamic,
                   hkpSurfaceInfo& surface) override;

    // Derived constructor reuses the native tail padding.
    f32 _88;
    f32 _8c;
};
KSYS_CHECK_SIZE_NX150(CharacterRigidBody, 0x90);
static_assert(offsetof(CharacterRigidBody, _88) == 0x88);
static_assert(offsetof(CharacterRigidBody, _8c) == 0x8c);

}  // namespace ksys::phys
