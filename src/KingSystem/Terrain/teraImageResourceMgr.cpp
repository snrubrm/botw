#include <atomic>
#include <cstring>
#include "KingSystem/Terrain/teraAreaNode.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

void ImageResourceMgr::sub_71011339D0(Request* request) {
    const Unk_710250dcd8* image = request->area->getImageMaybe(request->type);
    if (image && image->_8 & 8)
        request->area->sub_71011080D4(request->type);
}

// NON_MATCHING: the original keeps the list node and reloads the found node from it.
bool Unk_7101118B34::sub_7101118B34(sead::Heap* heap, Unk_7101106F44* area,
                                    Unk_710110d278::Key* key, bool check) {
    Unk_7101108460* found = nullptr;
    for (Unk_7101108460* node : area->mNodes) {
        if (node->getB()->_8 == key) {
            found = node;
            break;
        }
    }

    if (found) {
        if (!check || !(Terrain::instance()->_a58 & 0x400) || found->getA()->_8 & 1)
            return true;
        return false;
    }

    if (area->mParent && !sub_7101118B34(heap, area->mParent, key, check))
        return false;

    Unk_7101108460* node = area->sub_7101108460(heap, key);
    if (!node)
        return false;
    if (check)
        node->getA()->_8 |= 1;
    return true;
}

// NON_MATCHING: two registers swapped in the type-3 loop.
void Unk_7101118B34::sub_71011176BC(Unk_7101106F44* area, bool flag) {
    void (Unk_7101118B34::*fn)(Unk_7101106F44*, const ImageTypeMaybe&) =
        flag ? &Unk_7101118B34::sub_71011171D8 : &Unk_7101118B34::sub_710111731C;

    (this->*fn)(area, sUnk_7101EC54AC);
    (this->*fn)(area, sUnk_7101EC54B4);
    for (Unk_7101108460* node : area->mNodes)
        (this->*fn)(area, node->getImageType());
    for (Unk_710250db28* image : area->mImages)
        (this->*fn)(area, image->getImageType());
}

// NON_MATCHING: `area` and `type` swap callee-saved registers.
void Unk_7101118B34::sub_71011171D8(Unk_7101106F44* area, const ImageTypeMaybe& type) {
    Unk_710250dcd8* image = area->getImageMaybe(type);
    if (!image)
        return;
    if (image->_18._0.increment() == 0)
        pushEntryMaybe(area, type);
}

// NON_MATCHING: `area` and `type` swap callee-saved registers.
void Unk_7101118B34::sub_710111731C(Unk_7101106F44* area, const ImageTypeMaybe& type) {
    Unk_710250dcd8* image = area->getImageMaybe(type);
    if (!image)
        return;
    if (image->_18._0.decrement() == 1)
        pushEntryMaybe(area, type);
}

void Unk_7101118B34::sub_7101118908(Unk_7101106F44* area, u16 id) {
    const Unk_7101108460* node = area->findNodeMaybe(id);
    if (!node->sub_7101108624())
        return;

    s32 count = 0;
    for (const Unk_7101106F44* child : area->mChildren) {
        if (!child)
            continue;
        const Unk_7101108460* child_node = child->findNodeMaybe(id);
        if (child_node)
            count += child_node->sub_7101108624();
    }

    if (count == 4) {
        Terrain::instance()->mImageResourceMgr->sub_710113625C(this, area, makeImageTypeMaybe(2, id),
                                                               false, nullptr);
        area->sub_7101108298(const_cast<Unk_7101108460*>(node));
    }
}

// NON_MATCHING: register allocation; the control flow matches.
bool Unk_7101118B34::sub_7101118C40(sead::Heap* heap, Unk_7101106F44* area,
                                    Unk_710110d278::Key* key, u32 size, bool check, f32 value) {
    const u16 id = key->id;
    Unk_7101108460* node = const_cast<Unk_7101108460*>(area->findNodeMaybe(id));

    if (!node) {
        if (Unk_7101106F44* parent = area->mParent) {
            if (!parent->sub_7101108174(id)) {
                if (!sub_7101118B34(heap, parent, key, check))
                    return false;
            } else if (const Unk_7101108460* parent_node = parent->findNodeMaybe(id)) {
                if (check && Terrain::instance()->_a58 & 0x400 &&
                    !(const_cast<Unk_7101108460*>(parent_node)->getA()->_8 & 1)) {
                    return false;
                }
                sub_7101118908(parent, id);
            } else if (!sub_7101118C40(heap, parent, key, size, check, value)) {
                return false;
            }
        }
        node = area->sub_7101108334(heap, key, size, value);
    } else {
        if (check && Terrain::instance()->_a58 & 0x400) {
            const Unk_710250dcd8* image = area->getImageMaybe(makeImageTypeMaybe(2, id));
            if (!image || !(image->_8 & 1))
                return false;
        }

        if (node->sub_7101108624() && u32(node->getA()->mSize) == size)
            return false;

        s32 count = 0;
        for (Unk_7101106F44* child : area->mChildren) {
            if (!child)
                continue;
            const Unk_7101108460* child_node = child->findNodeMaybe(id);
            if (child_node && (child_node->sub_7101108624() ||
                               sub_7101118C40(heap, child, key, size, check, value))) {
                ++count;
            }
        }
        if (count == 4)
            return true;

        Terrain::instance()->mImageResourceMgr->sub_710113625C(this, area, makeImageTypeMaybe(2, id),
                                                               false, nullptr);
        area->sub_71011081D4(node, heap, size, value);
    }

    if (check) {
        node->getA()->_8 |= 0x10;
        node->getA()->_8 |= 0x20;
        node->getA()->_8 |= 1;
    }
    return true;
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
    System*& slot = mSystems[system->_1334 & 7];
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

}  // namespace ksys::tera
