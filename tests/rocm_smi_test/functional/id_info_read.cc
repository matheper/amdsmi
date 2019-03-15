/*
 * =============================================================================
 * The University of Illinois/NCSA
 * Open Source License (NCSA)
 *
 * Copyright (c) 2019, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Developed by:
 *
 *                 AMD Research and AMD ROC Software Development
 *
 *                 Advanced Micro Devices, Inc.
 *
 *                 www.amd.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal with the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimers.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimers in
 *    the documentation and/or other materials provided with the distribution.
 *  - Neither the names of <Name of Development Group, Name of Institution>,
 *    nor the names of its contributors may be used to endorse or promote
 *    products derived from this Software without specific prior written
 *    permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS WITH THE SOFTWARE.
 *
 */

#include <stdint.h>
#include <stddef.h>

#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "rocm_smi/rocm_smi.h"
#include "rocm_smi_test/functional/id_info_read.h"
#include "rocm_smi_test/test_common.h"

TestIdInfoRead::TestIdInfoRead() : TestBase() {
  set_title("RSMI ID Info Read Test");
  set_description("This test verifies that ID information such as the "
             "device, subsystem and vendor IDs can be read properly.");
}

TestIdInfoRead::~TestIdInfoRead(void) {
}

void TestIdInfoRead::SetUp(void) {
  TestBase::SetUp();

  return;
}

void TestIdInfoRead::DisplayTestInfo(void) {
  TestBase::DisplayTestInfo();
}

void TestIdInfoRead::DisplayResults(void) const {
  TestBase::DisplayResults();
  return;
}

void TestIdInfoRead::Close() {
  // This will close handles opened within rsmitst utility calls and call
  // rsmi_shut_down(), so it should be done after other hsa cleanup
  TestBase::Close();
}

static const uint32_t kBufferLen = 80;

void TestIdInfoRead::Run(void) {
  rsmi_status_t err;
  uint16_t id;
  uint64_t val_ui64;

  char buffer[kBufferLen];

  TestBase::Run();

  for (uint32_t i = 0; i < num_monitor_devs(); ++i) {
    IF_VERB(STANDARD) {
      std::cout << "\t**Device index: " << id << std::endl;
    }

    // Get the device ID, name, vendor ID and vendor name for the device
    err = rsmi_dev_id_get(i, &id);
    if (err != RSMI_STATUS_SUCCESS) {
        CHK_ERR_ASRT(err)
    } else {
      IF_VERB(STANDARD) {
        std::cout << "\t**Device ID: 0x" << std::hex << id << std::endl;
      }
    }
    err = rsmi_dev_name_get(i, buffer, kBufferLen);
    if (err == RSMI_STATUS_NOT_FOUND) {
      std::cout << "\t**Device Marketing name not found on this system." <<
                                                                    std::endl;
    } else if (err != RSMI_STATUS_SUCCESS) {
        CHK_ERR_ASRT(err)
    } else {
      IF_VERB(STANDARD) {
        std::cout << "\t**Device Marketing name: " << buffer << std::endl;
      }
    }
    err = rsmi_dev_vendor_id_get(i, &id);
    if (err != RSMI_STATUS_SUCCESS) {
        CHK_ERR_ASRT(err)
    } else {
      IF_VERB(STANDARD) {
        std::cout << "\t**Vendor ID: 0x" << std::hex << id << std::endl;
      }
    }
    err = rsmi_dev_vendor_name_get(i, buffer, kBufferLen);
    if (err == RSMI_STATUS_NOT_FOUND) {
      std::cout << "\t**Device Vendor name string not found on this system." <<
                                                                     std::endl;
    } else if (err != RSMI_STATUS_SUCCESS) {
        CHK_ERR_ASRT(err)
    } else {
      IF_VERB(STANDARD) {
        std::cout << "\t**Device Vendor name: " << buffer << std::endl;
      }
    }

    // Get the device ID, name, vendor ID and vendor name for the sub-device
    err = rsmi_dev_subsystem_id_get(i, &id);
    if (err != RSMI_STATUS_SUCCESS) {
        CHK_ERR_ASRT(err)
    } else {
      IF_VERB(STANDARD) {
        std::cout << "\t**Subsystem ID: 0x" << std::hex << id << std::endl;
      }
    }
    err = rsmi_dev_subsystem_name_get(i, buffer, kBufferLen);
    if (err == RSMI_STATUS_NOT_FOUND) {
      std::cout << "\t**Subsystem name string not found on this system." <<
                                                                    std::endl;
    } else if (err != RSMI_STATUS_SUCCESS) {
        CHK_ERR_ASRT(err)
    } else {
      IF_VERB(STANDARD) {
        std::cout << "\t**Subsystem name: " << buffer << std::endl;
      }
    }
    err = rsmi_dev_subsystem_vendor_id_get(i, &id);
    if (err != RSMI_STATUS_SUCCESS) {
        CHK_ERR_ASRT(err)
    } else {
      IF_VERB(STANDARD) {
        std::cout << "\t**Sub-system Vendor ID: 0x" << std::hex <<
                                                              id << std::endl;
      }
    }
    err = rsmi_dev_vendor_name_get(i, buffer, kBufferLen);
    if (err == RSMI_STATUS_NOT_FOUND) {
      std::cout <<
           "\t**Subsystem Vendor name string not found on this system." <<
                                                                    std::endl;
    } else if (err != RSMI_STATUS_SUCCESS) {
        CHK_ERR_ASRT(err)
    } else {
      IF_VERB(STANDARD) {
        std::cout << "\t**Subsystem Vendor name: " << buffer << std::endl;
      }
    }

    err = rsmi_dev_pci_id_get(i, &val_ui64);
    CHK_ERR_ASRT(err)
    IF_VERB(STANDARD) {
      std::cout << "\t**PCI ID (BDFID): 0x" << std::hex << val_ui64;
      std::cout << " (" << std::dec << val_ui64 << ")" << std::endl;
    }
  }
}
