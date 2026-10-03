#include "Game/AI/aiUnk_71025be918.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace {
// inline-only in the original; names are guesses (the same sequences are inlined into 0x7100707ba4 /
// 0x7100707e84 / 0x7100708214: the early `this + 0x20` / `this + 0x8` computations are the pointer
// parameters of these helpers).
void setPartialBone(ksys::as::ASList* as_list, s32 slot, const sead::SafeString& bone, s32 mode) {
    const auto key = as_list->_8->searchBone(bone);
    as_list->mSlots[slot].sub_7101165008(key, mode, true);
}

// Makes `count` bones partial bones of the slot (below the root).
void applyPartialBones(ksys::as::ASList* as_list, s32 slot, const sead::SafeString* bones, s32 count) {
    as_list->sub_710115C9E0(slot);
    setPartialBone(as_list, slot, "Root", 3);
    for (s32 i = 0; i < count; ++i)
        setPartialBone(as_list, slot, bones[i], 0);
    as_list->mSlots[slot].sub_7101164E38(false);
}

// Re-applies `count` bones on the slot 0.
void reapplyPartialBones(ksys::as::ASList* as_list, const sead::SafeString* bones, s32 count) {
    for (s32 i = 0; i < count; ++i)
        setPartialBone(as_list, 0, bones[i], 3);
}
}  // namespace

// NON_MATCHING: the original computes `this + 8` before the store of `_18`
void Unk_71025be918Data::sub_7100707A88(s32 slot, const sead::SafeString& bone) {
    _18 = slot;
    _8 = bone;
}

void Unk_71025be918Data::sub_7100707A9C(s32 slot, const sead::SafeString* bones) {
    _50 = slot;
    for (s32 i = 0; i < 3; ++i)
        mA[i] = bones[i];
}

void Unk_71025be918Data::sub_7100707AF4(s32 slot, const sead::SafeString* bones) {
    _88 = slot;
    for (s32 i = 0; i < 3; ++i)
        mB[i] = bones[i];
}

void Unk_71025be918Data::sub_7100707B4C(bool use_b) {
    if (_54 && _8c == use_b)
        return;
    _54 = true;
    _8c = use_b;
    sub_7100707BA4();
    sub_7100707E84();
}

// NON_MATCHING: stack slots of the BoneAccessKey temporaries (the original uses a separate slot per inlined group)
void Unk_71025be918Data::sub_7100707BA4() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;

    if (_54)
        applyPartialBones(as_list, _50, mA, 3);

    if (!_8c)
        return;
    const s32 slot = _88;
    if (_1c) {
        as_list = mActor->getASList();
        if (!as_list)
            return;
        as_list->sub_710115B01C(slot, 0, true);
        as_list->sub_710115C9E0(slot);
        as_list->mSlots[slot].sub_7101164E38(true);
    } else {
        applyPartialBones(as_list, slot, mB, 3);
    }
}

// NON_MATCHING: stack slots of the BoneAccessKey temporaries (the original uses a separate slot per inlined group)
void Unk_71025be918Data::sub_7100707E84() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    as_list->sub_710115C9E0(0);
    if (_54) {
        reapplyPartialBones(as_list, mA, 3);
        if (_8c && !_1c)
            reapplyPartialBones(as_list, mB, 3);
    }
    if (_1c)
        reapplyPartialBones(as_list, &_8, 1);
    as_list->mSlots[0].sub_7101164E38(false);
}

void Unk_71025be918Data::sub_7100707FF0() {
    if (!_54)
        return;
    _54 = false;
    if (auto* as_list = mActor->getASList()) {
        const s32 slot = _50;
        as_list->sub_710115B01C(slot, 0, true);
        as_list->sub_710115C9E0(slot);
        as_list->mSlots[slot].sub_7101164E38(true);
    }
    if (_8c) {
        _8c = false;
        if (auto* as_list = mActor->getASList()) {
            const s32 slot = _88;
            as_list->sub_710115B01C(slot, 0, true);
            as_list->sub_710115C9E0(slot);
            as_list->mSlots[slot].sub_7101164E38(true);
        }
    }
    sub_7100707E84();
}

void Unk_71025be918Data::sub_71007080E0() {
    if (_8c)
        return;
    _8c = true;
    sub_7100707BA4();
    sub_7100707E84();
}

void Unk_71025be918Data::sub_7100708124() {
    if (!_8c)
        return;
    _8c = false;
    if (auto* as_list = mActor->getASList()) {
        const s32 slot = _88;
        as_list->sub_710115B01C(slot, 0, true);
        as_list->sub_710115C9E0(slot);
        as_list->mSlots[slot].sub_7101164E38(true);
    }
    sub_7100707E84();
}

void Unk_71025be918Data::sub_71007081B8() {
    if (_1c)
        return;
    _1c = true;
    sub_7100708214();
    if (_54 && _8c)
        sub_7100707BA4();
    sub_7100707E84();
}

// NON_MATCHING: stack slot of the first BoneAccessKey temporary (0x18 in the original)
void Unk_71025be918Data::sub_7100708214() {
    auto* as_list = mActor->getASList();
    if (!as_list || !_1c)
        return;
    applyPartialBones(as_list, _18, &_8, 1);
}

void Unk_71025be918Data::sub_7100708308() {
    if (!_1c)
        return;
    _1c = false;
    if (auto* as_list = mActor->getASList()) {
        const s32 slot = _18;
        as_list->sub_710115B01C(slot, 0, true);
        as_list->sub_710115C9E0(slot);
        as_list->mSlots[slot].sub_7101164E38(true);
    }
    if (_54 && _8c)
        sub_7100707BA4();
    sub_7100707E84();
}
