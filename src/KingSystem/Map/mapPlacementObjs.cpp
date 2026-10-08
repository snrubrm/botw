#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementTree.h"

namespace ksys::map {

PlacementObjs::~PlacementObjs() {
    for (size_t i = 0; i < 10; ++i) {
        auto& group = mGroups.mBuffer[i];
        group.objects.freeBuffer();
        group.num_objs = 0;
    }
}

int PlacementObjs::allocGroupForDynamicMap(PlacementMap* pmap) {
    for (int i = 0; i < 9; ++i) {
        auto& group = mGroups[i + 1];
        if (!group.map) {
            group.map = pmap;
            return i + 1;
        }
    }
    return -1;
}

void PlacementObjs::resetGroup(int group_idx) {
    mGroups[group_idx].map = nullptr;
    mGroups[group_idx].num_objs = 0;
}

void PlacementObjs::freeObjects() {
    for (s32 group_idx = 0; group_idx < 10; ++group_idx) {
        auto& group = mGroups(group_idx);
        for (s32 i = 0; i < group.num_objs; ++i)
            group.objects[i].free();
    }
}

Object* PlacementObjs::allocObj(int group_idx) {
    auto& group = mGroups[group_idx];
    if (group.num_objs >= group.objects.size())
        return nullptr;
    return &group.objects[group.num_objs++];
}

// Inline-only in the original (lane4 s45): the binary search of findObjByHash / findObjByHashInAllGroups.
static Object* findObjInGroup(PlacementObjs::Group& group, int group_idx, const u32& hash,
                              int start, int end) {
    s32 b = group_idx == 0 ? end : group.num_objs - 1;
    s32 a = group_idx == 0 ? start : 0;
    while (a < b) {
        const s32 m = (a + b) / 2;
        const s64 c = s64(group.objects[m].getHashId()) - s64(hash);
        if (c == 0)
            return &group.objects[m];
        if (c < 0)
            a = m + 1;
        else
            b = m;
    }
    auto* obj = &group.objects[a];
    return obj->getHashId() == hash ? obj : nullptr;
}

// NON_MATCHING: scheduling only (the original loads the hash and the group's size / buffer after computing the
// search bounds; ours loads size / buffer first).
Object* PlacementObjs::findObjByHash(const u32& hash, int group_idx, int start, int end) {
    return findObjInGroup(mGroups[group_idx], group_idx, hash, start, end);
}

Object* PlacementObjs::findObjByHashInAllGroups(const u32& hash, int start, int end,
                                                int* out_group) {
    for (s32 group_idx = 0; group_idx < 10; ++group_idx) {
        if (auto* obj = findObjInGroup(mGroups(group_idx), group_idx, hash, start, end)) {
            if (out_group)
                *out_group = group_idx;
            return obj;
        }
    }
    return nullptr;
}

void PlacementObjs::x_0(PlacementTree* tree) {
    for (s32 group_idx = 0; group_idx < 10; ++group_idx) {
        auto& group = mGroups(group_idx);
        for (s32 i = 0; i < group.num_objs; ++i) {
            auto* obj = &group.objects[i];
            if (obj->getFlags0().isOn(Object::Flag0::_1))
                tree->calledForPlaceActor1(obj);
        }
    }
}

}  // namespace ksys::map
