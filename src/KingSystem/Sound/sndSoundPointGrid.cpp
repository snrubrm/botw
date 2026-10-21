// The TU at 0x71012bf7b4 .. 0x71012c1308 (before sndSoundMgr38_60.cpp): Unk_SoundMgr38_10::_11c0.
#include "KingSystem/Sound/sndSoundPointGrid.h"
#include <cstring>
#include <aal/aalListener.h>
#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Sound/sndInfoData.h"

namespace ksys::snd {

namespace {
// The sub-cells around the listener that updateCells fills in turn.
const sead::Vector2i sOffsets[9] = {{0, 0},  {-1, -1}, {0, -1}, {1, -1}, {1, 0},
                                    {1, 1},  {0, 1},   {-1, 1}, {-1, 0}};
}  // namespace

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

// NON_MATCHING: regalloc in the list clears, the row index of the old cell map and scheduling of the sub-cell
// index.
void Unk_710251ad68::updateCells(map::PlacementMgr* mgr, const aal::Listener* listener) {
    sead::Vector3f pos;
    listener->getMatrix().getTranslation(pos);
    sead::Vector2i cell;
    mgr->sub_71011EB43C(&cell, &pos);

    if (cell.x != mCell.x || cell.y != mCell.y) {
        const s32 dx = cell.x - mCell.x;
        const s32 dy = cell.y - mCell.y;
        s32 map[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
        bool free[9] = {true, true, true, true, true, true, true, true, true};

        for (s32 y = 0; y < 3; ++y) {
            const s32 old_y = y + dy;
            if (0 <= old_y && old_y < 3) {
                for (s32 x = 0; x < 3; ++x) {
                    const s32 old_x = x + dx;
                    if (0 <= old_x && old_x < 3) {
                        const s32 list = mCellMap[old_y * 3 + old_x];
                        free[list] = false;
                        map[y * 3 + x] = list;
                    }
                }
            }
        }

        for (s32 i = 0; i < 9; ++i) {
            if (map[i] >= 0)
                continue;
            for (s32 list = 0; list < 9; ++list) {
                if (!free[list])
                    continue;
                mLists[0].mLists[list].clear();
                mLists[0].mNumActors = 0;
                mLists[1].mLists[list].clear();
                mLists[1].mNumActors = 0;
                free[list] = false;
                map[i] = list;
                break;
            }
        }

        std::memcpy(mCellMap, map, sizeof(map));
    }

    mCell = cell;

    const sead::Vector2i offset = sOffsets[_8e4];
    sead::Vector3f query = pos;
    sead::Vector3f d = sead::Vector3f::zero;
    d.x = offset.x * 20.0f;
    d.z = offset.y * 20.0f;
    query.setAdd(d, query);
    _8e4 = _8e4 >= 8 ? 0 : _8e4 + 1;

    _8e8 = mCellMap[4 + offset.x + offset.y * 3];
    mLists[0].mLists[_8e8].clear();
    mLists[0].mNumActors = 0;
    mLists[1].mLists[_8e8].clear();
    mLists[1].mNumActors = 0;
    _a30 = 0;

    sead::Delegate1R<Unk_710251ad68, map::Unk_71012497f8Entry*, bool> callback(
        this, &Unk_710251ad68::sub_71012C0898);
    mgr->sub_71011EB428(&query, 0.0f, false, &callback);

    if (!mgr)
        return;
    for (auto& obj : mgr->mTraverseResults[1 - mgr->mTraverseResultIdx]._70) {
        if (auto* p = mLists[0].mLists[_8e8].emplaceBack())
            *p = obj.getTranslate();
    }
}

// NON_MATCHING: when the actor is found in the first set, the original stores the type from a register (ours stores
// wzr).
bool Unk_710251ad68::sub_71012C0898(map::Unk_71012497f8Entry* entry) {
    if (!entry->_80)
        return true;

    const char* name = entry->mName.cstr();
    SoundType set = SoundType::cBush;
    void* const actor = entry->_10;

    for (s32 i = 0; i < _a30; ++i) {
        if (_8f0[i] == actor)
            return true;
    }

    bool known = false;
    for (s32 i = 0; i < mLists[0].mNumActors; ++i) {
        if (mLists[0].mActors[i] == actor) {
            set = SoundType::cBush;
            known = true;
            break;
        }
    }
    if (!known) {
        for (s32 i = 0; i < mLists[1].mNumActors; ++i) {
            if (mLists[1].mActors[i] == actor) {
                set = SoundType::cGrass;
                known = true;
                break;
            }
        }
    }

    if (!known) {
        const char* user = act::InfoData::instance()->getSLinkUser(name);
        const al::ByamlIter info = InfoData::instance()->getInfo(user);
        const sead::SafeString type = InfoData::instance()->getMiscPlantShakeType(info);
        if (type == "None") {
            if (_a30 < 40) {
                _8f0[_a30] = entry->_10;
                ++_a30;
            }
            return true;
        }
        if (type == "Bush")
            set = SoundType::cBush;
        else if (type == "Grass")
            set = SoundType::cGrass;
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
