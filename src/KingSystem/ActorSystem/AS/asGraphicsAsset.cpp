#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

// NON_MATCHING: the two default key halfwords are stored in the opposite order.
GraphicsAsset::GraphicsAsset(const CreateArg& arg, s32 value, gsys::MaterialAnmType type)
    : AnmAsset(arg, value, nullptr), _14(type) {}



void GraphicsAsset::m5(act::Actor*, gsys::Model* model, const sead::SafeString& name,
                       sead::Heap*, const res::AS* as) {
    auto* animation = model->getAnimation();
    if (!animation) {
        mKey = {};
        return;
    }

    const res::ASResource* resource = nullptr;
    const sead::SafeString* animation_name = &name;
    if (as) {
        resource = as->getElementResources()[m6()];
        animation_name = &sead::DynamicCast<const res::ASAssetResource>(resource)->getFileName();
    }
    mKey = animation->searchMaterialAnmKey(_14, *animation_name);
    if (!mKey.isValid() || animation->getMaterialAnms().size() < 1)
        return;
    _c = animation->isMaterialAnmLooped(mKey);
    sub_710131586C(animation->sub_7100BFF158(mKey), resource);
}

bool GraphicsAsset::m10(Context* ctx, State* state, const res::ASResource* resource) {
    if (!mKey.isValid())
        return true;
    return AnmAsset::m10(ctx, state, resource);
}

// NON_MATCHING: the filename address is computed after the virtual duration call.
void GraphicsAsset::m14(Context* ctx, void* state, EventState*, const res::ASResource* resource) {
    if (!mKey.isValid())
        return;

    const auto* asset = sead::DynamicCast<const res::ASAssetResource>(resource);
    if (!asset || !static_cast<MotionState*>(state)->_34)
        return;

    auto* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const f32 frame = ctx->sub_7101258D4C(record, false)->_4;
    ctx->sub_710125930C(frame, m4(), asset->getFileName(), asset->getTypeIndex());
}

int GraphicsAsset::m31(Context* ctx, const res::ASResource* resource) {
    if (!mKey.isValid())
        return -1;
    return ctx->sub_7101258CD4(sub_71011653E8(resource))->_2;
}

}  // namespace ksys::as
