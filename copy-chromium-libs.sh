#!/bin/sh -e


git clone --depth=1 https://github.com/chromium/chromium -b 0f9c87a64f094d5ad3315de4e8c7d3ff22fe8abc # as of 2020-01-20

mkdir -p third_party
cp -r chromium/third_party/rnnoise third_party
cp -r chromium/third_party/pffft third_party
