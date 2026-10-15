#include "Game/Actor/Action/actionBasicSignalBossAwakeSleep.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

BasicSignalBossAwakeSleep::BasicSignalBossAwakeSleep(const InitArg& arg) : BasicSignalEnemyNotice(arg) {}

BasicSignalBossAwakeSleep::~BasicSignalBossAwakeSleep() = default;

bool BasicSignalBossAwakeSleep::init_(sead::Heap* heap) {
    return BasicSignalEnemyNotice::init_(heap);
}

void BasicSignalBossAwakeSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    BasicSignalEnemyNotice::enter_(params);
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
                    ksys::act::ActorLinkConstDataAccess accessor;
                    objects(i)->getActorWithAccessor(accessor);
                    is_calc = accessor.isStateCalc();
                }
                if (is_calc) {
                    if (auto* obj2 = mActor->getMapObject()) {
                        if (auto* link_data2 = obj2->getLinkData()) {
                            auto objects2 = link_data2->mObjects;
                            for (s32 j = 0; j < objects2.size(); ++j) {
                                ksys::act::ActorLinkConstDataAccess accessor2;
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
    BasicSignalEnemyNotice::leave_();
}

void BasicSignalBossAwakeSleep::loadParams_() {
    BasicSignalEnemyNotice::loadParams_();
}

// NON_MATCHING: activation selection and the shared signal tail use different branches.
void BasicSignalBossAwakeSleep::calc_() {
    BasicSignalEnemyNotice::calc_();
    if (ksys::evt::Manager::instance()->hasActiveEvent()) {
        mActor->m107();
        return;
    }
    auto* object = mActor->getMapObject();
    if (!_1c) {
        if (object && object->getLinkData()) {
            auto objects = object->getLinkData()->mObjects;
            for (s32 i = 0; i < objects.size(); ++i) {
                bool is_calc;
                {
                    ksys::act::ActorLinkConstDataAccess accessor;
                    objects(i)->getActorWithAccessor(accessor);
                    is_calc = accessor.isStateCalc();
                }
                if (!is_calc)
                    continue;
                auto* current = mActor->getMapObject();
                if (current && current->getLinkData()) {
                    auto linked = current->getLinkData()->mObjects;
                    for (s32 j = 0; j < linked.size(); ++j) {
                        ksys::act::ActorLinkConstDataAccess accessor;
                        linked(j)->getActorWithAccessor(accessor);
                        _20.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
                    }
                }
                mActor->m107();
                _50 = 3;
                _54 = false;
                return;
            }
        }
        if (_50 >= 0) {
            --_50;
            mActor->m107();
        }
        mActor->emitBasicSigOff();
    } else {
        if (object && object->getLinkData()) {
            auto objects = object->getLinkData()->mObjects;
            for (s32 i = 0; i < objects.size(); ++i) {
                const sead::FormatFixedSafeString<128> name(objects(i)->getUnitConfigName());
                if (name.findIndex("Assassin_Senior") == -1)
                    continue;
                if (objects(i)->checkRevivalFlag(ksys::map::ActorData::Flag::RevivalEnable)) {
                    if (auto* manager = ksys::gdt::Manager::instance()) {
                        bool created = false;
                        manager->getParam().get().getBool(&created, "AssassinBoss_TreasureBoxCreate");
                        if (!created)
                            objects(i)->setRevivalFlagValueIf(
                                ksys::map::ActorData::Flag::RevivalEnable, false);
                    }
                }
                break;
            }
        }
        bool activate = _54;
        if (!activate) {
            object = mActor->getMapObject();
            if (object && object->getLinkData()) {
                auto objects = object->getLinkData()->mObjects;
                for (s32 i = 0; i < objects.size(); ++i) {
                    bool is_calc;
                    {
                        ksys::act::ActorLinkConstDataAccess accessor;
                        objects(i)->getActorWithAccessor(accessor);
                        is_calc = accessor.isStateCalc();
                    }
                    if (!is_calc) {
                        activate = true;
                        break;
                    }
                }
            }
        }
        if (activate) {
            sub_71000B9770();
            mActor->emitBasicSigOn();
            mActor->m107();
            _50 = 3;
        } else if (_50 >= 0) {
            --_50;
            mActor->m107();
        }
    }
    _54 = false;
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
        ksys::act::ActorLinkConstDataAccess accessor;
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
