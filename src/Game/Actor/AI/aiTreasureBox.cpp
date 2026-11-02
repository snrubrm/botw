#include "Game/Actor/AI/aiTreasureBox.h"
#include "Game/Actor/aiUnk_710073BB28.h"
#include "KingSystem/Physics/Constraint/physUnk_7102519e58.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

bool sub_710072B8E8(ksys::act::Actor* actor);

namespace uking::ai {

TreasureBox::TreasureBox(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TreasureBox::~TreasureBox() {
    auto** unit = static_cast<void**>(mSharpWeaponAddParam_a);
    if (*unit)
        *unit = nullptr;
    if (_c0._10)
        delete _c0._10;
}

// NON_MATCHING: name-search temporaries and hinge initialization are scheduled differently.
bool TreasureBox::init_(sead::Heap* heap) {
    *mIsOpenTreasureBox_a = false;
    *mIsSetupDropActor_a = false;
    auto* actor = mActor;
    const auto& name = actor->getName();
    if (name.findIndex("Iron") != -1 || name.findIndex("Wood") != -1 ||
        name.findIndex("Sandworm") != -1) {
        _c0._10 = new (heap) Unk_71024f7180;
        if (_c0._10) {
            const Unk_71024f7180::InitArg arg{actor->getPhysics(), "Body", sead::Vector3f::ex,
                                            sead::Vector3f::ez, "Cover"};
            if (!_c0._10->init(arg, heap)) {
                delete _c0._10;
                _c0._10 = nullptr;
            }
        }
    }
    return true;
}

void TreasureBox::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* map_object = actor->getMapObject();
    if (!*mIsSetupDropActor_a)
        setupDropActor();

    const bool revival_enabled =
        map_object && map_object->checkRevivalFlag(ksys::map::ActorData::Flag::RevivalEnable);
    _80.x();
    const bool waiting_for_revival = actor->isWaitRevivalForUsed();
    if (revival_enabled || waiting_for_revival || *mIsOpenTreasureBox_a) {
        ksys::act::disableAttClient(mActor, "Open");
        if (_c0._10)
            _c0._10->_44 = true;
        changeChild("オープン待機", nullptr);
    } else {
        ksys::act::enableAttClient(mActor, "Open");
        _80.x();
        if (_c0._10)
            _c0._10->_44 = false;
        changeChild("クローズ待機", nullptr);
    }
}

// NON_MATCHING: the compiler uses different registers and schedules a destination load earlier.
void TreasureBox::setupDropActor() {
    if (mDropActorName_a->isEmpty()) {
        if (auto* drop_data = sead::DynamicCast<ksys::act::DropData>(mActor->getDropData())) {
            // AI string storage is FixedSafeString<80>, with a FixedSafeString<64> fallback.
            static_cast<sead::BufferedSafeString*>(mDropActorName_a)->copy(drop_data->_10[0][0]._8);
        }
    }
    auto* name = mDropActorName_a;
    if (name->isEmpty()) {
        static_cast<sead::BufferedSafeString*>(name)->copy(ksys::act::getDefaultDropActor());
    } else {
        setupDropActorWithName();
    }
    *mIsSetupDropActor_a = true;
}

// NON_MATCHING: temporary strings and the modifier output use different stack slots.
void TreasureBox::setupDropActorWithName() {
    auto* actor = mActor;
    auto* level_sensor = ksys::eco::Ecosystem::instance()->mLevelSensor;
    const auto modifier = ksys::act::getRandomWeaponModifier(
        static_cast<ksys::eco::WeaponModifier>(*mSharpWeaponJudgeType_m), *mDropActorName_a);
    const char* name = mDropActorName_a->cstr();
    Unk_71025afb58* unit = nullptr;
    if (modifier == ksys::eco::WeaponModifier::NoneForced) {
        ksys::act::getBoolParam(actor, "IsAmiibo", false);
    } else {
        const char* scaled_name;
        ksys::eco::WeaponModifier scaled_modifier;
        const bool scaled =
            level_sensor->scaleWeapon(name, modifier, &scaled_name, &scaled_modifier, mActor);
        name = scaled ? scaled_name : name;
        // The selected value is read before getBoolParam can access shared state.
        const auto selected_modifier = scaled ? scaled_modifier : modifier;
        const bool is_amiibo = ksys::act::getBoolParam(actor, "IsAmiibo", false);
        switch (selected_modifier) {
        case ksys::eco::WeaponModifier::None:
        case ksys::eco::WeaponModifier::NoneForced:
            break;
        case ksys::eco::WeaponModifier::Blue:
            if (is_amiibo)
                _c0._8.pickRandomBlueModifierAmiibo(name);
            else
                _c0._8.pickRandomBlueModifierTbox(name);
            unit = &_c0;
            break;
        case ksys::eco::WeaponModifier::Yellow:
            if (is_amiibo)
                _c0._8.pickRandomYellowModifierAmiibo(name);
            else
                _c0._8.pickRandomYellowModifierTbox(name);
            unit = &_c0;
            break;
        default:
            return;
        }
    }
    *static_cast<void**>(mSharpWeaponAddParam_a) = unit;
    if (*mDropActorName_a != name)
        static_cast<sead::BufferedSafeString*>(mDropActorName_a)->copy(name);
}

void TreasureBox::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TreasureBox::calc_() {
    if (isCurrentChild("壊れる"))
        return;
    auto* actor = mActor;
    if (isCurrentChild("クローズ待機")) {
        if (_80._30) {
            if (_c0._10)
                _c0._10->_44 = true;
            const bool can_get_pouch = actorHasTagCanGetPouch(*mDropActorName_a);
            getDemoGetAnotherActor(actor, *mDropActorName_a, can_get_pouch, true, &_c0._8);
            if (can_get_pouch)
                ksys::act::disableAttClient(actor, "Open");
            _80.x();
            return;
        }
        auto* event_mgr = ksys::evt::Manager::instance();
        if (event_mgr && !event_mgr->_1d2b8 && !(event_mgr->_1d2f4_bytes[1] & 1) && _c0._10)
            _c0._10->_44 = false;
        ksys::act::enableAttClient(actor, "Open");
        auto* body = actor->getMainBody();
        if (body && body->getMotionType() == ksys::phys::MotionType::Dynamic) {
            auto* info = body->getContactPointInfo();
            if (body->isActive() && info &&
                (info->getNumContactPoints().load() == 0 || info->begin().isEnd()))
                ksys::act::disableAttClient(actor, "Open");
            else
                ksys::act::enableAttClient(actor, "Open");
        }
    } else if (getCurrentChild()->isFinished()) {
        ksys::act::disableAttClient(mActor, "Open");
        if (_c0._10)
            _c0._10->_44 = true;
        changeChild("オープン待機", nullptr);
        return;
    }
    if (_80._30)
        return;
    auto* event_mgr = ksys::evt::Manager::instance();
    if (!event_mgr || event_mgr->_1d2b8 || (event_mgr->_1d2f4_bytes[1] & 1))
        return;
    auto* chemical = actor->getChemicalStuff();
    auto* life = actor->getLife();
    if ((!life || *life > 0) && (!chemical || chemical->_c0 != 3))
        return;
    ksys::act::disableAttClient(mActor, "Open");
    changeChild("壊れる", nullptr);
}

// NON_MATCHING: the contact checks and listener result join the return paths differently.
bool TreasureBox::handleMessage_(const ksys::Message* message) {
    if (!isCurrentChild("クローズ待機"))
        return false;
    auto* actor = mActor;
    if (sub_710072B8E8(actor))
        return true;
    auto* body = actor->getMainBody();
    if (body && body->getMotionType() == ksys::phys::MotionType::Dynamic) {
        auto* info = body->getContactPointInfo();
        if (body->isActive() && info &&
            (info->getNumContactPoints().load() == 0 || info->begin().isEnd())) {
            return true;
        }
    }
    return _80.m2(*message);
}

void TreasureBox::loadParams_() {
    getMapUnitParam(&mSharpWeaponJudgeType_m, "SharpWeaponJudgeType");
    getMapUnitParam(&mDropActor_m, "DropActor");
    getMapUnitParam(&mDropTable_m, "DropTable");
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
    getAITreeVariable(&mIsSetupDropActor_a, "IsSetupDropActor");
    getAITreeVariable(&mDropActorName_a, "DropActorName");
    getAITreeVariable(&mSharpWeaponAddParam_a, "SharpWeaponAddParam");
}

}  // namespace uking::ai
