#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::eft {

// 0x7100da07fc (the local static is at 0x7102601008, its guard at 0x7102601018; the name is a guess)
xlink2::HandleELink searchAndEmitELink(act::Actor* actor, const char* name) {
    static xlink2::HandleELink sEmptyHandle;
    if (actor) {
        if (auto* xlink = actor->getXLink()) {
            if (auto* user_instance = xlink->_48)
                return user_instance->searchAndEmit(name);
        }
    }
    return sEmptyHandle;
}

// 0x710105dd24 (the local static is at 0x71026152c8, its guard at 0x71026152d8; the name is a guess)
xlink2::HandleSLink searchAndEmitSLink(act::Actor* actor, const char* name, bool force) {
    if (auto* xlink = actor->getXLink()) {
        if (!xlink->_cc.isOn(0x100) || force) {
            if (auto* user_instance = xlink->_50)
                return user_instance->searchAndEmit(name);
        }
    }
    static xlink2::HandleSLink sEmptyHandle;
    return sEmptyHandle;
}

}  // namespace ksys::eft
