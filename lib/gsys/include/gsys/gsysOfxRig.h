#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <gsys/gsysIModelRigObj.h>
#include <gsys/gsysModelRig.h>

namespace gsys {

class Model;
class ModelUnit;

// The rig template behind OfxLensFlareRig and OfxLargeLensFlareRig; its constructor
// 0x7100c4da3c / 0x7100c4dc34 is called by the EnvObj type factories on 0x2f0-byte
// objects, and the offset list at +0x260 keeps the rig's OfxHook objects (offset 0x30
// is stored at +0x274 by initialize 0x7100c534). Only the parts the effect manager
// needs are modelled here.
template <typename Impl>
class OfxRig : public ModelRig {
public:
    class OfxHook;

    // One effect object of the manager (0x28 bytes). The manager first builds an array
    // of these, then hands slots out as hooks bind to model units.
    class OfxObj {
    public:
        virtual ~OfxObj() {}

        /* 0x08 */ s32 mIndexOfx = -1;
        /* 0x10 */ void* mOfx = nullptr;
        /* 0x18 */ s32 mPresetIndex = -1;
        /* 0x20 */ OfxHook* mHook = nullptr;
    };
    static_assert(sizeof(OfxObj) == 0x28);

    // One binding of an effect object to a model unit (0x50 bytes). It is a model rig
    // object (node at +0x08) and also lives in the rig's own offset list (node at +0x30).
    class OfxHook : public IModelRigObj {
    public:
        virtual ~OfxHook() {}

        /* 0x18 */ OfxObj* mObj = nullptr;
        /* 0x20 */ Model* mModel = nullptr;
        /* 0x28 */ s16 mUnitIndex = -1;
        /* 0x2a */ s16 mPreviousUnitIndex = -1;
        /* 0x30 */ sead::ListNode mRigNode;
        /* 0x40 */ OfxRig<Impl>* mRig = nullptr;
        /* 0x48 */ u16 mVisible = 0xffff;
        /* 0x4a */ u16 mPreviousVisible = 0xffff;
    };
    static_assert(sizeof(OfxHook) == 0x50);

    // 0x260
    sead::OffsetList<OfxHook> mHooks;
};

}  // namespace gsys
