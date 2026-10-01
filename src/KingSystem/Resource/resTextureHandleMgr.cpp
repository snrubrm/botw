#include "KingSystem/Resource/resTextureHandleMgr.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

void TextureHandleMgr::preCalc() {}

void TextureHandleMgr::sub_7100FE60B0(bool on) {
    if (mFlags.isOn(2) != on) {
        mFlags.change(2, on);
        stubbedLogFunction();
    }
}

void TextureHandleMgr::sub_7100FE60DC(bool on) {
    if (mFlags.isOn(1) != on) {
        mFlags.change(1, on);
        mFlags.change(4, on);
        stubbedLogFunction();
    }
}

bool TextureHandleMgr::sub_7100FE6120() const {
    return mFlags2.isOn(2);
}

ArchiveWork* TextureHandleMgr::getArchiveWork() const {
    return mArchiveWork;
}

}  // namespace ksys::res
