#include "Game/AI/AI/aiAssassinShooterJuniorAzitoRoot.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

AssassinShooterJuniorAzitoRoot::AssassinShooterJuniorAzitoRoot(const InitArg& arg)
    : RememberMesOneActorEnemyRoot(arg) {}

AssassinShooterJuniorAzitoRoot::~AssassinShooterJuniorAzitoRoot() = default;

bool AssassinShooterJuniorAzitoRoot::init_(sead::Heap* heap) {
    return RememberMesOneActorEnemyRoot::init_(heap);
}

void AssassinShooterJuniorAzitoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RememberMesOneActorEnemyRoot::enter_(params);
    sub_7100322CA8(nullptr);
}

// Sends the message of `_238` to the actors of the map object's linked objects (only those whose unit config
// name equals `name` if it is given); the sender's actor link is set to mActor first.
void AssassinShooterJuniorAzitoRoot::sub_7100322CA8(const char* name) {
    _238._18.y(mActor);
    auto* object = mActor->getMapObject();
    if (!object)
        return;
    auto* links = object->getLinkData();
    if (!links)
        return;

    auto objects = links->mObjects;
    for (s32 i = 0; i < objects.size(); ++i) {
        if (!objects(i))
            continue;
        const char* unit_name = objects(i)->getUnitConfigName();
        if (name && sead::SafeString(unit_name) != name)
            continue;
        ksys::act::ActorConstDataAccess accessor;
        objects(i)->getActorWithAccessor(accessor);
        if (accessor.hasProc())
            _238.sub_710070DD78(accessor, true);
    }
}

void AssassinShooterJuniorAzitoRoot::leave_() {
    RememberMesOneActorEnemyRoot::leave_();
}

void AssassinShooterJuniorAzitoRoot::loadParams_() {
    RememberMesOneActorEnemyRoot::loadParams_();
}

void AssassinShooterJuniorAzitoRoot::calc_() {
    auto* prev_child = getCurrentChild();
    RememberMesOneActorEnemyRoot::calc_();
    if (prev_child == getCurrentChild() || !isCurrentChild("リアクション"))
        return;

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    auto& link = enemy->getActorPartsActor(mRememberKey_s);
    if (!link.hasProc())
        return;

    auto* target = sub_71005D9050(mActor);
    auto* actor = mActor;
    const auto& target_pos = sub_71005D9330(actor);
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_268._18.mLock);
        auto& data = _268._18.mData;
        if (target)
            data._0 = *target;
        else
            data._0.reset();
        data._10.acquire(actor, false);
        data._20 = 0;
        data._24 = 2;
        data._28 = target_pos;
        data._34 = 0;
    }
    _268.sub_710070DCC0(&link, true);
}

}  // namespace uking::ai
