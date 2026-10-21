// The TU at 0x71012bf7b4 .. 0x71012c1308 (before sndSoundMgr38_60.cpp): Unk_SoundMgr38_10::_11c0.
#include "KingSystem/Sound/sndSoundPointGrid.h"
#include <aal/aalListener.h>
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Sound/sndInfoData.h"

namespace ksys::snd {

// NON_MATCHING: clang merges the zero stores at 0xa34 .. 0xa3c and the two floats into wider stores.
Unk_710251ad68::Unk_710251ad68() = default;

Unk_710251ad68::~Unk_710251ad68() {
    finalize();
}

void Unk_710251ad68::finalize() {
    for (s32 i = 0; i < mLists[0].mLists.size(); ++i)
        mLists[0].mLists[i].freeBuffer();
    for (s32 i = 0; i < mLists[1].mLists.size(); ++i)
        mLists[1].mLists[i].freeBuffer();
}

// NON_MATCHING: Lists::init is inlined here (the original calls it).
void Unk_710251ad68::init(sead::Heap* heap) {
    mLists[0].init(20, heap);
    mLists[1].init(40, heap);
    for (s32 i = 0; i < 9; ++i)
        mCellMap[i] = i;
}

void Unk_710251ad68::Lists::init(s32 num, sead::Heap* heap) {
    for (s32 i = 0; i < mLists.size(); ++i)
        mLists[i].allocBuffer(num, heap);
    mNumActors = 0;
}

void Unk_710251ad68::reset() {
    for (s32 i = 0; i < mLists[0].mLists.size(); ++i)
        mLists[0].mLists[i].clear();
    mLists[0].mNumActors = 0;
    for (s32 i = 0; i < mLists[1].mLists.size(); ++i)
        mLists[1].mLists[i].clear();
    mLists[1].mNumActors = 0;
    for (s32 i = 0; i < 9; ++i)
        mCellMap[i] = i;
    mState = 0;
}

// NON_MATCHING: the original keeps `set` on the stack (an out-parameter or enum?) and keeps the actor in a
// register only for the searches.
bool Unk_710251ad68::sub_71012C0898(map::Unk_71012497f8Entry* entry) {
    if (!entry->_80)
        return true;

    const char* name = entry->mName.cstr();
    s32 set = 0;

    for (s32 i = 0; i < _a30; ++i) {
        if (_8f0[i] == entry->_10)
            return true;
    }

    bool known = false;
    for (s32 i = 0; i < mLists[0].mNumActors; ++i) {
        if (mLists[0].mActors[i] == entry->_10) {
            set = 0;
            known = true;
            break;
        }
    }
    if (!known) {
        for (s32 i = 0; i < mLists[1].mNumActors; ++i) {
            if (mLists[1].mActors[i] == entry->_10) {
                set = 1;
                known = true;
                break;
            }
        }
    }

    if (!known) {
        const char* user = act::InfoData::instance()->getSLinkUser(name);
        const sead::SafeString type =
            InfoData::instance()->getMiscPlantShakeType(InfoData::instance()->getInfo(user));
        if (type == "None") {
            if (_a30 < 40) {
                _8f0[_a30] = entry->_10;
                ++_a30;
            }
            return true;
        }
        if (type == "Bush")
            set = 0;
        else if (type == "Grass")
            set = 1;
        else
            return true;

        auto& lists = mLists[set];
        if (lists.mNumActors < 20) {
            lists.mActors[lists.mNumActors] = entry->_10;
            ++lists.mNumActors;
        }
    }

    if (auto* pos = mLists[set].mLists[_8e8].emplaceBack())
        *pos = entry->mPosition;
    return true;
}

void Unk_710251ad68::updatePoints(const aal::Listener* listener) {
    for (s32 i = 0; i < 2; ++i) {
        for (s32 dir = 0; dir < 32; ++dir)
            mPoints[i][dir].distance = sead::Mathf::maxNumber();

        for (s32 cell = 0; cell < mLists[i].mLists.size(); ++cell) {
            for (auto& pos : mLists[i].mLists[cell]) {
                sead::Vector3f local;
                listener->calcLocalPosition(&local, pos);
                u32 dir = 0;
                if (local.x != 0.0f || local.z != 0.0f)
                    dir = sead::Mathf::atan2Idx(local.z, local.x) >> 27;
                const f32 distance = local.length();
                if (distance < mPoints[i][dir].distance) {
                    mPoints[i][dir].pos = pos;
                    mPoints[i][dir].distance = distance;
                }
            }
        }
    }
}

}  // namespace ksys::snd
