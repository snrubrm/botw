#include "Game/AI/AI/aiAssassinMiddleAzitoDlcRoot.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::ai {

// NON_MATCHING (static initializer): the original also initialises two bytes before these objects
// (0 at 0x71025b77e8, 0xfe at 0x71025b77ec), probably statics from an included header.
namespace {
ksys::util::InitConstants sInitConstants;
sead::FixedSafeString<64> sGrabFlagName("BalladOfHeroGerudo_AssasinGrabAncientBall");
sead::FixedSafeString<32> sSuspiciousObjectChildName("不審物発見");
}  // namespace

AssassinMiddleAzitoDlcRoot::AssassinMiddleAzitoDlcRoot(const InitArg& arg)
    : AssassinMiddleAzitoRoot(arg) {}

AssassinMiddleAzitoDlcRoot::~AssassinMiddleAzitoDlcRoot() = default;

bool AssassinMiddleAzitoDlcRoot::init_(sead::Heap* heap) {
    return AssassinMiddleAzitoRoot::init_(heap);
}

void AssassinMiddleAzitoDlcRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinMiddleAzitoRoot::enter_(params);
}

void AssassinMiddleAzitoDlcRoot::calc_() {
    AssassinMiddleAzitoRoot::calc_();
    if (isCurrentChild(sSuspiciousObjectChildName))
        return;

    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm)
        return;
    bool grabbed = false;
    gdm->getParam().get().getBool(&grabbed, sGrabFlagName);
    if (grabbed)
        gdm->setBool(false, sGrabFlagName);
}

void AssassinMiddleAzitoDlcRoot::leave_() {
    AssassinMiddleAzitoRoot::leave_();
}

void AssassinMiddleAzitoDlcRoot::loadParams_() {
    AssassinMiddleAzitoRoot::loadParams_();
}

bool Unk_71023d8428::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.getName().findIndex("DgnObj_RemainsLithograghBall_AoC") != -1;
}

bool AssassinMiddleAzitoDlcRoot::m74(Unk2* out, Unk1* info) {
    Unk_71023d8428 filter;
    if (AssassinNormal::m74(out, info))
        return true;
    return sub_710040CF88(&filter, out);
}

}  // namespace uking::ai
