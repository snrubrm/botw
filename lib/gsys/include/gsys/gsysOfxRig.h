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
    // 0x7100c4da3c / 0x7100c4dc34 (declared only). The type factories allocate
    // 0x2f0 bytes and call this constructor.
    OfxRig();

    class OfxHook;

    // One effect object of the manager (0x28 bytes). The manager first builds an array
    // of these, then hands slots out as hooks bind to model units.
    class OfxObj {
    public:
        virtual ~OfxObj();

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
        virtual ~OfxHook();

        /* 0x18 */ OfxObj* mObj = nullptr;
        /* 0x20 */ Model* mModel = nullptr;
        /* 0x28 */ s16 mUnitIndex = -1;
        /* 0x2a */ s16 mPreviousUnitIndex = -1;
        /* 0x30 */ sead::ListNode mRigNode;
        /* 0x40 */ OfxRig<Impl>* mRig = nullptr;
        /* 0x48 */ u16 mVisible = 0xffff;
        /* 0x4a */ u16 mPreviousVisible = 0xffff;

        // 0x7100c30764 / 0x7100c309b4 (declared only name); the native body ANDs the unit's
        // visibility mask with the passed mask and stores the 0/1 result.
        void updateFromModel(ModelUnit* unit, u32 visibility_mask, f32 delta_time);
    };
    static_assert(sizeof(OfxHook) == 0x50);

    // 0x7100c4c534 / 0x7100c4c95c: the ModelRig setup, then the hook list's node offset.
    void initialize(int index, sead::Heap* heap) override;

    // 0x7100c4c03c / 0x7100c4c26c in the concrete rigs (declared only; bodies U).
    virtual void updateObj_(OfxObj* obj, const sead::Matrix34f& matrix, const sead::Vector3f& a,
                            const sead::Vector3f& b) const = 0;

    // Empty overrides of ModelRig's m24 / m25 / m26 (slots 205-207). The base still carries the
    // lane1 placeholder names (LocationalLightRig overrides them), so these real names are plain
    // members for now; the bodies and symbols are the original ones.
    void bindBone_(Model* model, const BoneAccessKey& key, const sead::SafeString& name);
    void bindMaterial_(Model* model, const MaterialAccessKey& key,
                       const sead::SafeString& name);
    void release_(Model* model, int unit_index);

    // 0x260
    sead::OffsetList<OfxHook> mHooks;
    // The constructor 0x7100c4da3c / 0x7100c4dc34 registers these three parameters.
    /* 0x278 */ agl::utl::Parameter<int> mPresetIdx;
    /* 0x298 */ agl::utl::Parameter<sead::Vector3f> mOffset;
    /* 0x2c0 */ agl::utl::Parameter<sead::Vector3f> mDirection;
    /* 0x2e8 */ void* _2e8 = nullptr;
};

}  // namespace gsys
