#pragma once

#include <message/seadMessageSet.h>
#include "Game/UI/euiMessageString.h"

namespace eui {

// A loaded message binary of the UI (one per language / archive; see MessageMgr). Strings are UTF-16.
class MessageSet : public sead::MessageSet<char16> {
public:
    // 0x7100be4e70 / 0x7100be4fb8 (D0; the destructor is the base class's)
    MessageSet();
    ~MessageSet() override = default;

    // inline-only in the original; name is a guess. Evidence: Archive::unload tests the handle at +8 before finalizing
    bool isInitialized() const { return mHandle != nullptr; }

    // 0x7100be4e88: the text with the given label (an empty MessageString if there is none)
    MessageString findMessage(const char* label) const;
    // 0x7100be4f10 (the same code as findMessage)
    MessageString tryFindMessage(const char* label) const;
    bool sub_7100BE4F98(const char* label) const;
};

}  // namespace eui
