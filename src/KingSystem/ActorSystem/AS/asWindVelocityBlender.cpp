#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

WindVelocityBlender::WindVelocityBlender(const CreateArg&, s32, const res::ASResource*) {}

f32 WindVelocityBlender::m38(Context* ctx, const res::ASResource* resource) {
    return ctx->mList->sub_710115EC98(0x1b, &ASList::sub_710115FA78, 0);
}

}  // namespace ksys::as
