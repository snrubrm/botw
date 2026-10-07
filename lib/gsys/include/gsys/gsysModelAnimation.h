#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <container/seadBuffer.h>

namespace ksys::as {
class ASList;
}

namespace gsys {

class Model;
class PartialSkeletalAnmBase;

enum class MaterialAnmType;
enum class SkeletalAnmType;

/// Identifies one animation of a ModelAnimation: the animation type and the index within that type
/// (passed by value as one 32-bit word, type in the low half).
template <typename T>
struct AnimationAccessKey {
    bool isValid() const { return type != -1 && index != -1; }

    s16 type = -1;
    s16 index = -1;
};

// TODO
/// The animations (skeletal and material animations) of a Model. Created by Model::createAnimation
/// (0x7100bf729c) and stored in the model (Model::getAnimation).
class ModelAnimation {
public:
    /// Argument of Model::createAnimation (0x7100bfa214: both counts default to 4).
    struct CreateArg {
        CreateArg();

        s32 _0;
        s32 _4;
        void* _8;
    };

    virtual ~ModelAnimation();

    /// One material animation slot (0x30 bytes).
    struct MaterialAnm {
        /// The animation currently set on the slot (invalid if none).
        AnimationAccessKey<MaterialAnmType> key;
        u8 _4[0x30 - 4];

        AnimationAccessKey<MaterialAnmType> getKey() const { return key; }
    };

    /// 0x7100bfdc04 / 0x7100bfa52c (declared only): releases the animation set / frees the object.
    void finalize();
    // 0x7100bfdbf4: enables the self-reference at +0x38.
    void sub_7100BFDBF4(bool enabled);
    // 0x7100bfd598 clears a skeletal slot; 0x7100bfdd10 clears material bindings.
    void sub_7100BFD598(s32 slot);
    void sub_7100BFDD10(s32 slot);
    void setSkeletalAnmByKey(int slot, AnimationAccessKey<SkeletalAnmType> key,
                             const PartialSkeletalAnmBase* partial);
    /// Frees the object through its virtual destructor (0x7100bfa52c); null is ignored.
    static void destroy(ModelAnimation* animation);
    /// Number of material animations of `type` (the table at +0x80 holds the running end index per type).
    s32 getMaterialAnmNum(MaterialAnmType type) const;
    /// 0x7100bfd768 (CSV name) / 0x7100bfddcc (unnamed): apply the skeletal / (probably) the material animations to a
    /// model.
    void applySkeletalAnm(Model* model);
    void sub_7100BFDDCC(Model* model);

    /// 0x7100bfe384 (declared only): sets the frame of the animation set on slot `slot`.
    void setMaterialAnmFrame(int slot, f32 frame);

    void setMaterialAnmByKey(int slot, AnimationAccessKey<MaterialAnmType> key, f32 frame);
    sead::SafeString sub_7100BFDF8C(int slot) const;
    sead::SafeString sub_7100BFDC84(AnimationAccessKey<MaterialAnmType> key) const;

    AnimationAccessKey<MaterialAnmType> searchMaterialAnmKey(
        MaterialAnmType type, const sead::SafeString& name) const;
    // The original named interface returns a signed integer, converted to float by GraphicsAsset.
    s32 isMaterialAnmLooped(AnimationAccessKey<MaterialAnmType> key) const;
    bool sub_7100BFF158(AnimationAccessKey<MaterialAnmType> key) const;

    sead::Buffer<MaterialAnm>& getMaterialAnms() { return mMaterialAnms; }
    const sead::Buffer<MaterialAnm>& getMaterialAnms() const { return mMaterialAnms; }

private:
    u8 _8[0x38 - 8];
    ModelAnimation* mSelfReferenceMaybe;
    u8 _40[0x50 - 0x40];
    sead::Buffer<MaterialAnm> mMaterialAnms;
    u8 _60[0x80 - 0x60];
    u16 mMaterialAnmEnd[8];
public:
    // ASList::sub_7101160ED4 stores its owner at +0x90 after enabling the animation.
    ksys::as::ASList* mASList;
};

}  // namespace gsys
