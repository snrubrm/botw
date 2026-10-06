#pragma once

#include <algorithm>
#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <math/seadBoundSphere.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>

namespace gsys {

struct BoneAccessKey;
class IModelAccesssHandle;
class IModelRigObj;
struct MaterialAccessKey;
class ModelAnimation;
class ModelBone;
class ModelScene;
class ModelUnit;

class ModelInfo {
public:
    ModelUnit* mModelUnit;
    void* _8;
    void* _10;
    u32 _18;
    s16 mAccessIndex;
    u8 _1e;
    /// The rig objects attached to this model unit (0x7100bf9c08 / 0x7100bf9c58); the list offset is set by the
    /// creator.
    sead::OffsetList<IModelRigObj> mRigObjs;
};

// TODO
class Model : public sead::IDisposer, public sead::hostio::Node {
public:
    Model();
    ~Model() override;

    sead::PtrArray<ModelInfo>& getUnits() { return mUnitAccess; }
    const sead::PtrArray<ModelInfo>& getUnits() const { return mUnitAccess; }

    const sead::Matrix34f& getMatrix() const { return mMatrix; }
    const sead::Vector3f& getScale() const { return mScale; }

    void setMatrix(const sead::Matrix34f& matrix) {
        _a0 |= 1;
        mMatrix = matrix;
    }

    void setScale(const sead::Vector3f& scale) {
        _a0 |= 1;
        mScale = scale;
    }

    /// The material / skeletal animation set of the model (created by createAnimation), or null.
    ModelAnimation* getAnimation() const { return mAnimation; }

    void setAutoAnimationFrameRate(f32 frame_rate);
    /// Sets the current frame of the auto animation of each ModelNW unit that has one.
    void forceAutoAnimationFrame(f32 frame);
    /// Updates the auto animation of each ModelNW unit that has one right away.
    void forceUpdateAutoAnimation();
    void sub_7100BF8738();

    /// Writes the bounding sphere of the model: the override if one is set, otherwise the union of the bounding
    /// spheres of the model units, gathered on demand. 0x7100bf97cc
    void getBounding(sead::BoundSphere3f* bounding) const;

    // 0x7100bf8e9c (CSV name; declared only): recomputes the world matrices of the model units from
    // mMatrix. Callers set the matrix with setMatrix() (which flags it as changed) first.
    void updateWorldMatrix();

    // 0x7100bf79a4 (declared only; names are guesses): the sum of ModelUnit::getBoneNum() over the first
    // min(mUnitPool.size(), mNumModels) pool entries. (0x7100bf7a04 is the maximum instead of the sum;
    // 0x7100bf7a68 / 0x7100bf7ac8 are the same for ModelUnit::getMaterialNum().)
    int getTotalBoneNum() const;
    // 0x7100bf7a04 / 0x7100bf7a68 / 0x7100bf7ac8: the maximum bone count and the sum / maximum of the material
    // counts of the used units (names are guesses).
    int getMaxBoneNum() const;
    int getTotalMaterialNum() const;
    int getMaxMaterialNum() const;
    // 0x7100bf7b2c (name is a guess): sets the total bone count; when `override` is false the count is
    // recomputed (getTotalBoneNum) and the override flag (_a0 bit 3) cleared.
    void setTotalBoneNum(int num, bool override);
    // 0x7100bf7dd8 / 0x7100bf7e34 (names are guesses): whether any used unit has bit `bit` set in its
    // visibility mask (ModelUnit +0xc, the mask x() changes) / sets the mask of every used unit.
    bool isVisibilityBitOn(int bit) const;
    void setVisibilityMask(u16 mask);
    // 0x7100bf8b54 (CSV name) / 0x7100bf8ba8 / 0x7100bf8c04 (CSV name) / 0x7100bf8d18: each forwards one value to
    // the used units (ModelUnit::resetRenderOption / resetRenderViewOption(option, -1) / 0x7100c3e79c /
    // ModelUnit::enableRenderOption(0x10, on)).
    void resetRenderToDepthShadow(int option);
    void sub_7100BF8BA8(int option);
    void resetRenderToDepthShadowOnly(int value);
    void sub_7100BF8D18(bool on);
    // 0x7100bf7ea4 / 0x7100bf7f18 (names are guesses): the OR over the model units (access array) of the
    // visibility mask (+0xc) / of the u16 at +0x14.
    u16 getVisibilityMaskAll() const;
    u16 getFlags14All() const;
    // 0x7100bf7f8c (name is a guess): the maximum over the model units of the u32 at ModelUnit +0x18.
    u32 getMaxValue18() const;
    // 0x7100bf7358 (name is a guess): finalizes and frees the animation set.
    void destroyAnimation_();

    // The bone setters forward to the model unit of the key (virtual slots of ModelUnit):
    // 0x7100bf7c30 (declared only)
    void setBoneLocalMatrix(const BoneAccessKey& key, const sead::Matrix34f& matrix,
                            const sead::Vector3f& scale);
    // 0x7100bf7c5c (declared only)
    void setBoneLocalRTMatrix(const BoneAccessKey& key, const sead::Matrix34f& matrix);
    // 0x7100bf7c84 (declared only)
    void setBoneWorldMatrix(const BoneAccessKey& key, const sead::Matrix34f& matrix);
    // 0x7100bf7bb4 (CSV name)
    BoneAccessKey searchBone(const sead::SafeString& name) const;
    // 0x7100bf82e8 (CSV name; declared only)
    MaterialAccessKey searchMaterial(const sead::SafeString& name) const;
    // 0x7100bf7cac (CSV name): calls ModelUnit::clearBoneLocalMatrix on every model unit.
    void clearBoneLocalMatrix() const;
    // 0x7100bf8364 (CSV name): ModelUnit::setMaterialVisibleAll on every model unit.
    void setMaterialVisibleAll(bool visible);
    // 0x7100bf9c08 / 0x7100bf9c58 (CSV names): attach / detach a rig object of the model unit `unit_idx`.
    void pushBack(int unit_idx, IModelRigObj* obj);
    bool erase(int unit_idx, IModelRigObj* obj);
    // 0x7100bf9bd8 (name is a guess): whether the rig object is attached to the model unit.
    bool hasRigObj(int unit_idx, IModelRigObj* obj) const;
    // 0x7100bf99b0 (CSV name): `_a1` bit 2 requests an update, `_a3` keeps the argument.
    void requestUpdate(u32 flags);
    // 0x7100bf95bc (CSV name): ModelUnit::calcBounding of the units in `_48`.
    void updateBounding();
    // 0x7100bf6d94 (CSV name): binds the model (and its used units) to a scene, unbinding it from the old one.
    void bind(ModelScene* scene);
    // 0x7100bf6e20 / 0x7100bf76d0 (CSV names): remove / search every registered access handle.
    void clearModelAccesssHandle();
    void updateModelAccesssHandle_();
    // 0x7100bf7cf0 (CSV name; declared only): sets (`on`) or clears bit `bit` of the u16 flags at
    // +0xc of the model unit of each of the first min(mUnitPool.size(), mNumModels) pool entries.
    void x(bool on, int bit);
    // 0x7100bf8c58 (CSV x_0) / 0x7100bf8cb8 (declared only): for each of the first min(mUnitPool.size(),
    // mNumModels) pool entries, ModelUnit::enableRenderViewOption(option 0 / option 1, on, bit). Names are
    // placeholders; the second one is the tail call of ksys::act::WeaponBase::sub_7100EE6AFC.
    void sub_7100BF8C58(bool on, int bit);
    void sub_7100BF8CB8(bool on, int bit);

    // 0x7100bf8e24 (CSV name; declared only): applies the animations of this model to `target` (a model that
    // shares the skeleton): bit 0 of `flags` applies the skeletal animation, bit 1 the material animation.
    void applyAnimationTo(Model* target, u32 flags);

    // For internal use.
    void add_(IModelAccesssHandle* handle) const;
    void remove_(IModelAccesssHandle* handle) const;
    sead::CriticalSection& getCS() const { return mCS; }

private:
    // inline-only in the original; name is a guess: the number of leading pool entries that hold model units
    // (every per-unit loop below runs over min(pool size, mNumModels) entries).
    u32 getUsedUnitNum() const { return std::min<u32>(mNumModels, mUnitPool.size()); }

    void gatherBounding_() const;

    sead::Buffer<ModelInfo> mUnitPool;
    /// Indices into this array are called "model unit access indices".
    sead::PtrArray<ModelInfo> mUnitAccess;
    sead::PtrArray<ModelInfo> _48;
    sead::Matrix34f mMatrix = sead::Matrix34f::ident;
    sead::Vector3f mScale = sead::Vector3f::ones;
    sead::Vector3f _94 = sead::Vector3f::ones;
    /// Flags. Bit 0 is set when the matrix is changed.
    u8 _a0 = 1;
    u8 _a1 = 0;
    u8 _a2 = 1;
    u8 _a3 = 0;
    u16 mNumModels = 0;
    u8 _a6[0xac - 0xa6];
    /// Total bone count (the sum over the model units unless overridden; see 0x7100bf7b2c).
    s32 _ac;
    f32 mAutoAnimationFrameRate;
    /// Result of gatherBounding_ (0x7100bf9600, CSV name; declared only): the union of the bounding spheres of
    /// the model units.
    mutable sead::BoundSphere3f mBounding;
    u8 _c4[0xc8 - 0xc4];
    /// If set, getBounding returns this instead of gathering the unit bounds. The name is a guess.
    const sead::BoundSphere3f* mBoundingOverrideMaybe;
    ModelAnimation* mAnimation;
    u8 _d8[0xf0 - 0xd8];
    /// The scene the model is bound to (bind()).
    ModelScene* mScene;
    u8 _f8[0x140 - 0xf8];
    mutable sead::CriticalSection mCS;
    mutable sead::OffsetList<IModelAccesssHandle> mHandleList;
    sead::FixedSafeString<256> mName{"名称未設定"};
    u8 _2b0[0x2b8 - 0x2b0];
};

}  // namespace gsys
