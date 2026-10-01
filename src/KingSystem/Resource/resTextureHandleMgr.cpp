#include "KingSystem/Resource/resTextureHandleMgr.h"

namespace ksys::res {

void TextureHandleMgr::preCalc() {}

ArchiveWork* TextureHandleMgr::getArchiveWork() const {
    return mArchiveWork;
}

}  // namespace ksys::res
