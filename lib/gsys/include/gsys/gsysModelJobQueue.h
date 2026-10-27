#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <mc/seadJob.h>
#include <mc/seadJobQueue.h>
#include <thread/seadCriticalSection.h>
#include <utility/aglAtomicPtrArray.h>
#include "gsys/gsysXluZPrePass.h"

namespace sead {
class WorkerMgr;
}

namespace gsys {

class Model;
class ModelScene;

// The job queue embedded in ModelScene at +0x5550. Layout from the constructor 0x7100c7e634 and
// the destructor 0x7100c7e6d0.
class ModelJobQueue {
public:
    // Jobs run by the queue (array at +0xb8, stride 0x30); invoke 0x7100c7fae4 forwards the four
    // arguments to ModelJobQueue::invoke_.
    class Job : public sead::Job {
    public:
        void invoke() override;

        ModelJobQueue* mQueue;
        s32 mArg0;
        s32 mArg1;
        s32 mArg2;
        s32 mArg3;
    };

    // Element of the buffer at +0xf8 (stride 0x3b8). The destructor destroys five
    // ModelRenderQueue members and an XluZPrePass; only the pre-pass object's offset is modelled.
    struct Unk_3b8 {
        u8 _0[0x2f8];
        XluZPrePass mXluZPrePass;
        u8 _3a0[0x3b8 - 0x3a0];
    };
    static_assert(sizeof(Unk_3b8) == 0x3b8);

    ModelJobQueue();
    virtual ~ModelJobQueue();

    void bind(Model* model);
    void unbind(Model* model);
    void invoke_(int, int, int, int);
    // 0x7100c7f5bc (declared only): sorts the queues before the scenes run sortQueue_.
    void preSort(sead::WorkerMgr* wm);
    // Inline-only in the original; name is a guess: the pre-pass object of a view's record. The
    // bounds-checked index repeats in ModelScene's draw paths and Graphics' Pfx / Opa passes.
    XluZPrePass& getXluZPrePassMaybe(s32 view) { return _f8[view].mXluZPrePass; }
    void clear();
    void swapDrawList();
    void calc(bool);
    void updateModel(bool, sead::WorkerMgr* wm);
    void updateModelUnit(sead::WorkerMgr* wm);
    void changeRequestFlag(bool, bool, bool);

    // Model::requestDraw 0x7100bf9b88 appends to this list; clear 0x7100c7f1a8 empties it.
    agl::utl::AtomicPtrArray<Model>& getDrawList() { return mDrawList; }

private:
    sead::FixedSizeJQ mJobQueue;
    u32 _a8 = 0;
    sead::Buffer<Job> mJobs;
    u16 _c0 = 4;
    u16 _c2 = 4;
    u8 _c4[4];
    u32 _c8 = 0;
    sead::PtrArray<Model> mModels;
    agl::utl::AtomicPtrArray<Model> mDrawList;
    u8 _f0[8];
    sead::Buffer<Unk_3b8> _f8;
    agl::utl::AtomicPtrArray<Model> _108;
    u32 _118 = 0;
    // calc 0x7100c7f1d0 sets or clears bit 1.
    u32 mFlags = 0x79;
    u16 _120 = 0;
    u8 _122 = 7;
    u8 _123 = 7;
    u8 _124 = 7;
    u8 _125[0x130 - 0x125];
    sead::CriticalSection mCS;
};
static_assert(sizeof(ModelJobQueue) == 0x170);

}  // namespace gsys
