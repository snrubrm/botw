#pragma once

#include <Havok/Ai/Pathfinding/NavMesh/hkaiNavMesh.h>
#include <Havok/Ai/Pathfinding/hkaiAgentTraversalInfo.h>
#include <Havok/Common/Base/hkBase.h>

class hkaiStreamingCollection;

// Reflection initializer 0x7101775738 establishes the hkReferencedObject
// parent and 0x10 extent. Default filter vtable 0x710255f1e0 has the inherited
// five slots, one unknown hook, then the two isEnabled operations at +0x30/+0x38.
class hkaiAstarEdgeFilter : public hkReferencedObject {
public:
    // Descriptive names: this 0x80 query is built by both graphSearchMaybe
    // 0x71015498ac and HavokAI 0x7100f86de4. Each 0x30 edge record holds a key,
    // edge/data pointers and position. The trailing face key/pointers occupy
    // +0x60/+0x68/+0x70. The default filter consumes +0x40 and +0x70.
    struct NavMeshQuery {
        struct EdgeInfo {
            hkUint32 m_key;
            const hkaiNavMesh::Edge* m_edge;
            const hkInt32* m_data;
            hkVector4f m_position;
        };
        static_assert(sizeof(EdgeInfo) == 0x30);

        EdgeInfo m_start;
        EdgeInfo m_goal;
        hkUint32 m_faceKey;
        const hkaiNavMesh::Face* m_face;
        const hkInt32* m_faceData;
    };
    static_assert(sizeof(NavMeshQuery) == 0x80);

    // Real nested class name from the existing DefaultAstarEdgeFilter symbol.
    // F86EF4..F86F08 constructs exactly this 0x20-byte callback context, with
    // flags 0x52 and a pointer to InputBase's eight-byte agent traversal info.
    struct NavMeshIsEnabledCallbackContext {
        const hkaiStreamingCollection* m_collection;
        const hkaiAgentTraversalInfo* m_agentInfo;
        const NavMeshQuery* m_query;
        hkUint8 m_flags;
    };
    static_assert(sizeof(NavMeshIsEnabledCallbackContext) == 0x20);

    struct NavVolumeIsEnabledCallbackContext;

    // The hook's signature is unknown; only its position is recovered.
    virtual void m5();
    virtual bool isEnabledMaybe(const NavMeshIsEnabledCallbackContext& context) const = 0;
    // Shared base default 0x7101530de4 returns true; game filters inherit it.
    virtual bool isEnabledMaybe(const NavVolumeIsEnabledCallbackContext& context) const;

private:
    // Reflected enum "type" has byte storage at +0xc; its values are unknown.
    hkUint8 m_type;
    hkUint8 _d[3];
};
static_assert(sizeof(hkaiAstarEdgeFilter) == 0x10);
