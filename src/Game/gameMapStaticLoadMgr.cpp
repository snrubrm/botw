#include "Game/gameMapStaticLoadMgr.h"
#include <basis/seadNew.h>
#include <new>

namespace ksys::map {

const sead::SafeString* sMapNames;
s32 sNumMubins;
MapStaticMubin* sMubins;
void* sUnk_7102603DE0;
void* sUnk_7102603DE8;

void MapStaticLoadMgr::loadStaticFiles(const sead::SafeString* names, s32 count, sead::Heap* heap,
                                       void* callback1, void* callback2) {
    sMapNames = names;
    sNumMubins = count;
    sUnk_7102603DE0 = callback1;
    sUnk_7102603DE8 = callback2;

    sMubins = new (heap, 8) MapStaticMubin[count];
    sub_7100E8D984();
}

}  // namespace ksys::map

ksys::res::Handle* getMapStaticMubin(const sead::SafeString& name) {
    for (s32 i = 0; i < ksys::map::sNumMubins; ++i) {
        if (ksys::map::sMubins[i].name == name)
            return &ksys::map::sMubins[i].handle;
    }
    return nullptr;
}
