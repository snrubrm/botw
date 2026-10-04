#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

BoneBlender::BoneBlender() {}

void BoneBlender::m12(Context* ctx, State* state, const res::ASResource* resource) {
    ctx->mList->sub_7101160ED4();
    Blender::m12(ctx, state, resource);
}

void BoneBlender::m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const auto* params = sead::DynamicCast<const res::ASSetting::BoneParams>(
        resource->getExtensions().getParser(res::ASParamParser::Type::BlenderBone));
    state->sub_7101257920(params);
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->m15(ctx, state, child_resource);
    if (record->_1 != 0xff) {
        state->_20 = 2;
        Element* child2 = mChildren[s8(record->_1)];
        const res::ASResource* child2_resource = sub_71013031FC(resource, s8(record->_1));
        child2->m15(ctx, state, child2_resource);
    }
    state->sub_710125792C();
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
