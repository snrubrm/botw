#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include "KingSystem/System/VFR.h"

namespace al {
class ByamlIter;
}

namespace ksys::eco {
enum class AreaItemType;

// 0x7100ee78b0 (CSV eco::getEcosystemActorName; in the actor utility TU): resolves the special
// actor names "LocalSeafood" (random fish of the area, same-group name), "EcoSystemRain" (rain bonus
// material of the area), "MaliceEnemyRandom" / "MaliceEnemyRandom2" (random Enemy_GanonGrudge
// variant); any other name is copied. Returns false for an empty name or when nothing was found.
bool getEcosystemActorName(sead::SafeString* out, const sead::SafeString& name,
                           const sead::Vector3f& pos);
}  // namespace ksys::eco

namespace ksys::map {
class Object;
}

namespace ksys::phys {
class CharacterController;
class RayCast;
class RigidBody;
}  // namespace ksys::phys

namespace ksys::act {

class Actor;
class AttClient;
class ActorConstDataAccess;
class ActorLinkConstDataAccess;
class BaseProcLink;

// 0x7100ee9b68: applies the animation time rate for the actor update.
void sub_7100EE9B68(Actor* actor, VFR::ScopedDeltaSetter* setter);
// 0x7100ee66c4 (declared only; used by res::AttCheckCharacterOn::check)
bool sub_7100EE66C4(Actor* actor, bool a2);
// 0x7100eeb078 (declared only; used by ForkDisableContact): looks `body` up in the mutex-guarded list of the
// rigid bodies it touches and calls `filter` on each entry; true when an entry was found (and accepted).
bool sub_7100EEB078(phys::RigidBody* body, phys::RigidBody** out,
                    sead::IDelegate2R<phys::RigidBody*, phys::RigidBody*, bool>* filter);
// 0x7100ee3fa8 (declared only; used by res::AttCheckLine::check): a sphere cast between the actor of `link` and the
// actor of `accessor` (line of sight when `as_line_of_sight`).
bool sub_7100EE3FA8(const ActorConstDataAccess& link, const ActorConstDataAccess& accessor,
                    bool as_line_of_sight, f32 radius);

enum class ArrowType {
    /// Wooden arrows.
    Normal = 0,
    /// Bomb arrows.
    Bomb = 1,
    /// Ancient arrows.
    Ancient = 2,
    /// Fire arrows.
    Fire = 3,
    /// Ice arrows.
    Ice = 4,
    /// Shock arrows.
    Electric = 5,

    Invalid = -1,
};

/// Compendium type (図鑑 type).
enum class ZukanType {
    Animal = 0,
    Enemy = 1,
    /// Materials (素材).
    Sozai = 2,
    Weapon = 3,
    Other = 4,
    Invalid = 5,
};

bool hasTag(Actor* actor, const sead::SafeString& tag);
bool hasTag(BaseProcLink* link, const sead::SafeString& tag);
bool hasTag(const ActorConstDataAccess& accessor, const sead::SafeString& tag);
bool hasTag(const sead::SafeString& actor, const sead::SafeString& tag);

bool hasTag(Actor* actor, u32 tag);
bool hasTag(BaseProcLink* link, u32 tag);
bool hasTag(const ActorConstDataAccess& accessor, u32 tag);
bool hasTag(const sead::SafeString& actor, u32 tag);

/// Checks whether the actor has at least one of the specified tags.
/// @param tags A comma separated list of tags.
bool hasOneTagAtLeast(Actor* actor, const sead::SafeString& tags);
bool hasOneTagAtLeast(BaseProcLink* link, const sead::SafeString& tags);
bool hasOneTagAtLeast(const ActorConstDataAccess& accessor, const sead::SafeString& tags);

bool shouldSkipSpawnWhenRaining(const map::Object* obj);
bool shouldSkipSpawnIfGodForestOff(const map::Object* obj);
bool shouldSkipSpawnGodForestActor(const map::Object* obj);
bool shouldSkipSpawnFairy(const map::Object* obj);
bool shouldSkipSpawnFairy(const sead::SafeString& actor);

/// Must be called before using any of the "should skip" functions above.
void initSpawnConditionGameDataFlags();

bool hasAnyRevivalTag(const sead::SafeString& actor);

bool hasStopTimerMiddleTag(Actor* actor);
bool hasStopTimerShortTag(Actor* actor);
bool canBeStasised(Actor* actor, bool force);

void highlightStasisableActors(bool on);

const char* arrowTypeToString(ArrowType idx);
ArrowType arrowTypeFromString(const sead::SafeString& name);

ZukanType getZukanType(al::ByamlIter* iter);
ZukanType getZukanType(Actor* actor);

bool isPlayerProfile(const ActorConstDataAccess& accessor);
bool isPlayerProfile(Actor* actor);
bool isPlayerProfile(BaseProcLink* link);

bool isCameraProfile(Actor* actor);

bool isNPCProfile(const ActorConstDataAccess& accessor);
bool isNPCProfile(Actor* actor);
bool isNPCProfile(BaseProcLink* link);
bool isNPCOffPodFromWeapon(Actor* actor);

bool isDemoNPCProfile(Actor* actor);

bool isEnemyProfile(const ActorConstDataAccess& accessor);
bool isEnemyProfile(Actor* actor);
bool isEnemyProfile(BaseProcLink* link);

bool isGuardianProfile(BaseProcLink* link);

bool isLargeEnemy(const ActorConstDataAccess& accessor);
bool isLargeEnemy(Actor* actor);

bool isGanonBeast(const ActorConstDataAccess& accessor);
bool isGanonBeast(BaseProcLink* link);

bool isNotLivingCreature(Actor* actor);
bool isNotLivingCreature(const ActorConstDataAccess& accessor);
bool isNotLivingCreature(BaseProcLink* link);

bool isWeaponProfile(const ActorConstDataAccess& accessor);
bool isWeaponProfile(const sead::SafeString& actor);
bool isWeaponProfile(Actor* actor);
bool isWeaponProfile(BaseProcLink* link);

bool isWeaponOrArmor(const ActorConstDataAccess& accessor);
bool isWeaponOrArmor(Actor* actor);

bool isBulletProfile(const ActorConstDataAccess& accessor);
bool isBulletProfile(Actor* actor);
bool isBulletProfile(BaseProcLink* link);

bool isHorseProfile(const ActorConstDataAccess& accessor);
bool isHorseProfile(Actor* actor);
bool isHorseProfile(BaseProcLink* link);

bool isAttClientEnabled(Actor* actor, const sead::SafeString& client);
bool enableAttClient(Actor* actor, const sead::SafeString& client);
bool disableAttClient(Actor* actor, const sead::SafeString& client);
void enableAllAttClients(Actor* actor);
void disableAllAttClients(Actor* actor);
// 0x7100ee3e14 (CSV act::getAttClientByName) / 0x7100ee3e2c: the actor's attention client `name`
// (ActorAttention::getClientByName / its const overload).
AttClient* getAttClientByName(Actor* actor, const sead::SafeString& name);
const AttClient* sub_7100EE3E2C(Actor* actor, const sead::SafeString& name);
bool isGrabAttClientEnabled(void* x, BaseProcLink* link);
// 0x7100ee3d24 (informal CSV name)
bool attentionStuff(Actor* actor);
// 0x7100ee3d9c (informal CSV name)
bool attentionStuff_0(Actor* actor);

bool isStalfosParts(BaseProcLink* link);

bool isDoor(const ActorConstDataAccess& accessor);
bool isDoor(BaseProcLink* link);

bool isPreyOrSwarm(const ActorConstDataAccess& accessor);
bool isPreyOrSwarm(Actor* actor);
bool isPreyOrSwarm(BaseProcLink* link);

bool isWolfOrBear(const ActorConstDataAccess& accessor);
bool isWolfOrBear(Actor* actor);
bool isWolfOrBear(BaseProcLink* link);

bool isRope(const ActorConstDataAccess& accessor);
bool isRope(Actor* actor);
bool isRope(BaseProcLink* link);

bool isTreeOrScaffoldOrSignboard(Actor* actor);

bool isAlive(BaseProcLink* link);

bool isAirOctaPlatform(const sead::SafeString& name);
bool isAirOctaWoodPlatformDlc(const sead::SafeString& name);

const sead::SafeString& getDefaultDropActor();

// 0x7100ee52c4-0x7100ee5324 (CSV names getStr_Atk / _Tgt / _Body / _Chemical; the rest named after
// their strings): rigid body / sensor group names.
// Source namespace inferred from the actor utility implementation.
const sead::SafeString& getStr_AtvKeyActorSaveDataIndex();
const sead::SafeString& getStr_Atk();
const sead::SafeString& getStr_Tgt();
const sead::SafeString& getStr_Body();
const sead::SafeString& getStr_Chemical();
const sead::SafeString& getStr_EntitySensor();
const sead::SafeString& getStr_Secure();
const sead::SafeString& getStr_Lod();
const sead::SafeString& getStr_CameraCheck();
const sead::SafeString& getStr_GeneralSensor();

void getRevivalGridPosition(const sead::Vector3f& pos, int* col1, int* row1, int* col2, int* row2);

bool itemIsForSale(Actor* actor);

bool getSameGroupActorName(sead::SafeString* name, BaseProcLink* link);
bool getSameGroupActorName(sead::SafeString* name, Actor* actor);
bool getSameGroupActorName(sead::SafeString* name, const sead::SafeString& default_value,
                           al::ByamlIter* actor_info);
bool getSameGroupActorName(sead::SafeString* name, const sead::SafeString& actor_name);

s32 getSelectedChoiceIdx(s32 max, const char* query_name);

bool getRandomAreaItem(sead::SafeString* item, const eco::AreaItemType& type,
                       const sead::Vector3f& pos);
bool isInSatoriMountainArea(const sead::Vector3f& pos);

// 0x7100ee22b4: returns the map object linked to `actor` whose unit config name is `unit_config_name`
// (any if empty) and which passes the `a3` filter (unchecked if empty). `idx` (optional) is the link
// index to start the search at and receives the index of the result (-1 if none).
map::Object* findLinkReferenceObj(Actor* actor, const sead::SafeString& unit_config_name,
                                  const sead::SafeString& a3, int* idx);

// 0x7100ee25f0 (lane4 s50): same, for the actor of a BaseProcLink.
map::Object* findLinkReferenceObj(BaseProcLink* link, const sead::SafeString& unit_config_name,
                                  const sead::SafeString& a3, int* idx);

namespace acc {
// 0x7100ee2348 (CSV act::acc::findLinkReferenceObj, 680 B; declaration only, lane4 s50): the accessor version of the
// two functions above.
map::Object* findLinkReferenceObj(ActorConstDataAccess& accessor,
                                  const sead::SafeString& unit_config_name,
                                  const sead::SafeString& a3, int* idx);
}  // namespace acc

// 0x7100ee2260 (CSV findLinkedActor): acquires the actor that `actor`'s placement
// link `link_name` points to into `accessor` (an empty accessor if there is none).
void findLinkedActor(ActorLinkConstDataAccess* accessor, Actor* actor,
                     const sead::SafeString& link_name);

// 0x7100ee57fc (declaration only): sets the actor's position through its character controller or rigid
// body (counterpart of sub_7100EE58C0).
void sub_7100EE57FC(Actor* actor, const sead::Vector3f& pos);
// 0x7100ee58c0: sets the actor's matrix through its character controller or rigid body.
void sub_7100EE58C0(Actor* actor, const sead::Matrix34f& mtx);

// 0x7100ee3f08 (CSV act::setEnabledTalkAndLockOn; declaration only, lane2 s21): enables / disables the "Talk" and
// "LockOn" attention clients of the actor.
void setEnabledTalkAndLockOn(Actor* actor, bool enabled);

// 0x7100ee2850 (declaration only; lane2 s21, placeholder name; 1.7 KB, 4 callers: NPCClerkRoot enter_ / calc_,
// 0x71001228dc): acquires the actor linked by the placement link of the actor into `accessor` (a 0x20-byte
// accessor object); `a3` is whether the actor has the GroupingDisplayItem tag. The last two arguments are null in
// NPCClerkRoot.
bool sub_7100EE2850(Actor* actor, ActorLinkConstDataAccess* accessor, bool a3,
                    ActorLinkConstDataAccess* a4, void* a5);
// 0x7100ee5b18 (declaration only): sets the actor's translation (copy of its matrix with a new
// translation passed to InstanceSet::setMtxAndScale).
void sub_7100EE5B18(Actor* actor, const sead::Vector3f& pos);
// 0x7100ee5980: sets the actor's linear velocity (per frame; scaled by 30 for the physics system)
// through its character controller or main rigid body.
void sub_7100EE5980(Actor* actor, const sead::Vector3f& vel);
// 0x7100ee5b84 (declaration only): gravity acting on the actor (character controller gravity, or
// world gravity scaled by the main rigid body's gravity factor). sub_710072DC50 forwards to it.
void sub_7100EE5B84(sead::Vector3f* gravity, Actor* actor);
// 0x7100ee5c44 (lane1 s43): the same gravity scaled by 1 / 900 (per frame squared); sub_710072DC54 forwards to it.
void sub_7100EE5C44(sead::Vector3f* gravity, Actor* actor);
// 0x7100ee5330 (declaration only; lane3 s17): takes a name (FireWoodBase::enter_ passes getStr_Chemical()).
void sub_7100EE5330(Actor* actor, const sead::SafeString& name);
// 0x7100ee5a14: sets the actor's angular velocity (per frame; scaled by 30 for the physics system).
void sub_7100EE5A14(Actor* actor, const sead::Vector3f& ang_vel);
void sub_7100EE3CAC(Actor* actor, s32 message, void* user_data);
// 0x7100ee544c (declaration only; lane3 s20; RemoveSensor::leave_): adds the rigid bodies of the named body set
// (getStr_* name) back to the world, then continues at 0x7100ee54e8.
void sub_7100EE544C(Actor* actor);
void sub_7100EE5624(Actor* actor);
// 0x7100edd218 (declaration only): the actor's Liftable ThrownMass, or 1 without Liftable params.
s32 sub_7100EDD218(Actor* actor);

// Per-frame -> per-second (x30) forwarders to the character controller / rigid body setters
// (0x7100ee60a0-0x7100ee62b0).
void sub_7100EE60A0(phys::CharacterController* controller, f32 value);
// 0x7100ee60ac (declared only).
void sub_7100EE60AC(phys::CharacterController* controller, const sead::Vector3f& up);
void sub_7100EE61B4(phys::CharacterController* controller, f32 value, const sead::Vector3f& up);
void sub_7100EE61E8(phys::CharacterController* controller, const sead::Vector3f& vel);
void sub_7100EE6228(phys::CharacterController* controller, const sead::Vector3f& ang_vel);
void sub_7100EE6268(phys::RigidBody* body, const sead::Vector3f& vel);
void sub_7100EE62B0(phys::RigidBody* body, const sead::Vector3f& ang_vel);

// 0x7100ee5d34 (CSV name): acquires the actor owning `body` (through its PhysicsUserTag) into
// `accessor`; does nothing for a null body or a body without an actor tag.
void getCollidedActorMaybe(ActorLinkConstDataAccess* accessor, phys::RigidBody* body);
// 0x7100eeac50: same without the null check on `body`.
void sub_7100EEAC50(ActorLinkConstDataAccess* accessor, phys::RigidBody* body);

// 0x7100ee67b0: position of the actor `link` points to.
void sub_7100EE67B0(sead::Vector3f* pos, BaseProcLink* link);
// 0x7100ee6818 (CSV name): AI tree variable `name` of the actor, or `default_value` if it has none.
bool getBoolParam(Actor* actor, const sead::SafeString& name, bool default_value);
// 0x7100ee7828 (CSV name): clears both strings, then fills them from the actor's
// map placement object (no-op for a null actor).
void getPlacementNameAndUniqueName(Actor* actor, sead::BufferedSafeString* name,
                                   sead::BufferedSafeString* unique_name);
// 0x7100ee9a14 (declared only): whether `body` is a player body other than the one whose Havok
// name is "SensorForArea".
bool sub_7100EE9A14(phys::RigidBody* body);

// 0x7100eeace8-0x7100eeaecc: contact layer presets for ray casts (each enables a fixed list of
// layers on `cast`). Placeholder names; sub_7100EEACE8 is used by the AI world ray cast
// sub_710072E928, sub_7100EEAE58 by sub_710072E5F8.
void sub_7100EEACE8(phys::RayCast* cast);
void sub_7100EEAD38(phys::RayCast* cast);
void sub_7100EEAD7C(phys::RayCast* cast);
void sub_7100EEADFC(phys::RayCast* cast);
void sub_7100EEAE58(phys::RayCast* cast);
// 0x7100eeaf28 (lane1 s23): enables the EntityWater layer (used by sub_710072E500 after sub_7100EEACE8).
void sub_7100EEAF28(phys::RayCast* cast);
void sub_7100EEAECC(phys::RayCast* cast);
// 0x7100eeaf80 / 0x7100eeafdc (declared only; lane1 s41, placeholder names): sub_7100EEAF80 enables contact layers
// 0, 8, 2, 4, 5 and 3 on `cast`; sub_7100EEAFDC sets the cast up as a downward line from `pos` (through the global
// gravity direction; no-op without the global object), `steps` * a constant plus 0.1 long.
void sub_7100EEAF80(phys::RayCast* cast);
// 0x7100eeaf30 (lane1 s43): the same without the player layer.
void sub_7100EEAF30(phys::RayCast* cast);
void sub_7100EEAFDC(phys::RayCast* cast, const sead::Vector3f& pos, s32 steps);
// 0x7100ee686c (CSV name): bool map unit parameter `name`, or `default_value` if it has none.
bool actorAIGetBool(Actor* actor, const sead::SafeString& name, bool default_value);
// 0x7100ee68c0 (CSV name): s32 map unit parameter `name`, or `default_value` if it has none.
s32 actorAIGetInt(Actor* actor, const sead::SafeString& name, s32 default_value);

}  // namespace ksys::act

// 0x7100ee2800 (lane4 s50, global namespace; placeholder name): acquires the actor of the ForSale link of the actor's
// map object (an empty accessor if there is none).
bool sub_7100EE2800(ksys::act::ActorLinkConstDataAccess* accessor, ksys::act::Actor* actor);

// 2026-10-07: original returns the first rigid body in the actor chemical elements.
ksys::phys::RigidBody* sub_7100EE5FE4(ksys::act::Actor* actor);

// 2026-10-07: EE427C stores this callback, installed by GameScene initialization with
// getDemoHandler (73A2B8). Both actor arguments and the name are used by that handler.
using GetDemoHandler = void (*)(ksys::act::Actor*, ksys::act::Actor*, const sead::SafeString&);
void setGetDemoHandler(GetDemoHandler handler);
void callGetDemoHandler(ksys::act::Actor* actor, const sead::SafeString& name);
void callGetDemoHandler2(ksys::act::Actor* actor, ksys::act::Actor* item,
                         const sead::SafeString& name);
