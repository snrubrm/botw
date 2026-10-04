#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

SpeedBlender::SpeedBlender() {}

f32 SpeedBlender::m38(Context* ctx, const res::ASResource* resource) {
    return ctx->mList->sub_710115EC98(0x13, &ASList::sub_710115F740, 0);
}

}  // namespace ksys::as
