#include "Game/gameStageInfo.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking {

static ksys::util::InitConstants sConstants;
sead::FixedSafeString<256> StageInfo::sStr;
sead::Vector3f StageInfo::sPSavePosAngleForStageGen;
sead::Vector3f StageInfo::sPSavePosForStageGen;
StageInfo StageInfo::sInfo;

}  // namespace uking
