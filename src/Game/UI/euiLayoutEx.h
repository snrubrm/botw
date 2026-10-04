#pragma once

#include <basis/seadTypes.h>

namespace nn::ui2d {
class Pane;

// Control description of a layout part (CSV nn::ui2d::ControlSrc; the SDK source is not available). Only the lookups
// used by eui are declared.
class ControlSrc {
public:
    // 0x7100ac05c0 / 0x7100ac0548 / 0x7100ac0634
    const char* FindFunctionalAnimName(const char* name) const;
    const char* FindFunctionalPaneName(const char* name) const;
    const void* FindExtUserDataByName(const char* name) const;
};
}  // namespace nn::ui2d

namespace eui {

class Animator;
class AnimatorSet;
class Screen;

// The eui layout (CSV eui::LayoutEx; derives from nn::ui2d::Layout, vtable 0x24c7d18 with 26 slots). Only the
// fields and functions used so far are declared.
class LayoutEx {
public:
    virtual ~LayoutEx();

    // 0x7100bdd41c / 0x7100bdd424 / 0x7100bdd980 / 0x7100bdd524
    Animator* createAnimatorAuto(const char* name, bool b);
    Animator* tryCreateAnimatorAuto(const char* name, bool b);
    Animator* tryCreateAnimatorAutoWithWarning(const char* name, bool b);
    AnimatorSet* createAnimatorSet(const char* const* names, u32 count, bool b);

    u8 _8[0x18 - 0x8];
    /* 0x18 */ nn::ui2d::Pane* mPane;
    u8 _20[0x30 - 0x20];
    /* 0x30 */ const char* mName;
    u8 _38[0x80 - 0x38];
    /* 0x80 */ Screen* mScreen;
};

}  // namespace eui
