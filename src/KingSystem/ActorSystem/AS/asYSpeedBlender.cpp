#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

YSpeedBlender::YSpeedBlender() {}

f32 YSpeedBlender::m38(Context* ctx, const res::ASResource* resource) {
    return ctx->mList->sub_710115EC98(0x14, &ASList::sub_710115F820, 0);
}

}  // namespace ksys::as
