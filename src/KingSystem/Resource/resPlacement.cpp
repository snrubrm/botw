#include "KingSystem/Resource/resPlacement.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resSystem.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::res {

void Placement::registerFactory(sead::Heap* heap) {
    auto* rm = sead::ResourceMgr::instance();
    if (!rm)
        return;

    if (rm->getDefaultFactory() != rm->findFactory("bplacement"))
        return;

    res::registerEntryFactory(new (heap) EntryFactory<Placement>(1.0, sizeof(Placement)),
                              "bplacement");
}

void Placement::doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) {
    mHeader = static_cast<Header*>(static_cast<void*>(buffer));
    mEntries = static_cast<Entry*>(static_cast<void*>(buffer + sizeof(Header)));
}

}  // namespace ksys::res

