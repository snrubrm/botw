#pragma once

#include "KingSystem/Sound/sndBgmMgr.h"

// 0x7100ffd79c (declared only): `SoundMgr::instance()->_30->_48` (the BGM controller, see
// ksys::snd::Unk_SoundMgr30::_48), or null without a SoundMgr or _30. Used by CreateBgm's destructor
// (`_8.sub_7100FF7BE0` releases one reference of a BGM kind), BattleBgmRequestFinishTag::calc_ (slot m10),
// HorseRiddenAI's helper 0x7100ffdd38 and XLink::calc. Placeholder name.
ksys::snd::Unk_71024fca78* sub_7100FFD79C();
