#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

GroundNormalSelector::GroundNormalSelector(const CreateArg&, s32, const res::ASResource*) {}
GroundNormalSideSelector::GroundNormalSideSelector(const CreateArg&, s32, const res::ASResource*) {}

f32 GroundNormalSelector::m40(Context* ctx, u32 a2, const res::ASResource* resource) {
    return ctx->mList->sub_710115EC98(0x15, &ASList::sub_710115F8A0, 0);
}

f32 GroundNormalSideSelector::m40(Context* ctx, u32 a2, const res::ASResource* resource) {
    return ctx->mList->sub_710115EC98(0x16, &ASList::sub_710115F98C, 0);
}

}  // namespace ksys::as
