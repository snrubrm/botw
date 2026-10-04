#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

FloatSelector::FloatSelector() {}

f32 FloatSelector::m40(Context* ctx, u32 a2, const res::ASResource* resource) {
    ASList* list = ctx->mList;
    return list->sub_710115EC98(sub_7101165408(resource), nullptr, 0);
}

}  // namespace ksys::as
