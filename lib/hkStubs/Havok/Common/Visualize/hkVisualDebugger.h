#pragma once

#include <Havok/Common/Base/hkBase.h>

// Created by ksys::phys::System in 0x710121542c (ctor 0x71016b239c). Only the slots used by the game are named.
class hkVisualDebugger : public hkReferencedObject {
public:
    // Slots 5..7 (vtable +0x28..+0x38): not identified yet.
    virtual void m5();
    virtual void m6();
    virtual void m7();
    // Slot 8 (vtable +0x40): System::sub_7101216454 calls it with the frame time in milliseconds.
    virtual void step(hkReal frameTimeInMs = 0);
};
