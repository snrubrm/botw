#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace ksys::as {

ComboSelector::ComboSelector() {}

int ComboSelector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    return resource->findIntIndex(ctx->mList->sub_710115EC5C(sub_7101165408(resource), 0));
}

}  // namespace ksys::as
