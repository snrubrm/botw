#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Visualize/hkProcess.h>

class hkpWorld;

// Third base of hkpWorldViewerBase at +0x40 (vtable 0x7102544490 + 0xc8).
class hkpPhysicsContextWorldListener {
public:
    virtual ~hkpPhysicsContextWorldListener() {}
    virtual void worldAddedCallback(hkpWorld* newWorld) = 0;
    virtual void worldRemovedCallback(hkpWorld* newWorld) = 0;
};

class hkpPhysicsContext : public hkReferencedObject {
public:
    // 0x7101675c68: removes cb from the listener array at +0xe8 (swap with the last entry).
    void removeWorldListener(hkpPhysicsContextWorldListener* cb);
};

// Base of the visual debugger world viewers: vtable 0x7102544490, D2 0x7101684e54 (83 viewer
// destructors call it), D0 0x7101685054 (size 0x50).
class hkpWorldViewerBase : public hkReferencedObject,
                           public hkProcess,
                           protected hkpPhysicsContextWorldListener {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpWorldViewerBase)

    ~hkpWorldViewerBase() override;

    void getConsumableCommands(hkUint8*& commands, int& numCommands) override;
    void consumeCommand(hkUint8 command) override;
    void step(hkReal frameTimeInMs) override;
    void worldAddedCallback(hkpWorld* newWorld) override;
    void worldRemovedCallback(hkpWorld* newWorld) override;

protected:
    hkpPhysicsContext* m_context;
};
static_assert(sizeof(hkpWorldViewerBase) == 0x50);
