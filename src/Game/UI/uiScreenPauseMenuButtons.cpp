#include "Game/UI/uiScreens.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actInfoData.h"

namespace uking::ui {

ScreenButton_7100989968::ScreenButton_7100989968() = default;
ScreenButton_7100989968::~ScreenButton_7100989968() = default;

void ScreenButton_7100989968::sub_710098923C() {
    if (mAnimator) {
        if (mAnimator->mFrame != mAnimator->GetFrameSize())
            mAnimator->StopAtMax();
        if (_28)
            _28->StopAtMax();
    }
}

void ScreenButton_7100989968::sub_71009892B0() {
    if (mAnimator) {
        if (mAnimator->mFrame != 0.0f)
            mAnimator->StopAtMin();
        if (_28)
            _28->StopAtMax();
        mButton->setFlag10(false);
    }
}


// 0x710098993c
void ScreenButton_7100989968::sub_710098993C(bool enabled, bool play) {
    if (!mButton)
        return;
    if (play)
        mButton->PlayDisableAnim(enabled);
    else
        mButton->StopDisableAnim(enabled);
}

// 0x7100989968
void ScreenButton_7100989968::sub_7100989968(bool enabled) {
    if (!mButton)
        return;
    if (mAnimator && mAnimator->mFrame == f32(mAnimator->GetFrameSize()))
        mButton->setFlag10(enabled);
    else
        mButton->setFlag10(false);
}

// 0x71009899ec
void ScreenButton_7100989968::sub_71009899EC() {
    if (mAnimator)
        mAnimator->PlayAuto(1.0f);
}

// NON_MATCHING: the compiler lays out the item-type branches differently.
void ScreenButton_7100989968::sub_710098931C(const PouchItem* item) {
    if (!item) {
        sub_71009896D8();
        return;
    }
    auto* info = ksys::act::InfoData::instance();
    if (info && info->hasTag(item->getName().cstr(), 0x9b44906f))
        sub_710098975C(item->getValue());
    else if (_18 && _18->mFrame != 0.0f)
        _18->StopAtMin();

    const auto type = item->getType();
    f32 frame = -1.0f;
    bool equipped = item->isEquipped();
    s32 category = -1;
    s32 value = 0;
    s32 bow_add = 0;
    if (type == PouchItemType::Arrow) {
        equipped = equipped & !sub_7100AA7BAC(nullptr);
    } else if (type <= PouchItemType::Shield) {
        WeaponStats stats;
        getWeaponStats(*item, &stats);
        sub_7100AA7290(stats.modifier, type == PouchItemType::Bow, &frame);
        value = stats.power;
        bow_add = stats.bow_add_value;
        category = type == PouchItemType::Sword ? 0 : type == PouchItemType::Shield ? 2 : 1;
    }
    if (sub_7100A82E28(s32(type))) {
        ArmorInfo armor;
        getArmorInfoMaybe(item->getName(), &armor);
        sub_7100AA4ACC(armor.effect, &frame);
        value = armor.defence;
        category = 3;
    } else if (type == PouchItemType::KeyItem) {
        equipped = false;
    } else if (type == PouchItemType::Food) {
        if (info && info->hasTag(item->getName().cstr(), 0x30a3552e)) {
            sub_7100AA4A4C(sub_7100AA42AC(*item), &frame);
            value = item->getCookData().mHealthRecover;
        } else {
            CookingInfo cook;
            cookingStuff_0(item->getName(), &cook);
            sub_7100AA4A4C(cook.effect, &frame);
            value = cook.healthRecover;
        }
        category = 5;
    } else if (type == PouchItemType::Material) {
        value = getItemHitPointRecover(sead::SafeString(item->getName().cstr()));
        category = 4;
    }
    mTexturePatternController.sub_7100988F30(frame);
    const sead::SafeString name = item->getName();
    s32 special_value = 0;
    if (sub_7100A9FC20(name, &special_value, false))
        value = special_value;
    mCategoryController.sub_7100989AF0(category, value, bow_add);
    if (_10) {
        if (equipped) {
            if (_10->mFrame != _10->GetFrameSize())
                _10->StopAtMax();
        } else if (_10->mFrame != 0.0f) {
            _10->StopAtMin();
        }
    }
    mBreakNewController.sub_71009B1578(sub_7100AA6E4C(*item));
}

void ScreenButton_7100989968::sub_71009896D8() {
    if (_10 && _10->mFrame != 0.0f)
        _10->StopAtMin();
    if (_18 && _18->mFrame != 0.0f)
        _18->StopAtMin();
    mBreakNewController.sub_71009B1578(-1);
    mTexturePatternController.sub_7100988FE8();
    mCategoryController.sub_7100989AF0(-1, 0, 0);
}

// NON_MATCHING: the compiler orders the negative-count tail call and common exit differently.
void ScreenButton_7100989968::sub_710098975C(s32 count) {
    if (count >= 0) {
        sead::FixedSafeString<32> text;
        text.format("%d", count);
        setWidgetString(mButton->mLayout, "T_ItemNum_00", text);
        if (_18 && _18->mFrame != _18->GetFrameSize())
            _18->StopAtMax();
        return;
    }
    if (_18 && _18->mFrame != 0.0f)
        _18->StopAtMin();
}

// NON_MATCHING: the compiler shares the Animator frame load across enabled/disabled branches.
void ScreenButton_7100989968::sub_7100989888(bool enabled, bool play) {
    if (!_10)
        return;
    if (enabled) {
        if (_10->mFrame == _10->GetFrameSize())
            return;
        if (play)
            _10->PlayAuto(1.0f);
        else
            _10->StopAtMax();
    } else {
        if (_10->mFrame == 0.0f)
            return;
        if (play)
            _10->PlayAuto(-1.0f);
        else
            _10->StopAtMin();
    }
}

bool ScreenButton_7100989968::sub_7100989A08() const {
    return mAnimator && mAnimator->mFrame == mAnimator->GetFrameSize();
}

void ScreenButton_7100989968::sub_7100989A40() {
    if (_28)
        _28->PlayAuto(1.0f);
}

}  // namespace uking::ui
