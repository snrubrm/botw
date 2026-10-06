#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

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

void ASList::Unk1::sub_7101164FF8() {
    if (_30)
        _30->_8 = 0;
}

}  // namespace ksys::as
