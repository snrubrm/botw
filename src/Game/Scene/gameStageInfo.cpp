#include "Game/Scene/gameStageInfo.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking {

// 0x71007cc064 / 0x71007cc078: linked before this TU's sinit, so they are StageInfo members.
const sead::SafeString& StageInfo::getCurrentMapType() {
    return ksys::StageInfo::getCurrentMapType();
}

const sead::SafeString& StageInfo::getCurrentMapName() {
    return ksys::StageInfo::getCurrentMapName();
}

static ksys::util::InitConstants sConstants;
sead::FixedSafeString<256> StageInfo::sStr;
sead::Vector3f StageInfo::sPSavePosAngleForStageGen;
sead::Vector3f StageInfo::sPSavePosForStageGen;
StageInfo StageInfo::sInfo;

void StageInfo::setPSavePosAngleForStageGen(const sead::Vector3f& angle) {
    sPSavePosAngleForStageGen = angle;
}

void StageInfo::setPSavePosForStageGen(const sead::Vector3f& pos) {
    if (!ksys::StageInfo::sIsDungeon && !ksys::StageInfo::sIsActorViewer)
        ksys::StageInfo::setCurrentMapNameForFieldPos(pos);
    sPSavePosForStageGen = pos;
}

void StageInfo::setCurrentMapNameFromPlayerPos() {
    if (auto* info = uking::act::PlayerInfo::instance()) {
        const sead::Vector3f& pos = info->getPlayerPos();
        if (!ksys::StageInfo::sIsDungeon && !ksys::StageInfo::sIsActorViewer)
            ksys::StageInfo::setCurrentMapNameForFieldPos(pos);
    }
}

bool StageInfo::getIsStageDebug() {
    return ksys::StageInfo::sIsStageDebug;
}

}  // namespace uking
