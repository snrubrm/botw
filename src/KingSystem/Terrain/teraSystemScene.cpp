#include "KingSystem/Terrain/teraSystem.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Terrain/teraAreaNode.h"

namespace ksys::tera {

void System::sub_7101112A74() {
    const u32 count = mScenes.size();
    for (u32 i = 0; i < count; ++i)
        mScenes[i].scene->sub_7101101964();
    _1338 &= ~8u;
}

void System::sub_71011129CC(const sead::SafeArray<s32, 19>& levels, bool force) {
    if (!force && (_1338 & 8))
        return;
    const u32 count = mScenes.size();
    for (u32 i = 0; i < count; ++i)
        mScenes[i].scene->sub_7101101914(levels);
    if (force)
        _1338 |= 8;
}

void System::sub_71011126C4(s32 value) {
    for (s32 i = 0; i < mScenes.size(); ++i)
        mScenes[i].scene->_2943 = sead::Mathi::max(value, 0);
}

void System::sub_710111F598(bool a, bool b) {
    for (s32 i = 0; i < mScenes.size(); ++i)
        mScenes[i].scene->sub_7101100234(a, b);
}

void System::sub_7101112AF0(s32 a, s32 b) {
    const u32 count = mScenes.size();
    for (u32 i = 0; i < count; ++i)
        mScenes[i].scene->sub_71010FFE70(a, b);
}

void System::sub_7101112B80(s32 a, s32 b, s32 c, s32 d) {
    const u32 count = mScenes.size();
    for (u32 i = 0; i < count; ++i)
        mScenes[i].scene->sub_7101100260(a, b, c, d);
}

void System::sub_7101112C30(const sead::Vector3f& vec) {
    const u32 count = mScenes.size();
    for (u32 i = 0; i < count; ++i) {
        Scene* scene = mScenes[i].scene;
        scene->_2760 = vec;
        scene->_2998 |= 4;
    }
}

void System::sub_7101115158(bool update) {
    if (!_8)
        return;

    if (update) {
        mLock.writeLock();
        for (s32 i = 0; i < mScenes.size(); ++i)
            mScenes[i].scene->sub_710110234C(this);
        _1338 |= 0x10000;
        sub_7101115BAC();
        mLock.writeUnlock();
    } else {
        _1338 |= 0x10002;
    }
}

void System::sub_7101112714(Unk_7101112C94Listener* listener) {
    if (!_8)
        return;

    mLock.writeLock();
    for (s32 i = 0; i < mScenes.size(); ++i)
        mScenes[i].scene->sub_7101101578(this, 0xff0000);

    for (u32 i = 0; i < _eea; ++i) {
        if (_ff8[i] & 1) {
            _ff8[i] &= ~1;
            sub_71011176BC(_fa8[i], false);
        }
    }
    sub_7101115BAC();

    {
        sead::ScopedLock<sead::CriticalSection> lock(&Terrain::instance()->mImageResourceMgr->mCS68);
        sub_7101112C94(_8, listener);
        _8 = nullptr;
        _ee9 = 0;
        mWriteIndex = 0;
        _104c = 0;
        for (s32 i = 0; i < mNumEntries; ++i) {
            Entry& entry = mEntries[i];
            entry.area = nullptr;
            entry.type = sUnk_7101EC54A8;
        }
        ++_1334.generation;
    }
    mLock.writeUnlock();
}

// NON_MATCHING: register allocation.
s32 System::Unk_710111E168::sub_710111E168(Unk_7101106F44* area) {
    System* sys = system;
    if (!area->sub_710111FAFC(sUnk_7101EC54AC, no_child)) {
        if (auto* image = area->getImageMaybe(sUnk_7101EC54AC))
            image->_8 |= 0x40;
    } else if (!Terrain::instance()->sub_710114D928(sys, area, sUnk_7101EC54AC)) {
        if (auto* image = area->getImageMaybe(sUnk_7101EC54AC))
            image->_8 |= 0x40;
    }
    if (!area->sub_710111FAFC(sUnk_7101EC54B4, no_child)) {
        if (auto* image = area->getImageMaybe(sUnk_7101EC54B4))
            image->_8 |= 0x40;
    } else if (!Terrain::instance()->sub_710114D928(sys, area, sUnk_7101EC54B4)) {
        if (auto* image = area->getImageMaybe(sUnk_7101EC54B4))
            image->_8 |= 0x40;
    }
    for (auto* node : area->mNodes) {
        const ImageTypeMaybe type = makeImageTypeMaybe(2, node->sub_7101108614());
        if (!area->sub_710111FAFC(type, no_child)) {
            if (auto* image = area->getImageMaybe(type))
                image->_8 |= 0x40;
        } else if (!Terrain::instance()->sub_710114D928(sys, area, type)) {
            if (auto* image = area->getImageMaybe(type))
                image->_8 |= 0x40;
        }
    }
    for (auto* image3 : area->mImages) {
        const ImageTypeMaybe type = image3->getImageType();
        if (!area->sub_710111FAFC(type, no_child)) {
            if (auto* image = area->getImageMaybe(type))
                image->_8 |= 0x40;
        } else if (!Terrain::instance()->sub_710114D928(sys, area, type)) {
            if (auto* image = area->getImageMaybe(type))
                image->_8 |= 0x40;
        }
    }
    return false;
}

void System::sub_7101112C94(Unk_7101106F44* area, Unk_7101112C94Listener* listener) {
    area->sub_7101107768();
    for (auto* child : area->mChildren) {
        if (child)
            sub_7101112C94(child, listener);
    }
    if (listener)
        listener->m0(area, 5);

    {
        sead::ScopedLock<sead::CriticalSection> lock(&Terrain::instance()->mImageResourceMgr->mCS68);
        Terrain::instance()->mImageResourceMgr->sub_710113625C(this, area, sUnk_7101EC54AC, false,
                                                               nullptr);
        Terrain::instance()->mImageResourceMgr->sub_710113625C(this, area, sUnk_7101EC54B4, false,
                                                               nullptr);
        for (auto* node : area->mNodes) {
            const ImageTypeMaybe type = node->getImageType();
            Terrain::instance()->mImageResourceMgr->sub_710113625C(this, area, type, false, nullptr);
        }
        for (auto* image : area->mImages) {
            const ImageTypeMaybe type = image->getImageType();
            Terrain::instance()->mImageResourceMgr->sub_710113625C(this, area, type, false, nullptr);
        }
    }
    delete area;
}

s32 System::sub_71011188E4() const {
    const Scene* scene = mScenes(0).scene;
    return sead::Mathi::max(scene->_2946 - 1 - scene->_2780, 0);
}

void* System::sub_710111F4F0() {
    return &mScenes(0).scene->_0[5];
}

Unk_710111F504* System::sub_710111F504() {
    return &mScenes(0).scene->_0[8];
}

void System::sub_710111F518(int level, int type) {
    for (s32 i = 0; i < mScenes.size(); ++i)
        mScenes[i].scene->sub_71011001D4(level, type);
}

bool System::sub_710111F618(s32 index) {
    return mScenes[index].scene->_2998 >> 3 & 1;
}

void System::sub_710111F644(void* value) {
    for (s32 i = 0; i < mScenes.size(); ++i)
        mScenes[i].scene->_2948->_afc0 = value;
}

// NON_MATCHING: the original keeps the comparison result in a register before the binary search step
// and checks the found index after the search.
Unk_7101106F44* System::sub_7101115080(u32 id) const {
    if (_1018.size() == 0) {
        for (s32 i = 0; i < _fa8.size(); ++i) {
            if (_fa8.getBufferPtr()[i]->mId == id)
                return _fa8.getBufferPtr()[i];
        }
        return nullptr;
    }

    const s32 idx = _1018.binarySearchC([id](const Unk_7101106F44* entry) {
        if (entry->mId < id)
            return -1;
        return entry->mId > id ? 1 : 0;
    });
    if (idx >= 0 && _1018.isIndexValid(idx))
        return _1018.getBufferPtr()[idx];
    return nullptr;
}

}  // namespace ksys::tera
