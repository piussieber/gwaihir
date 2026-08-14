# Copyright 2025 ETH Zurich and University of Bologna.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
#
# Pius Sieber <pisieber@student.ethz.ch>

APP              := bfs_cheshire
$(APP)_BUILD_DIR ?= $(GW_CHS_SW_DIR)/apps/$(APP)/build
$(APP)_DATA_CFG  := $(GW_CHS_SW_DIR)/apps/$(APP)/data/params.json
SRC_DIR          := $(GW_CHS_SW_DIR)/apps/$(APP)/src
SRCS             := $(SRC_DIR)/main.c
$(APP)_INCDIRS   := $(GW_CHS_SW_DIR)/apps/$(APP)/data

include $(SN_ROOT)/sw/kernels/datagen.mk
include $(SN_ROOT)/sw/kernels/common.mk
