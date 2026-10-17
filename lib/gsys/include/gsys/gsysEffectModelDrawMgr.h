#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <thread/seadCriticalSection.h>

namespace gsys {

class Model;

// Native ctor 0x7100c559dc, size 0xa8. Only the record layout used by
// requestDeleteModel 0x7100c55dd8 / execDeleteModel 0x7100c55e50 is modelled.
class EffectModelDrawMgr {
public:
    struct Entry {
        // Inline-only in the original; name is a guess. execDeleteModel 0x7100c55e50 and
        // the entry-array teardown 0x7100c55a5c repeat this ownership/resource cleanup.
        void clear();

        Model* mModel;  // +0x00, released through Model::sub_7100BF69F8
        void* _8;       // +0x08, cleared by execDeleteModel
        void* _10;      // +0x10, cleared by execDeleteModel
        u8 _18[0x10];
        void* _28;      // +0x28, cleared by execDeleteModel
        void* _30;      // +0x30, cleared by execDeleteModel
        u32 mFlags;     // +0x38, bit 0 owned, bit 1 delete requested
        u32 _3c;
        void* _40;  // +0x40, deleted by execDeleteModel
        u8 _48[8];
    };
    static_assert(sizeof(Entry) == 0x50);

    EffectModelDrawMgr();
    bool requestDeleteModel(u32 id);
    bool execDeleteModel(u32 id);

private:
    u32 mCapacity;  // +0x00, requestDeleteModel rejects id >= mCapacity
    u32 _4;
    u16 _8;  // +0x08
    u8 _a[6];
    sead::Buffer<Entry> mEntries;  // +0x10 size, +0x18 buffer
    void* _20;                     // +0x20
    sead::CriticalSection mCS;     // +0x28
    sead::CriticalSection mCS2;    // +0x68
};
static_assert(sizeof(EffectModelDrawMgr) == 0xa8);

}  // namespace gsys
