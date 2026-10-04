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

void Selector::m38() {}

int Selector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    return -1;
}

}  // namespace ksys::as
