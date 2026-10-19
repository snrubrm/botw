#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>

namespace sead {
class Heap;
}

namespace agl::lght {
class LocalLightMapObj;
}

namespace gsys {

class EffectModelDrawMgr;
class Model;
class ModelDrawObj;
class ModelResource;
class ModelScene;

// Native 0x7100c55364 (initialize), 0x7100c555f0 (createModel), 0x7100c5571c (addInstance) and
// 0x7100c558bc (pushBack) establish the class. The manager's entry array is
// sead::Buffer<EffectModelDrawUnit> (0x7100c55a5c), so the unit is the 0x50-byte record; its
// inline clear() sequence repeats in sead::Buffer<EffectModelDrawUnit>::freeBuffer.
class EffectModelDrawUnit {
public:
    // 0x7100c55c74's caller (ksys::eft::EffectModelData::addEffectModel_0 0x7100d9f8ac) fills this
    // 0x28-byte record before calling EffectModelDrawMgr::addModel. createModel 0x7100c555f0 forwards
    // +0x00 into Model::CreateArg::_4, binds +0x08 as the scene and passes +0x10/+0x18/+0x20 to
    // Model::create; initialize 0x7100c55364 reads +0x04 as an element count.
    struct CreateArg {
        s32 _0;                     // +0x00
        u32 _4;                     // +0x04
        ModelScene* mModelScene;    // +0x08
        ModelResource* mResource;   // +0x10
        const char** mNames;        // +0x18
        u32 mCount;                 // +0x20
    };
    static_assert(sizeof(CreateArg) == 0x28);

    // The record is not polymorphic but has a real teardown: sead::Buffer<EffectModelDrawUnit>::
    // freeBuffer 0x7100c55a5c destroys the records through the element destructor, whose body is the
    // same sequence execDeleteModel 0x7100c55e50 inlines.
    ~EffectModelDrawUnit();
    // Inline-only in the original; name is a guess. Repeats in sead::Buffer<EffectModelDrawUnit>::
    // freeBuffer 0x7100c55a5c and the manager's execDeleteModel 0x7100c55e50.
    void clear();

    // 0x7100c55364 / 0x7100c555f0 / 0x7100c5571c / 0x7100c558bc (declared only; bodies U).
    bool initialize(const CreateArg& arg, sead::Heap* heap);
    bool createModel(const CreateArg& arg, sead::Heap* heap);
    bool addInstance(EffectModelDrawMgr* mgr, u32, const sead::Matrix34f&, const sead::Vector3f&,
                     const agl::lght::LocalLightMapObj*, u16);
    void pushBack(EffectModelDrawMgr* mgr);

    Model* mModel;   // +0x00, released through Model::sub_7100BF69F8
    void* _8;        // +0x08, cleared by clear()
    void* _10;       // +0x10, cleared by clear()
    u32 mUnkCount;   // +0x18, set from CreateArg::_4 by initialize
    u32 mUnkCount2;  // +0x1c
    u32 _20;         // +0x20, reset by preCalc
    u32 _24;         // +0x24
    u16* _28;        // +0x28, cleared by clear() and zeroed element-wise by preCalc
    void* _30;       // +0x30, cleared by clear()
    u32 mFlags;      // +0x38, bit 0 owned, bit 1 delete requested, bit 2 used
    u32 _3c;         // +0x3c
    void* _40;       // +0x40, deleted by clear()
    u8 _48[8];       // +0x48
};
static_assert(sizeof(EffectModelDrawUnit) == 0x50);

// Native ctor 0x7100c559dc, size 0xa8.
class EffectModelDrawMgr {
public:
    EffectModelDrawMgr();
    ~EffectModelDrawMgr();

    // 0x7100c55b28 (declared only): allocates the unit buffer and the model draw object array.
    void initialize(int, int, int, sead::Heap*);
    // 0x7100c55c74: returns the index of the first free record after initializing it, or -1.
    int addModel(EffectModelDrawUnit::CreateArg arg, sead::Heap* heap);
    bool requestDeleteModel(u32 id);
    bool execDeleteModel(u32 id);
    // 0x7100c55f64 / 0x7100c5610c: clear / refresh the used records before and after drawing.
    void preCalc();
    void postCalc();
    // 0x7100c56000: adds an instance to the owned record `id`; returns false when it is absent or
    // marked for deletion.
    bool addInstance(u32 id, u32 type, const sead::Matrix34f& matrix, const sead::Vector3f& pos,
                     const agl::lght::LocalLightMapObj* light, u16);

private:
    u32 mCapacity;  // +0x00, addModel rejects id >= mCapacity
    u32 _4;         // +0x04, count of the ModelDrawObj array at +0x20
    u16 _8;         // +0x08
    u8 _a[6];
    sead::Buffer<EffectModelDrawUnit> mEntries;  // +0x10 size, +0x18 buffer
    ModelDrawObj* mModelDrawObjs;                // +0x20
    sead::CriticalSection mCS;                   // +0x28
    sead::CriticalSection mCS2;                  // +0x68
};
static_assert(sizeof(EffectModelDrawMgr) == 0xa8);

}  // namespace gsys
