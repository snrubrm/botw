#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace ksys::act {

// In a TU of its own: next to sub_7100D7EA7C the inliner expands the call into the destructors (the original calls it).
Unk_71024dccf8::~Unk_71024dccf8() {
    if (_20)
        _20->sub_7100D7EA7C(this);
}

}  // namespace ksys::act
