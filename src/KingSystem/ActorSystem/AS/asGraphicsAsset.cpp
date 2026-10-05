#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

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

int GraphicsAsset::m31(Context* ctx, const res::ASResource* resource) {
    if (!mKey.isValid())
        return -1;
    return ctx->sub_7101258CD4(sub_71011653E8(resource))->_2;
}

}  // namespace ksys::as
