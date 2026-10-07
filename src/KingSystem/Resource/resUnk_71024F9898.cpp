#include "KingSystem/Resource/resUnk_71024F9898.h"
#include <gsys/gsysCameraAnimation.h>
#include <gsys/gsysModelResource.h>
#include <nn/g3d/ResFile.h>
#include "KingSystem/Resource/resSystem.h"

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

bool Unk_71024F9898::parse_(u8* data, size_t size, sead::Heap* heap) {
    _38 = gsys::ModelResource::create_(gsys::ModelResource::CreateArg(data + mAllocSize), heap);
    auto* file = _38->getResFile();
    for (s32 i = 0; i < file->mExternalFileCount; ++i) {
        const char* name = file->mEmbeddedFilesDictOffset ?
            file->mEmbeddedFilesDictOffset->GetKey(i).data() : nullptr;
        if (sead::SafeString(name).findIndex("rtcamera") != -1) {
            _48 = file->mEmbeddedFilesOffset[i].data;
            stubbedLogFunction();
            stubbedLogFunction();
            stubbedLogFunction();
            stubbedLogFunction();
            break;
        }
    }
    if (_48)
        return true;
    _40 = gsys::CameraAnimation::create(_38, sead::SafeString(sead::SafeString::cEmptyString), heap);
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
