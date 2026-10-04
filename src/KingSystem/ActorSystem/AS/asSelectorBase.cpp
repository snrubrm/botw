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

bool SelectorBase::m10(Context* ctx, State* state, const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    if (index < 0)
        return true;

    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m10(ctx, state, child_resource);
}

}  // namespace ksys::as
