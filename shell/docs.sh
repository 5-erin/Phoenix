#!/bin/bash

build/Debug/Phoenix --apidump --tool scripts/ci/docs.luau --headless $@
