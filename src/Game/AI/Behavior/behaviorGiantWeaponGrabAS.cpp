#include "Game/AI/Behavior/behaviorGiantWeaponGrabAS.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71025be918.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::behavior {

GiantWeaponGrabAS::GiantWeaponGrabAS(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void GiantWeaponGrabAS::m8() {
    _d8 = false;
    _d9 = false;
}

void GiantWeaponGrabAS::loadParams() {
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLeftTargetBone_s, "LeftTargetBone");
    getStaticParam(&mVeryThinFrame_s, "VeryThinFrame");
    getStaticParam(&mThinFrame_s, "ThinFrame");
    getStaticParam(&mNormalFrame_s, "NormalFrame");
    getStaticParam(&mThickFrame_s, "ThickFrame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mPartialBone0_s, "PartialBone0");
    getStaticParam(&mPartialBone1_s, "PartialBone1");
    getStaticParam(&mPartialBone2_s, "PartialBone2");
    getStaticParam(&mLeftPartialBone0_s, "LeftPartialBone0");
    getStaticParam(&mLeftPartialBone1_s, "LeftPartialBone1");
    getStaticParam(&mLeftPartialBone2_s, "LeftPartialBone2");
    getAITreeVariable(&mGiantPartBoneUnit_a, "GiantPartBoneUnit");
}

GiantWeaponGrabAS::~GiantWeaponGrabAS() = default;

bool GiantWeaponGrabAS::m6(sead::Heap* heap) {
    if (!_e0.acquire(heap, static_cast<Unk_71025afb58**>(mGiantPartBoneUnit_a), mActor))
        return false;
    if (Unk_71025be918Data* data = sead::DynamicCast<Unk_71025be918>(*_e0._0)) {
        sead::SafeString right[3];
        right[0] = mPartialBone0_s;
        right[1] = mPartialBone1_s;
        right[2] = mPartialBone2_s;
        data->sub_7100707A9C(*mTargetBone_s, right);
        sead::SafeString left[3];
        left[0] = mLeftPartialBone0_s;
        left[1] = mLeftPartialBone1_s;
        left[2] = mLeftPartialBone2_s;
        data->sub_7100707AF4(*mLeftTargetBone_s, left);
    }
    return true;
}

void GiantWeaponGrabAS::m7() {
    auto* weapon = sub_71005D83E8(mActor, 0);
    const bool has_weapon = weapon != nullptr;
    if (has_weapon) {
        const bool weapon_flag = weapon->m233();
        if (_d8) {
            if (sub_71005DD734(mActor, 0x35, nullptr, 0, 0))
                sub_7100626768();
            if (sub_71005DD5B0(mActor, 0x35, nullptr, 0, 0)) {
                if (auto* unit = sead::DynamicCast<Unk_71025be918>(*_e0._0))
                    unit->sub_7100708124();
            }
        } else {
            _d8 = has_weapon;
            const bool is_playing = sub_71005DD798(mActor, 0x35, nullptr, 0, 0);
            _d9 = weapon_flag && !is_playing;
            const f32* frame;
            if (ksys::act::hasTag(weapon, ksys::act::tags::ThickTreeWeapon))
                frame = mThickFrame_s;
            else if (ksys::act::hasTag(weapon, ksys::act::tags::ThinTreeWeapon))
                frame = mThinFrame_s;
            else if (ksys::act::hasTag(weapon, ksys::act::tags::VeryThinTreeWeapon))
                frame = mVeryThinFrame_s;
            else
                frame = mNormalFrame_s;
            sub_7100626590(*frame, _d9);
        }
    } else if (_d8) {
        _d8 = has_weapon;
        if (auto* unit = sead::DynamicCast<Unk_71025be918>(*_e0._0))
            unit->sub_7100707FF0();
    }
}

void GiantWeaponGrabAS::m9() {
    if (_d8) {
        _d8 = false;
        if (auto* unit = sead::DynamicCast<Unk_71025be918>(*_e0._0))
            unit->sub_7100707FF0();
    }
}

void GiantWeaponGrabAS::sub_7100626590(f32 frame, bool use_b) {
    if (auto* unit = sead::DynamicCast<Unk_71025be918>(*_e0._0))
        unit->sub_7100707B4C(use_b);
    if (auto* as_list = mActor->getASList()) {
        const s32 slot = *mTargetBone_s;
        as_list->sub_710115B140(mASName_s, slot, 0, 0, 0);
        as_list->x_3(slot, 0, &ksys::as::ASList::Unk2::sub_7101163044, frame);
        as_list->x_3(slot, 0, &ksys::as::ASList::Unk2::sub_71011631DC, frame);
        as_list->sub_710115F444(slot, 0, &ksys::as::ASList::Unk2::sub_710042BBEC);
    }
    if (use_b) {
        if (auto* as_list = mActor->getASList()) {
            const s32 slot = *mLeftTargetBone_s;
            as_list->sub_710115B140(mASName_s, slot, 0, 0, 0);
            as_list->x_3(slot, 0, &ksys::as::ASList::Unk2::sub_7101163044, frame);
            as_list->x_3(slot, 0, &ksys::as::ASList::Unk2::sub_71011631DC, frame);
            as_list->sub_710115F444(slot, 0, &ksys::as::ASList::Unk2::sub_710042BBEC);
        }
    }
}

void GiantWeaponGrabAS::sub_7100626768() {
    if (auto* unit = sead::DynamicCast<Unk_71025be918>(*_e0._0))
        unit->sub_71007080E0();
    f32 frame = 0;
    if (auto* as_list = mActor->getASList()) {
        if (as_list->x_7(*mTargetBone_s, 0, &ksys::as::ASList::Unk2::sub_710002E82C))
            frame = as_list->x_5(*mTargetBone_s, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
    }
    if (auto* as_list = mActor->getASList()) {
        const s32 slot = *mLeftTargetBone_s;
        as_list->sub_710115B140(mASName_s, slot, 0, 0, 0);
        as_list->x_3(slot, 0, &ksys::as::ASList::Unk2::sub_7101163044, frame);
        as_list->x_3(slot, 0, &ksys::as::ASList::Unk2::sub_71011631DC, frame);
        as_list->sub_710115F444(slot, 0, &ksys::as::ASList::Unk2::sub_710042BBEC);
    }
}

}  // namespace uking::behavior
