#include "KingSystem/Sound/sndBgmMgr.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2ResourceAccessorSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

// TU 0x710100ce68..0x710100f268 (static initialiser) in the original.

Unk_71024fe808::~Unk_71024fe808() = default;

// NON_MATCHING: placeholder destructor; the original (0x710100df48) also destroys members or bases
// this class does not declare yet.
Unk_71024fe970::~Unk_71024fe970() = default;
