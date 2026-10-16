#include <Havok/Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>

// NON_MATCHING: the inlined removeReference retry loop places the store-exclusive block first
// (same as hkpKeyframedRigidMotion's destructor); everything else matches. The thunks and D0 share it.
hkpWorldViewerBase::~hkpWorldViewerBase() {
    if (m_context) {
        m_context->removeWorldListener(this);
        m_context->removeReference();
        m_context = nullptr;
    }
}
