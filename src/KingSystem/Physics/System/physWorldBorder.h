#pragma once

#include <Havok/Physics2012/Dynamics/World/BroadPhaseBorder/hkpBroadPhaseBorder.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// The complete 2523358 table contains the primary and all three listener tables.
// World creation 12B3948 allocates 80 bytes and supplies the layer and Havok world.
class WorldBorder : public hkpBroadPhaseBorder {
public:
    HK_DECLARE_CLASS_ALLOCATOR(WorldBorder)

    WorldBorder(ContactLayerType layer, hkpWorld* world);
    ~WorldBorder() override = default;

    void maxPositionExceededCallback(hkpEntity* body) override;

private:
    /* 0x78 */ ContactLayerType mLayer;
};
KSYS_CHECK_SIZE_NX150(WorldBorder, 0x80);

}  // namespace ksys::phys
