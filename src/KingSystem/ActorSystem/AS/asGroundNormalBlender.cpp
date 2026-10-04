#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

GroundNormalBlender::GroundNormalBlender() {}
GroundNormalSideBlender::GroundNormalSideBlender() {}

f32 GroundNormalBlender::m38(Context* ctx, const res::ASResource* resource) {
    return ctx->mList->sub_710115EC98(0x15, &ASList::sub_710115F8A0, 0);
}

f32 GroundNormalSideBlender::m38(Context* ctx, const res::ASResource* resource) {
    return ctx->mList->sub_710115EC98(0x16, &ASList::sub_710115F98C, 0);
}

}  // namespace ksys::as
