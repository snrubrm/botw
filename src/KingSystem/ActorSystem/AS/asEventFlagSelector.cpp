#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

EventFlagSelector::EventFlagSelector() {}

EventFlagSelector::~EventFlagSelector() {
    _18.freeBuffer();
}

}  // namespace ksys::as
