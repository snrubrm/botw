#include "KingSystem/ActorSystem/AS/ASList.h"
#include <gsys/gsysModelUnit.h>
#include "KingSystem/Resource/Actor/resResourceModelList.h"
#include "KingSystem/Mii/miiUMii.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceASList.h"
#include "KingSystem/System/VFR.h"

namespace ksys::as {

// (in this file so that the callers in ASList.cpp cannot see that `a5` is unused here)
// NON_MATCHING: when the define is not found and `a5` is false the original calls
// `as_list->getPath().findIndex("Dummy.baslist")` and drops the result (a stripped diagnostic); the compiler removes
// the call here because the result is unused.
ASList::Unk8* ASList::sub_710115AABC(const sead::SafeString& name, sead::SafeString* out_name,
                                     bool* out_a3, void** out_a4, bool a5) {
    *out_a3 = false;
    *out_a4 = nullptr;
    if (!_d8)
        return nullptr;

    Unk8* result;
    const s32 index = _d8->getParam()->getRes().mASList->findASDefine(name);
    if (index >= 0) {
        result = &_138[index];
        *out_name = _d8->getParam()->getRes().mASList->getASDefines()[index].name.ref();
        *out_a4 = _d8->getParam()->getRes().mASList->getASDefines()[index].as;
        return result;
    } else {
        Unk6* node = _148;
        while (node && !(name == node->_18))
            node = node->_30;
        if (!node)
            return nullptr;
        *out_a3 = true;
        if (_160 > (*_c8.begin())->_0->sub_7101258E08() ||
            _162 > (*_c8.begin())->_0->sub_7101258E20() ||
            _161 > (*_c8.begin())->_0->sub_7101258E14()) {
            if (!_158)
                return nullptr;
        }
        *out_name = node->_18;
        *out_a4 = const_cast<res::AS*>(node->_28);
        return node;
    }
}

// (in this file because the original does not inline Unk2::sub_7101162E88 into it)
void ASList::sub_710115C1D0(int slot, int other_slot, int bank, int other_bank) {
    const bool a1 = other_slot > slot || (other_slot == slot && other_bank >= bank);
    auto* entry = getEntry(slot, bank);
    if (!entry)
        return;
    auto* other_entry = getEntry(other_slot, other_bank);
    entry->sub_7101162E88(other_entry, a1);
}

void ASList::Unk1::sub_7101164EB8() {
    Unk2* first = nullptr;
    f32 highest = 0.0f;
    for (auto& entry : _20) {
        entry.sub_7101162318();
        if (entry._18) {
            if (!first)
                first = &entry;
            highest = entry._10 > highest ? entry._10 : highest;
        }
    }
    if (highest < 1.0f && first)
        first->_10 = 1.0f;
}

// NON_MATCHING: register allocation only (the address of `_8` is computed before the loop here, after it in the
// original, which shifts the loop registers by one).
bool ASList::Unk1::sub_7101164CA4(f32 delta) {
    bool running = false;
    if (_8._c < 1.0f) {
        f32 weight = 1.0f;
        if (_20.size() != 0) {
            f32 sum = 0.0f;
            f32 total = 0.0f;
            for (auto& entry : _20) {
                if (!entry._18 && sead::Mathf::equalsEpsilon(entry.sub_71011631D0(), 1.0f))
                    continue;
                sum += entry._10 * entry.sub_71011631D0();
                total += entry._10;
            }
            if (total > 0.0f) {
                weight = sum;
                if (total > 1.0f)
                    weight = sum / total;
            }
        }
        f32 step = weight * VFR::instance()->getDeltaFrame();
        _8.sub_71011598FC(step * delta);
        running = _8._c < 1.0f;
    }
    if (!running && _4d && _30) {
        _4d = false;
        _30->sub_7100BFF4CC(_0, &_38);
    }
    return running;
}

void ASList::Unk1::sub_7101164B24() {
    for (auto& entry : _20)
        entry.sub_710116173C();
}

bool ASList::Unk1::sub_71011653A4() const {
    return _4e[0] == 2;
}

bool ASList::Unk1::sub_71011653B4() const {
    return _4e[0] == 1;
}

bool ASList::Unk1::sub_71011653C4() const {
    return _4e[0] == 0;
}

// NON_MATCHING: selected entry/index updates use conditional selects instead of a branch.
ASList::Unk2* ASList::Unk1::sub_7101165278(s32* index) {
    f32 value = 0.0f;
    f32 highest = 0.0f;
    Unk2* selected = nullptr;
    s32 selected_index = -1;
    for (auto& entry : _20) {
        if (!entry._18)
            continue;
        const s32 entry_index = entry.sub_710116360C(&value);
        value *= entry._10;
        if (highest < value) {
            highest = value;
            selected_index = entry_index;
            selected = &entry;
        }
    }
    if (index)
        *index = selected_index;
    return selected;
}

ASList::Unk2* ASList::Unk1::sub_710116532C(s32* index) {
    for (auto& entry : _20) {
        if (!entry._18)
            continue;
        const s32 entry_index = entry.sub_710116367C();
        if (entry_index >= 0) {
            if (index)
                *index = entry_index;
            return &entry;
        }
    }
    if (index)
        *index = -1;
    return nullptr;
}

bool ASList::Unk1::sub_71011650B8(int row, int bit) const {
    if (!_30)
        return true;
    return _38[row].words[bit >> 5] & (1u << (bit & 0x1f));
}

bool ASList::Unk1::sub_7101164C24(const gsys::BoneAccessKey& key) const {
    if (!key.isValid())
        return false;
    if (!_30)
        return true;
    return sub_71011650B8(key.model_unit_index, key.bone_index) && !_4d;
}

void ASList::Unk1::sub_7101164F3C(sead::Vector3f* a1, sead::Vector3f* a2,
                                  const gsys::BoneAccessKey* key) {
    if (!key->isValid())
        return;
    if (_30) {
        if (!sub_71011650B8(key->model_unit_index, key->bone_index))
            return;
        if (_4d)
            return;
    }
    for (auto& entry : _20)
        entry.sub_7101162DE4(a1, a2, key);
}

// NON_MATCHING: the selected key lives at sp + 0xc here, at sp + 8 in the original (an 8-byte object in the original).
void ASList::Unk1::sub_7101164B5C(const gsys::BoneAccessKey* key, sead::Vector3f* a2, sead::Vector3f* a3) {
    gsys::BoneAccessKey selected;
    if (key->isValid()) {
        if (!_30 || (sub_71011650B8(key->model_unit_index, key->bone_index) && !_4d))
            selected = *key;
    }
    for (auto& entry : _20)
        entry.sub_7101162454(&selected, a2, a3);
}

bool ASList::Unk1::sub_71011650FC(f32 value, sead::Matrix34f* out, bool full, gsys::BoneAccessKey* key) {
    if (!key->isValid())
        return false;
    if (_30) {
        if (!sub_71011650B8(key->model_unit_index, key->bone_index))
            return false;
        if (_4d)
            return false;
    }
    out->makeIdentity();
    bool result = false;
    f32 total = 0.0f;
    for (auto& entry : _20) {
        if (entry._10 < 0.001f)
            continue;
        if (result) {
            sead::Matrix34f other;
            if (entry.sub_71011636CC(value, &other, full, key)) {
                total += entry._10;
                sub_71011658C0(entry._10 / total, out, out, &other);
            }
        } else {
            if (!entry.sub_71011636CC(value, out, full, key)) {
                result = false;
                continue;
            }
            total += entry._10;
        }
        result = true;
    }
    return result;
}

void ASList::Unk1::sub_7101164E64(BoneBlendState* state) {
    _48 = 0.0f;
    for (auto& entry : _20)
        entry.sub_7101162C58(_30, state);
}

void ASList::Unk1::sub_7101164E38(bool a1) {
    if (!_30)
        return;
    if (a1) {
        _4d = true;
        return;
    }
    _4d = false;
    _30->sub_7100BFF4CC(_0, &_38);
}

// NON_MATCHING: model-unit and key loads are shared across the two branches.
void ASList::Unk1::sub_7101165008(const gsys::BoneAccessKey& key, int mode, bool variant) {
    auto* partial = _30;
    if (!partial)
        return;
    auto* model = _0;
    if (variant) {
        const auto name = model->getUnits()[key.model_unit_index]->mModelUnit->getBoneName(key.bone_index);
        partial->sub_7100BFF95C(model, name, mode);
    } else {
        const auto name = model->getUnits()[key.model_unit_index]->mModelUnit->getBoneName(key.bone_index);
        partial->sub_7100BFF8E4(model, name, mode);
    }
}

namespace {
const char* const sPartialBoneNames[] = {
    "DFM_Spine_1", "DFM_Spine_2", "DFM_Waist", "DFM_Neck_Controlled", "DFM_Chin", "DFM_Lip",
    "Neck_Root", "Head_Controled", "Ear_L", "Ear_R", "Beard_Base", "Lip_U_Scale_Trans",
    "Null_Teeth_U", "Nose", "Nose_U", "Null_Nose_Base", "Lip_D_Root", "Lip_D_Scale",
    "Nose_Root", "Hair_Root", "Glass_Root", "Mustache_Root", "Hat_Root",
};
}

// NON_MATCHING: typed key checks and folded constant names change scheduling and size.
void ASList::Unk1::sub_7101164900(const res::ModelList* model_list, int idx, act::Actor* actor) {
    if (!_30)
        return;
    _30->mCount = 0;
    const s32 count = model_list->getNumPartials(idx);
    for (s32 i = 0; i < count; ++i) {
        res::ModelList::PartialInfo info;
        model_list->getPartialInfo(&info, idx, i);
        const auto key = _0->searchBone(info.bone);
        if (!key.isValid())
            continue;
        if (info.recursible)
            _30->sub_7100BFF95C(_0, info.bone, info.bind_flag);
        else
            _30->sub_7100BFF8E4(_0, info.bone, info.bind_flag);
    }
    if (_4e[0] != 2 && actor->sub_71011C7A98() &&
        *actor->getUMii()->getBody().race == mii::UMii::Body::Race_Hylian) {
        for (s32 i = 6; i < 23; ++i)
            _30->sub_7100BFF8E4(_0, sPartialBoneNames[i], 3);
        for (s32 i = 0; i < 6; ++i)
            _30->sub_7100BFF95C(_0, sPartialBoneNames[i], 3);
    }
    if (_30) {
        _4d = false;
        _30->sub_7100BFF4CC(_0, &_38);
    }
}

void ASList::Unk1::sub_7101164FF8() {
    // This halfword is the registered key count also incremented by the two
    // library registration methods at 0x7100bff8e4 and 0x7100bff95c.
    if (_30)
        _30->mCount = 0;
}

}  // namespace ksys::as
