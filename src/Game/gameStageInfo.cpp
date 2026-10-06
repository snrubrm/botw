#include "Game/gameStageInfo.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking {

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
    if (auto* info = ksys::act::PlayerInfo::instance()) {
        const sead::Vector3f& pos = info->getPlayerPos();
        if (!ksys::StageInfo::sIsDungeon && !ksys::StageInfo::sIsActorViewer)
            ksys::StageInfo::setCurrentMapNameForFieldPos(pos);
    }
}

bool StageInfo::getIsStageDebug() {
    return ksys::StageInfo::sIsStageDebug;
}

}  // namespace uking
