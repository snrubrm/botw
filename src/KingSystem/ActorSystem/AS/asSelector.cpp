#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

Selector::Selector() {}

// NON_MATCHING: order of the argument copies at entry (the float is copied after a5 / a4)
bool Selector::m32(Context* ctx, void* a2, void* a3, void* a4, void* a5,
                   const res::ASResource* resource, f32 value) {
    const int index = m39(ctx, 0, resource);
    if (index == -1)
        return false;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m32(ctx, a2, a3, a4, a5, child_resource, value);
}

// NON_MATCHING: callee-saved register numbers (resource / ctx swapped) and the placement of the `record->_0 = index`
// sign test (the original stores the byte and tests the sign-extended register)
void Selector::m12(Context* ctx, State* state, const res::ASResource* resource) {
    auto* selector_resource = sead::DynamicCast<const res::ASSelectorResource>(resource);
    if (!selector_resource)
        return;
    if (!(ctx->_920 & 2)) {
        const bool no_sync = selector_resource->getNoSync();
        selector_resource = sead::DynamicCast<const res::ASSelectorResource>(resource);
        if (selector_resource && !selector_resource->getJudgeOnce()) {
            Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
            const u32 new_index = m39(ctx, 1, resource);
            const s8 old_index = record->_0;
            if (new_index != old_index) {
                f32 old_progress;
                if (old_index < 0) {
                    old_progress = 0.0f;
                } else {
                    Element* old_child = mChildren[old_index];
                    const res::ASResource* old_resource = sub_71013031FC(resource, old_index);
                    old_progress = 0.0f;
                    if (!no_sync) {
                        if (const ElementParams* params = old_child->m25(ctx, old_resource))
                            old_progress = params->sub_710130298C(true);
                    }
                    old_child->sub_7101165E60(ctx, old_resource);
                }
                record->_0 = new_index;
                if (static_cast<s8>(new_index) >= 0) {
                    PlayState play_state;
                    play_state._0 = old_progress;
                    play_state._4 = !no_sync;
                    ctx->mFlags |= 0x22;
                    play_state._8 = ctx->sub_7101258D1C(sub_71011653E8(resource)) + 1;
                    Element* child = mChildren[new_index];
                    const res::ASResource* child_resource = sub_71013031FC(resource, new_index);
                    child->sub_710116541C(ctx, &play_state, child_resource);
                    if (no_sync)
                        ctx->_e8 = -1.0f;
                    SelectorBase::m12(ctx, state, resource);
                    ctx->mFlags &= ~2u;
                    return;
                }
            }
        }
    }
    SelectorBase::m12(ctx, state, resource);
}

bool Selector::m9(Context* ctx, PlayState* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    const int index = m39(ctx, 1, resource);
    const s8 old_index = record->_0;
    if (old_index >= 0 && old_index != index) {
        Element* old_child = mChildren[old_index];
        old_child->sub_7101165E60(ctx, sub_71013031FC(resource, old_index));
    }
    record->_0 = index;
    m38(ctx, resource);
    if (record->_0 >= 0) {
        Element* child = mChildren[index];
        return child->sub_710116541C(ctx, state, sub_71013031FC(resource, index));
    }
    return false;
}

void Selector::m38(Context* ctx, const res::ASResource* resource) {}

int Selector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    return -1;
}

}  // namespace ksys::as
