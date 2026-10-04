#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <nn/ui2d/Layout.h>

namespace nn::ui2d {
class Pane;
struct ResExtUserData;

// Control description of a layout part (CSV nn::ui2d::ControlSrc; the SDK source is not available). Only the lookups
// used by eui are declared.
class ControlSrc {
public:
    // 0x7100ac05c0 / 0x7100ac0548 / 0x7100ac0634
    const char* FindFunctionalAnimName(const char* name) const;
    const char* FindFunctionalPaneName(const char* name) const;
    const ResExtUserData* FindExtUserDataByName(const char* name) const;
};
}  // namespace nn::ui2d

namespace sead {
class Heap;
}

namespace eui {

// 0x7100befa64
sead::Heap* GetNwAllocatorHeap();

class Animator;
class AnimatorSet;
class Screen;

// The eui layout (CSV eui::LayoutEx; derives from nn::ui2d::Layout, vtable 0x24c7d18 with 26 slots). Only the
// fields and functions used so far are declared.
class LayoutEx : public nn::ui2d::Layout {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Layout)

    using nn::ui2d::Layout::mName;

    // 0x7100bdd16c (not decompiled)
    explicit LayoutEx(Screen* screen);
    ~LayoutEx() override;

    bool BuildImpl(nn::ui2d::BuildResultInformation*, nn::gfx::Device*, const void*,
                   nn::ui2d::ResourceAccessor*, const nn::ui2d::BuildArgSet&,
                   const nn::ui2d::Layout::PartsBuildDataSet*) override;
    nn::ui2d::Pane* BuildPaneObj(nn::ui2d::BuildResultInformation*, nn::gfx::Device*, u32,
                               const void*, const void*, const nn::ui2d::BuildArgSet&) override;
    bool BuildPartsLayout(nn::ui2d::BuildResultInformation*, nn::gfx::Device*, const char*,
                          const nn::ui2d::Layout::PartsBuildDataSet&,
                          const nn::ui2d::BuildArgSet&) override;
    void CalculateImpl(nn::ui2d::DrawInfo&, bool) override;

    // Own slots 20-25, from the original vtable; undecompiled signatures use placeholders.
    virtual void m20(Animator* animator);
    virtual LayoutEx* m21();
    virtual void attachPartsLayoutArchive_(const sead::SafeString& name);
    virtual void doInitializeDefalutAnimator_();
    virtual nn::ui2d::Pane* m24(nn::ui2d::BuildResultInformation*, u32, const void*, const void*,
                              const nn::ui2d::BuildArgSet&);
    virtual void m25(nn::ui2d::Pane*, const nn::ui2d::BuildArgSet&);

    // 0x7100bde308 / 0x7100bde39c
    bool isAnimOpenEnd(bool b) const;
    bool isAnimCloseEnd(bool b) const;

    // 0x7100bde0b4 (not decompiled)
    void startAnimCloseImpl_(bool a1, bool a2);

    // 0x7100bdd41c / 0x7100bdd424 / 0x7100bdd980 / 0x7100bdd524
    Animator* createAnimatorAuto(const char* name, bool b);
    Animator* tryCreateAnimatorAuto(const char* name, bool b);
    Animator* tryCreateAnimatorAutoWithWarning(const char* name, bool b);
    AnimatorSet* createAnimatorSet(const char* const* names, u32 count, bool b);

    /* 0x60 */ Animator* mOpenAnimator = nullptr;
    /* 0x68 */ Animator* mCloseAnimator = nullptr;
    /* 0x70 */ Animator* _70 = nullptr;
    /* 0x78 */ Animator* _78 = nullptr;
    /* 0x80 */ Screen* mScreen;
    /* 0x88 */ void* _88 = nullptr;
    /* 0x90 */ u8 _90 = 0;
    /* 0x91 */ u8 _91 = 2;  // animation state

};
static_assert(sizeof(LayoutEx) == 0x98);

}  // namespace eui
