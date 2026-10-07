#include "KingSystem/Resource/resResourceJpg.h"
#include <common/aglTextureData.h>

namespace ksys::res {

ResourceJpg::ResourceJpg() = default;

// NON_MATCHING: the original inlines TextureData destruction; the real library destructor stays emitted.
ResourceJpg::~ResourceJpg() {
    _50 = false;
    if (_70) {
        _38.InvalidateDescriptorSlot();
        _70->getImagePtr().deleteGPUMemBlock();
        delete _70;
        _70 = nullptr;
    }
    if (_78) {
        _58.InvalidateDescriptorSlot();
        _78->getImagePtr().deleteGPUMemBlock();
        delete _78;
        _78 = nullptr;
    }
}

s32 ResourceJpg::getLoadDataAlignment() const {
    return cLoadDataAlignment;
}

bool ResourceJpg::m2_() {
    return _50;
}

// NON_MATCHING: TextureData destruction remains an actual library call rather than its inlined NVNtexture body.
void ResourceJpg::onDestroy_() {
    _50 = false;
    if (_70) {
        _38.InvalidateDescriptorSlot();
        _70->getImagePtr().deleteGPUMemBlock();
        delete _70;
        _70 = nullptr;
    }
    if (_78) {
        _58.InvalidateDescriptorSlot();
        _78->getImagePtr().deleteGPUMemBlock();
        delete _78;
        _78 = nullptr;
    }
}

}  // namespace ksys::res
