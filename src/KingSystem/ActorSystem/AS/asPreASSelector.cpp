#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

PreASSelector::PreASSelector() {}

const char* PreASSelector::m40(Context* ctx, const res::ASResource* resource) {
    return ctx->mUnk18.cstr();
}

}  // namespace ksys::as
