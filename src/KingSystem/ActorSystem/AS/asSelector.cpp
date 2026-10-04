#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

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
