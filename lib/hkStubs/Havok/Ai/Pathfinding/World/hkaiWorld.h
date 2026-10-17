#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Common/Base/Types/hkRefPtr.h>

class hkaiSilhouetteGenerator;
class hkaiObstacleGenerator;
class hkaiStreamingCollection;
class hkaiNavMeshCutter;
class hkaiDynamicNavMeshQueryMediator;

// Reflection initializer 0x710177600c identifies the referenced-object parent
// and 0x2b0 size. The member records at 0x710255e6e0 identify the generator
// arrays at 0xb8/0xc8; unidentified regions retain padding.
class hkaiWorld : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaiWorld)
    // The reflected type-info constructor at 0x7101555c80 takes the finish-load flag.
    explicit hkaiWorld(hkFinishLoadedObjectFlag flag);
    ~hkaiWorld() override;

    // Original add/remove silhouette and obstacle operations. Address spellings
    // preserve the unproved method names; the reflection records prove their types.
    void sub_710153AABC(hkaiSilhouetteGenerator* generator);
    void sub_710153AC2C(hkaiSilhouetteGenerator* generator);
    void sub_710151E18C(hkaiObstacleGenerator* generator);
    void sub_710151E2EC(hkaiObstacleGenerator* generator);

    // Descriptive accessor name. Native 0x71015568c8 / 0x71015568d0 return the
    // reflected dynamicNavMeshMediator reference at +0x40.
    hkaiDynamicNavMeshQueryMediator* getMediator();
    const hkaiDynamicNavMeshQueryMediator* getMediator() const;

    // Reflection records 255e708/255e730 identify the pointer types. The
    // constructor 15555b8 replaces each with a newly allocated referenced
    // object and releases the previous reference, proving hkRefPtr ownership.
    hkVector4 m_up;
    hkRefPtr<hkaiStreamingCollection> m_streamingCollection;
    hkRefPtr<hkaiNavMeshCutter> m_cutter;

private:
    hkUint8 _30[0x40 - 0x30];
    hkRefPtr<hkaiDynamicNavMeshQueryMediator> m_mediator;
    hkUint8 _48[0xb8 - 0x48];
    hkArray<hkRefPtr<hkaiSilhouetteGenerator>> m_silhouetteGenerators;
    hkArray<hkRefPtr<hkaiObstacleGenerator>> m_obstacleGenerators;
    hkUint8 _d8[0x2b0 - 0xd8];
};
static_assert(sizeof(hkaiWorld) == 0x2b0);
