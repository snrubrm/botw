#include "Game/AI/Action/actionBasicSignalBossAwakeSleep.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

BasicSignalBossAwakeSleep::BasicSignalBossAwakeSleep(const InitArg& arg) : BasicSignalEnemy(arg) {}

BasicSignalBossAwakeSleep::~BasicSignalBossAwakeSleep() = default;

bool BasicSignalBossAwakeSleep::init_(sead::Heap* heap) {
    return BasicSignalEnemy::init_(heap);
}

void BasicSignalBossAwakeSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    BasicSignalEnemy::enter_(params);
    _50 = 3;
    _54 = false;
    if (_1c) {
        sub_71000B9770();
        mActor->emitBasicSigOn();
        return;
    }

    if (auto* obj = mActor->getMapObject()) {
        if (auto* link_data = obj->getLinkData()) {
            auto objects = link_data->mObjects;
            for (s32 i = 0; i < objects.size(); ++i) {
                bool is_calc;
                {
                    ksys::act::ActorConstDataAccess accessor;
                    objects(i)->getActorWithAccessor(accessor);
                    is_calc = accessor.isStateCalc();
                }
                if (is_calc) {
                    if (auto* obj2 = mActor->getMapObject()) {
                        if (auto* link_data2 = obj2->getLinkData()) {
                            auto objects2 = link_data2->mObjects;
                            for (s32 j = 0; j < objects2.size(); ++j) {
                                ksys::act::ActorConstDataAccess accessor2;
                                objects2(j)->getActorWithAccessor(accessor2);
                                _20.sub_710070DBB0(*accessor2.getMessageTransceiverId(), true);
                            }
                        }
                    }
                    return;
                }
            }
        }
    }
    mActor->emitBasicSigOff();
}

void BasicSignalBossAwakeSleep::leave_() {
    mActor->emitBasicSigOff();
    BasicSignalEnemy::leave_();
}

void BasicSignalBossAwakeSleep::loadParams_() {
    BasicSignalEnemy::loadParams_();
}

void BasicSignalBossAwakeSleep::calc_() {
    BasicSignalEnemy::calc_();
}

void BasicSignalBossAwakeSleep::m32() {
    mActor->m107();
    _54 = true;
}

void BasicSignalBossAwakeSleep::m33() {
    mActor->m107();
}

void BasicSignalBossAwakeSleep::sub_71000B9770() {
    auto* obj = mActor->getMapObject();
    if (!obj)
        return;
    auto* link_data = obj->getLinkData();
    if (!link_data)
        return;
    auto objects = link_data->mObjects;
    for (s32 i = 0; i < objects.size(); ++i) {
        ksys::act::ActorConstDataAccess accessor;
        objects(i)->getActorWithAccessor(accessor);
        if (accessor.isStateSleep()) {
            sead::Matrix34f mtx;
            accessor.getHomeMtx(&mtx);
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 6, -1);
        } else {
            _38.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
        }
    }
}

}  // namespace uking::action
