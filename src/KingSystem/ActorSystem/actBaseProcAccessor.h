#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>

namespace ksys {
struct MesTransceiverId;
namespace act {

class Actor;
class BaseProc;

/// Holds a reference to a BaseProc for safe, multi-threaded access (unofficial name; upstream 6e9afd0f7).
class BaseProcAccessor {
public:
    BaseProcAccessor() = default;
    explicit BaseProcAccessor(BaseProc* proc) { acquire(proc); }
    /// Destructor that automatically releases any acquired BaseProc.
    ~BaseProcAccessor();

    BaseProcAccessor(const BaseProcAccessor&) = delete;
    BaseProcAccessor& operator=(const BaseProcAccessor&) = delete;
    BaseProcAccessor(BaseProcAccessor&& other) noexcept {
        *this = std::move(other);
    }
    BaseProcAccessor& operator=(BaseProcAccessor&& other) noexcept {
        std::swap(mAcquired, other.mAcquired);
        std::swap(mProc, other.mProc);
        return *this;
    }

    /// Acquire a BaseProc. This increments its reference count.
    /// If an actor was already acquired, it is released.
    bool acquire(BaseProc* proc);

    void release() { acquire(nullptr); }

    bool hasProc() const { return mProc != nullptr; }
    // Inline in the original (ActorObserver compares the procs of two accessors directly).
    BaseProc* getProc() const { return mProc; }

    const Actor* getActor() const;
    // Defined in actActorLinkConstDataAccess.cpp, where the original links them. Matching callers use them on
    // 0x10-byte accessors, so they stay members of this class (upstream 6e9afd0f7 moved them to the subclass).
    const MesTransceiverId* getMessageTransceiverId() const;
    const sead::Matrix34f& getActorMtx() const;
    // 0x7100d11860: the transform of the physics body of the actor (main body accessor) or its matrix; false
    // without an actor.
    bool sub_7100D11860(sead::Matrix34f* mtx) const;

protected:
    friend class ActorLinkConstDataAccess;
    friend class BaseProc;
    friend class BaseProcHandle;
    friend class BaseProcUnit;

    bool mAcquired = false;
    BaseProc* mProc = nullptr;
};

/// Acquire the specified BaseProc using `accessor`. Using ActorLinkConstDataAccess is mandatory
/// when acquiring from a low priority thread (see BaseProcMgr for a definition).
bool acquireProc(BaseProcAccessor* accessor, BaseProc* proc, const sead::SafeString& from,
                 s32 = 2);

}  // namespace act

}  // namespace ksys
