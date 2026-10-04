#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

EventFlagSelector::EventFlagSelector() {}

EventFlagSelector::~EventFlagSelector() {
    _18.freeBuffer();
}

const char* EventFlagSelector::m40(Context* ctx, const res::ASResource* resource) {
    return sub_710131D9F0(ctx, resource).cstr();
}

}  // namespace ksys::as
