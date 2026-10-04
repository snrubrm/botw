#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

void IntSelector::m12(Context* ctx, State* state, const res::ASResource* resource) {
    s32 index;
    if (!sub_71013031B4(&index, ctx, resource))
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m12(ctx, state, child_resource);
}

int IntSelector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    return _18;
}

}  // namespace ksys::as
