#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"

namespace uking::act {

ksys::res::DamageParam* Unk_71025ae680::sub_71006DF5A4() {
    if (!_10 || !_10->getParam())
        return nullptr;
    return _10->getParam()->getRes().mDamageParam;
}

}  // namespace uking::act
