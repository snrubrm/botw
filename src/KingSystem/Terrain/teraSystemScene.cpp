#include "KingSystem/Terrain/teraSystem.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadEndian.h>
#include <prim/seadPtrUtil.h>
#include <prim/seadScopedLock.h>
#include <prim/seadStringUtil.h>
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

// NON_MATCHING: bit 7 of the debug byte is tested through a sign-extending load in ours.
// NON_MATCHING: stack layout of the token iterator and the string.
bool System::sub_710111B16C(const sead::SafeString& version) {
    u32 major = -1;
    u32 minor = -1;
    auto it = version.tokenBegin(".");
    sead::FixedSafeString<64> token;
    it.getAndForward(&token);
    sead::StringUtil::tryParseU32(&major, token, sead::StringUtil::CardinalNumber::BaseAuto);
    it.getAndForward(&token);
    sead::StringUtil::tryParseU32(&minor, token, sead::StringUtil::CardinalNumber::BaseAuto);

    if (major == 10) {
        if (minor == 0)
            return true;
        if (auto* debug = Terrain::instance()->_a50) {
            auto entry = debug->_70.log("【データロード】マイナーバージョンの不一致");
            if (entry.buffer)
                entry.buffer->setDisplayTime(10.0f);
        }
        return false;
    }
    if (major == 9 && minor == 1)
        return true;
    if (auto* debug = Terrain::instance()->_a50) {
        auto entry = debug->_70.log("【データロード】メジャーバージョンの不一致");
        if (entry.buffer)
            entry.buffer->setDisplayTime(10.0f);
    }
    return false;
}

void System::sub_7101115584(s32 index, Unk_7101115584Arg* arg) {
    if (!_8)
        return;
    mLock.readLock();
    SceneSlot& slot = mScenes[index];
    slot._88 = true;
    slot.scene->sub_7101100F08(this, arg,
                               (_1338 & 2) || (Terrain::instance()->_a50->_1d >> 4 & 1));
    if (arg->_198) {
        auto* debug = Terrain::instance()->_a50;
        if (!debug || !(debug->_18 >> 7 & 1))
            sub_7101115338(arg->_0, _8, _1c, _24);
    }
    sub_7101115674(arg);
    mLock.readUnlock();
}

// NON_MATCHING: the delegate set-up is scheduled differently.
bool System::loadScene(sead::Heap* heap, const sead::XmlDocument* doc, const sead::SafeString& dir,
                       bool keep_flags) {
    mLock.writeLock();
    sub_7101112714(nullptr);
    Terrain::instance()->_380->sub_71011382EC();
    sub_7101119278(dir, !keep_flags);

    bool ok = false;
    if (parseSceneXmlMaybe(heap, doc->getRoot())) {
        if (!keep_flags) {
            Unk_710111E168 context{this, true};
            sead::Delegate1R<Unk_710111E168, Unk_7101106F44*, s32> delegate(
                &context, &Unk_710111E168::sub_710111E168);
            _8->sub_7101107DB0(4, &delegate);
        }
        if (!(Terrain::instance()->_a58 & 1))
            x_2();
        x_3();
        ok = true;
    }
    mLock.writeUnlock();
    return ok;
}

// NON_MATCHING: the byte swap loop keeps a separate pointer to _10 in the original.
bool System::sub_710111DD0C(sead::Heap* heap, SceneBinaryMaybe* data) {
    if (data->magic[0] != 'T' || data->magic[1] != 'S' || data->magic[2] != 'C' || data->magic[3] != 'B') {
        if (auto* debug = Terrain::instance()->_a50) {
            auto entry = debug->_70.log("[tscb 読み込み失敗] シグネチャが違います");
            if (entry.buffer)
                entry.buffer->setDisplayTime(10.0f);
        }
        return false;
    }
    if (data->version_major != 10 || data->version_minor != 0) {
        if (auto* debug = Terrain::instance()->_a50) {
            auto entry = debug->_70.log(
                "[tscb 読み込み失敗] ファイルのバージョンが違います : require %d.%d - exist %d.%d", 10, 0,
                data->version_major, data->version_minor);
            if (entry.buffer)
                entry.buffer->setDisplayTime(10.0f);
        }
        return false;
    }

    if (data->swapped != 1) {
        data->swapped = sead::Endian::swapU32(data->swapped);
        data->swap_size = sead::Endian::swapU32(data->swap_size);
        for (u32 i = 0; i < data->swap_size; i += 4) {
            auto* word = static_cast<u32*>(sead::PtrUtil::addOffset(&data->_10, i));
            *word = sead::Endian::swapU32(*word);
        }
    }

    Terrain::instance()->_3c8 = data->_10;
    Terrain::instance()->_3cc = data->_14;
    _10 = data->_20;
    _18 = data->_28;
    _1c = Terrain::instance()->sub_710114D8E4(this);
    _24 = Terrain::instance()->sub_710114D8F8(this);

    const SceneOffsetMaybe<SceneBinaryMaybe::Material>* materials = data->materials.get();
    if (Terrain::instance()->_a58 & 1)
        Terrain::instance()->_370->_4ae0->_10.sub_71011406CC(data->num_materials);
    const u32 num_materials =
        sead::Mathu::min(data->num_materials, u32(Terrain::instance()->_370->_4ae0->_10._700));
    for (u32 i = 0; i < num_materials; ++i) {
        const SceneBinaryMaybe::Material* material = materials[i].get();
        MaterialUVWMaybe& entry = _e8[s32(i)];
        entry.value = material->value;
        entry._4 = material->_4;
        entry._8 = material->_8;
        entry._c = material->_c;
        entry._10 = material->_10;
    }

    const SceneOffsetMaybe<SceneBinaryMaybe::Area>* areas = data->areas.get();
    for (u32 i = 0; i < data->num_areas; ++i) {
        const SceneBinaryMaybe::Area* area = areas[i].get();
        const f32 scale = Terrain::instance()->_3c8;
        const sead::Vector2f pos = {area->pos.x * scale, area->pos.y * scale};
        Unk_7101106F44* node = sub_7101117A08(area->size, heap, &pos, 0, nullptr);
        sub_710111DAB8(heap, node, area);
        _10 = data->_20;
    }
    return true;
}

// NON_MATCHING: as loadScene.
bool System::sub_710111E960(sead::Heap* heap, SceneBinaryMaybe* data, size_t size,
                            const sead::SafeString& dir, bool keep_flags) {
    mLock.writeLock();
    sub_7101112714(nullptr);
    Terrain::instance()->_380->sub_71011382EC();
    sub_7101119278(dir, !keep_flags);

    bool ok = false;
    if (sub_710111DD0C(heap, data)) {
        if (!keep_flags) {
            Unk_710111E168 context{this, true};
            sead::Delegate1R<Unk_710111E168, Unk_7101106F44*, s32> delegate(
                &context, &Unk_710111E168::sub_710111E168);
            _8->sub_7101107DB0(4, &delegate);
        }
        if (!(Terrain::instance()->_a58 & 1))
            x_2();
        x_3();
        ok = true;
    }
    mLock.writeUnlock();
    return ok;
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

Unk_71010FEDBC* System::sub_710111F4F0() {
    return &mScenes(0).scene->_0[5];
}

Unk_71010FEDBC* System::sub_710111F504() {
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
