#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <container/seadBuffer.h>

namespace gsys {

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
    /// One material animation slot (0x30 bytes).
    struct MaterialAnm {
        /// The animation currently set on the slot (invalid if none).
        AnimationAccessKey<MaterialAnmType> key;
        u8 _4[0x30 - 4];

        AnimationAccessKey<MaterialAnmType> getKey() const { return key; }
    };

    /// 0x7100bfe384 (declared only): sets the frame of the animation set on slot `slot`.
    void setMaterialAnmFrame(int slot, f32 frame);

    AnimationAccessKey<MaterialAnmType> searchMaterialAnmKey(
        MaterialAnmType type, const sead::SafeString& name) const;
    // The original named interface returns a signed integer, converted to float by GraphicsAsset.
    s32 isMaterialAnmLooped(AnimationAccessKey<MaterialAnmType> key) const;
    bool sub_7100BFF158(AnimationAccessKey<MaterialAnmType> key) const;

    sead::Buffer<MaterialAnm>& getMaterialAnms() { return mMaterialAnms; }
    const sead::Buffer<MaterialAnm>& getMaterialAnms() const { return mMaterialAnms; }

private:
    u8 _0[0x50];
    sead::Buffer<MaterialAnm> mMaterialAnms;
};

}  // namespace gsys
