#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

StringSelector::StringSelector() {}

const char* StringSelector::m40(Context* ctx, const res::ASResource* resource) {
    ASList* list = ctx->mList;
    return list->sub_710115ECF4(sub_7101165408(resource), 0);
}

}  // namespace ksys::as
