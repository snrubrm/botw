#pragma once

#include <Havok/Ai/Pathfinding/Astar/hkaiAstarEdgeFilter.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Initializer 0x7100f77b98 installs the table at 0x71024f6bb8 and sets type 1.
// Deleting destructor 0x7100f7e414 establishes the 0x10-byte extent. Only the
// known callback prefix is declared; the final operation at +0x40 is unresolved,
// so this class's lifetime and vtable are not defined here.
class Unk_71024f6ba8 : public hkaiAstarEdgeFilter {
public:
    ~Unk_71024f6ba8() override;
    using hkaiAstarEdgeFilter::isEnabledMaybe;
    // 0x7100f7d674: game mesh traversal filter. The volume callback is inherited.
    bool isEnabledMaybe(const NavMeshIsEnabledCallbackContext& context) const override;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f6ba8, 0x10);

// The default game filter stored at 0x710260ddf0; initialized by 0x7100f77b98.
extern Unk_71024f6ba8 sUnk_710260ddf0;

}  // namespace ksys::phys
