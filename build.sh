#!/bin/bash

OPENCV_BUILD_DIR="/Users/taichi.muraki/opencv-wasm-build/opencv-3.4.14"

docker run \
  --rm \
  -v $OPENCV_BUILD_DIR:/src \
  -v $(pwd):/code \
  -v $(pwd)/build:/build \
  -w /build \
  -u $(id -u):$(id -g) \
  emscripten/emsdk:2.0.18 \
  bash -c "emcmake cmake -DOpenCV_DIR=/src/build_wasm_no_bulk_memory /code; emmake make"
