#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

BoneBlender::BoneBlender() {}

void BoneBlender::m12(Context* ctx, State* state, const res::ASResource* resource) {
    ctx->mList->sub_7101160ED4();
    Blender::m12(ctx, state, resource);
}

bool BoneBlender::m27(Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m27(ctx, child_resource);
}

f32 BoneBlender::m39(s32* first, s32* second, Context* ctx, const res::ASResource* resource) {
    *first = 0;
    *second = mChildren.size() == 2 ? 1 : -1;
    return 0.01f;
}

}  // namespace ksys::as
