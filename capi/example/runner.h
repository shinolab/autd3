// File: runner.h
// Project: example
// Created Date: 16/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 06/06/2022
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#pragma once

#pragma warning(push)
#pragma warning(disable : 6011 6386)

#include <stdlib.h>

#ifndef M_PI
#define M_PI (3.141592653589793238462643383279502884L)
#endif

#include "autd3_c_api.h"
#include "examples/bessel.h"
#include "examples/check.h"
#include "examples/focus.h"
#include "examples/gain_stm.h"
#include "examples/group.h"
#include "examples/plane.h"
#include "examples/point_stm.h"
#ifdef BUILD_GAIN_HOLO
#include "examples/holo.h"
#endif
#ifdef BUILD_MODULATION_AUDIO_FILE
#include "examples/mod_audio_file.h"
#endif

#define DEBUG_AUTD_CAPI

#ifdef DEBUG_AUTD_CAPI
#include "examples/api_debug.h"
#endif

typedef void (*TestFunction)(void*);

typedef struct {
  const char* name;
  TestFunction func;
} Test;

int run(void* autd) {
  int32_t example_size = 6;
#ifdef BUILD_GAIN_HOLO
  example_size++;
#endif
#ifdef BUILD_MODULATION_AUDIO_FILE
  example_size++;
#endif
#ifdef DEBUG_AUTD_CAPI
  example_size++;
#endif
  if (AUTDNumDevices(autd) == 2) example_size++;

  Test* examples = (Test*)malloc(example_size * sizeof(Test));

  int idx = 0;
  examples[idx].name = "Single Focus";
  examples[idx++].func = focus;
  examples[idx].name = "Bessel";
  examples[idx++].func = bessel;
#ifdef BUILD_GAIN_HOLO
  examples[idx].name = "Holo";
  examples[idx++].func = holo;
#endif
#ifdef BUILD_MODULATION_AUDIO_FILE
  examples[idx].name = "Modulation from audio file";
  examples[idx++].func = mod_audio_file;
#endif
  examples[idx].name = "PointSTM";
  examples[idx++].func = point_stm;
  examples[idx].name = "GainSTM";
  examples[idx++].func = gain_stm;
  if (AUTDNumDevices(autd) == 2) {
    examples[idx].name = "Grouped";
    examples[idx++].func = group;
  }
  examples[idx].name = "Plane";
  examples[idx++].func = plane;
  examples[idx].name = "Check";
  examples[idx++].func = check;
#ifdef DEBUG_AUTD_CAPI
  examples[idx].name = "API Debug";
  examples[idx++].func = api_debug;
#endif

  AUTDClear(autd);
  AUTDSynchronize(autd);

  printf("========= Firmware infomations ==========\n");
  void* firm_info_list = NULL;
  const int32_t firm_info_list_size = AUTDGetFirmwareInfoListPointer(autd, &firm_info_list);
  for (int32_t i = 0; i < firm_info_list_size; i++) {
    char info[256];
    AUTDGetFirmwareInfo(firm_info_list, i, info);
    printf("[%d]: %s\n", i, info);
  }
  AUTDFreeFirmwareInfoListPointer(firm_info_list);
  printf("=========================================\n");

  while (1) {
    for (int32_t i = 0; i < example_size; i++) {
      printf("[%d]: %s\n", i, examples[i].name);
    }
    printf("[Others]: finish.\n");

    printf("Choose number: ");
    int32_t i;
    if (!scanf("%d", &i)) {
      break;
    }
    (void)getchar();
    if (i >= example_size) {
      break;
    }

    examples[i].func(autd);

    printf("press any key to finish...");
    (void)getchar();

    printf("Finish.\n");
    AUTDStop(autd);
  }

  AUTDClear(autd);
  AUTDClose(autd);

  AUTDFreeController(autd);

  free(examples);

  return 0;
}

#pragma warning(pop)
