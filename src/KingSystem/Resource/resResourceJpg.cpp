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

Unk_710247eb88::Unk_710247eb88() = default;

// NON_MATCHING: TextureData destruction is emitted rather than the original inlined NVNtexture body.
Unk_710247eb88::~Unk_710247eb88() {
    _38 = false;
    if (_70) {
        _40.InvalidateDescriptorSlot();
        _70->getImagePtr().deleteGPUMemBlock();
        delete _70;
        _70 = nullptr;
    }
    _39 = false;
    if (_78) {
        _58.InvalidateDescriptorSlot();
        _78->getImagePtr().deleteGPUMemBlock();
        delete _78;
        _78 = nullptr;
    }
}

s32 Unk_710247eb88::getLoadDataAlignment() const {
    return 0x2000;
}

// NON_MATCHING: TextureData destruction stays emitted instead of its inlined NVNtexture body.
void Unk_710247eb88::sub_71009CD5F8() {
    _38 = false;
    if (_70) {
        _40.InvalidateDescriptorSlot();
        _70->getImagePtr().deleteGPUMemBlock();
        delete _70;
        _70 = nullptr;
    }
}

// NON_MATCHING: TextureData destruction stays emitted instead of its inlined NVNtexture body.
void Unk_710247eb88::sub_71009CD66C() {
    _39 = false;
    if (_78) {
        _58.InvalidateDescriptorSlot();
        _78->getImagePtr().deleteGPUMemBlock();
        delete _78;
        _78 = nullptr;
    }
}

void Unk_710247eb88::sub_71009CDAE8() {
    _38 = false;
    _39 = false;
    if (_70) {
        _40.InvalidateDescriptorSlot();
        _70 = nullptr;
    }
    if (_78) {
        _58.InvalidateDescriptorSlot();
        _78 = nullptr;
    }
}

}  // namespace ksys::res
