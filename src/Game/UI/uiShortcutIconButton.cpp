#include "Game/UI/uiShortcutIconButton.h"
#include "Game/UI/euiButton.h"

namespace uking::ui {

Unk_7102474c68::Unk_7102474c68() = default;
Unk_7102474c68::~Unk_7102474c68() = default;
void Unk_7102474c68::m6() {
    mTextures.sub_7100A816D8();
    if (_10) {
        if (sub_7100939CA0()) {
            if ((_10->mFlags & 0x10) && !mActive) {
                mActive = true;
                _10->On();
            }
        } else if (mActive) {
            mActive = false;
            _10->Off();
        }
    }
}
void Unk_7102474c68::m7() { sub_7100936EEC(); }
void Unk_7102474c68::m8() { mTextures.unload(0); }
void Unk_7102474c68::m12() { mArchive.mSwitch.sub_71009330E4(); }
void Unk_7102474c68::m13() {
    sub_7100936EEC();
    _10->ForceOff();
    mActive = false;
}
void Unk_7102474c68::m14() { mTextures.unload(0); }

}  // namespace uking::ui
