#include "Game/UI/uiScreens.h"
#include "Game/UI/euiConstantBuffer.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/UI/euiArcResourceMgr.h"
#include "Game/UI/euiMultiArcResourceAccessor.h"
#include <nn/ui2d/ResExtUserData.h>
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/SeadController.h"

namespace uking::ui {

// 0x71010a9b0c (CSV ScreenBase::ctor)
ScreenBase::ScreenBase() = default;

// 0x71010a9d9c
void ScreenBase::doInitialize_(sead::Heap* heap) {
    eui::Screen::doInitialize_(heap);
}

// 0x71010a9f58
void* ScreenBase::getSlink2ResourceList_(xlink2::UserInstanceSLink*) const {
    // The address of the resource manager's asset info reader is the SLink resource list.
    return &ksys::snd::SoundMgr::instance()->_60->mSlinkResources;
}

// NON_MATCHING: only the register assignment of the first two loads differs (mMgr / mDrawInfo), as in eui::Screen::doSetupDrawInfo_
// 0x71010a9b44
void ScreenBase::sub_71010A9B44(bool) {}

// 0x71010a9f70 (CSV ScreenBase::doSetupDrawInfo_)
void ScreenBase::doSetupDrawInfo_() {
    mDrawInfo->mGraphicsResource = mMgr->getGraphicsResource();
    eui::SetupDrawInfoPerspective(0.6981317f, mDrawInfo, mLayout->GetLayoutSize());
    mMgr->getConstantBuffer()->applyToDrawInfo(mDrawInfo);
}


// 0x71010a9f44 (CSV ScreenBase::getAnimationStep_)
f32 ScreenBase::getAnimationStep_() const {
    return eui::ScreenMgr::instance()->getAnimationStep();
}

// 0x71010a9fc0 (CSV ScreenBase::getArchiveName_)
const char* ScreenBase::getArchiveName_() const {
    return "Common";
}

// 0x71010a9b48
const char* ScreenBase::replacePartsLayoutName(const char* name, eui::PartsEx* parts, eui::LayoutEx*) {
    const auto* data = parts->FindExtUserDataByName("ReplacePartsForNN");
    if (data && data->GetType() == nn::ui2d::ExtUserDataType_String)
        return data->GetString();
    return name;
}

// 0x71010a9eb8 (CSV ScreenBase::registerController_)
void ScreenBase::registerController_() {
    if (isEnableControl())
        mUIController->registerWith(ksys::SeadController::getInstance(), false);
}

// 0x71010a9fcc: also attaches the Title / Horse / BootUp / Test archives for some screen IDs, then the
// screen's own layout archive
nn::ui2d::ResourceAccessor* ScreenBase::doCreateResourceAccessor_(sead::Heap* heap) {
    auto* accessor = eui::Screen::doCreateResourceAccessor_(heap);
    if (!accessor)
        return nullptr;
    auto* multi = nn::font::DynamicCast<eui::MultiArcResourceAccessor>(accessor);
    if (!multi)
        return accessor;

    if (mId == 1) {
        if (auto* archive = multi->mArcResourceMgr->findArcResource("Title"))
            multi->attachArchive(archive->mData, archive->mTextureResource);
    }
    if (mId == 23) {
        if (auto* archive = multi->mArcResourceMgr->findArcResource("Horse"))
            multi->attachArchive(archive->mData, archive->mTextureResource);
    }
    if (mId == 90 || mId == 91) {
        if (auto* archive = multi->mArcResourceMgr->findArcResource("BootUp"))
            multi->attachArchive(archive->mData, archive->mTextureResource);
    }
    if (mId == 93) {
        if (auto* archive = multi->mArcResourceMgr->findArcResource("Test"))
            multi->attachArchive(archive->mData, archive->mTextureResource);
    }
    if (auto* archive = multi->mArcResourceMgr->findArcResource(getLayoutName_()))
        multi->attachArchive(archive->mData, archive->mTextureResource);
    return accessor;
}

}  // namespace uking::ui
