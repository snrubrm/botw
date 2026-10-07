#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

SpeedSelector::SpeedSelector(const CreateArg&, s32, const res::ASResource*) {}

f32 SpeedSelector::m40(Context* ctx, u32 a2, const res::ASResource* resource) {
    return ctx->mList->sub_710115EC98(0x13, &ASList::sub_710115F740, 0);
}

}  // namespace ksys::as
