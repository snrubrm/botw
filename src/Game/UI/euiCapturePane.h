#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include <gfx/seadColor.h>
#include <nn/ui2d/Pane.h>


namespace sead {
class Heap;
}

namespace eui {

class LayoutEx;

// Only the static resource-policy helpers are recovered here. The capture
// pane's object layout, construction and virtual interface are not modeled.
// The RTTI static is at 0x71025d6530 (guard 0x71025d6538): a Pane subclass, DynamicCast'ed by the pane walks
// sub_7100BEE240 / sub_7100BEE3C8 / sub_7100BEE564.
class CapturePane : public nn::ui2d::Pane {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Pane)

    // 0x7100bf166c (2040 bytes, not decompiled; the CSV name listed (Heap*, const char*) but the pane is `this`):
    // `layout_name` is the layout's name (or its screen's name)
    void initializeCaptureTextureData_(const char* layout_name);
    // 0x7100bf1e64 (56 bytes, not decompiled; placeholder name)
    void sub_7100BF1E64();

    // The members sit in the tail padding of nn::ui2d::Pane (starting at 0xda).
    /* 0xda */ u8 _da;
    /* 0xdb */ bool _db;

    static sead::Color4f* setupClearColor_(sead::Heap*, nn::ui2d::Pane*, LayoutEx*,
                                          sead::BitFlag<u8>* flags);
    static void setupCaptureOutputAlpha255_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags);
    static void setupCaptureOriginalSize_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags);
};
static_assert(offsetof(CapturePane, _db) == 0xdb);

}  // namespace eui
