#include "Game/Actor/aiUnk_710073BB28.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/UI/uiUtils.h"
#include "Game/gamePlayReport.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/Actor/resResourceActorLink.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include <container/seadBuffer.h>
#include <gfx/seadColor.h>
#include <limits>
#include <math/seadVector.h>

// The TU's merged static block (0x71025c91e0), built by its initializer 0x710073e168. The prefix is
// the same InitConstants / tick / FLT_MAX vector / 19 color block that the other UI-side TUs have
// (uiTUStatics.h); this TU additionally has the tick pair and the InitTimeInfo before the vector.
// The two 8-byte statics at +0x08 / +0x10 are only zeroed by the initializer; their type is a guess.
// GlobalMerge keeps the declaration order, so the tag buffers land at +0x168 / +0x178 as in the
// original.
namespace {
ksys::util::InitConstants sInitConstants;  // +0x00
sead::TickSpan sUnk_71025C91E8;            // +0x08
sead::TickSpan sUnk_71025C91F0;            // +0x10
ksys::util::InitTimeInfo sInitTimeInfo;    // +0x18
sead::Vector3f sMaxVector{std::numeric_limits<f32>::max(), std::numeric_limits<f32>::max(),
                          std::numeric_limits<f32>::max()};  // +0x28
sead::Color4f sColorBlack{0.0f, 0.0f, 0.0f, 1.0f};           // +0x34
sead::Color4f sColorBlackHalf{0.0f, 0.0f, 0.0f, 0.5f};
sead::Color4f sColorGray{0.5f, 0.5f, 0.5f, 1.0f};
sead::Color4f sColorGrayHalf{0.5f, 0.5f, 0.5f, 0.5f};
sead::Color4f sColorWhite{1.0f, 1.0f, 1.0f, 1.0f};
sead::Color4f sColorWhiteHalf{1.0f, 1.0f, 1.0f, 0.5f};
sead::Color4f sColorRed{1.0f, 0.0f, 0.0f, 1.0f};
sead::Color4f sColorRedHalf{1.0f, 0.0f, 0.0f, 0.5f};
sead::Color4f sColorGreen{0.0f, 1.0f, 0.0f, 1.0f};
sead::Color4f sColorGreenHalf{0.0f, 1.0f, 0.0f, 0.5f};
sead::Color4f sColorBlue{0.0f, 0.0f, 1.0f, 1.0f};
sead::Color4f sColorBlueHalf{0.0f, 0.0f, 1.0f, 0.5f};
sead::Color4f sColorYellow{1.0f, 1.0f, 0.0f, 1.0f};
sead::Color4f sColorYellowHalf{1.0f, 1.0f, 0.0f, 0.5f};
sead::Color4f sColorMagenta{1.0f, 0.0f, 1.0f, 1.0f};
sead::Color4f sColorMagentaHalf{1.0f, 0.0f, 1.0f, 0.5f};
sead::Color4f sColorCyan{0.0f, 1.0f, 1.0f, 1.0f};
sead::Color4f sColorCyanHalf{0.0f, 1.0f, 1.0f, 0.5f};
sead::Color4f sColorClear{0.0f, 0.0f, 0.0f, 0.0f};  // +0x154, block ends at +0x164

// The two tags shared by the item get demos: the names at 0x71024512b0 and their crc32 hashes at
// 0x7101e7b808.
const char* sTagNames[] = {"CanGetPouch", "CanGetCollectSet"};
sead::Buffer<const char*> sTagNameList(sTagNames);  // +0x168
const u32 sTagHashes[] = {0xe0194f30, 0x17919f47};
sead::Buffer<const u32> sTagHashList(sTagHashes);   // +0x178
}  // namespace

// 0x710073ba0c
bool itemCanGetPouch(ksys::act::Actor* actor) {
    auto* link = actor->getParam()->getRes().mActorLink;
    if (link->hasTag(sTagHashList[0]))
        return true;
    // The call's result is discarded in the original.
    link->hasTag(sTagHashList[1]);
    return false;
}

// 0x710073ba74
bool itemCanNotGetPouch(ksys::act::Actor* actor) {
    auto* link = actor->getParam()->getRes().mActorLink;
    if (link->hasTag(sTagHashList[0]))
        return false;
    return link->hasTag(sTagHashList[1]);
}

// 0x710073bb88
bool actorHasTagCanGetPouch(const sead::SafeString& actor_name) {
    if (ksys::act::InfoData::instance()->hasTag(actor_name.cstr(), sTagHashList[0]))
        return !uking::ui::PauseMenuDataMgr::instance()->cannotGetItem(actor_name, 1);
    // The result of this check is discarded in the original.
    ksys::act::InfoData::instance()->hasTag(actor_name.cstr(), sTagHashList[1]);
    if (ksys::act::InfoData::instance()->hasTag(actor_name.cstr(), sTagHashList[0]))
        return false;
    return ksys::act::InfoData::instance()->hasTag(actor_name.cstr(), sTagHashList[1]);
}

void sub_710073BB28(bool a, bool b) {
    uking::ui::sub_7100A94AC8();
    uking::ui::sub_7100A94C74(a, b);
}

bool sub_710073BB54() {
    if (uking::ui::sub_7100A94AC8())
        return true;
    return !uking::ui::sub_7100A94E08();
}

bool sub_710073BB80(ksys::act::Actor* actor) {
    return actorHasTagCanGetPouch(actor->getName());
}

void sub_710073BADC() {
    uking::ui::playSound("mc_DoUnable", nullptr);
}

void weaponBroken(ksys::act::Actor* actor) {
    uking::ui::PauseMenuDataMgr::instance()->removeWeaponIfEquipped(actor->getName());
    uking::ui::mainScreen3DStuff();
}

void uking::removeFromInventory(const sead::SafeString& name) {
    uking::ui::PauseMenuDataMgr::instance()->removeWeaponIfEquipped(name);
    uking::ui::mainScreen3DStuff();
}

void masterSwordBroken() {
    uking::ui::PauseMenuDataMgr::instance()->breakMasterSword();
    uking::ui::mainScreen3DStuff();
}

// Declaration-only: full native 620-byte item handler and 332-byte event tail
// establish the side-effect-only return and these two inputs. Source namespace is unknown.
void doGetItem(const sead::SafeString& name, const uking::act::WeaponModifierInfo* modifier);

void setItemDataToPouch(const sead::SafeString& name,
                       const uking::act::WeaponModifierInfo* modifier) {
    if (ksys::act::hasTag(name, ksys::act::tags::ZukanWeapon) &&
        !uking::ui::PauseMenuDataMgr::instance()->cannotGetItem(name, 1)) {
        auto* info = uking::act::PlayerInfo::instance();
        uking::reportGetItem(info ? info->getPlayerPos() : sead::Vector3f::zero, name);
    }
    doGetItem(name, modifier);
}

// NON_MATCHING: the native bool argument uses branch normalization instead of a mask.
void getDemoGetAnotherActor(ksys::act::Actor* actor, const sead::SafeString& actor_name,
                           bool can_get_pouch, bool option, uking::act::WeaponModifierInfo* modifier) {
    if (auto* manager = ksys::evt::Manager::instance()) {
        ksys::evt::Metadata metadata;
        callGetAnotherItemDemo(&metadata, actor_name, can_get_pouch,
                               ksys::act::hasTag(actor, ksys::act::tags::GetAnotherActor), option,
                               modifier);
        manager->callEvent(metadata, actor, nullptr);
    }
}
