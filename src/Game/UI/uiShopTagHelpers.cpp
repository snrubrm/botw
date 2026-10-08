#include "Game/UI/uiScreens.h"

// Shop tag-argument helpers (the 0x7100aa4b4c/0x7100aa4e70 tag resolvers live in this TU in the
// original: the 16-byte forwarders sit right next to them).
namespace uking::ui {

// 0x7100aa4e60
u32 sub_7100AA4E60(ShopInfoTagData* data, sead::WBufferedSafeString* out) {
    return sub_7100AA4B4C(data, data->_58, out);
}

// 0x7100aa5140
u32 sub_7100AA5140(ShopInfoTagData* data, sead::WBufferedSafeString* out) {
    return sub_7100AA4E70(data, data->_58, data->_5c, out);
}

// Emits the Delegate2R vtable (0x71024987e0) + invoke (0x7100a534e8) + clone (0x7100a5351c).
}  // namespace uking::ui

template class sead::Delegate2R<uking::ui::ScreenShopInfo,
                                const sead::MessageSet<char16>::TagInfo*,
                                sead::WBufferedSafeString*, u32>;
