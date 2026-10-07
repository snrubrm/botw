#include "KingSystem/Resource/resUnk_71024F9898.h"
#include <gsys/gsysCameraAnimation.h>
#include <gsys/gsysModelResource.h>
#include <nn/g3d/ResFile.h>

namespace ksys::res {

Unk_71024F9898::Unk_71024F9898() = default;
Unk_71024F9898::~Unk_71024F9898() = default;

s32 Unk_71024F9898::getLoadDataAlignment() const {
    return cLoadDataAlignment;
}

bool Unk_71024F9898::needsParse() const {
    return true;
}

bool Unk_71024F9898::m2_() {
    return _40 != nullptr;
}

void Unk_71024F9898::onDestroy_() {
    if (_40) {
        gsys::CameraAnimation::sub_71014092F8(_40);
        _40 = nullptr;
    }
    if (_38) {
        auto* file = _38->getResFile();
        gsys::ModelResource::sub_7100C0B764(_38);
        _38 = nullptr;
        file->Unrelocate();
    }
}

}  // namespace ksys::res
