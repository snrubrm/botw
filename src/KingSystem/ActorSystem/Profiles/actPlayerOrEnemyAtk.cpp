#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemy.h"

namespace ksys::act {

// Kept out of actPlayerOrEnemy.cpp: getBaseAtkPower tail-calls it (the original does not inline it).
s32 PlayerOrEnemy::getEnemyAtkPower() {
    if (isEnemyProfile(this))
        return getParam()->getRes().mGParamList->getEnemy()->mPower.ref();
    isPlayerProfile(this);
    return 0;
}

}  // namespace ksys::act
