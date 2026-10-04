#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

SyncPlayContainer::SyncPlayContainer() {}

bool SyncPlayContainer::m10(Context* ctx, State* state, const res::ASResource* resource) {
    bool result = true;
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        result &= child->m10(ctx, state, child_resource);
        ++index;
    }
    return result;
}

}  // namespace ksys::as
