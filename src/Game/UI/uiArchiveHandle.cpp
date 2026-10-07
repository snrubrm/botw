#include "Game/UI/uiArchiveHandle.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiUtils.h"

namespace nn::ui2d {

// 0x71009c3308
ArchiveHandle::ArchiveHandle() = default;

// 0x71009c3358
ArchiveHandle::~ArchiveHandle() = default;

// NON_MATCHING: final layout lookup and receiver scheduling changes saved registers.
void ArchiveHandle::sub_71009C33F8(eui::LayoutEx* layout) {
    if (!layout)
        return;
    mLayout = layout;
    mEquipOff = mLayout->createAnimatorAuto("EquipOff", false);
    if (mEquipOff)
        mEquipOff->StopAtMin();
    mNumOff = mLayout->createAnimatorAuto("NumOff", false);
    if (mNumOff)
        mNumOff->StopAtMin();
    mCategoryIcon = mLayout->createAnimatorAuto("CategoryIcon", false);
    if (mCategoryIcon)
        mCategoryIcon->StopAtMin();
    auto* icon = mLayout->findPartsLayout("Pa_IconNow_00");
    mBreak.sub_71009B14F8(icon);
    if (icon) {
        mBombLoop = icon->createAnimatorAuto("BombLoop", true);
        if (mBombLoop)
            mBombLoop->StopAtMin();
    }
    mTexture.sub_7100988EF0(mLayout->findPartsLayout("Pa_SpIcon_00"));
    mNumber.sub_7100989A80(mLayout->findPartsLayout("Pa_Param_00"));
    auto* smoke = mLayout->findPartsLayout("Pa_IconSmoke_00");
    auto* electric = mLayout->findPartsLayout("Pa_IconElect_00");
    mSwitch.sub_7100932F74(smoke, electric);
}

void ArchiveHandle::sub_71009C35A4(s32 count) {
    if (mNumOff && mNumOff->mFrame != mNumOff->GetFrameSize())
        mNumOff->StopAtMax();
    sead::FixedSafeString<128> text;
    text.format("%d", count);
    uking::ui::setWidgetString(mLayout, "T_BowNum_00", text);
}
void ArchiveHandle::sub_71009C372C(bool play, f32 frame) {
    if (play) {
        if (mBombLoop)
            mBombLoop->PlayFromFrame(eui::Animator::PlayType(1), frame, 1.0f);
    } else {
        if (mBombLoop && mBombLoop->mRate != 0)
            mBombLoop->StopAtMin();
    }
}
eui::LayoutEx* ArchiveHandle::sub_71009C37B0(s32 index) const {
    if (mSwitch.sub_7100933038(index))
        return mSwitch.sub_7100932F7C(index);
    return nullptr;
}

void ArchiveHandle::sub_71009C3580(bool off) {
    if (mEquipOff) {
        if (off)
            mEquipOff->StopAtMin();
        else
            mEquipOff->StopAtMax();
    }
}
void ArchiveHandle::sub_71009C3694() {
    if (!mNumOff || mNumOff->mFrame == 0)
        return;
    mNumOff->StopAtMin();
}
void ArchiveHandle::sub_71009C36E4(bool play) {
    if (play) {
        if (mBombLoop && mBombLoop->mRate == 0)
            mBombLoop->PlayAuto(1.0f);
    } else {
        if (mBombLoop && mBombLoop->mRate != 0)
            mBombLoop->StopAtMin();
    }
}
void ArchiveHandle::sub_71009C3764(u32 category) {
    if (mCategoryIcon)
        mCategoryIcon->Stop(category);
}
f32 ArchiveHandle::sub_71009C3788() const {
    if (mBombLoop && mBombLoop->mRate != 0)
        return mBombLoop->mFrame;
    return 0;
}

void ArchiveHandle::sub_71009C3570(s32 state) { mBreak.sub_71009B1578(state); }
void ArchiveHandle::sub_71009C3578(s32 state, f32 frame) { mBreak.sub_71009B163C(state, frame); }
void ArchiveHandle::sub_71009C36B8(f32 frame) { mTexture.sub_7100988F30(frame); }
void ArchiveHandle::sub_71009C36C0() { mTexture.sub_7100988FE8(); }
void ArchiveHandle::sub_71009C36C8(s32 category, s32 value, s32 number) {
    mNumber.sub_7100989AF0(category, value, number);
}
void ArchiveHandle::sub_71009C36D0() { mNumber.sub_7100989AF0(-1, 0, 0); }
Material* ArchiveHandle::sub_71009C3780() const { return mBreak.sub_71009B1738(); }
f32 ArchiveHandle::sub_71009C37A8() const { return mBreak.sub_71009B1784(); }

}  // namespace nn::ui2d
