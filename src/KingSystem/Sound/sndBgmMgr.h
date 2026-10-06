#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys::snd {

// Placeholder name (`SoundMgr::_30->_78`, see sub_7100FFD784; the BGM interface used by the EventBgm* actions). Only the
// methods those actions call are declared (declaration only).
class Unk_SoundMgr30_78 {
public:
    // 0x71010078a0 (100 B): starts the BGM `name`.
    void sub_71010078A0(const sead::SafeString& name);
    // 0x7101007904 (92 B): stops the BGM `name` with a fade of `fade_sec` seconds.
    void sub_7101007904(f32 fade_sec, const sead::SafeString& name);
};

// 0x7100ffd784 (24 B): `SoundMgr::instance()->_30->_78`.
Unk_SoundMgr30_78* sub_7100FFD784();

}  // namespace ksys::snd
