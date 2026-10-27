#include "Game/gameMapStaticLoadMgr.h"
#include <basis/seadNew.h>
#include <new>
#include <resource/seadResource.h>
#include "KingSystem/AOC/aocManager.h"

namespace ksys::map {

const sead::SafeString* sMapNames;
s32 sNumMubins;
MapStaticMubin* sMubins;
bool sUnk_7102603DD8;
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

void MapStaticLoadMgr::sub_7100E8D984() {
    if (!sUnk_7102603DD8 && sNumMubins > 0) {
        for (s64 i = 0; i < sNumMubins; ++i) {
            // C++14 evaluation order: the original evaluates the destination first.
            sMubins[i].name.operator=(sMapNames[i]);

            ksys::res::LoadRequest request;
            request.mRequester = "MapStaticLoadMgr";
            request._22 = true;
            request._26 = false;

            sead::FixedSafeString<64> path;
            path.format("Map/%s/Static.mubin", sMapNames[i].cstr());

            if (ksys::aoc::Manager::instance())
                request.mAocFileDevice =
                    ksys::aoc::Manager::instance()->getFileDeviceForMapFile(path);

            if ((ksys::aoc::Manager::instance() &&
                 ksys::aoc::Manager::instance()->getVersion() != 0) ||
                !ksys::aoc::Manager::isAocField(sMapNames[i])) {
                // The original discards the cast result.
                sead::DynamicCast<sead::DirectResource>(sMubins[i].handle.load(path, &request));
            }
        }
    }
}

}  // namespace ksys::map

ksys::res::Handle* getMapStaticMubin(const sead::SafeString& name) {
    for (s32 i = 0; i < ksys::map::sNumMubins; ++i) {
        if (ksys::map::sMubins[i].name == name)
            return &ksys::map::sMubins[i].handle;
    }
    return nullptr;
}
