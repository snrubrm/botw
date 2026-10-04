#include "KingSystem/ActorSystem/AS/asElement.h"

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

}  // namespace ksys::as
