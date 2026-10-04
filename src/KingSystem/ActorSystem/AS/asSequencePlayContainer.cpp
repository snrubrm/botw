#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

SequencePlayContainer::SequencePlayContainer() {}

bool SequencePlayContainer::m27(Context* ctx, const res::ASResource* resource) {
    if (auto* sequence = sead::DynamicCast<const res::ASSequencePlayContainerResource>(resource)) {
        if (sequence->getSequenceLoop())
            return true;
    }
    return SelectorBase::m27(ctx, resource);
}

bool SequencePlayContainer::m24(Context* ctx, const res::ASResource* resource) {
    int index;
    if (!sub_71013031B4(&index, ctx, resource))
        return true;
    if (auto* sequence = sead::DynamicCast<const res::ASSequencePlayContainerResource>(resource)) {
        if (sequence->getSequenceLoop())
            return false;
    }
    if (index != mChildren.size() - 1)
        return false;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m24(ctx, child_resource);
}

// NON_MATCHING: register allocation (the original keeps the resource cast in x28 and the result in w21) and the
// exit blocks are not shared the way the original shares them
bool SequencePlayContainer::m32(Context* ctx, void* a2, void* a3, void* a4, void* a5,
                                const res::ASResource* resource, f32 value) {
    auto* sequence = sead::DynamicCast<const res::ASSequencePlayContainerResource>(resource);
    bool result = false;
    if (value > 0.0f) {
        int index = 0;
        do {
            Element* child = mChildren[index];
            const res::ASResource* child_resource = sub_71013031FC(resource, index);
            if (!child->m32(ctx, a2, a3, a4, a5, child_resource, value))
                return result;
            value = *static_cast<f32*>(a5);
            if (value < 0.0f)
                return true;
            if (!sequence->getSequenceLoop() && index == mChildren.size() - 1)
                return true;
            index = index + 1 == mChildren.size() ? 0 : index + 1;
            result = true;
        } while (value > 0.0f);
    }
    return result;
}

}  // namespace ksys::as
