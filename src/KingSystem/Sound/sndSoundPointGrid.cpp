// The TU at 0x71012bf7b4 .. 0x71012c1308 (before sndSoundMgr38_60.cpp): Unk_SoundMgr38_10::_11c0.
#include "KingSystem/Sound/sndSoundPointGrid.h"

namespace ksys::snd {

// NON_MATCHING: clang merges the zero stores at 0xa34 .. 0xa3c and the two floats into wider stores.
Unk_710251ad68::Unk_710251ad68() = default;

Unk_710251ad68::~Unk_710251ad68() {
    finalize();
}

void Unk_710251ad68::finalize() {
    for (s32 i = 0; i < _8.mLists.size(); ++i)
        _8.mLists[i].freeBuffer();
    for (s32 i = 0; i < _260.mLists.size(); ++i)
        _260.mLists[i].freeBuffer();
}

// NON_MATCHING: Lists::init is inlined here (the original calls it).
void Unk_710251ad68::init(sead::Heap* heap) {
    _8.init(20, heap);
    _260.init(40, heap);
    for (s32 i = 0; i < 9; ++i)
        mCellMap[i] = i;
}

void Unk_710251ad68::Lists::init(s32 num, sead::Heap* heap) {
    for (s32 i = 0; i < mLists.size(); ++i)
        mLists[i].allocBuffer(num, heap);
    mNumActors = 0;
}

void Unk_710251ad68::reset() {
    for (s32 i = 0; i < _8.mLists.size(); ++i)
        _8.mLists[i].clear();
    _8.mNumActors = 0;
    for (s32 i = 0; i < _260.mLists.size(); ++i)
        _260.mLists[i].clear();
    _260.mNumActors = 0;
    for (s32 i = 0; i < 9; ++i)
        mCellMap[i] = i;
    mState = 0;
}

}  // namespace ksys::snd
