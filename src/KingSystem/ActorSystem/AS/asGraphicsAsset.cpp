#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

bool GraphicsAsset::m10(Context* ctx, State* state, const res::ASResource* resource) {
    if (_10 == -1 || _12 == -1)
        return true;
    return AnmAsset::m10(ctx, state, resource);
}

int GraphicsAsset::m31(Context* ctx, const res::ASResource* resource) {
    if (_10 == -1 || _12 == -1)
        return -1;
    return ctx->sub_7101258CD4(sub_71011653E8(resource))->_2;
}

}  // namespace ksys::as
