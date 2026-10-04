#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

Blender::Blender() {}

bool Blender::m10(Context* ctx, State* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const f32 weight = state->weight;
    state->weight = weight * (1 - record->_4);
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    bool result = child->m10(ctx, state, child_resource);
    if (record->_1 != 0xff) {
        state->weight = weight * record->_4;
        Element* child2 = mChildren[static_cast<s8>(record->_1)];
        const res::ASResource* child2_resource =
            sub_71013031FC(resource, static_cast<s8>(record->_1));
        result &= child2->m10(ctx, state, child2_resource);
    }
    state->weight = weight;
    return result;
}

void Blender::m11(Context* ctx, State* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->sub_710116554C(ctx, state, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->sub_710116554C(ctx, state, child2_resource);
}

void Blender::m15(Context* ctx, State* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->m15(ctx, state, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->m15(ctx, state, child2_resource);
}

void Blender::m16(Context* ctx, const res::ASResource* resource, f32 value) {}
void Blender::m19(Context* ctx, const res::ASResource* resource, f32 value) {}
void Blender::m20(Context* ctx, const res::ASResource* resource, f32 value) {}
void Blender::m21(Context* ctx, const res::ASResource* resource, f32 value) {}
void Blender::m22(Context* ctx, const res::ASResource* resource) {}

f32 Blender::m26(Context* ctx, const res::ASResource* resource) {
    return ctx->sub_7101258CD4(sub_71011653E8(resource))->_8;
}

bool Blender::m27(Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    if (!child->m27(ctx, child_resource))
        return false;
    const s8 second = record->_1;
    if (second == -1)
        return true;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    return child2->m27(ctx, child2_resource);
}

void Blender::m28(f32* a1, Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->m28(a1, ctx, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->m28(a1, ctx, child2_resource);
}

void Blender::m29(f32* a1, Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->m29(a1, ctx, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->m29(a1, ctx, child2_resource);
}

int Blender::m30(f32* a1, Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    int result = child->m30(a1, ctx, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return result;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    const int value = child2->m30(a1, ctx, child2_resource);
    if (value >= 0)
        result = value;
    return result;
}

int Blender::m31(Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    const int result = child->m31(ctx, child_resource);
    if (result >= 0)
        return result;
    const s8 second = record->_1;
    if (second == -1)
        return result;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    return child2->m31(ctx, child2_resource);
}

void Blender::m35(Context* ctx, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const s8 first = record->_0;
    if (first >= 0) {
        Element* child = mChildren[first];
        const res::ASResource* child_resource = sub_71013031FC(resource, first);
        child->sub_7101165E60(ctx, child_resource);
    }
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->sub_7101165E60(ctx, child2_resource);
}

void Blender::m36(Context* ctx, sead::BufferedSafeString* out, const sead::SafeString& name,
                  const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const s8 first = record->_0;
    Element* child = mChildren[first];
    const res::ASResource* child_resource = sub_71013031FC(resource, first);
    child->sub_7101165EBC(ctx, out, name, first, child_resource);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->sub_7101165EBC(ctx, out, name, second, child2_resource);
}

// NON_MATCHING: callee-saved register numbers / argument copy order at entry (the original copies the integer
// arguments before the float ones; see SelectorBase::m17)
void Blender::m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 a5, f32 a6) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    Element* child = mChildren[record->_0];
    const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
    child->m17(ctx, a2 & 1, a3 & 1, child_resource, a5, a6);
    const s8 second = record->_1;
    if (second == -1)
        return;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->m17(ctx, a2 & 1, a3 & 1, child2_resource, a5, a6);
}

// NON_MATCHING: the original folds the sign extension of the child index into the addressing mode in the
// two-child path (`w2, sxtw #3`) and keeps a separate `sxtw` in the single-child path; ours is the other way round
void Blender::m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const int first = record->_0;
    if (record->_1 == 0xff) {
        Element* child = mChildren[first];
        const res::ASResource* child_resource = sub_71013031FC(resource, first);
        child->m34(a1, ctx, a3, child_resource);
        return;
    }
    auto* state = static_cast<State*>(a3);
    const f32 weight = state->weight;
    state->weight = weight * (1 - record->_4);
    Element* child = mChildren[first];
    const res::ASResource* child_resource = sub_71013031FC(resource, first);
    child->m34(a1, ctx, a3, child_resource);
    const s8 second = record->_1;
    state->weight = weight * record->_4;
    Element* child2 = mChildren[second];
    const res::ASResource* child2_resource = sub_71013031FC(resource, second);
    child2->m34(a1, ctx, a3, child2_resource);
    state->weight = weight;
}

bool Blender::sub_71013166C4(Context::Record* record, Context* ctx, PlayState* state,
                             const res::ASResource* resource) {
    Element* first = mChildren[record->_0];
    if (!first->sub_710116541C(ctx, state, sub_71013031FC(resource, record->_0))) {
        record->_2 = 2;
        record->_4 = 1.0f;
    }
    const s8 second = record->_1;
    if (second == -1) {
        if (record->_2 == 2) {
            record->_4 = 0.0f;
            record->_2 = 0;
            return false;
        }
        return true;
    }
    Element* second_child = mChildren[second];
    if (!second_child->sub_710116541C(ctx, state, sub_71013031FC(resource, second))) {
        record->_4 = 0.0f;
        record->_2 = 1;
    }
    return true;
}

bool Blender::m9(Context* ctx, PlayState* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    auto* blender_resource = sead::DynamicCast<const res::ASBlenderResource>(resource);
    const int key = sub_7101165408(resource);
    ctx->sub_710125A1F0(m38(ctx, resource), key, this, blender_resource);
    s32 first, second;
    record->_4 = m39(&first, &second, ctx, resource);
    const s8 old_second = record->_1;
    if (record->_0 >= 0 && (record->_0 != first || (old_second != -1 && old_second != second)))
        m35(ctx, resource);
    record->_0 = first;
    record->_1 = second;
    record->_2 = 0;
    return sub_71013166C4(record, ctx, state, blender_resource);
}

f32 Blender::m38(Context* ctx, const res::ASResource* resource) {
    ASList* list = ctx->mList;
    return list->sub_710115EC98(sub_7101165408(resource), nullptr, 0);
}

}  // namespace ksys::as
