#include "KingSystem/Terrain/teraAreaNode.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

// NON_MATCHING: the type-2 search keeps the list node and calls getA from two places in the original.
void ImageResourceMgr::sub_71011339D0(Request* request) {
    const Unk_710250dcd8* image = request->area->getImageMaybe(request->type);
    if (image && image->_8 & 8)
        request->area->sub_71011080D4(request->type);
}

// NON_MATCHING: the original keeps the list node and reloads the found node from it.
bool Unk_7101118B34::sub_7101118B34(sead::Heap* heap, Unk_7101106F44* area,
                                    Unk_710110d278::Key* key, bool check) {
    Unk_7101108460* found = nullptr;
    for (Unk_7101108460* node : area->mNodes) {
        if (node->getB()->_8 == key) {
            found = node;
            break;
        }
    }

    if (found) {
        if (!check || !(Terrain::instance()->_a58 & 0x400) || found->getA()->_8 & 1)
            return true;
        return false;
    }

    if (area->mParent && !sub_7101118B34(heap, area->mParent, key, check))
        return false;

    Unk_7101108460* node = area->sub_7101108460(heap, key);
    if (!node)
        return false;
    if (check)
        node->getA()->_8 |= 1;
    return true;
}

// NON_MATCHING: two registers swapped in the type-3 loop.
void Unk_7101118B34::sub_71011176BC(Unk_7101106F44* area, bool flag) {
    void (Unk_7101118B34::*fn)(Unk_7101106F44*, const ImageTypeMaybe&) =
        flag ? &Unk_7101118B34::sub_71011171D8 : &Unk_7101118B34::sub_710111731C;

    (this->*fn)(area, sUnk_7101EC54AC);
    (this->*fn)(area, sUnk_7101EC54B4);
    for (Unk_7101108460* node : area->mNodes)
        (this->*fn)(area, node->getImageType());
    for (Unk_710250db28* image : area->mImages)
        (this->*fn)(area, image->getImageType());
}

}  // namespace ksys::tera
