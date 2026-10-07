#pragma once

#include "Game/UI/uiScreens.h"

namespace uking::ui {

// The shortcut-icon unit's constructor composes the archive controllers and
// texture slots after the common button-unit state.
class Unk_7102474c68 : public Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_7102474c68, Unk_7102474e38)
public:
    Unk_7102474c68();
    ~Unk_7102474c68() override;
    void m4(sead::Heap*) override;
    void m6() override;
    void m7() override;
    void m8() override;
    void m12() override;
    void m13() override;
    void m14() override;
    void sub_7100936EEC();

private:
    /* 0x48 */ nn::ui2d::ArchiveHandle mArchive;
    /* 0xf0 */ UiTexSlots mTextures;
    /* 0x1c0 */ bool mActive = false;
};

}  // namespace uking::ui
