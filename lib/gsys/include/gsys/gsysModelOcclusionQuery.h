#pragma once

#include <cull/aglOcclusionQuery.h>

namespace gsys {

// A model's occlusion query, stored at Model +0xe0 and deleted by Model's destructor 0x7100bf6bdc
// through destroy. The deleting destructor sits in the agl::cull::OcclusionQuery D0 slot
// (vtable +0x20), so the class is an OcclusionQuery with no virtuals of its own.
class ModelOcclusionQuery : public agl::cull::OcclusionQuery {
public:
    // 0x7100c07d38: null-tests and calls the deleting destructor.
    static void destroy(ModelOcclusionQuery* query);
};

}  // namespace gsys
