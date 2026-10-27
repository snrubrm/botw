#pragma once

#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "gsys/gsysGPUStressAnalyzer.h"

namespace sead
{
class Heap;
class WorkerMgr;
}

namespace agl
{
class DrawContext;
}

namespace gsys
{

class G3dResModelEx;
class Model;
class ModelScene;

// Model manager singleton (CSV 0x7100c01c18 .. 0x7100c030b0). createInstance 0x7100c01ce8
// allocates 0x208 bytes, constructs the SingletonDisposer buffer at +8 (the vptr is at +0) and
// installs the ModelMgr vtable. It then initialises three intrusive lists at +0x190 / +0x1a8 /
// +0x1c0 with the node offsets 0x110 / 0x120 / 0x120 (stores at +0x1a4 / +0x1bc / +0x1d4).
// ModelRig::listenPropertyEventEnvObj 0x7100c83d48 walks the first list, whose elements are
// Models: it tests Model +0xf0 (mScene) before registering the model. Only that list and the
// extent are proved here; the other two lists' element types are unproved, so they stay padding.
// Vtable 0x71024ca098: slot 0 is the sead::hostio::Node stub, then D1 / D0.
class ModelMgr : public sead::hostio::Node
{
    SEAD_SINGLETON_DISPOSER(ModelMgr)

public:
    // Inlined into createInstance (0x7100c01ce8); declared only.
    ModelMgr();
    virtual ~ModelMgr();

    sead::OffsetList<Model>& getModelList() { return mModelList; }
    const sead::OffsetList<Model>& getModelList() const { return mModelList; }

    // 0x7100c030a8: nothing in the retail build.
    void createFFLTexturePerFrame(agl::DrawContext* context);
    // 0x7100c030ac: forwards to the AGL meter.
    f32 getMeterScale() const;
    // 0x7100c02cc8 (declared only): re-registers a scene with every live model.
    void rebindModelScene(const ModelScene* scene);
    // 0x7100c02d64: a rolling 11-bit XluZ pre-pass ID.
    s32 getXluZPrePassID();

    // 0x7100c0288c / 0x7100c028f0 / 0x7100c02954 / 0x7100c029b8 / 0x7100c02a1c: run one step on every
    // scene. The step's flag bit selects whether the worker manager is forwarded.
    // 0x7100c01fd4: allocates the three model arrays and the stress analyzer.
    void initialize(sead::Heap* heap, sead::Heap* debug_heap);
    // 0x7100c02a80 / 0x7100c02b00: edit every live model with the given resource (or none).
    void editAll();
    void editAll(const G3dResModelEx* res_model);

    void calcModel(sead::WorkerMgr* wm);
    void sortQueue(sead::WorkerMgr* wm);
    void calcWorld(sead::WorkerMgr* wm);
    void calcRenderView(sead::WorkerMgr* wm);
    void calcDrawBackGround(sead::WorkerMgr* wm);
    void calcGPU(sead::WorkerMgr* wm);

private:
    // Bit 0 enables the worker manager; bits 1 / 3 / 4 / 6 select the scene step.
    /* 0x28 */ u32 mFlags;
    /* 0x2c */ u8 _2c[4];
    /* 0x30 */ sead::PtrArray<Model> mArray30;
    /* 0x40 */ sead::PtrArray<ModelScene> mArray40;
    /* 0x50 */ sead::PtrArray<ModelScene> mScenes;
    /* 0x60 */ u8 _60[0x10];
    /* 0x70 */ GPUStressAnalyzer mGPUStressAnalyzer;
    /* 0xb0 */ u8 _b0[0x1c];
    /* 0xcc */ sead::Atomic<s32> mXluZPrePassId;
    /* 0xd0 */ u8 _d0[0x150 - 0xd0];
    /* 0x150 */ sead::CriticalSection mCS;

public:
    sead::CriticalSection& getCS() { return mCS; }

private:

public:
    // Walked directly by ModelRig::listenPropertyEventEnvObj (0x7100c83d48).
    /* 0x190 */ sead::OffsetList<Model> mModelList;

private:
    /* 0x1a8 */ u8 _1a8[0x1e0 - 0x1a8];
    /* 0x1e0 */ sead::hostio::Node mNode1e0;
    /* 0x1e8 */ sead::PtrArray<Model> mArray1e8;
    /* 0x1f8 */ u8 _1f8[0x208 - 0x1f8];
};
static_assert(sizeof(ModelMgr) == 0x208);
static_assert(offsetof(ModelMgr, mModelList) == 0x190);

}  // namespace gsys
