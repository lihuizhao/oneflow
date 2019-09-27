#include "oneflow/core/kernel/foreign_watch_kernel.h"
#include "oneflow/core/common/buffer_manager.h"
#include "oneflow/core/common/protobuf.h"
#include "oneflow/core/register/ofblob.h"
#include "oneflow/core/job/foreign_watcher.h"

namespace oneflow {

void ForeignWatchKernel::ForwardDataContent(
    const KernelCtx& ctx, std::function<Blob*(const std::string&)> BnInOp2Blob) const {
  OfBlob of_blob(ctx.device_ctx, BnInOp2Blob("in"));
  Global<ForeignWatcher>::Get()->Call(op_conf().foreign_watch_conf().handler_uuid(),
                                      reinterpret_cast<int64_t>(&of_blob));
}

REGISTER_KERNEL(OperatorConf::kForeignWatchConf, ForeignWatchKernel);

}  // namespace oneflow
