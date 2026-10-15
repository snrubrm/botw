#pragma once

#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace uking::ui {

// Placeholder: screen name -> screen id entry (vtable 0x710237e1d0 in the event action TUs, no RTTI; 0x48 bytes).
// Each TU that includes this builds its own table of entries in its static initializer.
struct ScreenNameEntry {
    ScreenNameEntry(const sead::SafeString& name_, s32 id_) : name(name_), id(id_) {}
    virtual ~ScreenNameEntry() = default;

    sead::FixedSafeString<32> name;
    s32 id;
};

// Placeholder: the 8-byte object each static initializer stores before its entry table is built.
struct ScreenNameTableHeader {
    ScreenNameTableHeader() : _0(0x8004ef), _4(0) {}

    u32 _0;
    u32 _4;
};

}  // namespace uking::ui
