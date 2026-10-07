#include "KingSystem/Resource/resTextureHandleList.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

TextureHandleList* TextureHandleList::sInstance;

void TextureHandleList::setInstance(TextureHandleList* list) {
    sInstance = list;
}

bool TextureHandleList::Entry::isLinked() const {
    return mListNode.isLinked();
}

void TextureHandleList::Entry::sub_71012BD4E0() {
    if (_8) {
        if (!_18) {
            stubbedLogFunction();
            return;
        }
        _18->m0(this);
        _8 = false;
    }
}

}  // namespace ksys::res
