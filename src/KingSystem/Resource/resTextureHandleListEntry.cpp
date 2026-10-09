#include "KingSystem/Resource/resTextureHandleList.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

TextureHandleList::Entry::Entry() : _8(false), _10(nullptr), _18(nullptr) {}

TextureHandleList::Entry::~Entry() {
    if (_40.sub_7100FE7FB0()) {
        stubbedLogFunction();
        sub_71012BD338();
    }
}

void TextureHandleList::Entry::Callback::m2(const void* arg) {
    Entry* entry = mOwner;
    if (!entry->isLinked()) {
        entry->_8 = true;
        TextureHandleList::sInstance->add(entry);
    }
}

void TextureHandleList::Entry::Callback::m3(const void* arg) {
    Entry* entry = mOwner;
    if (!entry->isLinked()) {
        entry->_8 = true;
        TextureHandleList::sInstance->add(entry);
    }
}

void TextureHandleList::Entry::Callback::m4(const void* arg) {
    Entry* entry = mOwner;
    if (!entry->isLinked()) {
        entry->_8 = true;
        TextureHandleList::sInstance->add(entry);
    }
}

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

void* TextureHandleList::Entry::sub_71012BD4D8() const {
    return _10;
}

bool TextureHandleList::Entry::sub_71012BD330() const {
    return _40.sub_7100FE7FB0();
}

void TextureHandleList::Entry::sub_71012BD338() {
    if (!_40.sub_7100FE7FB0())
        return;
    TextureHandleList::sInstance->remove(this);
    void* arg;
    _40.sub_7100FE7FBC(&arg);
    _10 = nullptr;
    _18 = nullptr;
}

}  // namespace ksys::res
