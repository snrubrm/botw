#include "KingSystem/Resource/resVfxResourceMgr.h"
#include "KingSystem/Resource/resEntryFactory.h"

namespace ksys::res {

Unk_7102518018::~Unk_7102518018() = default;

s32 Unk_7102518018::getLoadDataAlignment() const {
    return cLoadDataAlignment;
}

// NON_MATCHING: native newResource_ value-initializes the resource storage.
template class EntryFactory<Unk_7102518018>;

}  // namespace ksys::res
