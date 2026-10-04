#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

IntSelector::IntSelector(const CreateArg& arg, s32 value, const res::ASResource* resource)
    : _18(-1) {
    if (const auto* children = sead::DynamicCast<const res::ASResourceWithChildren>(resource))
        _18 = getValue(arg.actor, children);
}

// NON_MATCHING: the compiler inlines the constructor into this factory.
Element* IntSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) IntSelector(arg, value, resource);
}

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
