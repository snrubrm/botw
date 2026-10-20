#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Pattern/Singleton/hkSingleton.h>

class hkCriticalSection;
class hkDebugDisplayHandler;

// Singleton registration 16B3508 names this owner; factory 16B3474 constructs it.
class hkDebugDisplay : public hkReferencedObject, public hkSingleton<hkDebugDisplay> {
public:
    hkDebugDisplay();
    ~hkDebugDisplay() override;

    // 16B332C dispatches the local pose to each registered display handler.
    // Declaration only; method name is descriptive.
    void displayLocalPoseMaybe(int numBones, const hkInt16* parentIndices,
                               const hkQsTransform* poseLocal,
                               const hkQsTransform& worldFromModel, int id, int tag,
                               hkUint32 color);

private:
    hkArray<hkDebugDisplayHandler*> m_debugDisplayHandlers;
    hkCriticalSection* m_criticalSection;
};
static_assert(sizeof(hkDebugDisplay) == 0x28);

template <>
hkDebugDisplay* hkSingleton<hkDebugDisplay>::s_instance;

// Process registration 16B5038 stores the registered Debug Display process tag.
extern hkInt32 sUnk_7102682950;
