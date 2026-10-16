#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpConstraintInstance;
struct hkpConstraintBrokenEvent;
struct hkpConstraintRepairedEvent;

// Slot order from hkpWorldCallbackUtil's constraint fire functions 0x710161c17c / c378 / c574 /
// c770 / c970 (timer names conAddCb, conRemCb, conVioCb, conBrokenCb, conRepairedCb call slots
// +0x10, +0x18, +0x28, +0x30, +0x38). Game listener vtable 0x71024f61a8 has the same eight slots;
// its deleting destructor 0x7100f6ade8 frees 8 bytes through the Havok heap.
class hkpConstraintListener {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpConstraintListener)

    virtual ~hkpConstraintListener() {}
    virtual void constraintAddedCallback(hkpConstraintInstance* constraint) {}
    virtual void constraintRemovedCallback(hkpConstraintInstance* constraint) {}
    virtual void constraintDeletedCallback(hkpConstraintInstance* constraint) {}
    virtual void constraintViolatedCallback(hkpConstraintInstance* constraint) {}
    virtual void constraintBreakingCallback(const hkpConstraintBrokenEvent& event) {}
    virtual void constraintRepairedCallback(const hkpConstraintRepairedEvent& event) {}
};
