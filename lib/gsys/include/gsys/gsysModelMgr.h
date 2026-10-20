#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>

namespace sead
{
class Heap;
}

namespace gsys
{

class Model;
class ModelScene;

// Model manager singleton (CSV 0x7100c01c18 .. 0x7100c030b0). createInstance 0x7100c01ce8
// allocates 0x208 bytes, constructs the SingletonDisposer buffer at +8 (the vptr is at +0) and
// installs the ModelMgr vtable. It then initialises three intrusive lists at +0x190 / +0x1a8 /
// +0x1c0 with the node offsets 0x110 / 0x120 / 0x120 (stores at +0x1a4 / +0x1bc / +0x1d4).
// ModelRig::listenPropertyEventEnvObj 0x7100c83d48 walks the first list, whose elements are
// Models: it tests Model +0xf0 (mScene) before registering the model. Only that list and the
// extent are proved here; the other two lists' element types are unproved, so they stay padding.
class ModelMgr
{
    SEAD_SINGLETON_DISPOSER(ModelMgr)

public:
    virtual ~ModelMgr();

    sead::OffsetList<Model>& getModelList() { return mModelList; }
    const sead::OffsetList<Model>& getModelList() const { return mModelList; }

private:
    /* 0x28 */ u8 _28[0x190 - 0x28];

public:
    // Walked directly by ModelRig::listenPropertyEventEnvObj (0x7100c83d48).
    /* 0x190 */ sead::OffsetList<Model> mModelList;

private:
    /* 0x1a8 */ u8 _1a8[0x208 - 0x1a8];
};
static_assert(sizeof(ModelMgr) == 0x208);
static_assert(offsetof(ModelMgr, mModelList) == 0x190);

}  // namespace gsys
