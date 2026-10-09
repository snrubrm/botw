#pragma once

#include <Havok/Common/Base/hkBase.h>

// Reflection 1775e00 names this 0x60-byte referenced object. Full cache
// producer 1531ca0 allocates it; 1531f80 fills both arrays and cached frame.
// Full native destructors f80864/f808f4 release the 4- and 16-byte arrays.
// Its complete five-slot table 24f6e30 adds no virtuals to hkReferencedObject.
class hkaiConvexSilhouetteSet : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaiConvexSilhouetteSet)
    ~hkaiConvexSilhouetteSet() override;

    hkArray<hkVector4> m_vertexPool;
    hkArray<hkInt32> m_silhouetteOffsets;
    hkQTransform m_cachedTransform;
    hkVector4 m_cachedUp;
};
static_assert(sizeof(hkaiConvexSilhouetteSet) == 0x60);
static_assert(offsetof(hkaiConvexSilhouetteSet, m_vertexPool) == 0x10);
static_assert(offsetof(hkaiConvexSilhouetteSet, m_silhouetteOffsets) == 0x20);
static_assert(offsetof(hkaiConvexSilhouetteSet, m_cachedTransform) == 0x30);
static_assert(offsetof(hkaiConvexSilhouetteSet, m_cachedUp) == 0x50);
