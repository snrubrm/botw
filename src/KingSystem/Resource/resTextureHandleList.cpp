#include "KingSystem/Resource/resTextureHandleList.h"
#include <prim/seadScopedLock.h>
#include "Game/gameUnkRttiPlaceholders.h"

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

// NON_MATCHING: placeholder destructor; the original (0x71012bdc1c) also destroys members or bases
// this class does not declare yet.
Unk_710251ab30::~Unk_710251ab30() = default;
