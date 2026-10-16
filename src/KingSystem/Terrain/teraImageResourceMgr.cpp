#include <atomic>
#include <cstring>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Terrain/teraAreaNode.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

ImageResourceMgr::~ImageResourceMgr() = default;

void ImageResourceMgr::sub_7101133588(Request* request) {
    mCS68.lock();
    if (!(request->_4c & 0x10)) {
        for (LoadTask& task : mKindLists2[u8(request->_50)]) {
            if (task._20 == 0 && task._80 == request)
                task._20 = 2;
        }
    }
    mLists1c0[u8(request->_50)].erase(request);
    request->_4c &= ~1;
    if (request->addr)
        request->addr = nullptr;
    res::Handle* handle = request->_90;
    request->_90 = nullptr;
    if (_6473 & 2) {
        mLists19c0[u8(request->_50)].pushBack(request);
        request->_4c |= 2;
        mList31c0.pushFront(request);
    }
    mCS68.unlock();

    if (handle && !(_6473 & 2)) {
        handle->~Handle();
        mCS68.lock();
        mHandleFreeList.free(handle);
        mCS68.unlock();
    }
    _626c = 0;
}

void ImageResourceMgr::sub_71011339D0(Request* request) {
    if (request->area->isImageFlagSetMaybe(request->type, 8))
        request->area->sub_71011080D4(request->type);
}

// NON_MATCHING: block order of the failed-reference path.
s32 Unk_7101106F44::sub_7101108860(Unk_7101106F44** out_area, sead::Vector2f* center, f32* size,
                                   const sead::Vector2f& pos, System* system,
                                   const ImageTypeMaybe& type, u32 levels) {
    *out_area = nullptr;
    Unk_7101106F44* start = system->sub_7101115218(center, size, pos, levels);
    sub_71011206E4(&start, center, size, type);
    if (!start)
        return 0;

    Unk_7101106F44* area = start;
    do {
        sub_7101120594(&area, center, size, type);
        if (!area)
            return 0;

        Unk_710250dcd8* image = area->getImageMaybe(type);
        if (image && (image->_18._4.increment() >> 30) == 0) {
            *out_area = area;
            return area == start ? 2 : 1;
        }
        if (Unk_710250dcd8* image_ = area->getImageMaybe(type))
            image_->_18._4.decrement();

        area = area->mParent;
    } while (area);
    return 0;
}

// NON_MATCHING: operand order of one add.
void ImageResourceMgr::sub_7101133724(Request* request) {
    const Unk_7101106F44* area = request->area;
    const Unk_710250dcd8* current = area->getImageMaybe(request->type);
    if (current && current->_8 & 8)
        return;

    if (sub_7101132270(request) || !(request->_4c & 4))
        request->addr->flushCPUCache(request->_6c + request->_64);
    const s32 mip_offset = request->_6c != 0 ? request->_64 : 0;

    std::memset(&request->sampler, 0, sizeof(request->sampler));
    request->area->sub_7101108020(request->type, &request->sampler, *request->addr, mip_offset,
                                  request->_4c >> 2 & 1);
    request->_4c |= 8;
    if (Unk_710250dcd8* image = request->area->getImageMaybe(request->type))
        image->_18.markUsedMaybe();
    request->_4c |= 4;
    ++_6270;
}

// NON_MATCHING: the original sets up `this` for sub_7101131290 after the fence (scheduling).
void ImageResourceMgr::sub_71011311BC() {
    mCS28.lock();
    mCS68.lock();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    sub_7101131290();
    for (Request& request : mList31c0.reverseRobustRange())
        sub_71011320B4(&request);

    _62a0.exchange(mList3200.size());
    if (_62a0.load() != 0)
        mThread->sendMessage(1, sead::MessageQueue::BlockType::Blocking);

    mCS68.unlock();
    mCS28.unlock();
}

// NON_MATCHING: regalloc; the manager pointer is reloaded after the lock and the getA lookups are laid out
// differently (same calls).
void ImageResourceMgr::Unk_7101132878::sub_7101132878(sead::OffsetList<LoadTask>* queue,
                                                      sead::OffsetList<LoadTask>* kind_lists,
                                                      bool load, bool unload) {
    if (load) {
        for (LoadTask& task : queue->robustRange()) {
            if (task._20 != 2) {
                if (task._20 != 0)
                    continue;
                if (task.handle.isValid(mgr->mSystems, task.area, mgr->_6470)) {
                    if (task.area->isImageFlagSetMaybe(task.type, 2)) {
                        if (Unk_710250dcd8* image = task.area->getImageMaybe(task.type))
                            image->_8 &= ~2;
                    }
                    task.system->sub_7101115158(false);
                }
            }
            queue->erase(&task);
            kind_lists[u8(task._24)].erase(&task);
            mgr->mCS68.lock();
            mgr->mList31e8.pushBack(&task);
            mgr->mCS68.unlock();
        }
    }

    if (unload) {
        for (LoadTask& task : queue->robustRange()) {
            if (task._20 != 3) {
                if (task._20 != 1)
                    continue;
                if (task.handle.isValid(mgr->mSystems, task.area, mgr->_6470)) {
                    if (!task.area->isImageFlagSetMaybe(task.type, 2)) {
                        if (Unk_710250dcd8* image = task.area->getImageMaybe(task.type))
                            image->_8 |= 2;
                        if (task.area->isImageFlagSetMaybe(task.type, 8)) {
                            if (Unk_710250dcd8* image = task.area->getImageMaybe(task.type))
                                image->sub_710110DD20(true);
                        }
                        task.area->sub_71011077C8(task.type);
                    }
                    task.system->sub_7101115158(false);
                }
            }
            queue->erase(&task);
            kind_lists[u8(task._24)].erase(&task);
            mgr->mCS68.lock();
            mgr->mList31e8.pushBack(&task);
            mgr->mCS68.unlock();
        }
    }
}

// NON_MATCHING: the sign test of the rounding picks with lt instead of ge (csel operands swapped).
void ImageResourceMgr::sub_7101132FE0(LoadTask* task, System* system, Unk_7101106F44* area,
                                      const ImageTypeMaybe& type) {
    Unk_710250dcd8* image = area->getImageMaybe(type);
    const u32 a = image->m9();
    const u32 b = image->m10();
    const s32 c0 = image->m4();
    const s32 c1 = image->m5();
    const u16 alignment = image->m8();

    u32 size0_a = 0, size0_b = 0, size1_a = 0, size1_b = 0;
    sub_710114ADD4(&size0_a, &size0_b, type, a, b, c0);
    sub_710114ADD4(&size1_a, &size1_b, type, a, b, c1);
    const s32 max_a = size0_a > size1_a ? size0_a : size1_a;
    const s32 max_b = size0_b > size1_b ? size0_b : size1_b;

    task->_20 = 0;
    task->_24 = area->mNameHash;
    task->handle.set(system, area, _6470);
    task->system = system;
    task->area = area;
    task->type = type;
    task->_3c = system->_1330;
    task->_58 = alignment;
    task->_5a = 0;
    task->_64 = c0;
    task->_68 = size0_a;
    task->_6c = size0_b;
    task->_70 = c1;
    task->_74 = size1_a;
    task->_78 = size1_b;
    task->_5c = 0;
    task->_60 = 0;
    task->_7c = 0;
    task->_80 = nullptr;

    const s32 n = alignment;
    task->_5c = alignment > 0x400 ? alignment : sead::Mathu::roundUp(0x400, alignment);
    s32 size = max_a < 0 ? max_a - n + 1 : max_a + n - 1;
    task->_60 = task->_5c + size - size % n;
    task->_7c = (max_b + task->_60 + 0x3f) & ~0x3f;
}

// NON_MATCHING: fence scheduling (as in sub_71011311BC) and the final unlock is not a tail call.
void ImageResourceMgr::sub_7101131290() {
    mCS28.lock();
    mCS68.lock();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    Unk_7101132878 prune{this};
    mCS68.lock();
    prune.sub_7101132878(&mList3200, mKindLists, true, true);
    prune.sub_7101132878(&mList4a18, mKindLists2, true, true);
    mCS68.unlock();

    for (s32 i = 0; i < 0x100; ++i) {
        for (Request& request : mLists1c0[i].robustRange()) {
            if (Unk_710250dcd8* image = request.area->getImageMaybe(request.type))
                image->sub_710110DD20(false);
            if (Unk_710250dcd8* image = request.area->getImageMaybe(request.type))
                image->_8 &= ~2;
            if (request._20.isValid(mSystems, request.area, _6470)) {
                request.area->sub_710110736C(request.type);
                sub_71011339D0(&request);
            }
            sub_7101133588(&request);
        }
    }
    mCS68.unlock();
    mCS28.unlock();
}

s32 ImageResourceMgr::sub_710113333C(LoadTask* task, bool a3) {
    sead::OffsetList<LoadTask>& list = mKindLists[u8(task->_24)];
    for (LoadTask& other : list) {
        if (task->_24 != other._24 || task->system != other.system || task->area != other.area ||
            task->type.raw != other.type.raw) {
            continue;
        }

        s32 result;
        if (!other.handle.isValid(mSystems, task->area, _6470)) {
            result = 0;
        } else if (other._20 != task->_20) {
            result = 2;
        } else {
            result = 1;
            if (!a3)
                return result;
        }
        mList3200.erase(&other);
        list.erase(&other);
        mCS68.lock();
        mList31e8.pushBack(&other);
        mCS68.unlock();
        return result;
    }
    return 0;
}

s32 ImageResourceMgr::sub_7101133274(LoadTask* request) {
    const s32 result = sub_710113333C(request, false);
    if (result != 0)
        return result;

    mKindLists[u8(request->_24)].pushBack(request);
    if (request->_20 == 1)
        mList3200.pushFront(request);
    else
        mList3200.pushBack(request);
    if (_62a0.exchange(mList3200.size()) == 0)
        mThread->sendMessage(1, sead::MessageQueue::BlockType::Blocking);
    return 0;
}

void ImageResourceMgr::sub_71011315BC() {
    _62a0.exchange(mList3200.size());
    if (_62a0.load() != 0)
        mThread->sendMessage(1, sead::MessageQueue::BlockType::Blocking);
}

bool ImageResourceMgr::sub_7101131CDC(System* system) {
    mCS28.lock();
    mCS68.lock();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    bool registered;
    System*& slot = mSystems[system->_1334.slot & 7];
    if (slot) {
        registered = false;
    } else {
        slot = system;
        registered = true;
    }
    mCS68.unlock();
    mCS28.unlock();
    return registered;
}

void ImageResourceMgr::sub_71011334B4() {
    mCS68.lock();
    LoadTask* first = nullptr;
    for (LoadTask& request : mList3200.reverseRobustRange()) {
        if (request._20 != 1)
            continue;
        if (first) {
            if (first == &request)
                break;
        } else {
            first = &request;
        }
        mList3200.erase(&request);
        mList3200.pushFront(&request);
    }
    mCS68.unlock();
}

void ImageResourceMgr::sub_71011355E8(LoadTask* task) {
    mCS68.lock();
    Request* request = task->_80;
    if (!request && !(_6473 & 2)) {
        if (!task->handle.isValid(mSystems, task->area, _6470)) {
            if (Unk_710250dcd8* image = task->area->getImageMaybe(task->type))
                image->_8 |= 0x80000000;
        }
    } else {
        Unk_7101106F44* area = task->area;
        const bool flag = (request->_4c & 8) && area->isImageFlagSetMaybe(task->type, 2);
        if (Unk_710250dcd8* image = area->getImageMaybe(task->type))
            image->sub_710110DD20(flag);
        request->_4c |= 0x10;
        if (task->area->isImageFlagSetMaybe(task->type, 0x40000000)) {
            if (Unk_710250dcd8* image = task->area->getImageMaybe(task->type))
                image->_8 &= ~0x40000000;
        }
    }
    mCS68.unlock();
}

bool ImageResourceMgr::sub_7101131D68() {
    if (mList4a18.size() == 0)
        return false;

    mCS68.lock();
    while (mList4a18.size() != 0) {
        LoadTask* request = mList4a18.popFront();
        mKindLists2[u8(request->_24)].erase(request);
        if (request->_20 == 0)
            sub_71011355E8(request);
        mList31e8.pushBack(request);
    }
    mCS68.unlock();
    return true;
}

void ImageResourceMgr::sub_7101131FD0(Request* request) {
    mCS68.lock();
    if (request->mNode10.isLinked()) {
        mList31c0.erase(request);
        mLists19c0[u8(request->_50)].erase(request);
        request->_4c &= ~2;
    }
    mLists1c0[u8(request->_50)].pushBack(request);
    request->_4c |= 1;
    mCS68.unlock();
}

bool ImageResourceMgr::sub_7101131D64() {
    return sub_7101131D68();
}

// NON_MATCHING: as in sub_7101130E44, the length is used unsigned and the directory select is a csel
// with swapped operands.
bool ImageResourceMgr::sub_7101130FBC(sead::BufferedSafeString* out, System* system,
                                      Unk_7101106F44* area, const ImageTypeMaybe& type) {
    const Unk_710250dcd8* image = area->getImageMaybe(type);
    const bool use_base_dir = image && (image->_8 >> 6 & 1);
    const sead::SafeString dir = system->_1050.cstr();

    bool use_base = false;
    const sead::SafeString* directory = &dir;
    if (use_base_dir) {
        use_base = _6473 & 1;
        if (use_base)
            directory = &mBaseDir;
    }
    const s32 length = out->format("%s/", directory->cstr());
    sead::BufferedSafeString rest(out->getBuffer() + length, out->getBufferSize() - length);
    area->sub_710111FD70(&rest, type);
    return use_base;
}

// NON_MATCHING: the length is used unsigned and the inlined copy differs (one cstr call in the original).
bool ImageResourceMgr::sub_7101130E44(sead::BufferedSafeString* out, const sead::SafeString& dir,
                                      const sead::SafeString& name, bool use_base_dir) {
    bool use_base = false;
    const sead::SafeString* directory = &dir;
    if (use_base_dir) {
        use_base = _6473 & 1;
        if (use_base)
            directory = &mBaseDir;
    }
    const s32 length = out->format("%s/", directory->cstr());
    sead::BufferedSafeString rest(out->getBuffer() + length, out->getBufferSize() - length);
    rest.copy(name);
    return use_base;
}

void ImageResourceMgr::sub_7101136950() {
    for (Request& request : mList31c0.reverseRobustRange()) {
        sub_7101136328(&request, nullptr);
        sub_71011320B4(&request);
    }
}

ImageResourceMgr::Request* ImageResourceMgr::sub_7101131E7C(sead::OffsetList<Request>* lists, void* a2,
                                                             Unk_7101106F44* area,
                                                             const ImageTypeMaybe& type) {
    if (!area->hasImageMaybe(type))
        return nullptr;

    for (Request& request : lists[u8(area->mNameHash)]) {
        if (area->mNameHash == request._50 && type.raw == request.type.raw && request.area == area &&
            request._38 == a2) {
            return &request;
        }
    }
    return nullptr;
}

// NON_MATCHING: the result of sub_7101133274 is compared to 2 and 1 separately in the original; the
// free-list address is computed before the second lock.
s32 ImageResourceMgr::sub_7101135AA0(System* system, Unk_7101106F44* area,
                                     const ImageTypeMaybe& type) {
    mCS68.lock();
    s32 ok = 1;
    if (area->isImageFlagSetMaybe(type, 2)) {
        mCS68.lock();
        LoadTask* task = mList31e8.popBack();
        mCS68.unlock();
        if (!task) {
            ok = 0;
        } else {
            Unk_710250dcd8* image = area->getImageMaybe(type);
            if (!image || !image->_18.tryMarkUnusedMaybe()) {
                mList31e8.pushBack(task);
                ok = 0;
            } else {
                task->_20 = 1;
                task->_24 = area->mNameHash;
                task->handle.set(system, area, _6470);
                task->system = system;
                task->area = area;
                task->type = type;
                task->_3c = system->_1330;
                if (Unk_710250dcd8* image = area->getImageMaybe(type))
                    image->_8 &= ~2;

                const s32 result = sub_7101133274(task);
                if (result == 2 || result == 1) {
                    mList31e8.pushBack(task);
                } else if (result == 0) {
                    if (Unk_710250dcd8* image = area->getImageMaybe(type))
                        image->sub_710110DD20(false);
                }
            }
        }
    }
    mCS68.unlock();
    return ok;
}

void ImageResourceMgr::sub_7101135F34(System* owner, Unk_7101106F44* area, const ImageTypeMaybe& type) {
    LoadTask task;
    mCS68.lock();
    if (Unk_710250dcd8* image = area->getImageMaybe(type))
        image->sub_710110DD20(false);
    if (Unk_710250dcd8* image = area->getImageMaybe(type))
        image->_8 &= ~2;
    task._20 = 1;
    task._24 = area->mNameHash;
    task.handle.set(owner, area, _6470);
    task.system = owner;
    task.area = area;
    task.type = type;
    task._3c = owner->_1330;
    sub_710113333C(&task, true);
    mCS68.unlock();
    sub_7101136188(&task);
}

// NON_MATCHING: argument setup order for sub_7101131E7C (scheduling).
s32 ImageResourceMgr::sub_7101136188(LoadTask* task) {
    mCS68.lock();
    s32 result;
    if (!task->handle.isValid(mSystems, task->area, _6470)) {
        result = 8;
    } else if (Request* request =
                   sub_7101131E7C(mLists1c0, task->system, task->area, task->type)) {
        if (request->_20.isValid(mSystems, request->area, _6470)) {
            request->area->sub_710110736C(request->type);
            sub_71011339D0(request);
        }
        sub_7101133588(request);
        result = 1;
    } else {
        result = 3;
    }
    mCS68.unlock();
    return result;
}

// NON_MATCHING: the original clears _98 and constructs the address in place; ours copies a temporary.
s32 ImageResourceMgr::Unk_7101136B40::sub_7101136B40(s32 result, Request* request) {
    if (!request->_20.isValid(mgr->mSystems, request->area, mgr->_6470)) {
        mgr->sub_7101133588(request);
        if (mgr->_6473 & 2)
            mgr->sub_71011320B4(request);
        return 8;
    }
    if (!request->addr) {
        request->_98 = agl::GPUMemAddrBase(
            mgr->mMemBlock6328,
            s32(reinterpret_cast<uintptr_t>(request) + request->_60 - mgr->_6318));
        request->addr = &request->_98;
    }
    mgr->sub_7101133724(request);
    return result;
}

// NON_MATCHING: the original addresses both statics from one TU static block base; ours reloads it.
bool ImageResourceMgr::Unk_7101136C10::sub_7101136C10(res::Handle* handle, LoadTask* task) {
    static const sead::TickSpan sWaitSpan = sead::TickSpan::makeFromSeconds(1) * 0.03f;
    static const sead::TickSpan sSleepSpan =
        sead::TickSpan::makeFromSeconds(1) * (1.0f / 300.0f);

    if (handle->waitForReady(sWaitSpan))
        return true;

    if (!task) {
        do {
            if (!(mgr->_6473 & 4)) {
                _8 = false;
                return false;
            }
            sead::Thread::sleep(sSleepSpan);
        } while (!handle->waitForReady(sWaitSpan));
        return true;
    }

    do {
        if (!(mgr->_6473 & 4)) {
            _8 = false;
            return false;
        }
        if (!task->handle.isValid(mgr->mSystems, task->area, mgr->_6470))
            return false;
        sead::Thread::sleep(sSleepSpan);
    } while (!handle->waitForReady(sWaitSpan));
    return true;
}

bool ImageResourceMgr::sub_710113625C(System* owner, Unk_7101106F44* area, const ImageTypeMaybe& type,
                                      bool a4, void* a5) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS68);
    sub_7101135F34(owner, area, type);
    if (_6473 & 2) {
        Request* request = sub_7101131E7C(mLists19c0, owner, area, type);
        if (!request)
            return false;
        if (a4)
            sub_7101136328(request, a5);
        sub_71011320B4(request);
    }
    return true;
}

// NON_MATCHING: block layout of the flag 8 branch (the original re-dispatches on the type) and regalloc.
bool ImageResourceMgr::sub_7101133AF8(System* system, Unk_7101106F44* area,
                                      const ImageTypeMaybe& type) {
    mCS68.lock();
    if (area->isImageFlagSetMaybe(type, 2)) {
        mCS68.unlock();
        return true;
    }

    mCS68.lock();
    LoadTask* request = mList31e8.popBack();
    if (!request) {
        mCS68.unlock();
        mCS68.unlock();
        return false;
    }
    mCS68.unlock();

    sub_7101132FE0(request, system, area, type);
    if (Unk_710250dcd8* image = area->getImageMaybe(type))
        image->_8 |= 2;

    const s32 result = sub_7101133274(request);
    if (result == 2) {
        if (area->isImageFlagSetMaybe(type, 8)) {
            if (Unk_710250dcd8* image = area->getImageMaybe(type))
                image->sub_710110DD20(true);
            area->sub_71011077C8(type);
        } else {
            if (Unk_710250dcd8* image = area->getImageMaybe(type))
                image->sub_710110DD20(false);
        }
    } else if (result != 1) {
        mCS68.unlock();
        return true;
    }
    mList31e8.pushBack(request);
    mCS68.unlock();
    return true;
}

}  // namespace ksys::tera
