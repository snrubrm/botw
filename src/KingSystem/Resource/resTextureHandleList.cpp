#include "KingSystem/Resource/resTextureHandleList.h"
#include <prim/seadScopedLock.h>

namespace ksys::res {

TextureHandleList::TextureHandleList(sead::Heap* heap) : mCS(heap) {}

TextureHandleList::~TextureHandleList() = default;

bool TextureHandleList::init() {
    mList.initOffset(Entry::getListNodeOffset());
    setInstance(this);
    return true;
}

void TextureHandleList::add(Entry* entry) {
    auto lock = sead::makeScopedLock(mCS);
    mList.pushBack(entry);
}

void TextureHandleList::remove(Entry* entry) {
    auto lock = sead::makeScopedLock(mCS);
    if (entry->isLinked())
        mList.erase(entry);
}

void TextureHandleList::sub_71012BD6BC() {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& entry : mList)
        entry.sub_71012BD4E0();
    mList.clear();
}

}  // namespace ksys::res
