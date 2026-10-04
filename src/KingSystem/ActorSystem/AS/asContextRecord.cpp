#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

static ElementParams sUnk_71026531e8;

// NON_MATCHING: load order (the original reads the entry index before the entry count) and registers
ElementParams* Context::Record::sub_7101257DF4(Frame* frame, bool a2) {
    if (!(_3 & 8))
        return &sUnk_71026531e8;
    const u8 index = _1;
    if (frame->mEntries.size() <= index)
        return &sUnk_71026531e8;
    return &frame->mEntries[index];
}

}  // namespace ksys::as
