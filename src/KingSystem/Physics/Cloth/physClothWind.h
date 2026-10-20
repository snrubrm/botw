#pragma once

#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include "KingSystem/Physics/Cloth/physClothAction.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Placeholder name (the draft name; ClothSet stores it at ClothInstance::mWind). Constructor at 0x71013082f4,
// vtables at 0x71025201a0 / 0x71025201d8. Allocated (0x48 bytes) and enabled by ClothSet's init at 0x7101218030.
// Pushes the cloth particles towards mWind (m3).
class ClothWind : public sead::hostio::Node, public ClothActionHandle {
public:
    // Placeholder: the wind state that 0x710121a3e4 builds on the stack (floats at 0xc..0x38).
    struct Arg;

    ClothWind(ClothSet* set, s16 index);
    ~ClothWind() override;
    // 0x71013083c4 (placeholder name; declared only): updates mWind and enables or disables the action.
    virtual void m4(const Arg& arg, f32 delta_time);
    void m3(Unk_71025335A8* sim_cloth, hkVector4f* output, hkReal timestep) override;

    sead::Vector3f mWind;
    f32 _30 = 3.0f;
    u32 _34 = 0;
    u32 _38 = 0;
    u32 _3c = 0;
    u32 _40 = 0;
};
KSYS_CHECK_SIZE_NX150(ClothWind, 0x48);

}  // namespace ksys::phys
