#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::act {

BaseProcAccessor::~BaseProcAccessor() {
    if (mAcquired && mProc)
        mProc->release();

    mAcquired = false;
    mProc = nullptr;
}

bool BaseProcAccessor::acquire(BaseProc* proc) {
    if (mProc) {
        if (mAcquired)
            mProc->release();

        mAcquired = false;
        mProc = nullptr;
    }

    return proc && proc->acquire(*this);
}

const Actor* BaseProcAccessor::getActor() const {
    if (!mProc)
        return nullptr;
    return sead::DynamicCast<Actor>(mProc);
}

bool acquireProc(BaseProcAccessor* accessor, BaseProc* proc, const sead::SafeString& from,
                 s32) {
    bool acquired = false;

    if (accessor) {
        acquired = accessor->acquire(proc);
        if (!acquired)
            return false;
    }

    if (acquired || BaseProcMgr::instance()->isHighPriorityThread())
        return true;

    sead::FixedSafeString<256> message;
    // (%s)Acquiring from a low priority thread. Please change via ActorLinkConstDataAccess
    message.format("(%s)低スレッドからの取得です。ActorLinkConstDataAccess経由に変更お願いします",
                   from.cstr());
    util::PrintDebug(message);
    return false;
}

}  // namespace ksys::act

Unk_71024de830::~Unk_71024de830() = default;
