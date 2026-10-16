#include <atomic>
#include <cstring>
#include "KingSystem/Terrain/teraAreaNode.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

ImageResourceMgr::~ImageResourceMgr() = default;

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

// NON_MATCHING: the original walks _31c0 backwards (prev links; sead::OffsetList has no reverse robust
// iterator in lib yet).
void ImageResourceMgr::sub_71011311BC() {
    mCS28.lock();
    mCS68.lock();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    sub_7101131290();
    for (Request& request : mList31c0.robustRange())
        sub_71011320B4(&request);

    _62a0.exchange(mList3200.size());
    if (_62a0.load() != 0)
        mThread->sendMessage(1, sead::MessageQueue::BlockType::Blocking);

    mCS68.unlock();
    mCS28.unlock();
}

s32 ImageResourceMgr::sub_7101133274(Request* request) {
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

// NON_MATCHING: the original walks the queue backwards (prev links).
void ImageResourceMgr::sub_71011334B4() {
    mCS68.lock();
    Request* first = nullptr;
    for (Request& request : mList3200.robustRange()) {
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

bool ImageResourceMgr::sub_7101131D68() {
    if (mList4a18.size() == 0)
        return false;

    mCS68.lock();
    while (mList4a18.size() != 0) {
        Request* request = mList4a18.popFront();
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

// NON_MATCHING: the original walks mList31c0 through the +0 links (as in sub_71011311BC).
void ImageResourceMgr::sub_7101136950() {
    for (Request& request : mList31c0.robustRange()) {
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
    Request* request = mList31e8.popBack();
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
    mList31e8.pushFront(request);
    mCS68.unlock();
    return true;
}

}  // namespace ksys::tera
