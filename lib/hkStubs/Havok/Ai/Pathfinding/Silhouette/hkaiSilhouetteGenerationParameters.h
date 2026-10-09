#pragma once

#include <Havok/Ai/Pathfinding/Silhouette/hkaiSilhouetteReferenceFrame.h>

// Reflection 17750f0 records 255d970..255da10 identify every member.
// Full world constructor 15555b8 initializes this storage at world + 0x60.
struct hkaiSilhouetteGenerationParameters {
    hkReal m_extraExpansion;
    hkReal m_bevelThreshold;
    hkReal m_maxSilhouetteSize;
    hkReal m_simplify2dConvexHullThreshold;
    hkaiSilhouetteReferenceFrame m_referenceFrame;
};
static_assert(sizeof(hkaiSilhouetteGenerationParameters) == 0x40);
static_assert(offsetof(hkaiSilhouetteGenerationParameters, m_referenceFrame) == 0x10);
