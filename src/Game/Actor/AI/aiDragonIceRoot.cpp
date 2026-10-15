#include "Game/Actor/AI/aiDragonIceRoot.h"
#include "Game/Actor/actDragon.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Event/evtEventFlowMgr.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

DragonIceRoot::DragonIceRoot(const InitArg& arg) : DragonRoot(arg) {}

DragonIceRoot::~DragonIceRoot() = default;

bool DragonIceRoot::init_(sead::Heap* heap) {
    if (!DragonRoot::init_(heap))
        return false;

    _3c0 = 99999.0f;
    const s32 num = *mGrudgeBulletMaxNum_s;
    if (num > 0)
        _260._0.tryAllocBuffer(num, heap);
    return true;
}

void DragonIceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRoot::enter_(params);
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (dragon && dragon->_1e0c == 3) {
        if (isRootAiParamINot5())
            sub_7100368FCC(true);
        if (dragon->sub_710000FDFC())
            dragon->sub_710000E500("Color_Grudge");
    }
}

void DragonIceRoot::sub_7100368FCC(bool enabled) {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;
    for (s32 i = 0; i < 4; ++i)
        dragon->sub_710000F654(i);
    for (s32 i = 0; i < 4; ++i) {
        if (dragon->sub_710000F70C(i) && !dragon->getGameDataFlagGrudgeAlive(i))
            dragon->sub_710000FC70(i, enabled, false);
    }
}

void DragonIceRoot::leave_() {
    DragonRoot::leave_();
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;
    if (dragon->_1e0c == 3 && dragon->getGameDataFlag("DropItem", -1)) {
        dragon->setGameDataFlag(true, "ReturnToSky", -1);
        dragon->setGameDataFlag(false, "CreateRunelDragon", -1);
    }
    if (_3d0) {
        if (auto* evt_mgr = ksys::evt::Manager::instance()) {
            if (auto* flow_mgr = evt_mgr->getEventFlowMgr()) {
                flow_mgr->unload(_3d0);
                _3d0 = nullptr;
            }
        }
    }
    _398.fadeXLink();
}

// NON_MATCHING: phase-switch branch order and alive-count addition scheduling differ.
void DragonIceRoot::calc_() {
    DragonRoot::calc_();
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon || !dragon->getCharacterController())
        return;
    auto* child = getCurrentChild();
    if (!child)
        return;

    if (child->isFinishedOrFailed()) {
        if (isCurrentChild("ラネール山頂から移動開始")) {
            dragon->_1f70.reset(0x20000000);
            if (sead::DynamicCast<act::Dragon>(mActor)) {
                _388 = 1;
                sub_7100357150(-1.0f, mGrudgeEventRail_pre1st_s, sead::Vector2f::zero);
                m40(-1.0f);
            }
        } else if (isCurrentChild("ラネール山頂へ帰還")) {
            changeChild("ラネール山頂待機", nullptr);
        } else if (isCurrentChild("ラネール山頂からの帰還予備動作")) {
            if (sead::DynamicCast<act::Dragon>(mActor)) {
                _388 = 5;
                changeChild("ラネール山頂から空へ", nullptr);
            }
        } else if (isCurrentChild("ラネール山頂から空へ")) {
            dragon->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            setFinished();
        }
    } else if (child->isChangeable()) {
        if (m47() && dragon->_1e0c == 3 && isCurrentChild("ラネール山頂待機"))
            changeChild("ラネール山頂からの帰還予備動作", nullptr);
        if (isCurrentChild("停止"))
            changeChild("帰還", nullptr);
        if ((dragon->_1f70.getDirect() & 0x300) == 0x200) {
            _38c = 0;
            if (!isCurrentChild("ラネール山頂待機") && _38._8.rail) {
                // Native retains this repeated name lookup and discards its result.
                if (_38._8.rail->getUniqueName())
                    _38._8.rail->getUniqueName();
                if (_388 == 6) {
                    s32 alive = dragon->getGameDataFlagGrudgeAlive(0);
                    alive += dragon->getGameDataFlagGrudgeAlive(1);
                    alive += dragon->getGameDataFlagGrudgeAlive(2);
                    alive += dragon->getGameDataFlagGrudgeAlive(3);
                    if (alive < 4)
                        _388 = 3 - alive;
                }
                switch (_388) {
                case 3:
                    if (sead::DynamicCast<act::Dragon>(mActor)) {
                        _3c8 = 40.0f;
                    }
                    break;
                case 2:
                    if (sead::DynamicCast<act::Dragon>(mActor)) {
                        _3c4 = 1200.0f;
                        _388 = 3;
                        sub_7100357150(-1.0f, mGrudgeEventRail_pre3rd_s, sead::Vector2f::zero);
                        m40(-1.0f);
                    }
                    break;
                case 1:
                    if (sead::DynamicCast<act::Dragon>(mActor)) {
                        _3c4 = 900.0f;
                        _388 = 2;
                        sub_7100357150(-1.0f, mGrudgeEventRail_pre2nd_s, sead::Vector2f::zero);
                        m40(-1.0f);
                    }
                    break;
                }
            }
        } else if (!dragon->_1f70.isOnBit(28) && dragon->_1e0c == 3) {
            // The native countdown also admits an unordered timer.
            if (!(_390 < 0)) {
                ksys::Timer::update(&_390, -1.0f);
            } else if (s32(_38c++) > 300) {
                _38c = 0;
                if (isCurrentChild("移動")) {
                    // Native repeats this lookup even though no caller consumes its name.
                    if (_38._8.rail->getUniqueName())
                        _38._8.rail->getUniqueName();
                    s32 active = dragon->sub_710000F70C(0);
                    active += dragon->sub_710000F70C(1);
                    active += dragon->sub_710000F70C(2);
                    active += dragon->sub_710000F70C(3);
                    switch (_388) {
                    case 3:
                        if (active < 1 && sead::DynamicCast<act::Dragon>(mActor)) {
                            _3c8 = 40.0f;
                        }
                        break;
                    case 2:
                        if (active < 2 && sead::DynamicCast<act::Dragon>(mActor)) {
                            _3c4 = 1200.0f;
                            _388 = 3;
                            sub_7100357150(-1.0f, mGrudgeEventRail_pre3rd_s, sead::Vector2f::zero);
                            m40(-1.0f);
                        }
                        break;
                    case 1:
                        if (active < 3 && sead::DynamicCast<act::Dragon>(mActor)) {
                            _3c4 = 900.0f;
                            _388 = 2;
                            sub_7100357150(-1.0f, mGrudgeEventRail_pre2nd_s, sead::Vector2f::zero);
                            m40(-1.0f);
                        }
                        break;
                    }
                }
            }
        }
    }
    if (dragon->_1e0c != 3)
        return;
    if (_3c8 > 0) {
        ksys::Timer::update(&_3c8, -1.0f);
        if (_3c8 <= 0) {
            _388 = 4;
            if (!dragon->getGameDataFlag("GrudgeDestroyComplete", -1))
                dragon->setGameDataFlag(true, "GrudgeDestroyComplete", -1);
        }
    }
    if (dragon->_1e0c != 3)
        return;
    auto* as_list = dragon->getASList();
    if (u32(_388) < 5) {
        dragon->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_1000000);
        if (as_list)
            as_list->x_2(66, 1, true, false);
    } else {
        dragon->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
        if (as_list)
            as_list->x_2(66, 1, false, false);
    }
    if (dragon->_1e0c != 3)
        return;
    // Native discards the event-slot helper's loaded/entry-point result.
    if (_388 == 3)
        sub_7100369CD4("Demo480_0", "DragonGrudgeAllOff");
    if (isCurrentChild("ラネール山頂待機") && !dragon->sub_710000FDFC())
        sub_7100369CD4("Demo480_3", "IceDragonPartsFirstGet");
    if (dragon->_1f70.isOnBit(28))
        return;
    bool destroyed = false;
    if (dragon->sub_710000FF60(0)) {
        xlinkSearchAndEmit(dragon, "GrudgeDestroy_A", 2, nullptr);
        destroyed = true;
    }
    if (dragon->sub_710000FF60(1)) {
        xlinkSearchAndEmit(dragon, "GrudgeDestroy_B", 2, nullptr);
        destroyed = true;
    }
    if (dragon->sub_710000FF60(2)) {
        xlinkSearchAndEmit(dragon, "GrudgeDestroy_C", 2, nullptr);
        destroyed = true;
    }
    if (dragon->sub_710000FF60(3)) {
        xlinkSearchAndEmit(dragon, "GrudgeDestroy_D", 2, nullptr);
        destroyed = true;
    }
    if (destroyed)
        _3b8 = f32(*mGrudgeSmokeTime_s);
    if (_3b8 > 0) {
        ksys::Timer::update(&_3b8, -1.0f);
        if (_3b8 <= 0)
            _398.fadeXLink();
    }
}

bool DragonIceRoot::sub_7100369CD4(const sead::SafeString& event_name,
                                      const sead::SafeString& entry_point) {
    auto* manager = ksys::evt::Manager::instance();
    if (!manager)
        return false;
    auto* flow_manager = manager->getEventFlowMgr();
    if (!flow_manager)
        return false;
    if (_3d0 && _3d0->mEntryPointName != entry_point) {
        flow_manager->unload(_3d0);
        _3d0 = nullptr;
    }
    if (!_3d0) {
        _3d0 = flow_manager->loadSimple(event_name, entry_point);
        if (!_3d0)
            return false;
    }
    return _3d0->mEntryPointName == entry_point;
}

void DragonIceRoot::loadParams_() {
    DragonRoot::loadParams_();
    getStaticParam(&mGrudgeBulletMaxNum_s, "GrudgeBulletMaxNum");
    getStaticParam(&mGrudgeBulletMinInterval_s, "GrudgeBulletMinInterval");
    getStaticParam(&mGrudgeSmokeTime_s, "GrudgeSmokeTime");
    getStaticParam(&mGrudgeEventRail_pre1stSpeed_s, "GrudgeEventRail_pre1stSpeed");
    getStaticParam(&mGrudgeEventRail_1stSpeed_s, "GrudgeEventRail_1stSpeed");
    getStaticParam(&mGrudgeEventRail_pre2ndSpeed_s, "GrudgeEventRail_pre2ndSpeed");
    getStaticParam(&mGrudgeEventRail_2ndSpeed_s, "GrudgeEventRail_2ndSpeed");
    getStaticParam(&mGrudgeEventRail_pre3rdSpeed_s, "GrudgeEventRail_pre3rdSpeed");
    getStaticParam(&mGrudgeEventRail_3rdSpeed_s, "GrudgeEventRail_3rdSpeed");
    getStaticParam(&mGrudgeEventRail_preEndSpeed_s, "GrudgeEventRail_preEndSpeed");
    getStaticParam(&mGrudgeEventRail_EndSpeed_s, "GrudgeEventRail_EndSpeed");
    getStaticParam(&mGrudgeEventRail_ReturnSpeed_s, "GrudgeEventRail_ReturnSpeed");
    getStaticParam(&mGrudgeBulletRate_s, "GrudgeBulletRate");
    getStaticParam(&mGrudgeEventRail_Start_s, "GrudgeEventRail_Start");
    getStaticParam(&mGrudgeEventRail_pre1st_s, "GrudgeEventRail_pre1st");
    getStaticParam(&mGrudgeEventRail_1st_s, "GrudgeEventRail_1st");
    getStaticParam(&mGrudgeEventRail_pre2nd_s, "GrudgeEventRail_pre2nd");
    getStaticParam(&mGrudgeEventRail_2nd_s, "GrudgeEventRail_2nd");
    getStaticParam(&mGrudgeEventRail_pre3rd_s, "GrudgeEventRail_pre3rd");
    getStaticParam(&mGrudgeEventRail_3rd_s, "GrudgeEventRail_3rd");
    getStaticParam(&mGrudgeEventRail_preEnd_s, "GrudgeEventRail_preEnd");
    getStaticParam(&mGrudgeEventRail_End_s, "GrudgeEventRail_End");
    getStaticParam(&mGrudgeEventRail_ReturnToSky_s, "GrudgeEventRail_ReturnToSky");
    getStaticParam(&mGrudgeBulletActorName_s, "GrudgeBulletActorName");
}

bool DragonIceRoot::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!DragonRoot::reenter_(other, true))
        return false;
    auto* root = sead::DynamicCast<DragonIceRoot>(other);
    if (!root)
        return false;
    if (!sead::DynamicCast<act::Dragon>(root->mActor))
        return false;
    if (!sead::DynamicCast<act::Dragon>(mActor))
        return false;

    _3bc = root->_3bc;
    _3c0 = root->_3c0;
    _3c4 = root->_3c4;
    _3c8 = root->_3c8;
    return true;
}

// NON_MATCHING: the alive-count switch and shared base-call branch are laid out differently.
void DragonIceRoot::m37() {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;
    xlinkEventOn(mActor, 25, 0, false);
    _388 = 6;
    if (dragon->_1e0c == 3 && m35() && m35()->getUniqueName() &&
        sead::SafeString(m35()->getUniqueName()) == mGrudgeEventRail_Start_s &&
        !dragon->getGameDataFlag("DropItem", -1)) {
        s32 alive = dragon->getGameDataFlagGrudgeAlive(0);
        alive += dragon->getGameDataFlagGrudgeAlive(1);
        alive += dragon->getGameDataFlagGrudgeAlive(2);
        alive += dragon->getGameDataFlagGrudgeAlive(3);
        if (alive == 4) {
            if (isRootAiParamINot5())
                xlinkEventOn(mActor, 25, 1, false);
        } else {
            dragon->_1f70.set(0x80000);
            if (alive == 0)
                dragon->setGameDataFlag(true, "GrudgeDestroyDemoEnd", -1);
        }
        if (alive == 0 || alive == 4) {
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            _24c.reset(0x14);
            _24c.set(4);
            _1d8 = 0;
            _388 = alive == 4 ? 0 : 4;
            dragon->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_1000000);
            if (auto* as_list = dragon->getASList())
                as_list->x_2(66, 1, alive != 0, false);
            changeChild("ラネール山頂待機", nullptr);
            return;
        }
        switch (alive) {
        case 1:
            _388 = 3;
            sub_7100357150(0.1f, mGrudgeEventRail_3rd_s, {10.0f, 10.0f});
            break;
        case 2:
            _388 = 2;
            sub_7100357150(0.1f, mGrudgeEventRail_2nd_s, {10.0f, 10.0f});
            break;
        case 3:
            _388 = 1;
            sub_7100357150(0.1f, mGrudgeEventRail_1st_s, {10.0f, 10.0f});
            break;
        }
        m41();
    }
    DragonRoot::m37();
}

f32 DragonIceRoot::m34() {
    f32 speed = DragonRoot::m34();
    switch (_388) {
    case 1:
        if (mGrudgeEventRail_pre1st_s == _38._8.rail->getUniqueName())
            speed *= *mGrudgeEventRail_pre1stSpeed_s;
        else if (mGrudgeEventRail_1st_s == _38._8.rail->getUniqueName())
            speed *= *mGrudgeEventRail_1stSpeed_s;
        break;
    case 2:
        if (mGrudgeEventRail_pre2nd_s == _38._8.rail->getUniqueName())
            speed *= *mGrudgeEventRail_pre2ndSpeed_s;
        else if (mGrudgeEventRail_2nd_s == _38._8.rail->getUniqueName())
            speed *= *mGrudgeEventRail_2ndSpeed_s;
        break;
    case 3:
        if (mGrudgeEventRail_pre3rd_s == _38._8.rail->getUniqueName())
            speed *= *mGrudgeEventRail_pre3rdSpeed_s;
        else if (mGrudgeEventRail_3rd_s == _38._8.rail->getUniqueName())
            speed *= *mGrudgeEventRail_3rdSpeed_s;
        break;
    case 4:
        if (mGrudgeEventRail_preEnd_s == _38._8.rail->getUniqueName())
            speed *= *mGrudgeEventRail_preEndSpeed_s;
        else if (mGrudgeEventRail_End_s == _38._8.rail->getUniqueName())
            speed *= *mGrudgeEventRail_EndSpeed_s;
        break;
    case 5:
        speed *= *mGrudgeEventRail_ReturnSpeed_s;
        break;
    }
    return speed;
}

void DragonIceRoot::m41() {
    DragonRoot::m41();
}

void DragonIceRoot::m42() {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;
    if (dragon->_1e0c != 3) {
        DragonRoot::m42();
        return;
    }
    if (!dragon->sub_710000FDFC() || !(_3c4 > 0))
        return;
    ksys::Timer::update(&_3c4, -1.0f);
    // The native countdown branch also admits an unordered timer.
    if (!(_3bc < 0)) {
        ksys::Timer::update(&_3bc, -1.0f);
        return;
    }
    if (!_24c.isOnBit(3))
        return;
    _260.sub_710036B89C();
    if (!(f32(sead::GlobalRandom::instance()->getS32Range(0, 100)) < *mGrudgeBulletRate_s))
        return;

    for (auto& entry : _260._0) {
        if (entry._0.isAllocatedOrFailed() || entry._10.hasProc())
            continue;
        ksys::act::InstParamPack pack;
        const auto position = mActor->getMtx().getTranslation();
        const sead::Vector3f offset{sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f),
                                   sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f),
                                   sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f)};
        pack->addPosition(position + offset);
        pack->add(offset * 0.01f - mActor->getVelocity() * 0.01f, "@TV");
        ksys::act::ActorCreator::instance()->requestCreateActor(
            mGrudgeBulletActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
            &entry._0, &pack, nullptr, 1);
        break;
    }
    _3bc = f32(*mGrudgeBulletMinInterval_s);
}

// NON_MATCHING: the compiler duplicates the four close calls for the current-child branch.
void DragonIceRoot::m43() {
    DragonRoot::m43();
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;

    if (dragon->sub_710000FDFC()) {
        _24c.set(0x20);
        static const f32 delays[] = {1050.0f, 1050.0f, 900.0f, 1200.0f};
        const f32 delay = u32(_388) < 4 ? delays[_388] : -1.0f;
        const bool moving_to_rail = isCurrentChild("レールに向かう");
        if (moving_to_rail || _3c0 <= delay) {
            dragon->sub_710000F52C(0);
            dragon->sub_710000F52C(1);
            dragon->sub_710000F52C(2);
            dragon->sub_710000F52C(3);
        } else {
            dragon->sub_710000F36C(0);
            if (isCurrentChild("ラネール山頂待機"))
                dragon->sub_710000F52C(1);
            else
                dragon->sub_710000F36C(1);
            dragon->sub_710000F36C(2);
            dragon->sub_710000F36C(3);
        }
        if (!moving_to_rail)
            ksys::Timer::update(&_3c0, 1.0f);
    } else if (dragon->_1e0c == 3 && !dragon->sub_710000FDFC() &&
               !isCurrentChild("ラネール山頂待機")) {
        _24c.set(0x20);
    }
}

void DragonIceRoot::m44(const sead::Vector3f& pos) {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon || dragon->_1e0c == 3)
        return;

    ksys::act::InstParamPack pack;
    pack->addPosition(pos);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "DragonIceBall", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, &pack,
        nullptr, 2);
}

// NON_MATCHING: flag extraction and the shared effect/return branches are scheduled differently.
bool DragonIceRoot::sub_710036AEA8(bool start, bool secondary) {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return false;
    auto* contact = sub_71007A255C(dragon, 0);
    if (!contact || !contact->_c0)
        return false;
    const auto body_name = contact->_c0->getHkBodyName();
    if (body_name.findIndex("怨念") == -1)
        return false;

    bool hit = false;
    bool blocked = false;
    if (body_name.findIndex("頭部") != -1) {
        auto* current = sead::DynamicCast<act::Dragon>(mActor);
        if (current && !current->_1f70.isOnBit(15)) {
            current->sub_710000FC70(0, start, secondary);
            hit = true;
        } else {
            hit = false;
        }
        blocked |= dragon->_1f70.isOnBit(15);
    }
    if (body_name.findIndex("胴前方") != -1) {
        auto* current = sead::DynamicCast<act::Dragon>(mActor);
        if (current && !current->_1f70.isOnBit(16)) {
            current->sub_710000FC70(1, start, secondary);
            hit = true;
        } else {
            hit = false;
        }
        blocked |= dragon->_1f70.isOnBit(16);
    }
    if (body_name.findIndex("胴後方") != -1) {
        auto* current = sead::DynamicCast<act::Dragon>(mActor);
        if (current && !current->_1f70.isOnBit(17)) {
            current->sub_710000FC70(2, start, secondary);
            hit = true;
        } else {
            hit = false;
        }
        blocked |= dragon->_1f70.isOnBit(17);
    }
    if (body_name.findIndex("尻尾") != -1) {
        auto* current = sead::DynamicCast<act::Dragon>(mActor);
        if (current && !current->_1f70.isOnBit(18)) {
            current->sub_710000FC70(3, start, secondary);
            hit = true;
        } else {
            hit = false;
        }
        blocked |= dragon->_1f70.isOnBit(18);
    }
    xlinkEventOn(dragon, 22, blocked ? 2 : 5, true);
    if (hit) {
        Unk_71012419b4 damage;
        xlinkSearchAndEmit(dragon, "GrudgeDamage", 2, &damage);
        damage.sub_71012419B4(contact->_0);
        _398.fadeXLink();
        _3b8 = 0;
        if (body_name.findIndex("頭部") != -1)
            xlinkSearchAndEmit(dragon, "GrudgeSmoke_A", 2, &_398);
        if (body_name.findIndex("胴前方") != -1)
            xlinkSearchAndEmit(dragon, "GrudgeSmoke_B", 2, &_398);
        if (body_name.findIndex("胴後方") != -1)
            xlinkSearchAndEmit(dragon, "GrudgeSmoke_C", 2, &_398);
        if (body_name.findIndex("尻尾") != -1)
            xlinkSearchAndEmit(dragon, "GrudgeSmoke_D", 2, &_398);
    } else {
        Unk_71012419b4 damage;
        xlinkSearchAndEmit(dragon, "GrudgeDamage", 1, &damage);
        damage.sub_71012419B4(contact->_0);
        if (body_name.findIndex("頭部") != -1)
            xlinkSearchAndEmit(dragon, "GrudgeInvincible_A", 0, nullptr);
        if (body_name.findIndex("胴前方") != -1)
            xlinkSearchAndEmit(dragon, "GrudgeInvincible_B", 0, nullptr);
        if (body_name.findIndex("胴後方") != -1)
            xlinkSearchAndEmit(dragon, "GrudgeInvincible_C", 0, nullptr);
        if (body_name.findIndex("尻尾") != -1)
            xlinkSearchAndEmit(dragon, "GrudgeInvincible_D", 0, nullptr);
    }
    return hit;
}

bool DragonIceRoot::m46() {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return false;
    if (dragon->_1e0c == 3)
        return true;
    return DragonRoot::m46();
}

}  // namespace uking::ai
