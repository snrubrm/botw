#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// TODO: incomplete. Only the listener count that SpatialPlayingParam::initialize reads is declared.
class ListenerMgr {
public:
    s32 getListenerNum() const { return mListenerNum; }

private:
    u8 _0[0x38];
    s32 mListenerNum;
};

}  // namespace aal
