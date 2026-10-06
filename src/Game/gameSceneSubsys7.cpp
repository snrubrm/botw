#include "Game/gameSceneSubsys7.h"
#include <heap/seadExpHeap.h>

SEAD_SINGLETON_DISPOSER_IMPL(GameSceneSubsys7)

void GameSceneSubsys7::init(sead::Heap* parent) {
    mHeap = sead::ExpHeap::create(0x1900000, "Terrain Scene", parent, sizeof(void*),
                                  sead::Heap::cHeapDirection_Forward, false);
}

void* GameSceneSubsys7::getTeraSystem() const {
    return mTeraSystem;
}
