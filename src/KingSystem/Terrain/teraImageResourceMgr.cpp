#include "KingSystem/Terrain/teraAreaNode.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

// NON_MATCHING: the type-2 search keeps the list node and calls getA from two places in the original.
void ImageResourceMgr::sub_71011339D0(Request* request) {
    const Unk_710250dcd8* image = request->area->getImageMaybe(request->type);
    if (image && image->_8 & 8)
        request->area->sub_71011080D4(request->type);
}

}  // namespace ksys::tera
