#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

SelectorBase::SelectorBase() {}

SelectorBase::~SelectorBase() {
    mChildren.freeBuffer();
}

const res::ASResource* SelectorBase::sub_71013031FC(const res::ASResource* resource,
                                                    int index) const {
    if (auto* parent = sead::DynamicCast<const res::ASResourceWithChildren>(resource))
        return parent->getChildren()[index];
    return nullptr;
}

bool SelectorBase::sub_71013031B4(s32* out, Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    *out = record->_0;
    return record->_0 >= 0;
}

bool SelectorBase::m10(Context* ctx, State* state, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return true;

    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m10(ctx, state, child_resource);
}


void SelectorBase::m11(Context* ctx, EventState* state, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->sub_710116554C(ctx, state, child_resource);
}

void SelectorBase::m12(Context* ctx, State* state, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m12(ctx, state, child_resource);
}

void SelectorBase::m13(Context* ctx, State* state, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m13(ctx, state, child_resource);
}

void SelectorBase::m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m15(ctx, state, child_resource);
}

void SelectorBase::m14(Context* ctx, void* a2, EventState* a3, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->sub_71011654E0(ctx, a2, a3, child_resource);
}

void SelectorBase::m16(Context* ctx, const res::ASResource* resource, f32 value) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m16(ctx, child_resource, value);
}

void SelectorBase::m19(Context* ctx, const res::ASResource* resource, f32 value) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m19(ctx, child_resource, value);
}

void SelectorBase::m20(Context* ctx, const res::ASResource* resource, f32 value) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m20(ctx, child_resource, value);
}

void SelectorBase::m21(Context* ctx, const res::ASResource* resource, f32 value) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m21(ctx, child_resource, value);
}

// NON_MATCHING: callee-saved register numbers (the original keeps the context in x20 and a2 in w21)
void SelectorBase::m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 a5, f32 a6) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m17(ctx, a2, a3, child_resource, a5, a6);
}

void SelectorBase::m22(Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m22(ctx, child_resource);
}

Element* SelectorBase::m23(Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return this;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m23(ctx, child_resource);
}

bool SelectorBase::m24(Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return true;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m24(ctx, child_resource);
}

const ElementParams* SelectorBase::m25(Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return nullptr;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m25(ctx, child_resource);
}

f32 SelectorBase::m26(Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return 0;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m26(ctx, child_resource);
}

bool SelectorBase::m27(Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return false;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m27(ctx, child_resource);
}

int SelectorBase::m31(Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return -1;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m31(ctx, child_resource);
}

void SelectorBase::m35(Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->sub_7101165E60(ctx, child_resource);
}

void SelectorBase::m28(f32* a1, Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m28(a1, ctx, child_resource);
}

void SelectorBase::m29(f32* a1, Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m29(a1, ctx, child_resource);
}

int SelectorBase::m30(f32* a1, Context* ctx, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return -1;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m30(a1, ctx, child_resource);
}

// NON_MATCHING: order of the argument copies at entry (a3 before the float)
bool SelectorBase::m33(Context* ctx, void* a2, void* a3, const res::ASResource* resource, f32 a5) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return false;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m33(ctx, a2, a3, child_resource, a5);
}

void SelectorBase::m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m34(a1, ctx, a3, child_resource);
}

void SelectorBase::m36(Context* ctx, sead::BufferedSafeString* out, sead::BufferedSafeString& name, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->sub_7101165EBC(ctx, out, name, index, child_resource);
}

}  // namespace ksys::as
