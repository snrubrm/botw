#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Common/Base/Types/hkRefPtr.h>

class hkaiSilhouetteGenerator;
class hkaiObstacleGenerator;

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

private:
    hkVector4 m_up;
    hkUint8 _20[0xb8 - 0x20];
    hkArray<hkRefPtr<hkaiSilhouetteGenerator>> m_silhouetteGenerators;
    hkArray<hkRefPtr<hkaiObstacleGenerator>> m_obstacleGenerators;
    hkUint8 _d8[0x2b0 - 0xd8];
};
static_assert(sizeof(hkaiWorld) == 0x2b0);
