#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/gameGraphics.h"
#include <gsys/gsysModel.h>
#include "Game/AI/aiUnk_7100EE53C4.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/System/DebugMessage.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include <container/seadSafeArray.h>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actDropMgr.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/System/physRayCast.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Resource/Actor/resResourceActorLink.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/World/worldManager.h"

extern ksys::DebugMessage sUnk_7102601328;

void getNameAndUniqueName(const ksys::map::Object* object, sead::BufferedSafeString* name,
                          sead::BufferedSafeString* unique_name);

// 2026-10-07: original 0x7100ee9efc reads a bool game-data result; declaration only.
bool checkIsGet(const sead::SafeString& name, bool mode);

// NON_MATCHING: the same-group lookup is inlined from this TU instead of retaining its original call.
bool checkIsGetSameGroupActorName(const sead::SafeString& actor_name, bool mode) {
    sead::SafeString group_name;
    const bool has_group = ksys::act::getSameGroupActorName(&group_name, actor_name);
    return checkIsGet(has_group ? group_name : actor_name, mode);
}

// 2026-10-07: original callback storage at2606B10 is written by EE427C and read by both dispatchers.
GetDemoHandler sGetDemoHandler = nullptr;

void setGetDemoHandler(GetDemoHandler handler) {
    sGetDemoHandler = handler;
}

void callGetDemoHandler(ksys::act::Actor* actor, const sead::SafeString& name) {
    if (sGetDemoHandler)
        sGetDemoHandler(actor, actor, name);
}

void callGetDemoHandler2(ksys::act::Actor* actor, ksys::act::Actor* item,
                         const sead::SafeString& name) {
    if (sGetDemoHandler)
        sGetDemoHandler(actor, item, name);
}

namespace ksys::act {

void getPlacementNameAndUniqueName(Actor* actor, sead::BufferedSafeString* name,
                                   sead::BufferedSafeString* unique_name) {
    name->clear();
    unique_name->clear();
    if (actor)
        getNameAndUniqueName(actor->getMapObject(), name, unique_name);
}

void sub_7100EE3CAC(Actor* actor, s32 message, void* user_data) {
    actor->sub_71011D8AFC(1, 3, message, user_data, nullptr);
}

void sub_7100EE7854(const ActorConstDataAccess& accessor, sead::BufferedSafeString* name,
                    sead::BufferedSafeString* unique_name) {
    getNameAndUniqueName(accessor.getMapObject(), name, unique_name);
}

int getSelectedChoiceIdx(int max_idx, const char* query_name) {
    auto* ui = uking::ui::UI::instance();
    if (!ui)
        return -1;
    const s32 selected = ui->sub_71010A70E4();
    if (selected >= 0 && selected < max_idx)
        return selected;
    sUnk_7102601328.log("クエリ[%s]: 選択された番号 (%d) が不正です。", query_name, selected);
    return -1;
}


void Actor::createDrops(int, int) {
    if (auto* manager = DropMgr::instance())
        manager->createDrops(this, false);
}


void findLinkedActor(ActorLinkConstDataAccess* accessor, Actor* actor,
                     const sead::SafeString& link_name) {
    if (actor) {
        if (auto* map = actor->getMapObject()) {
            if (auto* links = map->getLinkData()) {
                if (auto* object = links->sub_7100D4EFA4(link_name)) {
                    object->getActorWithAccessor(*accessor);
                    return;
                }
            }
        }
    }
    accessor->acquire(nullptr);
}


// NON_MATCHING: the original materialises `-1` before the null result in the no-actor path
map::Object* findLinkReferenceObj(Actor* actor, const sead::SafeString& unit_config_name,
                                  const sead::SafeString& a3, int* idx) {
    if (actor) {
        ActorConstDataAccess accessor{actor};
        return acc::findLinkReferenceObj(accessor, unit_config_name, a3, idx);
    }
    if (idx)
        *idx = -1;
    return nullptr;
}

map::Object* findLinkReferenceObj(BaseProcLink* link, const sead::SafeString& unit_config_name,
                                  const sead::SafeString& a3, int* idx) {
    ActorConstDataAccess accessor;
    acquireActor(link, &accessor);
    return acc::findLinkReferenceObj(accessor, unit_config_name, a3, idx);
}

namespace {

ActorConstDataAccess getAccessor(BaseProcLink* link) {
    ActorConstDataAccess accessor;
    acquireActor(link, &accessor);
    return accessor;
}

ActorConstDataAccess getAccessor(Actor* actor) {
    ActorConstDataAccess accessor{actor};
    return accessor;
}

sead::SafeString sStr_Atk = "Atk";
sead::SafeString sStr_Tgt = "Tgt";
sead::SafeString sStr_Body = "Body";
sead::SafeString sStr_Chemical = "Chemical";
sead::SafeString sStr_EntitySensor = "EntitySensor";
sead::SafeString sStr_Secure = "Secure";
sead::SafeString sStr_Lod = "Lod";
sead::SafeString sStr_CameraCheck = "CameraCheck";
sead::SafeString sStr_GeneralSensor = "GeneralSensor";
sead::SafeString sStr_AtvKeyActorSaveDataIndex = "AtvKeyActorSaveDataIndex";
sead::SafeString sDefaultDropActor = "Item_Fruit_A";
sead::SafeArray<const char*, 6> sArrowTypes{{
    "NormalArrow",
    "BombArrow_A",
    "AncientArrow",
    "FireArrow",
    "IceArrow",
    "ElectricArrow",
}};
gdt::FlagHandle sAnimalMasterAppearanceHandle = gdt::InvalidHandle;
gdt::FlagHandle sFairyCountCheckHandle = gdt::InvalidHandle;
gdt::FlagHandle sIsGetStopTimerLv2Handle = gdt::InvalidHandle;

}  // namespace

bool hasTag(Actor* actor, const sead::SafeString& tag) {
    if (!actor)
        return false;
    return actor->getParam()->getRes().mActorLink->hasTag(tag.cstr());
}

bool hasTag(BaseProcLink* link, const sead::SafeString& tag) {
    return hasTag(getAccessor(link), tag);
}

bool hasTag(const ActorConstDataAccess& accessor, const sead::SafeString& tag) {
    return accessor.hasTag(tag.cstr());
}

bool hasTag(const sead::SafeString& actor, const sead::SafeString& tag) {
    auto* data = InfoData::instance();
    return data && data->hasTag(actor.cstr(), tag.cstr());
}

bool hasTag(Actor* actor, u32 tag) {
    return actor && actor->getParam()->getRes().mActorLink->hasTag(tag);
}

bool hasTag(BaseProcLink* link, u32 tag) {
    return hasTag(getAccessor(link), tag);
}

bool hasTag(const ActorConstDataAccess& accessor, u32 tag) {
    return accessor.hasTag(tag);
}

bool hasTag(const sead::SafeString& actor, u32 tag) {
    auto* data = InfoData::instance();
    return data && data->hasTag(actor.cstr(), tag);
}

bool hasOneTagAtLeast(Actor* actor, const sead::SafeString& tags) {
    sead::FixedSafeString<32> tag;
    for (auto it = tags.tokenBegin(","); tags.tokenEnd(",") != it; ++it) {
        it.get(&tag);
        if (hasTag(actor, tag))
            return true;
    }
    return false;
}

bool hasOneTagAtLeast(BaseProcLink* link, const sead::SafeString& tags) {
    sead::FixedSafeString<32> tag;
    for (auto it = tags.tokenBegin(","); tags.tokenEnd(",") != it; ++it) {
        it.get(&tag);
        if (hasTag(link, tag))
            return true;
    }
    return false;
}

bool hasOneTagAtLeast(const ActorConstDataAccess& accessor, const sead::SafeString& tags) {
    sead::FixedSafeString<32> tag;
    for (auto it = tags.tokenBegin(","); tags.tokenEnd(",") != it; ++it) {
        it.get(&tag);
        if (hasTag(accessor, tag))
            return true;
    }
    return false;
}

// NON_MATCHING: this version doesn't have unnecessary register moves.
bool shouldSkipSpawnWhenRaining(const map::Object* obj) {
    if (obj->getFlags().isOff(map::Object::Flag::CreateNotRain))
        return false;

    if (!world::Manager::instance())
        return false;

    const auto pos = obj->getTranslate();
    return !world::Manager::instance()->isRaining(pos);
}

bool shouldSkipSpawnIfGodForestOff(const map::Object* obj) {
    bool value = false;
    if (obj->getFlags().isOff(map::Object::Flag::UnderGodForestOff))
        return false;
    if (!gdt::Manager::instance()->getBool(sAnimalMasterAppearanceHandle, &value, true))
        return false;
    return value != 0;
}

bool shouldSkipSpawnGodForestActor(const map::Object* obj) {
    bool value = false;
    if (obj->getFlags().isOn(map::Object::Flag::UnderGodForest) &&
        gdt::Manager::instance()->getBool(sAnimalMasterAppearanceHandle, &value, true) && !value) {
        return true;
    }
    return shouldSkipSpawnIfGodForestOff(obj);
}

static bool isFairyCountCheckEnabled() {
    bool value = false;
    return gdt::Manager::instance()->getBool(sFairyCountCheckHandle, &value, true) && value;
}

bool shouldSkipSpawnFairy(const map::Object* obj) {
    const map::ActorData& actor_data = obj->getActorData();
    if (!actor_data.mFlags.isOnBit(map::ActorData::Flag::Fairy))
        return false;

    return isFairyCountCheckEnabled();
}

bool shouldSkipSpawnFairy(const sead::SafeString& actor) {
    auto* info = InfoData::instance();
    if (!info || !info->hasTag(actor.cstr(), tags::Fairy))
        return false;

    return isFairyCountCheckEnabled();
}

void initSpawnConditionGameDataFlags() {
    sFairyCountCheckHandle = gdt::Manager::instance()->getBoolHandle("FairyCountCheck");
    sAnimalMasterAppearanceHandle =
        gdt::Manager::instance()->getBoolHandle("AnimalMaster_Appearance");
    sIsGetStopTimerLv2Handle = gdt::Manager::instance()->getBoolHandle("IsGet_Obj_StopTimerLv2");
}

// TODO: remove this once IsGetStopTimerLv2 is used
// The only purpose of this function is to prevent sIsGetStopTimerLv2Handle from being optimized out
auto initSpawnConditionGameDataFlags_dummy() {
    return sIsGetStopTimerLv2Handle;
}

// NON_MATCHING: redundant branches in the original code.
bool hasAnyRevivalTag(const sead::SafeString& actor) {
    auto* info = InfoData::instance();
    al::ByamlIter iter;
    if (!info || !info->getActorIter(&iter, actor.cstr()))
        return false;

    for (auto tag : {
             tags::RevivalBloodyMoon,
             tags::RevivalRandom,
             tags::RevivalNone,
             tags::RevivalNoneForUsed,
             tags::RevivalRandomForDrop,
             tags::RevivalNoneForDrop,
             tags::RevivalUnderGodTime,
         }) {
        if (info->hasTag(iter, tag))
            return true;
    }
    return false;
}

bool hasStopTimerMiddleTag(Actor* actor) {
    return hasTag(actor, tags::StopTimerMiddle);
}

bool hasStopTimerShortTag(Actor* actor) {
    return hasTag(actor, tags::StopTimerShort);
}

// NON_MATCHING: the original selects the element address (`csel x8, &arr[idx], &arr[0]`), we select the index
const char* arrowTypeToString(ArrowType idx) {
    return sArrowTypes[u32(idx)];
}

ArrowType arrowTypeFromString(const sead::SafeString& name) {
    for (s32 i = 0; i < sArrowTypes.size(); ++i) {
        if (name == sArrowTypes[i])
            return ArrowType(i);
    }
    return ArrowType::Invalid;
}

ZukanType getZukanType(al::ByamlIter* iter) {
    if (!iter)
        return ZukanType::Invalid;

    auto* info = InfoData::instance();

    if (info->hasTag(*iter, tags::ZukanAnimal))
        return ZukanType::Animal;

    if (info->hasTag(*iter, tags::ZukanEnemy))
        return ZukanType::Enemy;

    if (info->hasTag(*iter, tags::ZukanSozai))
        return ZukanType::Sozai;

    if (info->hasTag(*iter, tags::ZukanWeapon))
        return ZukanType::Weapon;

    if (info->hasTag(*iter, tags::ZukanOther))
        return ZukanType::Other;

    return ZukanType::Invalid;
}

ZukanType getZukanType(Actor* actor) {
    if (!actor)
        return ZukanType::Invalid;

    if (hasTag(actor, tags::ZukanAnimal))
        return ZukanType::Animal;

    if (hasTag(actor, tags::ZukanEnemy))
        return ZukanType::Enemy;

    if (hasTag(actor, tags::ZukanSozai))
        return ZukanType::Sozai;

    if (hasTag(actor, tags::ZukanWeapon))
        return ZukanType::Weapon;

    if (hasTag(actor, tags::ZukanOther))
        return ZukanType::Other;

    return ZukanType::Invalid;
}

static bool isProfile(const ActorConstDataAccess& accessor, const sead::SafeString& profile) {
    return accessor.hasProc() && accessor.getProfile() == profile;
}

bool isTagProfileMaybe(const sead::SafeString& profile) {
    return profile == "ComplexTag" || profile == "SoleTag" || profile == "SpotBgmTag" ||
           profile == "EventTag";
}

bool isTagProfileMaybe(Actor* actor) {
    return actor && isTagProfileMaybe(actor->getProfile());
}

bool isPlayerProfile(const ActorConstDataAccess& accessor) {
    return isProfile(accessor, "Player");
}

bool isPlayerProfile(Actor* actor) {
    return isPlayerProfile(getAccessor(actor));
}

bool isPlayerProfile(BaseProcLink* link) {
    return isPlayerProfile(getAccessor(link));
}

const sead::SafeString& getDefaultDropActor() {
    return sDefaultDropActor;
}

const sead::SafeString& getStr_AtvKeyActorSaveDataIndex() {
    return sStr_AtvKeyActorSaveDataIndex;
}

const sead::SafeString& getStr_Atk() {
    return sStr_Atk;
}

const sead::SafeString& getStr_Tgt() {
    return sStr_Tgt;
}

const sead::SafeString& getStr_Body() {
    return sStr_Body;
}

const sead::SafeString& getStr_Chemical() {
    return sStr_Chemical;
}

const sead::SafeString& getStr_EntitySensor() {
    return sStr_EntitySensor;
}

const sead::SafeString& getStr_Secure() {
    return sStr_Secure;
}

const sead::SafeString& getStr_Lod() {
    return sStr_Lod;
}

const sead::SafeString& getStr_CameraCheck() {
    return sStr_CameraCheck;
}

const sead::SafeString& getStr_GeneralSensor() {
    return sStr_GeneralSensor;
}

void sub_7100EE5330(Actor* actor, const sead::SafeString& name) {
    auto* set = actor->getRigidBodyByName(name.cstr());
    if (!set)
        return;
    const int size = set->getRigidBodies().size();
    for (int i = 0; i < size; ++i)
        set->getRigidBodies()[i]->addToWorld();
}

s32 sub_7100EDD218(Actor* actor) {
    if (auto* gparams = actor->getParam()->getRes().mGParamList) {
        if (auto* liftable = gparams->getLiftable())
            return liftable->mThrownMass.ref();
    }
    return 1;
}

void sub_7100EE53C4(Actor* actor) {
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F5EC30();
    else if (auto* body = actor->getMainBody())
        body->addToWorld();
}

void sub_7100EE5408(Actor* actor) {
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F5EC44();
    else if (auto* body = actor->getMainBody())
        body->removeFromWorld();
}

void sub_7100EE5624(Actor* actor) {
    if (auto* set = actor->getRigidBodyByName(sStr_Tgt.cstr())) {
        for (s32 i = 0, n = set->getRigidBodies().size(); i < n; ++i)
            set->getRigidBodies()[i]->removeFromWorld();
    }
    ::sub_7100EE56C0(actor);
}

bool isCameraProfile(Actor* actor) {
    return isProfile(getAccessor(actor), "Camera");
}

bool isNPCProfile(const ActorConstDataAccess& accessor) {
    return isProfile(accessor, "NPC");
}

bool isNPCProfile(Actor* actor) {
    return isNPCProfile(getAccessor(actor));
}

bool isNPCProfile(BaseProcLink* link) {
    return isNPCProfile(getAccessor(link));
}

bool isNPCOffPodFromWeapon(Actor* actor) {
    if (!actor)
        return false;

    auto* gparam = actor->getParam()->getRes().mGParamList;
    if (!gparam)
        return false;

    const auto* npc_param = gparam->getNpc();
    return npc_param && npc_param->mIsOffPodFromWeapon.ref();
}

bool isDemoNPCProfile(Actor* actor) {
    return isProfile(getAccessor(actor), "DemoNPC");
}

bool isEnemyProfile(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    const auto& profile = accessor.getProfile();

    return profile == "Enemy" || profile == "GiantEnemy" || profile == "Guardian" ||
           profile == "GuardianComponent" || profile == "LastBoss" || profile == "GelEnemy" ||
           profile == "EnemySwarm" || profile == "SiteBoss" || profile == "Sandworm" ||
           profile == "Dragon";
}

bool isEnemyProfile(Actor* actor) {
    return isEnemyProfile(getAccessor(actor));
}

bool isEnemyProfile(BaseProcLink* link) {
    return isEnemyProfile(getAccessor(link));
}

bool isGuardianProfile(BaseProcLink* link) {
    const auto accessor = getAccessor(link);
    if (!accessor.hasProc())
        return false;

    const auto& profile = accessor.getProfile();
    return profile == "Guardian" || profile == "GuardianComponent";
}

bool isLargeEnemy(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    const auto& profile = accessor.getProfile();
    return profile == "GiantEnemy" || profile == "LastBoss" || profile == "SiteBoss" ||
           profile == "Sandworm" || profile == "Dragon";
}

bool isLargeEnemy(Actor* actor) {
    return isLargeEnemy(getAccessor(actor));
}

bool isGanonBeast(const ActorConstDataAccess& accessor) {
    return accessor.hasProc() && accessor.getName() == "Enemy_GanonBeast";
}

bool isGanonBeast(BaseProcLink* link) {
    return isGanonBeast(getAccessor(link));
}

bool isNotLivingCreature(Actor* actor) {
    return isNotLivingCreature(getAccessor(actor));
}

bool isNotLivingCreature(const ActorConstDataAccess& accessor) {
    if (isPlayerProfile(accessor))
        return false;
    if (isNPCProfile(accessor))
        return false;
    if (isEnemyProfile(accessor))
        return false;
    if (isHorseProfile(accessor))
        return false;
    if (isPreyOrSwarm(accessor))
        return false;
    return true;
}

bool isNotLivingCreature(BaseProcLink* link) {
    return isNotLivingCreature(getAccessor(link));
}

bool isWeaponProfile(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;
    return isWeaponProfile(accessor.getName());
}

bool isWeaponProfile(const sead::SafeString& actor) {
    const char* profile = nullptr;
    InfoData::instance()->getActorProfile(&profile, actor.cstr());
    return sead::SafeString(profile).startsWith("Weapon");
}

bool isWeaponProfile(Actor* actor) {
    return isWeaponProfile(getAccessor(actor));
}

bool isWeaponProfile(BaseProcLink* link) {
    return isWeaponProfile(getAccessor(link));
}

bool isWeaponOrArmor(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    const auto& name = accessor.getName();
    const char* profile_cstr = nullptr;
    InfoData::instance()->getActorProfile(&profile_cstr, name.cstr());

    const sead::SafeString profile = profile_cstr;
    return profile.startsWith("Weapon") || profile.startsWith("OptionalWeapon") ||
           profile.startsWith("Armor");
}

bool isWeaponOrArmor(Actor* actor) {
    return isWeaponOrArmor(getAccessor(actor));
}

bool isBulletProfile(const ActorConstDataAccess& accessor) {
    return isProfile(accessor, "Bullet");
}

bool isBulletProfile(Actor* actor) {
    return isBulletProfile(getAccessor(actor));
}

bool isBulletProfile(BaseProcLink* link) {
    return isBulletProfile(getAccessor(link));
}

bool isHorseProfile(const ActorConstDataAccess& accessor) {
    return isProfile(accessor, "Horse");
}

bool isHorseProfile(Actor* actor) {
    return isHorseProfile(getAccessor(actor));
}

bool isHorseProfile(BaseProcLink* link) {
    return isHorseProfile(getAccessor(link));
}

bool isGrabAttClientEnabled(void*, BaseProcLink* link) {
    return getAccessor(link).isAttClientEnabled("Grab");
}

bool isStalfosParts(BaseProcLink* link) {
    const auto accessor = getAccessor(link);
    return accessor.hasProc() && accessor.hasTag(tags::StalfosParts);
}

bool isDoor(const ActorConstDataAccess& accessor) {
    return accessor.hasProc() && accessor.hasTag(tags::Door);
}

bool isDoor(BaseProcLink* link) {
    return isDoor(getAccessor(link));
}

bool isPreyOrSwarm(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;
    const auto& profile = accessor.getProfile();
    return profile == "Prey" || profile == "Swarm";
}

bool isPreyOrSwarm(Actor* actor) {
    return isPreyOrSwarm(getAccessor(actor));
}

bool isPreyOrSwarm(BaseProcLink* link) {
    return isPreyOrSwarm(getAccessor(link));
}

bool isWolfOrBear(const ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;
    return accessor.hasTag(tags::AnimalTypeWolf) || accessor.hasTag(tags::AnimalTypeBear);
}

bool isWolfOrBear(Actor* actor) {
    return isWolfOrBear(getAccessor(actor));
}

bool isWolfOrBear(BaseProcLink* link) {
    return isWolfOrBear(getAccessor(link));
}

bool isRope(Actor* actor) {
    const auto accessor = getAccessor(actor);
    return accessor.hasProc() && accessor.isDerivedFrom<RopeBase>();
}

bool isRope(BaseProcLink* link) {
    const auto accessor = getAccessor(link);
    return accessor.hasProc() && accessor.isDerivedFrom<RopeBase>();
}

bool isRope(const ActorConstDataAccess& accessor) {
    return accessor.hasProc() && accessor.isDerivedFrom<RopeBase>();
}

bool isTreeOrScaffoldOrSignboard(Actor* actor) {
    const auto accessor = getAccessor(actor);
    if (!accessor.hasProc())
        return false;

    return accessor.hasTag(tags::Tree) || accessor.hasTag(tags::Scaffold) ||
           accessor.hasTag(tags::Signboard);
}

bool isAirOctaPlatform(const sead::SafeString& name) {
    return name == "Obj_BoardWood_Square_01" || name == "Obj_BoardWood_Triangle_01" ||
           name == "FldObj_DLC_FlyShield_A_Snow_01" || name == "FldObj_DLC_FlyShield_A_Snow_02";
}

bool isAirOctaWoodPlatformDlc(const sead::SafeString& name) {
    return name == "FldObj_DLC_FlyShield_Wood_A_02" ||
           name == "FldObj_DLC_FlyShield_Wood_A_Snow_02";
}

void getRevivalGridPosition(const sead::Vector3f& pos, int* col1, int* row1, int* col2, int* row2) {
    const int col = sead::Mathi::clamp((int(pos.x) + 5000) / 1000, 0, 9);
    const int row = sead::Mathi::clamp((int(pos.z) + 4000) / 1000, 0, 7);

    const auto x = (float(col) + 0.5f) * 1000.0f - 5000.0f;
    const auto z = (float(row) + 0.5f) * 1000.0f - 4000.0f;

    if (x < pos.x) {
        *col1 = col;
        *col2 = col + 1;
    } else {
        *col1 = col - 1;
        *col2 = col;
    }

    if (z < pos.z) {
        *row1 = row;
        *row2 = row + 1;
    } else {
        *row1 = row - 1;
        *row2 = row;
    }
}

bool getSameGroupActorName(sead::SafeString* name, BaseProcLink* link) {
    return getAccessor(link).getSameGroupActorName(name);
}

bool getSameGroupActorName(sead::SafeString* name, Actor* actor) {
    return getAccessor(actor).getSameGroupActorName(name);
}

bool getSameGroupActorName(sead::SafeString* name, const sead::SafeString& default_value,
                           al::ByamlIter* actor_info) {
    const sead::SafeString value = InfoData::instance()->getSameGroupActorName(*actor_info);
    if (value.isEmpty()) {
        *name = default_value;
        return false;
    }
    *name = value;
    return true;
}

bool getSameGroupActorName(sead::SafeString* name, const sead::SafeString& actor_name) {
    const sead::SafeString value = InfoData::instance()->getSameGroupActorName(actor_name.cstr());
    if (value.isEmpty()) {
        *name = actor_name;
        return false;
    }
    *name = value;
    return true;
}

}  // namespace ksys::act

namespace ksys::eco {

bool getEcosystemActorName(sead::SafeString* out, const sead::SafeString& name,
                           const sead::Vector3f& pos) {
    if (name.isEmpty()) {
        *out = sead::SafeString::cEmptyString;
        return false;
    }

    if (name == "LocalSeafood") {
        if (!act::getRandomAreaItem(out, AreaItemType::Fish, pos))
            return false;
        act::getSameGroupActorName(out, *out);
        return true;
    }

    if (name == "EcoSystemRain") {
        *out = sead::SafeString::cEmptyString;
        auto* eco = Ecosystem::instance();
        const int area = eco->getFieldMapArea(pos.x, pos.z);
        if (area < 0)
            return false;

        AreaItemSet items;
        eco->getAreaItems(area, AreaItemType::RainBonusMaterial, &items);
        f32 value = sead::GlobalRandom::instance()->getF32() * 100.0f;
        for (int i = 0; i < items.count; ++i) {
            if (value < items.items[i].num) {
                *out = items.items[i].name;
                return true;
            }
            value -= items.items[i].num;
        }
        return true;
    }

    if (name == "MaliceEnemyRandom") {
        switch (sead::GlobalRandom::instance()->getU32(3)) {
        case 0:
            *out = "Enemy_GanonGrudge";
            break;
        case 1:
            *out = "Enemy_GanonGrudge_01";
            break;
        case 2:
            *out = "Enemy_GanonGrudge_02";
            break;
        default:
            *out = sead::SafeString::cEmptyString;
            return false;
        }
        return true;
    }

    if (name == "MaliceEnemyRandom2") {
        switch (sead::GlobalRandom::instance()->getU32(3)) {
        case 0:
            *out = "Enemy_GanonGrudge_NoLost";
            break;
        case 1:
            *out = "Enemy_GanonGrudge_01_NoLost";
            break;
        case 2:
            *out = "Enemy_GanonGrudge_02_NoLost";
            break;
        default:
            *out = sead::SafeString::cEmptyString;
            return false;
        }
        return true;
    }

    *out = name;
    return true;
}

}  // namespace ksys::eco

namespace ksys::act {

bool getRandomAreaItem(sead::SafeString* item, const eco::AreaItemType& type,
                       const sead::Vector3f& pos) {
    auto* eco = eco::Ecosystem::instance();
    if (!eco)
        return false;

    const int area = eco->getFieldMapArea(pos.x, pos.z);
    eco::AreaItemSet items;
    eco->getAreaItems(area, type, &items);

    int chosen_idx = -1;
    int running_total = 0;

    for (int idx = 0; idx < items.count; ++idx) {
        const int num = items.items[idx].num;
        running_total += num;
        if (int(sead::GlobalRandom::instance()->getU32(running_total)) < num)
            chosen_idx = idx;
    }

    if (chosen_idx < 0) {
        *item = sead::SafeString::cEmptyString;
        return false;
    }

    *item = items.items[chosen_idx].name;
    return true;
}

bool isInSatoriMountainArea(const sead::Vector3f& pos) {
    return eco::Ecosystem::instance()->getFieldMapArea(pos.x, pos.z) == 64;
}

void Actor::emitBasicSigOn() {
    emitSignal(map::MapLinkDefType::BasicSig, true);
    emitSignal(map::MapLinkDefType::BasicSigOnOnly, true);
}

void Actor::emitBasicSigOff() {
    emitSignal(map::MapLinkDefType::BasicSig, false);
}

bool Actor::checkBasicSig() const {
    return checkSignal(map::MapLinkDefType::BasicSig);
}

bool Actor::checkLinkBasicSig() const {
    return checkLinkSignal(map::MapLinkDefType::BasicSig);
}

bool Actor::hasPlacementLinkForBasicSig() const {
    return findPlacementLinkWithType(map::MapLinkDefType::BasicSig) != nullptr;
}

bool Actor::sub_7100EE2050() {
    sead::SafeString tag = "EventTag";
    sub_71011D8AFC(1, 1, 0x800012, nullptr, &tag);
    return true;
}

bool Actor::sub_7100EE20A4() {
    sead::SafeString tag = "EventTag";
    sub_71011D8AFC(1, 1, 0x800013, nullptr, &tag);
    return true;
}

bool Actor::checkRemainsSignal() const {
    return checkSignal(map::MapLinkDefType::Remains);
}

bool Actor::hasPlacementLinkWithTypeRemains() const {
    return findPlacementLinkWithType(map::MapLinkDefType::Remains) != nullptr;
}

bool Actor::checkAxisXSignal() const {
    return checkSignal(map::MapLinkDefType::AxisX);
}

void Actor::emitSignalAxisY_1() {
    emitSignal(map::MapLinkDefType::AxisY, true);
}

void Actor::emitSignalAxisY_0() {
    emitSignal(map::MapLinkDefType::AxisY, false);
}

bool Actor::checkAxisYSignal() const {
    return checkSignal(map::MapLinkDefType::AxisY);
}

bool Actor::hasPlacementLinkWithTypeAxisY() const {
    return findPlacementLinkWithType(map::MapLinkDefType::AxisY) != nullptr;
}

bool Actor::checkAxisZSignal() const {
    return checkSignal(map::MapLinkDefType::AxisZ);
}

bool Actor::checkNAxisXSignal() const {
    return checkSignal(map::MapLinkDefType::NAxisX);
}

void Actor::emitSignalNAxisY_1() {
    emitSignal(map::MapLinkDefType::NAxisY, true);
}

void Actor::emitSignalNAxisY_0() {
    emitSignal(map::MapLinkDefType::NAxisY, false);
}

bool Actor::checkNAxisYSignal() const {
    return checkSignal(map::MapLinkDefType::NAxisY);
}

bool Actor::hasPlacementLinkWithType5AxisY() const {
    return findPlacementLinkWithType(map::MapLinkDefType::NAxisY) != nullptr;
}

bool Actor::checkNAxisZSignal() const {
    return checkSignal(map::MapLinkDefType::NAxisZ);
}

void Actor::emitGimmickSuccessSignal_1() {
    emitSignal(map::MapLinkDefType::GimmickSuccess, true);
}

void Actor::emitGimmickSuccessSignal_0() {
    emitSignal(map::MapLinkDefType::GimmickSuccess, false);
}

bool Actor::checkGimmickSuccessSignal() const {
    return checkSignal(map::MapLinkDefType::GimmickSuccess);
}

bool Actor::checkLinkGimmickSuccessSignal() const {
    return checkLinkSignal(map::MapLinkDefType::GimmickSuccess);
}

bool Actor::checkVelocityControlSignal() const {
    return checkSignal(map::MapLinkDefType::VelocityControl);
}

bool Actor::checkFreezeSignal() const {
    return checkSignal(map::MapLinkDefType::Freeze);
}

bool Actor::hasPlacementLinkWithTypeFreeze() const {
    return findPlacementLinkWithType(map::MapLinkDefType::Freeze) != nullptr;
}

bool Actor::checkForbidAttentionSignal() const {
    if (!hasForbidAttentionLink())
        return false;
    return checkSignal(map::MapLinkDefType::ForbidAttention);
}

bool Actor::hasForbidAttentionLink_0() const {
    return hasForbidAttentionLink();
}

}  // namespace ksys::act

namespace ksys::act {

void sub_7100EE57FC(Actor* actor, const sead::Vector3f& pos) {
    if (auto* controller = actor->getCharacterController()) {
        if (controller->sub_7100F5E954())
            controller->sub_7100F5FBE0(pos);
        else
            controller->warpActorToPosition(pos);
    } else if (auto* body = actor->getMainBody()) {
        if (body->isAddedToWorld())
            body->changePosition(pos, phys::KeepAngularVelocity{false});
        else
            body->setPosition(pos);
    }
}

void sub_7100EE58C0(Actor* actor, const sead::Matrix34f& mtx) {
    if (auto* controller = actor->getCharacterController()) {
        if (controller->sub_7100F5E954())
            controller->sub_7100F5F938(mtx);
        else
            controller->sub_7100F60500(mtx);
    } else if (auto* body = actor->getMainBody()) {
        if (body->isAddedToWorld())
            body->changePositionAndRotation(mtx);
        else
            body->setTransform(mtx);
    }
}

void sub_7100EE5980(Actor* actor, const sead::Vector3f& vel) {
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F5F6FC(vel * 30.0f);
    else if (auto* body = actor->getMainBody())
        body->setLinearVelocity(vel * 30.0f);
}

void sub_7100EE5A14(Actor* actor, const sead::Vector3f& ang_vel) {
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F5FB24(ang_vel * 30.0f);
    else if (auto* body = actor->getMainBody())
        body->setAngularVelocity(ang_vel * 30.0f);
}

void sub_7100EE60A0(phys::CharacterController* controller, f32 value) {
    controller->sub_7100F5E7F0(value * 30.0f);
}

void sub_7100EE61B4(phys::CharacterController* controller, f32 value, const sead::Vector3f& up) {
    controller->sub_7100F5E7F0(value * 30.0f);
    sub_7100EE60AC(controller, up);
}

void sub_7100EE61E8(phys::CharacterController* controller, const sead::Vector3f& vel) {
    controller->sub_7100F5F6FC(vel * 30.0f);
}

void sub_7100EE6228(phys::CharacterController* controller, const sead::Vector3f& ang_vel) {
    controller->sub_7100F5FB24(ang_vel * 30.0f);
}

void sub_7100EE6268(phys::RigidBody* body, const sead::Vector3f& vel) {
    body->setLinearVelocity(vel * 30.0f);
}

void sub_7100EE62B0(phys::RigidBody* body, const sead::Vector3f& ang_vel) {
    body->setAngularVelocity(ang_vel * 30.0f);
}

void getCollidedActorMaybe(ActorLinkConstDataAccess* accessor, phys::RigidBody* body) {
    if (!body)
        return;
    auto* tag = body->getUserTag();
    if (!tag)
        return;
    if (auto* user_tag = sead::DynamicCast<PhysicsUserTag>(tag))
        user_tag->acquireActor(accessor);
}

void sub_7100EE67B0(sead::Vector3f* pos, BaseProcLink* link) {
    ActorConstDataAccess accessor;
    acquireActor(link, &accessor);
    accessor.getActorMtx().getTranslation(*pos);
}

bool getBoolParam(Actor* actor, const sead::SafeString& name, bool default_value) {
    bool* value = nullptr;
    auto* root = actor->getRootAi();
    if (root && root->getAITreeVariable2(&value, name) && value)
        return *value;
    return default_value;
}

bool actorAIGetBool(Actor* actor, const sead::SafeString& name, bool default_value) {
    const bool* value = nullptr;
    auto* root = actor->getRootAi();
    if (root && root->getMapUnitParam(&value, name) && value)
        return *value;
    return default_value;
}

s32 actorAIGetInt(Actor* actor, const sead::SafeString& name, s32 default_value) {
    const s32* value = nullptr;
    auto* root = actor->getRootAi();
    if (root && root->getMapUnitParam(&value, name) && value)
        return *value;
    return default_value;
}

bool isAttClientEnabled(Actor* actor, const sead::SafeString& client) {
    if (!actor)
        return false;
    auto* attention = actor->getAttention();
    if (!attention)
        return false;
    return attention->isClientEnabled(client);
}

bool enableAttClient(Actor* actor, const sead::SafeString& client) {
    if (!actor)
        return false;
    auto* attention = actor->getAttention();
    if (!attention)
        return false;
    return attention->enableClient(client);
}

bool disableAttClient(Actor* actor, const sead::SafeString& client) {
    if (!actor)
        return false;
    auto* attention = actor->getAttention();
    if (!attention)
        return false;
    return attention->disableClient(client);
}

void enableAllAttClients(Actor* actor) {
    if (!actor)
        return;
    auto* attention = actor->getAttention();
    if (!attention)
        return;
    attention->enableAllClients();
}

void disableAllAttClients(Actor* actor) {
    if (!actor)
        return;
    auto* attention = actor->getAttention();
    if (!attention)
        return;
    attention->disableAllClients();
}

AttClient* getAttClientByName(Actor* actor, const sead::SafeString& name) {
    if (!actor)
        return nullptr;
    auto* attention = actor->getAttention();
    if (!attention)
        return nullptr;
    return attention->getClientByName(name);
}

const AttClient* sub_7100EE3E2C(Actor* actor, const sead::SafeString& name) {
    if (!actor)
        return nullptr;
    const auto* attention = actor->getAttention();
    if (!attention)
        return nullptr;
    return attention->getClientByName(name);
}

void sub_7100EEAC50(ActorLinkConstDataAccess* accessor, phys::RigidBody* body) {
    if (auto* tag = sead::DynamicCast<PhysicsUserTag>(body->getUserTag()))
        tag->acquireActor(accessor);
}

void sub_7100EEACE8(phys::RayCast* cast) {
    cast->enableLayer(phys::ContactLayer::EntityGround);
    cast->enableLayer(phys::ContactLayer::EntityGroundRough);
    cast->enableLayer(phys::ContactLayer::EntityGroundSmooth);
    cast->enableLayer(phys::ContactLayer::EntityGroundObject);
    cast->enableLayer(phys::ContactLayer::EntityTree);
}

// 0x7100eeaf30 (lane1 s43): the layers of sub_7100EEAF80 without the player.
// NON_MATCHING: the original builds the -dir temporary first (stack slots and scheduling differ)
void sub_7100EEAFDC(phys::RayCast* cast, const sead::Vector3f& pos, s32 steps) {
    const auto* unk = Graphics::instance()->getUnk_aa8();
    if (!unk)
        return;
    const sead::Vector3f& dir = unk->_7f8;
    const f32 length = steps * 200.0f + 0.1f;
    cast->setStartAndDisplacementScaled(pos - dir * length, -dir, 200.0f);
}

void sub_7100EEAF30(phys::RayCast* cast) {
    cast->enableLayer(phys::ContactLayer::EntityObject);
    cast->enableLayer(phys::ContactLayer::EntityGround);
    cast->enableLayer(phys::ContactLayer::EntityGroundObject);
    cast->enableLayer(phys::ContactLayer::EntityNPC);
    cast->enableLayer(phys::ContactLayer::EntityRagdoll);
}

void sub_7100EEAF80(phys::RayCast* cast) {
    cast->enableLayer(phys::ContactLayer::EntityObject);
    cast->enableLayer(phys::ContactLayer::EntityGround);
    cast->enableLayer(phys::ContactLayer::EntityGroundObject);
    cast->enableLayer(phys::ContactLayer::EntityNPC);
    cast->enableLayer(phys::ContactLayer::EntityRagdoll);
    cast->enableLayer(phys::ContactLayer::EntityPlayer);
}

void sub_7100EEAF28(phys::RayCast* cast) {
    cast->enableLayer(phys::ContactLayer::EntityWater);
}

void sub_7100EEAD38(phys::RayCast* cast) {
    cast->enableLayer(phys::ContactLayer::EntityGround);
    cast->enableLayer(phys::ContactLayer::EntityGroundRough);
    cast->enableLayer(phys::ContactLayer::EntityGroundSmooth);
    cast->enableLayer(phys::ContactLayer::EntityGroundObject);
}

void sub_7100EEAD7C(phys::RayCast* cast) {
    cast->enableLayer(phys::ContactLayer::EntityNPC);
    cast->enableLayer(phys::ContactLayer::EntityGround);
    cast->enableLayer(phys::ContactLayer::EntityGroundRough);
    cast->enableLayer(phys::ContactLayer::EntityGroundSmooth);
    cast->enableLayer(phys::ContactLayer::EntityGroundObject);
    cast->enableLayer(phys::ContactLayer::EntityTree);
    cast->enableLayer(phys::ContactLayer::EntityObject);
    cast->enableLayer(phys::ContactLayer::EntitySmallObject);
    cast->enableLayer(phys::ContactLayer::EntityRope);
}

void sub_7100EEADFC(phys::RayCast* cast) {
    cast->enableLayer(phys::ContactLayer::EntityNPC);
    cast->enableLayer(phys::ContactLayer::EntityGround);
    cast->enableLayer(phys::ContactLayer::EntityGroundRough);
    cast->enableLayer(phys::ContactLayer::EntityGroundSmooth);
    cast->enableLayer(phys::ContactLayer::EntityGroundObject);
    cast->enableLayer(phys::ContactLayer::EntityTree);
}

void sub_7100EEAE58(phys::RayCast* cast) {
    cast->enableLayer(phys::ContactLayer::EntityGround);
    cast->enableLayer(phys::ContactLayer::EntityGroundRough);
    cast->enableLayer(phys::ContactLayer::EntityGroundSmooth);
    cast->enableLayer(phys::ContactLayer::EntityGroundObject);
    cast->enableLayer(phys::ContactLayer::EntityTree);
    cast->enableLayer(phys::ContactLayer::EntityObject);
    cast->enableLayer(phys::ContactLayer::EntitySmallObject);
    cast->enableLayer(phys::ContactLayer::EntityRope);
}

void sub_7100EE5B84(sead::Vector3f* gravity, Actor* actor) {
    f32 factor;
    if (auto* controller = actor->getCharacterController()) {
        *gravity = controller->get70();
        factor = controller->get110();
    } else {
        *gravity = phys::System::instance()->getField48();
        auto* body = actor->getMainBody();
        if (!body)
            return;
        factor = body->getGravityFactor();
    }
    *gravity *= factor;
}

void sub_7100EE5C44(sead::Vector3f* gravity, Actor* actor) {
    sub_7100EE5B84(gravity, actor);
    *gravity *= 1.0f / 900.0f;
}

bool itemIsForSale(Actor* actor) {
    if (auto* obj = actor->getMapObject()) {
        auto* link_data = obj->getLinkData();
        return link_data && link_data->findLinkWithType(map::MapLinkDefType::ForSale);
    }
    return false;
}

}  // namespace ksys::act

namespace ksys::map {

// 0x7100ee2788: the original tests `this` for null (callers null check the object too).
bool Object::getForSaleLink() {
    if (!this)
        return false;
    auto* link_data = getLinkData();
    return link_data && link_data->findLinkWithType(MapLinkDefType::ForSale);
}

}  // namespace ksys::map

namespace ksys::act {

bool isAlive(BaseProcLink* link) {
    ActorConstDataAccess accessor;
    acquireActor(link, &accessor);
    if (accessor.hasProc())
        return accessor.getLife() > 0;
    return false;
}

void sub_7100EE5AA8(Actor* actor, const sead::Vector3f& impulse) {
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F60398(impulse);
    else if (auto* body = actor->getMainBody())
        body->applyLinearImpulse(impulse);
}

void sub_7100EE5AF8(Actor* actor, const sead::Matrix34f& mtx) {
    if (auto* physics = actor->getPhysics())
        physics->setMtxAndScale(mtx, false, false, actor->getScale().x);
}

void sub_7100EE5B18(Actor* actor, const sead::Vector3f& pos) {
    sead::Matrix34f mtx = actor->getMtx();
    mtx.setTranslation(pos);
    if (auto* physics = actor->getPhysics())
        physics->setMtxAndScale(mtx, false, false, actor->getScale().x);
}

void sub_7100EEAECC(phys::RayCast* cast) {
    cast->enableLayer(phys::ContactLayer::EntityGround);
    cast->enableLayer(phys::ContactLayer::EntityGroundRough);
    cast->enableLayer(phys::ContactLayer::EntityGroundSmooth);
    cast->enableLayer(phys::ContactLayer::EntityGroundObject);
    cast->enableLayer(phys::ContactLayer::EntityTree);
    cast->enableLayer(phys::ContactLayer::EntityObject);
}

void setEnabledTalkAndLockOn(Actor* actor, bool enabled) {
    if (!actor || !actor->getAttention())
        return;
    auto* talk = actor->getAttention()->getClientByName("Talk");
    auto* lock_on = actor->getAttention()->getClientByName("LockOn");
    if (!talk)
        return;
    talk->setEnabled(enabled);
    if (lock_on)
        lock_on->setEnabled(enabled);
}

bool attentionStuff(Actor* actor) {
    bool result = false;
    if (actor) {
        if (auto* attention = Attention::instance()) {
            ActorConstDataAccess accessor;
            if (attention->x(&accessor))
                result = accessor.hasProc(actor);
        }
    }
    return result;
}

bool attentionStuff_0(Actor* actor) {
    bool result = false;
    if (actor) {
        if (auto* attention = Attention::instance()) {
            ActorConstDataAccess accessor;
            if (attention->sub_7100D7482C(&accessor))
                result = accessor.hasProc(actor);
        }
    }
    return result;
}

void sub_7100EE9B68(Actor* actor, VFR::ScopedDeltaSetter* setter) {
    if (actor && setter) {
        setter->set(4, 0x41);
        if (auto* model = actor->getModel())
            model->setAutoAnimationFrameRate(setter->mTimeRate);
    }
}

}  // namespace ksys::act

// 0x7100ee5240 (unnamed in the CSV, global namespace; also declared by actionForceSetPlayerRestartPosAngle.cpp): the
// map object referenced by the link of the event's actor.
ksys::map::Object* sub_7100EE5240(ksys::act::Actor* actor, const sead::SafeString& anchor,
                                  const sead::SafeString& unique) {
    auto& link = ksys::evt::sub_7100DC85D4(actor);
    if (!link.hasProc())
        return nullptr;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    return ksys::act::acc::findLinkReferenceObj(accessor, anchor, unique, nullptr);
}

// 0x7100ee2800 (unnamed in the CSV, global namespace; declaration in actActorUtil.h): acquires the actor of the "ForSale"
// link of the actor's map object into `accessor` (an empty accessor if there is none).
bool sub_7100EE2800(ksys::act::ActorLinkConstDataAccess* accessor, ksys::act::Actor* actor) {
    if (auto* object = actor->getMapObject()) {
        if (auto* links = object->getLinkData()) {
            if (auto* link = links->findLinkWithType(ksys::map::MapLinkDefType::ForSale))
                return link->getObjectProcWithAccessor(*accessor);
        }
    }
    return accessor->acquire(nullptr);
}

// NON_MATCHING: the direct first-body return simplifies the original search loop and final indexed selection.
ksys::phys::RigidBody* sub_7100EE5FE4(ksys::act::Actor* actor) {
    if (!actor)
        return nullptr;
    auto* chemicals = actor->getChemicalContainer();
    if (!chemicals)
        return nullptr;
    s32 count = chemicals->_58.size() + chemicals->_80;
    for (s32 i = 0; i < count; ++i) {
        auto* element = chemicals->sub_7100E3718C(i);
        if (!element)
            return nullptr;
        if (element->_278.size() > 0)
            return element->_278[0].body;
    }
    return nullptr;
}
