#include "KingSystem/Event/evtEventSystem.h"
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/gameRoot1.h"
#include "Game/gameRoot4.h"
#include "Game/gameRoot38.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "Game/gameScene.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::ui {
void sub_7100A941DC();
}

namespace ksys::evt {

SEAD_SINGLETON_DISPOSER_IMPL(EventSystem)

// NON_MATCHING (createInstance, which has this constructor inlined): the original loads the disposer pointer's GOT slot
// before the vtable's, and stores the first three members (0x30 / 0x32 / 0x34) before the vptrs; ours schedules the
// vtable address first.
EventSystem::EventSystem() {
    for (auto& flag : _3c.mBuffer)
        flag = true;
    for (auto& flag : _45.mBuffer)
        flag = true;
    _50 = 0;
}

EventSystem::~EventSystem() = default;

int EventSystem::handleMessage(const Message& message) {
    return 1;
}

// 0x71008aa970
void EventSystem::x() {
    _30 = 0;
    mSpeaker.updateActorPosition();
    x_4();
    uking::ui::sub_7100A941DC();
}

// NON_MATCHING: singleton load scheduling, branch sharing and zero argument width differ.
void EventSystem::x_4() {
    if (!_32)
        return;
    if (u32(_50) < 9) {
        if (_38 > 0) {
            if (uking::Root1::instance())
                uking::Root1::instance()->sub_7100899CA4(uking::Root1::FlagIdx::_1, 0);
        } else {
            auto* root = uking::Root1::instance();
            if (_34 > 0) {
                if (root)
                    root->sub_7100899CA4(uking::Root1::FlagIdx::_1, 1);
            } else if (root) {
                if (_3c[_50])
                    root->sub_7100899CA4(uking::Root1::FlagIdx::_1, 0);
                else
                    root->sub_7100899CA4(uking::Root1::FlagIdx::_1, 1);
            }
        }
        if (uking::Root4::instance())
            uking::Root4::instance()->sub_71008BCE5C(uking::Root4::FlagIdx::_1, _45[_50], 3);
    }
    _32 = false;
}

// 0x71008ac148
void EventSystem::sub_71008AC148(EventFlowBase* flow) {
    if (flow->getBaseProcLink()->mMetadata.getFlags().getDirect() == 500) {
        const u64 flags = flow->_340;
        if (flags & 0x400000)
            --_38;
        else if (flags & 0x800000)
            --_34;
        else
            return;
    } else {
        --_50;
    }
    _32 = 1;
}

// NON_MATCHING: the stored flag is selected as `bit 22 ? 1 : (!(bit 23) && !byte3)` by `tst w8, #0x400000; csel` in the
// original; ours extracts the bit (`ubfx` + `csinc` / 64-bit selects, depending on the form of the expression).
// 0x71008ac1bc
void EventSystem::sub_71008AC1BC(EventFlowBase* flow) {
    if (flow->getBaseProcLink()->mMetadata.getFlags().getDirect() == 500) {
        const u64 flags = flow->_340;
        if (flags & 0x400000)
            ++_38;
        else if (flags & 0x800000)
            ++_34;
        else
            return;
        _32 = 1;
    } else {
        const s32 count = _50;
        if (count >= 8) {
            _50 = count + 1;
            return;
        }
        const s32 index = count + 1;
        _3c[index] = (!flow->byte3FlagIsSet() && !(flow->_340 & 0x800000)) || (flow->_340 & 0x400000);
        _45[index] = !flow->byte3FlagIsSet();
        _50 = index;
        _32 = 1;
    }
}

// 0x71008ac118
bool EventSystem::sub_71008AC118() const {
    auto* manager = Manager::instance();
    if (!manager)
        return false;
    auto* flow = manager->sub_7100DB222C();
    if (!flow)
        return false;
    return flow->byte3FlagIsSet();
}

// NON_MATCHING: everything else matches, but the original tests bit 7 of the Manager flag byte as `ldrb; tbnz #7` (ours:
// `ldrsb; tbnz #0x1f`; a bool bitfield view gives the same)
// 0x71008ac078
void EventSystem::x_2(s32 value) {
    _140 = value;
    uking::Root38::instance()->setFlag(3, value != 0);
    if (_140)
        _13c = 0;
    if (!(Manager::instance()->_1d2f4_bytes[0] & 0x80))
        uking::ui::showLoadSaveIcon(_140 ? getSceneStatus() != 4 : false);
}

// 0x71008ac100
void EventSystem::x_3(bool value) {
    uking::Root38::instance()->setFlag(5, value);
}

// 0x71008abf30
void EventSystem::sub_71008ABF30() {
    mSpeaker.sub_7100E49784();
}

// 0x71008abf38
void EventSystem::sub_71008ABF38(act::ActorConstDataAccess* accessor) {
    if (accessor)
        act::acquireActor(&mSpeaker.mLink, accessor);
}

bool EventSystem::setSpeaker(act::Actor* actor) {
    if (!actor)
        return false;
    if (actor->getName() == "NPC_DRCVoice")
        return false;
    if (actor->getName() == "NPC_GodVoice")
        return false;
    if (mSpeaker.setSpeaker(actor))
        return true;
    actor->isDeletedOrDeleting();
    return false;
}

}  // namespace ksys::evt
