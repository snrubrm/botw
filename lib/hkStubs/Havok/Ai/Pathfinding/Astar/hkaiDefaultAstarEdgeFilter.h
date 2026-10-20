#pragma once

#include <Havok/Ai/Pathfinding/Astar/hkaiAstarEdgeFilter.h>

// The two named callbacks at 0x710177708c / 0x71017770f0 consume the masks
// below. Deleting destructor 0x710177712c fixes the extent at 0x120. Only
// the known callback prefix is declared; do not instantiate or define its
// lifetime until the final virtual operation at vptr +0x40 is recovered.
class hkaiDefaultAstarEdgeFilter : public hkaiAstarEdgeFilter {
public:
    bool isEnabledMaybe(const NavMeshIsEnabledCallbackContext& context) const override;
    bool isEnabledMaybe(const NavVolumeIsEnabledCallbackContext& context) const override;

private:
    hkUint32 m_edgeMasks[32];
    hkUint32 m_faceMasks[32];
    hkUint32 m_volumeMask;
    hkUint8 _114[0x120 - 0x114];
};
static_assert(sizeof(hkaiDefaultAstarEdgeFilter) == 0x120);

