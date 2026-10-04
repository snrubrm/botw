#include "Game/UI/euiLayoutEx.h"
#include <new>
#include <prim/seadStringBuilder.h>
#include <gfx/nin/seadGraphicsNvn.h>
#include <nn/font/font_ScalableFont.h>
#include <nn/ui2d/ResPane.h>
#include <nn/ui2d/ResourceAccessor.h>
#include <nn/util/util_BytePtr.h>
#include <nn/ui2d/DrawInfo.h>
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/BuildTypes.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiFontMgr.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiTextSearcher.h"

namespace eui {

// 0x7100bdd16c
LayoutEx::LayoutEx(Screen* screen) : mScreen(screen) {}

// NON_MATCHING: the original snapshots mScreen before allocation; this natural body reads it at construction.
// 0x7100bdf0f0
LayoutEx* LayoutEx::m21(const char*, const nn::ui2d::Layout::PartsBuildDataSet&,
                       const nn::ui2d::BuildArgSet&) {
    void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(LayoutEx), 4);
    if (!memory)
        return nullptr;
    return new (memory) LayoutEx(mScreen);
}

// 0x7100bdd988
s32 LayoutEx::setMessageStringForEachId(const char* id, const MessageString& message,
                                       bool adjust_size, void* user_data) {
    const s32 count = setMessageStringForEachIdRecursive_(mPane, id, message, nullptr, -1, user_data);
    if (count && adjust_size && (_90 & 1))
        adjustPaneSizeToTextSizeRecursive_(mPane);
    return count;
}

// 0x7100bddd64
s32 LayoutEx::setMessageStringForEachIdWithPage(const char* id, const MessageString& message,
                                               bool* has_next_page, u32 page, bool adjust_size,
                                               void* user_data) {
    const s32 count = setMessageStringForEachIdRecursive_(mPane, id, message, has_next_page, page, user_data);
    if (count && adjust_size && (_90 & 1))
        adjustPaneSizeToTextSizeRecursive_(mPane);
    return count;
}

// 0x7100bddc70
void LayoutEx::adjustPaneSizeToTextSizeRecursive_(nn::ui2d::Pane* pane) {
    AdjustPaneSizeToTextSize(pane, this);
    for (auto& child : pane->GetChildList()) {
        if (!nn::font::DynamicCast<nn::ui2d::Parts>(&child))
            adjustPaneSizeToTextSizeRecursive_(&child);
    }
}

// NON_MATCHING: resource selection and RTTI boolean-return blocks differ naturally.
// 0x7100bdeeac
bool LayoutEx::isScalableFontTextBox_(const nn::ui2d::ResTextBox* resource,
                                      const nn::ui2d::ResTextBox* replacement,
                                      const nn::ui2d::BuildArgSet& args) {
    if (!static_cast<TextSearcher*>(args.mTextSearcher)->getTagProcessor()->mFontMgr->getScalableFontMgr())
        return false;
    const nn::ui2d::BuildResSet* resources = args.mResources;
    if (replacement && !(args.mTextOverrideFlags & 1)) {
        resources = args.mOverrideResources;
        resource = replacement;
    }
    const void* names = nn::util::ConstBytePtr(resources->mFontList, 0xc).Get();
    const u32* offsets = nn::util::ConstBytePtr(names).Get<u32>();
    const char* name = nn::util::ConstBytePtr(names, offsets[resource->mFontIndex]).Get<char>();
    nn::font::Font* font = mResourceAccessor->AcquireFont(sead::GraphicsNvn::instance()->getNnDevice(), name);
    if (!font)
        return false;
    return nn::font::DynamicCast<nn::font::ScalableFont>(font) != nullptr;
}

// 0x7100bdeffc
nn::ui2d::Layout* LayoutEx::BuildPartsLayout(nn::ui2d::BuildResultInformation* result,
                                           nn::gfx::Device* device, const char* name,
                                           const nn::ui2d::Layout::PartsBuildDataSet& parts,
                                           const nn::ui2d::BuildArgSet& args) {
    const auto* parent = static_cast<const LayoutEx*>(args.mParentLayout);
    if (parent->mScreen)
        name = parent->mScreen->replacePartsLayoutName(
            name, static_cast<PartsEx*>(parts.mPartsPane), const_cast<LayoutEx*>(parent));
    attachPartsLayoutArchive_(sead::SafeString(name));
    const void* resource = GetLayoutResourceData(name);
    LayoutEx* layout = m21(name, parts, args);
    layout->_88 = this;
    layout->BuildImpl(result, device, resource, mResourceAccessor, args, &parts);
    return layout;
}

// NON_MATCHING: waiting-animation branches and StringBuilder initialization are scheduled differently.
// 0x7100bdde7c
void LayoutEx::sub_7100BDDE7C(bool recursive, s32 mode, bool force) {
    const bool reverse = mOpenAnimator && !mCloseAnimator && mOpenAnimator->mRate < 0;
    if (recursive || force) {
        if (mOpenAnimator) {
            Animator* close = mCloseAnimator;
            if (close) {
                close->nn::ui2d::AnimTransform::SetEnabled(false);
                close->mRate = 0;
            }
            if (mode == 1) {
                mOpenAnimator->StopAtMax();
                _91 = 2;
            } else if (mode == 2) {
                mOpenAnimator->StopAtMin();
                _91 = 0;
            } else {
                if (reverse)
                    mOpenAnimator->PlayFromCurrent(Animator::PlayType(0), 1.0f);
                else
                    mOpenAnimator->PlayAuto(1.0f);
                if (mScreen && mScreen->_f0 && _88 && !_88->mPane->GetParent()) {
                    sead::FixedStringBuilder<64> name;
                    name.copy(mPane->GetName());
                    name.append("_open", -1);
                    mScreen->invokeSoundLink2Event_(name.cstr());
                }
                _91 = 1;
            }
        } else if (mCloseAnimator) {
            mCloseAnimator->StopAtMin();
        }
    }
    if (_70 && !reverse && (!mOpenAnimator || force || recursive)) {
        if (_90 & 2)
            _70->PlayRandom(Animator::PlayType(1), 1.0f);
        else
            _70->PlayAuto(1.0f);
    }
    for (auto& part : mPartsLayoutList)
        static_cast<LayoutEx*>(part.layout)->sub_7100BDDE7C(recursive, mode, false);
}

// 0x7100bddddc
LayoutEx* LayoutEx::findPartsLayout(const char* name) {
    nn::ui2d::Parts* parts = FindPartsPaneByName(name);
    return parts ? static_cast<LayoutEx*>(parts->mPartsLayoutLink.layout) : nullptr;
}

// NON_MATCHING: StringBuilder initialization and virtual-call argument loads are scheduled differently.
// 0x7100bde0b4
void LayoutEx::startAnimCloseImpl_(bool recursive, bool instant) {
    Animator* open = mOpenAnimator;
    if (mCloseAnimator) {
        if (open) {
            open->nn::ui2d::AnimTransform::SetEnabled(false);
            open->mRate = 0;
        }
        if (instant) {
            mCloseAnimator->StopAtMax();
            _91 = 0;
        } else {
            mCloseAnimator->PlayAuto(1.0f);
            if (mScreen && mScreen->_f0 && _88 && !_88->mPane->GetParent()) {
                sead::FixedStringBuilder<64> name;
                name.copy(mPane->GetName());
                name.append("_close", -1);
                mScreen->invokeSoundLink2Event_(name.cstr());
            }
            _91 = 3;
        }
    } else if (open) {
        if (instant) {
            open->StopAtMin();
            _91 = 0;
        } else {
            if (open->mRate > 0)
                open->PlayFromCurrent(Animator::PlayType(0), -1.0f);
            else
                open->PlayAuto(-1.0f);
            if (mScreen && mScreen->_f0 && _88 && !_88->mPane->GetParent()) {
                sead::FixedStringBuilder<64> name;
                name.copy(mPane->GetName());
                name.append("_close", -1);
                mScreen->invokeSoundLink2Event_(name.cstr());
            }
            _91 = 3;
        }
    } else {
        sub_7100BDE29C(mPane->GetParent() != nullptr && !recursive);
    }
    if (recursive) {
        for (auto& part : mPartsLayoutList)
            static_cast<LayoutEx*>(part.layout)->startAnimCloseImpl_(true, instant);
    }
}

// 0x7100bde29c
void LayoutEx::sub_7100BDE29C(bool recursive) {
    Animator* animator = _70;
    if (animator) {
        animator->nn::ui2d::AnimTransform::SetEnabled(false);
        animator->mRate = 0;
    }
    if (recursive) {
        for (auto& part : mPartsLayoutList)
            static_cast<LayoutEx*>(part.layout)->sub_7100BDE29C(true);
    }
}

// 0x7100bde308
bool LayoutEx::isAnimOpenEnd(bool recursive) const {
    if (mOpenAnimator && mOpenAnimator->mFrame != mOpenAnimator->GetFrameSize())
        return false;
    if (recursive) {
        for (const auto& part : mPartsLayoutList) {
            if (!static_cast<const LayoutEx*>(part.layout)->isAnimOpenEnd(true))
                return false;
        }
    }
    return true;
}

// NON_MATCHING: duplicate constant-return blocks remain around the recursive traversal.
// 0x7100bde39c
bool LayoutEx::isAnimCloseEnd(bool recursive) const {
    if (mCloseAnimator) {
        if (mCloseAnimator->mFrame != mCloseAnimator->GetFrameSize())
            return false;
        if (mCloseAnimator->mEnabled)
            return false;
    } else if (mOpenAnimator) {
        if (mOpenAnimator->mFrame != 0.0f)
            return false;
        if (mOpenAnimator->mEnabled)
            return false;
    }
    if (recursive) {
        for (const auto& part : mPartsLayoutList) {
            if (!static_cast<const LayoutEx*>(part.layout)->isAnimCloseEnd(true))
                return false;
        }
    }
    return true;
}

// 0x7100bde5a0
void LayoutEx::CalculateImpl(nn::ui2d::DrawInfo& info, bool force) {
    if (mPane) {
        nn::ui2d::Pane::CalculateContext context;
        context.Set(info, this);
        info.mLayout = this;
        mPane->Calculate(info, context, force);
        info.mLayout = nullptr;
    }
}

// 0x7100bde620
bool LayoutEx::BuildImpl(nn::ui2d::BuildResultInformation* result, nn::gfx::Device* device,
                         const void* data, nn::ui2d::ResourceAccessor* accessor,
                         const nn::ui2d::BuildArgSet& args,
                         const nn::ui2d::Layout::PartsBuildDataSet* parts) {
    const bool built = nn::ui2d::Layout::BuildImpl(result, device, data, accessor, args, parts);
    if (built)
        doInitializeDefalutAnimator_();
    return built;
}

// 0x7100bde458
void LayoutEx::setDrawTargetAnim(DrawTarget target) {
    if (_78)
        _78->Stop(int(target));
    for (auto& part : mPartsLayoutList)
        static_cast<LayoutEx*>(part.layout)->setDrawTargetAnim(target);
}

// 0x7100bdd524
AnimatorSet* LayoutEx::createAnimatorSet(const char* const* names, u32 count, bool enabled) {
    void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(AnimatorSet) + count * sizeof(Animator*), 4);
    if (!memory)
        return nullptr;
    auto* set = new (memory) AnimatorSet;
    set->setBuffer(count, reinterpret_cast<Animator**>(set + 1));
    for (u32 i = 0; i < count; ++i) {
        if (names[i] && names[i][0])
            set->setAnimator(i, tryCreateAnimatorAuto(names[i], i == 0 && enabled));
    }
    return set;
}

// 0x7100bdd41c
Animator* LayoutEx::createAnimatorAuto(const char* name, bool b) {
    return tryCreateAnimatorAuto(name, b);
}

// 0x7100bdd980
Animator* LayoutEx::tryCreateAnimatorAutoWithWarning(const char* name, bool b) {
    return tryCreateAnimatorAuto(name, b);
}

}  // namespace eui
