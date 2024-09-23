// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef IREE_COMPILER_PLUGINS_INPUT_TORCH_INPUTCONVERSION_PASSES_H_
#define IREE_COMPILER_PLUGINS_INPUT_TORCH_INPUTCONVERSION_PASSES_H_

#include "mlir/IR/BuiltinOps.h"
#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "torch-mlir/Dialect/TorchConversion/Transforms/Passes.h"

namespace mlir::iree_compiler::TorchInput {

struct TorchToIREELoweringPipelineOptions
    : public PassPipelineOptions<TorchToIREELoweringPipelineOptions>, mlir::torch::Torch::TorchLoweringPipelineOptions {
  Option<bool> strictSymbolicShapes{
      *this, "strict-symbolic-shapes",
      llvm::cl::desc("Use strict symbolic shapes."), llvm::cl::init(true)};
};

// Creates a pipeline that lowers from the torch backend contract to IREE.
// This is based on the torch-backend-to-linalg-on-tensors-backend-pipeline
// pipeline in torch-mlir but includes IREE specific lowerings.
void createTorchToIREEPipeline(
    OpPassManager &pm, const TorchToIREELoweringPipelineOptions &options);

//===----------------------------------------------------------------------===//
// Register all Passes
//===----------------------------------------------------------------------===//

#define GEN_PASS_DECL
#include "compiler/plugins/input/Torch/InputConversion/Passes.h.inc" // IWYU pragma: keep

void registerTMTensorConversionPasses();

} // namespace mlir::iree_compiler::TorchInput

#endif // IREE_COMPILER_PLUGINS_INPUT_TORCH_INPUTCONVERSION_PASSES_H_
