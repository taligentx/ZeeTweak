// DISPLAY WARNING: Type casts are NOT being printed

void Reset_Handler(void)

{
  undefined **ppuVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  ppuVar1 = &__Vectors;
  puVar2 = &DAT_20000000;
  iVar4 = 0x100;
  if (true) {
    do {
      *puVar2 = *ppuVar1;
      ppuVar1 = ppuVar1 + 1;
      puVar2 = puVar2 + 1;
      iVar4 = iVar4 + -4;
    } while (iVar4 != 0);
  }
  puVar2 = &__erodata;
  puVar3 = &stderr;
  iVar4 = 0x28c;
  if (true) {
    do {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
      iVar4 = iVar4 + -4;
    } while (iVar4 != 0);
  }
  puVar2 = &__bss_start__;
  iVar4 = 0x308ec;
  if (true) {
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
      iVar4 = iVar4 + -4;
    } while (iVar4 != 0);
  }
  SystemInit();
  board_init();
  main();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}




void __exit(int __status)

{
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}




void InterruptHandler(void)

{
  undefined4 *puVar1;
  undefined4 in_r13;
  undefined4 *puVar2;
  code *unaff_retaddr;
  code *pcVar3;
  
  do {
    *(register0x00000038 + -4) = in_r13;
    puVar2 = &DAT_20001544;
    g_trap_sp = register0x00000038;
    for (puVar1 = 0x0; puVar1 < 0x31; puVar1 = puVar1 + 1) {
      *puVar2 = *puVar1;
      puVar2 = puVar2 + 1;
    }
    DAT_2000157c = g_trap_sp;
    DAT_20001584 = g_trap_sp + -4;
    in_r13 = *DAT_20001584;
    pcVar3 = InterruptHandler;
    DAT_20001578 = in_r13;
    DAT_20001580 = unaff_retaddr;
    DAT_20001588 = DAT_20001584;
    trap_c(&DAT_20001544);
    register0x00000038 = &DAT_20001544;
    unaff_retaddr = pcVar3;
  } while( true );
}




void InterruptHandler(void)

{
  undefined4 *puVar1;
  undefined4 in_r13;
  undefined4 *puVar2;
  code *pcVar3;
  code *unaff_retaddr;
  
  do {
    *(register0x00000038 + -4) = in_r13;
    puVar2 = &DAT_20001544;
    g_trap_sp = register0x00000038;
    for (puVar1 = 0x0; puVar1 < 0x31; puVar1 = puVar1 + 1) {
      *puVar2 = *puVar1;
      puVar2 = puVar2 + 1;
    }
    DAT_2000157c = g_trap_sp;
    DAT_20001584 = g_trap_sp + -4;
    in_r13 = *DAT_20001584;
    pcVar3 = InterruptHandler;
    DAT_20001578 = in_r13;
    DAT_20001580 = unaff_retaddr;
    DAT_20001588 = DAT_20001584;
    trap_c(&DAT_20001544);
    register0x00000038 = &DAT_20001544;
    unaff_retaddr = pcVar3;
  } while( true );
}




void cpu_yield(void)

{
  system_VIC_TSPEND = 1;
  return;
}




StackType_t vPortStartTask(void)

{
  uint uVar1;
  StackType_t SVar2;
  StackType_t *pSVar3;
  StackType_t *pSVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  
  pSVar3 = pxCurrentTCB->pxTopOfStack;
  SVar2 = pSVar3[0x2f];
  pSVar4 = pSVar3;
  for (puVar6 = 0x0; puVar6 < 0x35; puVar6 = puVar6 + 1) {
    *puVar6 = *pSVar3;
    pSVar3 = pSVar3 + 1;
  }
  puVar5 = pSVar4 + 0x3c;
  puVar6 = pSVar4 + 0x3c;
  for (uVar1 = 0; uVar1 < 0x3d; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x40) = *puVar6;
    puVar6 = puVar6 + 1;
  }
  puVar6 = puVar5 + 0x40;
  for (uVar1 = 0; uVar1 < 0x3d; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x400) = *puVar6;
    puVar6 = puVar6 + 1;
  }
  return SVar2;
}




StackType_t tspend_handler(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  StackType_t SVar2;
  StackType_t *pSVar3;
  StackType_t *pSVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  StackType_t local_c4 [14];
  undefined4 local_88 [16];
  undefined4 local_48 [16];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  pSVar3 = local_c4;
  for (puVar6 = 0x0; puVar6 < 0x35; puVar6 = puVar6 + 1) {
    *pSVar3 = *puVar6;
    pSVar3 = pSVar3 + 1;
  }
  puVar6 = local_88;
  for (uVar1 = 0; uVar1 < 0x3d; uVar1 = uVar1 + 4) {
    *puVar6 = *(uVar1 + 0x40);
    puVar6 = puVar6 + 1;
  }
  puVar6 = local_48;
  for (uVar1 = 0; uVar1 < 0x3d; uVar1 = uVar1 + 4) {
    *puVar6 = *(uVar1 + 0x43c);
    puVar6 = puVar6 + 1;
  }
  pxCurrentTCB->pxTopOfStack = local_c4;
  uStack_8 = param_2;
  uStack_4 = param_2;
  vTaskSwitchContext();
  pSVar3 = pxCurrentTCB->pxTopOfStack;
  SVar2 = pSVar3[0x2f];
  pSVar4 = pSVar3;
  for (puVar6 = 0x0; puVar6 < 0x35; puVar6 = puVar6 + 1) {
    *puVar6 = *pSVar3;
    pSVar3 = pSVar3 + 1;
  }
  puVar5 = pSVar4 + 0x3c;
  puVar6 = pSVar4 + 0x3c;
  for (uVar1 = 0; uVar1 < 0x3d; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x40) = *puVar6;
    puVar6 = puVar6 + 1;
  }
  puVar6 = puVar5 + 0x40;
  for (uVar1 = 0; uVar1 < 0x3d; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x400) = *puVar6;
    puVar6 = puVar6 + 1;
  }
  return SVar2;
}




double * sin(double *__return_storage_ptr__,double __x)

{
  double *pdVar1;
  uint uVar2;
  uint in_r1;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  uStack_14 = 0;
  uStack_10 = 0;
  uStack_c = 0;
  uStack_8 = 0;
  if (0x3fe921fb < (in_r1 & 0x3fffffff)) {
    if (false) {
      uVar2 = __ieee754_rem_pio2(__return_storage_ptr__,in_r1,&uStack_14);
      uVar2 = uVar2 & 3;
      if (uVar2 == 1) {
        pdVar1 = __kernel_cos(uStack_14,uStack_10,uStack_c,uStack_8);
      }
      else if (uVar2 == 2) {
        pdVar1 = __kernel_sin(uStack_14,uStack_10,uStack_c,uStack_8,1);
      }
      else if (uVar2 == 0) {
        pdVar1 = __kernel_sin(uStack_14,uStack_10,uStack_c,uStack_8,1);
      }
      else {
        pdVar1 = __kernel_cos(uStack_14,uStack_10,uStack_c,uStack_8);
      }
    }
    else {
      pdVar1 = __subdf3(__return_storage_ptr__,in_r1,__return_storage_ptr__);
    }
    return pdVar1;
  }
  pdVar1 = __kernel_sin(__return_storage_ptr__,in_r1,0,0,0);
  return pdVar1;
}




double * sqrt(double *__return_storage_ptr__,double __x)

{
  int iVar1;
  double *pdVar2;
  uint in_r1;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  
  if (true) {
    __muldf3(__return_storage_ptr__,in_r1,__return_storage_ptr__);
    pdVar2 = __adddf3();
    return pdVar2;
  }
  if (in_r1 < 1) {
    if ((in_r1 & 0x3fffffff) == 0 && __return_storage_ptr__ == 0x0) {
      return __return_storage_ptr__;
    }
    if (in_r1 != 0) {
      __subdf3(__return_storage_ptr__,in_r1,__return_storage_ptr__);
      pdVar2 = __divdf3();
      return pdVar2;
    }
    iVar9 = 0;
    do {
      in_r1 = __return_storage_ptr__ >> 0xb;
      iVar9 = iVar9 + -0x15;
      __return_storage_ptr__ = __return_storage_ptr__ << 0x15;
    } while (in_r1 == 0);
    if (true) goto LAB_08010850;
    uVar8 = 0;
    uVar11 = 0x20;
    uVar5 = 0xffffffff;
  }
  else {
    iVar9 = in_r1 >> 0x14;
    if (iVar9 != 0) goto LAB_08010742;
    iVar9 = 0;
LAB_08010850:
    uVar8 = 0;
    do {
      uVar5 = uVar8;
      in_r1 = in_r1 * 2;
      uVar8 = uVar5 + 1;
    } while (true);
    uVar11 = 0x20 - uVar8;
  }
  iVar9 = iVar9 - uVar5;
  in_r1 = __return_storage_ptr__ >> (uVar11 & 0x3f) | in_r1;
  __return_storage_ptr__ = __return_storage_ptr__ << (uVar8 & 0x3f);
LAB_08010742:
  uVar8 = in_r1 & 0x7ffff | 0x100000;
  if ((iVar9 - 0x3ffU & 1) != 0) {
    uVar8 = uVar8 * 2 - (__return_storage_ptr__ >> 0x1f);
    __return_storage_ptr__ = __return_storage_ptr__ * 2;
  }
  iVar3 = uVar8 * 2 - (__return_storage_ptr__ >> 0x1f);
  iVar9 = __return_storage_ptr__ * 2;
  uVar8 = 0x16;
  do {
    uVar5 = uVar8;
    bVar7 = false;
    iVar6 = 0;
    uVar8 = uVar5 - 1;
    iVar3 = iVar3 * 2 - (iVar9 >> 0x1f);
    iVar9 = iVar9 * 2;
  } while (uVar8 != 0);
  iVar1 = 0x20;
  do {
    if (iVar6 < iVar3) {
      iVar10 = iVar6;
      if ((false) && (true)) {
        iVar10 = iVar6 + 1;
      }
LAB_080107be:
      iVar4 = iVar3 - iVar6;
      iVar6 = iVar10;
      if (false) {
        iVar4 = iVar4 + -1;
      }
    }
    else {
      iVar4 = iVar3;
      if ((iVar3 == iVar6) && (true)) {
        if ((false) && (true)) {
          iVar10 = iVar6 + 1;
          goto LAB_080107be;
        }
        iVar4 = 0;
        iVar6 = iVar3;
      }
    }
    iVar3 = iVar4 * 2 - (iVar9 >> 0x1f);
    iVar1 = iVar1 + -1;
    iVar9 = iVar9 * 2;
    if (iVar1 == 0) {
      if (iVar3 == 0 && iVar9 == 0) {
        pdVar2 = 0x0;
      }
      else if (false) {
        bVar7 = true;
        pdVar2 = 0x0;
      }
      else {
        pdVar2 = uVar5 >> 1;
      }
      if (bVar7) {
        pdVar2 = pdVar2 | 0x80000000;
      }
      return pdVar2;
    }
  } while( true );
}




undefined4 __kernel_poly(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  puVar2 = param_1 + param_2 * 8;
  uVar4 = *puVar2;
  if (param_2 != 0) {
    iVar3 = param_2 * 8 + -8 + param_1;
    uVar5 = puVar2[1];
    do {
      uVar1 = param_4;
      __muldf3(param_3,param_4,uVar4,uVar5);
      iVar3 = iVar3 + -8;
      uVar4 = __adddf3();
      uVar5 = uVar1;
    } while (iVar3 != param_1 + -8);
  }
  return uVar4;
}




undefined4 __kernel_sin(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  
  if ((false) && (iVar1 = __fixdfsi(param_1), iVar1 == 0)) {
    return param_1;
  }
  uVar6 = param_2;
  uVar2 = __muldf3(param_1,param_2,param_1,param_2);
  uVar7 = param_2;
  uVar3 = __muldf3(param_1,param_2,uVar2,uVar6);
  puVar9 = &DAT_20000118;
  uVar5 = DAT_20000124;
  uVar4 = DAT_20000120;
  do {
    uVar8 = uVar6;
    __muldf3(uVar2,uVar6,uVar4,uVar5);
    puVar9 = puVar9 + -2;
    uVar4 = __adddf3();
    uVar5 = uVar8;
  } while (puVar9 != 0x200000f8);
  if (param_5 != 0) {
    uVar5 = __muldf3(param_3,param_4,0,0);
    uVar6 = uVar7;
    uVar4 = __muldf3(uVar3,uVar7,uVar4,uVar8);
    __subdf3(uVar5,param_4,uVar4,uVar6);
    __muldf3();
    uVar6 = __subdf3();
    uVar5 = __muldf3(uVar3,uVar7,0x55555554,0x3fc55555);
    uVar6 = __adddf3(uVar6,param_4,uVar5,uVar7);
    uVar6 = __subdf3(param_1,param_2,uVar6,param_4);
    return uVar6;
  }
  __muldf3(uVar2,uVar6,uVar4,uVar8);
  __subdf3();
  __muldf3();
  uVar6 = __adddf3();
  return uVar6;
}




void __kernel_cos(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  
  uVar8 = param_2 & 0x7fffffff;
  if ((false) && (iVar1 = __fixdfsi(), iVar1 == 0)) {
    return;
  }
  uVar5 = param_2;
  uVar2 = __muldf3(param_1,param_2,param_1,param_2);
  puVar9 = &DAT_20000148;
  uVar3 = DAT_20000150;
  uVar7 = DAT_20000154;
  do {
    uVar6 = uVar5;
    __muldf3(uVar2,uVar5,uVar3,uVar7);
    puVar9 = puVar9 + -2;
    uVar3 = __adddf3();
    uVar7 = uVar6;
  } while (puVar9 != &DAT_20000120);
  uVar7 = uVar5;
  __muldf3(uVar2,uVar5,uVar3,uVar6);
  uVar3 = __muldf3();
  uVar4 = __muldf3(param_1,param_2,param_3,param_4);
  __subdf3(uVar3,uVar7,uVar4,param_2);
  __muldf3(uVar2,uVar5,0,0);
  uVar3 = __subdf3();
  if (0x3fd33332 < uVar8) {
    if (uVar8 == 0) {
      uVar4 = 0;
      uVar2 = __subdf3(0,0,0,0);
    }
    else {
      uVar2 = 0;
      uVar4 = 0;
    }
    uVar3 = __subdf3(uVar3,uVar5,0,0);
    __subdf3(uVar2,uVar4,uVar3,uVar5);
    return;
  }
  __subdf3(0,0,uVar3,uVar5);
  return;
}




double * _rem(double *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  double *pdVar1;
  int iVar2;
  undefined4 uVar3;
  double *pdVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  undefined4 unaff_r7;
  
  pdVar1 = fmod(param_1,CONCAT44(unaff_r5,unaff_r4),CONCAT44(unaff_r7,unaff_r6));
  iVar2 = __gtdf2();
  if (0 < iVar2) {
    uVar6 = param_4;
    uVar3 = __muldf3(param_3,param_4,0,0);
    iVar2 = __gtdf2(pdVar1,param_2,uVar3,uVar6);
    if (0 < iVar2) {
      pdVar1 = __subdf3(pdVar1,param_2,param_3,param_4);
    }
  }
  iVar2 = __ltdf2(pdVar1,param_2,0,0);
  if (iVar2 < 0) {
    uVar6 = param_2;
    pdVar4 = fabs(pdVar1,CONCAT44(unaff_r5,unaff_r4));
    uVar3 = param_4;
    uVar5 = __muldf3(param_3,param_4,0,0);
    iVar2 = __gtdf2(pdVar4,uVar6,uVar5,uVar3);
    if (0 < iVar2) {
      pdVar1 = __adddf3(pdVar1,param_2,param_3,param_4);
      return pdVar1;
    }
  }
  return pdVar1;
}




int __ieee754_rem_pio2(double *param_1,uint param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  double *pdVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined4 in_stack_ffffffd0;
  undefined4 in_stack_ffffffd4;
  
  uVar11 = param_2 & 0x3fffffff;
  if (uVar11 < 0x3fe921fc) {
    *param_3 = param_1;
    param_3[1] = param_2;
    param_3[2] = 0;
    param_3[3] = 0;
    return 0;
  }
  if (uVar11 < 0x4002d97c) {
    uVar10 = 0x3ff921fb;
    if (param_2 < 1) {
      uVar10 = 0xbff921fb;
    }
    uVar1 = 0;
    iVar2 = 1;
    if (param_2 < 1) {
      iVar2 = -1;
    }
    uVar10 = __subdf3(param_1,param_2,0,uVar10);
    if (uVar11 == 0x3ff921fb) {
      uVar8 = uVar1;
      uVar9 = __muldf3(0,0,0,0x3dd0b461);
      uVar10 = __subdf3(uVar10,param_2,uVar9,uVar8);
      uVar8 = 0x2e037073;
      uVar9 = 0x3ba3198a;
    }
    else {
      uVar8 = 0x1a626331;
      uVar9 = 0x3dd0b461;
    }
    uVar8 = __muldf3(0,0,uVar8,uVar9);
    uVar11 = param_2;
    uVar1 = __subdf3(uVar10,param_2,uVar8,uVar1);
    *param_3 = uVar1;
    param_3[1] = uVar11;
    __subdf3(uVar10,param_2,uVar1,uVar11);
    uVar10 = __subdf3();
    param_3[2] = uVar10;
    param_3[3] = param_2;
  }
  else {
    if (0x413921fb < uVar11) {
      if (true) {
        uVar11 = ((uVar11 >> 0x14) - 0x469) / 0x36;
        param_1 = __muldf3(param_1,param_2,*(&DAT_0802e7a8 + uVar11 * 8),*(&DAT_0802e7a8 + (uVar11 * 2 + 1) * 4));
      }
      uVar11 = param_2;
      uVar10 = __subdf3(param_1,param_2,0);
      uVar4 = param_2;
      uVar1 = __muldf3(0,param_2,0,0xbe1dbfb1);
      uVar5 = uVar11;
      uVar8 = __muldf3(uVar10,uVar11,0,0x3fdb4445);
      uVar1 = __adddf3(uVar1,uVar4,uVar8,uVar5);
      uVar8 = __muldf3(0,param_2,0,0x3fdb4445);
      uVar5 = uVar4;
      uVar8 = __adddf3(uVar1,uVar4,uVar8,param_2);
      uVar6 = uVar5;
      uVar9 = __subdf3();
      __subdf3(uVar1,uVar4,uVar9,uVar6,param_2);
      __muldf3(uVar10,uVar11,0,0xbe1dbfb1);
      uVar10 = __adddf3();
      _rem(uVar8,uVar5,0xa740a5a7,0x40056a4a);
      __divdf3();
      __muldf3();
      __adddf3();
      iVar2 = __fixdfsi();
      uVar1 = _rem(uVar8,uVar5,0xa740a5a7,0x3fe56a4a);
      __adddf3(uVar10,uVar11,uVar1,uVar5);
      _rem();
      uVar10 = __divdf3();
      *param_3 = uVar10;
      param_3[1] = uVar11;
      return iVar2 / 2;
    }
    uVar4 = param_2;
    pdVar3 = fabs(param_1,CONCAT44(in_stack_ffffffd4,in_stack_ffffffd0));
    uVar5 = uVar4;
    __muldf3();
    __adddf3();
    iVar2 = __fixdfsi();
    uVar10 = __floatsidf();
    uVar6 = uVar5;
    uVar1 = __muldf3();
    uVar1 = __subdf3(pdVar3,uVar4,uVar1,uVar6);
    uVar7 = uVar5;
    uVar8 = __muldf3(uVar10,uVar5,0x1a626331,0x3dd0b461);
    uVar6 = uVar4;
    uVar8 = __subdf3(uVar1,uVar4,uVar8,uVar5);
    uVar5 = uVar4;
    if (0x10 < (uVar11 >> 0x14) - ((uVar6 & 0x3fffffff) >> 0x14)) {
      uVar11 = uVar7;
      uVar8 = __muldf3(uVar10,uVar7,0,0x3dd0b461);
      uVar8 = __subdf3(uVar1,uVar4,uVar8,uVar11);
      uVar11 = uVar7;
      uVar1 = __muldf3(uVar10,uVar7,0,0x3ba3198a);
      uVar5 = uVar4;
      uVar1 = __subdf3(uVar8,uVar4,uVar1,uVar7);
      __subdf3(uVar8,uVar4,uVar1,uVar5);
      __subdf3();
      __muldf3(uVar10,uVar11,0x252049c1,0x397b839a,uVar10,uVar11,uVar7);
      uVar10 = __subdf3();
      uVar6 = uVar5;
      uVar8 = __subdf3(uVar1,uVar5,uVar10,uVar11);
    }
    *param_3 = uVar8;
    param_3[1] = uVar6;
    __subdf3(uVar1,uVar5,uVar8,uVar6);
    uVar10 = __subdf3();
    param_3[2] = uVar10;
    param_3[3] = uVar5;
    if (param_2 < 0) {
      param_3[1] = uVar6;
      param_3[3] = uVar5;
      iVar2 = -iVar2;
    }
  }
  return iVar2;
}




float sqrtf(float __x)

{
  float fVar1;
  
  fVar1 = __ieee754_sqrtf();
  return fVar1;
}




void __ieee754_sqrtf(void)

{
  int iVar1;
  uint in_vr0;
  
  if (true) {
    return;
  }
  if (((in_vr0 & 0x3fffffff) != 0) && (-1 < in_vr0)) {
    if (((in_vr0 & 0x3fffffff) < 0x800000) && (true)) {
      do {
      } while (true);
    }
    iVar1 = 0x19;
    do {
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    return;
  }
  return;
}




double * fmod(double *__return_storage_ptr__,double __x,double __y)

{
  double *pdVar1;
  uint in_r1;
  uint uVar2;
  double *in_r2;
  uint in_r3;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  uVar4 = in_r3 & 0x3fffffff;
  if (((in_r2 == 0x0 && uVar4 == 0) || (uVar5 = in_r1 & 0x3fffffff, -1 < uVar5)) || ((-in_r2 | in_r2) < 0 || uVar4 != 0)) {
    __muldf3(__return_storage_ptr__);
    pdVar1 = __divdf3();
    return pdVar1;
  }
  if (uVar5 <= uVar4) {
    if (uVar5 < uVar4) {
      return __return_storage_ptr__;
    }
    if (__return_storage_ptr__ < in_r2) {
      return __return_storage_ptr__;
    }
    if (__return_storage_ptr__ == in_r2) {
      return 0x0;
    }
  }
  if (uVar5 < 0x100000) {
    if (uVar5 == 0) {
      iVar7 = -0x413;
      for (pdVar1 = __return_storage_ptr__; 0 < pdVar1; pdVar1 = pdVar1 * 2) {
        iVar7 = iVar7 + -1;
      }
    }
    else {
      iVar3 = uVar5 << 0xb;
      iVar7 = -0x3fe;
      do {
        iVar3 = iVar3 * 2;
        iVar7 = iVar7 + -1;
      } while (0 < iVar3);
    }
  }
  else {
    iVar7 = (uVar5 >> 0x14) + -0x3ff;
  }
  if (uVar4 < 0x100000) {
    if (uVar4 == 0) {
      iVar3 = -0x413;
      for (pdVar1 = in_r2; 0 < pdVar1; pdVar1 = pdVar1 * 2) {
        iVar3 = iVar3 + -1;
      }
    }
    else {
      iVar6 = uVar4 << 0xb;
      iVar3 = -0x3fe;
      do {
        iVar6 = iVar6 * 2;
        iVar3 = iVar3 + -1;
      } while (0 < iVar6);
    }
  }
  else {
    iVar3 = (uVar4 >> 0x14) + -0x3ff;
  }
  if (iVar7 < -0x3fe) {
    uVar2 = -iVar7 - 0x3fe;
    if (uVar2 < 0x20) {
      uVar5 = __return_storage_ptr__ >> (0x20 - uVar2 & 0x3f) | uVar5 << (uVar2 & 0x3f);
      __return_storage_ptr__ = __return_storage_ptr__ << (uVar2 & 0x3f);
    }
    else {
      uVar5 = __return_storage_ptr__ << (-iVar7 - 0x41eU & 0x3f);
      __return_storage_ptr__ = 0x0;
    }
  }
  else {
    uVar5 = in_r1 & 0x7ffff | 0x100000;
  }
  if (iVar3 < -0x3fe) {
    uVar2 = -iVar3 - 0x3fe;
    if (uVar2 < 0x20) {
      uVar4 = uVar4 << (uVar2 & 0x3f) | in_r2 >> (0x20 - uVar2 & 0x3f);
      in_r2 = in_r2 << (uVar2 & 0x3f);
    }
    else {
      uVar4 = in_r2 << (-iVar3 - 0x41eU & 0x3f);
      in_r2 = 0x0;
    }
  }
  else {
    uVar4 = in_r3 & 0x7ffff | 0x100000;
  }
  iVar7 = iVar7 - iVar3;
  while( true ) {
    uVar2 = uVar5 - uVar4;
    if (__return_storage_ptr__ < in_r2) {
      uVar2 = uVar2 - 1;
    }
    if (iVar7 == 0) break;
    if (uVar2 < 0) {
      uVar5 = uVar5 * 2 - (__return_storage_ptr__ >> 0x1f);
    }
    else {
      __return_storage_ptr__ = __return_storage_ptr__ - in_r2;
      if (uVar2 == 0 && __return_storage_ptr__ == 0x0) {
        return 0x0;
      }
      uVar5 = uVar2 * 2 - (__return_storage_ptr__ >> 0x1f);
    }
    __return_storage_ptr__ = __return_storage_ptr__ * 2;
    iVar7 = iVar7 + -1;
  }
  if (-1 < uVar2) {
    __return_storage_ptr__ = __return_storage_ptr__ - in_r2;
    uVar5 = uVar2;
  }
  if (uVar5 == 0 && __return_storage_ptr__ == 0x0) {
    return 0x0;
  }
  for (; uVar5 < 0x100000; uVar5 = uVar5 * 2 - iVar7) {
    iVar7 = __return_storage_ptr__ >> 0x1f;
    __return_storage_ptr__ = __return_storage_ptr__ * 2;
    iVar3 = iVar3 + -1;
  }
  if (-0x3ff < iVar3) {
    return __return_storage_ptr__;
  }
  uVar4 = -iVar3 - 0x3fe;
  if (uVar4 < 0x15) {
    pdVar1 = uVar5 << (0x20 - uVar4 & 0x3f) | __return_storage_ptr__ >> (uVar4 & 0x3f);
  }
  else if (uVar4 < 0x20) {
    pdVar1 = uVar5 << (0x20 - uVar4 & 0x3f) | __return_storage_ptr__ >> (uVar4 & 0x3f);
  }
  else {
    pdVar1 = uVar5 >> (-iVar3 - 0x41eU & 0x3f);
  }
  return pdVar1;
}




double * fabs(double *__return_storage_ptr__,double __x)

{
  return __return_storage_ptr__;
}




undefined4 __fixunsdfsi(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = __gedf2(param_1,param_2,0,0);
  if (iVar1 < 0) {
    uVar2 = __fixdfsi(param_1,param_2);
    return uVar2;
  }
  __subdf3(param_1,param_2,0,0);
  uVar2 = __fixdfsi();
  return uVar2;
}




int __fixsfdi(void)

{
  int iVar1;
  float in_vr0;
  
  if (0.0 <= in_vr0) {
    iVar1 = __fixunssfdi();
    return iVar1;
  }
  iVar1 = __fixunssfdi();
  return -iVar1;
}




int __fixdfdi(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = __ltdf2();
  if (-1 < iVar1) {
    iVar1 = __fixunsdfdi(param_1,param_2);
    return iVar1;
  }
  iVar1 = __fixunsdfdi(param_1,param_2);
  return -iVar1;
}




undefined4 __fixunssfdi(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = __extendsfdf2();
  uVar3 = param_2;
  __muldf3();
  __fixunsdfsi();
  __floatunsidf();
  uVar2 = __muldf3();
  __subdf3(uVar1,param_2,uVar2,uVar3);
  uVar3 = __fixunsdfsi();
  return uVar3;
}




undefined4 __fixunsdfdi(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = param_2;
  __muldf3(param_1,param_2,0,0);
  __fixunsdfsi();
  __floatunsidf();
  uVar1 = __muldf3();
  __subdf3(param_1,param_2,uVar1,uVar2);
  uVar2 = __fixunsdfsi();
  return uVar2;
}




void __floatdisf(uint param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = param_2 + 0x1fffff + (param_1 != 0);
  if (((0x3fffff < uVar1) || ((uVar1 == 0x3fffff && (param_1 == 0)))) && ((param_1 & 0x7ff) != 0)) {
    param_1 = param_1 & 0xfffff800 | 0x800;
  }
  __floatsidf(param_2);
  __muldf3();
  __floatunsidf(param_1);
  __adddf3();
  __truncdfsf2();
  return;
}




void __floatundidf(undefined4 param_1,undefined4 param_2)

{
  __floatsidf(param_2);
  __muldf3();
  __floatunsidf(param_1);
  __adddf3();
  return;
}




uint __divdi3(uint param_1,uint param_2,uint param_3,uint param_4)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  
  if (param_2 < 0) {
    bVar1 = param_1 == 0;
    param_1 = -param_1;
    param_2 = -(bVar1 ^ 1) - param_2;
    uVar12 = 0xffffffff;
  }
  else {
    uVar12 = 0;
  }
  if (param_4 < 0) {
    uVar12 = ~uVar12;
    bVar1 = param_3 == 0;
    param_3 = -param_3;
    param_4 = -(bVar1 ^ 1) - param_4;
  }
  if (param_4 == 0) {
    if (param_2 < param_3) {
      if (param_3 < 0x10000) {
        iVar5 = 0;
        if (0xff < param_3) {
          iVar5 = 8;
        }
      }
      else {
        iVar5 = 0x18;
        if (param_3 < 0x1000000) {
          iVar5 = 0x10;
        }
      }
      uVar3 = param_3 >> iVar5;
      uVar2 = 0x20 - (iVar5 + (&DAT_0802e85c)[uVar3]);
      if (uVar2 != 0) {
        param_3 = param_3 << (uVar2 & 0x3f);
        param_2 = param_1 >> (iVar5 + (&DAT_0802e85c)[uVar3] & 0x3f) | param_2 << (uVar2 & 0x3f);
        param_1 = param_1 << (uVar2 & 0x3f);
      }
      uVar9 = param_3 >> 0x10;
      uVar3 = param_2 / uVar9;
      uVar6 = (param_3 & 0x7fff) * uVar3;
      uVar4 = param_1 >> 0x10 | (param_2 - uVar3 * uVar9) * 0x10000;
      uVar2 = uVar3;
      if (uVar4 < uVar6) {
        uVar4 = uVar4 + param_3;
        uVar2 = uVar3 - 1;
        if ((param_3 <= uVar4) && (uVar4 < uVar6)) {
          uVar2 = uVar3 - 2;
          uVar4 = uVar4 + param_3;
        }
      }
      uVar7 = (uVar4 - uVar6) / uVar9;
      uVar3 = uVar7 * (param_3 & 0x7fff);
      uVar4 = param_1 & 0x7fff | ((uVar4 - uVar6) - uVar7 * uVar9) * 0x10000;
      uVar9 = uVar7;
      if (uVar4 < uVar3) {
        uVar4 = uVar4 + param_3;
        uVar9 = uVar7 - 1;
        if ((param_3 <= uVar4) && (uVar4 < uVar3)) {
          uVar9 = uVar7 - 2;
        }
      }
      uVar9 = uVar2 << 0x10 | uVar9;
    }
    else {
      if (param_3 == 0) {
        param_3 = 1 / 0;
      }
      if (param_3 < 0x10000) {
        iVar5 = 0;
        if (0xff < param_3) {
          iVar5 = 8;
        }
      }
      else {
        iVar5 = 0x18;
        if (param_3 < 0x1000000) {
          iVar5 = 0x10;
        }
      }
      uVar3 = iVar5 + (&DAT_0802e85c)[param_3 >> iVar5];
      uVar2 = 0x20 - uVar3;
      if (uVar2 == 0) {
        param_2 = param_2 - param_3;
        uVar9 = param_3 >> 0x10;
        uVar2 = param_3 & 0x7fff;
      }
      else {
        uVar4 = param_2 >> (uVar3 & 0x3f);
        param_3 = param_3 << (uVar2 & 0x3f);
        uVar7 = param_1 >> (uVar3 & 0x3f) | param_2 << (uVar2 & 0x3f);
        uVar9 = param_3 >> 0x10;
        uVar3 = uVar4 / uVar9;
        param_1 = param_1 << (uVar2 & 0x3f);
        uVar2 = param_3 & 0x7fff;
        uVar6 = uVar2 * uVar3;
        uVar3 = (uVar4 - uVar3 * uVar9) * 0x10000 | uVar7 >> 0x10;
        if (((uVar3 < uVar6) && (uVar3 = uVar3 + param_3, param_3 <= uVar3)) && (uVar3 < uVar6)) {
          uVar3 = uVar3 + param_3;
        }
        uVar4 = (uVar3 - uVar6) / uVar9;
        param_2 = ((uVar3 - uVar6) - uVar4 * uVar9) * 0x10000 | uVar7 & 0x7fff;
        uVar4 = uVar2 * uVar4;
        if (((param_2 < uVar4) && (param_2 = param_2 + param_3, param_3 <= param_2)) && (param_2 < uVar4)) {
          param_2 = param_2 + param_3;
        }
        param_2 = param_2 - uVar4;
      }
      uVar6 = param_2 / uVar9;
      uVar7 = uVar6 * uVar2;
      uVar4 = param_1 >> 0x10 | (param_2 - uVar6 * uVar9) * 0x10000;
      uVar3 = uVar6;
      if (uVar4 < uVar7) {
        uVar4 = uVar4 + param_3;
        uVar3 = uVar6 - 1;
        if ((param_3 <= uVar4) && (uVar4 < uVar7)) {
          uVar3 = uVar6 - 2;
          uVar4 = uVar4 + param_3;
        }
      }
      uVar6 = (uVar4 - uVar7) / uVar9;
      uVar4 = ((uVar4 - uVar7) - uVar6 * uVar9) * 0x10000 | param_1 & 0x7fff;
      uVar9 = uVar6;
      if (uVar4 < uVar6 * uVar2) {
        uVar4 = uVar4 + param_3;
        uVar9 = uVar6 - 1;
        if ((param_3 <= uVar4) && (uVar4 < uVar6 * uVar2)) {
          uVar9 = uVar6 - 2;
        }
      }
      uVar9 = uVar3 << 0x10 | uVar9;
    }
  }
  else if (param_2 < param_4) {
    uVar9 = 0;
  }
  else {
    if (param_4 < 0x10000) {
      iVar5 = (0xff < param_4) << 3;
    }
    else {
      iVar5 = 0x10;
      if (0xffffff < param_4) {
        iVar5 = 0x18;
      }
    }
    uVar3 = (&DAT_0802e85c)[param_4 >> iVar5] + iVar5;
    uVar2 = 0x20 - uVar3;
    if (uVar2 == 0) {
      if (param_4 < param_2) {
        uVar9 = 1;
      }
      else {
        uVar9 = param_3 <= param_1;
      }
    }
    else {
      uVar7 = param_4 << (uVar2 & 0x3f) | param_3 >> (uVar3 & 0x3f);
      uVar4 = param_2 >> (uVar3 & 0x3f);
      uVar11 = uVar7 >> 0x10;
      uVar6 = param_2 << (uVar2 & 0x3f) | param_1 >> (uVar3 & 0x3f);
      uVar9 = uVar4 / uVar11;
      uVar10 = (uVar7 & 0x7fff) * uVar9;
      uVar4 = uVar6 >> 0x10 | (uVar4 - uVar9 * uVar11) * 0x10000;
      param_3 = param_3 << (uVar2 & 0x3f);
      uVar3 = uVar9;
      if (uVar4 < uVar10) {
        uVar4 = uVar4 + uVar7;
        uVar3 = uVar9 - 1;
        if ((uVar7 <= uVar4) && (uVar4 < uVar10)) {
          uVar3 = uVar9 - 2;
          uVar4 = uVar4 + uVar7;
        }
      }
      uVar9 = (uVar4 - uVar10) / uVar11;
      uVar8 = uVar9 * (uVar7 & 0x7fff);
      uVar6 = uVar6 & 0x7fff | ((uVar4 - uVar10) - uVar9 * uVar11) * 0x10000;
      uVar4 = uVar9;
      if (uVar6 < uVar8) {
        uVar6 = uVar6 + uVar7;
        uVar4 = uVar9 - 1;
        if ((uVar7 <= uVar6) && (uVar6 < uVar8)) {
          uVar4 = uVar9 - 2;
          uVar6 = uVar6 + uVar7;
        }
      }
      uVar9 = uVar3 << 0x10 | uVar4;
      uVar3 = param_3 & 0x7fff;
      param_3 = param_3 >> 0x10;
      uVar7 = (uVar4 & 0x7fff) * uVar3;
      uVar4 = param_3 * (uVar4 & 0x7fff) + (uVar9 >> 0x10) * uVar3 + (uVar7 >> 0x10);
      uVar3 = param_3 * (uVar9 >> 0x10) + (uVar4 >> 0x10);
      if ((uVar6 - uVar8 < uVar3) || ((uVar6 - uVar8 == uVar3 && (param_1 << (uVar2 & 0x3f) < uVar4 * 0x10000 + (uVar7 & 0x7fff))))) {
        uVar9 = uVar9 - 1;
      }
    }
  }
  if (uVar12 != 0) {
    uVar9 = -uVar9;
  }
  return uVar9;
}




uint __moddi3(uint param_1,uint param_2,uint param_3,uint param_4)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  
  if (param_2 < 0) {
    bVar1 = param_1 == 0;
    param_1 = -param_1;
    param_2 = -(bVar1 ^ 1) - param_2;
    iVar14 = -1;
  }
  else {
    iVar14 = 0;
  }
  if (param_4 < 0) {
    bVar1 = param_3 == 0;
    param_3 = -param_3;
    param_4 = -(bVar1 ^ 1) - param_4;
  }
  if (param_4 == 0) {
    if (param_2 < param_3) {
      if (param_3 < 0x10000) {
        iVar7 = 0;
        if (0xff < param_3) {
          iVar7 = 8;
        }
      }
      else {
        iVar7 = 0x10;
        if (0xffffff < param_3) {
          iVar7 = 0x18;
        }
      }
      uVar4 = param_3 >> iVar7;
      uVar12 = 0x20 - (iVar7 + (&DAT_0802e85c)[uVar4]);
      if (uVar12 != 0) {
        param_3 = param_3 << (uVar12 & 0x3f);
        param_2 = param_1 >> (iVar7 + (&DAT_0802e85c)[uVar4] & 0x3f) | param_2 << (uVar12 & 0x3f);
        param_1 = param_1 << (uVar12 & 0x3f);
      }
      uVar2 = param_3 >> 0x10;
      uVar4 = param_3 & 0x7fff;
      uVar8 = uVar4 * (param_2 / uVar2);
      uVar5 = param_1 >> 0x10 | (param_2 - (param_2 / uVar2) * uVar2) * 0x10000;
      if (((uVar5 < uVar8) && (uVar5 = uVar5 + param_3, param_3 <= uVar5)) && (uVar5 < uVar8)) {
        uVar5 = uVar5 + param_3;
      }
      uVar3 = (uVar5 - uVar8) / uVar2;
      iVar7 = (uVar5 - uVar8) - uVar3 * uVar2;
    }
    else {
      if (param_3 == 0) {
        param_3 = 1 / 0;
      }
      if (param_3 < 0x10000) {
        iVar7 = 0;
        if (0xff < param_3) {
          iVar7 = 8;
        }
      }
      else {
        iVar7 = 0x10;
        if (0xffffff < param_3) {
          iVar7 = 0x18;
        }
      }
      uVar4 = iVar7 + (&DAT_0802e85c)[param_3 >> iVar7];
      uVar12 = 0x20 - uVar4;
      if (uVar12 == 0) {
        param_2 = param_2 - param_3;
        uVar8 = param_3 >> 0x10;
        uVar4 = param_3 & 0x7fff;
      }
      else {
        param_3 = param_3 << (uVar12 & 0x3f);
        uVar3 = param_2 >> (uVar4 & 0x3f);
        uVar8 = param_3 >> 0x10;
        uVar9 = param_1 >> (uVar4 & 0x3f) | param_2 << (uVar12 & 0x3f);
        uVar5 = uVar3 / uVar8;
        uVar4 = param_3 & 0x7fff;
        uVar2 = uVar4 * uVar5;
        uVar5 = (uVar3 - uVar5 * uVar8) * 0x10000 | uVar9 >> 0x10;
        param_1 = param_1 << (uVar12 & 0x3f);
        if (((uVar5 < uVar2) && (uVar5 = uVar5 + param_3, param_3 <= uVar5)) && (uVar5 < uVar2)) {
          uVar5 = uVar5 + param_3;
        }
        uVar3 = (uVar5 - uVar2) / uVar8;
        uVar6 = uVar4 * uVar3;
        param_2 = ((uVar5 - uVar2) - uVar3 * uVar8) * 0x10000 | uVar9 & 0x7fff;
        if (((param_2 < uVar6) && (param_2 = param_2 + param_3, param_3 <= param_2)) && (param_2 < uVar6)) {
          param_2 = param_2 + param_3;
        }
        param_2 = param_2 - uVar6;
      }
      uVar2 = (param_2 / uVar8) * uVar4;
      uVar5 = param_1 >> 0x10 | (param_2 - (param_2 / uVar8) * uVar8) * 0x10000;
      if (((uVar5 < uVar2) && (uVar5 = uVar5 + param_3, param_3 <= uVar5)) && (uVar5 < uVar2)) {
        uVar5 = uVar5 + param_3;
      }
      uVar3 = (uVar5 - uVar2) / uVar8;
      iVar7 = (uVar5 - uVar2) - uVar3 * uVar8;
    }
    uVar4 = uVar4 * uVar3;
    uVar5 = param_1 & 0x7fff | iVar7 << 0x10;
    if (((uVar5 < uVar4) && (uVar5 = uVar5 + param_3, param_3 <= uVar5)) && (uVar5 < uVar4)) {
      uVar5 = param_3 + uVar5;
    }
    param_1 = uVar5 - uVar4 >> (uVar12 & 0x3f);
    goto LAB_080118a4;
  }
  if (param_2 < param_4) goto LAB_080118a4;
  if (param_4 < 0x10000) {
    iVar7 = (0xff < param_4) << 3;
  }
  else {
    iVar7 = 0x10;
    if (0xffffff < param_4) {
      iVar7 = 0x18;
    }
  }
  uVar12 = (&DAT_0802e85c)[param_4 >> iVar7] + iVar7;
  uVar4 = 0x20 - uVar12;
  if (uVar4 == 0) {
    if ((param_4 < param_2) || (param_3 <= param_1)) {
      param_1 = param_1 - param_3;
    }
    goto LAB_080118a4;
  }
  uVar3 = param_4 << (uVar4 & 0x3f) | param_3 >> (uVar12 & 0x3f);
  uVar5 = param_2 >> (uVar12 & 0x3f);
  uVar6 = uVar3 >> 0x10;
  uVar8 = uVar5 / uVar6;
  uVar9 = param_1 >> (uVar12 & 0x3f) | param_2 << (uVar4 & 0x3f);
  uVar11 = (uVar3 & 0x7fff) * uVar8;
  uVar2 = uVar9 >> 0x10 | (uVar5 - uVar8 * uVar6) * 0x10000;
  param_3 = param_3 << (uVar4 & 0x3f);
  param_1 = param_1 << (uVar4 & 0x3f);
  uVar5 = uVar8;
  if (uVar2 < uVar11) {
    uVar2 = uVar2 + uVar3;
    uVar5 = uVar8 - 1;
    if ((uVar3 <= uVar2) && (uVar2 < uVar11)) {
      uVar5 = uVar8 - 2;
      uVar2 = uVar2 + uVar3;
    }
  }
  uVar13 = (uVar2 - uVar11) / uVar6;
  uVar10 = (uVar3 & 0x7fff) * uVar13;
  uVar8 = ((uVar2 - uVar11) - uVar13 * uVar6) * 0x10000 | uVar9 & 0x7fff;
  uVar2 = uVar13;
  if (uVar8 < uVar10) {
    uVar8 = uVar8 + uVar3;
    uVar2 = uVar13 - 1;
    if ((uVar3 <= uVar8) && (uVar8 < uVar10)) {
      uVar2 = uVar13 - 2;
      uVar8 = uVar8 + uVar3;
    }
  }
  uVar8 = uVar8 - uVar10;
  uVar9 = (uVar5 << 0x10 | uVar2) >> 0x10;
  uVar6 = (uVar2 & 0x7fff) * (param_3 & 0x7fff);
  uVar5 = (uVar6 >> 0x10) + (param_3 >> 0x10) * (uVar2 & 0x7fff) + uVar9 * (param_3 & 0x7fff);
  uVar2 = (param_3 >> 0x10) * uVar9 + (uVar5 >> 0x10);
  uVar5 = uVar5 * 0x10000 + (uVar6 & 0x7fff);
  if (uVar8 < uVar2) {
LAB_08011b0e:
    uVar9 = uVar5 - param_3;
    iVar7 = uVar8 - ((uVar2 - uVar3) - ~(uVar9 <= uVar5));
  }
  else {
    uVar9 = uVar5;
    if (uVar8 == uVar2) {
      if (param_1 < uVar5) goto LAB_08011b0e;
      iVar7 = 0;
    }
    else {
      iVar7 = uVar8 - uVar2;
    }
  }
  param_1 = iVar7 - ~(param_1 - uVar9 <= param_1) << (uVar12 & 0x3f) | param_1 - uVar9 >> (uVar4 & 0x3f);
LAB_080118a4:
  if (iVar14 != 0) {
    param_1 = -param_1;
  }
  return param_1;
}




uint __udivdi3(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  
  if (param_4 == 0) {
    if (param_2 < param_3) {
      if (param_3 < 0x10000) {
        iVar5 = 0;
        if (0xff < param_3) {
          iVar5 = 8;
        }
      }
      else {
        iVar5 = 0x18;
        if (param_3 < 0x1000000) {
          iVar5 = 0x10;
        }
      }
      uVar3 = param_3 >> iVar5;
      uVar4 = 0x20 - (iVar5 + (&DAT_0802e85c)[uVar3]);
      if (uVar4 != 0) {
        param_3 = param_3 << (uVar4 & 0x3f);
        param_2 = param_1 >> (iVar5 + (&DAT_0802e85c)[uVar3] & 0x3f) | param_2 << (uVar4 & 0x3f);
        param_1 = param_1 << (uVar4 & 0x3f);
      }
      uVar1 = param_3 >> 0x10;
      uVar2 = param_2 / uVar1;
      uVar4 = (param_3 & 0x7fff) * uVar2;
      uVar9 = param_1 >> 0x10 | (param_2 - uVar2 * uVar1) * 0x10000;
      uVar3 = uVar2;
      if (uVar9 < uVar4) {
        uVar9 = uVar9 + param_3;
        uVar3 = uVar2 - 1;
        if ((param_3 <= uVar9) && (uVar9 < uVar4)) {
          uVar3 = uVar2 - 2;
          uVar9 = uVar9 + param_3;
        }
      }
      uVar2 = (uVar9 - uVar4) / uVar1;
      uVar6 = uVar2 * (param_3 & 0x7fff);
      uVar1 = param_1 & 0x7fff | ((uVar9 - uVar4) - uVar2 * uVar1) * 0x10000;
      uVar4 = uVar2;
      if (uVar1 < uVar6) {
        uVar1 = uVar1 + param_3;
        uVar4 = uVar2 - 1;
        if ((param_3 <= uVar1) && (uVar1 < uVar6)) {
          uVar4 = uVar2 - 2;
        }
      }
      return uVar3 << 0x10 | uVar4;
    }
    if (param_3 == 0) {
      param_3 = 1 / 0;
    }
    if (param_3 < 0x10000) {
      iVar5 = 0;
      if (0xff < param_3) {
        iVar5 = 8;
      }
    }
    else {
      iVar5 = 0x18;
      if (param_3 < 0x1000000) {
        iVar5 = 0x10;
      }
    }
    uVar3 = iVar5 + (&DAT_0802e85c)[param_3 >> iVar5];
    uVar4 = 0x20 - uVar3;
    if (uVar4 == 0) {
      param_2 = param_2 - param_3;
      uVar7 = param_3 >> 0x10;
      uVar3 = param_3 & 0x7fff;
      uVar1 = param_1;
    }
    else {
      param_3 = param_3 << (uVar4 & 0x3f);
      uVar10 = param_2 >> (uVar3 & 0x3f);
      uVar1 = param_1 << (uVar4 & 0x3f);
      uVar7 = param_3 >> 0x10;
      uVar2 = uVar10 / uVar7;
      uVar6 = param_1 >> (uVar3 & 0x3f) | param_2 << (uVar4 & 0x3f);
      uVar3 = param_3 & 0x7fff;
      uVar9 = uVar3 * uVar2;
      uVar4 = uVar6 >> 0x10 | (uVar10 - uVar2 * uVar7) * 0x10000;
      if (((uVar4 < uVar9) && (uVar4 = uVar4 + param_3, param_3 <= uVar4)) && (uVar4 < uVar9)) {
        uVar4 = uVar4 + param_3;
      }
      uVar10 = (uVar4 - uVar9) / uVar7;
      uVar2 = uVar3 * uVar10;
      param_2 = ((uVar4 - uVar9) - uVar10 * uVar7) * 0x10000 | uVar6 & 0x7fff;
      if (((param_2 < uVar2) && (param_2 = param_2 + param_3, param_3 <= param_2)) && (param_2 < uVar2)) {
        param_2 = param_2 + param_3;
      }
      param_2 = param_2 - uVar2;
    }
    uVar6 = param_2 / uVar7;
    uVar2 = uVar6 * uVar3;
    uVar9 = uVar1 >> 0x10 | (param_2 - uVar6 * uVar7) * 0x10000;
    uVar4 = uVar6;
    if (uVar9 < uVar2) {
      uVar9 = uVar9 + param_3;
      uVar4 = uVar6 - 1;
      if ((param_3 <= uVar9) && (uVar9 < uVar2)) {
        uVar4 = uVar6 - 2;
        uVar9 = uVar9 + param_3;
      }
    }
    uVar6 = (uVar9 - uVar2) / uVar7;
    uVar2 = ((uVar9 - uVar2) - uVar6 * uVar7) * 0x10000 | uVar1 & 0x7fff;
    uVar1 = uVar6;
    if (uVar2 < uVar6 * uVar3) {
      uVar2 = uVar2 + param_3;
      uVar1 = uVar6 - 1;
      if ((param_3 <= uVar2) && (uVar2 < uVar6 * uVar3)) {
        uVar1 = uVar6 - 2;
      }
    }
    return uVar4 << 0x10 | uVar1;
  }
  if (param_2 < param_4) {
    return 0;
  }
  if (param_4 < 0x10000) {
    iVar5 = (0xff < param_4) << 3;
  }
  else {
    iVar5 = 0x10;
    if (0xffffff < param_4) {
      iVar5 = 0x18;
    }
  }
  uVar4 = (&DAT_0802e85c)[param_4 >> iVar5] + iVar5;
  uVar3 = 0x20 - uVar4;
  if (uVar3 == 0) {
    if (param_2 <= param_4) {
      return param_3 <= param_1;
    }
    return 1;
  }
  uVar6 = param_3 >> (uVar4 & 0x3f) | param_4 << (uVar3 & 0x3f);
  uVar9 = param_2 >> (uVar4 & 0x3f);
  uVar7 = uVar6 >> 0x10;
  uVar2 = uVar9 / uVar7;
  uVar1 = param_1 >> (uVar4 & 0x3f) | param_2 << (uVar3 & 0x3f);
  uVar10 = (uVar6 & 0x7fff) * uVar2;
  uVar9 = uVar1 >> 0x10 | (uVar9 - uVar2 * uVar7) * 0x10000;
  param_3 = param_3 << (uVar3 & 0x3f);
  uVar4 = uVar2;
  if (uVar9 < uVar10) {
    uVar9 = uVar9 + uVar6;
    uVar4 = uVar2 - 1;
    if ((uVar6 <= uVar9) && (uVar9 < uVar10)) {
      uVar4 = uVar2 - 2;
      uVar9 = uVar9 + uVar6;
    }
  }
  uVar2 = (uVar9 - uVar10) / uVar7;
  uVar8 = (uVar6 & 0x7fff) * uVar2;
  uVar9 = uVar1 & 0x7fff | ((uVar9 - uVar10) - uVar2 * uVar7) * 0x10000;
  uVar1 = uVar2;
  if (uVar9 < uVar8) {
    uVar9 = uVar9 + uVar6;
    uVar1 = uVar2 - 1;
    if ((uVar6 <= uVar9) && (uVar9 < uVar8)) {
      uVar1 = uVar2 - 2;
      uVar9 = uVar9 + uVar6;
    }
  }
  uVar2 = uVar4 << 0x10 | uVar1;
  uVar4 = param_3 & 0x7fff;
  param_3 = param_3 >> 0x10;
  uVar6 = (uVar1 & 0x7fff) * uVar4;
  uVar4 = (uVar6 >> 0x10) + param_3 * (uVar1 & 0x7fff) + (uVar2 >> 0x10) * uVar4;
  uVar1 = param_3 * (uVar2 >> 0x10) + (uVar4 >> 0x10);
  if ((uVar1 <= uVar9 - uVar8) && ((uVar9 - uVar8 != uVar1 || (uVar4 * 0x10000 + (uVar6 & 0x7fff) <= param_1 << (uVar3 & 0x3f))))) {
    return uVar2;
  }
  return uVar2 - 1;
}




uint __umoddi3(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  
  if (param_4 != 0) {
    if (param_2 < param_4) {
      return param_1;
    }
    if (param_4 < 0x10000) {
      iVar8 = (0xff < param_4) << 3;
    }
    else {
      iVar8 = 0x10;
      if (0xffffff < param_4) {
        iVar8 = 0x18;
      }
    }
    uVar2 = (&DAT_0802e85c)[param_4 >> iVar8] + iVar8;
    uVar6 = 0x20 - uVar2;
    if (uVar6 == 0) {
      if ((param_4 < param_2) || (param_3 <= param_1)) {
        param_1 = param_1 - param_3;
      }
      return param_1;
    }
    uVar4 = param_3 >> (uVar2 & 0x3f) | param_4 << (uVar6 & 0x3f);
    uVar1 = param_2 >> (uVar2 & 0x3f);
    uVar3 = param_1 >> (uVar2 & 0x3f) | param_2 << (uVar6 & 0x3f);
    uVar7 = uVar4 >> 0x10;
    uVar11 = uVar1 / uVar7;
    param_3 = param_3 << (uVar6 & 0x3f);
    uVar5 = (uVar4 & 0x7fff) * uVar11;
    uVar9 = uVar3 >> 0x10 | (uVar1 - uVar11 * uVar7) * 0x10000;
    param_1 = param_1 << (uVar6 & 0x3f);
    uVar1 = uVar11;
    if (uVar9 < uVar5) {
      uVar9 = uVar9 + uVar4;
      uVar1 = uVar11 - 1;
      if ((uVar4 <= uVar9) && (uVar9 < uVar5)) {
        uVar1 = uVar11 - 2;
        uVar9 = uVar9 + uVar4;
      }
    }
    uVar11 = (uVar9 - uVar5) / uVar7;
    uVar10 = uVar11 * (uVar4 & 0x7fff);
    uVar9 = uVar3 & 0x7fff | ((uVar9 - uVar5) - uVar11 * uVar7) * 0x10000;
    uVar3 = uVar11;
    if (uVar9 < uVar10) {
      uVar9 = uVar9 + uVar4;
      uVar3 = uVar11 - 1;
      if ((uVar4 <= uVar9) && (uVar9 < uVar10)) {
        uVar3 = uVar11 - 2;
        uVar9 = uVar9 + uVar4;
      }
    }
    uVar1 = (uVar1 << 0x10 | uVar3) >> 0x10;
    uVar9 = uVar9 - uVar10;
    uVar11 = (uVar3 & 0x7fff) * (param_3 & 0x7fff);
    uVar3 = (uVar11 >> 0x10) + (param_3 >> 0x10) * (uVar3 & 0x7fff) + uVar1 * (param_3 & 0x7fff);
    uVar1 = (uVar3 >> 0x10) + (param_3 >> 0x10) * uVar1;
    uVar3 = uVar3 * 0x10000 + (uVar11 & 0x7fff);
    if (uVar1 <= uVar9) {
      uVar11 = uVar3;
      if (uVar9 != uVar1) {
        iVar8 = uVar9 - uVar1;
        goto LAB_080120ea;
      }
      if (uVar3 <= param_1) {
        iVar8 = 0;
        goto LAB_080120ea;
      }
    }
    uVar11 = uVar3 - param_3;
    iVar8 = uVar9 - ((uVar1 - uVar4) - ~(uVar11 <= uVar3));
LAB_080120ea:
    return param_1 - uVar11 >> (uVar6 & 0x3f) | iVar8 - ~(param_1 - uVar11 <= param_1) << (uVar2 & 0x3f);
  }
  if (param_2 < param_3) {
    if (param_3 < 0x10000) {
      iVar8 = 0;
      if (0xff < param_3) {
        iVar8 = 8;
      }
    }
    else {
      iVar8 = 0x18;
      if (param_3 < 0x1000000) {
        iVar8 = 0x10;
      }
    }
    uVar2 = param_3 >> iVar8;
    uVar6 = 0x20 - (iVar8 + (&DAT_0802e85c)[uVar2]);
    if (uVar6 != 0) {
      param_3 = param_3 << (uVar6 & 0x3f);
      param_2 = param_1 >> (iVar8 + (&DAT_0802e85c)[uVar2] & 0x3f) | param_2 << (uVar6 & 0x3f);
      param_1 = param_1 << (uVar6 & 0x3f);
    }
    uVar9 = param_3 >> 0x10;
    uVar3 = (param_3 & 0x7fff) * (param_2 / uVar9);
    uVar1 = param_1 >> 0x10 | (param_2 - (param_2 / uVar9) * uVar9) * 0x10000;
    if (((uVar1 < uVar3) && (uVar1 = uVar1 + param_3, param_3 <= uVar1)) && (uVar1 < uVar3)) {
      uVar1 = uVar1 + param_3;
    }
    uVar4 = (uVar1 - uVar3) / uVar9;
    uVar2 = uVar4 * (param_3 & 0x7fff);
    uVar1 = param_1 & 0x7fff | ((uVar1 - uVar3) - uVar4 * uVar9) * 0x10000;
    if (uVar2 <= uVar1) {
      return uVar1 - uVar2 >> (uVar6 & 0x3f);
    }
  }
  else {
    if (param_3 == 0) {
      param_3 = 1 / 0;
    }
    if (param_3 < 0x10000) {
      iVar8 = 0;
      if (0xff < param_3) {
        iVar8 = 8;
      }
    }
    else {
      iVar8 = 0x18;
      if (param_3 < 0x1000000) {
        iVar8 = 0x10;
      }
    }
    uVar2 = iVar8 + (&DAT_0802e85c)[param_3 >> iVar8];
    uVar6 = 0x20 - uVar2;
    if (uVar6 == 0) {
      param_2 = param_2 - param_3;
      uVar9 = param_3 >> 0x10;
      uVar2 = param_3 & 0x7fff;
    }
    else {
      param_3 = param_3 << (uVar6 & 0x3f);
      uVar1 = param_2 >> (uVar2 & 0x3f);
      uVar9 = param_3 >> 0x10;
      uVar3 = param_2 << (uVar6 & 0x3f) | param_1 >> (uVar2 & 0x3f);
      uVar11 = uVar1 / uVar9;
      uVar2 = param_3 & 0x7fff;
      uVar4 = uVar2 * uVar11;
      uVar1 = uVar3 >> 0x10 | (uVar1 - uVar11 * uVar9) * 0x10000;
      param_1 = param_1 << (uVar6 & 0x3f);
      if (((uVar1 < uVar4) && (uVar1 = uVar1 + param_3, param_3 <= uVar1)) && (uVar1 < uVar4)) {
        uVar1 = uVar1 + param_3;
      }
      uVar11 = (uVar1 - uVar4) / uVar9;
      uVar5 = uVar2 * uVar11;
      param_2 = ((uVar1 - uVar4) - uVar11 * uVar9) * 0x10000 | uVar3 & 0x7fff;
      if (((param_2 < uVar5) && (param_2 = param_2 + param_3, param_3 <= param_2)) && (param_2 < uVar5)) {
        param_2 = param_2 + param_3;
      }
      param_2 = param_2 - uVar5;
    }
    uVar3 = (param_2 / uVar9) * uVar2;
    uVar1 = param_1 >> 0x10 | (param_2 - (param_2 / uVar9) * uVar9) * 0x10000;
    if (((uVar1 < uVar3) && (uVar1 = uVar1 + param_3, param_3 <= uVar1)) && (uVar1 < uVar3)) {
      uVar1 = uVar1 + param_3;
    }
    uVar4 = (uVar1 - uVar3) / uVar9;
    uVar2 = uVar2 * uVar4;
    uVar1 = ((uVar1 - uVar3) - uVar4 * uVar9) * 0x10000 | param_1 & 0x7fff;
    if (uVar2 <= uVar1) goto LAB_08012000;
  }
  uVar1 = uVar1 + param_3;
  if ((param_3 <= uVar1) && (uVar1 < uVar2)) {
    uVar1 = param_3 + uVar1;
  }
LAB_08012000:
  return uVar1 - uVar2 >> (uVar6 & 0x3f);
}




void __extendsfdf2(void)

{
  undefined1 auStack_18 [4];
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  uint uStack_8;
  
  __unpack_f(auStack_18,&uStack_14);
  __make_dp(uStack_14,uStack_10,uStack_c,uStack_8 << 0x1e,uStack_8 >> 2);
  return;
}




uint * _fpadd_parts(uint *param_1,uint *param_2,uint *param_3)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint local_2c;
  uint uStack_28;
  
  uVar2 = *param_1;
  if (uVar2 < 2) {
    return param_1;
  }
  uVar7 = *param_2;
  if (uVar7 < 2) {
    return param_2;
  }
  if (uVar2 == 4) {
    if (uVar7 != 4) {
      return param_1;
    }
    if (param_1[1] == param_2[1]) {
      return param_1;
    }
    return &__thenan_df;
  }
  if (uVar7 == 4) {
    return param_2;
  }
  if (uVar7 == 2) {
    if (uVar2 != 2) {
      return param_1;
    }
    *param_3 = 2;
    param_3[1] = param_1[1];
    param_3[2] = param_1[2];
    param_3[3] = param_1[3];
    uVar2 = param_2[1];
    param_3[4] = param_1[4];
    param_3[1] = param_1[1] & uVar2;
    return param_3;
  }
  if (uVar2 == 2) {
    return param_2;
  }
  uVar2 = param_1[2];
  uVar8 = param_2[2];
  uVar10 = uVar2 - uVar8;
  uVar7 = uVar10;
  if (uVar10 < 0) {
    uVar7 = ~uVar10 + 1;
  }
  local_2c = param_1[3];
  uVar3 = param_1[4];
  uVar5 = param_2[3];
  uVar6 = param_2[4];
  uVar4 = uVar6;
  uStack_28 = uVar3;
  if (uVar7 < 0x40) {
    if (uVar10 < 1) {
      if (uVar10 != 0) {
        uVar10 = uVar7 - 0x20;
        bVar1 = (uVar10 & 0x80000000) == 0;
        uVar8 = local_2c >> (uVar7 & 0x3f) | (uVar3 << 1) << (0x1f - uVar7 & 0x3f);
        if (bVar1) {
          uVar8 = uVar3 >> (uVar10 & 0x3f);
        }
        uStack_28 = uVar3 >> (uVar7 & 0x3f);
        iVar9 = 1 << (uVar7 & 0x3f);
        uVar6 = 0;
        if (bVar1) {
          iVar9 = 0;
          uStack_28 = 0;
          uVar6 = 1 << (uVar10 & 0x3f);
        }
        uVar2 = uVar2 + uVar7;
        if (iVar9 == 0) {
          uVar6 = uVar6 - 1;
        }
        local_2c = uVar8 | ((local_2c & iVar9 - 1U) != 0 || (uVar3 & uVar6) != 0);
      }
      goto LAB_08012234;
    }
    uVar10 = uVar7 - 0x20;
    bVar1 = (uVar10 & 0x80000000) == 0;
    uVar8 = uVar5 >> (uVar7 & 0x3f) | (uVar6 << 1) << (0x1f - uVar7 & 0x3f);
    if (bVar1) {
      uVar8 = uVar6 >> (uVar10 & 0x3f);
    }
    iVar9 = 1 << (uVar7 & 0x3f);
    uVar4 = uVar6 >> (uVar7 & 0x3f);
    uVar7 = 0;
    if (bVar1) {
      iVar9 = 0;
      uVar4 = 0;
      uVar7 = 1 << (uVar10 & 0x3f);
    }
    if (iVar9 == 0) {
      uVar7 = uVar7 - 1;
    }
    uVar10 = param_1[1];
    uVar5 = ((iVar9 - 1U & uVar5) != 0 || (uVar7 & uVar6) != 0) | uVar8;
    if (uVar10 == param_2[1]) goto LAB_0801233e;
  }
  else {
    if (uVar8 < uVar2) {
      uVar5 = 0;
      uVar4 = 0;
    }
    else {
      local_2c = 0;
      uStack_28 = 0;
      uVar2 = uVar8;
    }
LAB_08012234:
    uVar10 = param_1[1];
    if (uVar10 == param_2[1]) {
LAB_0801233e:
      uVar7 = local_2c + uVar5;
      uVar8 = uStack_28 + uVar4 + CARRY4(local_2c,uVar5);
      param_3[1] = uVar10;
      param_3[2] = uVar2;
      param_3[3] = uVar7;
      param_3[4] = uVar8;
      goto LAB_08012358;
    }
  }
  if (uVar10 == 0) {
    uVar7 = local_2c - uVar5;
    uVar8 = (uStack_28 - uVar4) - (uVar5 <= local_2c ^ 1);
  }
  else {
    uVar7 = uVar5 - local_2c;
    uVar8 = (uVar4 - uStack_28) - (local_2c <= uVar5 ^ 1);
  }
  if (uVar8 < 0) {
    bVar1 = uVar7 == 0;
    uVar7 = -uVar7;
    uVar8 = -(bVar1 ^ 1) - uVar8;
    param_3[1] = 1;
    param_3[2] = uVar2;
    param_3[3] = uVar7;
    param_3[4] = uVar8;
  }
  else {
    param_3[1] = 0;
    param_3[2] = uVar2;
    param_3[3] = uVar7;
    param_3[4] = uVar8;
  }
  uVar2 = uVar8;
  if (uVar7 == 0) {
    uVar2 = uVar8 - 1;
  }
  if ((uVar2 < 0x10000000) && ((uVar2 != 0xfffffff || (uVar7 != 0)))) {
    uVar2 = param_3[2] - 1;
    do {
      uVar4 = uVar2;
      bVar1 = CARRY4(uVar7,uVar7);
      uVar7 = uVar7 * 2;
      uVar8 = uVar8 * 2 + bVar1;
      uVar10 = (uVar8 - 1) + (uVar7 != 0);
      uVar2 = uVar4 - 1;
      if (0xfffffff < uVar10) break;
    } while ((uVar10 != 0xfffffff) || (uVar7 != 0));
    param_3[3] = uVar7;
    param_3[4] = uVar8;
    param_3[2] = uVar4;
    *param_3 = 3;
    return param_3;
  }
LAB_08012358:
  *param_3 = 3;
  if (0x1fffffff < uVar8) {
    param_3[3] = uVar7 >> 1 | uVar8 << 0x1f | uVar7 & 1;
    param_3[4] = uVar8 >> 1;
    param_3[2] = param_3[2] + 1;
  }
  return param_3;
}




void __adddf3(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined1 auStack_48 [20];
  undefined1 auStack_34 [20];
  undefined1 auStack_20 [20];
  
  local_58 = param_1;
  uStack_54 = param_2;
  uStack_50 = param_3;
  uStack_4c = param_4;
  __unpack_d(&local_58,auStack_48);
  __unpack_d(&uStack_50,auStack_34);
  _fpadd_parts(auStack_48,auStack_34,auStack_20);
  __pack_d();
  return;
}




void __subdf3(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined1 auStack_48 [20];
  undefined1 auStack_34 [4];
  uint uStack_30;
  undefined1 auStack_20 [20];
  
  local_58 = param_1;
  uStack_54 = param_2;
  uStack_50 = param_3;
  uStack_4c = param_4;
  __unpack_d(&local_58,auStack_48);
  __unpack_d(&uStack_50,auStack_34);
  uStack_30 = uStack_30 ^ 1;
  _fpadd_parts(auStack_48,auStack_34,auStack_20);
  __pack_d();
  return;
}




void __muldf3(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  uint uStack_60;
  uint uStack_5c;
  int iStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  uint uStack_4c;
  uint uStack_48;
  int iStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  uint uStack_34;
  int iStack_30;
  uint uStack_2c;
  uint uStack_28;
  
  uStack_70 = param_1;
  uStack_6c = param_2;
  uStack_68 = param_3;
  uStack_64 = param_4;
  __unpack_d(&uStack_70,&uStack_60);
  __unpack_d(&uStack_68,&uStack_4c);
  if (uStack_60 < 2) {
LAB_08012674:
    uStack_5c = uStack_5c != uStack_48;
    __pack_d(&uStack_60);
    return;
  }
  if (uStack_4c < 2) {
LAB_0801265a:
    uStack_48 = uStack_5c != uStack_48;
    __pack_d(&uStack_4c);
    return;
  }
  if (uStack_60 == 4) {
    if (uStack_4c != 2) goto LAB_08012674;
  }
  else {
    if (uStack_4c != 4) {
      if (uStack_60 == 2) goto LAB_08012674;
      if (uStack_4c == 2) goto LAB_0801265a;
      uVar7 = 0;
      uVar2 = __muldi3(uStack_40,0,uStack_54);
      uVar8 = 0;
      uVar3 = __muldi3(uStack_3c,0,uStack_54);
      iVar9 = 0;
      uVar4 = __muldi3(uStack_50,0,uStack_3c);
      iVar10 = 0;
      uVar5 = __muldi3(uStack_50,0,uStack_40);
      uVar11 = iVar10 + uVar8 + CARRY4(uVar5,uVar3);
      if ((uVar11 < uVar8) || ((uVar8 == uVar11 && (uVar5 + uVar3 < uVar3)))) {
        iVar10 = 1;
      }
      else {
        iVar10 = 0;
      }
      uVar8 = 0;
      uVar3 = uVar5 + uVar3 + uVar7;
      if (((uVar3 < uVar7) || ((uVar7 == uVar3 && (false)))) && (uVar8 = 1, false)) {
        iVar10 = iVar10 + 1;
      }
      uStack_2c = uVar8 + uVar4 + uVar11;
      uStack_28 = iVar10 + iVar9 + CARRY4(uVar4,uVar11) + CARRY4(uVar8,uVar4 + uVar11);
      iStack_58 = iStack_58 + iStack_44;
      iStack_30 = iStack_58 + 4;
      uStack_34 = uStack_5c != uStack_48;
      if (uStack_28 < 0x20000000) {
        if (uStack_28 < 0x10000000) {
          iVar9 = iStack_58 + 3;
          do {
            iStack_30 = iVar9;
            bVar1 = CARRY4(uStack_2c,uStack_2c);
            uStack_2c = uStack_2c * 2;
            uStack_28 = uStack_28 * 2 + bVar1;
            if (uVar3 < 0) {
              uStack_2c = uStack_2c | 1;
            }
            bVar1 = CARRY4(uVar2,uVar2);
            uVar2 = uVar2 * 2;
            uVar3 = uVar3 * 2 + bVar1;
            iVar9 = iStack_30 + -1;
          } while (uStack_28 < 0x10000000);
        }
      }
      else {
        iVar9 = iStack_58 + 5;
        uVar4 = uStack_28;
        do {
          iStack_30 = iVar9;
          if ((uStack_2c & 1) != 0) {
            uVar2 = uVar2 >> 1 | uVar3 << 0x1f;
            uVar3 = uVar3 >> 1;
          }
          uStack_28 = uVar4 >> 1;
          uStack_2c = uVar4 << 0x1f | uStack_2c >> 1;
          iVar9 = iStack_30 + 1;
          uVar4 = uStack_28;
        } while (0x1fffffff < uStack_28);
      }
      if ((((uStack_2c & 0xff) == 0x80) && ((uStack_2c & 0x100) == 0)) && (uVar2 != 0 || uVar3 != 0)) {
        uStack_28 = uStack_28 + (0xffffff7f < uStack_2c);
        uStack_2c = uStack_2c + 0x80 & 0xffffff00;
      }
      uStack_38 = 3;
      puVar6 = &uStack_38;
      goto LAB_0801264e;
    }
    if (uStack_60 != 2) goto LAB_0801265a;
  }
  puVar6 = &__thenan_df;
LAB_0801264e:
  __pack_d(puVar6);
  return;
}




void __divdf3(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  uint *puVar2;
  int iVar3;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  uint uStack_44;
  uint uStack_40;
  int iStack_3c;
  uint uStack_38;
  uint uStack_34;
  uint local_30;
  uint uStack_2c;
  int iStack_28;
  uint uStack_24;
  uint uStack_20;
  
  local_54 = param_1;
  uStack_50 = param_2;
  uStack_4c = param_3;
  uStack_48 = param_4;
  __unpack_d(&local_54,&uStack_44);
  __unpack_d(&uStack_4c,&local_30);
  if (1 < uStack_44) {
    if (local_30 < 2) {
      puVar2 = &local_30;
      goto LAB_080127d0;
    }
    uStack_40 = uStack_40 ^ uStack_2c;
    if ((uStack_44 == 4) || (uStack_44 == 2)) {
      if (uStack_44 == local_30) {
        puVar2 = &__thenan_df;
        goto LAB_080127d0;
      }
    }
    else {
      if (local_30 == 4) {
        uStack_38 = 0;
        uStack_34 = 0;
        iStack_3c = 0;
        puVar2 = &uStack_44;
        goto LAB_080127d0;
      }
      if (local_30 == 2) {
        uStack_44 = 4;
        puVar2 = &uStack_44;
        goto LAB_080127d0;
      }
      iStack_3c = iStack_3c - iStack_28;
      if ((uStack_34 < uStack_20) || ((uStack_20 == uStack_34 && (uStack_38 < uStack_24)))) {
        iStack_3c = iStack_3c + -1;
        bVar1 = CARRY4(uStack_38,uStack_38);
        uStack_38 = uStack_38 * 2;
        uStack_34 = uStack_34 * 2 + bVar1;
      }
      iVar3 = 0x3d;
      do {
        if ((uStack_20 <= uStack_34) && ((uStack_20 != uStack_34 || (uStack_24 <= uStack_38)))) {
          bVar1 = uStack_24 <= uStack_38;
          uStack_38 = uStack_38 - uStack_24;
          uStack_34 = (uStack_34 - uStack_20) - (bVar1 ^ 1);
        }
        iVar3 = iVar3 + -1;
        bVar1 = CARRY4(uStack_38,uStack_38);
        uStack_38 = uStack_38 * 2;
        uStack_34 = uStack_34 * 2 + bVar1;
      } while (iVar3 != 0);
      uStack_34 = 0;
      uStack_38 = 0;
    }
  }
  puVar2 = &uStack_44;
LAB_080127d0:
  __pack_d(puVar2);
  return;
}




void __nedf2(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  uint auStack_34 [5];
  uint auStack_20 [5];
  
  local_44 = param_1;
  uStack_40 = param_2;
  uStack_3c = param_3;
  uStack_38 = param_4;
  __unpack_d(&local_44,auStack_34);
  __unpack_d(&uStack_3c,auStack_20);
  if ((1 < auStack_34[0]) && (1 < auStack_20[0])) {
    __fpcmp_parts_d(auStack_34,auStack_20);
  }
  return;
}




undefined4 __gtdf2(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  uint auStack_34 [5];
  uint auStack_20 [5];
  
  local_44 = param_1;
  uStack_40 = param_2;
  uStack_3c = param_3;
  uStack_38 = param_4;
  __unpack_d(&local_44,auStack_34);
  __unpack_d(&uStack_3c,auStack_20);
  if ((1 < auStack_34[0]) && (1 < auStack_20[0])) {
    uVar1 = __fpcmp_parts_d(auStack_34,auStack_20);
    return uVar1;
  }
  return 0xffffffff;
}




undefined4 __gedf2(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  uint auStack_34 [5];
  uint auStack_20 [5];
  
  local_44 = param_1;
  uStack_40 = param_2;
  uStack_3c = param_3;
  uStack_38 = param_4;
  __unpack_d(&local_44,auStack_34);
  __unpack_d(&uStack_3c,auStack_20);
  if ((1 < auStack_34[0]) && (1 < auStack_20[0])) {
    uVar1 = __fpcmp_parts_d(auStack_34,auStack_20);
    return uVar1;
  }
  return 0xffffffff;
}




void __ltdf2(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  uint auStack_34 [5];
  uint auStack_20 [5];
  
  local_44 = param_1;
  uStack_40 = param_2;
  uStack_3c = param_3;
  uStack_38 = param_4;
  __unpack_d(&local_44,auStack_34);
  __unpack_d(&uStack_3c,auStack_20);
  if ((1 < auStack_34[0]) && (1 < auStack_20[0])) {
    __fpcmp_parts_d(auStack_34,auStack_20);
  }
  return;
}




undefined4 __floatsidf(uint param_1)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_18;
  uint uStack_14;
  int iStack_10;
  int iStack_c;
  uint uStack_8;
  
  local_18 = 3;
  uStack_14 = param_1 >> 0x1f;
  if (param_1 == 0) {
    local_18 = 2;
  }
  else {
    if (param_1 < 0) {
      if (param_1 == 0) {
        return 0;
      }
      param_1 = -param_1;
    }
    uVar3 = LZCOUNT(param_1) + 0x1d;
    uVar4 = LZCOUNT(param_1) - 3;
    bVar1 = (uVar4 & 0x80000000) == 0;
    uStack_8 = (param_1 >> 1) >> (0x1f - uVar3 & 0x3f);
    if (bVar1) {
      uStack_8 = param_1 << (uVar4 & 0x3f);
    }
    iStack_c = param_1 << (uVar3 & 0x3f);
    if (bVar1) {
      iStack_c = 0;
    }
    iStack_10 = 0x3c - uVar3;
  }
  uVar2 = __pack_d(&local_18);
  return uVar2;
}




uint __fixdfsi(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 local_20;
  undefined4 uStack_1c;
  uint uStack_18;
  int iStack_14;
  int iStack_10;
  uint uStack_c;
  uint uStack_8;
  
  local_20 = param_1;
  uStack_1c = param_2;
  __unpack_d(&local_20,&uStack_18);
  if (uStack_18 < 3) {
    return 0;
  }
  if (uStack_18 != 4) {
    if (iStack_10 < 0) {
      return 0;
    }
    if (iStack_10 < 0x1f) {
      uVar2 = -iStack_10 + 0x3c;
      uVar3 = -iStack_10 + 0x1c;
      uVar1 = uStack_8 >> (uVar3 & 0x3f);
      if ((uVar3 & 0x80000000) != 0) {
        uVar1 = uStack_c >> (uVar2 & 0x3f) | (uStack_8 << 1) << (0x1f - uVar2 & 0x3f);
      }
      if (iStack_14 == 0) {
        return uVar1;
      }
      return -uVar1;
    }
  }
  return (iStack_14 != 0) + 0x7fffffff;
}




void __make_dp(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  uStack_c = param_5;
  local_1c = param_1;
  uStack_18 = param_2;
  uStack_14 = param_3;
  uStack_10 = param_4;
  __pack_d(&local_1c);
  return;
}




void __truncdfsf2(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  uint uStack_c;
  int iStack_8;
  
  local_20 = param_1;
  uStack_1c = param_2;
  __unpack_d(&local_20,&uStack_18);
  uVar1 = iStack_8 << 2 | uStack_c >> 0x1e;
  if ((uStack_c & 0x1fffffff) != 0) {
    uVar1 = uVar1 | 1;
  }
  __make_fp(uStack_18,uStack_14,uStack_10,uVar1);
  return;
}




void __floatunsidf(uint param_1)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  undefined4 local_1c;
  undefined4 uStack_18;
  int iStack_14;
  int iStack_10;
  uint uStack_c;
  
  uStack_18 = 0;
  if (param_1 != 0) {
    uVar3 = LZCOUNT(param_1) + 0x1d;
    uVar2 = LZCOUNT(param_1) - 3;
    local_1c = 3;
    bVar1 = (uVar2 & 0x80000000) == 0;
    uStack_c = (param_1 >> 1) >> (0x1f - uVar3 & 0x3f);
    if (bVar1) {
      uStack_c = param_1 << (uVar2 & 0x3f);
    }
    iStack_10 = param_1 << (uVar3 & 0x3f);
    if (bVar1) {
      iStack_10 = 0;
    }
    iStack_14 = 0x3c - uVar3;
    __pack_d(&local_1c);
    return;
  }
  local_1c = 2;
  __pack_d(&local_1c);
  return;
}




int __muldi3(uint param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = (param_1 & 0x7fff) * (param_3 & 0x7fff);
  return ((uVar1 >> 0x10) + (param_3 >> 0x10) * (param_1 & 0x7fff) + (param_1 >> 0x10) * (param_3 & 0x7fff)) * 0x10000 + (uVar1 & 0x7fff);
}




void __unpack_f(uint *param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = (*(param_1 + 2) & 0x3fff) >> 7;
  uVar4 = *param_1 & 0x3fffff;
  param_2[1] = *(param_1 + 3) >> 7;
  if (uVar2 != 0) {
    if (uVar2 == 0xff) {
      if (uVar4 == 0) {
        *param_2 = 4;
      }
      else {
        *param_2 = 0;
        param_2[3] = uVar4 << 7;
      }
    }
    else {
      param_2[2] = uVar2 - 0x7f;
      *param_2 = 3;
      param_2[3] = uVar4 << 7 | 0x40000000;
    }
    return;
  }
  if (uVar4 != 0) {
    *param_2 = 3;
    uVar4 = uVar4 << 7;
    iVar1 = -0x7f;
    do {
      iVar3 = iVar1;
      uVar4 = uVar4 * 2;
      iVar1 = iVar3 + -1;
    } while (uVar4 < 0x40000000);
    param_2[2] = iVar3;
    param_2[3] = uVar4;
    return;
  }
  *param_2 = 2;
  return;
}




void __make_fp(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  local_14 = param_1;
  uStack_10 = param_2;
  uStack_c = param_3;
  uStack_8 = param_4;
  __pack_f(&local_14);
  return;
}




uint __pack_d(uint *param_1)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  uVar3 = *param_1;
  uVar5 = param_1[3];
  uVar6 = param_1[4];
  if (uVar3 < 2) {
    return uVar6 << 0x18 | uVar5 >> 8;
  }
  if (((uVar3 != 4) && (uVar3 != 2)) && (uVar5 != 0 || uVar6 != 0)) {
    uVar3 = param_1[2];
    if (uVar3 < -0x3fe) {
      uVar4 = -uVar3 - 0x3fe;
      if (uVar4 < 0x39) {
        uVar2 = -uVar3 - 0x41e;
        bVar1 = (uVar2 & 0x80000000) == 0;
        uVar3 = uVar5 >> (uVar4 & 0x3f) | (uVar6 << 1) << (0x1f - uVar4 & 0x3f);
        if (bVar1) {
          uVar3 = uVar6 >> (uVar2 & 0x3f);
        }
        iVar7 = 1 << (uVar4 & 0x3f);
        uVar8 = uVar6 >> (uVar4 & 0x3f);
        uVar4 = 0;
        if (bVar1) {
          iVar7 = 0;
          uVar8 = 0;
          uVar4 = 1 << (uVar2 & 0x3f);
        }
        if (iVar7 == 0) {
          uVar4 = uVar4 - 1;
        }
        uVar5 = (uVar5 & iVar7 - 1U) != 0 || (uVar6 & uVar4) != 0;
        uVar6 = uVar3 | uVar5;
        if ((uVar3 & 0xff | uVar5) == 0x80) {
          if ((uVar3 & 0x100) == 0) {
            return uVar3 >> 8 | uVar8 << 0x18;
          }
          uVar5 = 0x80;
        }
        else {
          uVar5 = 0x7f;
        }
        return uVar6 + uVar5 >> 8 | (uVar8 + CARRY4(uVar6,uVar5)) * 0x1000000;
      }
    }
    else if (uVar3 < 0x400) {
      if ((uVar5 & 0xff) == 0x80) {
        if ((uVar5 & 0x100) != 0) {
          bVar1 = 0xffffff7f < uVar5;
          uVar5 = uVar5 + 0x80;
          uVar6 = uVar6 + bVar1;
        }
      }
      else {
        bVar1 = 0xffffff80 < uVar5;
        uVar5 = uVar5 + 0x7f;
        uVar6 = uVar6 + bVar1;
      }
      if (0x1fffffff < uVar6) {
        uVar3 = uVar6 << 0x1f;
        uVar6 = uVar6 >> 1;
        uVar5 = uVar3 | uVar5 >> 1;
      }
      return uVar5 >> 8 | uVar6 << 0x18;
    }
  }
  return 0;
}




void __unpack_d(uint *param_1,undefined4 *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar4 = (*(param_1 + 6) & 0x3fff) >> 4;
  uVar6 = param_1[1];
  uVar7 = *param_1;
  uVar5 = uVar6 & 0x7ffff;
  param_2[1] = *(param_1 + 7) >> 7;
  if (uVar4 != 0) {
    if (uVar4 == 0x7ff) {
      if (uVar7 == 0 && uVar5 == 0) {
        *param_2 = 4;
      }
      else {
        *param_2 = 0;
        param_2[3] = uVar7 << 8;
        param_2[4] = (uVar6 & 0x7ffff) << 8 | uVar7 >> 0x18;
      }
    }
    else {
      param_2[2] = uVar4 - 0x3ff;
      *param_2 = 3;
      param_2[3] = uVar7 << 8;
      param_2[4] = uVar5 << 8 | uVar7 >> 0x18;
    }
    return;
  }
  if (uVar7 != 0 || uVar5 != 0) {
    uVar5 = uVar5 << 8 | uVar7 >> 0x18;
    uVar7 = uVar7 << 8;
    *param_2 = 3;
    iVar2 = -0x3ff;
    do {
      iVar3 = iVar2;
      bVar1 = CARRY4(uVar7,uVar7);
      uVar7 = uVar7 * 2;
      uVar5 = uVar5 * 2 + bVar1;
      iVar2 = iVar3 + -1;
    } while (uVar5 < 0x10000000);
    param_2[2] = iVar3;
    param_2[3] = uVar7;
    param_2[4] = uVar5;
    return;
  }
  *param_2 = 2;
  return;
}




int __fpcmp_parts_d(uint *param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar2 = *param_1;
  if ((uVar2 < 2) || (uVar4 = *param_2, uVar4 < 2)) {
    return 1;
  }
  if (uVar2 == 4) {
    if (uVar4 == 4) {
      return param_2[1] - param_1[1];
    }
LAB_08012e52:
    iVar1 = -1;
    if (param_1[1] == 0) {
      iVar1 = 1;
    }
    return iVar1;
  }
  if (uVar4 != 4) {
    if (uVar2 != 2) {
      if (uVar4 == 2) goto LAB_08012e52;
      uVar2 = param_1[1];
      if (uVar2 != param_2[1]) {
LAB_08012e2a:
        iVar1 = -1;
        if (uVar2 == 0) {
          iVar1 = 1;
        }
        return iVar1;
      }
      if (param_2[2] < param_1[2]) goto LAB_08012e2a;
      if (param_1[2] < param_2[2]) {
        if (uVar2 != 0) {
          return 1;
        }
        return -1;
      }
      uVar3 = param_1[4];
      uVar4 = param_2[4];
      if ((uVar4 < uVar3) || ((uVar3 == uVar4 && (param_2[3] < param_1[3])))) {
        if (uVar2 == 0) {
          return 1;
        }
        return -1;
      }
      if (uVar4 <= uVar3) {
        if (uVar4 != uVar3) {
          return 0;
        }
        if (param_2[3] <= param_1[3]) {
          return 0;
        }
      }
      goto LAB_08012e3e;
    }
    if (uVar4 == 2) {
      return 0;
    }
  }
  uVar2 = param_2[1];
LAB_08012e3e:
  iVar1 = 1;
  if (uVar2 == 0) {
    iVar1 = -1;
  }
  return iVar1;
}




uint __pack_f(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *param_1;
  uVar2 = param_1[3];
  if (uVar1 < 2) {
    return (uVar2 & 0xfffffff) >> 7 | 0x400000;
  }
  if (uVar1 != 4) {
    if (uVar1 == 2) {
      return 0;
    }
    if (uVar2 != 0) {
      uVar1 = param_1[2];
      if (uVar1 < -0x7e) {
        uVar1 = -uVar1 - 0x7e;
        if (0x19 < uVar1) {
          return 0;
        }
        uVar3 = uVar2 >> (uVar1 & 0x3f);
        uVar1 = (uVar2 & (1 << (uVar1 & 0x3f)) - 1U) != 0;
        uVar2 = uVar1 | uVar3;
        if ((uVar1 | uVar3 & 0x7f) == 0x40) {
          if ((uVar3 & 0x80) != 0) {
            uVar2 = uVar2 + 0x40;
          }
        }
        else {
          uVar2 = uVar2 + 0x3f;
        }
        return (uVar2 & 0x1fffffff) >> 7;
      }
      if (uVar1 < 0x80) {
        if ((uVar2 & 0x7f) == 0x40) {
          if ((uVar2 & 0x80) != 0) {
            uVar2 = uVar2 + 0x40;
          }
        }
        else {
          uVar2 = uVar2 + 0x3f;
        }
        if (uVar2 < 0) {
          uVar2 = uVar2 >> 1;
        }
        return (uVar2 & 0x1fffffff) >> 7;
      }
    }
  }
  return 0;
}




int putchar(int __c)

{
  int iVar1;
  
  iVar1 = putc(__c,stdout);
  return iVar1;
}




int puts(char *__s)

{
  int iVar1;
  
  fputs(__s,stdout);
  iVar1 = fputc(10,stdout);
  return iVar1;
}




int fputs(char *__s,FILE *__stream)

{
  uint __c;
  int iVar1;
  int iVar2;
  
  if (__stream == 0x0) {
    return -1;
  }
  os_critical_enter(&__stream->_IO_write_end);
  __c = *__s;
  if (__c == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = 0;
    do {
      iVar1 = fputc(__c,__stream);
      if (iVar1 == -1) {
        return -1;
      }
      __s = __s + 1;
      __c = *__s;
      iVar2 = iVar2 + 1;
    } while (__c != 0);
  }
  os_critical_exit(&__stream->_IO_write_end);
  return iVar2;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


int rand(void)

{
  DAT_200001b8 = DAT_200001b8 * 0x41c64e6d + 0x3039;
  return DAT_200001b8 >> 1;
}




void srand(uint __seed)

{
  DAT_200001b8 = __seed;
  return;
}




void * memset(void *__s,int __c,size_t __n)

{
  undefined1 uVar1;
  uint uVar2;
  size_t sVar3;
  uint *puVar4;
  
  if (__n != 0) {
    uVar1 = __c;
    sVar3 = __n;
    puVar4 = __s;
    if ((__s & 3) != 0) {
      *__s = uVar1;
      sVar3 = __n - 1;
      if (sVar3 == 0) {
        return __s;
      }
      puVar4 = __s + 1;
      if ((puVar4 & 3) != 0) {
        *puVar4 = uVar1;
        sVar3 = __n - 2;
        if (sVar3 == 0) {
          return __s;
        }
        puVar4 = __s + 2;
        if ((puVar4 & 3) != 0) {
          *puVar4 = uVar1;
          sVar3 = __n - 3;
          puVar4 = __s + 3;
        }
      }
    }
    uVar2 = __c & 0xffU | (__c & 0xffU) << 8;
    uVar2 = uVar2 | uVar2 << 0x10;
    for (; 0xf < sVar3; sVar3 = sVar3 - 0x10) {
      *puVar4 = uVar2;
      puVar4[1] = uVar2;
      puVar4[2] = uVar2;
      puVar4[3] = uVar2;
      puVar4 = puVar4 + 4;
    }
    for (; 3 < sVar3; sVar3 = sVar3 - 4) {
      *puVar4 = uVar2;
      puVar4 = puVar4 + 1;
    }
    if (((sVar3 != 0) && (*puVar4 = uVar1, sVar3 != 1)) && (*(puVar4 + 1) = uVar1, sVar3 != 2)) {
      *(puVar4 + 2) = uVar1;
      return __s;
    }
  }
  return __s;
}




void * memcpy(void *__dest,void *__src,size_t __n)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  
  puVar5 = __dest;
  puVar2 = __dest;
  if (((__src | __dest) & 3) == 0) {
    for (; 0xf < __n; __n = __n - 0x10) {
      uVar3 = *(__src + 4);
      uVar4 = *(__src + 8);
      *puVar5 = *__src;
      uVar6 = *(__src + 0xc);
      puVar5[1] = uVar3;
      puVar5[2] = uVar4;
      puVar5[3] = uVar6;
      __src = __src + 0x10;
      puVar5 = puVar5 + 4;
    }
    for (; 3 < __n; __n = __n - 4) {
      uVar3 = *__src;
      __src = __src + 4;
      *puVar5 = uVar3;
      puVar5 = puVar5 + 1;
    }
    for (; __n != 0; __n = __n - 1) {
      uVar1 = *__src;
      __src = __src + 1;
      *puVar5 = uVar1;
      puVar5 = puVar5 + 1;
    }
  }
  else {
    for (; __n != 0; __n = __n - 1) {
      uVar1 = *__src;
      __src = __src + 1;
      *puVar2 = uVar1;
      puVar2 = puVar2 + 1;
    }
  }
  return __dest;
}




undefined4 os_critical_open(void)

{
  return 0;
}




undefined4 os_critical_enter(void)

{
  return 0;
}




undefined4 os_critical_exit(void)

{
  return 0;
}




undefined4 os_critical_close(void)

{
  return 0;
}




int putc(int __c,FILE *__stream)

{
  int iVar1;
  
  iVar1 = fputc(__c,__stream);
  return iVar1;
}




void HAL_GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_InitTypeDef *GPIO_Init)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint32_t uVar7;
  
  uVar3 = GPIO_Init->Pin;
  if (uVar3 != 0) {
    uVar1 = 0;
    do {
      uVar2 = 1 << (uVar1 & 0x3f);
      if (uVar2 == (uVar2 & uVar3)) {
        uVar6 = GPIO_Init->Mode;
        uVar4 = ~uVar2;
        GPIOx->AF_SEL = GPIOx->AF_SEL & uVar4;
        if (uVar6 == 2) {
          GPIOx->DIR = uVar2 | GPIOx->DIR;
          uVar5 = 0xffffff7b;
LAB_080131b8:
          uVar7 = GPIO_Init->Pull;
          if (uVar7 != 0x12) goto LAB_080131c2;
LAB_080131f6:
          GPIOx->PULLUP_EN = uVar2 | GPIOx->PULLUP_EN;
          GPIOx->PULLDOWN_EN = uVar4 & GPIOx->PULLDOWN_EN;
          if (uVar5 < 5) goto LAB_080131d4;
LAB_08013214:
          if ((uVar6 & 0x80) == 0) goto LAB_08013168;
        }
        else {
          if (uVar6 < 3) {
            if (uVar6 == 1) {
              uVar5 = 0xffffff7a;
              goto LAB_080131ac;
            }
            uVar5 = uVar6 - 0x87;
            goto LAB_080131b8;
          }
          uVar5 = uVar6 - 0x87;
          if (uVar5 < 5) {
LAB_080131ac:
            GPIOx->DIR = uVar4 & GPIOx->DIR;
            goto LAB_080131b8;
          }
          uVar7 = GPIO_Init->Pull;
          if (uVar7 == 0x12) goto LAB_080131f6;
LAB_080131c2:
          if (uVar7 == 0x13) {
            GPIOx->PULLUP_EN = uVar4 & GPIOx->PULLUP_EN;
            GPIOx->PULLDOWN_EN = uVar4 & GPIOx->PULLDOWN_EN;
          }
          else if (uVar7 == 0x14) {
            GPIOx->PULLUP_EN = uVar2 | GPIOx->PULLUP_EN;
            GPIOx->PULLDOWN_EN = uVar2 | GPIOx->PULLDOWN_EN;
          }
          if (4 < uVar5) goto LAB_08013214;
LAB_080131d4:
          switch((&PTR_LAB_0802e95c)[uVar5] & 0xfffffffe) {
          case 0x801324e:
            GPIOx->IS = GPIOx->IS | uVar2;
            GPIOx->IEV = GPIOx->IEV | uVar2;
            break;
          case 0x801326c:
            GPIOx->IS = uVar4 & GPIOx->IS;
            GPIOx->IBE = GPIOx->IBE | uVar2;
            break;
          case 0x8013284:
            GPIOx->IS = uVar4 & GPIOx->IS;
            GPIOx->IBE = uVar4 & GPIOx->IBE;
            GPIOx->IEV = uVar4 & GPIOx->IEV;
            break;
          case 0x80132aa:
            GPIOx->IS = uVar4 & GPIOx->IS;
            GPIOx->IBE = uVar4 & GPIOx->IBE;
            GPIOx->IEV = GPIOx->IEV | uVar2;
            break;
          case 0x80132ce:
            GPIOx->IS = uVar2 | GPIOx->IS;
            GPIOx->IEV = uVar4 & GPIOx->IEV;
          }
        }
        GPIOx->IE = uVar2 | GPIOx->IE;
      }
LAB_08013168:
      uVar1 = uVar1 + 1;
    } while (uVar3 >> (uVar1 & 0x3f) != 0);
  }
  return;
}




void HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx,uint32_t GPIO_Pin)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  if (GPIO_Pin != 0) {
    uVar3 = 0;
    do {
      uVar2 = 1 << (uVar3 & 0x3f) & GPIO_Pin;
      if (uVar2 != 0) {
        uVar1 = ~uVar2;
        GPIOx->DIR = GPIOx->DIR & uVar1;
        GPIOx->PULLUP_EN = uVar2 | GPIOx->PULLUP_EN;
        GPIOx->PULLDOWN_EN = GPIOx->PULLDOWN_EN & uVar1;
        GPIOx->IS = GPIOx->IS & uVar1;
        GPIOx->IBE = GPIOx->IBE & uVar1;
        GPIOx->IEV = GPIOx->IEV & uVar1;
        GPIOx->IE = uVar1 & GPIOx->IE;
      }
      uVar3 = uVar3 + 1;
    } while (GPIO_Pin >> (uVar3 & 0x3f) != 0);
  }
  return;
}




undefined4 HAL_UART_Init(int *huart)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int local_14 [3];
  
  if (huart != 0x0) {
    if (huart[0xd] == 0) {
      huart[0xc] = 0;
      HAL_UART_MspInit();
    }
    huart[0xd] = 0x24;
    puVar3 = *huart;
    uVar1 = huart[4];
    *puVar3 = *puVar3 & 0xffffff3f;
    *puVar3 = huart[2] | uVar1 | huart[5] | huart[3] | *puVar3 & 0xffffff20;
    if (puVar3 == &peripheral_uart2_line_ctrl) {
      uVar1 = Ram40010a00;
      Ram40010a00 = uVar1 & 0xfeffffff;
    }
    puVar3[1] = huart[6] | 0x14U | puVar3[1] & 0xffffffe2;
    puVar3[2] = puVar3[2] & 0xffffff03 | 0x24;
    puVar3[3] = puVar3[3] | 0x3f;
    SystemClock_Get(local_14);
    uVar2 = huart[1] * 0x10;
    uVar1 = (local_14[0] * 1000000) / uVar2;
    puVar3 = *huart;
    puVar3[4] = ((local_14[0] * 1000000 - uVar1 * uVar2) * 0x10) / uVar2 << 0x10 | uVar1 - 1;
    *puVar3 = *puVar3 | 0xc0;
    huart[0xf] = 0;
    huart[0xd] = 0x20;
    huart[0xe] = 0x20;
    return 0;
  }
  return 1;
}




HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart)

{
  if (huart != 0x0) {
    huart->gState = HAL_UART_STATE_BUSY;
    huart->Instance->LC = huart->Instance->LC & 0xffffff3f;
    HAL_UART_MspDeInit();
    huart->ErrorCode = 0;
    huart->Lock = HAL_UNLOCKED;
    huart->gState = HAL_UART_STATE_RESET;
    huart->RxState = HAL_UART_STATE_RESET;
    return HAL_OK;
  }
  return HAL_ERROR;
}




HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart,uint8_t *pData,uint16_t Size,uint32_t Timeout)

{
  uint32_t uVar1;
  USART_TypeDef *pUVar2;
  uint32_t uVar3;
  undefined2 in_register_0000000a;
  uint32_t uVar4;
  
  if (huart->gState == HAL_UART_STATE_READY) {
    if ((pData == 0x0) || (CONCAT22(in_register_0000000a,Size) == 0)) {
      return HAL_ERROR;
    }
    if (huart->Lock != HAL_LOCKED) {
      huart->Lock = HAL_LOCKED;
      huart->ErrorCode = 0;
      huart->gState = HAL_UART_STATE_BUSY_TX;
      uVar1 = HAL_GetTick();
      huart->TxXferCount = Size;
      huart->TxXferSize = Size;
      huart->Lock = HAL_UNLOCKED;
      if (huart->TxXferCount == 0) {
        pUVar2 = huart->Instance;
      }
      else {
        pUVar2 = huart->Instance;
        do {
          while (0x1f < (pUVar2->FIFOS & 0x3f)) {
            if (Timeout != 0xffffffff) {
              if ((Timeout == 0) || (uVar3 = HAL_GetTick(), Timeout < uVar3 - uVar1)) goto LAB_08013548;
              pUVar2 = huart->Instance;
            }
          }
          uVar4 = *pData;
          pData = pData + 1;
          pUVar2->TDW = uVar4;
          huart->TxXferCount = huart->TxXferCount - 1;
        } while (huart->TxXferCount != 0);
      }
      while( true ) {
        do {
          if ((pUVar2->FIFOS & 0x3f) == 0) {
            huart->gState = HAL_UART_STATE_READY;
            return HAL_OK;
          }
        } while (Timeout == 0xffffffff);
        if ((Timeout == 0) || (uVar3 = HAL_GetTick(), Timeout < uVar3 - uVar1)) break;
        pUVar2 = huart->Instance;
      }
LAB_08013548:
      huart->gState = HAL_UART_STATE_READY;
      huart->RxState = HAL_UART_STATE_READY;
      huart->Lock = HAL_UNLOCKED;
      return HAL_TIMEOUT;
    }
  }
  return HAL_BUSY;
}




HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart,uint8_t *pData,uint16_t Size)

{
  uint uVar1;
  USART_TypeDef *pUVar2;
  
  if (huart->RxState == HAL_UART_STATE_READY) {
    if (pData == 0x0) {
      return HAL_ERROR;
    }
    if (huart->Lock != HAL_LOCKED) {
      huart->RxXferCount = 0;
      huart->RxXferSize = Size;
      huart->ErrorCode = 0;
      huart->RxState = HAL_UART_STATE_BUSY_RX;
      pUVar2 = huart->Instance;
      huart->pRxBuffPtr = pData;
      uVar1 = pUVar2->INTS;
      huart->Lock = HAL_UNLOCKED;
      pUVar2->INTS = uVar1 | 0x1ec;
      pUVar2->INTM = pUVar2->INTM & 0xfffffe13;
      return HAL_OK;
    }
  }
  return HAL_BUSY;
}




void HAL_UART_TxCpltCallback(void)

{
  return;
}




void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)

{
  uint32_t *puVar1;
  uint8_t *puVar2;
  USART_TypeDef *pUVar3;
  uint32_t uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  pUVar3 = huart->Instance;
  uVar6 = pUVar3->INTS;
  uVar8 = pUVar3->INTM;
  pUVar3->INTS = pUVar3->INTS | uVar6;
  if ((((uVar6 & 0x1ec) != 0) && ((uVar8 & 0x1ec) == 0)) && (huart->ErrorCode = uVar6 & 0xe0, huart->RxState == HAL_UART_STATE_BUSY_RX)) {
    uVar7 = (pUVar3->FIFOS & 0x7ff) >> 6;
    if ((pUVar3 == &peripheral_uart4_line_ctrl) && (uVar7 != 10)) {
      uVar5 = uVar7 - 1 & 0xff;
      if (uVar7 != 0) {
        do {
          uVar5 = uVar5 - 1 & 0xff;
        } while (uVar5 != 0xff);
      }
      huart->RxXferCount = 0;
    }
    else {
      do {
        while( true ) {
          do {
            uVar7 = uVar7 - 1 & 0xff;
            if (uVar7 == 0xff) goto LAB_080135c8;
          } while ((huart->ErrorCode & 0xe0) != 0);
          *huart->pRxBuffPtr = huart->Instance->RDW;
          huart->RxXferCount = huart->RxXferCount + 1;
          uVar5 = huart->RxXferSize;
          puVar2 = huart->pRxBuffPtr + 1;
          huart->pRxBuffPtr = puVar2;
          if (uVar5 == 0) break;
          if (uVar5 == huart->RxXferCount) {
            huart->pRxBuffPtr = puVar2 + -uVar5;
            HAL_UART_RxCpltCallback(huart);
            huart->RxXferCount = 0;
          }
        }
      } while (uVar7 != 0);
      huart->pRxBuffPtr = puVar2 + -huart->RxXferCount;
      HAL_UART_RxCpltCallback(huart);
      huart->RxXferCount = 0;
    }
  }
LAB_080135c8:
  if ((((uVar6 & 2) != 0) && ((uVar8 & 4) == 0)) &&
     ((huart->gState == HAL_UART_STATE_BUSY_TX && ((huart->TxXferCount != 0 && (pUVar3 = huart->Instance, (pUVar3->FIFOS & 0x3f) != 0x20)))))) {
    puVar1 = huart->pTxBuffPtr;
    do {
      uVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      pUVar3->TDW = uVar4;
      huart->TxXferCount = huart->TxXferCount - 1;
      huart->pTxBuffPtr = puVar1;
      if (huart->TxXferCount == 0) break;
    } while ((pUVar3->FIFOS & 0x3f) != 0x20);
  }
  if ((((uVar6 & 1) != 0) && ((uVar8 & 1) == 0)) && (huart->TxXferCount == 0)) {
    huart->Instance->INTM = huart->Instance->INTM | 3;
    huart->gState = HAL_UART_STATE_READY;
    HAL_UART_TxCpltCallback(huart);
    return;
  }
  return;
}




void SystemClock_Get(uint *sysclk)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0x1e0 / (uRam00000e10 & 0xff);
  uVar1 = uRam00000e10 & 0x7fff;
  uVar2 = uRam00000e10 & 0x7fffff;
  sysclk[1] = uVar3;
  sysclk[2] = 0x1e0 / (uVar1 >> 8);
  *sysclk = uVar3 / (uVar2 >> 0x10);
  return;
}




HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)

{
  uint uVar1;
  
  system_CORET_RVR = ((0x1e0 / (uRam00000e10 & 0xff)) * 1000000) / 1000 - 1;
  system_CORET_CVR = 0;
  system_CORET_CSR = 7;
  uVar1 = system_VIC_IPR6;
  system_VIC_IPR6 = (TickPriority & 1) << 0xe | uVar1 & 0xffff00ff;
  system_VIC_ISER0 = 0;
  system_VIC_reserved = 0;
  uwTickPrio = TickPriority;
  return HAL_OK;
}




void SystemClock_Config(uint32_t clk)

{
  uint uVar1;
  
  if (clk - 2 < 0xef) {
    uRam00000e00 = 0x802;
    uRam00000e08 = 0xf;
    if (clk < 0xd) {
      uVar1 = 0xc / clk << 0x10;
      uRam00000e10 = 0x300;
    }
    else {
      uRam00000e10 = (clk >> 2) << 8;
      uVar1 = 0;
    }
    uRam00000e10 = clk | 0x80000000 | uVar1 | uRam00000e10;
    HAL_InitTick(7);
  }
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


void HAL_IncTick(void)

{
  uwTick = uwTick + 1;
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


uint32_t HAL_GetTick(void)

{
  return uwTick;
}




void HAL_NVIC_SetPriority(IRQn_Type IRQn,uint32_t Priority)

{
  int iVar1;
  
  iVar1 = (IRQn & SEC_IRQn) << 3;
  *(&system_VIC_IPR0 + (IRQn & ~SEC_IRQn)) = *(&system_VIC_IPR0 + (IRQn & ~SEC_IRQn)) & ~(0xff << iVar1) | ((Priority & 3) << 6) << iVar1;
  return;
}




void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (IRQn & 0x3f) >> 5;
  iVar2 = 1 << (IRQn & WDG_IRQn);
  (&system_VIC_ISER0)[uVar1] = iVar2;
  (&system_VIC_reserved)[uVar1] = iVar2;
  return;
}




void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)

{
  (&system_VIC_ISER0)[((IRQn & 0x3f) >> 5) + 0x20] = 1 << (IRQn & WDG_IRQn);
  return;
}




void SPI_Receive_IT(SPI_HandleTypeDef *hspi)

{
  SPI_TypeDef *pSVar1;
  uint32_t uVar2;
  uint uVar3;
  int iVar4;
  uint32_t fifo_count;
  uint uVar5;
  
  pSVar1 = hspi->Instance;
  uVar5 = (pSVar1->STATUS & 0x7ff) >> 8;
  if (uVar5 == 0) {
    return;
  }
  do {
    uVar3 = 0;
    fifo_count = pSVar1->RXDATA;
    iVar4 = 4;
    uVar2 = 0;
    do {
      if (hspi->RxXferCount == uVar2) break;
      hspi->pRxBuffPtr[(hspi->RxXferSize - hspi->RxXferCount) + uVar2] = fifo_count >> (uVar3 & 0x3f);
      uVar2 = uVar2 + 1;
      uVar3 = uVar3 + 8;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    hspi->RxXferCount = hspi->RxXferCount - uVar2;
    uVar5 = uVar5 - 1;
    if (hspi->RxXferCount == 0) {
      return;
    }
    if (uVar5 == 0) {
      return;
    }
    pSVar1 = hspi->Instance;
  } while( true );
}




HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)

{
  uint uVar1;
  SPI_TypeDef *pSVar2;
  
  if (hspi != 0x0) {
    if (hspi->State == HAL_SPI_STATE_RESET) {
      hspi->Lock = HAL_UNLOCKED;
      HAL_SPI_MspInit(hspi);
    }
    hspi->State = HAL_SPI_STATE_BUSY;
    pSVar2 = hspi->Instance;
    uVar1 = (hspi->Init).CLKPolarity;
    pSVar2->CH_CFG = pSVar2->CH_CFG & 0xffe7ffff;
    pSVar2->CH_CFG = (hspi->Init).NSS | 0x400000;
    pSVar2->SPI_CFG = (hspi->Init).Mode | uVar1 | (hspi->Init).CLKPhase | (hspi->Init).FirstByte;
    pSVar2->CLK_CFG = (hspi->Init).BaudRatePrescaler;
    pSVar2->CH_CFG = pSVar2->CH_CFG | 4;
    hspi->ErrorCode = 0;
    hspi->State = HAL_SPI_STATE_READY;
    return HAL_OK;
  }
  return HAL_ERROR;
}




HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi,uint8_t *pData,uint32_t Size,uint32_t Timeout)

{
  uint32_t uVar1;
  HAL_StatusTypeDef HVar2;
  byte *pbVar3;
  uint32_t uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  uint uVar11;
  SPI_TypeDef *pSVar12;
  
  if (hspi->Lock == HAL_LOCKED) {
    return HAL_BUSY;
  }
  hspi->Lock = HAL_LOCKED;
  uVar1 = HAL_GetTick();
  pSVar12 = hspi->Instance;
  if (hspi->State == HAL_SPI_STATE_READY) {
    if ((pData == 0x0) || (Size == 0)) {
      HVar2 = HAL_ERROR;
    }
    else {
      pSVar12->CH_CFG = pSVar12->CH_CFG | 0x400000;
      do {
        uVar7 = 0;
      } while (false);
      pSVar12->CH_CFG = pSVar12->CH_CFG | 0x80000;
      hspi->State = HAL_SPI_STATE_BUSY_TX;
      uVar8 = Size / 0x1ff8;
      hspi->ErrorCode = 0;
      hspi->pRxBuffPtr = 0x0;
      hspi->RxXferSize = 0;
      hspi->RxXferCount = 0;
      do {
        uVar11 = 0xfffffe00;
        if (uVar8 <= uVar7) {
          uVar11 = (Size % 0x1ff8) * 0x40;
        }
        uVar4 = 0x1ff8;
        if (uVar8 <= uVar7) {
          uVar4 = Size % 0x1ff8;
        }
        hspi->TxXferCount = uVar4;
        hspi->TxXferSize = uVar4;
        uVar6 = pSVar12->CH_CFG;
        hspi->pTxBuffPtr = pData;
        pSVar12->CH_CFG = uVar6 & 0xfff80007 | uVar11;
        pSVar12->CH_CFG = pSVar12->CH_CFG | 1;
        while (hspi->TxXferCount != 0) {
          uVar11 = 0x20 - (pSVar12->STATUS & 0x3f) >> 2;
          if ((uVar11 != 0) && (hspi->TxXferCount != 0)) {
            pbVar10 = hspi->pTxBuffPtr;
            do {
              if (hspi->TxXferCount == 0) {
                uVar6 = 0;
                uVar4 = 0;
              }
              else {
                uVar5 = 0;
                uVar6 = 0;
                uVar4 = 0;
                iVar9 = 4;
                pbVar3 = pbVar10;
                do {
                  uVar4 = uVar4 | *pbVar3 << (uVar5 & 0x3f);
                  uVar6 = uVar6 + 1;
                  if (hspi->TxXferCount <= uVar6) break;
                  pbVar3 = pbVar3 + 1;
                  uVar5 = uVar5 + 8;
                  iVar9 = iVar9 + -1;
                } while (iVar9 != 0);
              }
              pbVar10 = pbVar10 + uVar6;
              uVar11 = uVar11 - 1;
              hspi->pTxBuffPtr = pbVar10;
              hspi->TxXferCount = hspi->TxXferCount - uVar6;
              pSVar12->TXDATA = uVar4;
            } while ((uVar11 != 0) && (hspi->TxXferCount != 0));
          }
          uVar4 = HAL_GetTick();
          pSVar12 = hspi->Instance;
          if ((Timeout <= uVar4 - uVar1) && (Timeout != 0xffffffff)) goto LAB_08013ac0;
        }
        while ((pSVar12->INT_SRC & 0x40) == 0) {
          uVar4 = HAL_GetTick();
          pSVar12 = hspi->Instance;
          if ((Timeout <= uVar4 - uVar1) && (Timeout != 0xffffffff)) goto LAB_08013ac0;
        }
        uVar7 = uVar7 + 1;
        pSVar12->INT_SRC = pSVar12->INT_SRC | 0x40;
        pData = pData + 0x1ff8;
      } while (uVar7 <= uVar8);
      HVar2 = HAL_OK;
    }
  }
  else {
    HVar2 = HAL_BUSY;
  }
LAB_08013956:
  pSVar12->CH_CFG = pSVar12->CH_CFG & 0xfff7ffff;
  hspi->State = HAL_SPI_STATE_READY;
  hspi->Lock = HAL_UNLOCKED;
  return HVar2;
LAB_08013ac0:
  HVar2 = HAL_TIMEOUT;
  goto LAB_08013956;
}




HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi,uint8_t *pData,uint32_t Size,uint32_t Timeout)

{
  uint32_t uVar1;
  HAL_StatusTypeDef HVar2;
  int iVar3;
  uint uVar4;
  uint32_t uVar5;
  SPI_TypeDef *pSVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  
  if (hspi->Lock == HAL_LOCKED) {
    return HAL_BUSY;
  }
  hspi->Lock = HAL_LOCKED;
  uVar1 = HAL_GetTick();
  pSVar6 = hspi->Instance;
  if (hspi->State == HAL_SPI_STATE_READY) {
    if ((pData != 0x0) && (Size != 0)) {
      pSVar6->CH_CFG = pSVar6->CH_CFG | 0x400000;
      do {
        uVar7 = 0;
      } while (false);
      uVar8 = Size / 0x1ff8;
      pSVar6->CH_CFG = pSVar6->CH_CFG | 0x100000;
      hspi->State = HAL_SPI_STATE_BUSY_RX;
      hspi->pTxBuffPtr = 0x0;
      hspi->ErrorCode = 0;
      hspi->TxXferSize = 0;
      hspi->TxXferCount = 0;
LAB_08013b96:
      uVar10 = 0xfffffe00;
      if (uVar8 <= uVar7) {
        uVar10 = (Size % 0x1ff8) * 0x40;
      }
      uVar5 = 0x1ff8;
      if (uVar8 <= uVar7) {
        uVar5 = Size % 0x1ff8;
      }
      hspi->RxXferCount = uVar5;
      hspi->RxXferSize = uVar5;
      uVar4 = pSVar6->CH_CFG;
      hspi->pRxBuffPtr = pData;
      pSVar6->CH_CFG = uVar4 & 0xfff80007 | uVar10;
      pSVar6->CH_CFG = pSVar6->CH_CFG | 1;
LAB_08013bd0:
      if (hspi->RxXferCount != 0) {
        uVar10 = (pSVar6->STATUS & 0x7ff) >> 8;
LAB_08013be0:
        if (uVar10 != 0) goto LAB_08013c00;
        do {
          uVar10 = 0;
          if ((pSVar6->INT_SRC & 0x40) == 0) goto LAB_08013c78;
LAB_08013c00:
          uVar9 = pSVar6->RXDATA;
          uVar4 = 0;
          uVar5 = 0;
          iVar3 = 4;
          do {
            if (hspi->RxXferCount == uVar5) break;
            hspi->pRxBuffPtr[uVar5] = uVar9 >> (uVar4 & 0x3f);
            uVar4 = uVar4 + 8;
            uVar5 = uVar5 + 1;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
          hspi->pRxBuffPtr = hspi->pRxBuffPtr + uVar5;
          hspi->RxXferCount = hspi->RxXferCount - uVar5;
          if (uVar10 != 0) goto code_r0x08013c3e;
          if (hspi->RxXferCount == 0) goto LAB_08013c78;
          pSVar6 = hspi->Instance;
        } while( true );
      }
      goto LAB_08013c54;
    }
    HVar2 = HAL_ERROR;
  }
  else {
    HVar2 = HAL_BUSY;
  }
LAB_08013b2e:
  pSVar6->CH_CFG = pSVar6->CH_CFG & 0xffefffff;
  hspi->State = HAL_SPI_STATE_READY;
  hspi->Lock = HAL_UNLOCKED;
  return HVar2;
code_r0x08013c3e:
  uVar10 = uVar10 - 1;
  if (hspi->RxXferCount == 0) goto LAB_08013c78;
  pSVar6 = hspi->Instance;
  goto LAB_08013be0;
LAB_08013c78:
  uVar5 = HAL_GetTick();
  if ((Timeout <= uVar5 - uVar1) && (Timeout != 0xffffffff)) {
    pSVar6 = hspi->Instance;
    HVar2 = HAL_TIMEOUT;
    goto LAB_08013b2e;
  }
  pSVar6 = hspi->Instance;
  goto LAB_08013bd0;
LAB_08013c54:
  if ((pSVar6->INT_SRC & 0x40) == 0) {
    uVar5 = HAL_GetTick();
    pSVar6 = hspi->Instance;
    if ((Timeout <= uVar5 - uVar1) && (Timeout != 0xffffffff)) {
      HVar2 = HAL_TIMEOUT;
      goto LAB_08013b2e;
    }
    goto LAB_08013c54;
  }
  uVar7 = uVar7 + 1;
  pSVar6->INT_SRC = pSVar6->INT_SRC | 0x40;
  pData = pData + 0x1ff8;
  if (uVar8 < uVar7) goto code_r0x08013cac;
  goto LAB_08013b96;
code_r0x08013cac:
  HVar2 = HAL_OK;
  goto LAB_08013b2e;
}




void HAL_SPI_TxCpltCallback(void)

{
  return;
}




void HAL_SPI_RxCpltCallback(void)

{
  return;
}




void HAL_SPI_TxRxCpltCallback(void)

{
  return;
}




void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi)

{
  uint uVar1;
  uint uVar2;
  SPI_TypeDef *pSVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint32_t uVar7;
  int iVar8;
  
  pSVar3 = hspi->Instance;
  uVar6 = pSVar3->INT_MASK;
  uVar5 = pSVar3->INT_SRC;
  pSVar3->INT_SRC = pSVar3->INT_SRC | uVar5;
  if (false) {
    if ((((uVar5 & 1) != 0) && ((uVar6 & 1) == 0)) && (uVar4 = hspi->TxXferSize - hspi->TxXferCount, uVar4 != (uVar4 / 0x1ff8) * 0x1ff8)) {
      if (hspi->TxXferCount == 0) {
        uVar4 = 0;
        uVar2 = 0;
      }
      else {
        iVar8 = 4;
        uVar4 = 0;
        uVar1 = 0;
        uVar2 = 0;
        do {
          uVar2 = uVar2 | hspi->pTxBuffPtr[(hspi->TxXferSize - hspi->TxXferCount) + uVar4] << (uVar1 & 0x3f);
          uVar4 = uVar4 + 1;
          if (hspi->TxXferCount <= uVar4) break;
          uVar1 = uVar1 + 8;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      pSVar3->TXDATA = uVar2;
      hspi->TxXferCount = hspi->TxXferCount - uVar4;
    }
    if (((uVar5 & 0x40) != 0) && ((uVar6 & 0x40) == 0)) {
      if (hspi->TxXferCount < 0x1ff9) {
        uVar7 = hspi->TxXferCount;
        if (uVar7 == 0) {
          pSVar3->INT_MASK = pSVar3->INT_MASK | 0x45;
          if (hspi->State == HAL_SPI_STATE_BUSY_TX) {
            pSVar3->CH_CFG = pSVar3->CH_CFG & 0xfff7ffff;
            hspi->State = HAL_SPI_STATE_READY;
            HAL_SPI_TxCpltCallback(hspi);
          }
          else if (hspi->State == HAL_SPI_STATE_BUSY_TX_RX) {
            pSVar3->CH_CFG = pSVar3->CH_CFG & 0xfff7ffff;
            pSVar3->CH_CFG = pSVar3->CH_CFG & 0xffefffff;
            hspi->State = HAL_SPI_STATE_READY;
            HAL_SPI_TxRxCpltCallback(hspi);
          }
          goto LAB_08013cf8;
        }
        uVar4 = uVar7 << 6;
      }
      else {
        uVar4 = 0xfffffe00;
        uVar7 = 0x1ff8;
      }
      pSVar3->CH_CFG = pSVar3->CH_CFG & 0xfff80007 | uVar4;
      if ((pSVar3->MODE_CFG & 1) == 0) {
        if (hspi->TxXferCount == 0) {
          uVar2 = 0;
          uVar4 = 0;
        }
        else {
          iVar8 = 4;
          uVar4 = 0;
          uVar1 = 0;
          uVar2 = 0;
          do {
            uVar4 = uVar4 | hspi->pTxBuffPtr[(hspi->TxXferSize - hspi->TxXferCount) + uVar2] << (uVar1 & 0x3f);
            uVar2 = uVar2 + 1;
            if (hspi->TxXferCount <= uVar2) break;
            uVar1 = uVar1 + 8;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
        pSVar3->TXDATA = uVar4;
        hspi->TxXferCount = hspi->TxXferCount - uVar2;
      }
      else {
        HAL_DMA_Start_IT(hspi->hdmatx,hspi->pTxBuffPtr + (hspi->TxXferSize - hspi->TxXferCount),&pSVar3->TXDATA,uVar7);
        hspi->TxXferCount = hspi->TxXferCount - uVar7;
        pSVar3 = hspi->Instance;
      }
      pSVar3->CH_CFG = pSVar3->CH_CFG | 1;
    }
LAB_08013cf8:
    if (((uVar5 & 4) != 0) && ((uVar6 & 4) == 0)) {
      hspi->ErrorCode = hspi->ErrorCode | 1;
    }
  }
  if (true) {
    return;
  }
  if (((uVar5 & 2) != 0) && ((uVar6 & 2) == 0)) {
    SPI_Receive_IT(hspi);
  }
  if (((uVar5 & 0x40) != 0) && ((uVar6 & 0x40) == 0)) {
    if (hspi->RxXferCount < 0x1ff9) {
      uVar7 = hspi->RxXferCount;
      if (uVar7 == 0) {
        pSVar3 = hspi->Instance;
        pSVar3->INT_MASK = pSVar3->INT_MASK | 0x62;
        if (hspi->State == HAL_SPI_STATE_BUSY_RX) {
          pSVar3->CH_CFG = pSVar3->CH_CFG & 0xffefffff;
          hspi->State = HAL_SPI_STATE_READY;
          HAL_SPI_RxCpltCallback(hspi);
        }
        else if (hspi->State == HAL_SPI_STATE_BUSY_TX_RX) {
          pSVar3->CH_CFG = pSVar3->CH_CFG & 0xfff7ffff;
          pSVar3->CH_CFG = pSVar3->CH_CFG & 0xffefffff;
          hspi->State = HAL_SPI_STATE_READY;
          HAL_SPI_TxRxCpltCallback(hspi);
        }
        goto LAB_08013d2c;
      }
      uVar4 = uVar7 << 6;
    }
    else {
      uVar4 = 0xfffffe00;
      uVar7 = 0x1ff8;
    }
    pSVar3 = hspi->Instance;
    pSVar3->CH_CFG = pSVar3->CH_CFG & 0xfff80007 | uVar4;
    if ((pSVar3->MODE_CFG & 2) == 0) {
      SPI_Receive_IT(hspi);
    }
    else {
      HAL_DMA_Start_IT(hspi->hdmarx,&pSVar3->RXDATA,hspi->pRxBuffPtr + (hspi->RxXferSize - hspi->RxXferCount),uVar7);
      hspi->RxXferCount = hspi->RxXferCount - uVar7;
    }
    hspi->Instance->CH_CFG = hspi->Instance->CH_CFG | 1;
  }
LAB_08013d2c:
  if (((uVar5 & 0x20) != 0) && ((uVar6 & 0x20) == 0)) {
    hspi->ErrorCode = hspi->ErrorCode | 2;
  }
  return;
}




HAL_StatusTypeDef HAL_WDG_DeInit(WDG_HandleTypeDef *hwdg)

{
  WDG_TypeDef *pWVar1;
  
  HAL_NVIC_DisableIRQ(WDG_IRQn);
  pWVar1 = hwdg->Instance;
  pWVar1->CR = 0;
  pWVar1->CLR = 1;
  return HAL_OK;
}




void HAL_WDG_MspInit(WDG_HandleTypeDef *hwdg)

{
  return;
}




HAL_StatusTypeDef HAL_WDG_Init(WDG_HandleTypeDef *hwdg)

{
  WDG_TypeDef *pWVar1;
  wm_sys_clk sysclk;
  
  if (hwdg != 0x0) {
    HAL_WDG_MspInit(hwdg);
    SystemClock_Get(&sysclk);
    pWVar1 = hwdg->Instance;
    pWVar1->LD = (hwdg->Init).Reload * sysclk.apbclk;
    pWVar1->CR = 3;
    return HAL_OK;
  }
  return HAL_ERROR;
}




int __readByCMD(uchar cmd,ulong addr,uchar *buf,ulong sz)

{
  undefined3 in_register_00000001;
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 uVar6;
  
  uVar2 = peripheral_flash_ctrl_cr;
  if ((uVar2 & 1) == 0) {
    uVar2 = peripheral_flash_ctrl_cr;
    if ((uVar2 & 2) == 0) {
      peripheral_flash_ctrl_cmd_info = 0xbc00c00b;
    }
    else {
      peripheral_flash_ctrl_cmd_info = 0xb400c00b;
    }
    peripheral_flash_ctrl_addr = CONCAT31(in_register_00000001,cmd) & 0xffffff;
    peripheral_flash_ctrl_cmd_start = 0x100;
  }
  else {
    peripheral_flash_ctrl_cmd_info = 0xec00c0eb;
    peripheral_flash_ctrl_addr = CONCAT31(in_register_00000001,cmd) & 0xffffff;
    peripheral_flash_ctrl_cmd_start = 0x100;
  }
  uVar2 = addr >> 2;
  if (uVar2 == 0) {
    pcVar4 = flashRead_cache;
    puVar3 = 0x0;
  }
  else {
    uVar1 = 0;
    puVar3 = 0x0;
    do {
      uVar1 = uVar1 + 1;
      pcVar4 = flashRead_cache + puVar3;
      uVar6 = *puVar3;
      puVar3 = puVar3 + 1;
      *pcVar4 = uVar6;
    } while (uVar2 != uVar1);
    puVar3 = uVar2 * 4;
    pcVar4 = flashRead_cache + puVar3;
  }
  if ((addr & 3) != 0) {
    *pcVar4 = *puVar3;
    pcVar5 = pcVar4 + 3;
    do {
      *pcVar5 = '\0';
      pcVar5 = pcVar5 + -1;
    } while (pcVar5 != pcVar4 + ((addr & 3) - 1));
  }
  return 0;
}




int flashRead(ulong addr,uchar *buf,ulong sz)

{
  uchar *buf_00;
  ulong sz_00;
  uchar *puVar1;
  uchar *puVar2;
  uint uVar3;
  uchar *__dest;
  
  uVar3 = addr & 0xff;
  puVar2 = 0x100 - uVar3;
  __readByCMD('\0',0x100,sz,0xffffff00);
  if (puVar2 < sz) {
    buf_00 = puVar2;
    memcpy(buf,flashRead_cache + uVar3,puVar2);
    sz_00 = (sz + uVar3) - 0x100 >> 8;
    puVar2 = buf + puVar2;
    uVar3 = sz + uVar3 & 0xff;
    __dest = puVar2;
    if (sz_00 != 0) {
      __dest = puVar2 + sz_00 * 0x100;
      do {
        __readByCMD('\0',0x100,buf_00,sz_00);
        buf_00 = 0x100;
        puVar1 = puVar2 + 0x100;
        memcpy(puVar2,flashRead_cache,0x100);
        puVar2 = puVar1;
      } while (puVar1 != __dest);
    }
    if (uVar3 != 0) {
      __readByCMD('\0',uVar3,buf_00,sz_00);
      memcpy(__dest,flashRead_cache,uVar3);
      return 0;
    }
  }
  else {
    memcpy(buf,flashRead_cache + uVar3,sz);
  }
  return 0;
}




HAL_StatusTypeDef HAL_FLASH_Read(uint32_t addr,uint8_t *buf,uint32_t len)

{
  peripheral_flash_ctrl_cmd_info = 0x2c09f;
  peripheral_flash_ctrl_cmd_start = 0x100;
  if ((((((uRam00000000 >> 0x10) - 1 & 0xff) < 0x21) && ((addr & 0x3ffffff) < 1 << (uRam00000000 >> 0x10 & 0x3f))) && (len != 0)) && (buf != 0x0)) {
    if (pFlash.Lock == HAL_LOCKED) {
      return HAL_BUSY;
    }
    pFlash.Lock = HAL_LOCKED;
    flashRead(addr,buf,len);
    pFlash.Lock = HAL_UNLOCKED;
    return HAL_OK;
  }
  return HAL_ERROR;
}




HAL_StatusTypeDef HAL_FLASH_Write(uint32_t addr,uint8_t *buf,uint32_t len)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint8_t *puVar4;
  HAL_StatusTypeDef HVar5;
  uint8_t *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint32_t uVar10;
  
  peripheral_flash_ctrl_cmd_info = 0x2c09f;
  peripheral_flash_ctrl_cmd_start = 0x100;
  if (0x20 < ((uRam00000000 >> 0x10) - 1 & 0xff)) {
    return HAL_ERROR;
  }
  HVar5 = HAL_ERROR;
  if ((((addr & 0x3ffffff) < 1 << (uRam00000000 >> 0x10 & 0x3f)) && (len != 0)) && (buf != 0x0)) {
    if (pFlash.Lock != HAL_LOCKED) {
      uVar8 = addr & 0xfff;
      pFlash.Lock = HAL_LOCKED;
      uVar9 = 0x1000 - uVar8;
      uVar10 = (uVar9 < len) * uVar9 + (uVar9 >= len) * len;
      uVar9 = addr & 0x3fff000;
      while( true ) {
        flashRead(uVar9,HAL_FLASH_Write_cache,0x1000);
        peripheral_flash_ctrl_cmd_info = 6;
        peripheral_flash_ctrl_cmd_start = 0x100;
        peripheral_flash_ctrl_cmd_info = 0x820;
        peripheral_flash_ctrl_addr = uVar9 & 0xffffff;
        peripheral_flash_ctrl_cmd_start = 0x100;
        if (uVar10 != 0) {
          puVar4 = HAL_FLASH_Write_cache + uVar8;
          puVar6 = buf;
          do {
            uVar2 = *puVar6;
            puVar6 = puVar6 + 1;
            *puVar4 = uVar2;
            puVar4 = puVar4 + 1;
          } while (puVar6 != buf + uVar10);
        }
        uVar8 = uVar9;
        do {
          puVar6 = HAL_FLASH_Write_cache + (uVar8 - uVar9);
          puVar3 = 0x0;
          iVar7 = 0x40;
          do {
            uVar2 = *puVar6;
            puVar6 = puVar6 + 4;
            *puVar3 = uVar2;
            puVar3 = puVar3 + 1;
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
          uVar1 = uVar8 & 0xffffff;
          uVar8 = uVar8 + 0x100;
          peripheral_flash_ctrl_cmd_info = 6;
          peripheral_flash_ctrl_cmd_start = 0x100;
          peripheral_flash_ctrl_cmd_info = 0x80ff9002;
          peripheral_flash_ctrl_addr = uVar1;
          peripheral_flash_ctrl_cmd_start = 0x100;
        } while (uVar9 + 0x1000 != uVar8);
        if (len == uVar10) break;
        len = len - uVar10;
        buf = buf + uVar10;
        uVar8 = 0;
        uVar10 = (len < 0x1000) * 0x1000 + (len >= 0x1000) * 0x1000;
        uVar9 = uVar9 + 0x1000;
      }
      pFlash.Lock = HAL_UNLOCKED;
      return HAL_OK;
    }
    HVar5 = HAL_BUSY;
  }
  return HVar5;
}




int zw_flash_read_uuid__FUN_080142f8(uint8_t flash_output_buffer_)

{
  uint uVar1;
  undefined3 in_register_00000001;
  undefined1 *puVar2;
  undefined4 uVar3;
  size_t __n;
  undefined1 uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 local_18;
  undefined1 auStack_14 [16];
  
  puVar2 = memset(CONCAT31(in_register_00000001,flash_output_buffer_),0xff,0x12);
  uVar1 = uRam00000000;
  peripheral_flash_ctrl_cmd_info = 0x2c09f;
  peripheral_flash_ctrl_cmd_start = 0x100;
  uVar5 = uRam00000000 & 0xff;
  if (uVar5 != 0xa1) {
    if (0xa1 < uVar5) {
      if (uVar5 != 0xeb) {
        if (uVar5 == 0xef) goto LAB_0801435c;
        if (uVar5 != 200) {
          return -1;
        }
      }
LAB_08014368:
      __n = 0x10;
      uVar3 = 0x13c04b;
      iVar8 = 5;
      uVar4 = 0x10;
      goto LAB_08014372;
    }
    if (uVar5 != 0x68) {
      if (uVar5 == 0x85) goto LAB_08014368;
      if (uVar5 != 0x20) {
        return -1;
      }
    }
  }
LAB_0801435c:
  __n = 8;
  uVar3 = 0xbc04b;
  iVar8 = 3;
  uVar4 = 8;
LAB_08014372:
  puVar2[1] = uVar4;
  *puVar2 = uVar1;
  peripheral_flash_ctrl_cmd_info = uVar3;
  peripheral_flash_ctrl_cmd_start = 0x100;
  puVar6 = 0x0;
  do {
    puVar7 = puVar6 + 1;
    *(puVar6 + &local_18) = *puVar6;
    puVar6 = puVar7;
  } while (puVar7 != iVar8 << 2);
  memcpy(puVar2 + 2,auStack_14,__n);
  return 0;
}




HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc)

{
  ADC_TypeDef *pAVar1;
  uint uVar2;
  
  pAVar1 = hadc->Instance;
  uVar2 = (hadc->Init).channel;
  pAVar1->ANA_CR = pAVar1->ANA_CR & 0xfffff0ff | uVar2;
  pAVar1->IF = 3;
  pAVar1->ANA_CR = pAVar1->ANA_CR & 0xfffff0f8 | uVar2 | 3;
  hadc->Lock = HAL_UNLOCKED;
  return HAL_OK;
}




HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hadc)

{
  int iVar1;
  ADC_TypeDef *pAVar2;
  uint uVar3;
  wm_sys_clk sysclk;
  
  if (hadc != 0x0) {
    hadc->Lock = HAL_UNLOCKED;
    HAL_ADC_MspInit(hadc);
    SystemClock_Get(&sysclk);
    uRam00000e14 = (sysclk.apbclk * 1000000) / (hadc->Init).freq >> 1 & 0xff00 | uRam00000e14 & 0xffff00ff;
    uRam00000e10 = uRam00000e10 | 0x80000000;
    pAVar2 = hadc->Instance;
    pAVar2->ADC_CR = pAVar2->ADC_CR & 0xc00c00fc | 0x5005002;
    pAVar2->PGA_CR = pAVar2->PGA_CR & 0xfffffe00 | 3;
    pAVar2->ANA_CR = pAVar2->ANA_CR & 0xfffff0f8 | 0xe03;
    iVar1 = 4;
    do {
      do {
      } while ((pAVar2->IF & 1) == 0);
      iVar1 = iVar1 + -1;
      pAVar2->IF = 1;
    } while (iVar1 != 0);
    if (false) {
      uVar3 = uRam00000200 & 0x1fffc;
    }
    else {
      uVar3 = uRam00000200 & 0x3fffc | 0x20000;
    }
    hadc->offset = uVar3;
    pAVar2->ANA_CR = pAVar2->ANA_CR & 0xfffffff8 | 4;
    return HAL_OK;
  }
  return HAL_ERROR;
}




int HAL_ADC_GET_INPUT_VOLTAGE(ADC_HandleTypeDef *hadc)

{
  int iVar1;
  ADC_TypeDef *pAVar2;
  uint uVar3;
  HAL_LockTypeDef HVar4;
  
  HVar4 = HAL_LOCKED;
  if (hadc->Lock != HAL_LOCKED) {
    HAL_ADC_Start(hadc);
    HVar4 = hadc->Lock;
  }
  pAVar2 = hadc->Instance;
  iVar1 = 4;
  do {
    do {
    } while ((pAVar2->IF & 1) == 0);
    iVar1 = iVar1 + -1;
    pAVar2->IF = 1;
  } while (iVar1 != 0);
  if (HVar4 != HAL_LOCKED) {
    pAVar2->ANA_CR = pAVar2->ANA_CR & 0xfffffff8 | 4;
    hadc->Lock = HAL_UNLOCKED;
  }
  if (false) {
    uVar3 = uRam00000200 & 0x1fffc;
  }
  else {
    uVar3 = uRam00000200 & 0x3fffc | 0x20000;
  }
  __floatsidf(uVar3 - hadc->offset);
  __muldf3();
  __muldf3();
  __divdf3();
  __adddf3();
  __muldf3();
  iVar1 = __fixdfsi();
  return iVar1;
}




void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)

{
  return;
}




void HAL_ADC_CompareCallback(ADC_HandleTypeDef *hadc)

{
  return;
}




void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc)

{
  ADC_TypeDef *pAVar1;
  
  pAVar1 = hadc->Instance;
  if (((pAVar1->ADC_CR & 2) != 0) && ((pAVar1->IF & 1) != 0)) {
    pAVar1->IF = 1;
    HAL_ADC_ConvCpltCallback(hadc);
    pAVar1 = hadc->Instance;
  }
  if (((pAVar1->ADC_CR & 0x20) != 0) && ((pAVar1->IF & 2) != 0)) {
    pAVar1->IF = 2;
    HAL_ADC_CompareCallback(hadc);
    return;
  }
  return;
}




HAL_StatusTypeDef __PWM_OutMode_Config(PWM_HandleTypeDef *hpwm,uint32_t Channel,uint32_t OutMode)

{
  PWM_TypeDef *pPVar1;
  
  if (OutMode == 4) {
    hpwm->Instance->BKCR = 1 << (Channel + 0xb & 0x3f) | hpwm->Instance->BKCR;
    return HAL_OK;
  }
  if (OutMode != 3) {
    if (OutMode != 1) {
      if (OutMode == 2) {
        pPVar1 = hpwm->Instance;
        pPVar1->BKCR = pPVar1->BKCR & 0xffff07ff;
        pPVar1->CR = pPVar1->CR & 0xffffffbf;
        pPVar1->CR = pPVar1->CR & ~(1 << ((Channel >> 1) + 0xe & 0x3f));
        pPVar1->CR = 1 << (Channel >> 1 & 0x3f) | pPVar1->CR;
        if (Channel == 0) {
          pPVar1->DTCR = (hpwm->Init).Dtdiv | (hpwm->Init).Dtcnt | 0x100000 | pPVar1->DTCR & 0xfffcff00;
        }
        else if (Channel == 2) {
          pPVar1->DTCR = (hpwm->Init).Dtdiv | (hpwm->Init).Dtcnt | 0x200000 | pPVar1->DTCR & 0xfffc00ff;
        }
      }
      else if (OutMode == 0) {
        pPVar1 = hpwm->Instance;
        pPVar1->BKCR = pPVar1->BKCR & 0xffff07ff;
        pPVar1->CR = pPVar1->CR & 0xffffffbf;
        if (Channel != 4) {
          pPVar1->CR = pPVar1->CR & ~(1 << ((Channel >> 1) + 0xe & 0x3f));
          pPVar1->CR = pPVar1->CR & ~(1 << (Channel >> 1 & 0x3f));
        }
      }
      return HAL_OK;
    }
    pPVar1 = hpwm->Instance;
    pPVar1->BKCR = pPVar1->BKCR & 0xffff07ff;
    pPVar1->CR = pPVar1->CR & 0xffffffbf;
    pPVar1->CR = 1 << ((Channel >> 1) + 0xe & 0x3f) | pPVar1->CR;
    return HAL_OK;
  }
  pPVar1 = hpwm->Instance;
  pPVar1->BKCR = pPVar1->BKCR & 0xffff07ff;
  pPVar1->CR = pPVar1->CR | 0x40;
  return HAL_OK;
}




HAL_StatusTypeDef __PWM_CountType_Config(PWM_HandleTypeDef *hpwm,uint32_t Channel,uint32_t CounterMode)

{
  uint uVar1;
  
  if (Channel != 4) {
    uVar1 = (Channel + 8) * 2;
    hpwm->Instance->CR = CounterMode << (uVar1 & 0x3f) | hpwm->Instance->CR & ~(0xff << (uVar1 & 0x3f));
    return HAL_OK;
  }
  hpwm->Instance->CH4CR2 = CounterMode << 3 | hpwm->Instance->CH4CR2 & 0xffffffe7;
  return HAL_OK;
}




HAL_StatusTypeDef __PWM_Freq_Config(PWM_HandleTypeDef *hpwm,uint32_t Channel,uint32_t Prescaler,uint32_t Period)

{
  PWM_TypeDef *pPVar1;
  uint32_t uVar2;
  
  uVar2 = hpwm->Channel;
  if (uVar2 == 0) {
    pPVar1 = hpwm->Instance;
    pPVar1->CLKDIV01 = (hpwm->Init).Prescaler;
    pPVar1->PERIOD = pPVar1->PERIOD & 0xffffff00 | (hpwm->Init).Period;
    return HAL_OK;
  }
  if (uVar2 != 1) {
    if (uVar2 == 2) {
      pPVar1 = hpwm->Instance;
      pPVar1->CLKDIV23 = (hpwm->Init).Prescaler;
      pPVar1->PERIOD = (hpwm->Init).Period << 0x10 | pPVar1->PERIOD;
    }
    else if (uVar2 == 3) {
      pPVar1 = hpwm->Instance;
      pPVar1->CLKDIV23 = (hpwm->Init).Prescaler << 0x10 | pPVar1->CLKDIV23 & 0x7fff;
      pPVar1->PERIOD = (hpwm->Init).Period << 0x18 | pPVar1->PERIOD & 0x7fffff;
    }
    else if (uVar2 == 4) {
      hpwm->Instance->CH4CR1 = (hpwm->Init).Prescaler << 0x10 | (hpwm->Init).Period << 8 | hpwm->Instance->CH4CR1 & 0xff;
      return HAL_OK;
    }
    return HAL_OK;
  }
  pPVar1 = hpwm->Instance;
  pPVar1->CLKDIV01 = (hpwm->Init).Prescaler << 0x10 | pPVar1->CLKDIV01 & 0x7fff;
  pPVar1->PERIOD = (hpwm->Init).Period << 8 | pPVar1->PERIOD & 0xffff00ff;
  return HAL_OK;
}




HAL_StatusTypeDef __PWM_Duty_Config(PWM_HandleTypeDef *hpwm,uint32_t Channel,uint32_t Pulse)

{
  if (Channel == 0) {
    hpwm->Instance->CMPDAT = Pulse | hpwm->Instance->CMPDAT & 0xffffff00;
    return HAL_OK;
  }
  if (Channel != 1) {
    if (Channel == 2) {
      hpwm->Instance->CMPDAT = Pulse << 0x10 | hpwm->Instance->CMPDAT;
    }
    else if (Channel == 3) {
      hpwm->Instance->CMPDAT = Pulse << 0x18 | hpwm->Instance->CMPDAT & 0x7fffff;
    }
    else if (Channel == 4) {
      hpwm->Instance->CH4CR2 = Pulse << 8 | hpwm->Instance->CH4CR2 & 0xffff00ff;
      return HAL_OK;
    }
    return HAL_OK;
  }
  hpwm->Instance->CMPDAT = Pulse << 8 | hpwm->Instance->CMPDAT & 0xffff00ff;
  return HAL_OK;
}




HAL_StatusTypeDef __PWM_AutoReload_Config(PWM_HandleTypeDef *hpwm,uint32_t Channel,uint32_t AutoReloadPreload)

{
  uint uVar1;
  
  if (Channel != 4) {
    uVar1 = Channel + 8 & 0x3f;
    hpwm->Instance->CR = (-2 << uVar1 | 0xfffffffeU >> 0x20 - uVar1) & hpwm->Instance->CR | AutoReloadPreload << (Channel + 8 & 0x3f);
    return HAL_OK;
  }
  hpwm->Instance->CH4CR2 = AutoReloadPreload * 2 | hpwm->Instance->CH4CR2 & 0xfffffffd;
  return HAL_OK;
}




HAL_StatusTypeDef __PWM_OutInverse_Config(PWM_HandleTypeDef *hpwm,uint32_t Channel,uint32_t OutInverse)

{
  uint uVar1;
  
  if (Channel != 4) {
    uVar1 = Channel + 2 & 0x3f;
    hpwm->Instance->CR = (-2 << uVar1 | 0xfffffffeU >> 0x20 - uVar1) & hpwm->Instance->CR | OutInverse << (Channel + 2 & 0x3f);
    return HAL_OK;
  }
  hpwm->Instance->CH4CR2 = OutInverse | hpwm->Instance->CH4CR2 & 0xfffffffe;
  return HAL_OK;
}




HAL_StatusTypeDef HAL_PWM_Init(PWM_HandleTypeDef *hpwm)

{
  if (hpwm == 0x0) {
    return HAL_ERROR;
  }
  HAL_PWM_MspInit(hpwm);
  __PWM_OutMode_Config(hpwm,hpwm->Channel,(hpwm->Init).OutMode);
  __PWM_CountType_Config(hpwm,hpwm->Channel,(hpwm->Init).CounterMode);
  __PWM_Freq_Config(hpwm,hpwm->Channel,(hpwm->Init).Prescaler,(hpwm->Init).Period);
  __PWM_Duty_Config(hpwm,hpwm->Channel,(hpwm->Init).Pulse);
  __PWM_AutoReload_Config(hpwm,hpwm->Channel,(hpwm->Init).AutoReloadPreload);
  __PWM_OutInverse_Config(hpwm,hpwm->Channel,(hpwm->Init).OutInverse);
  if (hpwm->Channel != 0) {
    if (hpwm->Channel != 4) {
      return HAL_OK;
    }
    hpwm->Instance->CH4CR3 = hpwm->Instance->CH4CR3 & 0xfffffffb;
    return HAL_OK;
  }
  hpwm->Instance->CR = hpwm->Instance->CR & 0xffffefff;
  return HAL_OK;
}




HAL_StatusTypeDef HAL_PWM_Start(PWM_HandleTypeDef *hpwm)

{
  int in_r1;
  
  if (hpwm != 0x0) {
    hpwm->Instance->CR = 1 << (in_r1 + 0x1bU & 0x3f) | hpwm->Instance->CR;
    return HAL_OK;
  }
  return HAL_ERROR;
}




HAL_StatusTypeDef HAL_PWM_Stop(PWM_HandleTypeDef *hpwm)

{
  uint uVar1;
  int in_r1;
  
  if (hpwm != 0x0) {
    uVar1 = in_r1 + 0x1bU & 0x3f;
    hpwm->Instance->CR = (-2 << uVar1 | 0xfffffffeU >> 0x20 - uVar1) & hpwm->Instance->CR;
    return HAL_OK;
  }
  return HAL_ERROR;
}




HAL_StatusTypeDef HAL_PWM_Duty_Set(PWM_HandleTypeDef *hpwm,uint32_t Duty)

{
  uint32_t in_r2;
  
  if (hpwm != 0x0) {
    __PWM_Duty_Config(hpwm,Duty,in_r2);
    return HAL_OK;
  }
  return HAL_ERROR;
}




void DMA_SetConfig(DMA_HandleTypeDef *hdma,uint32_t SrcAddress,uint32_t DstAddress,uint16_t DataLength)

{
  undefined2 in_register_0000000e;
  uint uVar1;
  uint32_t uVar3;
  uint32_t uVar2;
  DMA_LinkDescriptor *pDVar4;
  DMA_Channel_TypeDef *pDVar5;
  uint uVar6;
  uint uVar7;
  
  uVar1 = CONCAT22(in_register_0000000e,DataLength);
  hdma->DmaBaseAddress->IF = 3 << (hdma->ChannelIndex * 2 & 0x3f);
  uVar2 = (hdma->Init).Mode;
  if (uVar2 == 0) {
    pDVar5 = hdma->Instance;
    pDVar5->SA = SrcAddress;
    pDVar5->DA = DstAddress;
    pDVar5->CR2 = uVar1 << 8 | pDVar5->CR2 & 0xff0000ff;
    return;
  }
  if (uVar2 != 1) {
    pDVar4 = hdma->LinkDesc;
    uVar6 = uVar1 >> 1;
    pDVar4->Control = pDVar4->Control | uVar6 << 7;
    uVar7 = pDVar4[1].Control;
    pDVar4->Valid = 0;
    pDVar4->SrcAddr = SrcAddress;
    pDVar4->DestAddr = DstAddress;
    pDVar4[1].Control = (uVar1 - uVar6) * 0x80 | uVar7;
    uVar3 = (hdma->Init).SrcInc;
    pDVar4[1].Valid = 0;
    if (uVar3 == 2) {
      pDVar4[1].SrcAddr = uVar6 + SrcAddress;
    }
    else {
      pDVar4[1].SrcAddr = SrcAddress;
    }
    if ((hdma->Init).DestInc == 8) {
      pDVar4[1].DestAddr = uVar6 + DstAddress;
    }
    else {
      pDVar4[1].DestAddr = DstAddress;
    }
    hdma->Instance->LA = pDVar4;
    return;
  }
  pDVar5 = hdma->Instance;
  pDVar5->SA = SrcAddress;
  pDVar5->DA = DstAddress;
  pDVar5->SWA = SrcAddress;
  pDVar5->DWA = DstAddress;
  pDVar5->WLEN = 0;
  if ((hdma->Init).SrcInc == 6) {
    pDVar5->WLEN = uVar1;
  }
  if ((hdma->Init).DestInc == 0x18) {
    pDVar5->WLEN = pDVar5->WLEN & 0x7fff | uVar1 << 0x10;
  }
  uVar6 = pDVar5->CR2;
  hdma->offset = uVar1;
  pDVar5->CR2 = uVar1 << 8 | uVar6 & 0xff0000ff;
  return;
}




HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma)

{
  uint32_t uVar1;
  uint uVar2;
  DMA_Channel_TypeDef *pDVar3;
  DMA_LinkDescriptor *pDVar4;
  DMA_LinkDescriptor *pDVar5;
  uint uVar6;
  
  if (hdma != 0x0) {
    pDVar3 = hdma->Instance;
    hdma->ChannelIndex = &pDVar3[-0x1745d47].LA / 0x30;
    hdma->State = HAL_DMA_STATE_BUSY;
    hdma->DmaBaseAddress = 0x800;
    pDVar3->CR2 = 0;
    pDVar3->MODE = 0;
    uVar1 = (hdma->Init).Direction;
    pDVar3->MODE = uVar1;
    if ((uVar1 == 1) && (uVar2 = (hdma->Init).RequestSourceSel, pDVar3->MODE = pDVar3->MODE & 0xffffffc3 | uVar2, (uVar2 & 0xfffffffb) == 0)) {
      uRam00000808 = uRam00000808 & 0xfffffff8 | (hdma->Init).RequestUartSel;
      uVar2 = (hdma->Init).Mode;
    }
    else {
      uVar2 = (hdma->Init).Mode;
    }
    if (uVar2 < 2) {
      pDVar3->CR2 = (hdma->Init).DataAlignment | (hdma->Init).DestInc | (hdma->Init).SrcInc;
      if (uVar2 == 1) {
        pDVar3->CR2 = pDVar3->CR2 | 1;
      }
    }
    else if (uVar2 - 2 < 2) {
      uVar6 = (hdma->Init).DestInc;
      pDVar3->MODE = pDVar3->MODE | 0x42;
      pDVar4 = hdma->LinkDesc;
      uVar6 = ((hdma->Init).DataAlignment | uVar6 | (hdma->Init).SrcInc) >> 1;
      pDVar4->Valid = 0;
      pDVar4->Control = uVar6;
      pDVar4->Next = pDVar4 + 1;
      pDVar4[1].Valid = 0;
      pDVar4[1].Control = uVar6;
      pDVar5 = pDVar4;
      if (uVar2 != 3) {
        pDVar5 = 0x0;
      }
      pDVar4[1].Next = pDVar5;
    }
    hdma->ErrorCode = 0;
    hdma->State = HAL_DMA_STATE_READY;
    hdma->Lock = HAL_UNLOCKED;
    return HAL_OK;
  }
  return HAL_ERROR;
}




HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma,uint32_t SrcAddress,uint32_t DstAddress,uint16_t DataLength)

{
  DMA_Channel_TypeDef *pDVar1;
  
  if (hdma->Lock == HAL_LOCKED) {
    return HAL_BUSY;
  }
  hdma->Lock = HAL_LOCKED;
  if (hdma->State != HAL_DMA_STATE_READY) {
    hdma->Lock = HAL_UNLOCKED;
    return HAL_BUSY;
  }
  hdma->State = HAL_DMA_STATE_BUSY;
  hdma->ErrorCode = 0;
  pDVar1 = hdma->Instance;
  pDVar1->CR1 = pDVar1->CR1 | 2;
  do {
  } while ((pDVar1->CR1 & 1) != 0);
  DMA_SetConfig(hdma,SrcAddress,DstAddress,DataLength);
  pDVar1 = hdma->Instance;
  hdma->DmaBaseAddress->IM = hdma->DmaBaseAddress->IM & ~(2 << (hdma->ChannelIndex * 2 & 0x3f));
  pDVar1->CR1 = pDVar1->CR1 | 1;
  return HAL_OK;
}



// WARNING: Unknown calling convention


void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma)

{
  DMA_TypeDef *pDVar1;
  DMA_LinkDescriptor *pDVar2;
  DMA_Channel_TypeDef *pDVar3;
  uint32_t uVar4;
  _func_2 *p_Var5;
  uint uVar6;
  uint uVar7;
  
  pDVar1 = hdma->DmaBaseAddress;
  uVar7 = 2 << (hdma->ChannelIndex * 2 & 0x3f);
  if (((pDVar1->IF & uVar7) == 0) || ((pDVar1->IM & uVar7) != 0)) goto LAB_08014c28;
  uVar4 = (hdma->Init).Mode;
  if (uVar4 == 0) {
    pDVar1->IM = pDVar1->IM | uVar7;
    hdma->Lock = HAL_UNLOCKED;
    p_Var5 = hdma->XferCpltCallback;
    hdma->State = HAL_DMA_STATE_READY;
  }
  else if (uVar4 == 1) {
    pDVar3 = hdma->Instance;
    uVar4 = hdma->offset;
    uVar6 = ((pDVar3->CR2 & 0x7fffff) >> 8) + uVar4;
    if (0xffff < uVar6) {
      pDVar3->CR1 = pDVar3->CR1 | 2;
      do {
      } while ((pDVar3->CR1 & 1) != 0);
      pDVar3->CR1 = pDVar3->CR1 | 1;
      uVar6 = uVar4;
    }
    pDVar3->CR2 = uVar6 << 8 | pDVar3->CR2 & 0xff0000ff;
    p_Var5 = hdma->XferCpltCallback;
  }
  else {
    if (1 < uVar4 - 2) goto LAB_08014c28;
    pDVar2 = hdma->LinkDesc;
    if (pDVar2->Valid == 0) {
      pDVar2->Valid = 0;
      p_Var5 = hdma->XferHalfCpltCallback;
    }
    else {
      if (pDVar2[1].Valid != 0) goto LAB_08014c28;
      if (uVar4 == 2) {
        pDVar1->IM = pDVar1->IM | uVar7;
        hdma->State = HAL_DMA_STATE_READY;
      }
      pDVar2[1].Valid = 0;
      hdma->Lock = HAL_UNLOCKED;
      p_Var5 = hdma->XferCpltCallback;
    }
  }
  if (p_Var5 != 0x0) {
    (*(p_Var5 & 0xfffffffe))(hdma);
    pDVar1 = hdma->DmaBaseAddress;
  }
LAB_08014c28:
  pDVar1->IF = uVar7 | pDVar1->IF;
  return;
}




void HAL_WDG_Init_wrapper(void)

{
  hwdg.Instance = &peripheral_wdog_1600;
  hwdg.Init.Reload = 5000000;
  HAL_WDG_Init(&hwdg);
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


int main(void)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  char *pcVar4;
  char local_74 [20];
  undefined1 auStack_60 [34];
  char local_3e [30];
  
  SystemClock_Config(2);
  printf_disabled_1("enter main\r\n");
  hwdg.Instance = &peripheral_wdog_1600;
  hwdg.Init.Reload = 5000000;
  HAL_WDG_Init(&hwdg);
  FUN_08025410();
  HAL_Delay(100);
  do {
    iVar1 = FUN_080259b8();
  } while (iVar1 == 0);
  FUN_080254a0(0);
  zw_flash_read_uuid__FUN_080142f8(local_74);
  HAL_FLASH_Read_Offset_0x96000(0,auStack_60,0x40);
  HAL_FLASH_Read_Offset_0x96000(0,auStack_60,0x40);
  pcVar3 = local_3e;
  pcVar4 = local_74;
  iVar1 = 0x12;
  do {
    if (*pcVar3 != *pcVar4) {
      FUN_08026294();
      FUN_080265c0(0,0,320,240,0xffe0);
      do {
                    // WARNING: Do nothing block with infinite loop
      } while( true );
    }
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  HAL_Delay(200);
  FUN_0802cbdc();
  HAL_Delay(100);
  SPIFLS_Init();
  FUN_0801f3cc(1);
  FUN_0802c058();
  zw_lcd_set_pwm(0);
  zw_HAL_Init_();
  zw_HAL_MspInit_();
  FUN_080161f8();
  zw_global_settings_init_(0x1000);
  zw_scope_menu_CN();
  printf_disabled_1("menu_Init..\r\n");
  zw_screenshot_init();
  printf_disabled_1("screenshot_init..\r\n");
  FUN_080219cc();
  HAL_Delay(200);
  FUN_0801f3cc(1);
  FUN_08026294();
  zw_boot_logo(0,0,image_BootLogo_0802e970);
  zw_draw_flush_offscreen();
  HAL_Delay(500);
  zw_lcd_set_pwm(1);
  HAL_Delay(200);
  zw_lcd_set_pwm(3);
  FUN_080254a0(1);
  HAL_Delay(200);
  zw_lcd_set_pwm(6);
  HAL_Delay(200);
  zw_lcd_set_pwm(10);
  HAL_Delay(200);
  zw_lcd_set_pwm(0x14);
  printf_disabled_1("end lcd_set_pwm..\r\n");
  HAL_Delay(200);
  SPIFLS_Init();
  FUN_08025700();
  do {
    iVar1 = FUN_080259b8();
  } while (iVar1 != 0);
  zw_fpga_all_reset();
  printf_disabled_1("end fpga_all_reset..\r\n");
  zw_SPI_Transmit__FUN_080267ac(0x11,0x87654321);
  uVar2 = FUN_080267f0(0x11);
  printf_disabled_1("WAVE_DUTY_CTRL = %x\r\n",uVar2);
  zw_gray_init();
  printf_disabled_1("end gray_Init..\r\n");
  zw_ui_all_init();
  printf_disabled_1("end ui_all_Init..\r\n");
  zw_cursor_init();
  printf_disabled_1("end cursor_Init..\r\n");
  if (screen_brightness_0_80 < 10) {
    screen_brightness_0_80 = 10;
  }
  zw_lcd_set_pwm(screen_brightness_0_80);
  zw_siggen_freq_duty(siggen_frequency_0_1hz,siggen_duty_cycle_0_1_);
  printf_disabled_1("end fpga_waveout_ctrl..\r\n");
  zw_timer_us(&DAT_2000a788,2000000);
  zw_timer_us(&DAT_20002690,80000);
  zw_timer_us(&DAT_200026a8,200000);
  zw_timer_us(&DAT_2000269c,100000);
  FUN_08025700();
  FUN_08025290();
  FUN_0802539c();
  zw_siggen_init();
  printf_disabled_1("waveout_Init..\r\n");
  FUN_08026294();
  zw_draw_init_(0);
  zw_draw_flush_offscreen();
  zw_power_on(5);
  FUN_08025410();
  FUN_0801f584();
  FUN_08024b68();
  FUN_08021ffc();
  DAT_2001de09 = 0;
  if (DAT_2001de0e == '\x01') {
    zw_draw_rectangle_filled(0,208,320,32,0);
    zw_flushOffscreenRectangle(0,0xd0,0x140,0x20);
  }
  if (DAT_2001ddf5 == '\x01') {
    DAT_2001ddf5 = '\0';
    FUN_0801f8ac(0x58);
    zw_dmm_calibration();
  }
main_loop:
  do {
    iVar1 = FUN_080270a8(&DAT_2000a788);
    while( true ) {
      if (iVar1 != 0) {
        (hwdg.Instance)->CLR = 1;
      }
      zw_keypress_handler();
      zw_power_button_handler_();
      FUN_08016cb4();
      event_id = zw_button_event();
      event_id = zw_voice_control();
      event_id = FUN_08016368();
      event_id = FUN_08016450();
      event_id = FUN_08016534();
      zw_scope_mode_setup_();
      FUN_08015ef0();
      event_id = zw_home_screen(event_id);
      if (system_status_ == 7) goto main_loop;
      event_id = FUN_0801f8ac();
      if (DAT_2001de0c == '\0') break;
      zw_dmm_init_();
      iVar1 = FUN_080270a8(&DAT_2000a788);
    }
    event_id = zw_siggen_related_FUN_08024208();
    if (DAT_2001de0d != '\0') {
      zw_siggen_fullscreen();
      goto main_loop;
    }
    event_id = zw_draw_personalization_menu();
    if (system_status_ != 8) {
      zw_siggen_related_FUN_08023a88();
      zw_screenshot_browser(event_id);
      FUN_08022848(event_id);
      if ((event_id != '\0') && ((system_status_ - 3 < 3 || (system_status_ == 7)))) {
        event_id = -1;
      }
      event_id = zw_scope_init_settings_(event_id);
      event_id = FUN_0802bd04();
      event_id = FUN_0801baa8();
      event_id = FUN_080185fc();
      FUN_080166cc();
      FUN_08024f5c(event_id);
      if ((system_status_ & 0xfb) != 3) {
        zw_scope_acquisition_state_();
        if (((((global_settings != 0) && (scan_mode__0_start_1_pretrigger_2_block_3_roll == '\0')) && (DAT_2001ddc9 == '\0')) &&
            ((persistance_mode_0_off_1_infinite_2_1s == '\0' && (roll_mode_enable == '\0')))) && (DAT_2001ddbb == '\0')) {
          trigger_armed_flag_ = 1;
          if (DAT_2001de15 == '\0') {
            FUN_08017cd0();
          }
          else {
            FUN_08018160();
          }
          iVar1 = FUN_080270a8(&DAT_200026a8);
          if ((iVar1 != 0) && (event_id == '\0')) {
            zw_scope_measurements();
          }
          iVar1 = FUN_080270a8(&DAT_2000269c);
          if (iVar1 != 0) {
            FUN_08026e44();
          }
        }
        iVar1 = FUN_080270a8(&DAT_20002690);
        if ((iVar1 != 0) || (system_status_ - 4 < 2)) {
          if (scan_mode__0_start_1_pretrigger_2_block_3_roll == '\0') {
            if ((((global_settings == 0) || (DAT_2001ddbb != '\0')) || (DAT_2001ddc9 != '\0')) ||
               ((persistance_mode_0_off_1_infinite_2_1s != '\0' || (roll_mode_enable != '\0')))) {
LAB_08015156:
              trigger_armed_flag_ = 1;
              if (DAT_2001de15 == '\0') {
                FUN_08017cd0();
              }
              else {
                FUN_08018160();
              }
              if (DAT_2001ddc9 == '\0') {
                iVar1 = FUN_080270a8(&DAT_200026a8);
                if ((iVar1 != 0) && (event_id == '\0')) {
                  zw_scope_measurements();
                }
                FUN_08026e44();
              }
              goto LAB_08015170;
            }
LAB_08015176:
            if (7 < timebase_index_2_5ns_30_10s) goto LAB_0801517c;
            zw_timer_us(&DAT_20002690,120000);
          }
          else {
            if (roll_mode_enable != '\0') goto LAB_08015156;
LAB_08015170:
            if (global_settings != 0) goto LAB_08015176;
LAB_0801517c:
            zw_timer_us(&DAT_20002690,80000);
          }
          FUN_0801bb50();
          if (DAT_2001ddc9 == '\0') {
            zw_draw_init_();
          }
          else {
            zw_scope_init(0);
          }
          zw_draw_flush_offscreen();
        }
        FUN_0801eff0(event_id);
        FUN_0801bd34(event_id);
        FUN_080254c0();
      }
    }
  } while( true );
}




int fls_drv_read_id(uint8_t *id)

{
  return id;
}




void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)

{
  uint uVar1;
  uint32_t uVar2;
  
  if (hadc->Instance != 0x200) {
    return;
  }
  uRam00000e00 = uRam00000e00 | 0x1800;
  uVar2 = (hadc->Init).channel;
  if (uVar2 == 0) {
    uVar1 = peripheral_gpioA_af_sel;
    peripheral_gpioA_af_sel = uVar1 & 0xfffffffd;
    uVar1 = peripheral_gpioA_dir;
    peripheral_gpioA_dir = uVar1 & 0xfffffffd;
    uVar1 = peripheral_gpioA_pull_en;
    peripheral_gpioA_pull_en = uVar1 | 2;
    uVar1 = peripheral_gpioA_dn_ena;
    peripheral_gpioA_dn_ena = uVar1 & 0xfffffffd;
    return;
  }
  if (uVar2 == 0x100) {
LAB_080152ce:
    uVar1 = peripheral_gpioA_af_sel;
    peripheral_gpioA_af_sel = uVar1 & 0xffffffef;
    uVar1 = peripheral_gpioA_dir;
    peripheral_gpioA_dir = uVar1 & 0xffffffef;
    uVar1 = peripheral_gpioA_pull_en;
    peripheral_gpioA_pull_en = uVar1 | 0x10;
    uVar1 = peripheral_gpioA_dn_ena;
    peripheral_gpioA_dn_ena = uVar1 & 0xffffffef;
  }
  else {
    if (uVar2 == 0x200) {
      uVar1 = peripheral_gpioA_af_sel;
      peripheral_gpioA_af_sel = uVar1 & 0xfffffff7;
      uVar1 = peripheral_gpioA_dir;
      peripheral_gpioA_dir = uVar1 & 0xfffffff7;
      uVar1 = peripheral_gpioA_pull_en;
      peripheral_gpioA_pull_en = uVar1 | 8;
      uVar1 = peripheral_gpioA_dn_ena;
      peripheral_gpioA_dn_ena = uVar1 & 0xfffffff7;
      return;
    }
    if (uVar2 != 0x300) {
      if (uVar2 == 0x800) {
        uVar1 = peripheral_gpioA_af_sel;
        peripheral_gpioA_af_sel = uVar1 & 0xfffffffd;
        uVar1 = peripheral_gpioA_dir;
        peripheral_gpioA_dir = uVar1 & 0xfffffffd;
        uVar1 = peripheral_gpioA_pull_en;
        peripheral_gpioA_pull_en = uVar1 | 2;
        uVar1 = peripheral_gpioA_dn_ena;
        peripheral_gpioA_dn_ena = uVar1 & 0xfffffffd;
        goto LAB_080152ce;
      }
      if (uVar2 != 0x900) {
        return;
      }
      uVar1 = peripheral_gpioA_af_sel;
      peripheral_gpioA_af_sel = uVar1 & 0xfffffff7;
      uVar1 = peripheral_gpioA_dir;
      peripheral_gpioA_dir = uVar1 & 0xfffffff7;
      uVar1 = peripheral_gpioA_pull_en;
      peripheral_gpioA_pull_en = uVar1 | 8;
      uVar1 = peripheral_gpioA_dn_ena;
      peripheral_gpioA_dn_ena = uVar1 & 0xfffffff7;
    }
    uVar1 = peripheral_gpioA_af_sel;
    peripheral_gpioA_af_sel = uVar1 & 0xfffffffb;
    uVar1 = peripheral_gpioA_dir;
    peripheral_gpioA_dir = uVar1 & 0xfffffffb;
    uVar1 = peripheral_gpioA_pull_en;
    peripheral_gpioA_pull_en = uVar1 | 4;
    uVar1 = peripheral_gpioA_dn_ena;
    peripheral_gpioA_dn_ena = uVar1 & 0xfffffffb;
  }
  return;
}




void HAL_PWM_MspInit(PWM_HandleTypeDef *hpwm)

{
  uint uVar1;
  
  uVar1 = peripheral_gpioA_af_sel;
  peripheral_gpioA_af_sel = uVar1 | 4;
  uVar1 = peripheral_gpioA_sf_s1;
  peripheral_gpioA_sf_s1 = uVar1 | 4;
  uVar1 = peripheral_gpioA_af_s0;
  peripheral_gpioA_af_s0 = uVar1 & 0xfffffffb;
  uVar1 = peripheral_gpioB_af_sel;
  peripheral_gpioB_af_sel = uVar1 | 0x2000000;
  uVar1 = peripheral_gpioB_sf_s1;
  peripheral_gpioB_sf_s1 = uVar1 & 0xfdffffff;
  uVar1 = peripheral_gpioB_af_s0;
  peripheral_gpioB_af_s0 = uVar1 | 0x2000000;
  uVar1 = peripheral_gpioA_af_sel;
  peripheral_gpioA_af_sel = uVar1 | 8;
  uVar1 = peripheral_gpioA_sf_s1;
  peripheral_gpioA_sf_s1 = uVar1 | 8;
  uVar1 = peripheral_gpioA_af_s0;
  peripheral_gpioA_af_s0 = uVar1 & 0xfffffff7;
  uRam00000e00 = uRam00000e00 | 0x2000;
  return;
}




void HAL_UART_MspInit(undefined4 *param_1)

{
  uint uVar1;
  undefined *puVar2;
  
  puVar2 = *param_1;
  if (puVar2 == &peripheral_uart3_line_ctrl) {
    uRam00000e00 = uRam00000e00 | 0x810;
    uVar1 = peripheral_gpioB_af_sel;
    peripheral_gpioB_af_sel = uVar1 | 1;
    uVar1 = peripheral_gpioB_sf_s1;
    peripheral_gpioB_sf_s1 = uVar1 | 1;
    uVar1 = peripheral_gpioB_af_s0;
    peripheral_gpioB_af_s0 = uVar1 & 0xfffffffe;
    uVar1 = peripheral_gpioB_af_sel;
    peripheral_gpioB_af_sel = uVar1 | 2;
    uVar1 = peripheral_gpioB_sf_s1;
    peripheral_gpioB_sf_s1 = uVar1 | 2;
    uVar1 = peripheral_gpioB_af_s0;
    peripheral_gpioB_af_s0 = uVar1 & 0xfffffffd;
    uVar1 = peripheral_gpioB_pull_en;
    peripheral_gpioB_pull_en = uVar1 & 0xfffffffd;
    HAL_NVIC_SetPriority(UART2_5_IRQn,0);
    HAL_NVIC_EnableIRQ(UART2_5_IRQn);
    puVar2 = *param_1;
  }
  if (puVar2 == &peripheral_uart4_line_ctrl) {
    uRam00000e00 = uRam00000e00 | 0x820;
    uVar1 = peripheral_gpioA_af_sel;
    peripheral_gpioA_af_sel = uVar1 | 0x100;
    uVar1 = peripheral_gpioA_sf_s1;
    peripheral_gpioA_sf_s1 = uVar1 & 0xfffffeff;
    uVar1 = peripheral_gpioA_af_s0;
    peripheral_gpioA_af_s0 = uVar1 | 0x100;
    uVar1 = peripheral_gpioA_af_sel;
    peripheral_gpioA_af_sel = uVar1 | 0x200;
    uVar1 = peripheral_gpioA_sf_s1;
    peripheral_gpioA_sf_s1 = uVar1 & 0xfffffdff;
    uVar1 = peripheral_gpioA_af_s0;
    peripheral_gpioA_af_s0 = uVar1 | 0x200;
    uVar1 = peripheral_gpioA_pull_en;
    peripheral_gpioA_pull_en = uVar1 & 0xfffffdff;
    HAL_NVIC_SetPriority(UART2_5_IRQn,0);
    HAL_NVIC_EnableIRQ(UART2_5_IRQn);
    puVar2 = *param_1;
  }
  if (puVar2 != 0x1000) {
    return;
  }
  uRam00000e00 = uRam00000e00 | 0x840;
  uVar1 = peripheral_gpioA_af_sel;
  peripheral_gpioA_af_sel = uVar1 | 0x2000;
  uVar1 = peripheral_gpioA_sf_s1;
  peripheral_gpioA_sf_s1 = uVar1 & 0xffffdfff;
  uVar1 = peripheral_gpioA_af_s0;
  peripheral_gpioA_af_s0 = uVar1 | 0x2000;
  uVar1 = peripheral_gpioA_pull_en;
  peripheral_gpioA_pull_en = uVar1 & 0xffffdfff;
  HAL_NVIC_SetPriority(UART2_5_IRQn,0);
  HAL_NVIC_EnableIRQ(UART2_5_IRQn);
  return;
}




void HAL_UART_MspDeInit(undefined4 *param_1)

{
  undefined *puVar1;
  
  puVar1 = *param_1;
  if (puVar1 == &peripheral_uart3_line_ctrl) {
    uRam00000e00 = uRam00000e00 & 0xffffffef;
    HAL_GPIO_DeInit(&peripheral_gpioB_data,3);
    puVar1 = *param_1;
  }
  if (puVar1 == &peripheral_uart4_line_ctrl) {
    uRam00000e00 = uRam00000e00 & 0xffffffdf;
    HAL_GPIO_DeInit(&peripheral_gpioA_data,0x300);
    puVar1 = *param_1;
  }
  if (puVar1 != 0x1000) {
    return;
  }
  uRam00000e00 = uRam00000e00 & 0xffffffbf;
  HAL_GPIO_DeInit(&peripheral_gpioA_data,0x2000);
  return;
}




void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)

{
  uint uVar1;
  
  uRam00000e00 = uRam00000e00 | 0x80;
  uVar1 = peripheral_gpioA_af_sel;
  peripheral_gpioA_af_sel = uVar1 | 1;
  uVar1 = peripheral_gpioA_sf_s1;
  peripheral_gpioA_sf_s1 = uVar1 & 0xfffffffe;
  uVar1 = peripheral_gpioA_af_s0;
  peripheral_gpioA_af_s0 = uVar1 | 1;
  uVar1 = peripheral_gpioB_af_sel;
  peripheral_gpioB_af_sel = uVar1 | 0x1000000;
  uVar1 = peripheral_gpioB_sf_s1;
  peripheral_gpioB_sf_s1 = uVar1 & 0xfeffffff;
  uVar1 = peripheral_gpioB_af_s0;
  peripheral_gpioB_af_s0 = uVar1 & 0xfeffffff;
  uVar1 = peripheral_gpioB_af_sel;
  peripheral_gpioB_af_sel = uVar1 | 0x10000;
  uVar1 = peripheral_gpioB_sf_s1;
  peripheral_gpioB_sf_s1 = uVar1 | 0x10000;
  uVar1 = peripheral_gpioB_af_s0;
  peripheral_gpioB_af_s0 = uVar1 & 0xfffeffff;
  uVar1 = peripheral_gpioB_af_sel;
  peripheral_gpioB_af_sel = uVar1 | 0x20000;
  uVar1 = peripheral_gpioB_sf_s1;
  peripheral_gpioB_sf_s1 = uVar1 | 0x20000;
  uVar1 = peripheral_gpioB_af_s0;
  peripheral_gpioB_af_s0 = uVar1 & 0xfffdffff;
  hdma_spi_tx.Instance = 0x810;
  hdma_spi_tx.Init.SrcInc = 2;
  hdma_spi_tx.Init.Direction = 1;
  hdma_spi_tx.Init.DestInc = 0;
  hdma_spi_tx.Init.DataAlignment = 0x40;
  hdma_spi_tx.Init.Mode = 0;
  hdma_spi_tx.Init.RequestSourceSel = 0x14;
  hspi->hdmatx = &hdma_spi_tx;
  hdma_spi_tx.Parent = hspi;
  HAL_DMA_Init(&hdma_spi_tx);
  hdma_spi_rx.Instance = 0x840;
  hdma_spi_rx.Init.DestInc = 8;
  hspi->hdmarx = &hdma_spi_rx;
  hdma_spi_rx.Init.RequestSourceSel = 0x10;
  hdma_spi_rx.Init.Direction = 1;
  hdma_spi_rx.Init.SrcInc = 0;
  hdma_spi_rx.Init.DataAlignment = 0x40;
  hdma_spi_rx.Init.Mode = 0;
  hdma_spi_rx.Parent = hspi;
  HAL_DMA_Init(&hdma_spi_rx);
  HAL_NVIC_SetPriority(SPI_LS_IRQn,1);
  HAL_NVIC_EnableIRQ(SPI_LS_IRQn);
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


void CORET_IRQHandler(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_78 [8];
  undefined4 auStack_58 [22];
  
  puVar4 = auStack_58;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *puVar4 = *(uVar1 + 0x48);
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_78;
  puVar4 = local_78;
  puVar3 = local_78;
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *puVar2 = *(uVar1 + 0x41c);
    puVar2 = puVar2 + 1;
  }
  HAL_IncTick();
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x400) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  puVar4 = puVar3 + 0x20;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x48) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


void ADC_IRQHandler(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_78 [8];
  undefined4 auStack_58 [22];
  
  puVar4 = auStack_58;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *puVar4 = *(uVar1 + 0x48);
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_78;
  puVar4 = local_78;
  puVar3 = local_78;
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *puVar2 = *(uVar1 + 0x41c);
    puVar2 = puVar2 + 1;
  }
  HAL_ADC_IRQHandler(&hadc);
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x400) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  puVar4 = puVar3 + 0x20;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x48) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


void UART1_IRQHandler(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_78 [8];
  undefined4 auStack_58 [22];
  
  puVar4 = auStack_58;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *puVar4 = *(uVar1 + 0x48);
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_78;
  puVar4 = local_78;
  puVar3 = local_78;
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *puVar2 = *(uVar1 + 0x41c);
    puVar2 = puVar2 + 1;
  }
  HAL_UART_IRQHandler(&DAT_20030c38);
  HAL_UART_IRQHandler(&DAT_2001de58);
  HAL_UART_IRQHandler(&DAT_2001dedc);
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x400) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  puVar4 = puVar3 + 0x20;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x48) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  return;
}




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)

{
  uint8_t *puVar1;
  USART_TypeDef *pUVar2;
  
  pUVar2 = huart->Instance;
  if (pUVar2 == &peripheral_uart3_line_ctrl) {
    if (huart->RxXferCount == 0) {
      return;
    }
    FUN_0802c344();
    pUVar2 = huart->Instance;
  }
  if (pUVar2 == &peripheral_uart4_line_ctrl) {
    if (huart->RxXferCount != 10) {
      return;
    }
    puVar1 = huart->pRxBuffPtr;
    DAT_2001de98 = *puVar1;
    DAT_2001de99 = puVar1[1];
    DAT_2001de9a = puVar1[2];
    DAT_2001de9b = puVar1[3];
    DAT_2001de9c = puVar1[4];
    DAT_2001de9d = puVar1[5];
    DAT_2001de9e = puVar1[6];
    DAT_2001de9f = puVar1[7];
    DAT_2001dea0 = puVar1[8];
    DAT_2001dea1 = puVar1[9];
    pUVar2 = huart->Instance;
  }
  if ((pUVar2 == 0x1000) && (huart->RxXferCount == 10)) {
    puVar1 = huart->pRxBuffPtr;
    DAT_2001debc = *puVar1;
    DAT_2001debd = puVar1[1];
    DAT_2001debe = puVar1[2];
    DAT_2001debf = puVar1[3];
    DAT_2001dec0 = puVar1[4];
    DAT_2001dec1 = puVar1[5];
    DAT_2001dec2 = puVar1[6];
    DAT_2001dec3 = puVar1[7];
    DAT_2001dec4 = puVar1[8];
    DAT_2001dec5 = puVar1[9];
    return;
  }
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


void SPI_LS_IRQHandler(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_78 [8];
  undefined4 auStack_58 [22];
  
  puVar4 = auStack_58;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *puVar4 = *(uVar1 + 0x48);
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_78;
  puVar4 = local_78;
  puVar3 = local_78;
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *puVar2 = *(uVar1 + 0x41c);
    puVar2 = puVar2 + 1;
  }
  HAL_SPI_IRQHandler(&hspi);
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x400) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  puVar4 = puVar3 + 0x20;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x48) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


void DMA_Channel0_IRQHandler(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_78 [8];
  undefined4 auStack_58 [22];
  
  puVar4 = auStack_58;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *puVar4 = *(uVar1 + 0x48);
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_78;
  puVar4 = local_78;
  puVar3 = local_78;
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *puVar2 = *(uVar1 + 0x41c);
    puVar2 = puVar2 + 1;
  }
  HAL_DMA_IRQHandler(&hdma_spi_tx);
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x400) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  puVar4 = puVar3 + 0x20;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x48) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


void DMA_Channel1_IRQHandler(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_78 [8];
  undefined4 auStack_58 [22];
  
  puVar4 = auStack_58;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *puVar4 = *(uVar1 + 0x48);
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_78;
  puVar4 = local_78;
  puVar3 = local_78;
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *puVar2 = *(uVar1 + 0x41c);
    puVar2 = puVar2 + 1;
  }
  HAL_DMA_IRQHandler(&hdma_spi_rx);
  for (uVar1 = 0; uVar1 < 0x1d; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x400) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  puVar4 = puVar3 + 0x20;
  for (uVar1 = 0; uVar1 < 0x35; uVar1 = uVar1 + 4) {
    *(uVar1 + 0x48) = *puVar4;
    puVar4 = puVar4 + 1;
  }
  return;
}




undefined4 FUN_08015808(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  
  if (0x32 < DAT_20019ca4 - DAT_20019ca5) {
    return 0;
  }
  pbVar4 = &DAT_20019efe;
  iVar2 = 300;
  uVar1 = DAT_200026c4;
  do {
    uVar1 = uVar1 + *pbVar4 + pbVar4[300];
    pbVar4 = pbVar4 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (DAT_200026c8 + '\x01' != '\x05') {
    DAT_200026c4 = uVar1;
    DAT_200026c8 = DAT_200026c8 + '\x01';
    return 0;
  }
  uVar3 = uVar1 / 0x1e;
  DAT_200026c8 = 0;
  DAT_200026c4 = 0;
  uVar1 = uVar1 / 3000 + (0x32 < uVar3 % 100);
  if (uVar1 == 0x7f) {
LAB_080158b4:
    if (ch1_v_div_index != 0xd) {
      ch1_v_div_index = ch1_v_div_index + 1;
      (&DAT_2000a834)[ch1_v_div_index] = 990000;
      FUN_0801eff0(0xff);
      zw_timer_us(&DAT_20002820,8000000);
      return 1;
    }
    FUN_0801eff0(0xff);
    return 2;
  }
  if (uVar1 == 0x80) {
    iVar2 = FUN_080270a8(&DAT_20002820);
    if (iVar2 != 0) goto LAB_080158b4;
  }
  else {
    if (0x81 < uVar1) {
      (&DAT_2000a834)[ch1_v_div_index] = (&DAT_2000a834)[ch1_v_div_index] + 0x7c060 + uVar3 * -0x28;
      goto LAB_080158ac;
    }
    if (uVar1 < 0x7d) {
      (&DAT_2000a834)[ch1_v_div_index] = (&DAT_2000a834)[ch1_v_div_index] + 0x7c060 + uVar3 * -0x28;
      goto LAB_080158ac;
    }
    if (uVar1 < 0x80) {
      (&DAT_2000a834)[ch1_v_div_index] = (&DAT_2000a834)[ch1_v_div_index] + 1000;
      goto LAB_080158ac;
    }
  }
  (&DAT_2000a834)[ch1_v_div_index] = (&DAT_2000a834)[ch1_v_div_index] + -1000;
LAB_080158ac:
  FUN_080251e4();
  return 1;
}




undefined4 FUN_08015974(void)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  
  if ((0x32 < DAT_20019ca4 - DAT_20019ca5) || (DAT_200026c8 = DAT_200026c8 + '\x01', DAT_200026c8 != '\x05')) {
    return 0;
  }
  DAT_200026c8 = 0;
  pbVar3 = &DAT_20019efe;
  uVar1 = 0;
  iVar2 = 300;
  do {
    uVar1 = uVar1 + *pbVar3 + pbVar3[300];
    pbVar3 = pbVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  uVar1 = (300 < uVar1 % 600) + uVar1 / 600;
  DAT_200026c4 = 0;
  uVar4 = ch1_v_div_index;
  if ((0x7f < uVar1) || (uVar1 != 0x7f)) {
    (&DAT_2000a8a4)[uVar4] = ((&DAT_2000a8a4)[uVar4] + '\x7f') - uVar1;
  }
  ch1_v_div_index = uVar4 + 1;
  if ((uVar4 + 1 & 0xff) < 0xe) {
    FUN_0801eff0(0xff);
    return 1;
  }
  ch1_v_div_index = 4;
  FUN_0801eff0(0xff);
  return 2;
}




undefined4 FUN_08015a34(void)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  
  if (DAT_2001a160 - DAT_2001a161 < 0x33) {
    pbVar3 = &DAT_2001a3ba;
    iVar2 = 300;
    uVar1 = DAT_200026c4;
    do {
      uVar1 = uVar1 + *pbVar3 + pbVar3[300];
      pbVar3 = pbVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    DAT_200026c8 = DAT_200026c8 + '\x01';
    DAT_200026c4 = uVar1;
    if (DAT_200026c8 == '\x05') {
      uVar4 = uVar1 / 0x1e;
      DAT_200026c8 = 0;
      DAT_200026c4 = 0;
      uVar1 = uVar1 / 3000 + (0x32 < uVar4 % 100);
      if (uVar1 != 0x7f) {
        if (uVar1 < 0x82) {
          if (uVar1 < 0x7d) {
            (&DAT_2000a834)[ch2_v_div_index + 0xe] = (&DAT_2000a834)[ch2_v_div_index + 0xe] + 0x7c060 + uVar4 * -0x28;
          }
          else {
            iVar2 = ch2_v_div_index + 0xe;
            if (uVar1 < 0x80) {
              (&DAT_2000a834)[iVar2] = (&DAT_2000a834)[iVar2] + 1000;
            }
            else {
              (&DAT_2000a834)[iVar2] = (&DAT_2000a834)[iVar2] + -1000;
            }
          }
        }
        else {
          (&DAT_2000a834)[ch2_v_div_index + 0xe] = (&DAT_2000a834)[ch2_v_div_index + 0xe] + 0x7c060 + uVar4 * -0x28;
        }
        FUN_080252e4();
        return 1;
      }
      if (ch2_v_div_index == 0xd) {
        FUN_0801eff0(0xff);
        return 2;
      }
      ch2_v_div_index = ch2_v_div_index + 1;
      (&DAT_2000a834)[ch2_v_div_index + 0xe] = 990000;
      FUN_0801eff0(0xff);
      return 1;
    }
  }
  return 0;
}




undefined4 FUN_08015b80(void)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  
  if (DAT_20019ca4 - DAT_20019ca5 < 0x33) {
    pbVar3 = &DAT_20019efe;
    iVar2 = 300;
    do {
      DAT_200026c4 = DAT_200026c4 + *pbVar3 + pbVar3[300];
      pbVar3 = pbVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    DAT_200026c8 = DAT_200026c8 + '\x01';
    if (DAT_200026c8 == '\x19') {
      DAT_200026c8 = 0;
      uVar1 = DAT_200026c4 / 15000;
      DAT_200026c4 = 0;
      if (uVar1 - 0xc1 < 0x13) {
        DAT_200026c4 = 0;
        DAT_200026c8 = 0;
        DAT_2000a8b4 = 75000 / (uVar1 - 0x7f);
        return 1;
      }
      DAT_2000a8b4 = 1000;
      return 1;
    }
  }
  return 0;
}




undefined4 FUN_08015c14(void)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  
  if (DAT_20019ca4 - DAT_20019ca5 < 0x33) {
    pbVar3 = &DAT_20019efe;
    iVar2 = 300;
    do {
      DAT_200026c4 = DAT_200026c4 + *pbVar3 + pbVar3[300];
      pbVar3 = pbVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    DAT_200026c8 = DAT_200026c8 + '\x01';
    if (DAT_200026c8 == '\x19') {
      DAT_200026c8 = 0;
      uVar1 = DAT_200026c4 / 15000;
      DAT_200026c4 = 0;
      if (uVar1 - 0x2b < 0x13) {
        DAT_200026c4 = 0;
        DAT_200026c8 = 0;
        DAT_2000a8bc = 75000 / (0x7f - uVar1);
        return 1;
      }
      DAT_2000a8bc = 1000;
      return 1;
    }
  }
  return 0;
}




undefined4 FUN_08015ca8(void)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  
  if (DAT_2001a160 - DAT_2001a161 < 0x33) {
    pbVar3 = &DAT_2001a3ba;
    iVar2 = 300;
    do {
      DAT_200026c4 = DAT_200026c4 + *pbVar3 + pbVar3[300];
      pbVar3 = pbVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    DAT_200026c8 = DAT_200026c8 + '\x01';
    if (DAT_200026c8 == '\x19') {
      DAT_200026c8 = 0;
      uVar1 = DAT_200026c4 / 15000;
      DAT_200026c4 = 0;
      if (uVar1 - 0xc1 < 0x13) {
        DAT_200026c4 = 0;
        DAT_200026c8 = 0;
        DAT_2000a8b8 = 75000 / (uVar1 - 0x7f);
        return 1;
      }
      DAT_2000a8b8 = 1000;
      return 1;
    }
  }
  return 0;
}




undefined4 FUN_08015d3c(void)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  
  if (DAT_2001a160 - DAT_2001a161 < 0x33) {
    pbVar3 = &DAT_2001a3ba;
    iVar2 = 300;
    do {
      DAT_200026c4 = DAT_200026c4 + *pbVar3 + pbVar3[300];
      pbVar3 = pbVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    DAT_200026c8 = DAT_200026c8 + '\x01';
    if (DAT_200026c8 == '\x19') {
      DAT_200026c8 = 0;
      uVar1 = DAT_200026c4 / 15000;
      DAT_200026c4 = 0;
      if (uVar1 - 0x2b < 0x13) {
        DAT_200026c4 = 0;
        DAT_200026c8 = 0;
        DAT_2000a8c0 = 75000 / (0x7f - uVar1);
        return 1;
      }
      DAT_2000a8c0 = 1000;
      return 1;
    }
  }
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_08015dd0(void)

{
  undefined2 uStack_a2;
  undefined2 uStack_9e;
  undefined2 uStack_9a;
  undefined2 uStack_96;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined2 uStack_18;
  undefined2 uStack_16;
  undefined2 uStack_14;
  undefined2 uStack_12;
  undefined2 uStack_10;
  undefined2 uStack_e;
  undefined2 uStack_c;
  undefined2 uStack_a;
  undefined2 uStack_8;
  
  uStack_94 = DAT_2000a834;
  uStack_90 = DAT_2000a838;
  uStack_8c = DAT_2000a83c;
  uStack_88 = DAT_2000a840;
  uStack_84 = DAT_2000a844;
  uStack_80 = DAT_2000a848;
  uStack_7c = DAT_2000a84c;
  uStack_78 = DAT_2000a850;
  uStack_74 = DAT_2000a854;
  uStack_70 = DAT_2000a858;
  uStack_6c = DAT_2000a85c;
  uStack_68 = DAT_2000a860;
  uStack_64 = DAT_2000a864;
  uStack_5c = DAT_2000a86c;
  uStack_58 = DAT_2000a870;
  uStack_54 = DAT_2000a874;
  uStack_50 = DAT_2000a878;
  uStack_4c = DAT_2000a87c;
  uStack_48 = DAT_2000a880;
  uStack_44 = DAT_2000a884;
  uStack_40 = DAT_2000a888;
  uStack_3c = DAT_2000a88c;
  uStack_38 = DAT_2000a890;
  uStack_60 = DAT_2000a868;
  uStack_34 = DAT_2000a894;
  uStack_28 = DAT_2000a8a0;
  uStack_30 = DAT_2000a898;
  uStack_2c = DAT_2000a89c;
  uStack_24 = _DAT_2000a8a4;
  uStack_20 = DAT_2000a8a8;
  uStack_1c = _DAT_2000a8ac;
  uStack_18 = DAT_2000a8b0;
  uStack_a2 = DAT_2000a8b4 >> 0x10;
  uStack_14 = uStack_a2;
  uStack_9e = DAT_2000a8b8 >> 0x10;
  uStack_10 = uStack_9e;
  uStack_9a = DAT_2000a8bc >> 0x10;
  uStack_e = DAT_2000a8bc;
  uStack_c = uStack_9a;
  uStack_a = DAT_2000a8c0;
  uStack_96 = DAT_2000a8c0 >> 0x10;
  uStack_16 = DAT_2000a8b4;
  uStack_12 = DAT_2000a8b8;
  uStack_8 = uStack_96;
  HAL_FLASH_Write_Offset_0x96000(0x2000,&uStack_94,0x8e);
  return;
}




void FUN_08015ef0(void)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  
  cVar1 = DAT_200026b4;
  if (system_status_ != '\x05') {
    return;
  }
  if (DAT_200026b4 == '\0') {
    memcpy(&DAT_200026cc,&global_settings,0x154);
    DAT_200026c8 = cVar1;
    DAT_200026b4 = 1;
    global_settings = 1;
    acq_buffer_ready_flag_ = 1;
    DAT_200026c4 = 0;
    timebase_index_2_5ns_30_10s = DAT_200001c0;
    DAT_2000282c = 0;
    ch1_trigger_level_10uV_target_l = 0;
    ch1_trigger_level_10uV_target_h = 0;
    ch2_trigger_level_10uV_target_l = 0;
    ch2_trigger_level_10uV_target_h = 0;
    horiz_trigger_delay_ps_l = 0;
    horiz_trigger_delay_ps_h = 0;
    roll_mode_view_offset__l = 0;
    roll_mode_view_offset__h = 0;
    ch1_v_div_index = 4;
    DAT_2000a844 = 990000;
    DAT_2000a87c = 990000;
    DAT_2000a8b4 = 1000;
    DAT_2000a8b8 = 1000;
    DAT_2000a8bc = 1000;
    DAT_2000a8c0 = 1000;
    ch2_v_div_index = 4;
    DAT_2000a8c4 = cVar1;
    ch2_enabled = cVar1;
    ch1_coupling_0_dc_1_ac = cVar1;
    ch1_vert_offset_pixels = 0;
    ch2_coupling_dc_ac = cVar1;
    ch2_vert_offset_pixels = 0;
    puVar2 = &DAT_2000a8a4;
    iVar3 = 0xe;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    FUN_0801eff0(0xff);
    zw_timer_us(&DAT_200026b8,720000000);
    zw_timer_us(&DAT_20002820,10000000);
    zw_draw_popup_message("CALIB",5,540000,0,1);
    return;
  }
  iVar3 = FUN_080270a8(&DAT_200026b8);
  if (iVar3 != 0) {
    DAT_200026b4 = 0;
    memcpy(&global_settings,&DAT_200026cc,0x154);
    FUN_0801eff0(0xff);
    system_status_ = 1;
    zw_draw_popup_message("FAILED",6,2000,0,2);
    zw_power_on(100);
    return;
  }
  if (scan_mode__0_start_1_pretrigger_2_block_3_roll != '\0') {
    return;
  }
  if (trigger_armed_flag_ != '\x01') {
    return;
  }
  DAT_2000282c = DAT_2000282c + 1;
  if (DAT_2000282c < 10) {
    return;
  }
  if (false) {
    return;
  }
  switch(DAT_200026b4) {
  case '\x01':
    cVar1 = FUN_08015808();
    if (cVar1 == '\x02') {
      timebase_index_2_5ns_30_10s = DAT_200001c0;
      ch1_v_div_index = 4;
      DAT_2000a8c4 = 1;
      adc_interleaving_enable_ = 1;
      DAT_200026b4 = cVar1;
      FUN_0801eff0(0xff);
      DAT_2000282c = 0;
      printf_disabled_2("start chB: %d\r\n",1);
      return;
    }
    goto LAB_08016114;
  case '\x02':
    cVar1 = FUN_08015974();
    if (cVar1 == '\x02') {
      DAT_200026b4 = 3;
      ch2_enabled = 1;
      timebase_index_2_5ns_30_10s = DAT_200001c0;
      DAT_2000a8c4 = 0;
      FUN_0801eff0(0xff);
      DAT_2000282c = 0;
      printf_disabled_2("chB done: %d\r\n",1);
      return;
    }
LAB_08016114:
    if (cVar1 == '\x01') {
LAB_08016118:
      DAT_2000282c = 0;
    }
    break;
  case '\x03':
    cVar1 = FUN_08015a34();
    if (cVar1 != '\x02') goto LAB_08016114;
    DAT_200026b4 = '\x04';
    timebase_index_2_5ns_30_10s = DAT_200001c0;
    ch1_v_div_index = 4;
    ch2_v_div_index = 4;
    FUN_0801eff0(0xff);
    goto LAB_08016118;
  case '\x04':
    ch2_enabled = 0;
    ch1_vert_offset_pixels = 0x4b;
    ch1_v_div_index = 10;
    timebase_index_2_5ns_30_10s = DAT_200001c0;
    FUN_0801eff0(0xff);
    DAT_200026b4 = '\x05';
    break;
  case '\x05':
    iVar3 = FUN_08015b80();
    if (iVar3 != 0) {
      ch1_vert_offset_pixels = -0x4b;
      FUN_0801eff0(0xff);
      DAT_200026b4 = '\x06';
    }
    break;
  case '\x06':
    iVar3 = FUN_08015c14();
    if (iVar3 != 0) {
      ch2_enabled = 1;
      ch2_vert_offset_pixels = 0x4b;
      ch2_v_div_index = 10;
      timebase_index_2_5ns_30_10s = DAT_200001c0;
      FUN_0801eff0(0xff);
      DAT_200026b4 = '\a';
    }
    break;
  case '\a':
    iVar3 = FUN_08015ca8();
    if (iVar3 != 0) {
      DAT_2000a8c4 = 0;
      ch2_vert_offset_pixels = -0x4b;
      FUN_0801eff0(0xff);
      DAT_200026b4 = '\b';
    }
    break;
  case '\b':
    iVar3 = FUN_08015d3c();
    if (iVar3 != 0) {
      DAT_2000a8c4 = 0;
      FUN_0801eff0(0xff);
      DAT_200026b4 = '\t';
    }
    break;
  case '\t':
    DAT_200026b4 = '\0';
    memcpy(&global_settings,&DAT_200026cc,0x154);
    FUN_0801eff0(0xff);
    FUN_08015dd0();
    system_status_ = '\x01';
    zw_draw_popup_message("DONE",4,1000,0,3);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_080161f8(void)

{
  int iVar1;
  undefined1 *puVar2;
  short *psVar3;
  undefined4 *puVar4;
  short *psVar5;
  undefined4 local_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined2 uStack_18;
  undefined2 uStack_16;
  undefined2 uStack_14;
  undefined2 uStack_12;
  undefined2 uStack_10;
  undefined2 uStack_e;
  undefined2 uStack_c;
  undefined2 uStack_a;
  undefined2 uStack_8;
  
  psVar3 = &local_94;
  HAL_FLASH_Read_Offset_0x96000(0x2000,&local_94,0x8e);
  puVar4 = &DAT_2000a834;
  DAT_2000a834 = local_94;
  DAT_2000a838 = uStack_90;
  DAT_2000a83c = uStack_8c;
  DAT_2000a840 = uStack_88;
  DAT_2000a844 = uStack_84;
  DAT_2000a848 = uStack_80;
  DAT_2000a84c = uStack_7c;
  DAT_2000a850 = uStack_78;
  DAT_2000a854 = uStack_74;
  DAT_2000a858 = uStack_70;
  DAT_2000a85c = uStack_6c;
  DAT_2000a860 = uStack_68;
  DAT_2000a864 = uStack_64;
  DAT_2000a86c = uStack_5c;
  DAT_2000a868 = uStack_60;
  DAT_2000a870 = uStack_58;
  DAT_2000a874 = uStack_54;
  DAT_2000a878 = uStack_50;
  DAT_2000a87c = uStack_4c;
  DAT_2000a880 = uStack_48;
  DAT_2000a884 = uStack_44;
  DAT_2000a888 = uStack_40;
  DAT_2000a88c = uStack_3c;
  DAT_2000a890 = uStack_38;
  DAT_2000a894 = uStack_34;
  DAT_2000a898 = uStack_30;
  DAT_2000a89c = uStack_2c;
  DAT_2000a8a0 = uStack_28;
  _DAT_2000a8a4 = uStack_24;
  DAT_2000a8a8 = uStack_20;
  _DAT_2000a8ac = uStack_1c;
  DAT_2000a8b0 = uStack_18;
  DAT_2000a8b4 = CONCAT22(uStack_14,uStack_16);
  DAT_2000a8b8 = CONCAT22(uStack_10,uStack_12);
  DAT_2000a8bc = CONCAT22(uStack_c,uStack_e);
  DAT_2000a8c0 = CONCAT22(uStack_8,uStack_a);
  if (1000 < DAT_2000a8b4 - 500U) {
    iVar1 = 0xe;
    do {
      *puVar4 = 990000;
      puVar4[0xe] = 990000;
      puVar4 = puVar4 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    puVar2 = &DAT_2000a8a4;
    iVar1 = 0xe;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    DAT_2000a8b4 = 1000;
    DAT_2000a8bc = 1000;
    DAT_2000a8b8 = 1000;
    DAT_2000a8c0 = 1000;
  }
  HAL_FLASH_Read_Offset_0x96000(0x2400,&local_94,0x30);
  psVar5 = &DAT_2001de34;
  iVar1 = 0xc;
  do {
    if (*psVar3 - 4000U < 0x9c5) {
      *psVar5 = *psVar3;
    }
    else {
      *psVar5 = 5000;
    }
    psVar3 = psVar3 + 1;
    psVar5 = psVar5 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}




uint FUN_08016368(uint param_1)

{
  if (DAT_2001de0a == '\x01') {
    if (param_1 == 0) {
      return 0;
    }
    if ((param_1 & 0xfd) == 0x21) {
      ch1_gain_cal_ = ch1_gain_cal_ + 1;
    }
    else {
      if ((param_1 == 0x22) || (param_1 == 0x24)) {
        ch1_gain_cal_ = ch1_gain_cal_ + -1;
      }
      if (param_1 == 3) {
        ch2_gain_cal_ = ch2_gain_cal_ + 1;
        return 0;
      }
    }
    if (param_1 == 4) {
      ch2_gain_cal_ = ch2_gain_cal_ + -1;
      param_1 = 0;
    }
    else {
      if ((param_1 - 1 & 0xff) < 2) {
        DAT_2001de0a = '\0';
        if (param_1 == 2) {
          if (frequency_meter_enable != 0) {
            FUN_08024f0c();
          }
          zw_save_settings_(0x1000);
          zw_draw_popup_message(" OK ",4,100,0,1);
          return 0;
        }
      }
      else {
        if (param_1 != 0x14) {
          return 0;
        }
        DAT_2001de0a = '\0';
        ch1_gain_cal_ = 1000;
        ch2_gain_cal_ = 1000;
        zw_save_settings_(0x1000);
      }
      zw_draw_popup_message("Exit",4,100,0,1);
      param_1 = 0;
    }
  }
  return param_1;
}




uint FUN_08016450(uint param_1)

{
  int *piVar1;
  int iVar2;
  
  if (DAT_2001de0a != '\x02') {
    return param_1;
  }
  if (param_1 == 0) {
    return 0;
  }
  if ((param_1 & 0xfd) == 0x21) {
    piVar1 = &DAT_2000a834;
    iVar2 = 0xe;
    do {
      *piVar1 = *piVar1 + 200;
      piVar1 = piVar1 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  else {
    if ((param_1 == 0x22) || (param_1 == 0x24)) {
      piVar1 = &DAT_2000a834;
      iVar2 = 0xe;
      do {
        *piVar1 = *piVar1 + -200;
        piVar1 = piVar1 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    if (param_1 == 3) {
      piVar1 = &DAT_2000a86c;
      iVar2 = 0xe;
      do {
        *piVar1 = *piVar1 + 200;
        piVar1 = piVar1 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
      goto LAB_08016490;
    }
  }
  if (param_1 != 4) {
    FUN_080251e4();
    FUN_080252e4();
    if (1 < (param_1 - 1 & 0xff)) {
      return 0;
    }
    DAT_2001de0a = 0;
    if (param_1 == 2) {
      FUN_08015dd0();
      zw_draw_popup_message(" OK ",4,100,0,1);
    }
    else {
      zw_draw_popup_message("Exit",4,100,0,1);
    }
    return 0;
  }
  piVar1 = &DAT_2000a86c;
  iVar2 = 0xe;
  do {
    *piVar1 = *piVar1 + -200;
    piVar1 = piVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
LAB_08016490:
  FUN_080251e4();
  FUN_080252e4();
  return 0;
}




uint FUN_08016534(uint param_1)

{
  if (DAT_2001de0a != '\x03') {
    return param_1;
  }
  if (param_1 == 0) {
    return 0;
  }
  if ((param_1 & 0xfd) == 0x21) {
    (&DAT_2000a834)[ch1_v_div_index] = (&DAT_2000a834)[ch1_v_div_index] + 200;
  }
  else {
    if ((param_1 == 0x22) || (param_1 == 0x24)) {
      (&DAT_2000a834)[ch1_v_div_index] = (&DAT_2000a834)[ch1_v_div_index] + -200;
    }
    if (param_1 == 3) {
      (&DAT_2000a834)[ch2_v_div_index + 0xe] = (&DAT_2000a834)[ch2_v_div_index + 0xe] + 200;
      goto LAB_08016576;
    }
  }
  if (param_1 != 4) {
    FUN_080251e4();
    FUN_080252e4();
    if (1 < (param_1 - 1 & 0xff)) {
      return 0;
    }
    DAT_2001de0a = 0;
    if (param_1 == 2) {
      FUN_08015dd0();
      zw_draw_popup_message(" OK ",4,100,0,1);
    }
    else {
      zw_draw_popup_message("Exit",4,100,0,1);
    }
    return 0;
  }
  (&DAT_2000a834)[ch2_v_div_index + 0xe] = (&DAT_2000a834)[ch2_v_div_index + 0xe] + -200;
LAB_08016576:
  FUN_080251e4();
  FUN_080252e4();
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void zw_cursor_init(void)

{
  _DAT_20002852 = 0x18;
  DAT_2000285b = 2;
  DAT_20002850 = 0x1d;
  DAT_20002858 = 3;
  DAT_20002854 = 0xd;
  DAT_20002856 = 0;
  DAT_2000285c = 0;
  DAT_2000285d = 1;
  DAT_20002845 = 1;
  DAT_20002838 = 0x1d;
  DAT_2000283a = 0x26;
  DAT_20002840 = 3;
  DAT_2000283c = 0xd;
  DAT_2000283e = 0;
  DAT_20002843 = 1;
  DAT_20002844 = 0;
  DAT_20002868 = 0x25;
  DAT_2000286a = 0x34;
  DAT_20002870 = 3;
  DAT_2000286c = 0x3a;
  DAT_2000286e = 0;
  DAT_20002873 = 0;
  DAT_20002874 = 0;
  DAT_20002875 = 1;
  DAT_2001de22 = 0x55;
  _DAT_20002886 = 0;
  DAT_2000288c = 0;
  DAT_20002880 = 0x55;
  DAT_20002882 = 0x12;
  DAT_20002888 = 3;
  DAT_20002884 = 3;
  DAT_2000288b = 1;
  cursor_x1_position = 0xff97;
  cursor_x2_position = 0x69;
  cursor_y1_position = 0x55;
  cursor_y2_position = 0xffab;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_080166cc(int param_1)

{
  short sVar1;
  
  if (param_1 != 0) {
    if (fft_mode_0_off_1_log_2_lin_3_music == '\0') {
      if ((_fft_mode_0_off_1_log_2_lin_3_music & 0xffffff00) != 0) {
        if (param_1 == 0x2c) {
          if (cursor_x1_position < 0x94) {
            cursor_x1_position = cursor_x1_position + 1;
          }
          else {
            cursor_x1_position = 0x94;
          }
        }
        else if (param_1 == 0x2b) {
          if (cursor_x1_position < -0x93) {
            cursor_x1_position = -0x94;
          }
          else {
            cursor_x1_position = cursor_x1_position + -1;
          }
        }
        else if (param_1 == 0x30) {
          if (cursor_x2_position < 0x94) {
            cursor_x2_position = cursor_x2_position + 1;
          }
          else {
            cursor_x2_position = 0x94;
          }
        }
        else if (param_1 == 0x2f) {
          if (cursor_x2_position < -0x93) {
            cursor_x2_position = -0x94;
          }
          else {
            cursor_x2_position = cursor_x2_position + -1;
          }
        }
        else if (param_1 == 0x29) {
          if (cursor_y1_position < 0x62) {
            cursor_y1_position = cursor_y1_position + 1;
          }
          else {
            cursor_y1_position = 0x62;
          }
        }
        else if (param_1 == 0x2a) {
          if (cursor_y1_position < -0x61) {
            cursor_y1_position = -0x62;
          }
          else {
            cursor_y1_position = cursor_y1_position + -1;
          }
        }
        else if (param_1 == 0x2d) {
          if (cursor_y2_position < 0x62) {
            cursor_y2_position = cursor_y2_position + 1;
          }
          else {
            cursor_y2_position = 0x62;
          }
        }
        else if (param_1 == 0x2e) {
          if (cursor_y2_position < -0x61) {
            cursor_y2_position = -0x62;
          }
          else {
            cursor_y2_position = cursor_y2_position + -1;
          }
        }
      }
    }
    else if ((param_1 - 3U & 0xff) < 2) {
      sVar1 = -1;
      if (param_1 == 4) {
        sVar1 = 1;
      }
      DAT_2001de22 = sVar1 + DAT_2001de22;
      if (DAT_2001de22 < 1) {
        DAT_2001de22 = 1;
      }
      else if (0x12a < DAT_2001de22) {
        DAT_2001de22 = 0x12a;
      }
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Restarted to delay deadcode elimination for space: register


void zw_scope_cursor_measurements_window(void)

{
  undefined1 uVar1;
  ulonglong uVar2;
  longlong lVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int32_t iVar12;
  
  if ((_fft_mode_0_off_1_log_2_lin_3_music & 0xff) == 0) {
    if ((_fft_mode_0_off_1_log_2_lin_3_music & 0xffffff00) != 0) {
      iVar8 = 6;
      if (settings_ch2_color_0_green_1_purple_2_cyan != '\0') {
        iVar8 = 3;
      }
      zw_draw_rectangle_filled(0xb,0x13,0x55,0x4c);
      zw_draw_rectangle(10,0x12,0x57,0x4e);
      if (cursors_x_enable != '\0') {
        zw_draw_line_vertical_dashed(cursor_x1_position + 0xa0,0x12,200,iVar8);
        zw_draw_line_vertical_dashed(cursor_x2_position + 0xa0,0x12,200,iVar8);
        iVar9 = cursor_x2_position;
        iVar4 = cursor_x1_position;
        uVar6 = iVar9 - iVar4;
        if (iVar9 < iVar4) {
          uVar6 = iVar4 - iVar9;
        }
        if (uVar6 == 0) {
          uVar6 = 1;
        }
        iVar4 = timebase_val_ns_h;
        uVar10 = timebase_val_ns_l;
        if (DAT_2001de15 != '\0') {
          iVar4 = *(&DAT_08055900 + zoom_timebase_index_ * 8);
          uVar10 = *(&DAT_080558fc + zoom_timebase_index_ * 8);
        }
        iVar4 = (uVar10 * uVar6 >> 0x20) + uVar6 * iVar4 + uVar10 * (uVar6 >> 0x1f);
        uVar6 = __divdi3(uVar10 * uVar6,iVar4,0x19);
        DAT_20002848 = uVar6 * 1000;
        DAT_2000284c = (uVar6 * 1000 >> 0x20) + iVar4 * 1000;
        zw_scope_int_values(DAT_20002848,DAT_2000284c,_DAT_20002850,_DAT_20002854);
        uVar5 = 0xde0b6b3;
        DAT_20002830 = __divdi3(0,0xde0b6b3,DAT_20002848,DAT_2000284c);
        DAT_20002834 = uVar5;
        zw_scope_int_values();
        zw_draw_string_small("T:",0xd,_DAT_20002852,2);
        zw_draw_string_small("F:",0xd,DAT_2000283a,2);
      }
      if (cursors_y_enable != '\0') {
        zw_draw_line_horizontal_dashed(10,0x76 - cursor_y1_position,300,iVar8);
        zw_draw_line_horizontal_dashed(10,0x76 - cursor_y2_position,300,iVar8);
        iVar9 = cursor_y1_position;
        iVar4 = cursor_y2_position;
        iVar11 = (iVar4 < iVar9) * iVar9 + (iVar4 >= iVar9) * iVar4;
        iVar8 = (iVar4 < iVar9) * iVar8 + (iVar4 >= iVar9) * iVar9;
        if (active_channel_0_ch1_1_ch2_2_math == '\0') {
          _DAT_2000286c = CONCAT22(DAT_2000286e,0x3a);
          iVar12 = ch1_vert_offset_pixels;
          iVar4 = ch1_volt_scale_10uV;
          uVar1 = ch1_probe_mode_0_x1_1_x10_2_x100;
        }
        else {
          _DAT_2000286c = CONCAT22(DAT_2000286e,0x5a);
          iVar12 = ch2_vert_offset_pixels;
          iVar4 = ch2_volt_scale_10uV;
          uVar1 = ch2_probe_mode;
        }
        _DAT_20002870 = CONCAT12(uVar1,DAT_20002870);
        DAT_20002860 = ((iVar11 - iVar12) * iVar4) / 0x19;
        _DAT_20002868 = CONCAT22(DAT_2000283a + 0xe,DAT_20002868);
        DAT_20002864 = DAT_20002860 >> 0x1f;
        zw_scope_int_values(DAT_20002860,DAT_20002864,_DAT_20002868,_DAT_2000286c);
        zw_draw_string_small("Y1:",0xc,DAT_2000286a,3);
        DAT_20002860 = ((iVar8 - iVar12) * iVar4) / 0x19;
        _DAT_20002868 = CONCAT22(DAT_2000286a + 0xe,DAT_20002868);
        DAT_20002864 = DAT_20002860 >> 0x1f;
        zw_scope_int_values(DAT_20002860,DAT_20002864,_DAT_20002868,_DAT_2000286c);
        zw_draw_string_small("Y2:",0xc,DAT_2000286a,3);
        DAT_20002860 = ((iVar11 - iVar8) * iVar4) / 0x19;
        _DAT_20002868 = CONCAT22(DAT_2000286a + 0xe,DAT_20002868);
        DAT_20002864 = DAT_20002860 >> 0x1f;
        zw_scope_int_values(DAT_20002860,DAT_20002864,_DAT_20002868,_DAT_2000286c);
        zw_draw_string_small("dY:",0xc,DAT_2000286a,3);
        return;
      }
    }
  }
  else {
    if (DAT_2001de22 < 0x105) {
      sVar7 = DAT_2001de22 + 1;
    }
    else {
      sVar7 = DAT_2001de22 + -0x28;
    }
    _DAT_20002880 = CONCAT22(DAT_20002882,sVar7);
    uVar6 = DAT_2001de22 + 1;
    uVar2 = DAT_2001dccc * uVar6;
    lVar3 = (uVar2 & 0xffffffff) * 1000000;
    uVar5 = lVar3;
    iVar8 = (lVar3 >> 0x20) + ((uVar2 >> 0x20) + (uVar6 >> 0x1f) * DAT_2001dccc) * 1000000;
    lVar3 = CONCAT44(iVar8,uVar5);
    if (iVar8 < 0) {
      lVar3 = CONCAT44(iVar8,uVar5) + 0x3ff;
    }
    DAT_20002878 = lVar3 >> 10;
    DAT_2000287c = (lVar3 >> 10) >> 0x20;
    zw_draw_line_vertical_dashed(DAT_2001de22 + 0xb,0x12,0x96,3);
    zw_scope_int_values(DAT_20002878,DAT_2000287c,_DAT_20002880,_DAT_20002884);
  }
  return;
}




void zw_fpga_all_reset(void)

{
  zw_SPI_Transmit__FUN_080267ac(1);
  return;
}




void FUN_08016ba0(void)

{
  zw_SPI_Transmit__FUN_080267ac(1,2);
  return;
}




void FUN_08016bac(void)

{
  DAT_2000289c = DAT_2000289c & 0xb8 | ch2_enabled | trigger_mode_0_auto_1_normal << 6 | roll_mode_enable << 2;
  zw_SPI_Transmit__FUN_080267ac(2);
  return;
}




void FUN_08016be4(char param_1)

{
  DAT_2000289c = DAT_2000289c & 0x7f | param_1 << 7;
  zw_SPI_Transmit__FUN_080267ac(2);
  return;
}




void FUN_08016c04(void)

{
  zw_SPI_Transmit__FUN_080267ac(1,2);
  zw_SPI_Transmit__FUN_080267ac(1,4);
  return;
}




void FUN_08016c18(char param_1)

{
  DAT_2000289c = DAT_2000289c & 0xef | param_1 << 4;
  zw_SPI_Transmit__FUN_080267ac(2);
  zw_SPI_Transmit__FUN_080267ac(1,8);
  return;
}




void FUN_08016c3c(undefined4 param_1)

{
  zw_SPI_Transmit__FUN_080267ac(0x1a,param_1);
  return;
}




void zw_power_control_(int param_1)

{
  DAT_2000289d = DAT_2000289d & 0xfe;
  if (param_1 != 0) {
    DAT_2000289d = DAT_2000289d | 1;
    zw_SPI_Transmit__FUN_080267ac(6);
    zw_HAL_PWM_Start_wrapper__FUN_0802c1f4();
    return;
  }
  zw_SPI_Transmit__FUN_080267ac(6);
  zw_HAL_PWM_Stop_wrapper__FUN_0802c204();
  return;
}




void zw_power_on(int param_1)

{
  if (key_beep_enable == '\0') {
    return;
  }
  zw_power_control_(1);
  DAT_200028a4 = 1;
  zw_timer_us(&DAT_20002890,param_1 * 1000);
  return;
}




void FUN_08016cb4(void)

{
  int iVar1;
  
  if ((DAT_200028a4 != '\0') && (iVar1 = FUN_080270a8(&DAT_20002890), iVar1 != 0)) {
    zw_power_control_(0);
    DAT_200028a4 = 0;
    return;
  }
  return;
}




void FUN_08016ce0(void)

{
  zw_SPI_Transmit__FUN_080267ac(1,0x100);
  return;
}




void FUN_08016cf0(int param_1)

{
  DAT_200028a0 = DAT_200028a0 & 0xfffeffff | param_1 << 0x10;
  zw_SPI_Transmit__FUN_080267ac(0x17);
  return;
}




void FUN_08016d0c(void)

{
  FUN_080267f0(0x18);
  return;
}




void FUN_08016d18(void)

{
  DAT_200028a0 = DAT_200028a0 & 0xfffeffff;
  zw_SPI_Transmit__FUN_080267ac(0x17);
  zw_SPI_Transmit__FUN_080267ac(1,0x200);
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


undefined4 FUN_08016d38(undefined4 *param_1)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  
  uVar2 = FUN_080267f0(0xf);
  if ((uVar2 & 8) != 0) {
    return 0;
  }
  iVar3 = FUN_080267f0(0x18);
  uVar4 = FUN_080267f0(0x19);
  printf_disabled_1("counter=%d\n",iVar3);
  printf_disabled_1("timeCnt=%d\n",uVar4);
  if ((iVar3 == 0) || (uVar4 == 0)) {
    return 2;
  }
  lVar1 = ((CONCAT44(uVar4 >> 0x1b,uVar4 << 5) - (CONCAT44(uVar2,uVar4) & 0x8ffffffff)) * 4 + (CONCAT44(uVar2,uVar4) & 0x8ffffffff)) * 0x1900;
  iVar6 = lVar1 >> 0x20;
  uVar2 = __divdi3(lVar1,iVar6,iVar3,0);
  iVar3 = iVar6;
  uVar5 = __divdi3();
  printf_disabled_1("period=%d\n",uVar5);
  if (iVar6 == 0 && uVar2 == 0) {
    return 2;
  }
  if (iVar6 < 1) {
    if ((iVar6 != 0) || (uVar2 < 100000000)) {
      iVar3 = 0xde0b6b3;
      uVar2 = __divdi3(0,0xde0b6b3,uVar2,iVar6);
      uVar5 = uVar2 * 100;
      iVar7 = (uVar2 * 100 >> 0x20) + iVar3 * 100;
      *param_1 = uVar5;
      param_1[1] = iVar7;
      goto LAB_08016e28;
    }
    if (uVar2 < 1000000000) {
      uVar5 = __divdi3(uVar2,0,10,0);
      iVar3 = 0xde0b6b3;
      uVar2 = __divdi3(0,0xde0b6b3,uVar5,iVar6);
      uVar5 = uVar2 * 10;
      iVar7 = (uVar2 * 10 >> 0x20) + iVar3 * 10;
      *param_1 = uVar5;
      param_1[1] = iVar7;
      goto LAB_08016e28;
    }
  }
  if ((iVar6 < 3) && ((iVar6 != 2 || (uVar2 < 0x540be400)))) {
    uVar5 = __divdi3(uVar2,iVar6,100,0);
    iVar7 = 0xde0b6b3;
    uVar5 = __divdi3(0,0xde0b6b3,uVar5,iVar6);
    *param_1 = uVar5;
    param_1[1] = iVar7;
  }
  else if ((iVar6 < 0x18) && ((iVar6 != 0x17 || (uVar2 < 0x4876e800)))) {
    iVar7 = 0x1634578;
    uVar5 = __divdi3(0,0x1634578,uVar5,iVar3);
    *param_1 = uVar5;
    param_1[1] = iVar7;
  }
  else {
    uVar5 = __divdi3(uVar2,iVar6,10000,0);
    iVar7 = 0x2386f2;
    uVar5 = __divdi3(0,0x2386f2,uVar5,iVar6);
    *param_1 = uVar5;
    param_1[1] = iVar7;
  }
LAB_08016e28:
  uVar5 = __divdi3(uVar5,iVar7,1000,0);
  printf_disabled_1("freq=%d\n",uVar5);
  return 1;
}




void FUN_08016f1c(int param_1,uint param_2)

{
  DAT_200028a0 = param_2 | param_1 << 8;
  zw_SPI_Transmit__FUN_080267ac(0x17);
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void zw_siggen_freq_duty(int freq,uint duty)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = freq >> 4;
  iVar2 = iVar4;
  __divdi3(freq << 0x1c,iVar4,125000000,0);
  uVar1 = __moddi3();
  iVar5 = 1;
  if ((iVar2 < 1) && ((iVar2 != 0 || (uVar1 < 3)))) {
    iVar5 = 0;
  }
  iVar2 = __divdi3(freq << 0x1c,iVar4,1250000000,0);
  zw_SPI_Transmit__FUN_080267ac(0x10,iVar2 + iVar5);
  printf_disabled_2("WAVE_FREQ_WORD= %d\r\n",iVar2 + iVar5);
  uVar3 = __divdi3(duty << 0x1c,duty >> 4,1000,0);
  zw_SPI_Transmit__FUN_080267ac(0x11,uVar3);
  return;
}




void FUN_08016fb8(undefined4 *param_1)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  bVar1 = DAT_2000289d >> 1;
  DAT_2000289d = DAT_2000289d & 0xfd | 4;
  puVar3 = param_1 + 0x80;
  zw_SPI_Transmit__FUN_080267ac(6);
  do {
    uVar2 = *param_1;
    param_1 = param_1 + 2;
    zw_SPI_Transmit__FUN_080267ac(0x10,uVar2);
  } while (param_1 != puVar3);
  DAT_2000289d = (bVar1 & 1) * '\x02' | DAT_2000289d & 0xfb;
  zw_SPI_Transmit__FUN_080267ac(6);
  zw_siggen_freq_duty(siggen_frequency_0_1hz,siggen_duty_cycle_0_1_);
  return;
}




void zw_siggen_enable_(int param_1)

{
  undefined1 auStack_404 [1024];
  
  if (param_1 != 0) {
    DAT_2000289d = DAT_2000289d | 2;
    zw_SPI_Transmit__FUN_080267ac(6);
    return;
  }
  memset(auStack_404,0,0x400);
  FUN_08016fb8(auStack_404);
  DAT_2000289d = DAT_2000289d & 0xfd;
  zw_SPI_Transmit__FUN_080267ac(6);
  return;
}




void FUN_0801705c(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = sample_rate_hz_h;
  uVar2 = sample_rate_hz_l;
  if (ch2_enabled == '\0') {
    uVar1 = __divdi3(250000000,0,sample_rate_hz_l,sample_rate_hz_h);
    uVar2 = __divdi3(uVar2,uVar4,10,0);
    iVar3 = __divdi3(250000000,0,uVar2,uVar4);
    if (uVar1 != 1) {
      if (iVar3 == 0x19) {
        uVar1 = 0x9400063;
      }
      else if (uVar1 == 2) {
        uVar1 = 0x8c00063;
      }
      else if (uVar1 == 5) {
        uVar1 = 0xa400063;
      }
      else if (uVar1 == 0x19) {
        uVar1 = 0xc400063;
      }
      else if ((uVar1 & 1) == 0) {
        if (uVar1 - 25000 < 2) {
          uVar1 = 0x541869;
        }
        else if (uVar1 < 0x2712) {
          uVar1 = (uVar1 >> 1) - 1 | 0x400000;
        }
        else {
          uVar1 = uVar1 / 2000 | 0x400000;
        }
      }
      else {
        uVar1 = uVar1 | 0x8400000;
      }
      goto LAB_080170de;
    }
  }
  else if (ch2_enabled == '\x01') {
    uVar1 = __divdi3(125000000,0,sample_rate_hz_l,sample_rate_hz_h);
    uVar2 = __divdi3(uVar2,uVar4,10,0);
    iVar3 = __divdi3(125000000,0,uVar2,uVar4);
    if (uVar1 != 1) {
      if (iVar3 == 0x19) {
        uVar1 = 0xa400005;
      }
      else if (uVar1 < 0x1389) {
        uVar1 = uVar1 - 1 | 0x400000;
      }
      else {
        uVar1 = uVar1 / 1000 | 0x400000;
      }
      goto LAB_080170de;
    }
  }
  uVar1 = 0;
LAB_080170de:
  zw_SPI_Transmit__FUN_080267ac(7,uVar1);
  return;
}




void FUN_08017190(void)

{
  uint16_t uVar1;
  int iVar2;
  uint16_t uVar3;
  int iVar4;
  
  if (trigger_edge_0_rise_1_fall == 0) {
    uVar1 = trigger_level_raw_adc__0_255 - 10;
    uVar3 = trigger_level_raw_adc__0_255;
  }
  else {
    uVar3 = trigger_level_raw_adc__0_255 + 10;
    uVar1 = trigger_level_raw_adc__0_255;
  }
  iVar4 = uVar3;
  iVar2 = uVar1;
  iVar2 = (iVar2 < 8) * 8 + (iVar2 >= 8) * iVar2;
  iVar4 = (iVar4 < 8) * 8 + (iVar4 >= 8) * iVar4;
  zw_SPI_Transmit__FUN_080267ac
            (5,(iVar2 < 0xfa) * iVar2 + (iVar2 >= 0xfa) * 0xfa | trigger_source_0_ch1_1_ch2 << 0x10 | trigger_edge_0_rise_1_fall << 0x11 |
               ((iVar4 < 0xfa) * iVar4 + (iVar4 >= 0xfa) * 0xfa) * 0x100);
  return;
}




void FUN_080171e4(void)

{
  if (ch2_enabled != '\x01') {
    zw_SPI_Transmit__FUN_080267ac(0xe,pre_trigger_samples_ + 0x400);
    return;
  }
  zw_SPI_Transmit__FUN_080267ac(0xe,pre_trigger_samples_ * 2 + 0x400);
  return;
}




void FUN_08017210(void)

{
  if (ch2_enabled != '\x01') {
    zw_SPI_Transmit__FUN_080267ac(8,post_trigger_samples_ + 0x400);
    return;
  }
  zw_SPI_Transmit__FUN_080267ac(8,post_trigger_samples_ * 2 + 0x400);
  return;
}




void FUN_0801723c(void)

{
  FUN_08016bac();
  FUN_0801705c();
  FUN_08017190();
  FUN_080171e4();
  FUN_08017210();
  FUN_08016c04();
  return;
}




void FUN_08017258(void)

{
  zw_SPI_Transmit__FUN_080267ac(1,0x80);
  return;
}




void FUN_08017264(void)

{
  zw_SPI_Transmit__FUN_080267ac(1,0x40);
  return;
}




int FUN_08017270(void)

{
  int iVar1;
  
  iVar1 = FUN_080267f0(9);
  if ((roll_mode_enable == '\0') && (iVar1 = iVar1 + -4, iVar1 < 0)) {
    iVar1 = iVar1 + DAT_200001c8;
  }
  if (ch2_enabled == '\x01') {
    return iVar1 / 2;
  }
  return iVar1;
}




void FUN_080172b0(undefined1 *param_1,undefined1 *param_2)

{
  undefined2 uVar1;
  
  uVar1 = FUN_080267f0(0x12);
  *param_1 = uVar1 >> 8;
  *param_2 = uVar1;
  return;
}




void FUN_080172c4(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_080267f0(0x14);
  *param_1 = uVar1;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_080172d4(char param_1)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar2 = buffer_pointer_ - buffer_trigger_index_;
  if (global_settings == 0) {
    if (roll_mode_enable != '\0') {
      if (roll_direction_0_left_1_right == '\0') {
        if (block_mode_enable_ == '\0') {
          uVar2 = (-1 < uVar2) * uVar2;
          goto LAB_08017304;
        }
      }
      else {
        uVar2 = pre_trigger_samples_ - buffer_trigger_index_;
      }
    }
  }
  else if ((roll_mode_enable != '\0') && (block_mode_enable_ == '\0')) {
    uVar2 = 0;
    goto LAB_08017304;
  }
  if (uVar2 < 0) {
    uVar2 = uVar2 + hw_buffer_wrap_addr_;
  }
  else if (hw_buffer_wrap_addr_ <= uVar2) {
    uVar2 = uVar2 - hw_buffer_wrap_addr_;
  }
LAB_08017304:
  fVar1 = _global_settings;
  if (ch2_enabled == '\x01') {
    uVar2 = uVar2 * 2 & 0x7ffff;
  }
  else {
    uVar2 = uVar2 & 0x7ffff;
    if (ch2_enabled == '\0') {
      fVar1 = _global_settings * 0.0;
    }
  }
  iVar5 = fVar1 - 0.0;
  uVar4 = roll_draw_cursor_x_;
  uVar3 = roll_split_index_;
  DAT_2000289c = DAT_2000289c & 0xf7 | param_1 << 3;
  zw_SPI_Transmit__FUN_080267ac(2,DAT_2000289c,0);
  zw_SPI_Transmit__FUN_080267ac(3,uVar2);
  zw_SPI_Transmit__FUN_080267ac(0xb,iVar5);
  zw_SPI_Transmit__FUN_080267ac(0xc,(uVar4 - uVar3) + 1);
  zw_SPI_Transmit__FUN_080267ac(1,0x10);
  return;
}




uint FUN_080173d4(void)

{
  uint uVar1;
  
  uVar1 = FUN_080267f0(0xf);
  return uVar1 & 1;
}




uint FUN_080173e4(void)

{
  uint uVar1;
  
  uVar1 = FUN_080267f0(0xf);
  return uVar1 >> 1 & 1;
}




void FUN_080173f4(int param_1,uint param_2,uint param_3,int param_4,int param_5)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  
  if (ch2_enabled == '\x01') {
    if (param_4 == 0) {
      bVar2 = 8;
      param_2 = param_2 * 2;
    }
    else {
      bVar2 = 0;
      param_2 = param_2 * 2;
    }
  }
  else {
    bVar2 = 0;
  }
  uVar3 = param_3 / 1000;
  zw_SPI_Transmit__FUN_080267ac(0x16,param_5 + -1);
  zw_SPI_Transmit__FUN_080267ac(3,param_2);
  DAT_2000289c = DAT_2000289c & 0xf7 | bVar2 | 0x20;
  zw_SPI_Transmit__FUN_080267ac(2);
  FUN_08027040((param_2 & 0x3ff) / 0x32 + param_5 * 0x14);
  FUN_08026890();
  if (uVar3 != 0) {
    iVar1 = param_1;
    do {
      zw_SPI_Receive_FUN_080268b8(iVar1,1000);
      iVar1 = iVar1 + 1000;
      FUN_08027040(param_5 * 0x14);
    } while (param_1 + uVar3 * 1000 != iVar1);
  }
  if (param_3 % 1000 != 0) {
    zw_SPI_Receive_FUN_080268b8(param_1 + uVar3 * 1000,param_3 % 1000);
  }
  FUN_080268d0();
  DAT_2000289c = DAT_2000289c & 0xdf;
  zw_SPI_Transmit__FUN_080267ac(2);
  return;
}




void zw_gray_init(void)

{
  DAT_20019ca0._0_1_ = 0;
  DAT_20019ca2 = 0x3f;
  DAT_2001a15c._0_1_ = 1;
  DAT_2001a15e = 0x5f;
  DAT_200197e6 = 0x3f;
  DAT_200197e4 = 0;
  DAT_2001932e = 0x5f;
  DAT_2001932c = 1;
  return;
}




void FUN_08017510(int param_1,int param_2)

{
  byte *pbVar1;
  byte bVar2;
  uint32_t Size;
  char cVar3;
  byte bVar4;
  int iVar5;
  byte *pbVar6;
  char *pcVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  uint uVar11;
  uint uVar12;
  byte abStack_4cc [600];
  byte abStack_274 [600];
  
  uVar11 = roll_draw_cursor_x_;
  uVar12 = roll_split_index_;
  FUN_080172d4(0);
  zw_timer_us(&DAT_20002a3c,1000000);
  while (iVar5 = FUN_080173e4(), iVar5 == 0) {
    FUN_08027040(1);
    iVar5 = FUN_080270a8(&DAT_20002a3c);
    if (iVar5 != 0) {
      printf_disabled_1("read maxmin1 error!!!!!\r\n");
      return;
    }
  }
  Size = ((uVar11 - uVar12) + 1) * 2;
  FUN_08026840(abStack_4cc + roll_split_index_ * 2,Size);
  FUN_080172d4(1);
  while (iVar5 = FUN_080173e4(), iVar5 == 0) {
    FUN_08027040(1);
    iVar5 = FUN_080270a8(&DAT_20002a3c);
    if (iVar5 != 0) {
      printf_disabled_2("read maxmin2 Error error error!!!!!\r\n");
      return;
    }
  }
  FUN_08026840(abStack_274 + roll_split_index_ * 2,Size);
  cVar3 = DAT_2000a8c4;
  if (ch2_enabled == '\0') {
    uVar11 = roll_split_index_;
    if (system_status_ == '\x05') {
      uVar12 = roll_draw_cursor_x_;
      if (uVar12 < uVar11) {
        return;
      }
      pbVar6 = uVar11 + 0x25e + param_1;
      pbVar10 = abStack_4cc + uVar11 * 2;
      pbVar8 = abStack_274 + uVar11 * 2;
      do {
        if (cVar3 == '\0') {
          *pbVar6 = pbVar8[1];
          bVar4 = *pbVar8;
        }
        else {
          *pbVar6 = pbVar10[1];
          bVar4 = *pbVar10;
        }
        pbVar10 = pbVar10 + 2;
        pbVar6[300] = bVar4;
        pbVar8 = pbVar8 + 2;
        pbVar6 = pbVar6 + 1;
      } while (pbVar10 != abStack_4cc + (uVar12 + 1) * 2);
      return;
    }
    uVar12 = roll_draw_cursor_x_;
    if (uVar12 < uVar11) {
      return;
    }
    pbVar8 = abStack_4cc + uVar11 * 2;
    pbVar6 = abStack_274 + uVar11 * 2;
    pcVar7 = param_1 + uVar11 + 0x25e;
    do {
      bVar2 = pbVar6[1];
      bVar4 = pbVar8[1];
      *pcVar7 = (bVar4 < bVar2) * bVar2 + (bVar4 >= bVar2) * bVar4;
      bVar4 = *pbVar8;
      pbVar8 = pbVar8 + 2;
      bVar2 = *pbVar6;
      pcVar7[300] = (bVar4 < bVar2) * bVar4 + (bVar4 >= bVar2) * bVar2;
      pbVar6 = pbVar6 + 2;
      pcVar7 = pcVar7 + 1;
    } while (pbVar8 != abStack_4cc + (uVar12 + 1) * 2);
    return;
  }
  uVar11 = roll_split_index_;
  uVar12 = roll_draw_cursor_x_;
  if (uVar12 < uVar11) {
    return;
  }
  pbVar9 = abStack_274 + uVar11 * 2;
  pbVar10 = abStack_4cc + uVar11 * 2;
  pbVar8 = param_1 + uVar11 + 0x25e;
  pbVar6 = uVar11 + 0x25e + param_2;
  do {
    pbVar8[300] = *pbVar9;
    pbVar1 = pbVar9 + 1;
    pbVar9 = pbVar9 + 2;
    *pbVar8 = *pbVar1;
    pbVar8 = pbVar8 + 1;
    pbVar6[300] = *pbVar10;
    *pbVar6 = pbVar10[1];
    pbVar6 = pbVar6 + 1;
    pbVar10 = pbVar10 + 2;
  } while (pbVar9 != abStack_274 + (uVar12 + 1) * 2);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_080176cc(int param_1,int param_2)

{
  byte bVar1;
  float fVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  
  if (fast_render_flag_ == '\0') {
    FUN_08018d24();
  }
  else {
    generate_interpolated__FUN_08019078();
  }
  fVar2 = _global_settings;
  uVar8 = roll_split_index_;
  uVar13 = roll_draw_cursor_x_;
  if (uVar8 <= uVar13) {
    param_1 = param_1 + uVar8;
    cVar3 = ch2_enabled;
    param_2 = param_2 + uVar8;
    uVar12 = 1;
    uVar6 = uVar8 * _global_settings & 0x7fff;
    do {
      iVar10 = uVar12 * fVar2 - (uVar12 - 1) * fVar2;
      uVar12 = uVar12 + 1;
      if (iVar10 == 1) {
        *(param_1 + 0x25e) = (&DAT_2001bb30)[uVar6];
        *(param_1 + 0x38a) = (&DAT_2001bb30)[uVar6];
        if (cVar3 == '\x01') {
          *(param_2 + 0x25e) = (&DAT_2001af78)[uVar6];
          *(param_2 + 0x38a) = (&DAT_2001af78)[uVar6];
        }
        uVar11 = uVar6 + 1;
      }
      else {
        uVar11 = iVar10 + uVar6;
        bVar1 = (&DAT_2001bb30)[uVar6];
        uVar4 = bVar1;
        if (uVar6 + 1 < uVar11) {
          puVar9 = &DAT_2001bb31 + uVar6;
          uVar5 = uVar4;
          do {
            uVar7 = *puVar9;
            puVar9 = puVar9 + 1;
            uVar5 = (uVar7 < uVar5) * uVar5 + (uVar7 >= uVar5) * uVar7;
            uVar4 = (uVar7 < uVar4) * uVar4 + (uVar7 >= uVar4) * uVar4;
          } while (&DAT_2001bb30 + uVar11 != puVar9);
          *(param_1 + 0x25e) = uVar5;
          *(param_1 + 0x38a) = uVar4;
          if (cVar3 == '\x01') {
            uVar4 = (&DAT_2001af78)[uVar6];
            puVar9 = &DAT_2001af79 + uVar6;
            uVar6 = uVar4;
            do {
              uVar5 = *puVar9;
              puVar9 = puVar9 + 1;
              uVar6 = (uVar5 < uVar6) * uVar6 + (uVar5 >= uVar6) * uVar5;
              uVar4 = (uVar5 < uVar4) * uVar4 + (uVar5 >= uVar4) * uVar4;
            } while (&DAT_2001af78 + uVar11 != puVar9);
LAB_080177f4:
            *(param_2 + 0x25e) = uVar6;
            *(param_2 + 0x38a) = uVar4;
          }
        }
        else {
          *(param_1 + 0x25e) = bVar1;
          *(param_1 + 0x38a) = bVar1;
          if (cVar3 == '\x01') {
            uVar4 = (&DAT_2001af78)[uVar6];
            uVar6 = uVar4;
            goto LAB_080177f4;
          }
        }
      }
      uVar8 = uVar8 + 1;
      param_2 = param_2 + 1;
      param_1 = param_1 + 1;
      uVar6 = uVar11;
    } while (uVar8 <= uVar13);
  }
  return;
}




void FUN_08017838(int param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char cVar9;
  uint uVar10;
  byte abStack_261 [300];
  byte abStack_135 [301];
  
  uVar8 = roll_draw_cursor_x_;
  uVar4 = roll_split_index_;
  uVar3 = uVar4;
  if (0x31 < uVar8 - uVar4) {
    for (; uVar3 <= uVar8; uVar3 = uVar3 + 1 & 0xffff) {
      bVar1 = *(param_1 + uVar3 + 0x38a);
      abStack_261[uVar3 + 1] = *(param_1 + uVar3 + 0x25e);
      abStack_135[uVar3 + 1] = bVar1;
    }
    while (uVar4 = uVar4 + 1 & 0xffff, uVar4 < uVar8) {
      uVar2 = abStack_261[uVar4 + 1];
      uVar3 = abStack_135[uVar4 + 1];
      uVar6 = abStack_261[uVar4 + 1];
      if (uVar2 - uVar3 < 0xf) {
        uVar7 = abStack_261[uVar4];
        if ((((uVar7 < uVar2) && (uVar10 = abStack_261[uVar4 + 2], uVar10 < uVar2)) && (((uVar10 + 9) - uVar7 & 0xffff) < 0x13)) &&
           ((uVar2 - uVar7 < 0x19 && (uVar2 - uVar10 < 0x19)))) {
          uVar6 = (uVar7 + uVar10) / 2;
        }
        uVar2 = abStack_135[uVar4];
        if (((uVar3 < uVar2) && (uVar7 = abStack_135[uVar4 + 2], uVar3 < uVar7)) &&
           ((((uVar7 + 9) - uVar2 & 0xffff) < 0x13 && ((uVar2 - uVar3 < 0x19 && (uVar7 - uVar3 < 0x19)))))) {
          uVar3 = (uVar2 + uVar7) / 2;
        }
        cVar9 = uVar3;
        if (uVar6 == uVar3) {
          cVar5 = cVar9;
          if (uVar3 < 0xff) {
            cVar5 = cVar9 + '\x01';
          }
        }
        else {
          cVar5 = (uVar3 < uVar6) * uVar6 + (uVar3 >= uVar6) * cVar9;
        }
        *(param_1 + uVar4 + 0x25e) = cVar5;
        *(param_1 + uVar4 + 0x38a) = cVar9;
      }
    }
  }
  return;
}




void FUN_08017974(char *param_1)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  
  FUN_08017838();
  param_1[4] = '\0';
  param_1[5] = -1;
  iVar4 = ch2_vert_scroll_offset;
  iVar3 = ch1_vert_scroll_offset;
  bVar2 = global_settings;
  uVar5 = roll_split_index_;
  uVar16 = roll_draw_cursor_x_;
  if (uVar16 < uVar5) {
    return;
  }
  uVar13 = 0xff;
  uVar14 = 0;
  uVar10 = 0xff;
  uVar15 = 0;
  do {
    uVar11 = param_1[uVar5 + 0x25e];
    bVar1 = param_1[uVar5 + 0x38a];
    uVar12 = bVar1;
    uVar6 = uVar11;
    uVar9 = uVar12;
    if (bVar2 == 0) {
      iVar8 = iVar3;
      if (*param_1 != '\0') {
        iVar8 = iVar4;
      }
      uVar6 = uVar11 + iVar8;
      if (uVar6 < 0xff) {
        if (uVar6 < 1) {
          uVar6 = 1;
          goto LAB_08017a5e;
        }
        uVar6 = uVar6 & 0xff;
        if (0xfe < uVar12 + iVar8) {
          uVar9 = 0xfe;
          goto LAB_080179e2;
        }
LAB_08017aa8:
        uVar9 = uVar12 + iVar8 & 0xff;
        if (uVar12 + iVar8 < 1) {
          uVar9 = 1;
        }
        goto LAB_080179e2;
      }
      uVar6 = 0xfe;
LAB_08017a5e:
      if (uVar12 + iVar8 < 0xff) goto LAB_08017aa8;
      uVar7 = uVar6 + 2 & 0xff;
      uVar9 = 0xfe;
LAB_08017a6e:
      if ((uVar7 - 7 & 0x7f) < 2) {
        uVar6 = uVar6 - 3 & 0xff;
        uVar9 = uVar9 + 3 & 0xff;
      }
      else if (uVar7 < 5) {
        if (2 < uVar7) {
          uVar6 = uVar6 - 1 & 0xff;
          uVar9 = uVar9 + 1 & 0xff;
        }
      }
      else {
        uVar6 = uVar6 - 2 & 0xff;
        uVar9 = uVar9 + 2 & 0xff;
      }
    }
    else {
LAB_080179e2:
      uVar7 = uVar6 - uVar9 & 0xff;
      if (9 < (uVar7 - 9 & 0x7f)) goto LAB_08017a6e;
      uVar6 = uVar6 - 4 & 0xff;
      uVar9 = uVar9 + 4 & 0xff;
    }
    uVar9 = (uVar9 < uVar10) * uVar9 + (uVar9 >= uVar10) * uVar10;
    uVar10 = (uVar6 < uVar15) * uVar15 + (uVar6 >= uVar15) * uVar6;
    param_1[uVar5 + 6] = ~uVar9;
    param_1[uVar5 + 0x132] = ~uVar10;
    if (bVar2 == 0) {
      if (uVar14 < uVar11) {
        param_1[4] = param_1[uVar5 + 0x25e];
      }
      if (uVar12 < uVar13) {
        param_1[5] = bVar1;
      }
    }
    else {
      if (uVar14 < uVar10) {
        param_1[4] = uVar10;
      }
      if (uVar9 < uVar13) {
        param_1[5] = uVar9;
      }
    }
    uVar5 = uVar5 + 1 & 0xffff;
    if (uVar16 < uVar5) {
      return;
    }
    uVar14 = param_1[4];
    uVar13 = param_1[5];
    uVar15 = uVar9;
  } while( true );
}




void FUN_08017ad4(char *param_1)

{
  byte bVar1;
  byte *pbVar2;
  ushort uVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  ushort *puVar8;
  byte *pbVar9;
  int iVar10;
  ushort *puVar11;
  uint uVar12;
  ushort *puVar13;
  uint uVar14;
  
  iVar10 = param_1[4] - param_1[5];
  if (*param_1 == '\0') {
    if (5 < iVar10) {
      return;
    }
  }
  else if (10 < iVar10) {
    return;
  }
  uVar14 = roll_split_index_;
  uVar12 = roll_draw_cursor_x_;
  if (uVar12 < uVar14) {
    return;
  }
  pbVar9 = param_1 + uVar14 + 6;
  iVar5 = 0;
  do {
    pbVar2 = pbVar9 + 300;
    bVar1 = *pbVar9;
    pbVar9 = pbVar9 + 1;
    iVar5 = iVar5 + bVar1 + *pbVar2;
  } while (param_1 + uVar12 + 7 != pbVar9);
  uVar12 = (iVar5 * 100) / ((uVar12 - uVar14) + 1);
  iVar5 = uVar12 / 200 + (0x32 < (uVar12 >> 1) % 100);
  if (0xf4 < iVar5 - 6U) {
    return;
  }
  if (*param_1 == '\0') {
    iVar10 = ch1_vert_offset_pixels + iVar5;
    if (iVar10 - 0x7dU < 7) {
      iVar10 = -ch1_vert_offset_pixels;
      iVar5 = iVar10 + 0x80;
      iVar6 = iVar10 + 0x81;
      iVar10 = iVar10 + 0x7f;
      goto LAB_08017b66;
    }
    if (iVar10 - 0x7aU < 0xd) {
      iVar5 = (((iVar10 + -0x80) * 2) / 3 - ch1_vert_offset_pixels) + 0x80;
    }
  }
  else {
    iVar6 = ch2_vert_offset_pixels + iVar5;
    if (iVar6 - 0x7dU < 7) {
      iVar5 = 0x80 - ch2_vert_offset_pixels;
    }
    else if (iVar6 - 0x7aU < 0xd) {
      iVar5 = (((iVar6 + -0x80) * 2) / 3 - ch2_vert_offset_pixels) + 0x80;
    }
    if ((ch2_vert_offset_pixels == 0) && (iVar5 - 0x7dU < 7)) {
      iVar10 = 0x7f;
      iVar6 = 0x81;
      iVar5 = 0x80;
      goto LAB_08017b66;
    }
    if (7 < iVar10) {
      return;
    }
  }
  iVar6 = iVar5 + 1;
  iVar10 = iVar5 + -1;
LAB_08017b66:
  memset(param_1 + 6,iVar6,300);
  memset(param_1 + 0x132,iVar10,300);
  if ((global_settings != 0) && (roll_mode_enable == '\0')) {
    uVar3 = DAT_200028a6 + 0x28;
    if (0x121 < DAT_200028a6 + 0x28) {
      uVar3 = DAT_200028a6 - 0xfa;
    }
    DAT_200028a6 = uVar3;
    if ((highspeed_sys_flag_ == '\0') || (DAT_200028a5 == '\0')) {
      DAT_20002a38 = 0x14;
      puVar11 = &DAT_200028a8;
      puVar13 = &DAT_20002970;
      puVar8 = &DAT_0802f220 + DAT_200028a6 * 2;
      iVar10 = 0x14;
      do {
        *puVar11 = *puVar8 % 0x127;
        puVar11 = puVar11 + 1;
        *puVar13 = puVar8[0x14] % 0x127;
        puVar13 = puVar13 + 1;
        puVar8 = puVar8 + 1;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
      uVar12 = 0x14;
    }
    else {
      uVar12 = DAT_20002a38;
      if (uVar12 == 0) {
        return;
      }
    }
    cVar4 = iVar5;
    uVar14 = 0;
    do {
      uVar3 = (&DAT_200028a8)[uVar14];
      uVar7 = uVar14 + 1;
      param_1[uVar3 + 6] = cVar4;
      param_1[uVar3 + 7] = cVar4;
      uVar3 = (&DAT_20002970)[uVar14];
      param_1[uVar3 + 0x132] = cVar4;
      param_1[uVar3 + 0x133] = cVar4;
      param_1[uVar3 + 0x134] = cVar4;
      uVar14 = uVar7;
    } while (uVar7 < uVar12);
  }
  return;
}




void FUN_08017cd0(void)

{
  char cVar1;
  undefined *__dest;
  uint uVar2;
  int iVar3;
  char cVar4;
  
  if (DAT_2001de09 == '\0') {
    if (((fast_render_flag_ != '\x02') && (DAT_2001dcdc == '\0')) && (roll_draw_cursor_x_ < 300)) {
      if ((fast_render_flag_ == '\0') && (mid_speed_config_ == '\0')) {
        FUN_08017510(&DAT_20019ca0,&DAT_2001a15c);
      }
      else {
        FUN_080176cc();
      }
      FUN_08017974(&DAT_20019ca0);
      FUN_08017ad4(&DAT_20019ca0);
      if (ch2_enabled == '\x01') {
        FUN_08017974(&DAT_2001a15c);
        FUN_08017ad4(&DAT_2001a15c);
      }
      cVar1 = ch2_enabled;
      uVar2 = DAT_200028a5;
      if (((uVar2 < 0x32) && (highspeed_sys_flag_ != '\0')) &&
         ((trigger_mode_0_auto_1_normal == '\0' && ((roll_mode_enable == '\0' && (persistance_mode_0_off_1_infinite_2_1s == '\0')))))) {
        __dest = &DAT_2000a8cc + uVar2 * 300;
        cVar4 = DAT_200028a5 + 1;
        iVar3 = uVar2 * 300 + 15000;
      }
      else {
        DAT_200028a5 = 0;
        iVar3 = 15000;
        cVar4 = '\x01';
        __dest = &DAT_2000a8cc;
        uVar2 = 0;
      }
      memcpy(__dest,&DAT_20019dd2,300);
      memcpy(&DAT_2000a8cc + iVar3,&DAT_20019ca6,300);
      if (cVar1 == '\x01') {
        iVar3 = (uVar2 + 100) * 300;
        memcpy(&DAT_2000a8cc + iVar3,&DAT_2001a28e,300);
        memcpy(&DAT_2000e364 + iVar3,&DAT_2001a162,300);
      }
      DAT_200028a5 = cVar4;
      return;
    }
  }
  else {
    if (DAT_200028a5 == 0) {
      memset(&DAT_2000a8cc,0,60000);
      DAT_2001df20 = 0;
    }
    FUN_080233e8(0);
    FUN_080234d4(&DAT_2001bb30);
    DAT_200028a5 = DAT_200028a5 + 1;
  }
  return;
}




void zw_screenshot_copy_buffer_(void)

{
  DAT_200028a5 = 0;
  memcpy(&DAT_2000a8cc,&DAT_20019dd2,300);
  memcpy(&DAT_2000e364,&DAT_20019ca6,300);
  memcpy(&DAT_20011dfc,&DAT_2001a28e,300);
  memcpy(&DAT_20015894,&DAT_2001a162,300);
  return;
}




void FUN_08017e88(uint param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  
  uVar6 = roll_draw_cursor_x_;
  if (uVar6 < 300) {
    uVar3 = DAT_200028a5;
    if (uVar3 == 0) {
      uVar3 = 1;
    }
    bVar5 = param_1 >> 0x10;
    if ((param_1 & 0xff) == 0) {
      uVar9 = roll_split_index_;
      uVar7 = 0;
      do {
        if (uVar9 <= uVar6) {
          uVar2 = uVar9;
          do {
            bVar1 = (&DAT_2000a8cc)[uVar2 + (uVar7 + 0x32) * 300];
            for (uVar4 = (&DAT_2000a8cc)[uVar2 + uVar7 * 300]; uVar4 <= bVar1; uVar4 = uVar4 + 1 & 0xffff) {
              if ((uVar4 - 0x1c & 0xffff) < 200) {
                framebuffer_[(uVar4 - 10) * 0x140 + uVar2 + 10] = bVar5;
              }
            }
            uVar2 = uVar2 + 1 & 0xffff;
          } while (uVar2 != (uVar6 + 1 & 0x7fff));
        }
        uVar7 = uVar7 + 1;
      } while ((uVar7 & 0x7fff) < uVar3);
    }
    else if ((param_1 & 0xff) == 1) {
      uVar7 = roll_split_index_;
      iVar8 = 100;
      do {
        if (uVar7 <= uVar6) {
          uVar9 = uVar7;
          do {
            bVar1 = (&DAT_2000a8cc)[uVar9 + (iVar8 + 0x32) * 300];
            for (uVar2 = (&DAT_2000a8cc)[uVar9 + iVar8 * 300]; uVar2 <= bVar1; uVar2 = uVar2 + 1 & 0xffff) {
              if ((uVar2 - 0x1c & 0xffff) < 200) {
                framebuffer_[(uVar2 - 10) * 0x140 + uVar9 + 10] = bVar5;
              }
            }
            uVar9 = uVar9 + 1 & 0xffff;
          } while ((uVar6 + 1 & 0x7fff) != uVar9);
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 != (uVar3 - 1 & 0xffff) + 0x65);
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void zw_scope_persistance(void)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  byte *pbVar11;
  undefined4 *puVar12;
  byte *pbVar13;
  undefined1 auStack_4c0 [1192];
  
  bVar1 = persistance_mode_0_off_1_infinite_2_1s;
  if (DAT_2001dcdc != '\0') {
    return;
  }
  if (persistance_mode_0_off_1_infinite_2_1s < 2) {
    if ((DAT_2001de09 != '\0') && (persistance_mode_0_off_1_infinite_2_1s == 0)) {
      FUN_0802364c();
      DAT_200028a5 = bVar1;
      return;
    }
  }
  else if (DAT_2001de09 == '\0') {
    pbVar13 = framebuffer_ + 0x17b6;
    do {
      pbVar11 = pbVar13 + -300;
      iVar10 = 300;
      do {
        bVar1 = *pbVar11;
        if ((bVar1 - 0x21 < 0x3f) && (bVar1 != 0x40)) {
          *pbVar11 = bVar1 - 1;
        }
        pbVar11 = pbVar11 + 1;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
      pbVar13 = pbVar13 + 0x140;
    } while (pbVar13 != framebuffer_ + 0x111b6);
  }
  uVar9 = _DAT_2001a168;
  uVar8 = _DAT_2001a164;
  uVar7 = _DAT_2001a160;
  uVar6 = _DAT_2001a15c;
  uVar5 = _DAT_20019cac;
  uVar4 = _DAT_20019ca8;
  uVar3 = _DAT_20019ca4;
  uVar2 = _DAT_20019ca0;
  if (active_channel_0_ch1_1_ch2_2_math == '\0') {
    if (ch2_enabled == '\x01') {
      memcpy(auStack_4c0,&DAT_2001a16c,0x4a6);
      FUN_08017e88(uVar6,uVar7,uVar8,uVar9);
    }
    puVar12 = &DAT_20019ca0;
  }
  else {
    memcpy(auStack_4c0,&DAT_20019cb0,0x4a6);
    FUN_08017e88(uVar2,uVar3,uVar4,uVar5);
    if (ch2_enabled != '\x01') {
      DAT_200028a5 = 0;
      return;
    }
    puVar12 = &DAT_2001a15c;
  }
  uVar2 = *puVar12;
  uVar3 = puVar12[1];
  uVar4 = puVar12[2];
  uVar5 = puVar12[3];
  memcpy(auStack_4c0,puVar12 + 4,0x4a6);
  FUN_08017e88(uVar2,uVar3,uVar4,uVar5);
  DAT_200028a5 = 0;
  return;
}




void FUN_08018160(void)

{
  byte bVar1;
  undefined1 uVar2;
  
  if (((fast_render_flag_ != '\x02') && (DAT_2001dcdc == '\0')) && (roll_draw_cursor_x_ < 300)) {
    if ((fast_render_flag_ == '\0') && (mid_speed_config_ == '\0')) {
      FUN_08017510(&DAT_20019ca0,&DAT_2001a15c);
    }
    else {
      FUN_080176cc();
    }
    FUN_08017974(&DAT_20019ca0);
    FUN_08017ad4(&DAT_20019ca0);
    if (ch2_enabled == '\x01') {
      FUN_08017974(&DAT_2001a15c);
      FUN_08017ad4(&DAT_2001a15c);
    }
    uVar2 = timebase_index_2_5ns_30_10s;
    bVar1 = global_settings;
    timebase_index_2_5ns_30_10s = zoom_timebase_index_;
    horiz_ref_mode__0_center__1_trig_lock_ = 1;
    global_settings = 0;
    zw_set_scope_parameters_();
    horiz_ref_mode__0_center__1_trig_lock_ = 0;
    global_settings = bVar1;
    if ((fast_render_flag_ == '\0') && (mid_speed_config_ == '\0')) {
      FUN_08017510(&DAT_200197e4,&DAT_2001932c);
    }
    else {
      FUN_080176cc();
    }
    FUN_08017974(&DAT_200197e4);
    FUN_08017ad4(&DAT_200197e4);
    if (ch2_enabled == '\x01') {
      FUN_08017974(&DAT_2001932c);
      FUN_08017ad4(&DAT_2001932c);
    }
    timebase_index_2_5ns_30_10s = uVar2;
    zw_set_scope_parameters_();
  }
  return;
}




void FUN_08018234(uint param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  
  uVar3 = roll_draw_cursor_x_;
  if (uVar3 < 300) {
    bVar5 = param_1 >> 0x10;
    if ((param_1 & 0xff) == 0) {
      uVar2 = roll_split_index_;
      if (uVar2 <= uVar3) {
        do {
          bVar1 = (&DAT_20019ca6)[uVar2];
          for (uVar4 = (&DAT_20019dd2)[uVar2]; uVar4 <= bVar1; uVar4 = uVar4 + 1 & 0xffff) {
            if ((uVar4 - 0x1e & 0xffff) < 0xc4) {
              framebuffer_[((uVar4 >> 1) + 4) * 0x140 + uVar2 + 10] = bVar5;
            }
          }
          uVar2 = uVar2 + 1 & 0xffff;
        } while (uVar2 != (uVar3 + 1 & 0x7fff));
      }
    }
    else if (((param_1 & 0xff) == 1) && (uVar2 = roll_split_index_, uVar2 <= uVar3)) {
      do {
        bVar1 = (&DAT_2001a162)[uVar2];
        for (uVar4 = (&DAT_2001a28e)[uVar2]; uVar4 <= bVar1; uVar4 = uVar4 + 1 & 0xffff) {
          if ((uVar4 - 0x1e & 0xffff) < 0xc4) {
            framebuffer_[((uVar4 >> 1) + 4) * 0x140 + uVar2 + 10] = bVar5;
          }
        }
        uVar2 = uVar2 + 1 & 0xffff;
      } while ((uVar3 + 1 & 0xffff) != uVar2);
    }
  }
  return;
}




void FUN_08018328(uint param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  
  uVar3 = roll_draw_cursor_x_;
  if (uVar3 < 300) {
    bVar5 = param_1 >> 0x10;
    if ((param_1 & 0xff) == 0) {
      uVar2 = roll_split_index_;
      if (uVar2 <= uVar3) {
        do {
          bVar1 = *(&DAT_200197ea + uVar2);
          for (uVar4 = (&DAT_20019916)[uVar2]; uVar4 <= bVar1; uVar4 = uVar4 + 1 & 0xffff) {
            if ((uVar4 - 0x1e & 0xffff) < 0xc4) {
              framebuffer_[((uVar4 >> 1) + 0x68) * 0x140 + uVar2 + 10] = bVar5;
            }
          }
          uVar2 = uVar2 + 1 & 0xffff;
        } while (uVar2 != (uVar3 + 1 & 0x7fff));
      }
    }
    else if (((param_1 & 0xff) == 1) && (uVar2 = roll_split_index_, uVar2 <= uVar3)) {
      do {
        bVar1 = *(&DAT_20019332 + uVar2);
        for (uVar4 = (&DAT_2001945e)[uVar2]; uVar4 <= bVar1; uVar4 = uVar4 + 1 & 0xffff) {
          if ((uVar4 - 0x1e & 0xffff) < 0xc4) {
            framebuffer_[((uVar4 >> 1) + 0x68) * 0x140 + uVar2 + 10] = bVar5;
          }
        }
        uVar2 = uVar2 + 1 & 0xffff;
      } while ((uVar3 + 1 & 0xffff) != uVar2);
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_0801841c(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  undefined1 auStack_4c0 [1192];
  
  uVar8 = _DAT_2001a168;
  uVar7 = _DAT_2001a164;
  uVar6 = _DAT_2001a160;
  uVar5 = _DAT_2001a15c;
  uVar4 = _DAT_20019cac;
  uVar3 = _DAT_20019ca8;
  uVar2 = _DAT_20019ca4;
  uVar1 = _DAT_20019ca0;
  if (DAT_2001dcdc != '\0') {
    return;
  }
  if (active_channel_0_ch1_1_ch2_2_math == '\0') {
    if (ch2_enabled == '\x01') {
      memcpy(auStack_4c0,&DAT_2001a16c,0x4a6);
      FUN_08018234(uVar5,uVar6,uVar7,uVar8);
    }
    puVar9 = &DAT_20019ca0;
LAB_0801843c:
    uVar1 = *puVar9;
    uVar2 = puVar9[1];
    uVar3 = puVar9[2];
    uVar4 = puVar9[3];
    memcpy(auStack_4c0,puVar9 + 4,0x4a6);
    FUN_08018234(uVar1,uVar2,uVar3,uVar4);
    uVar4 = _DAT_20019338;
    uVar3 = _DAT_20019334;
    uVar2 = _DAT_20019330;
    uVar1 = _DAT_2001932c;
    if (active_channel_0_ch1_1_ch2_2_math != '\0') {
LAB_08018518:
      uVar4 = _DAT_200197f0;
      uVar3 = _DAT_200197ec;
      uVar2 = _DAT_200197e8;
      uVar1 = _DAT_200197e4;
      memcpy(auStack_4c0,&DAT_200197f4,0x4a6);
      FUN_08018328(uVar1,uVar2,uVar3,uVar4);
      if (ch2_enabled != '\x01') {
        DAT_200028a5 = 0;
        return;
      }
      puVar9 = &DAT_2001932c;
      goto LAB_08018488;
    }
    if (ch2_enabled == '\x01') {
      memcpy(auStack_4c0,&DAT_2001933c,0x4a6);
      FUN_08018328(uVar1,uVar2,uVar3,uVar4);
    }
  }
  else {
    memcpy(auStack_4c0,&DAT_20019cb0,0x4a6);
    FUN_08018234(uVar1,uVar2,uVar3,uVar4);
    if (ch2_enabled == '\x01') {
      puVar9 = &DAT_2001a15c;
      goto LAB_0801843c;
    }
    if (active_channel_0_ch1_1_ch2_2_math != '\0') goto LAB_08018518;
  }
  puVar9 = &DAT_200197e4;
LAB_08018488:
  uVar1 = *puVar9;
  uVar2 = puVar9[1];
  uVar3 = puVar9[2];
  uVar4 = puVar9[3];
  memcpy(auStack_4c0,puVar9 + 4,0x4a6);
  FUN_08018328(uVar1,uVar2,uVar3,uVar4);
  DAT_200028a5 = 0;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


int FUN_080185fc(int param_1)

{
  byte bVar1;
  
  if (param_1 == 0x4a) {
    if (DAT_2001de15 != '\0') {
      DAT_2001de15 = 0;
      ch1_enabled_measurements_bitfield = DAT_2001a614;
      ch2_enabled_measurements_bitfield = DAT_20019c9c;
      FUN_0801eff0(0xff);
      return 0;
    }
    if ((DAT_2001ddc9 == '\0') && ((_fft_mode_0_off_1_log_2_lin_3_music & 0xffffff00) == 0)) {
      if ((roll_mode_enable == '\0') && (((global_settings == 1 || ((0xb < DAT_2000a8c8 && (global_settings != 2)))) && (DAT_2000a8c8 < 0x19)))) {
        DAT_2001de15 = '\x01';
        DAT_2001de09 = 0;
        _fft_mode_0_off_1_log_2_lin_3_music = fft_mode_0_off_1_log_2_lin_3_music;
        DAT_2001ddc9 = '\0';
        DAT_2001a614 = ch1_enabled_measurements_bitfield;
        DAT_20019c9c = ch2_enabled_measurements_bitfield;
        ch1_enabled_measurements_bitfield = 0;
        ch2_enabled_measurements_bitfield = 0;
        if (timebase_index_2_5ns_30_10s < 0xc) {
          timebase_index_2_5ns_30_10s = 0xc;
          zoom_timebase_index_ = '\t';
        }
        else {
          zoom_timebase_index_ = timebase_index_2_5ns_30_10s - 3;
        }
        horiz_window_pos_ps__l = 0;
        horiz_window_pos_ps__h = 0;
        roll_mode_view_offset__l = 0;
        roll_mode_view_offset__h = 0;
        FUN_0801eff0(0xff);
        param_1 = 0;
        DAT_2001a158 = timebase_val_ns_l;
      }
      else {
        zw_draw_popup_message("Limit",5,1000,0,1);
        param_1 = 0;
      }
    }
  }
  else if (param_1 == 0x4d) {
    bVar1 = ~(DAT_2001de09 != 0);
    if (DAT_2001de09 != 0) {
      DAT_2001de09 = bVar1;
      return 0;
    }
    param_1 = 0;
    DAT_2001de09 = bVar1;
    if (ch2_enabled == '\x01') {
      FUN_0801eff0(0x47);
    }
  }
  return param_1;
}




void FUN_08018734(void)

{
  if (DAT_2001de15 == '\0') {
    return;
  }
  DAT_2001de15 = 0;
  ch1_enabled_measurements_bitfield = DAT_2001a614;
  ch2_enabled_measurements_bitfield = DAT_20019c9c;
  FUN_0801eff0(0xff);
  return;
}




void FUN_0801876c(void)

{
  ushort uVar1;
  byte *pbVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  undefined *puVar6;
  short sVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  short sVar11;
  uint uVar12;
  byte *pbVar13;
  byte *pbVar14;
  byte bVar15;
  uint uVar16;
  byte *pbVar17;
  uint uVar18;
  byte *pbVar19;
  byte *pbVar20;
  uint uVar21;
  byte abStack_274 [300];
  byte abStack_148 [300];
  
  if ((((channel_math_mode_0_off_1_add_2_sub != '\0') && (fft_mode_0_off_1_log_2_lin_3_music == '\0')) && (DAT_2001de15 == '\0')) && (ch2_enabled != '\0')) {
    uVar12 = roll_split_index_;
    uVar21 = roll_draw_cursor_x_;
    if (uVar12 <= uVar21) {
      sVar11 = (ch2_vert_offset_pixels + 0x80) - ch1_vert_offset_pixels;
      pbVar14 = abStack_148 + uVar12;
      pbVar13 = abStack_274 + uVar12;
      pbVar17 = &DAT_20019ca6 + uVar12;
      uVar1 = 0x180U - (ch1_vert_offset_pixels + ch2_vert_offset_pixels) & 0x7fff;
      pbVar2 = &DAT_2001a162 + uVar12;
      uVar10 = 0;
      uVar16 = 0xff;
      uVar18 = uVar12;
      pbVar19 = pbVar13;
      pbVar20 = pbVar14;
      do {
        if (channel_math_mode_0_off_1_add_2_sub == '\x01') {
          sVar7 = (*pbVar2 + sVar11) - *pbVar17;
          sVar3 = (pbVar2[300] + sVar11) - pbVar17[300];
        }
        else {
          if (channel_math_mode_0_off_1_add_2_sub != '\x02') {
            return;
          }
          sVar7 = (uVar1 - *pbVar17) - *pbVar2;
          sVar3 = (uVar1 - pbVar17[300]) - pbVar2[300];
        }
        iVar8 = DAT_2001de2c + sVar7;
        iVar4 = DAT_2001de2c + sVar3;
        iVar8 = (iVar8 < 0xff) * iVar8 + (iVar8 >= 0xff) * 0xff;
        uVar9 = (-1 < iVar8) * iVar8;
        if (iVar4 < 0) {
          uVar16 = 0;
          bVar15 = 0xff;
          uVar5 = 0;
        }
        else {
          uVar5 = (iVar4 < 0xff) * iVar4 + (iVar4 >= 0xff) * 0xff;
          if (uVar16 < uVar5) {
            bVar15 = ~uVar16;
            uVar5 = uVar16;
          }
          else {
            uVar16 = uVar5 & 0xff;
            bVar15 = ~uVar5;
          }
        }
        if (uVar9 < uVar10) {
          uVar9 = uVar10;
        }
        uVar18 = uVar18 + 1;
        *pbVar19 = bVar15;
        pbVar19 = pbVar19 + 1;
        *pbVar20 = ~((uVar9 < uVar5) * uVar5 + (uVar9 >= uVar5) * uVar9);
        pbVar20 = pbVar20 + 1;
        pbVar17 = pbVar17 + 1;
        pbVar2 = pbVar2 + 1;
        uVar10 = uVar16;
        uVar16 = uVar9 & 0x7f;
      } while (uVar18 <= uVar21);
      do {
        uVar10 = *pbVar14;
        bVar15 = *pbVar13;
        if (uVar10 <= bVar15) {
          puVar6 = &DAT_2001d32e + uVar12 + uVar10 * 0x140;
          do {
            if (uVar10 - 0x1c < 200) {
              if (0x13f < uVar12 + 10) {
                return;
              }
              *puVar6 = 2;
            }
            uVar10 = uVar10 + 1;
            puVar6 = puVar6 + 0x140;
          } while (uVar10 <= bVar15);
        }
        uVar12 = uVar12 + 1;
        pbVar14 = pbVar14 + 1;
        pbVar13 = pbVar13 + 1;
      } while (uVar12 <= uVar21);
    }
  }
  return;
}




void FUN_0801890c(uint param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  iVar2 = (param_1 & 3) * 0x4c;
  iVar1 = (param_1 >> 2) * 0x3f;
  iVar5 = iVar2 + 0xe;
  uVar7 = iVar1 + 0x1bU & 0xffff;
  iVar4 = iVar2 + 0xd;
  uVar6 = iVar1 + 0x1aU & 0xffff;
  FUN_080264d0(iVar5,uVar7,7,0x7e0);
  FUN_080264d0(iVar4,uVar6,8,0x7e0);
  iVar3 = iVar2 + 0x43;
  FUN_08026548(iVar5,uVar7,7,0x7e0);
  FUN_08026548(iVar4,uVar6,8,0x7e0);
  FUN_080264d0(iVar3,uVar7,7,0x7e0);
  FUN_080264d0(iVar3,uVar6,8,0x7e0);
  FUN_08026548(iVar2 + 0x4a,uVar7,7,0x7e0);
  uVar8 = iVar1 + 0x57U & 0xffff;
  FUN_08026548(iVar2 + 0x49,uVar6,8,0x7e0);
  uVar7 = iVar1 + 0x56U & 0xffff;
  FUN_080264d0(iVar5,uVar8,7,0x7e0);
  uVar6 = iVar1 + 0x50U & 0xffff;
  FUN_080264d0(iVar4,uVar7,8,0x7e0);
  FUN_08026548(iVar5,uVar6,7,0x7e0);
  FUN_08026548(iVar4,uVar6,8,0x7e0);
  FUN_080264d0(iVar3,uVar8,7,0x7e0);
  FUN_080264d0(iVar3,uVar7,8,0x7e0);
  FUN_08026548(iVar2 + 0x4a,uVar6,8,0x7e0);
  FUN_08026548(iVar2 + 0x49,uVar6,8,0x7e0);
  return;
}




int zw_home_screen(int param_1)

{
  if (param_1 == 1) {
    if (system_status_ == '\a') {
      system_status_ = 1;
      FUN_0801890c(DAT_20002a48);
      return 0;
    }
    system_status_ = 7;
    DAT_20002a48 = '\0';
    zw_draw_bitmap(image_Home_Screen_0802f4e4,0,0,320,240);
    FUN_0801890c(DAT_20002a48);
    DAT_2001de01 = 0;
    long_memory_enable_ = 0;
    DAT_2001de0e = 0;
    DAT_2001de0c = 0;
    DAT_2001de0d = 0;
    DAT_2001ddc9 = 0;
    return 0;
  }
  if (system_status_ != '\a') {
    return param_1;
  }
  if (param_1 == 0) {
    return 0;
  }
  printf_disabled_1("page: home");
  if (param_1 == 4) {
    if (DAT_20002a48 != '\x04') {
      DAT_20002a48 = DAT_20002a48 + '\x01';
      goto LAB_08018a70;
    }
  }
  else {
    if (param_1 == 3) {
      DAT_20002a48 = DAT_20002a48 + -1;
    }
    else if (param_1 == 0xb) {
      DAT_20002a48 = DAT_20002a48 + -4;
    }
    else if (param_1 == 0x13) {
      DAT_20002a48 = DAT_20002a48 + '\x04';
    }
LAB_08018a70:
    if (DAT_20002a48 < '\0') {
      DAT_20002a48 = DAT_20002a48 + '\b';
    }
    else if ('\a' < DAT_20002a48) {
      DAT_20002a48 = DAT_20002a48 + -8;
    }
    if ('\x04' < DAT_20002a48) {
      DAT_20002a48 = '\x04';
      goto LAB_08018a86;
    }
    if (param_1 != 2) goto LAB_08018a86;
    system_status_ = '\x01';
    if (DAT_20002a48 == '\0') {
      DAT_2001de0e = 0;
      DAT_2001de0c = 0;
      DAT_2001ddc9 = 0;
    }
    else {
      if (DAT_20002a48 == '\x01') {
        DAT_2001de0e = 0;
        DAT_2001de0c = 0;
        DAT_2001ddc9 = 0;
        system_status_ = 1;
        return 0x58;
      }
      if (DAT_20002a48 == '\x02') {
        system_status_ = 1;
        DAT_2001ddc9 = 0;
        DAT_2001de0d = 1;
        return 0x7e;
      }
      if (DAT_20002a48 == '\x03') {
        system_status_ = 1;
        DAT_2001ddc9 = 0;
        DAT_2001de0c = 0;
        DAT_2001de0e = 0;
        return 0x4e;
      }
      if (DAT_20002a48 == '\x04') {
        system_status_ = 8;
        DAT_2001ddc9 = 0;
        DAT_2001de0c = 0;
        DAT_2001de0e = 0;
        return 0x7f;
      }
    }
  }
  DAT_20002a48 = '\0';
LAB_08018a86:
  zw_draw_bitmap(image_Home_Screen_0802f4e4,0,0,320,240);
  FUN_0801890c(DAT_20002a48);
  return 0;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void FUN_08018bbc(uint param_1)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  iVar5 = DAT_2001dd14;
  iVar3 = hardware_trigger_delay_;
  if ((DAT_2001dd14 < 1) && ((DAT_2001dd14 != 0 || (hardware_trigger_delay_ == 0)))) {
    iVar6 = __divdi3(hardware_trigger_delay_,DAT_2001dd14,1000,0);
    lVar1 = -CONCAT44(iVar5,iVar3);
    DAT_20002a50 = __moddi3(lVar1,lVar1 >> 0x20,1000,0);
    iVar6 = buffer_pointer_ - iVar6;
    if (-1 < iVar6) goto LAB_08018c14;
LAB_08018ce4:
    iVar6 = iVar6 + hw_buffer_wrap_addr_;
  }
  else {
    iVar6 = DAT_2001dd14;
    iVar2 = __moddi3(hardware_trigger_delay_,DAT_2001dd14,1000,0);
    iVar3 = __divdi3(iVar3,iVar5,1000,0);
    iVar5 = 1;
    if ((iVar6 < 1) && ((iVar6 != 0 || (iVar2 == 0)))) {
      iVar5 = 0;
    }
    DAT_20002a50 = 0;
    if (iVar6 != 0 || iVar2 != 0) {
      DAT_20002a50 = 1000 - iVar2;
    }
    iVar6 = buffer_pointer_ - (iVar5 + iVar3);
    if (iVar6 < 0) goto LAB_08018ce4;
LAB_08018c14:
    if (hw_buffer_wrap_addr_ <= iVar6) {
      iVar6 = iVar6 - hw_buffer_wrap_addr_;
    }
  }
  if (fast_render_flag_ != '\0') {
    iVar3 = (iVar6 - DAT_20002a4c) + -0xf;
    if (iVar3 < 0) {
      iVar3 = iVar3 + hw_buffer_wrap_addr_;
    }
    FUN_080173f4(&ch1_DAT_2001d2a0,iVar3,param_1,0);
    if (ch2_enabled != '\x01') {
      return;
    }
    FUN_080173f4(&ch2_DAT_2001a618,iVar3,param_1);
    return;
  }
  if (ch2_enabled == '\0') {
    uVar4 = 6000;
    if (6000 < param_1) {
LAB_08018c96:
      uVar7 = ((param_1 - (param_1 / uVar4) * uVar4 & 0xffff) != 0) + (param_1 / uVar4 & 0xffff);
      goto LAB_08018c34;
    }
  }
  else if (ch2_enabled == '\x01') {
    uVar4 = 3000;
    uVar7 = 1;
    if (param_1 < 0xbb9) goto LAB_08018c34;
    goto LAB_08018c96;
  }
  uVar7 = 1;
LAB_08018c34:
  FUN_080173f4(&DAT_2001bb30,iVar6,param_1 / uVar7,0);
  if (ch2_enabled == '\x01') {
    FUN_080173f4(&DAT_2001af78,iVar6,param_1 / uVar7);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_08018d24(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = _global_settings * 0.0 * 0.0;
  uVar1 = uVar2 / 100;
  FUN_08018bbc(uVar1 + (uVar2 != uVar1 * 100) & 0xffff);
  return;
}




void FUN_08018d68(uint *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  uint uVar7;
  uint *puVar8;
  short sVar9;
  int iVar10;
  uint uVar11;
  uint *puVar12;
  float in_vr0;
  float fVar13;
  short local_20;
  
  iVar10 = param_2;
  uVar1 = __floatunsidf(param_4);
  __divdf3(0,0x41086a00,uVar1,iVar10);
  __truncdfsf2();
  if (param_3 == 0) {
    return;
  }
  uVar11 = 0;
  puVar8 = param_1 + 0x1f;
  puVar12 = param_1 + (param_3 - 1U & 0x7fff) + 1;
  sVar9 = 1;
  fVar13 = in_vr0;
  do {
    iVar10 = 0;
    do {
      local_20 = fVar13;
      if (local_20 == sVar9) {
        fVar13 = fVar13 + in_vr0;
        if (render_scale_factor__1M_timebase_ns < 0x4e21) goto LAB_08018e1e;
        if (global_settings == 0) {
          if (ch2_enabled == '\0') {
            if ((sample_rate_hz_h < 1) && ((sample_rate_hz_h != 0 || (sample_rate_hz_l < 250000000)))) goto LAB_08018e1e;
            goto LAB_08018e6a;
          }
          if ((0 < sample_rate_hz_h) || ((sample_rate_hz_h == 0 && (124999999 < sample_rate_hz_l)))) goto LAB_08018e6a;
LAB_08018e1e:
          puVar6 = &DAT_08054cf0 + iVar10;
          iVar3 = 0;
          puVar2 = param_1;
          do {
            uVar4 = *puVar2;
            puVar2 = puVar2 + 1;
            uVar7 = *puVar6;
            puVar6 = puVar6 + 2;
            iVar5 = (uVar7 & 0xffff) * (uVar4 & 0xffff);
            iVar3 = iVar3 + iVar5;
          } while (puVar8 != puVar2);
        }
        else {
LAB_08018e6a:
          puVar6 = &DAT_080551c8 + iVar10;
          iVar3 = 0;
          puVar2 = param_1;
          do {
            uVar4 = *puVar2;
            puVar2 = puVar2 + 1;
            uVar7 = *puVar6;
            puVar6 = puVar6 + 2;
            iVar5 = (uVar7 & 0xffff) * (uVar4 & 0xffff);
            iVar3 = iVar3 + iVar5;
          } while (puVar8 != puVar2);
        }
        iVar3 = (iVar3 < 0x7f8000) * iVar5 + (iVar3 >= 0x7f8000) * 0x7f8000;
        *(param_2 + uVar11) = (-1 < iVar3) * iVar3 >> 0xf;
        uVar11 = uVar11 + 1 & 0x7fff;
        if (uVar11 == 0x2a8) {
          return;
        }
      }
      iVar10 = iVar10 + 0x3e;
      sVar9 = sVar9 + 1;
    } while (iVar10 != 0x4d8);
    param_1 = param_1 + 1;
    puVar8 = puVar8 + 1;
    if (puVar12 == param_1) {
      return;
    }
  } while( true );
}




void FUN_08018eb8(void)

{
  bool bVar1;
  uint16_t uVar2;
  bool bVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  
  uVar2 = trigger_level_raw_adc__0_255;
  if (global_settings == 0) {
    uVar2 = trigger_level_raw_adc_buffer;
  }
  iVar7 = uVar2 - 2;
  iVar6 = uVar2 + 2;
  iVar8 = (iVar7 < 10) * 10 + (iVar7 >= 10) * iVar7;
  iVar7 = (iVar6 < 0xf0) * iVar6 + (iVar6 >= 0xf0) * 0xf0;
  iVar6 = (buffer_pointer_ - DAT_20002a4c) + -0xf;
  if (iVar6 < 0) {
    iVar6 = iVar6 + hw_buffer_wrap_addr_;
  }
  FUN_080173f4(&ch1_DAT_2001d2a0,iVar6,DAT_20002a4c * 2 + 0x1f,trigger_source_0_ch1_1_ch2 != '\0',1);
  iVar6 = DAT_20002a4c;
  DAT_20002a58 = (render_scale_factor__1M_timebase_ns * DAT_20002a4c) / 20000;
  pbVar5 = &DAT_2001bb30;
  FUN_08018d68(&ch1_DAT_2001d2a0,&DAT_2001bb30,DAT_20002a4c * 2 & 0xffff);
  bVar1 = trigger_level_raw_adc__0_255 < DAT_2001bb30;
  uVar9 = (iVar6 * render_scale_factor__1M_timebase_ns * 2) / 10000;
  if (1 < uVar9) {
    uVar4 = 1;
    bVar3 = false;
    do {
      pbVar5 = pbVar5 + 1;
      if (*pbVar5 < iVar7) {
        if (*pbVar5 <= (iVar7 < iVar8) * iVar8 + (iVar7 >= iVar8) * iVar8) {
          bVar3 = false;
        }
        if (trigger_edge_0_rise_1_fall == '\0') goto LAB_08018f78;
LAB_08018f98:
        if (((trigger_edge_0_rise_1_fall == '\x01') && (bVar1)) && (!bVar3)) {
          DAT_20002a58 = uVar4;
          return;
        }
      }
      else {
        bVar3 = true;
        if (trigger_edge_0_rise_1_fall != '\0') goto LAB_08018f98;
LAB_08018f78:
        if ((!bVar1) && (bVar3)) {
          DAT_20002a58 = uVar4;
          return;
        }
      }
      bVar1 = bVar3;
      uVar4 = uVar4 + 1;
      bVar3 = bVar1;
    } while (uVar9 != uVar4);
  }
  return;
}




void FUN_08018fdc(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar1 = (DAT_20002a50 * render_scale_factor__1M_timebase_ns) / 10000000 + DAT_20002a58;
  puVar3 = &DAT_2001bb30;
  puVar2 = &DAT_2001bb30 + iVar1;
  iVar4 = 300;
  do {
    uVar5 = *puVar2;
    puVar2 = puVar2 + 1;
    *puVar3 = uVar5;
    puVar3 = puVar3 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if (ch2_enabled != '\x01') {
    return;
  }
  if (timebase_val_ns_l == 10) {
    if (timebase_val_ns_h == 0) {
      iVar4 = 10;
      goto LAB_0801902e;
    }
  }
  else if (timebase_val_ns_l == 0x14) {
    if (timebase_val_ns_h == 0) {
      iVar4 = 4;
      goto LAB_0801902e;
    }
  }
  else if ((timebase_val_ns_l == 0x32) && (timebase_val_ns_h == 0)) {
    iVar4 = 2;
    goto LAB_0801902e;
  }
  iVar4 = 0;
LAB_0801902e:
  puVar3 = &DAT_2001af78;
  puVar2 = &DAT_2001af78 + iVar4 + iVar1;
  iVar1 = 300;
  do {
    uVar5 = *puVar2;
    puVar2 = puVar2 + 1;
    *puVar3 = uVar5;
    puVar3 = puVar3 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}




void generate_interpolated__FUN_08019078(void)

{
  int iVar1;
  uint uVar2;
  
  if (render_scale_factor__1M_timebase_ns == 200000) {
    iVar1 = 0x2e;
  }
  else if (render_scale_factor__1M_timebase_ns == 0x1e848) {
    iVar1 = 0x37;
  }
  else if (render_scale_factor__1M_timebase_ns == 100000) {
    iVar1 = 0x3d;
  }
  else if (render_scale_factor__1M_timebase_ns == 50000) {
    iVar1 = 0x5b;
  }
  else if (render_scale_factor__1M_timebase_ns == 40000) {
    iVar1 = 0x6a;
  }
  else if (render_scale_factor__1M_timebase_ns == 25000) {
    iVar1 = 0x97;
  }
  else if (render_scale_factor__1M_timebase_ns == 20000) {
    iVar1 = 0xb5;
  }
  else if (render_scale_factor__1M_timebase_ns == 0x30d4) {
    iVar1 = 0x10f;
  }
  else {
    iVar1 = 0x14b;
  }
  DAT_20002a4c = 1000000 / render_scale_factor__1M_timebase_ns;
  FUN_08018eb8();
  FUN_08018bbc(DAT_20002a4c * 2 + iVar1 & 0xffff);
  uVar2 = iVar1 + DAT_20002a4c * 2 + -0x1f & 0xffff;
  FUN_08018d68(&ch1_DAT_2001d2a0,&DAT_2001bb30,uVar2,render_scale_factor__1M_timebase_ns);
  if (ch2_enabled == '\x01') {
    FUN_08018d68(&ch2_DAT_2001a618,&DAT_2001af78,uVar2,render_scale_factor__1M_timebase_ns);
  }
  FUN_08018fdc();
  DAT_20002a54 = DAT_20002a54 + 1;
  if (DAT_20002a54 == 10) {
    DAT_20002a54 = 0;
  }
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void FUN_08019190(int param_1,undefined4 param_2)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = DAT_2001dd14;
  iVar3 = hardware_trigger_delay_;
  if ((DAT_2001dd14 < 1) && ((DAT_2001dd14 != 0 || (hardware_trigger_delay_ == 0)))) {
    iVar4 = __divdi3(hardware_trigger_delay_,DAT_2001dd14,1000,0);
    lVar1 = -CONCAT44(iVar5,iVar3);
    DAT_20002a50 = __moddi3(lVar1,lVar1 >> 0x20,1000,0);
    iVar4 = buffer_pointer_ - iVar4;
  }
  else {
    iVar4 = DAT_2001dd14;
    iVar2 = __moddi3(hardware_trigger_delay_,DAT_2001dd14,1000,0);
    iVar3 = __divdi3(iVar3,iVar5,1000,0);
    iVar5 = 1;
    if ((iVar4 < 1) && ((iVar4 != 0 || (iVar2 == 0)))) {
      iVar5 = 0;
    }
    DAT_20002a50 = 0;
    if (iVar4 != 0 || iVar2 != 0) {
      DAT_20002a50 = 1000 - iVar2;
    }
    iVar4 = buffer_pointer_ - (iVar5 + iVar3);
  }
  if (iVar4 < 0) {
    iVar4 = iVar4 + hw_buffer_wrap_addr_;
  }
  else if (hw_buffer_wrap_addr_ <= iVar4) {
    iVar4 = iVar4 - hw_buffer_wrap_addr_;
  }
  FUN_080173f4(&DAT_2001bb30,param_1 + iVar4,param_2,0);
  if (ch2_enabled == '\x01') {
    FUN_080173f4(&DAT_2001af78,param_1 + iVar4,param_2);
    return;
  }
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void zw_scope_measurements_calc_vpp_avg_rms__08019288(int *param_1,uint *param_2,char param_3,uint param_4)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  ulonglong uVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  double *pdVar9;
  int iVar10;
  uint uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  ushort uVar20;
  int iVar21;
  ushort uVar22;
  int iVar23;
  ushort in_stack_000004b0;
  double __x;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  
  uVar1 = param_4 & 0x7f;
  uVar15 = in_stack_000004b0;
  uVar11 = param_4 >> 8 & 0xff;
  uVar8 = uVar15;
  if (param_3 == '\0') {
    uVar12 = ch1_vert_offset_buffer_10uV_l;
    uVar13 = ch1_vert_offset_buffer_10uV_h;
    if (global_settings != 0) {
      uVar12 = ch1_vert_offset_10uV_l;
      uVar13 = ch1_vert_offset_10uV_h;
    }
    uVar19 = ch1_gain_cal_;
    uVar18 = ch1_volt_scale_10uV;
    if (uVar15 == 0) {
      lVar3 = 0;
      iVar14 = ch1_volt_scale_10uV / 0x19;
      uVar22 = 0x80;
      uVar20 = 0xff80;
      lVar4 = 0;
    }
    else {
LAB_08019308:
      uVar8 = 0;
      iVar14 = uVar18 / 0x19;
      lVar4 = 0;
      iVar23 = 0x80;
      iVar21 = -0x80;
      uVar6 = 0;
      do {
        iVar10 = *param_1;
        param_1 = param_1 + 1;
        iVar10 = iVar10 + -0x80;
        uVar5 = iVar10 * iVar14 - CONCAT44(uVar13,uVar12);
        uVar6 = uVar6 + 1;
        lVar3 = (uVar5 & 0xffffffff) * (uVar5 & 0xffffffff);
        uVar8 = uVar8 + iVar10;
        lVar4 = lVar4 + CONCAT44((uVar5 >> 0x20) * uVar5 * 2 + (lVar3 >> 0x20),lVar3);
        iVar21 = (iVar21 < iVar10) * iVar10 + (iVar21 >= iVar10) * iVar21;
        iVar23 = (iVar23 < iVar10) * iVar23 + (iVar23 >= iVar10) * iVar10;
      } while (uVar6 < uVar15);
      uVar20 = iVar21 & 0x7fff;
      uVar22 = iVar23 & 0x7fff;
      lVar3 = uVar8 * iVar14;
      if (param_3 != '\0') goto LAB_08019388;
    }
    DAT_20002a5c = uVar20;
    DAT_20002a5e = uVar22;
    uVar20 = DAT_20002a60;
    uVar22 = DAT_20002a62;
  }
  else {
    uVar12 = ch2_vert_offset_buffer_10uV_l;
    uVar13 = ch2_vert_offset_buffer_10uV_h;
    if (global_settings != 0) {
      uVar12 = ch2_vert_offset_10uV_l;
      uVar13 = ch2_vert_offset_10uV_h;
    }
    uVar19 = ch2_gain_cal_;
    uVar18 = ch2_volt_scale_10uV;
    if (uVar15 != 0) goto LAB_08019308;
    lVar3 = 0;
    iVar14 = ch2_volt_scale_10uV / 0x19;
    lVar4 = 0;
    uVar20 = 0xff80;
    uVar22 = 0x80;
  }
LAB_08019388:
  DAT_20002a62 = uVar22;
  DAT_20002a60 = uVar20;
  uVar16 = lVar4 >> 0x20;
  DAT_20002a6c = uVar8 / uVar15;
  uVar5 = (uVar1 - 0x80) * iVar14 - CONCAT44(uVar13,uVar12);
  lVar2 = (uVar5 & 0xffffffff) * uVar19;
  uVar8 = (lVar2 >> 0x20) + uVar19 * (uVar5 >> 0x20);
  uVar6 = __divdi3(lVar2,uVar8,0x3f2,0);
  param_2[8] = uVar6;
  param_2[9] = uVar8;
  __x = CONCAT44(uVar8,uVar6);
  uVar5 = (uVar11 - 0x80) * iVar14 - CONCAT44(uVar13,uVar12);
  lVar2 = (uVar5 & 0xffffffff) * uVar19;
  uVar8 = (lVar2 >> 0x20) + uVar19 * (uVar5 >> 0x20);
  uVar6 = __divdi3(lVar2,uVar8,0x3f2,0);
  uStack_3c = lVar3;
  uStack_38 = lVar3 >> 0x20;
  *param_2 = __x - CONCAT44(uVar8,uVar6);
  param_2[10] = uVar6;
  param_2[0xb] = uVar8;
  uVar7 = __divdi3(uStack_3c,uStack_38,uVar15,0);
  uVar5 = CONCAT44(uStack_38,uVar7) - CONCAT44(uVar13,uVar12);
  lVar3 = (uVar5 & 0xffffffff) * uVar19;
  uVar8 = (lVar3 >> 0x20) + uVar19 * (uVar5 >> 0x20);
  uVar19 = __divdi3(lVar3,uVar8,0x3ca,0);
  param_2[0xc] = uVar19;
  param_2[0xd] = uVar8;
  uVar8 = __divdi3(lVar4,uVar16,uVar15,0);
  if ((uVar16 < 1) && ((uVar16 != 0 || (uVar8 < 0x77359401)))) {
    pdVar9 = __floatsidf();
    sqrt(pdVar9,__x);
    uVar8 = __fixdfdi();
    param_2[0xe] = uVar8;
    param_2[0xf] = uVar16;
  }
  else if ((uVar16 < 0x1231) && ((uVar16 != 0x1230 || (uVar8 < 0x9ce56710)))) {
    __divdi3();
    pdVar9 = __floatsidf();
    sqrt(pdVar9,__x);
    __muldf3();
    uVar8 = __fixdfdi();
    param_2[0xe] = uVar8;
    param_2[0xf] = uVar16;
  }
  else if ((uVar16 < 0x71afe) && ((uVar16 != 0x71afd || (uVar8 < 0x499c4240)))) {
    __divdi3();
    pdVar9 = __floatsidf();
    sqrt(pdVar9,__x);
    __muldf3();
    uVar8 = __fixdfdi();
    param_2[0xe] = uVar8;
    param_2[0xf] = uVar16;
  }
  else {
    __divdi3();
    pdVar9 = __floatsidf();
    sqrt(pdVar9,__x);
    __muldf3();
    uVar8 = __fixdfdi();
    param_2[0xe] = uVar8;
    param_2[0xf] = uVar16;
  }
  if ((uVar11 < 6) || (0xfa < uVar1)) {
    *param_2 = 1;
    param_2[1] = 0;
  }
  else if (uVar1 - uVar11 < 10) {
    *param_2 = 0;
    param_2[1] = 0;
  }
  uVar8 = uVar18;
  if ((uVar18 & 0x80000000) != 0) {
    uVar8 = uVar18 + 3;
  }
  uVar8 = -(uVar8 >> 2);
  uVar19 = param_2[0xb];
  uVar15 = uVar8 >> 0x1f;
  if ((uVar15 < uVar19) || ((uVar19 == uVar15 && (uVar8 < param_2[10])))) {
    uVar6 = uVar18;
    if ((uVar18 & 0x80000000) != 0) {
      uVar6 = uVar18 + 3;
    }
    uVar16 = uVar6 >> 0x1f;
    if ((uVar19 < uVar16) || ((uVar16 == uVar19 && (param_2[10] < uVar6 >> 2)))) {
      uVar19 = param_2[9];
      if (((uVar15 < uVar19) || ((uVar19 == uVar15 && (uVar8 < param_2[8])))) && ((uVar19 < uVar16 || ((uVar16 == uVar19 && (param_2[8] < uVar6 >> 2)))))) {
        param_2[10] = 0;
        param_2[0xb] = 0;
        param_2[8] = 0;
        param_2[9] = 0;
        *param_2 = 0;
        param_2[1] = 0;
      }
    }
  }
  if ((uVar1 - 6 & 0xff) < 0xf5) {
    uVar19 = param_2[0xd];
    if ((param_2[9] < uVar19) || ((param_2[9] == uVar19 && (param_2[8] < param_2[0xc])))) {
      param_2[8] = param_2[0xc];
      param_2[9] = uVar19;
    }
  }
  else {
    param_2[8] = 1;
    param_2[9] = 0;
  }
  if ((uVar11 - 6 & 0xff) < 0xf5) {
    uVar19 = param_2[0xd];
    if ((uVar19 < param_2[0xb]) || ((param_2[0xb] == uVar19 && (param_2[0xc] < param_2[10])))) {
      param_2[0xb] = uVar19;
      param_2[10] = param_2[0xc];
    }
joined_r0x080196be:
    if (uVar1 < 0xfb) {
      uVar19 = param_2[1];
      if ((uVar19 < 1) && ((uVar19 != 0 || (*param_2 < 2)))) {
        uVar6 = param_2[0xd];
        uVar17 = param_2[0xc];
        if ((uVar15 < uVar6) || ((uVar6 == uVar15 && (uVar8 < uVar17)))) {
          uVar16 = uVar18;
          if ((uVar18 & 0x80000000) != 0) {
            uVar16 = uVar18 + 3;
          }
          if ((uVar16 >> 0x1f <= uVar6) && ((uVar16 >> 0x1f != uVar6 || (uVar16 >> 2 <= uVar17)))) goto LAB_080197b0;
LAB_0801981a:
          param_2[0xc] = 0;
          param_2[0xd] = 0;
LAB_080197dc:
          if ((0 < uVar19) || ((uVar19 == 0 && (1 < *param_2)))) goto LAB_080196e6;
        }
        else {
LAB_080197b0:
          uVar16 = uVar18 / -0x32 >> 0x1f;
          if ((uVar16 < uVar6) || ((uVar6 == uVar16 && (uVar18 / -0x32 < uVar17)))) goto LAB_080197ca;
        }
        uVar19 = param_2[0xf];
        uVar6 = param_2[0xe];
        if ((uVar19 <= uVar15) && ((uVar19 != uVar15 || (uVar6 <= uVar8)))) goto LAB_080196ec;
        uVar8 = uVar18;
        if ((uVar18 & 0x80000000) != 0) {
          uVar8 = uVar18 + 3;
        }
        if ((uVar8 >> 0x1f <= uVar19) && ((uVar8 >> 0x1f != uVar19 || (uVar8 >> 2 <= uVar6)))) goto LAB_080196ec;
      }
      else {
        uVar6 = param_2[0xd];
        uVar16 = uVar18 / -0x32 >> 0x1f;
        uVar17 = param_2[0xc];
        if ((uVar16 < uVar6) || ((uVar6 == uVar16 && (uVar18 / -0x32 < uVar17)))) {
LAB_080197ca:
          uVar16 = uVar18 / 0x32 >> 0x1f;
          if ((uVar6 < uVar16) || ((uVar16 == uVar6 && (uVar17 < uVar18 / 0x32)))) goto LAB_0801981a;
          goto LAB_080197dc;
        }
LAB_080196e6:
        uVar6 = param_2[0xe];
        uVar19 = param_2[0xf];
LAB_080196ec:
        uVar8 = uVar18 / -0x32 >> 0x1f;
        if ((uVar19 <= uVar8) && ((uVar19 != uVar8 || (uVar6 <= uVar18 / -0x32)))) goto LAB_0801950a;
        uVar8 = uVar18 / 0x32 >> 0x1f;
        if ((uVar8 <= uVar19) && ((uVar8 != uVar19 || (uVar18 / 0x32 <= uVar6)))) goto LAB_0801950a;
      }
      param_2[0xe] = 0;
      param_2[0xf] = 0;
      goto LAB_0801950a;
    }
    param_2[0xc] = 1;
    param_2[0xd] = 0;
  }
  else {
    param_2[10] = 1;
    param_2[0xb] = 0;
    if (5 < uVar11) goto joined_r0x080196be;
    param_2[0xc] = 1;
    param_2[0xd] = 0;
  }
  param_2[0xe] = 1;
  param_2[0xf] = 0;
LAB_0801950a:
  if (uVar1 < uVar11) {
    *param_2 = 1;
    param_2[1] = 0;
    param_2[0xc] = 1;
    param_2[0xd] = 0;
    param_2[0xe] = 1;
    param_2[0xf] = 0;
    param_2[8] = 1;
    param_2[9] = 0;
    param_2[10] = 1;
    param_2[0xb] = 0;
  }
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void zw_scope_measurements_calc_top_base_amp__08019848(byte *param_1,int param_2,char param_3,uint param_4)

{
  byte bVar1;
  uint uVar3;
  ushort uVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  byte *pbVar13;
  undefined4 uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  ushort in_stack_000004b0;
  byte bVar2;
  
  uVar20 = in_stack_000004b0;
  uVar18 = param_4 >> 8 & 0xff;
  if (param_3 == '\0') {
    uVar8 = ch1_vert_offset_buffer_10uV_l;
    uVar14 = ch1_vert_offset_buffer_10uV_h;
    iVar11 = ch1_volt_scale_10uV;
    uVar4 = ch1_gain_cal_;
    bVar1 = DAT_20002a5e;
    bVar2 = DAT_20002a5c;
    if (global_settings != 0) {
      uVar8 = ch1_vert_offset_10uV_l;
      uVar14 = ch1_vert_offset_10uV_h;
    }
  }
  else {
    uVar8 = ch2_vert_offset_buffer_10uV_l;
    uVar14 = ch2_vert_offset_buffer_10uV_h;
    iVar11 = ch2_volt_scale_10uV;
    uVar4 = ch2_gain_cal_;
    bVar1 = DAT_20002a62;
    bVar2 = DAT_20002a60;
    if (global_settings != 0) {
      uVar8 = ch2_vert_offset_10uV_l;
      uVar14 = ch2_vert_offset_10uV_h;
    }
  }
  uVar17 = uVar4;
  uVar16 = bVar2 ^ 0x80;
  uVar15 = bVar1 ^ 0x80;
  uVar3 = (uVar16 + uVar15) / 2;
  uVar12 = uVar16 - uVar3;
  if ((uVar12 & 0x80000000) != 0) {
    uVar12 = uVar12 + 3;
  }
  uVar19 = (uVar3 & 0x7f) + (uVar12 >> 2) & 0xff;
  uVar12 = uVar16;
  if (uVar19 < uVar16) {
    uVar21 = 0;
    do {
      if (uVar20 != 0) {
        uVar9 = 0;
        pbVar13 = param_1;
        do {
          while ((uVar19 == *pbVar13 || (*pbVar13 == uVar19 + 1))) {
            pbVar13 = pbVar13 + 1;
            uVar9 = uVar9 + 1 & 0xffff;
            if (param_1 + (uVar20 - 1 & 0x7fff) + 1 == pbVar13) goto LAB_08019922;
          }
          pbVar13 = pbVar13 + 1;
        } while (param_1 + (uVar20 - 1 & 0x7fff) + 1 != pbVar13);
LAB_08019922:
        if ((uVar21 < uVar9) && (uVar20 / 0x14 <= uVar9)) {
          uVar21 = uVar9 & 0x7f;
          uVar12 = uVar19 & 0xff;
        }
      }
      uVar19 = uVar19 + 2 & 0xffff;
    } while (uVar19 < uVar16);
  }
  uVar16 = uVar3 - uVar15;
  if ((uVar16 & 0x80000000) != 0) {
    uVar16 = uVar16 + 3;
  }
  uVar3 = (uVar3 & 0x7f) - (uVar16 >> 2) & 0x7f;
  if (uVar15 < uVar3) {
    uVar16 = 0;
    uVar19 = uVar15;
    do {
      if (uVar20 != 0) {
        uVar21 = 0;
        pbVar13 = param_1;
        do {
          while ((uVar19 == *pbVar13 || (*pbVar13 == uVar19 + 1))) {
            pbVar13 = pbVar13 + 1;
            uVar21 = uVar21 + 1 & 0xffff;
            if (pbVar13 == param_1 + (uVar20 - 1 & 0x7fff) + 1) goto LAB_080199aa;
          }
          pbVar13 = pbVar13 + 1;
        } while (pbVar13 != param_1 + (uVar20 - 1 & 0x7fff) + 1);
LAB_080199aa:
        if ((uVar16 < uVar21) && (uVar20 / 0x14 <= uVar21)) {
          uVar16 = uVar21 & 0x7f;
          uVar15 = uVar19 & 0xff;
        }
      }
      uVar19 = uVar19 + 2 & 0xffff;
    } while (uVar19 < uVar3);
  }
  uVar6 = (iVar11 * (uVar12 - 0x80)) / 0x19 - CONCAT44(uVar14,uVar8);
  lVar5 = (uVar6 & 0xffffffff) * uVar17;
  iVar10 = (lVar5 >> 0x20) + uVar17 * (uVar6 >> 0x20);
  uVar7 = __divdi3(lVar5,iVar10,1000,0);
  uVar6 = ((uVar15 - 0x80) * iVar11) / 0x19 - CONCAT44(uVar14,uVar8);
  *(param_2 + 0x10) = uVar7;
  *(param_2 + 0x14) = iVar10;
  lVar5 = (uVar6 & 0xffffffff) * uVar17;
  iVar11 = (lVar5 >> 0x20) + uVar17 * (uVar6 >> 0x20);
  uVar8 = __divdi3(lVar5,iVar11,1000,0);
  *(param_2 + 0x18) = uVar8;
  *(param_2 + 0x1c) = iVar11;
  if ((uVar18 < 6) || (0xfa < (param_4 & 0xff))) {
    *(param_2 + 8) = 1;
    *(param_2 + 0xc) = 0;
  }
  else if (uVar12 - uVar15 < 10) {
    *(param_2 + 8) = 0;
    *(param_2 + 0xc) = 0;
  }
  else {
    *(param_2 + 8) = CONCAT44(iVar10,uVar7) - CONCAT44(iVar11,uVar8);
  }
  if (0xf4 < (uVar12 - 6 & 0xff)) {
    *(param_2 + 0x10) = 1;
    *(param_2 + 0x14) = 0;
  }
  if (0xf4 < (uVar15 - 6 & 0xff)) {
    *(param_2 + 0x18) = 1;
    *(param_2 + 0x1c) = 0;
  }
  if ((param_4 & 0xff) < uVar18) {
    *(param_2 + 0x18) = 1;
    *(param_2 + 0x1c) = 0;
    *(param_2 + 0x10) = 1;
    *(param_2 + 0x14) = 0;
    *(param_2 + 8) = 1;
    *(param_2 + 0xc) = 0;
  }
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register
// WARNING: Restarted to delay deadcode elimination for space: stack


void FUN_08019b0c(int param_1,int param_2,char param_3,uint param_4)

{
  short sVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  longlong lVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  uint *puVar8;
  short sVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  undefined4 *puVar14;
  uint *puVar15;
  uint uVar16;
  int iVar17;
  uint uVar18;
  int iVar19;
  char cVar20;
  char cVar21;
  ushort uVar22;
  uint uVar23;
  uint uVar24;
  ushort in_stack_000004b0;
  uint local_1c4 [50];
  uint local_fc [50];
  
  uVar10 = param_4 >> 8 & 0xff;
  uVar24 = in_stack_000004b0;
  sVar9 = DAT_20002a60;
  sVar1 = DAT_20002a62;
  if (param_3 == '\0') {
    sVar9 = DAT_20002a5c;
    sVar1 = DAT_20002a5e;
  }
  uVar11 = sVar9 - DAT_20002a6c;
  uVar12 = uVar11;
  if ((uVar11 & 0x80000000) != 0) {
    uVar12 = uVar11 + 3;
  }
  sVar9 = (uVar12 >> 2) + DAT_20002a6c;
  iVar19 = sVar9;
  iVar17 = uVar11 / 2 + DAT_20002a6c;
  if (iVar17 <= iVar19 + 4) {
    iVar17 = sVar9 + 5;
  }
  uVar11 = DAT_20002a6c - sVar1;
  uVar12 = uVar11;
  if ((uVar11 & 0x80000000) != 0) {
    uVar12 = uVar11 + 3;
  }
  uVar13 = DAT_20002a6c - uVar11 / 2;
  uVar11 = uVar13 & 0x7fff;
  uVar12 = DAT_20002a6c - (uVar12 >> 2) & 0x7fff;
  if (uVar12 <= uVar11 + 4) {
    uVar12 = (uVar13 & 0xffff) + 5 & 0x7fff;
  }
  if (uVar24 == 0) {
    uVar18 = 0;
    if (DAT_20002a68 != 0) {
      uVar3 = 0;
      uVar16 = 0;
      uVar24 = 0;
      uVar12 = 0;
LAB_08019c60:
      iVar7 = timebase_val_ns_h;
      uVar11 = timebase_val_ns_l;
      iVar19 = DAT_20002a68;
      uVar2 = timebase_val_ns_l * (uVar3 & 0xffffffff);
      lVar4 = (uVar2 & 0xffffffff) * 1000000;
      iVar17 = (lVar4 >> 0x20) + ((uVar2 >> 0x20) + (uVar3 >> 0x20) * timebase_val_ns_l + timebase_val_ns_h * uVar3) * 1000000;
      uVar5 = __divdi3(lVar4,iVar17,DAT_20002a68);
      *(param_2 + 0x40) = uVar5;
      *(param_2 + 0x44) = iVar17;
      uVar3 = uVar11 * uVar12;
      lVar4 = (uVar3 & 0xffffffff) * 1000000;
      iVar17 = (lVar4 >> 0x20) + ((uVar3 >> 0x20) + uVar24 * uVar11 + iVar7 * uVar12) * 1000000;
      uVar5 = __divdi3(lVar4,iVar17,iVar19,0);
      *(param_2 + 0x48) = uVar5;
      *(param_2 + 0x4c) = iVar17;
LAB_08019cc4:
      if (uVar16 != 0) goto LAB_08019cc8;
    }
    *(param_2 + 0x40) = 0;
    *(param_2 + 0x44) = 0;
    if ((uVar18 != 0) && (0x13 < (param_4 & 0xff) - uVar10)) {
      return;
    }
  }
  else {
    uVar18 = 0;
    sVar9 = 1;
    uVar22 = 1;
    uVar16 = 0;
    cVar20 = '\0';
    cVar21 = '\0';
    uVar13 = 0;
    do {
      iVar7 = *(param_1 + uVar13) - 0x80;
      if (cVar21 == '\x01') goto LAB_08019cfc;
      if (cVar21 == '\0') goto LAB_08019f32;
      if (cVar21 == '\x02') goto LAB_08019d88;
      while( true ) {
        if (cVar20 == '\x01') goto LAB_08019e42;
        if (cVar20 == '\0') break;
        if (cVar20 != '\x02') goto LAB_08019f52;
LAB_08019e9e:
        cVar20 = cVar21;
        uVar13 = uVar13 + 1;
        uVar23 = uVar18;
        if (iVar7 <= uVar12) goto LAB_08019d26;
LAB_08019ea6:
        uVar18 = uVar23;
        if (uVar23 < 100) {
          uVar13 = uVar13 & 0xffff;
          uVar18 = uVar23 + 1 & 0xffff;
          *(local_fc + uVar23 * 2) = sVar9;
          if (uVar24 <= uVar13) goto LAB_08019db6;
          iVar7 = *(param_1 + uVar13) - 0x80;
          sVar9 = 1;
          if (cVar20 == '\x01') {
            cVar20 = '\0';
            sVar9 = 1;
            goto LAB_08019cfc;
          }
          if (cVar20 == '\0') {
            cVar21 = iVar7 < iVar19;
          }
          else {
            cVar21 = cVar20;
            if (cVar20 == '\x02') {
              cVar20 = '\0';
              goto LAB_08019d88;
            }
          }
          break;
        }
joined_r0x08019eb2:
        uVar13 = uVar13 & 0xffff;
        if (uVar24 <= uVar13) goto LAB_08019db6;
        iVar7 = *(param_1 + uVar13) - 0x80;
        if (cVar20 == '\x01') goto LAB_0801a05e;
        if (cVar20 == '\0') {
          cVar21 = iVar7 < iVar19;
          goto LAB_08019e9e;
        }
        cVar21 = cVar20;
        if (cVar20 != '\x02') goto LAB_08019e9e;
LAB_08019d88:
        uVar23 = uVar13 + 1 & 0x7fff;
        uVar13 = uVar23 - 1 & 0xffff;
        if (iVar19 <= iVar7) {
          uVar22 = uVar22 + 1 & 0x7fff;
          cVar21 = '\x02';
          if (cVar20 == '\x01') goto LAB_08019ec0;
          if (cVar20 == '\0') {
            if (uVar24 <= uVar23) goto LAB_08019db6;
LAB_08019f78:
            cVar20 = uVar12 < iVar7;
            iVar7 = *(param_1 + uVar23) - 0x80;
            uVar13 = uVar23;
          }
          else {
            cVar21 = cVar20;
            if (cVar20 == '\x02') goto LAB_08019e9e;
            if (uVar24 <= uVar23) goto LAB_08019db6;
LAB_08019d78:
            iVar7 = *(param_1 + uVar23) - 0x80;
            uVar13 = uVar23;
          }
          goto LAB_08019d88;
        }
        if (99 < uVar16) {
          cVar21 = '\x02';
          if (cVar20 == '\x01') goto LAB_08019ec0;
          if (cVar20 == '\0') {
            if (uVar23 < uVar24) goto LAB_08019f78;
            goto LAB_08019dbc;
          }
          cVar21 = cVar20;
          if (cVar20 != '\x02') {
            if (uVar23 < uVar24) goto LAB_08019d78;
            goto LAB_08019dbc;
          }
          goto LAB_08019e9e;
        }
        *(local_1c4 + uVar16 * 2) = uVar22;
        uVar16 = uVar16 + 1 & 0xffff;
        uVar22 = 1;
        if (cVar20 == '\x01') {
          uVar13 = uVar13 + 1;
          cVar21 = '\0';
joined_r0x08019ec8:
          cVar20 = cVar21;
          uVar13 = uVar13 & 0xffff;
          if (iVar7 < uVar11) {
            if (uVar24 <= uVar13) goto LAB_08019db6;
            iVar7 = *(param_1 + uVar13) - 0x80;
            sVar9 = 1;
            if (cVar20 != '\x01') {
              if (cVar20 == '\0') {
                cVar20 = iVar7 < iVar19;
                uVar13 = uVar13 + 1;
              }
              else {
                if (cVar20 == '\x02') goto LAB_08019d88;
                uVar13 = uVar13 + 1;
              }
              goto LAB_08019d20;
            }
LAB_0801a05e:
            cVar20 = '\x02';
          }
          else {
            if (uVar24 <= uVar13) goto LAB_08019db6;
            iVar7 = *(param_1 + uVar13) - 0x80;
            if (cVar20 != '\x01') {
              if (cVar20 == '\0') {
                cVar21 = iVar7 < iVar19;
LAB_08019ec0:
                uVar13 = uVar13 + 1;
              }
              else {
                cVar21 = cVar20;
                if (cVar20 == '\x02') {
                  cVar20 = '\x01';
                  goto LAB_08019d88;
                }
LAB_08019e42:
                uVar13 = uVar13 + 1;
              }
              goto joined_r0x08019ec8;
            }
          }
LAB_08019cfc:
          while( true ) {
            uVar13 = uVar13 + 1;
            puVar14 = (uVar13 & 0xffff) + param_1;
            while( true ) {
              if (iVar17 < iVar7) {
                uVar22 = 1;
                cVar21 = '\x02';
                if (cVar20 == '\x01') goto joined_r0x08019ec8;
                if (cVar20 == '\0') {
                  cVar20 = uVar12 < iVar7;
                }
                else if (cVar20 == '\x02') goto LAB_08019d20;
                if (uVar24 <= (uVar13 & 0xffff)) goto LAB_08019db6;
                uVar13 = uVar13 & 0xffff;
                iVar7 = *(param_1 + uVar13) - 0x80;
                goto LAB_08019d88;
              }
              cVar21 = cVar20;
              if (cVar20 == '\x01') goto joined_r0x08019ec8;
              if (cVar20 == '\0') break;
              if (cVar20 == '\x02') {
                cVar20 = '\x01';
                goto LAB_08019d20;
              }
              if (uVar24 <= (uVar13 & 0xffff)) goto LAB_08019db6;
              uVar5 = *puVar14;
              puVar14 = puVar14 + 1;
              iVar7 = uVar5 + -0x80;
              uVar13 = (uVar13 & 0xffff) + 1;
            }
            cVar20 = uVar12 < iVar7;
            uVar13 = uVar13 & 0xffff;
            if (uVar24 <= uVar13) break;
            iVar7 = *(param_1 + uVar13) - 0x80;
          }
          goto LAB_08019db6;
        }
        if (cVar20 != '\0') {
          if (cVar20 != '\x02') goto joined_r0x08019f28;
          cVar20 = '\0';
          uVar13 = uVar13 + 1;
LAB_08019d20:
          uVar23 = uVar18;
          if (uVar12 < iVar7) goto LAB_08019ea6;
LAB_08019d26:
          sVar9 = sVar9 + 1;
          goto joined_r0x08019eb2;
        }
        cVar20 = uVar12 < iVar7;
joined_r0x08019f28:
        if (uVar24 <= uVar23) goto LAB_08019dbc;
        iVar7 = *(param_1 + uVar23) - 0x80;
        uVar13 = uVar23;
LAB_08019f32:
        cVar21 = iVar7 < iVar19;
      }
      cVar20 = uVar12 < iVar7;
LAB_08019f52:
      uVar13 = uVar13 + 1 & 0xffff;
    } while (uVar13 < uVar24);
LAB_08019db6:
    if (uVar16 == 0) {
      if (uVar18 != 0) {
        uVar3 = 0;
        goto LAB_08019de2;
      }
      if (DAT_20002a68 != 0) {
        uVar6 = 0;
        uVar5 = 0;
        uVar16 = 0;
        uVar24 = uVar18;
        goto LAB_0801a07e;
      }
    }
    else {
LAB_08019dbc:
      puVar15 = local_1c4;
      puVar8 = ((uVar16 - 1 & 0xffff) + 1) * 2 + puVar15;
      uVar3 = 0;
      do {
        uVar24 = *puVar15;
        puVar15 = puVar15 + 2;
        uVar3 = uVar3 + uVar24;
        uVar5 = uVar3 >> 0x20;
      } while (puVar15 != puVar8);
      if (uVar18 != 0) {
LAB_08019de2:
        puVar15 = local_fc;
        puVar8 = ((uVar18 - 1 & 0xffff) + 1) * 2 + puVar15;
        lVar4 = 0;
        do {
          uVar5 = uVar3 >> 0x20;
          uVar24 = *puVar15;
          puVar15 = puVar15 + 2;
          lVar4 = lVar4 + uVar24;
          uVar24 = lVar4 >> 0x20;
        } while (puVar8 != puVar15);
        if (uVar16 != 0) {
          uVar6 = __divdi3(uVar3,uVar5,uVar16,0);
          uVar3 = CONCAT44(uVar5,uVar6);
        }
        uVar12 = __divdi3(lVar4,uVar24,uVar18,0);
        if (DAT_20002a68 != 0) goto LAB_08019c60;
        goto LAB_08019cc4;
      }
      uVar6 = __divdi3(uVar3,uVar5,uVar16,0);
      uVar24 = uVar18;
      if (DAT_20002a68 != 0) {
LAB_0801a07e:
        uVar3 = CONCAT44(uVar5,uVar6);
        uVar18 = uVar24;
        uVar12 = uVar24;
        goto LAB_08019c60;
      }
LAB_08019cc8:
      if (0x13 < (param_4 & 0xff) - uVar10) {
        if (uVar18 != 0) {
          return;
        }
        goto LAB_08019c16;
      }
    }
    *(param_2 + 0x40) = 0;
    *(param_2 + 0x44) = 0;
  }
LAB_08019c16:
  *(param_2 + 0x48) = 0;
  *(param_2 + 0x4c) = 0;
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register
// WARNING: Restarted to delay deadcode elimination for space: stack


void FUN_0801a0e8(byte *param_1,int param_2,uint param_3,uint param_4)

{
  ushort uVar1;
  uint uVar2;
  byte bVar3;
  longlong lVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  short sVar8;
  undefined2 uVar9;
  int iVar10;
  undefined4 uVar11;
  short sVar12;
  undefined4 uVar13;
  short sVar14;
  uint uVar15;
  uint uVar16;
  ushort *puVar17;
  uint uVar18;
  uint uVar19;
  byte *pbVar20;
  bool bVar21;
  ushort uVar22;
  int iVar23;
  ushort in_stack_000004b0;
  undefined1 auStack_5bc [1200];
  uint uStack_10c;
  undefined8 uStack_108;
  uint uStack_100;
  ushort local_fc [100];
  
  uVar2 = param_3 & 0x7f;
  uVar19 = in_stack_000004b0;
  uVar18 = ch2_enabled_measurements_bitfield;
  sVar8 = DAT_20002a62;
  sVar14 = DAT_20002a60;
  if (uVar2 == 0) {
    uVar18 = ch1_enabled_measurements_bitfield;
    sVar8 = DAT_20002a5e;
    sVar14 = DAT_20002a5c;
  }
  iVar10 = sVar14 + sVar8;
  uVar15 = sVar14 - sVar8;
  sVar8 = (iVar10 - (iVar10 >> 0x1f) & 0xffffU) >> 1;
  if (system_status_ == '\x04') {
    if ((uVar15 & 0x80000000) != 0) {
      uVar15 = uVar15 + 3;
    }
    sVar14 = uVar15 >> 2;
  }
  else {
    if ((uVar15 & 0x80000000) != 0) {
      uVar15 = uVar15 + 7;
    }
    sVar14 = uVar15 >> 3;
  }
  sVar12 = sVar8 - sVar14;
  sVar8 = sVar8 + sVar14;
  if (uVar19 != 0) {
    if (sVar8 < *param_1 - 0x80) {
      uVar15 = 1;
LAB_0801a154:
      if (uVar15 < uVar19) {
        bVar3 = param_1[uVar15];
        bVar21 = true;
LAB_0801a164:
        uVar22 = bVar3;
        uVar15 = uVar15 + 1;
        pbVar20 = param_1 + (uVar15 & 0x7fff);
LAB_0801a16e:
        if (sVar8 < uVar22 - 0x80) {
          if (bVar21) goto LAB_0801a1f8;
          if ((uVar15 & 0xffff) < uVar19) {
            bVar3 = param_1[uVar15 & 0xffff];
            uStack_108._0_4_ = 1;
LAB_0801a18c:
            sVar14 = bVar3 - 0x80;
            uVar16 = (uVar15 & 0xffff) + 1 & 0xffff;
            uVar22 = 1;
            uVar15 = 0;
            iVar10 = uStack_108;
            if (sVar8 < sVar14) goto LAB_0801a1d4;
LAB_0801a1a4:
            iVar23 = iVar10;
            if (sVar14 < sVar12) {
              iVar23 = 0;
              goto LAB_0801a1d8;
            }
LAB_0801a1b8:
            uVar22 = uVar22 + 1 & 0x7fff;
            iVar10 = iVar23;
            while (uVar16 < uVar19) {
              bVar3 = param_1[uVar16];
              while( true ) {
                sVar14 = bVar3 - 0x80;
                uVar16 = uVar16 + 1 & 0xffff;
                if (sVar14 <= sVar8) goto LAB_0801a1a4;
LAB_0801a1d4:
                iVar23 = 1;
LAB_0801a1d8:
                if (iVar23 == iVar10) goto LAB_0801a1b8;
                if (uVar15 < 100) break;
                if (uVar19 <= uVar16) goto LAB_0801a2ac;
                bVar3 = param_1[uVar16];
              }
              local_fc[uVar15] = uVar22;
              uVar15 = uVar15 + 1 & 0x7fff;
              uVar22 = 1;
              iVar10 = iVar23;
            }
LAB_0801a2ac:
            uVar15 = uVar15 >> 1;
            if ((uVar18 & 0xc0) != 0) goto LAB_0801a374;
            goto LAB_0801a2b8;
          }
          uStack_108._0_4_ = 1;
          goto LAB_0801a23a;
        }
        if ((uVar22 - 0x80 < sVar12) && (bVar21)) {
          if ((uVar15 & 0xffff) < uVar19) {
            bVar3 = param_1[uVar15 & 0xffff];
            uStack_108._0_4_ = 0;
            goto LAB_0801a18c;
          }
        }
        else {
LAB_0801a1f8:
          if ((uVar15 & 0xffff) < uVar19) goto code_r0x0801a1fe;
        }
      }
    }
    else if (*param_1 - 0x80 < sVar12) {
      uVar15 = 1;
LAB_0801a32c:
      if (uVar15 < uVar19) {
        bVar3 = param_1[uVar15];
        bVar21 = false;
        goto LAB_0801a164;
      }
    }
    else if (1 < uVar19) {
      uVar15 = 1;
      pbVar20 = param_1;
      do {
        pbVar20 = pbVar20 + 1;
        uVar15 = uVar15 + 1 & 0xffff;
        if (sVar8 < *pbVar20 - 0x80) goto LAB_0801a154;
        if (*pbVar20 - 0x80 < sVar12) goto LAB_0801a32c;
      } while (uVar19 != uVar15);
    }
  }
  uStack_108._0_4_ = 0;
LAB_0801a23a:
  if ((uVar18 & 0xc0) != 0) {
    uVar15 = 0;
LAB_0801a374:
    uStack_10c = uVar19;
    uStack_100 = uVar15;
    memcpy(auStack_5bc,&stack0x00000000,0x4ae);
    FUN_08019b0c(param_1,param_2,param_3,param_4);
    uVar15 = uStack_100;
LAB_0801a2b8:
    iVar10 = DAT_20002a68;
    if (((uVar15 != 0) && (0x13 < (param_4 & 0xff) - (param_4 >> 8 & 0xff))) && (DAT_20002a68 != 0)) {
      uVar5 = 0;
      puVar17 = local_fc;
      uVar7 = 0;
      uVar18 = 0;
      do {
        if (uStack_108 == 1) {
          uVar22 = *puVar17;
          uVar1 = puVar17[1];
        }
        else {
          uVar22 = puVar17[1];
          uVar1 = *puVar17;
        }
        uVar7 = uVar7 + uVar22;
        uVar19 = uVar18 + 1;
        uVar18 = uVar19 & 0xffff;
        uVar5 = uVar5 + uVar1;
        puVar17 = puVar17 + 2;
      } while (uVar18 != uVar15);
      uVar6 = uVar5 + uVar7;
      uVar11 = uVar6 >> 0x20;
      lVar4 = (uVar7 & 0xffffffff) * 1000;
      uStack_108 = uVar5;
      uVar9 = __divdi3(lVar4,(lVar4 >> 0x20) + (uVar7 >> 0x20) * 1000,uVar6,uVar11);
      *(param_2 + 0x60) = uVar9;
      lVar4 = (uStack_108 & 0xffffffff) * 1000;
      uVar9 = __divdi3(lVar4,(lVar4 >> 0x20) + uStack_108._4_4_ * 1000,uVar6,uVar11);
      bVar21 = timebase_index_2_5ns_30_10s < 0x19;
      lVar4 = CONCAT44(timebase_val_ns_h,timebase_val_ns_l);
      uVar5 = timebase_val_ns_l * (uVar6 & 0xffffffff);
      *(param_2 + 0x62) = uVar9;
      iVar23 = uVar6 * lVar4 >> 0x20;
      if (bVar21) {
        lVar4 = (uVar5 & 0xffffffff) * 1000000;
        iVar23 = (lVar4 >> 0x20) + iVar23 * 1000000;
        uVar11 = __divdi3(lVar4,iVar23,uVar18 * iVar10);
        *(param_2 + 0x50) = uVar11;
        *(param_2 + 0x54) = iVar23;
      }
      else {
        lVar4 = (uVar5 & 0xffffffff) * 1000;
        iVar23 = (lVar4 >> 0x20) + iVar23 * 1000;
        uVar18 = __divdi3(lVar4,iVar23,uVar18 * iVar10);
        uVar11 = uVar18 * 1000;
        iVar23 = (uVar18 * 1000 >> 0x20) + iVar23 * 1000;
        *(param_2 + 0x50) = uVar11;
        *(param_2 + 0x54) = iVar23;
      }
      uVar13 = 0xde0b6b3;
      uVar11 = __divdi3(0,0xde0b6b3,uVar11,iVar23);
      *(param_2 + 0x58) = uVar11;
      *(param_2 + 0x5c) = uVar13;
      uVar9 = uVar19;
      if (uVar2 != 0) {
        DAT_2001dc66 = uVar9;
        return;
      }
      DAT_2001dc64 = uVar9;
      return;
    }
  }
  *(param_2 + 0x60) = 0;
  *(param_2 + 0x62) = 0;
  *(param_2 + 0x50) = 0;
  *(param_2 + 0x54) = 0;
  *(param_2 + 0x58) = 0;
  *(param_2 + 0x5c) = 0;
  if (uVar2 == 0) {
    DAT_2001dc64 = 0;
  }
  else {
    DAT_2001dc66 = 0;
  }
  return;
code_r0x0801a1fe:
  uVar11 = *pbVar20;
  pbVar20 = pbVar20 + 1;
  uVar22 = uVar11;
  uVar15 = (uVar15 & 0xffff) + 1;
  goto LAB_0801a16e;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void zw_scope_measurements(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint local_4cc [300];
  uint uStack_1c;
  
  uVar2 = _DAT_20019ca4;
  uVar1 = _DAT_20019ca0;
  DAT_2001dc64 = 0;
  DAT_2001dc66 = 0;
  if (global_settings != 2) {
    if (roll_split_index_ <= roll_draw_cursor_x_) {
      if (fast_render_flag_ == '\x01') {
        measurement_sample_count_ = 300;
        DAT_2001dccc = sample_rate_hz_l;
        DAT_2001dcd0 = sample_rate_hz_h;
        DAT_20002a68 = 25000;
        uStack_1c = 300;
        memcpy(local_4cc,&DAT_20019ca8,0x4ae);
        zw_scope_measurements_calc_vpp_avg_rms__08019288(&DAT_2001bb30,&DAT_2001dc68,uVar1,uVar2);
        uVar2 = _DAT_20019ca4;
        uVar1 = _DAT_20019ca0;
        uStack_1c = 300;
        memcpy(local_4cc,&DAT_20019ca8,0x4ae);
        FUN_0801a0e8(&DAT_2001bb30,&DAT_2001dc68,uVar1,uVar2);
        uVar2 = _DAT_20019ca4;
        uVar1 = _DAT_20019ca0;
        if ((ch1_enabled_measurements_bitfield & 0x1810) != 0) {
          uStack_1c = 300;
          memcpy(local_4cc,&DAT_20019ca8,0x4ae);
          zw_scope_measurements_calc_top_base_amp__08019848(&DAT_2001bb30,&DAT_2001dc68,uVar1,uVar2);
        }
        uVar2 = _DAT_2001a160;
        uVar1 = _DAT_2001a15c;
        if (ch2_enabled != '\x01') {
          return;
        }
        if (ch1_enabled_measurements_bitfield == 0) {
          return;
        }
        uStack_1c = 300;
        memcpy(local_4cc,&DAT_2001a164,0x4ae);
        zw_scope_measurements_calc_vpp_avg_rms__08019288(&DAT_2001af78,&DAT_2001dc00,uVar1,uVar2);
        uVar2 = _DAT_2001a160;
        uVar1 = _DAT_2001a15c;
        uStack_1c = 300;
        memcpy(local_4cc,&DAT_2001a164,0x4ae);
        FUN_0801a0e8(&DAT_2001af78,&DAT_2001dc00,uVar1,uVar2);
        if ((ch2_enabled_measurements_bitfield & 0x1810) == 0) {
          return;
        }
        uStack_1c = 300;
      }
      else {
        if ((roll_mode_enable == '\0') || (block_mode_enable_ != '\0')) {
          iVar5 = buffer_pointer_ - buffer_trigger_index_;
          if (iVar5 < 0) {
            iVar5 = iVar5 + hw_buffer_wrap_addr_;
          }
          else if (hw_buffer_wrap_addr_ <= iVar5) {
            iVar5 = iVar5 - hw_buffer_wrap_addr_;
          }
        }
        else {
          iVar5 = (-1 < buffer_pointer_ - buffer_trigger_index_) * (buffer_pointer_ - buffer_trigger_index_);
        }
        uVar4 = (roll_draw_cursor_x_ - roll_split_index_) + 1;
        uVar7 = uVar4 * _global_settings;
        uVar6 = (uVar7 != (uVar7 / 3000) * 3000) + uVar7 / 3000;
        uVar7 = uVar7 / uVar6;
        DAT_20002a68 = (uVar7 * 25000) / uVar4;
        measurement_sample_count_ = uVar7;
        if (uVar7 < 0x401) {
          DAT_2001dccc = sample_rate_hz_l;
          DAT_2001dcd0 = sample_rate_hz_h;
        }
        else {
          uVar4 = sample_rate_hz_h;
          uVar3 = __divdi3(sample_rate_hz_l,sample_rate_hz_h,uVar6,0);
          uVar4 = uVar4 << 10 | uVar3 >> 0x16;
          DAT_2001dccc = __divdi3(uVar3 << 10,uVar4,uVar7,0);
          DAT_2001dcd0 = uVar4;
        }
        local_4cc[0] = uVar6;
        FUN_080173f4(&DAT_2001bb30,iVar5,uVar7,0);
        if ((ch2_enabled == '\x01') && (ch1_enabled_measurements_bitfield != 0)) {
          local_4cc[0] = uVar6;
          FUN_080173f4(&DAT_2001af78,iVar5,measurement_sample_count_);
        }
        uVar2 = _DAT_20019ca4;
        uVar1 = _DAT_20019ca0;
        uStack_1c = measurement_sample_count_ & 0xffff;
        memcpy(local_4cc,&DAT_20019ca8,0x4ae);
        zw_scope_measurements_calc_vpp_avg_rms__08019288(&DAT_2001bb30,&DAT_2001dc68,uVar1,uVar2);
        uVar2 = _DAT_20019ca4;
        uVar1 = _DAT_20019ca0;
        uStack_1c = measurement_sample_count_ & 0xffff;
        memcpy(local_4cc,&DAT_20019ca8,0x4ae);
        FUN_0801a0e8(&DAT_2001bb30,&DAT_2001dc68,uVar1,uVar2);
        uVar2 = _DAT_20019ca4;
        uVar1 = _DAT_20019ca0;
        if ((ch1_enabled_measurements_bitfield & 0x1810) != 0) {
          uStack_1c = measurement_sample_count_ & 0xffff;
          memcpy(local_4cc,&DAT_20019ca8,0x4ae);
          zw_scope_measurements_calc_top_base_amp__08019848(&DAT_2001bb30,&DAT_2001dc68,uVar1,uVar2);
        }
        uVar2 = _DAT_2001a160;
        uVar1 = _DAT_2001a15c;
        if (ch2_enabled != '\x01') {
          return;
        }
        if (ch1_enabled_measurements_bitfield == 0) {
          return;
        }
        uStack_1c = measurement_sample_count_ & 0xffff;
        memcpy(local_4cc,&DAT_2001a164,0x4ae);
        zw_scope_measurements_calc_vpp_avg_rms__08019288(&DAT_2001af78,&DAT_2001dc00,uVar1,uVar2);
        uVar2 = _DAT_2001a160;
        uVar1 = _DAT_2001a15c;
        uStack_1c = measurement_sample_count_ & 0xffff;
        memcpy(local_4cc,&DAT_2001a164,0x4ae);
        FUN_0801a0e8(&DAT_2001af78,&DAT_2001dc00,uVar1,uVar2);
        if ((ch2_enabled_measurements_bitfield & 0x1810) == 0) {
          return;
        }
        uStack_1c = measurement_sample_count_ & 0xffff;
      }
      uVar2 = _DAT_2001a160;
      uVar1 = _DAT_2001a15c;
      memcpy(local_4cc,&DAT_2001a164,0x4ae);
      zw_scope_measurements_calc_top_base_amp__08019848(&DAT_2001af78,&DAT_2001dc00,uVar1,uVar2);
      return;
    }
  }
  DAT_2001dcca = 0;
  DAT_2001dcc8 = 0;
  DAT_2001dcc4 = 0;
  DAT_2001dcc0 = 0;
  DAT_2001dcbc = 0;
  DAT_2001dcb8 = 0;
  DAT_2001dcb4 = 0;
  DAT_2001dcb0 = 0;
  DAT_2001dcac = 0;
  DAT_2001dca8 = 0;
  DAT_2001dca4 = 0;
  DAT_2001dca0 = 0;
  DAT_2001dc9c = 0;
  DAT_2001dc98 = 0;
  DAT_2001dc94 = 0;
  DAT_2001dc90 = 0;
  DAT_2001dc8c = 0;
  DAT_2001dc88 = 0;
  DAT_2001dc84 = 0;
  DAT_2001dc80 = 0;
  DAT_2001dc7c = 0;
  DAT_2001dc78 = 0;
  DAT_2001dc74 = 0;
  DAT_2001dc70 = 0;
  DAT_2001dc6c = 0;
  DAT_2001dc68 = 0;
  DAT_2001dc66 = 0;
  DAT_2001dc64 = 0;
  DAT_2001dc62 = 0;
  DAT_2001dc60 = 0;
  DAT_2001dc5c = 0;
  DAT_2001dc58 = 0;
  DAT_2001dc54 = 0;
  DAT_2001dc50 = 0;
  DAT_2001dc4c = 0;
  DAT_2001dc48 = 0;
  DAT_2001dc44 = 0;
  DAT_2001dc40 = 0;
  DAT_2001dc3c = 0;
  DAT_2001dc38 = 0;
  DAT_2001dc34 = 0;
  DAT_2001dc30 = 0;
  DAT_2001dc2c = 0;
  DAT_2001dc28 = 0;
  DAT_2001dc24 = 0;
  DAT_2001dc20 = 0;
  DAT_2001dc1c = 0;
  DAT_2001dc18 = 0;
  DAT_2001dc14 = 0;
  DAT_2001dc10 = 0;
  DAT_2001dc0c = 0;
  DAT_2001dc08 = 0;
  DAT_2001dc04 = 0;
  DAT_2001dc00 = 0;
  return;
}




void zw_scope_measurement_labels
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,
               undefined4 param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16,undefined4 param_17,undefined4 param_18,undefined4 param_19,undefined4 param_20,undefined4 param_21,
               undefined4 param_22,undefined4 param_23,undefined4 param_24,undefined4 param_25,char param_26)

{
  undefined1 uVar1;
  ushort uVar2;
  uint uVar3;
  ushort uStack_60;
  ushort uStack_5e;
  byte *pbStack_58;
  undefined2 uStack_54;
  undefined2 uStack_52;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  uint uStack_3c;
  
  if (DAT_20030bb0 == '\0') {
    uVar2 = ch1_color_index;
    if (param_26 == '\0') {
      uVar3 = ch1_enabled_measurements_bitfield;
      uVar1 = ch1_probe_mode_0_x1_1_x10_2_x100;
      if (1 < ch1_color_index) {
        uVar2 = 0x3f;
      }
    }
    else {
      uVar3 = ch2_enabled_measurements_bitfield;
      uVar1 = ch2_probe_mode;
      if (1 < ch1_color_index) {
        uVar2 = 0x5f;
      }
    }
    pbStack_58 = image_measurement_label_background;
    uStack_54 = DAT_2001ddea;
    uStack_3c = uStack_3c & 0xffff0000;
    uStack_52 = 0x20;
    uStack_40 = CONCAT22(CONCAT11(uStack_40._3_1_,uVar1),3);
    if ((uVar3 & 1) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_4c = param_24;
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = CONCAT13(1,uStack_40);
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_23;
      zw_scope_int_values(param_23,param_24,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x11,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x12,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small("Frq",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,3,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 2) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x2e);
      uStack_40 = uStack_40 & 0xffffff;
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_1;
      uStack_4c = param_2;
      zw_scope_int_values(param_1,param_2,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x15,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x15,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x16,(&DAT_080556a0)[DAT_20002a64] + 0x1c,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small("PKPK",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,4,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x26,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 4) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_4c = param_14;
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = uStack_40 & 0xffffff;
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_13;
      zw_scope_int_values(param_13,param_14,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x1f,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x20,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small("Mea:",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,4,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 8) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_4c = param_16;
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = uStack_40 & 0xffffff;
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_15;
      zw_scope_int_values(param_15,param_16,uStack_48,uStack_44,uStack_40,uStack_3c);
      zw_draw_string_small("RMS",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,3,uVar2,0x20);
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a6e = DAT_20002a6e + 1;
        DAT_20002a64 = 0;
      }
    }
    if ((uVar3 & 0x10) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = uStack_40 & 0xffffff;
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_3;
      uStack_4c = param_4;
      zw_scope_int_values(param_3,param_4,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x24,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x16,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small("AMP",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,3,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 0x20) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x2e);
      uStack_40 = CONCAT13(3,uStack_40);
      uStack_44 = CONCAT22(0x20,uVar2);
      zw_scope_int_values(param_25,param_25 >> 0x1f,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x1a,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x1b,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x1c,(&DAT_080556a0)[DAT_20002a64] + 0x1c,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small("Duty",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,4,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x26,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 0x40) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_4c = param_18;
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = CONCAT13(2,uStack_40);
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_17;
      zw_scope_int_values(param_17,param_18,uStack_48,uStack_44,uStack_40,uStack_3c);
      zw_draw_string_small("T+ ",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,3,uVar2,0x20);
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 0x80) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_4c = param_20;
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = CONCAT13(2,uStack_40);
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_19;
      zw_scope_int_values(param_19,param_20,uStack_48,uStack_44,uStack_40,uStack_3c);
      zw_draw_string_small("T- ",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,3,uVar2,0x20);
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 0x100) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_4c = param_22;
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = CONCAT13(2,uStack_40);
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_21;
      zw_scope_int_values(param_21,param_22,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x13,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x14,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small(" T ",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,3,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 0x200) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_4c = param_10;
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = uStack_40 & 0xffffff;
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_9;
      zw_scope_int_values(param_9,param_10,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x17,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x18,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small("MAX",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,3,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 0x400) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_4c = param_12;
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = uStack_40 & 0xffffff;
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_11;
      zw_scope_int_values(param_11,param_12,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x17,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x19,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small("MIN",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,3,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 0x800) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_4c = param_6;
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = uStack_40 & 0xffffff;
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_5;
      zw_scope_int_values(param_5,param_6,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x2c,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x2e,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small("TOP",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,3,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 0x1000) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_4c = param_8;
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x24);
      uStack_40 = uStack_40 & 0xffffff;
      uStack_44 = CONCAT22(0x20,uVar2);
      uStack_50 = param_7;
      zw_scope_int_values(param_7,param_8,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x2d,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x2e,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small("Bas",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,3,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x1a,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
    if ((uVar3 & 0x2000) != 0) {
      uStack_60 = (&DAT_080556a0)[DAT_20002a64];
      uStack_5e = (&DAT_080556a4)[DAT_20002a6e];
      zw_draw_element(&uStack_60);
      uStack_48 = CONCAT22((&DAT_080556a4)[DAT_20002a6e] + 1,(&DAT_080556a0)[DAT_20002a64] + 0x2e);
      uStack_40 = CONCAT13(3,uStack_40);
      uStack_44 = CONCAT22(0x20,uVar2);
      zw_scope_int_values(param_25._2_2_,param_25._2_2_ >> 0x1f,uStack_48,uStack_44,uStack_40,uStack_3c);
      if (language_0_CN_1_EN == '\0') {
        zw_draw_CN(0x23,(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x1a,(&DAT_080556a0)[DAT_20002a64] + 0x10,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
        zw_draw_CN(0x1b,(&DAT_080556a0)[DAT_20002a64] + 0x1c,(&DAT_080556a4)[DAT_20002a6e] + 1,uVar2,0x20);
      }
      else {
        zw_draw_string_small("Dut-",(&DAT_080556a0)[DAT_20002a64] + 4,(&DAT_080556a4)[DAT_20002a6e] + 1,4,uVar2,0x20);
      }
      zw_draw_string_small(":",(&DAT_080556a0)[DAT_20002a64] + 0x26,(&DAT_080556a4)[DAT_20002a6e] + 1,1,uVar2,0x20);
      DAT_20002a64 = DAT_20002a64 + 1;
      if (DAT_20002a64 == 3) {
        DAT_20002a64 = 0;
        DAT_20002a6e = DAT_20002a6e + 1;
      }
    }
  }
  return;
}




void zw_draw_measurement_labels_setup_(void)

{
  undefined1 auStack_6c [84];
  uint uStack_18;
  
  DAT_20002a64 = '\0';
  DAT_20002a6e = '\0';
  uStack_18 = 0;
  memcpy(auStack_6c,&DAT_2001dc78,0x54);
  zw_scope_measurement_labels(DAT_2001dc68,DAT_2001dc6c,DAT_2001dc70,DAT_2001dc74);
  if (DAT_20002a64 != '\0') {
    DAT_20002a6e = DAT_20002a6e + '\x01';
    DAT_20002a64 = '\0';
  }
  uStack_18 = ch2_enabled;
  if (uStack_18 != 1) {
    return;
  }
  memcpy(auStack_6c,&DAT_2001dc10,0x54);
  zw_scope_measurement_labels(DAT_2001dc00,DAT_2001dc04,DAT_2001dc08,DAT_2001dc0c);
  return;
}




void FUN_0801b950(void)

{
  if ((DAT_2001de01 & 8) == 0) {
    return;
  }
  zw_draw_ParametrizedGlyph(&DAT_20002a70);
  return;
}




void FUN_0801b974(void)

{
  if (ch1_coupling_0_dc_1_ac == '\x01') {
    ch1_trigger_level_10uV_target_l = 0;
    ch1_trigger_level_10uV_target_h = 0;
  }
  else {
    ch1_trigger_level_10uV_target_l =
         (ch1_volt_scale_10uV * (((DAT_20019ca4 + DAT_20019ca5) / 2 + -0x7f) - (ch1_vert_offset_pixels - ch1_vert_scroll_offset))) / 0x19;
    ch1_trigger_level_10uV_target_h = ch1_trigger_level_10uV_target_l >> 0x1f;
  }
  if (global_settings == 0) {
    ch1_vert_scroll_offset = ch1_vert_scroll_offset - ch1_vert_offset_pixels;
    roll_mode_view_offset__l = horiz_trigger_delay_ps_l;
    roll_mode_view_offset__h = horiz_trigger_delay_ps_h;
  }
  else {
    roll_mode_view_offset__l = 0;
    roll_mode_view_offset__h = 0;
    ch1_vert_scroll_offset = 0;
  }
  ch1_vert_offset_pixels = 0;
  horiz_trigger_delay_ps_l = roll_mode_view_offset__l;
  horiz_trigger_delay_ps_h = roll_mode_view_offset__h;
  FUN_0801eff0(0xff);
  return;
}




void FUN_0801ba08(void)

{
  if (ch2_coupling_dc_ac == '\x01') {
    ch2_trigger_level_10uV_target_l = 0;
    ch2_trigger_level_10uV_target_h = 0;
  }
  else {
    ch2_trigger_level_10uV_target_l =
         (ch2_volt_scale_10uV * (((DAT_2001a160 + DAT_2001a161) / 2 + -0x80) - (ch2_vert_offset_pixels - ch2_vert_scroll_offset))) / 0x19;
    ch2_trigger_level_10uV_target_h = ch2_trigger_level_10uV_target_l >> 0x1f;
  }
  if (global_settings == 0) {
    ch2_vert_scroll_offset = ch2_vert_scroll_offset - (ch2_vert_offset_pixels + -5);
    roll_mode_view_offset__l = horiz_trigger_delay_ps_l;
    roll_mode_view_offset__h = horiz_trigger_delay_ps_h;
  }
  else {
    roll_mode_view_offset__l = 0;
    roll_mode_view_offset__h = 0;
    ch2_vert_scroll_offset = 0;
  }
  ch2_vert_offset_pixels = 5;
  horiz_trigger_delay_ps_l = roll_mode_view_offset__l;
  horiz_trigger_delay_ps_h = roll_mode_view_offset__h;
  FUN_0801eff0(0xff);
  return;
}




int FUN_0801baa8(int param_1)

{
  if (param_1 == 0x14) {
    FUN_0801b974();
    return 0x14;
  }
  if (param_1 != 0x54) {
    return param_1;
  }
  FUN_0801ba08();
  return 0x54;
}




void FUN_0801bacc(int param_1)

{
  if (ch1_coupling_0_dc_1_ac != '\x01') {
    ch1_trigger_level_10uV_target_l = (ch1_volt_scale_10uV * (((DAT_20019ca4 + DAT_20019ca5) / 2 + -0x7f) - param_1)) / 0x19;
    ch1_trigger_level_10uV_target_h = ch1_trigger_level_10uV_target_l >> 0x1f;
    return;
  }
  ch1_trigger_level_10uV_target_l = 0;
  ch1_trigger_level_10uV_target_h = 0;
  return;
}




void FUN_0801bb08(int param_1)

{
  if (ch2_coupling_dc_ac != '\x01') {
    ch2_trigger_level_10uV_target_l = (ch2_volt_scale_10uV * (((DAT_2001a160 + DAT_2001a161) / 2 + -0x80) - param_1)) / 0x19;
    ch2_trigger_level_10uV_target_h = ch2_trigger_level_10uV_target_l >> 0x1f;
    return;
  }
  ch2_trigger_level_10uV_target_l = 0;
  ch2_trigger_level_10uV_target_h = 0;
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void FUN_0801bb50(void)

{
  longlong lVar1;
  char cVar2;
  uint uVar3;
  int32_t iVar4;
  int iVar5;
  
  cVar2 = trigger_source_0_ch1_1_ch2;
  if ((RTAuto_enable_ == '\0') && (trigger_level_mode_0_auto_1_manual == '\x01')) {
    return;
  }
  if (global_settings != 1) {
    return;
  }
  if (counter_enable != '\0') {
    return;
  }
  if (DAT_20002a6f + 1 < 3) {
    DAT_20002a6f = DAT_20002a6f + 1;
    return;
  }
  DAT_20002a6f = counter_enable;
  if ((trigger_source_0_ch1_1_ch2 == '\0') || (ch2_enabled == '\0')) {
    if (ch1_coupling_0_dc_1_ac == '\x01') {
      ch1_trigger_level_10uV_target_l = 0;
      ch1_trigger_level_10uV_target_h = 0;
    }
    else {
      ch1_trigger_level_10uV_target_l =
           (ch1_volt_scale_10uV * (((DAT_20019ca4 + DAT_20019ca5) / 2 + -0x7f) - (ch1_vert_offset_pixels - ch1_vert_scroll_offset))) / 0x19;
      ch1_trigger_level_10uV_target_h = ch1_trigger_level_10uV_target_l >> 0x1f;
    }
    lVar1 = CONCAT44(ch1_trigger_level_10uV_target_h,ch1_trigger_level_10uV_target_l) + CONCAT44(ch1_vert_offset_10uV_h,ch1_vert_offset_10uV_l);
    uVar3 = (ch1_volt_scale_10uV * 0x7f) / 0x19;
    iVar5 = uVar3 >> 0x1f;
    if ((uVar3 < lVar1) || ((false && (uVar3 < lVar1)))) {
LAB_0801bca8:
      lVar1 = CONCAT44(iVar5,uVar3);
    }
    else {
      uVar3 = (ch1_volt_scale_10uV * -0x7f) / 0x19;
      iVar5 = uVar3 >> 0x1f;
      if ((lVar1 < uVar3) || ((false && (lVar1 < uVar3)))) goto LAB_0801bca8;
    }
    ch1_trigger_level_10uV_actual_h = lVar1 >> 0x20;
    ch1_trigger_level_10uV_actual_l = lVar1;
    iVar4 = __divdi3(lVar1 * 0x19,lVar1 * 0x19 >> 0x20,ch1_volt_scale_10uV,ch1_volt_scale_10uV >> 0x1f);
    ch1_trigger_level_pixels___100 = iVar4;
    if ((cVar2 == '\0') || (ch2_enabled == '\0')) goto LAB_0801bcc4;
  }
  else {
    if (ch2_coupling_dc_ac == '\x01') {
      ch2_trigger_level_10uV_target_l = 0;
      ch2_trigger_level_10uV_target_h = 0;
    }
    else {
      ch2_trigger_level_10uV_target_l =
           (ch2_volt_scale_10uV * (((DAT_2001a160 + DAT_2001a161) / 2 + -0x80) - (ch2_vert_offset_pixels - ch2_vert_scroll_offset))) / 0x19;
      ch2_trigger_level_10uV_target_h = ch2_trigger_level_10uV_target_l >> 0x1f;
    }
    lVar1 = CONCAT44(ch2_trigger_level_10uV_target_h,ch2_trigger_level_10uV_target_l) + CONCAT44(ch2_vert_offset_10uV_h,ch2_vert_offset_10uV_l);
    uVar3 = (ch2_volt_scale_10uV * 0x7f) / 0x19;
    iVar5 = uVar3 >> 0x1f;
    if ((uVar3 < lVar1) || ((false && (uVar3 < lVar1)))) {
LAB_0801bd02:
      lVar1 = CONCAT44(iVar5,uVar3);
    }
    else {
      uVar3 = (ch2_volt_scale_10uV * -0x7f) / 0x19;
      iVar5 = uVar3 >> 0x1f;
      if ((lVar1 < uVar3) || ((false && (lVar1 < uVar3)))) goto LAB_0801bd02;
    }
    ch2_trigger_level_10uV_h = lVar1 >> 0x20;
    ch2_trigger_level_10uV_l = lVar1;
    ch2_trigger_level_pixels = __divdi3(lVar1 * 0x19,lVar1 * 0x19 >> 0x20,ch2_volt_scale_10uV,ch2_volt_scale_10uV >> 0x1f);
  }
  iVar4 = ch2_trigger_level_pixels;
LAB_0801bcc4:
  trigger_level_raw_adc__0_255 = iVar4 + 0x80;
  if (0xe3 < trigger_level_raw_adc__0_255) {
    trigger_level_raw_adc__0_255 = 0xe3;
    return;
  }
  if (0x1c < trigger_level_raw_adc__0_255) {
    return;
  }
  trigger_level_raw_adc__0_255 = 0x1d;
  return;
}




void FUN_0801bd34(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  
  if (param_1 == 0x52) {
    if (DAT_2001de02 == '\0') {
      DAT_20002f36 = '\x01';
      goto LAB_0801bd46;
    }
    DAT_2001de02 = '\0';
  }
  if (DAT_20002f36 == '\0') {
    return;
  }
LAB_0801bd46:
  if (scan_mode__0_start_1_pretrigger_2_block_3_roll == '\0') {
    DAT_20002f36 = '\0';
    DAT_2001de02 = '\x01';
    puVar3 = &DAT_20019ca6;
    puVar7 = &DAT_20002a84;
    puVar6 = &DAT_20002bb0;
    puVar4 = &DAT_2001a162;
    puVar5 = &DAT_20002cdc;
    puVar1 = &DAT_20002e08;
    iVar2 = 300;
    do {
      *puVar7 = *puVar3;
      puVar7 = puVar7 + 1;
      *puVar6 = puVar3[300];
      puVar6 = puVar6 + 1;
      *puVar5 = *puVar4;
      puVar5 = puVar5 + 1;
      *puVar1 = puVar4[300];
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    DAT_20002f38 = roll_split_index_;
    DAT_20002f34 = roll_draw_cursor_x_;
  }
  return;
}




void FUN_0801bdec(void)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  cVar2 = ch2_enabled;
  if (DAT_2001de02 != '\0') {
    uVar5 = DAT_20002f34;
    for (uVar3 = DAT_20002f38; uVar3 <= uVar5; uVar3 = uVar3 + 1 & 0xffff) {
      if (cVar2 == '\x01') {
        bVar1 = (&DAT_20002cdc)[uVar3];
        for (uVar4 = (&DAT_20002e08)[uVar3]; uVar4 <= bVar1; uVar4 = uVar4 + 1 & 0xffff) {
          if ((uVar4 - 0x1c & 0xffff) < 200) {
            framebuffer_[(uVar4 - 10) * 0x140 + uVar3 + 10] = 4;
          }
        }
      }
      bVar1 = (&DAT_20002a84)[uVar3];
      for (uVar4 = (&DAT_20002bb0)[uVar3]; uVar4 <= bVar1; uVar4 = uVar4 + 1 & 0xffff) {
        if ((uVar4 - 0x1c & 0xffff) < 200) {
          framebuffer_[(uVar4 - 10) * 0x140 + uVar3 + 10] = 2;
        }
      }
    }
  }
  return;
}




void FUN_0801bec4(void)

{
  int iVar1;
  byte bStack_a;
  byte bStack_9;
  
  iVar1 = FUN_080270a8(&DAT_20002f4c);
  if (iVar1 != 0) {
    if ((trigger_source_0_ch1_1_ch2 == '\0') || (ch2_enabled == '\0')) {
      FUN_08016c18(0);
    }
    else {
      FUN_08016c18(1);
    }
    FUN_080172b0(&bStack_a,&bStack_9);
    if ((bStack_a - bStack_9 < 0x1a) ||
       ((trigger_level_mode_0_auto_1_manual != '\0' && ((trigger_level_raw_adc__0_255 <= bStack_9 || (bStack_a <= trigger_level_raw_adc__0_255)))))) {
      DAT_20002f49 = 0;
      return;
    }
    DAT_20002f49 = 1;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Restarted to delay deadcode elimination for space: register


void zw_scope_acquisition_state_(void)

{
  byte bVar1;
  longlong lVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  uint16_t local_18;
  
  if (system_status_ != '\x04') {
    FUN_0801bec4();
  }
  if (global_settings == 0) {
    if (scan_mode__0_start_1_pretrigger_2_block_3_roll != 2) {
      if (2 < scan_mode__0_start_1_pretrigger_2_block_3_roll) {
        if (scan_mode__0_start_1_pretrigger_2_block_3_roll == 3) {
LAB_0801c05a:
          FUN_08016ba0();
          scan_mode__0_start_1_pretrigger_2_block_3_roll = 0;
          return;
        }
LAB_0801bfe8:
        if (scan_mode__0_start_1_pretrigger_2_block_3_roll != 0xff) {
          return;
        }
        iVar3 = FUN_080270a8(&DAT_20002f64);
        if (iVar3 == 0) {
          return;
        }
        scan_mode__0_start_1_pretrigger_2_block_3_roll = 0;
        return;
      }
      if (scan_mode__0_start_1_pretrigger_2_block_3_roll == 0) {
        return;
      }
LAB_0801bf98:
      if (scan_mode__0_start_1_pretrigger_2_block_3_roll != 1) {
        return;
      }
      iVar3 = FUN_080270a8(&DAT_20002f58);
      if (iVar3 == 0) {
        return;
      }
      if ((roll_mode_flag_ == '\0') && (system_status_ != '\x05')) {
        if (DAT_20002f49 == '\0') {
          zw_timer_us(&DAT_20002f3c,200000);
        }
        else {
          zw_timer_us(&DAT_20002f3c,500000);
        }
      }
      else {
        zw_timer_us(&DAT_20002f3c,5000);
      }
      scan_mode__0_start_1_pretrigger_2_block_3_roll = 2;
      roll_mode_flag_ = '\0';
      FUN_08017264();
      return;
    }
LAB_0801c0fe:
    iVar3 = FUN_080173d4();
    if (iVar3 == 0) {
      if (trigger_mode_icon_0_auto_1_normal == '\0') {
        if (global_settings == 2) {
          return;
        }
        iVar3 = FUN_080270a8(&DAT_20002f3c);
        if (iVar3 != 0) {
          FUN_08017258();
          return;
        }
      }
      bVar1 = global_settings;
      if ((global_settings == 0) && (trigger_mode_0_auto_1_normal != '\0')) {
        FUN_08016ba0();
        scan_mode__0_start_1_pretrigger_2_block_3_roll = bVar1;
      }
    }
    else {
      buffer_pointer_ = FUN_08017270();
      DAT_2001dcdc = 0;
      scan_mode__0_start_1_pretrigger_2_block_3_roll = 0;
      trigger_armed_flag_ = '\0';
      DAT_2001de0f = 0;
      if (global_settings == 2) {
        _global_settings = _global_settings & 0xffffff00;
      }
      DAT_20002f48 = ~(DAT_20002f48 != 0);
      FUN_08016be4();
    }
  }
  else {
    if (acq_buffer_ready_flag_ == '\0') {
      if (scan_mode__0_start_1_pretrigger_2_block_3_roll == 2) goto LAB_0801c0fe;
      if (2 < scan_mode__0_start_1_pretrigger_2_block_3_roll) {
        if (scan_mode__0_start_1_pretrigger_2_block_3_roll != 3) goto LAB_0801bfe8;
LAB_0801bf74:
        iVar3 = FUN_080270a8(&DAT_20002f64);
        if (iVar3 == 0) {
          return;
        }
        zw_timer_us(&DAT_20002f64,60000);
        FUN_08017258();
        uVar4 = FUN_08017270();
        uVar5 = uVar4 / _global_settings;
        lVar2 = (buffer_depth_h >> 0x1f) + CONCAT44(buffer_depth_h,buffer_depth_l);
        buffer_pointer_ = _global_settings * uVar5 - ((lVar2 >> 0x20) << 0x1f | lVar2 >> 1);
        if (block_mode_enable_ != 0) {
          DAT_20002f70 = uVar4;
          return;
        }
        if ((-1 < buffer_depth_h) && (((buffer_depth_h != 0 || (uVar4 <= buffer_depth_l)) && (DAT_20002f70 <= uVar4)))) {
          if (roll_direction_0_left_1_right == '\0') {
            if (uVar4 < 0x15) {
              roll_split_index_ = 299;
              fVar6 = 0.0;
            }
            else {
              uVar5 = 299.0 - (uVar4 - 0x14) / _global_settings;
              local_18 = uVar5;
              roll_split_index_ = local_18;
              fVar6 = 299 - (uVar5 & 0xffff);
            }
            roll_draw_cursor_x_ = 299;
          }
          else {
            uVar5 = uVar5 & 0x7fff;
            roll_split_index_ = 0;
            if (1 < uVar5) {
              uVar5 = uVar5 - 1 & 0x7fff;
            }
            roll_draw_cursor_x_ = uVar5;
            fVar6 = uVar5;
          }
          fVar6 = fVar6 * _global_settings;
          __floatdisf(buffer_depth_h << 0x1f | buffer_depth_l >> 1,buffer_depth_h >> 1);
          DAT_20002f70 = uVar4;
          _global_settings = fVar6 - _global_settings;
          return;
        }
        block_mode_enable_ = ~(roll_direction_0_left_1_right != '\0');
        if (roll_direction_0_left_1_right == '\0') {
          DAT_20002f70 = uVar4;
          roll_split_index_ = 0;
          return;
        }
        roll_draw_cursor_x_ = 0x12a;
        FUN_08016ba0(0,0);
        scan_mode__0_start_1_pretrigger_2_block_3_roll = 0xff;
        zw_timer_us(&DAT_20002f64,500000);
        DAT_20002f70 = uVar4;
        return;
      }
      if (scan_mode__0_start_1_pretrigger_2_block_3_roll != 0) goto LAB_0801bf98;
    }
    else {
      FUN_08016ba0();
      acq_buffer_ready_flag_ = '\0';
      scan_mode__0_start_1_pretrigger_2_block_3_roll = 0;
      trigger_armed_flag_ = '\x01';
      if (system_status_ != '\x04') {
        if ((trigger_source_0_ch1_1_ch2 == '\0') || (ch2_enabled == '\0')) {
          FUN_08016c18(0);
        }
        else {
          FUN_08016c18(1);
        }
        zw_timer_us(&DAT_20002f4c,500000);
        if (scan_mode__0_start_1_pretrigger_2_block_3_roll == 2) goto LAB_0801c0fe;
        if (2 < scan_mode__0_start_1_pretrigger_2_block_3_roll) {
          if (scan_mode__0_start_1_pretrigger_2_block_3_roll != 3) goto LAB_0801bfe8;
          if (global_settings == 0) goto LAB_0801c05a;
          goto LAB_0801bf74;
        }
        if (scan_mode__0_start_1_pretrigger_2_block_3_roll != 0) goto LAB_0801bf98;
      }
      if (global_settings == 0) {
        return;
      }
    }
    if (roll_mode_enable == '\x01') {
      roll_split_index_ = 299;
      if (roll_direction_0_left_1_right != '\0') {
        roll_split_index_ = 0;
      }
      DAT_20002f70 = 0;
      block_mode_enable_ = 0;
      zw_timer_us(&DAT_20002f64,120000);
      scan_mode__0_start_1_pretrigger_2_block_3_roll = 3;
      FUN_0801723c();
      DAT_2001ddbb = 0;
    }
    else if (trigger_armed_flag_ != '\0') {
      FUN_0801723c();
      if ((timebase_val_ns_h < 1) && ((timebase_val_ns_h != 0 || (timebase_val_ns_l < 100000)))) {
        lVar2 = (CONCAT44(pre_trigger_samples_ >> 0x1b,pre_trigger_samples_ << 5) - pre_trigger_samples_) * 0x1f8 + pre_trigger_samples_;
      }
      else {
        lVar2 = ((CONCAT44(pre_trigger_samples_ >> 0x1b,pre_trigger_samples_ << 5) - pre_trigger_samples_) * 4 + pre_trigger_samples_) * 0x4b;
      }
      uVar5 = __divdi3(lVar2 << 7,(lVar2 << 7) >> 0x20,sample_rate_hz_l,sample_rate_hz_h);
      zw_timer_us(&DAT_20002f58,(uVar5 < 2000) * 2000 + (uVar5 >= 2000) * uVar5);
      scan_mode__0_start_1_pretrigger_2_block_3_roll = 1;
      DAT_2001ddbb = 0;
    }
  }
  return;
}




void zw_save_settings_(uint32_t param_1)

{
  void *buf;
  
  if (((DAT_2001de04 == '\0') && (system_status_ != '\x03')) && (DAT_2001de15 == '\0')) {
    FUN_0802b8e4();
    buf = memcpy(&DAT_20002f74,&global_settings,0x154);
    *(buf + 0x3fe) = 0x47;
    *(buf + 0x3ff) = 0x4f;
    HAL_FLASH_Write_Offset_0x96000(param_1,buf,0x400);
    return;
  }
  return;
}




undefined4 FUN_0801c3f0(uint32_t param_1)

{
  undefined1 *puVar1;
  
  HAL_FLASH_Read_Offset_0x96000(param_1,&DAT_20002f74,0x400);
  if ((DAT_20003372 == 'G') && (DAT_20003373 == 'O')) {
    puVar1 = memcpy(&global_settings,&DAT_20002f74,0x154);
    puVar1[1] = 1;
    *puVar1 = 1;
    puVar1[0xdc] = 0;
    *(puVar1 + 0x1c) = 0;
    *(puVar1 + 0x20) = 0;
    *(puVar1 + 0x24) = 0;
    *(puVar1 + 0x28) = 0;
    if (0x5e < puVar1[0xfa] - 5) {
      puVar1[0xfa] = 0x32;
    }
    puVar1[0x124] = 0;
    puVar1[0x121] = 0;
    puVar1[0x122] = 0;
    puVar1[0x123] = 0;
    puVar1[0xe6] = 0;
    puVar1[0xe9] = 0;
    puVar1[0xfd] = 0;
    puVar1[0xfe] = 0;
    puVar1[0x120] = 0;
    puVar1[0x12a] = 0;
    puVar1[299] = 0;
    puVar1[0xfc] = 0;
    puVar1[0x11e] = 0;
    puVar1[0x11f] = 0;
    puVar1[0x125] = 0;
    puVar1[0x129] = 0;
    puVar1[0x12d] = 0;
    puVar1[0x132] = 0;
    puVar1[0x10f] = 0;
    puVar1[0x135] = 0;
    puVar1[0x140] = 0;
    puVar1[0x141] = 0;
    puVar1[0x144] = 0;
    puVar1[0x145] = 0;
    puVar1[0x148] = 0;
    puVar1[0x11d] = 0xff;
    if (600 < *(puVar1 + 0x70) - 700U) {
      *(puVar1 + 0x70) = 1000;
    }
    if (600 < *(puVar1 + 0xb0) - 700U) {
      *(puVar1 + 0xb0) = 1000;
    }
    FUN_0801eff0(0xff);
    return 1;
  }
  return 0;
}




void FUN_0801c508(uint32_t param_1)

{
  DAT_20003372 = 0;
  DAT_20003373 = 0;
  HAL_FLASH_Write_Offset_0x96000(param_1,&DAT_20002f74,0x400);
  return;
}




void zw_screenshot_view(int imgSel)

{
  undefined4 uVar1;
  short sVar2;
  ushort imgIdx;
  
  imgIdx = (&img_list_)[imgSel];
  printf_disabled_2("view imgSel = %d\r\n",imgSel);
  printf_disabled_2("view imgIdx = %d\r\n",imgIdx);
  HAL_FLASH_Read_Offset_0x96000((imgIdx + 0x54) * 2048,img_data_buffer_,2048);
  memcpy(&DAT_20019ca6,img_data_buffer_,300);
  memcpy(&DAT_20019dd2,img_data_buffer_ + 300,300);
  memcpy(&DAT_2001a162,img_data_buffer_ + 600,300);
  memcpy(&DAT_2001a28e,img_data_buffer_ + 900,300);
  memcpy(&global_settings,img_data_buffer_ + 1200,340);
  memcpy(&DAT_2001dc68,img_data_buffer_ + 1540,100);
  memcpy(&DAT_2001dc00,img_data_buffer_ + 1640,100);
  uVar1 = DAT_2001a158;
  DAT_2001a158._0_1_ = img_data_buffer_[0x6cc];
  DAT_2001a158._1_1_ = img_data_buffer_[0x6cd];
  DAT_2001a158._2_1_ = img_data_buffer_[0x6ce];
  DAT_2001a158._3_1_ = img_data_buffer_[0x6cf];
  zw_screenshot_copy_buffer_();
  system_status_ = 3;
  DAT_2001de05 = settings_buffer_[0x125];
  DAT_2001de01 = DAT_2001de01 & 0xfe;
  DAT_2001de02 = 0;
  fft_mode_0_off_1_log_2_lin_3_music = 0;
  persistance_mode_0_off_1_infinite_2_1s = 0;
  DAT_2001de0a = 0;
  DAT_2001de0e = 0;
  DAT_2001de0c = 0;
  zw_draw_init_(0);
  sVar2 = zw_draw_string_large_integer(imgSel + 1,10,18,1,2,3);
  zw_draw_string_large("/",sVar2 + 10,18,1,1,2);
  zw_draw_string_large_integer(img_count_,sVar2 + 20,18,1,2,3);
  zw_draw_flush_offscreen();
  memcpy(&global_settings,settings_buffer_,340);
  system_status_ = 3;
  DAT_2001de01 = 0;
  DAT_2001ddc9 = 0;
  DAT_2001de0e = 0;
  DAT_2001de0c = 0;
  DAT_2001de0d = 0;
  DAT_2001a158 = uVar1;
  return;
}




void zw_screenshot_init(void)

{
  astruct *waveform_index_;
  undefined2 *puVar1;
  int iVar2;
  undefined1 buf [160];
  
  zw_timer_us(&DAT_2000342c,90000);
  HAL_FLASH_Read_Offset_0x96000(0x29000,buf,140);
  waveform_index_ = memcpy(&img_list_,buf,136);
  if ((63 < waveform_index_->current_count_) || (waveform_index_->max_files_ != 63)) {
    iVar2 = 63;
    waveform_index_->max_files_ = 63;
    waveform_index_->current_count_ = 0;
    puVar1 = &img_list_;
    do {
      *puVar1 = 0;
      puVar1 = puVar1 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    memcpy(buf,&img_list_,136);
    HAL_FLASH_Write_Offset_0x96000(0x29000,buf,136);
    printf_disabled_1("queue init done = %d\r\n",1);
  }
  DAT_20003394 = 299;
  DAT_20003396 = 135;
  DAT_2000339c = image_screenshots_zoom;
  DAT_200033a0 = 0;
  DAT_200033a2 = 32;
  DAT_20003392 = 32;
  DAT_20003384 = 300;
  DAT_20003386 = 183;
  DAT_20003390 = 0;
  DAT_2000338c = image_screenshots_trash;
  DAT_20003382 = 32;
  DAT_20003374 = 295;
  DAT_20003376 = 219;
  DAT_20003380 = 0;
  DAT_2000337c = image_screenshots_exit;
  return;
}




void zw_screenshot_save(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  if ((param_1 == 0xe) && (system_status_ == '\x01')) {
    if (DAT_2001ddc9 == '\0') {
      if (DAT_2001de15 == '\0') {
        memcpy(&DAT_20003d94,&DAT_20019ca6,300);
        memcpy(&DAT_20003ec0,&DAT_20019dd2,300);
        memcpy(&DAT_20003fec,&DAT_2001a162,300);
        memcpy(&DAT_20004118,&DAT_2001a28e,300);
        memcpy(&DAT_20004244,&global_settings,0x154);
        memcpy(&DAT_20004398,&DAT_2001dc68,100);
        memcpy(&DAT_200043fc,&DAT_2001dc00,100);
        DAT_20004460 = DAT_2001a158;
        DAT_20004461 = DAT_2001a158 >> 8;
        DAT_20004462 = DAT_2001a158 >> 16;
        DAT_20004463 = DAT_2001a158 >> 24;
        if (DAT_20003424 == 0) {
          uVar1 = 0x3f;
        }
        else {
          uVar2 = 0x3f;
          uVar4 = 0;
          do {
            if (img_count_ == 0) {
LAB_0801c874:
              uVar1 = uVar4;
              if (uVar2 != uVar4) break;
            }
            else {
              uVar2 = uVar4;
              if (uVar4 != img_list_) {
                iVar3 = 0;
                uVar2 = img_list_;
                do {
                  iVar3 = iVar3 + 1;
                  if (iVar3 == img_count_) goto LAB_0801c874;
                  uVar2 = (&img_list_)[iVar3];
                } while (uVar2 != uVar4);
              }
            }
            uVar4 = uVar4 + 1;
            uVar1 = uVar2;
          } while (uVar4 != DAT_20003424);
          if (uVar1 < 0x3f) {
            HAL_FLASH_Write_Offset_0x96000((uVar1 + 0x54) * 0x800,&DAT_20003d94,0x800);
          }
          uVar1 = uVar1 & 0xff;
        }
        FUN_080270c4(&img_list_,uVar1);
        memcpy(&DAT_20003d94,&img_list_,0x88);
        HAL_FLASH_Write_Offset_0x96000(0x29000,&DAT_20003d94,0x88);
        zw_draw_popup_message("SAVE DONE",9,1000,0,3);
      }
      else {
        zw_draw_popup_message("Limit",5,0x5dc,1,2);
      }
    }
    else {
      zw_draw_popup_message("Can\'t save XY",0xd,0x5dc,1,2);
    }
  }
  return;
}




void FUN_0801c92c(uint param_1,int param_2,byte *param_3,byte *param_4,undefined2 param_5)

{
  byte bVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte bVar7;
  int iVar8;
  byte *pbVar9;
  byte local_c0 [76];
  byte local_74 [76];
  
  pbVar9 = local_c0;
  pbVar6 = local_c0;
  bVar1 = *param_4;
  local_c0[0] = *param_3;
  local_74[0] = bVar1;
  pbVar5 = local_74 + 1;
  iVar8 = 0x4a;
  bVar7 = *param_3;
  do {
    pbVar9 = pbVar9 + 1;
    param_4 = param_4 + 4;
    param_3 = param_3 + 4;
    bVar3 = *param_3;
    if (bVar3 < bVar1) {
      *pbVar9 = bVar1;
      bVar3 = bVar1;
    }
    else {
      *pbVar9 = bVar3;
    }
    bVar1 = *param_4;
    if (bVar7 < bVar1) {
      *pbVar5 = bVar7;
      bVar1 = bVar7;
    }
    else {
      *pbVar5 = bVar1;
    }
    pbVar5 = pbVar5 + 1;
    iVar8 = iVar8 + -1;
    bVar7 = bVar3;
  } while (iVar8 != 0);
  pbVar9 = local_74;
  do {
    while ((uVar2 = *pbVar9, uVar2 < 0xe5 && (0x1b < *pbVar6))) {
      uVar4 = *pbVar6 - uVar2 & 0xffff;
      pbVar9 = pbVar9 + 1;
      zw_draw_line_vertical(param_1,uVar2 / 5 + param_2 & 0xffff,(uVar4 < 5) + uVar4 / 5,param_5);
      pbVar6 = pbVar6 + 1;
      param_1 = param_1 + 1 & 0xffff;
      if (pbVar9 == pbVar5) {
        return;
      }
    }
    pbVar9 = pbVar9 + 1;
    pbVar6 = pbVar6 + 1;
    param_1 = param_1 + 1 & 0xffff;
  } while (pbVar9 != pbVar5);
  return;
}




void FUN_0801c9f0(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined1 auStack_4c0 [300];
  undefined1 auStack_394 [300];
  undefined1 auStack_268 [300];
  undefined1 auStack_13c [300];
  
  HAL_FLASH_Read_Offset_0x96000(((&img_list_)[param_3] + 0x54) * 0x800,img_data_buffer_,0x800);
  memcpy(auStack_4c0,img_data_buffer_,300);
  memcpy(auStack_394,img_data_buffer_ + 300,300);
  memcpy(auStack_268,img_data_buffer_ + 600,300);
  memcpy(auStack_13c,img_data_buffer_ + 900,300);
  if (img_data_buffer_[0x4b2] != 0) {
    if (img_data_buffer_[0x5ce] != 0) {
      FUN_0801c92c(param_1,param_2,auStack_4c0,auStack_394,0x3f);
      FUN_0801c92c(param_1,param_2,auStack_268,auStack_13c,0x5f);
      return;
    }
    FUN_0801c92c(param_1,param_2,auStack_268,auStack_13c,0x5f);
  }
  FUN_0801c92c(param_1,param_2,auStack_4c0,auStack_394,0x3f);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void zw_screenshot_browser(int param_1)

{
  short sVar1;
  uint uVar2;
  short sVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 auStack_82c [2048];
  
  if (param_1 == 0) {
    return;
  }
  zw_screenshot_save();
  if (system_status_ != 3) {
    if (param_1 != 0x4e) {
      return;
    }
    memcpy(settings_buffer_,&global_settings,340);
    system_status_ = 3;
    DAT_2001de01 = 0;
    DAT_2001ddc9 = 0;
    DAT_2001de0e = 0;
    DAT_2001de0c = 0;
    DAT_2001de0d = 0;
    DAT_2001dcdc = 0;
    DAT_20003438 = 1;
    _img_viewer_index_ = 0;
    printf_disabled_1("imgVal=%d\r\n",0x4e);
    if (DAT_20003438 != 0) goto LAB_0801cbb6;
LAB_0801cb18:
    uVar2 = img_count_ - 1;
LAB_0801cb22:
    if (param_1 == 0x4) {
      _img_viewer_index_ = _img_viewer_index_ + 1;
LAB_0801cb2a:
      if (_img_viewer_index_ <= uVar2) {
        if (_img_viewer_index_ < 0) {
          _img_viewer_index_ = 0;
        }
        goto LAB_0801cb32;
      }
    }
    else {
      if ((param_1 != 0x3) || (_img_viewer_index_ < 1)) goto LAB_0801cb2a;
      _img_viewer_index_ = _img_viewer_index_ - 1;
      if (_img_viewer_index_ <= uVar2) goto LAB_0801cb32;
    }
    _img_viewer_index_ = uVar2;
LAB_0801cb32:
    if (img_count_ <= _img_viewer_index_) {
      return;
    }
    zw_screenshot_view();
    return;
  }
  if ((param_1 == 0xe) || (param_1 == 0x18)) {
    memcpy(&global_settings,settings_buffer_,340);
    system_status_ = 1;
    global_settings = 1;
    horiz_trigger_delay_ps_l = 0;
    horiz_trigger_delay_ps_h = 0;
    roll_mode_view_offset__l = 0;
    roll_mode_view_offset__h = 0;
    DAT_2001de01 = 0;
    DAT_2001de02 = 0;
    scan_mode__0_start_1_pretrigger_2_block_3_roll = 0;
    FUN_0801eff0(0xff);
    return;
  }
  printf_disabled_1("imgVal=%d\r\n",param_1);
  if (DAT_20003438 == 0) {
    if ((param_1 == 0x8) || (param_1 == 0x2)) {
      DAT_20003438 = 1;
      goto LAB_0801cbb6;
    }
    if (param_1 != 0x10) goto LAB_0801cb18;
LAB_0801cd64:
    zw_screenshot_delete_(&img_list_,img_viewer_index_);
    if (img_count_ == 0) {
      DAT_20003438 = 1;
      _img_viewer_index_ = 0;
    }
    else if (img_count_ - 1 < _img_viewer_index_) {
      _img_viewer_index_ = img_count_ - 1;
    }
    memcpy(auStack_82c,&img_list_,0x88);
    HAL_FLASH_Write_Offset_0x96000(0x29000,auStack_82c,0x88);
    if (DAT_20003438 == 0) {
      uVar2 = img_count_ - 1;
      goto LAB_0801cb2a;
    }
LAB_0801cbc6:
    uVar2 = _img_viewer_index_;
    if (img_count_ != 0) goto LAB_0801cd16;
  }
  else {
    if ((param_1 == 0x8) || (param_1 == 0x2)) {
      uVar2 = img_count_ - 1;
      if (_img_viewer_index_ <= uVar2) {
        DAT_20003438 = 0;
        goto LAB_0801cb22;
      }
    }
    else if (param_1 == 0x10) goto LAB_0801cd64;
LAB_0801cbb6:
    if (param_1 == 0x4) {
      _img_viewer_index_ = _img_viewer_index_ + 1;
      goto LAB_0801cbc6;
    }
    if (param_1 == 0x3) {
      _img_viewer_index_ = _img_viewer_index_ - 1;
      goto LAB_0801cbc6;
    }
    if (param_1 == 0xb) {
      if (2 < _img_viewer_index_) {
        _img_viewer_index_ = _img_viewer_index_ - 3;
      }
      goto LAB_0801cbc6;
    }
    if ((param_1 != 0x13) || (uVar2 = _img_viewer_index_ + 3, img_count_ <= _img_viewer_index_ + 3)) goto LAB_0801cbc6;
LAB_0801cd16:
    _img_viewer_index_ = uVar2;
    if (-1 < _img_viewer_index_) {
      if (img_count_ - 1 < _img_viewer_index_) {
        _img_viewer_index_ = (img_count_ / 9) * 9;
        uVar2 = (_img_viewer_index_ / 9) * 9;
      }
      else {
        uVar2 = (_img_viewer_index_ / 9) * 9;
      }
      goto LAB_0801cbce;
    }
  }
  uVar2 = 0;
  _img_viewer_index_ = 0;
LAB_0801cbce:
  zw_draw_rectangle_filled(0,0,320,240,1);
  zw_draw_string_large("Image view",18,0,10,0,32);
  zw_draw_rectangle_filled(0,18,320,2,4);
  zw_draw_element(&DAT_20003394);
  zw_draw_element(&DAT_20003384);
  zw_draw_element(&DAT_20003374);
  sVar1 = zw_draw_string_large_integer(_img_viewer_index_ / 9 + 1,145,220,0,1,2);
  zw_draw_string_large("/",sVar1 + 145,220,1,0,1);
  uVar5 = 2;
  zw_draw_string_large_integer((img_count_ + 8) / 9,sVar1 + 155,220,0,1,2);
  sVar1 = 0x1f;
  uVar6 = 2;
  do {
    sVar3 = 0x1b;
    uVar4 = uVar2;
    do {
      zw_draw_rectangle_filled(sVar3,sVar1 + 1,77,53,0,uVar5,uVar6);
      if (uVar4 < img_count_) {
        FUN_0801c9f0(sVar3 + 1,sVar1 + 2,uVar4);
      }
      if (_img_viewer_index_ == uVar4) {
        zw_draw_rectangle(sVar3 + -1,sVar1,79,55,uVar6);
        zw_draw_rectangle(sVar3 + -2,sVar1 - 1U & 0x7fff,81,57,uVar6);
      }
      sVar3 = sVar3 + 94;
      uVar4 = uVar4 + 1;
    } while (sVar3 != 309);
    sVar1 = sVar1 + 65;
    uVar2 = uVar2 + 3;
  } while (sVar1 != 226);
  zw_draw_flush_offscreen();
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void FUN_0801ce24(int param_1)

{
  longlong lVar1;
  ulonglong uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  
  uVar6 = ch1_trigger_level_10uV_target_h;
  uVar5 = ch1_trigger_level_10uV_target_l;
  uVar4 = ch1_vert_offset_10uV_h;
  uVar3 = ch1_vert_offset_10uV_l;
  iVar9 = ch1_volt_scale_10uV;
  if (param_1 == 0x25) {
    uVar2 = CONCAT44(ch1_trigger_level_10uV_target_h,ch1_trigger_level_10uV_target_l) + CONCAT44(ch1_vert_offset_10uV_h,ch1_vert_offset_10uV_l);
    lVar1 = (uVar2 & 0xffffffff) * 0x19;
    iVar8 = (lVar1 >> 0x20) + (uVar2 >> 0x20) * 0x19;
    uVar7 = __divdi3(lVar1,iVar8,ch1_volt_scale_10uV,ch1_volt_scale_10uV >> 0x1f);
    if ((iVar8 < 1) && ((iVar8 != 0 || (uVar7 < 100)))) {
      if ((iVar8 < -1) || ((iVar8 == -1 && (uVar7 < 0xffffff9c)))) {
        lVar1 = iVar9 * -4 - CONCAT44(uVar4,uVar3);
      }
      else {
        if (shift_key_ == '\x01') {
          iVar9 = iVar9 / 0x19;
        }
        else {
          iVar9 = iVar9 / 10;
        }
        lVar1 = iVar9 + CONCAT44(uVar6,uVar5);
      }
      goto LAB_0801cf04;
    }
  }
  else {
    if (param_1 != 0x26) {
      return;
    }
    uVar2 = CONCAT44(ch1_trigger_level_10uV_target_h,ch1_trigger_level_10uV_target_l) + CONCAT44(ch1_vert_offset_10uV_h,ch1_vert_offset_10uV_l);
    lVar1 = (uVar2 & 0xffffffff) * 0x19;
    iVar8 = (lVar1 >> 0x20) + (uVar2 >> 0x20) * 0x19;
    uVar7 = __divdi3(lVar1,iVar8,ch1_volt_scale_10uV,ch1_volt_scale_10uV >> 0x1f);
    if ((-2 < iVar8) && ((iVar8 != -1 || (0xffffff9c < uVar7)))) {
      if ((iVar8 < 1) && ((iVar8 != 0 || (uVar7 < 0x65)))) {
        if (shift_key_ == '\x01') {
          iVar9 = iVar9 / 0x19;
        }
        else {
          iVar9 = iVar9 / 10;
        }
        lVar1 = CONCAT44(uVar6,uVar5) - iVar9;
      }
      else {
        lVar1 = (iVar9 << 2) - CONCAT44(uVar4,uVar3);
      }
      goto LAB_0801cf04;
    }
  }
  zw_draw_popup_message("Limit",5,1000,0);
  lVar1 = CONCAT44(ch1_trigger_level_10uV_target_h,ch1_trigger_level_10uV_target_l);
LAB_0801cf04:
  ch1_trigger_level_10uV_target_h = lVar1 >> 0x20;
  ch1_trigger_level_10uV_target_l = lVar1;
  DAT_2001dcd8 = DAT_2001dcd8 | 2;
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void FUN_0801cf70(int param_1)

{
  longlong lVar1;
  ulonglong uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  
  uVar6 = ch2_trigger_level_10uV_target_h;
  uVar5 = ch2_trigger_level_10uV_target_l;
  uVar4 = ch2_vert_offset_10uV_h;
  uVar3 = ch2_vert_offset_10uV_l;
  iVar9 = ch2_volt_scale_10uV;
  if (param_1 == 0x27) {
    uVar2 = CONCAT44(ch2_trigger_level_10uV_target_h,ch2_trigger_level_10uV_target_l) + CONCAT44(ch2_vert_offset_10uV_h,ch2_vert_offset_10uV_l);
    lVar1 = (uVar2 & 0xffffffff) * 0x19;
    iVar8 = (lVar1 >> 0x20) + (uVar2 >> 0x20) * 0x19;
    uVar7 = __divdi3(lVar1,iVar8,ch2_volt_scale_10uV,ch2_volt_scale_10uV >> 0x1f);
    if ((iVar8 < 1) && ((iVar8 != 0 || (uVar7 < 100)))) {
      if ((iVar8 < -1) || ((iVar8 == -1 && (uVar7 < 0xffffff9c)))) {
        lVar1 = iVar9 * -4 - CONCAT44(uVar4,uVar3);
      }
      else {
        if (shift_key_ == '\x01') {
          iVar9 = iVar9 / 0x19;
        }
        else {
          iVar9 = iVar9 / 10;
        }
        lVar1 = iVar9 + CONCAT44(uVar6,uVar5);
      }
      goto LAB_0801d064;
    }
  }
  else {
    if (param_1 != 0x28) {
      return;
    }
    uVar2 = CONCAT44(ch2_trigger_level_10uV_target_h,ch2_trigger_level_10uV_target_l) + CONCAT44(ch2_vert_offset_10uV_h,ch2_vert_offset_10uV_l);
    lVar1 = (uVar2 & 0xffffffff) * 0x19;
    iVar8 = (lVar1 >> 0x20) + (uVar2 >> 0x20) * 0x19;
    uVar7 = __divdi3(lVar1,iVar8,ch2_volt_scale_10uV,ch2_volt_scale_10uV >> 0x1f);
    if ((-2 < iVar8) && ((iVar8 != -1 || (0xffffff9c < uVar7)))) {
      if ((iVar8 < 1) && ((iVar8 != 0 || (uVar7 < 0x65)))) {
        if (shift_key_ == '\x01') {
          iVar9 = iVar9 / 0x19;
        }
        else {
          iVar9 = iVar9 / 10;
        }
        lVar1 = CONCAT44(uVar6,uVar5) - iVar9;
      }
      else {
        lVar1 = (iVar9 << 2) - CONCAT44(uVar4,uVar3);
      }
      goto LAB_0801d064;
    }
  }
  zw_draw_popup_message("Limit",5,1000,0);
  lVar1 = CONCAT44(ch2_trigger_level_10uV_target_h,ch2_trigger_level_10uV_target_l);
LAB_0801d064:
  ch2_trigger_level_10uV_target_h = lVar1 >> 0x20;
  ch2_trigger_level_10uV_target_l = lVar1;
  DAT_2001dcd8 = DAT_2001dcd8 | 2;
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void zw_scope_ch1_vertical_movement_(int param_1)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  
  if (global_settings == 0) goto LAB_0801d116;
  if (param_1 == 0x15) {
    if (ch1_v_div_index < 0xd) {
      ch1_v_div_index = ch1_v_div_index + 1;
LAB_0801d220:
      FUN_0802bc38(*(&DAT_08055a1c + ch1_v_div_index * 4),*(&DAT_08055a1c + ch1_v_div_index * 4) >> 0x1f,0x6e0087,0x3f);
      goto LAB_0801d116;
    }
    ch1_v_div_index = 0xd;
  }
  else {
    if (param_1 != 0x16) goto LAB_0801d116;
    if (4 < ch1_v_div_index) {
      ch1_v_div_index = ch1_v_div_index - 1;
      goto LAB_0801d220;
    }
    ch1_v_div_index = 4;
  }
  zw_draw_popup_message("Limit",5,1000,0);
LAB_0801d116:
  if (cursors_y_enable != '\0') {
    return;
  }
  if ((DAT_2001ddc9 == '\0') && (active_channel_0_ch1_1_ch2_2_math != '\0')) {
    return;
  }
  if (param_1 == 0x21) {
    if (ch1_volt_scale_10uV < 100000) {
      uVar2 = 800000 / (100000 / ch1_volt_scale_10uV);
    }
    else {
      uVar2 = (ch1_volt_scale_10uV / 100000) * 800000;
    }
    iVar3 = uVar2 >> 0x1f;
    if ((ch1_vert_offset_10uV_h < iVar3) || ((ch1_vert_offset_10uV_h == iVar3 && (ch1_vert_offset_10uV_l < uVar2)))) {
      if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
        iVar3 = 1;
        ch1_vert_offset_pixels = ch1_vert_offset_pixels + 1;
        if (global_settings != 0) {
          return;
        }
      }
      else {
        ch1_vert_offset_pixels = ch1_vert_offset_pixels + 2;
        if (global_settings != 0) {
          return;
        }
        iVar3 = 2;
      }
      ch1_vert_scroll_offset = iVar3 + ch1_vert_scroll_offset;
      return;
    }
    lVar1 = CONCAT44((uVar2 * 0x19 >> 0x20) + iVar3 * 0x19,uVar2 * 0x19);
  }
  else {
    if (param_1 != 0x22) {
      return;
    }
    if (ch1_volt_scale_10uV < 100000) {
      uVar2 = 800000 / (100000 / ch1_volt_scale_10uV);
    }
    else {
      uVar2 = (ch1_volt_scale_10uV / 100000) * 800000;
    }
    if ((-uVar2 < CONCAT44(ch1_vert_offset_10uV_h,ch1_vert_offset_10uV_l)) || ((false && (-uVar2 < ch1_vert_offset_10uV_l)))) {
      if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
        iVar3 = 1;
        ch1_vert_offset_pixels = ch1_vert_offset_pixels + -1;
        if (global_settings != 0) {
          return;
        }
      }
      else {
        ch1_vert_offset_pixels = ch1_vert_offset_pixels + -2;
        if (global_settings != 0) {
          return;
        }
        iVar3 = 2;
      }
      ch1_vert_scroll_offset = ch1_vert_scroll_offset - iVar3;
      return;
    }
    lVar1 = (uVar2 - CONCAT44((uVar2 >> 0x1f) << 2 | uVar2 >> 0x1e,uVar2 << 2)) * 8 - uVar2;
  }
  ch1_vert_offset_pixels = __divdi3(lVar1,lVar1 >> 0x20,ch1_volt_scale_10uV,ch1_volt_scale_10uV >> 0x1f);
  zw_draw_popup_message("Limit",5,1000,0);
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void zw_scope_ch2_vertical_movement_(int param_1)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  
  if (ch2_enabled == '\0') {
    return;
  }
  if (global_settings == 0) goto LAB_0801d34c;
  if (param_1 == 0xd) {
    if (ch2_v_div_index < 0xd) {
      ch2_v_div_index = ch2_v_div_index + 1;
LAB_0801d412:
      FUN_0802bc38(*(&DAT_08055a1c + ch2_v_div_index * 4),*(&DAT_08055a1c + ch2_v_div_index * 4) >> 0x1f,0x6e0087,0x5f);
      goto LAB_0801d34c;
    }
    ch2_v_div_index = 0xd;
  }
  else {
    if (param_1 != 5) goto LAB_0801d34c;
    if (4 < ch2_v_div_index) {
      ch2_v_div_index = ch2_v_div_index - 1;
      goto LAB_0801d412;
    }
    ch2_v_div_index = 4;
  }
  zw_draw_popup_message("Limit",5,1000,0);
LAB_0801d34c:
  if (cursors_y_enable != '\0') {
    return;
  }
  if ((DAT_2001ddc9 == '\0') && (active_channel_0_ch1_1_ch2_2_math != '\x01')) {
    return;
  }
  if (param_1 == 0x23) {
    if (ch2_volt_scale_10uV < 100000) {
      uVar2 = 800000 / (100000 / ch2_volt_scale_10uV);
    }
    else {
      uVar2 = (ch2_volt_scale_10uV / 100000) * 800000;
    }
    iVar3 = uVar2 >> 0x1f;
    if ((ch2_vert_offset_10uV_h < iVar3) || ((ch2_vert_offset_10uV_h == iVar3 && (ch2_vert_offset_10uV_l < uVar2)))) {
      if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
        iVar3 = 1;
        ch2_vert_offset_pixels = ch2_vert_offset_pixels + 1;
        if (global_settings != 0) {
          return;
        }
      }
      else {
        ch2_vert_offset_pixels = ch2_vert_offset_pixels + 2;
        if (global_settings != 0) {
          return;
        }
        iVar3 = 2;
      }
      ch2_vert_scroll_offset = iVar3 + ch2_vert_scroll_offset;
      return;
    }
    lVar1 = CONCAT44((uVar2 * 0x19 >> 0x20) + iVar3 * 0x19,uVar2 * 0x19);
  }
  else {
    if (param_1 != 0x24) {
      return;
    }
    if (ch2_volt_scale_10uV < 100000) {
      uVar2 = 800000 / (100000 / ch2_volt_scale_10uV);
    }
    else {
      uVar2 = (ch2_volt_scale_10uV / 100000) * 800000;
    }
    if ((-uVar2 < CONCAT44(ch2_vert_offset_10uV_h,ch2_vert_offset_10uV_l)) || ((false && (-uVar2 < ch2_vert_offset_10uV_l)))) {
      if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
        iVar3 = 1;
        ch2_vert_offset_pixels = ch2_vert_offset_pixels + -1;
        if (global_settings != 0) {
          return;
        }
      }
      else {
        ch2_vert_offset_pixels = ch2_vert_offset_pixels + -2;
        if (global_settings != 0) {
          return;
        }
        iVar3 = 2;
      }
      ch2_vert_scroll_offset = ch2_vert_scroll_offset - iVar3;
      return;
    }
    lVar1 = (uVar2 - CONCAT44((uVar2 >> 0x1f) << 2 | uVar2 >> 0x1e,uVar2 << 2)) * 8 - uVar2;
  }
  ch2_vert_offset_pixels = __divdi3(lVar1,lVar1 >> 0x20,ch2_volt_scale_10uV,ch2_volt_scale_10uV >> 0x1f);
  zw_draw_popup_message("Limit",5,1000,0);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_0801d55c(int param_1)

{
  int iVar1;
  
  if (ch2_enabled == 0) {
    return;
  }
  if (cursors_y_enable != 0) {
    return;
  }
  if (DAT_2001ddc9 != 0) {
    return;
  }
  if (active_channel_0_ch1_1_ch2_2_math != 2) {
    return;
  }
  if (param_1 == 0x31) {
    if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
      iVar1 = 1;
      _DAT_2001de2c = _DAT_2001de2c + 1;
      if (global_settings != 0) goto LAB_0801d592;
    }
    else {
      _DAT_2001de2c = _DAT_2001de2c + 2;
      if (global_settings != 0) goto LAB_0801d592;
      iVar1 = 2;
    }
    DAT_2001de30 = iVar1 + DAT_2001de30;
  }
  else if (param_1 == 0x32) {
    if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
      iVar1 = 1;
      _DAT_2001de2c = _DAT_2001de2c + -1;
      if (global_settings != 0) goto LAB_0801d592;
    }
    else {
      _DAT_2001de2c = _DAT_2001de2c + -2;
      if (global_settings != 0) goto LAB_0801d592;
      iVar1 = 2;
    }
    DAT_2001de30 = DAT_2001de30 - iVar1;
  }
LAB_0801d592:
  if (_DAT_2001de2c < 0x65) {
    if (_DAT_2001de2c < -100) {
      _DAT_2001de2c = -100;
    }
  }
  else {
    _DAT_2001de2c = 100;
  }
  if (DAT_2001de30 < 101) {
    if (DAT_2001de30 < -100) {
      DAT_2001de30 = -100;
    }
  }
  else {
    DAT_2001de30 = 100;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Restarted to delay deadcode elimination for space: register
// WARNING: Restarted to delay deadcode elimination for space: stack


void zw_horizontal_control__0801d64c(int param_1)

{
  undefined4 *puVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined4 uVar10;
  int iVar11;
  uint uVar12;
  
  lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
  if (long_memory_enable_ != '\0') {
    timebase_index_2_5ns_30_10s = ~(ch2_enabled != 1) + 2;
    _horiz_trigger_delay_ps_l = 0;
    _roll_mode_view_offset__l = 0;
    goto LAB_0801d69a;
  }
  if (param_1 == 0x11) {
    uVar12 = timebase_index_2_5ns_30_10s;
    if (uVar12 < 0x1e) {
      if (DAT_2001de15 == '\0') {
        uVar12 = uVar12 + 1;
LAB_0801d894:
        timebase_index_2_5ns_30_10s = uVar12;
        iVar11 = (uVar12 & 0xff) * 8;
        FUN_0802bc38(*(&DAT_080558fc + iVar11) * 1000,(*(&DAT_080558fc + iVar11) * 1000 >> 0x20) + *(&DAT_08055900 + iVar11) * 1000,0x6e0087,1);
        lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
        if (global_settings != 1) goto LAB_0801d6a6;
        goto LAB_0801d8ce;
      }
      if (zoom_timebase_index_ < uVar12) {
        uVar12 = zoom_timebase_index_ + 1;
        zoom_timebase_index_ = uVar12;
        iVar11 = (uVar12 & 0xff) * 8;
        FUN_0802bc38(*(&DAT_080558fc + iVar11) * 1000,(*(&DAT_080558fc + iVar11) * 1000 >> 0x20) + *(&DAT_08055900 + iVar11) * 1000,0x6e0087,1);
        uVar8 = *(&DAT_080558fc + zoom_timebase_index_ * 8);
        uVar10 = *(&DAT_08055900 + zoom_timebase_index_ * 8);
LAB_0801d7cc:
        uVar4 = DAT_2001a158 - CONCAT44(uVar10,uVar8);
        lVar3 = (uVar4 & 0xffffffff) * 6000;
        uVar12 = lVar3;
        puVar1 = (lVar3 >> 0x20) + (uVar4 >> 0x20) * 6000;
        lVar2 = CONCAT44(puVar1,uVar12);
        if ((horiz_window_pos_ps__h <= puVar1) && ((horiz_window_pos_ps__h != puVar1 || (lVar2 = CONCAT44(puVar1,uVar12), horiz_window_pos_ps__l <= uVar12)))) {
          lVar2 = -CONCAT44(puVar1,uVar12);
          if ((lVar2 <= CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l)) &&
             ((lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l), true ||
              (lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l), lVar2 <= horiz_window_pos_ps__l)))) goto LAB_0801d6a6;
        }
        lVar3 = lVar2;
        goto LAB_0801d6a6;
      }
    }
LAB_0801d87e:
    zw_draw_popup_message("Limit",5,1000,0);
    lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
  }
  else if (param_1 == 9) {
    uVar12 = timebase_index_2_5ns_30_10s;
    if (ch2_enabled == 1) {
      if (3 < uVar12) {
        if (DAT_2001de15 == '\0') goto LAB_0801d9ac;
        goto LAB_0801d822;
      }
      timebase_index_2_5ns_30_10s = 3;
    }
    else {
      if (DAT_2001de15 == '\0') {
        if (2 < uVar12) {
LAB_0801d9ac:
          uVar12 = uVar12 - 1;
          goto LAB_0801d894;
        }
      }
      else {
LAB_0801d822:
        if (6 < uVar12 - zoom_timebase_index_) goto LAB_0801d87e;
        if (2 < uVar12) {
          uVar12 = zoom_timebase_index_ - 1;
          zoom_timebase_index_ = uVar12;
          iVar11 = (uVar12 & 0xff) * 8;
          FUN_0802bc38(*(&DAT_080558fc + iVar11) * 1000,(*(&DAT_080558fc + iVar11) * 1000 >> 0x20) + *(&DAT_08055900 + iVar11) * 1000,0x6e0087,1);
          uVar8 = *(&DAT_080558fc + zoom_timebase_index_ * 8);
          uVar10 = *(&DAT_08055900 + zoom_timebase_index_ * 8);
          goto LAB_0801d7cc;
        }
      }
      timebase_index_2_5ns_30_10s = 2;
    }
    zw_draw_popup_message("Limit",5,1000,0);
    lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
    if (global_settings == 1) {
LAB_0801d8ce:
      lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
      DAT_2000a8c8 = timebase_index_2_5ns_30_10s;
    }
  }
LAB_0801d6a6:
  horiz_window_pos_ps__h = lVar3 >> 0x20;
  horiz_window_pos_ps__l = lVar3;
  if (((cursors_x_enable != '\0') || (DAT_2001ddc9 != '\0')) || (fft_mode_0_off_1_log_2_lin_3_music != '\0')) goto LAB_0801d69a;
  if (param_1 == 4) {
    if ((global_settings == 0) || (roll_mode_enable != '\0')) {
      if (global_settings == 0) {
        if (DAT_2001de15 == '\0') {
          if (roll_split_index_ < 299) {
            if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
              uVar8 = timebase_val_ns_l * 0x28;
              iVar11 = (timebase_val_ns_l * 0x28 >> 0x20) + timebase_val_ns_h * 0x28;
            }
            else {
              uVar8 = timebase_val_ns_l * 100;
              iVar11 = (timebase_val_ns_l * 100 >> 0x20) + timebase_val_ns_h * 100;
            }
            _roll_mode_view_offset__l = _roll_mode_view_offset__l - CONCAT44(iVar11,uVar8);
          }
          lVar5 = _roll_mode_view_offset__l;
          uVar12 = _roll_mode_view_offset__l;
          lVar3 = 100 - _buffer_depth_l;
          uVar10 = 0xe8;
          uVar8 = __divdi3(0x1000,0xe8,sample_rate_hz_l);
          lVar2 = (lVar3 / 2) * CONCAT44(uVar10,uVar8);
          lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
          if ((lVar2 < lVar5) || ((false && (lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l), lVar2 < uVar12)))) goto LAB_0801d69a;
          goto LAB_0801da3c;
        }
      }
      else if (DAT_2001de15 == '\0') goto LAB_0801d69a;
    }
    else if (DAT_2001de15 == '\0') {
      if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
        uVar8 = timebase_val_ns_l * 0x28;
        iVar11 = (timebase_val_ns_l * 0x28 >> 0x20) + timebase_val_ns_h * 0x28;
      }
      else {
        uVar8 = timebase_val_ns_l * 100;
        iVar11 = (timebase_val_ns_l * 100 >> 0x20) + timebase_val_ns_h * 100;
      }
      lVar2 = CONCAT44(iVar11,uVar8) + _horiz_trigger_delay_ps_l;
      lVar5 = (_buffer_depth_l + -100) / 2;
      uVar10 = 0xe8;
      _horiz_trigger_delay_ps_l = lVar2;
      uVar8 = __divdi3(0x1000,0xe8,sample_rate_hz_l);
      lVar7 = CONCAT44(uVar10,uVar8);
      lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
      if ((lVar2 < lVar5 * lVar7) ||
         ((lVar6 = lVar5 * lVar7, false && (lVar6 = lVar5 * lVar7, lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l), lVar2 < lVar5 * lVar7))))
      goto LAB_0801d69a;
LAB_0801d754:
      lVar5 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
      _horiz_trigger_delay_ps_l = lVar6;
      goto LAB_0801d758;
    }
    iVar11 = *(&DAT_080558fc + zoom_timebase_index_ * 8);
    if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
      uVar12 = (iVar11 * 1000) / 0x19;
    }
    else {
      uVar12 = (iVar11 * 1000) / 10;
    }
    uVar9 = DAT_2001a158 - iVar11;
    lVar3 = lVar3 - uVar12;
    lVar5 = (CONCAT44(uVar9 >> 0x1e,uVar9 * 4) + uVar9) * -0x4b0;
    if ((lVar5 <= lVar3) && ((true || (lVar5 <= lVar3)))) goto LAB_0801d69a;
  }
  else {
    if (param_1 != 3) goto LAB_0801d69a;
    if (global_settings == 0) {
      if (DAT_2001de15 == '\0') {
        if (1 < roll_draw_cursor_x_) {
          if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
            uVar8 = timebase_val_ns_l * 0x28;
            iVar11 = (timebase_val_ns_l * 0x28 >> 0x20) + timebase_val_ns_h * 0x28;
          }
          else {
            uVar8 = timebase_val_ns_l * 100;
            iVar11 = (timebase_val_ns_l * 100 >> 0x20) + timebase_val_ns_h * 100;
          }
          _roll_mode_view_offset__l = CONCAT44(iVar11,uVar8) + _roll_mode_view_offset__l;
        }
        lVar2 = _roll_mode_view_offset__l;
        uVar12 = _roll_mode_view_offset__l;
        lVar5 = (_buffer_depth_l + -100) / 2;
        uVar10 = 0xe8;
        uVar8 = __divdi3(0x1000,0xe8,sample_rate_hz_l);
        lVar7 = CONCAT44(uVar10,uVar8);
        lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
        if ((lVar2 < lVar5 * lVar7) ||
           ((lVar2 = lVar5 * lVar7, false && (lVar2 = lVar5 * lVar7, lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l), uVar12 < lVar5 * lVar7))))
        goto LAB_0801d69a;
LAB_0801da3c:
        lVar5 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
        _roll_mode_view_offset__l = lVar2;
        goto LAB_0801d758;
      }
    }
    else if (roll_mode_enable == '\0') {
      if (DAT_2001de15 == '\0') {
        if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
          uVar8 = timebase_val_ns_l * 0x28;
          iVar11 = (timebase_val_ns_l * 0x28 >> 0x20) + timebase_val_ns_h * 0x28;
        }
        else {
          uVar8 = timebase_val_ns_l * 100;
          iVar11 = (timebase_val_ns_l * 100 >> 0x20) + timebase_val_ns_h * 100;
        }
        lVar2 = _horiz_trigger_delay_ps_l - CONCAT44(iVar11,uVar8);
        lVar3 = 100 - _buffer_depth_l;
        uVar10 = 0xe8;
        _horiz_trigger_delay_ps_l = lVar2;
        uVar8 = __divdi3(0x1000,0xe8,sample_rate_hz_l);
        lVar6 = (lVar3 / 2) * CONCAT44(uVar10,uVar8);
        lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
        if ((lVar6 < lVar2) || ((false && (lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l), lVar6 < lVar2)))) goto LAB_0801d69a;
        goto LAB_0801d754;
      }
    }
    else if (DAT_2001de15 == '\0') goto LAB_0801d69a;
    iVar11 = *(&DAT_080558fc + zoom_timebase_index_ * 8);
    if ((shift_key_ == '\x01') || (force_fine_movement_ == '\x01')) {
      uVar12 = (iVar11 * 1000) / 0x19;
    }
    else {
      uVar12 = (iVar11 * 1000) / 10;
    }
    uVar9 = DAT_2001a158 - iVar11;
    lVar3 = uVar12 + lVar3;
    lVar5 = (CONCAT44(uVar9 >> 0x1e,uVar9 * 4) + uVar9) * 0x4b0;
    if ((lVar3 <= lVar5) && ((true || (lVar3 <= lVar5)))) goto LAB_0801d69a;
  }
LAB_0801d758:
  horiz_window_pos_ps__h = lVar5 >> 0x20;
  horiz_window_pos_ps__l = lVar5;
  zw_draw_popup_message("Limit",5,1000,0);
  lVar3 = CONCAT44(horiz_window_pos_ps__h,horiz_window_pos_ps__l);
LAB_0801d69a:
  horiz_window_pos_ps__h = lVar3 >> 0x20;
  horiz_window_pos_ps__l = lVar3;
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


int FUN_0801dc8c(uint param_1,int param_2,uint param_3,int param_4)

{
  ulonglong uVar1;
  uint uVar2;
  int iVar3;
  
  if (param_2 < 1) {
    if (param_2 == 0) {
      if (1000000000 < param_1) goto LAB_0801dd1a;
LAB_0801ddf0:
      if (param_1 < 0xf4241) goto LAB_0801dd76;
    }
    else if (param_2 < 1) {
      if (param_2 == 0) goto LAB_0801ddf0;
LAB_0801dd76:
      uVar1 = CONCAT44(param_4,param_3) + 0x38d7e00008000;
      if ((uVar1 < 0x71afd00000001) && ((true || (uVar1 == 0)))) {
        uVar1 = CONCAT44(param_4,param_3) + 0xe800001000;
        if ((0x1d100002000 < uVar1) || ((false && (0x2000 < uVar1)))) {
          uVar2 = __divdi3(param_3,param_4,1000,0);
          iVar3 = __divdi3(uVar2 * param_1,(uVar2 * param_1 >> 0x20) + uVar2 * param_2 + param_4 * param_1,1000000000,0);
          return iVar3;
        }
        goto LAB_0801dcfa;
      }
      uVar2 = __divdi3(param_3,param_4,1000000,0);
      goto LAB_0801de18;
    }
    param_1 = __divdi3(param_1,param_2,1000,0);
    uVar1 = CONCAT44(param_4,param_3) + 0x38d7e00008000;
    if ((0x71afd00000000 < uVar1) || ((false && (uVar1 != 0)))) {
      uVar2 = __divdi3(param_3,param_4,1000000,0);
      iVar3 = __divdi3(uVar2 * param_1,(uVar2 * param_1 >> 0x20) + uVar2 * param_2 + param_4 * param_1,1000,0);
      return iVar3;
    }
    iVar3 = 1;
  }
  else {
LAB_0801dd1a:
    param_1 = __divdi3(param_1,param_2,1000000,0);
    uVar1 = CONCAT44(param_4,param_3) + 0x38d7e00008000;
    if ((0x71afd00000000 < uVar1) || ((false && (uVar1 != 0)))) {
      iVar3 = __divdi3(param_3,param_4,1000000,0);
      return iVar3 * param_1;
    }
    iVar3 = 2;
  }
  uVar1 = CONCAT44(param_4,param_3) + 0xe800001000;
  if ((uVar1 < 0x1d100002001) && ((true || (uVar1 < 0x2001)))) {
    if (iVar3 != 0) {
      if (iVar3 != 1) {
        iVar3 = __divdi3(param_3 * param_1,(param_3 * param_1 >> 0x20) + param_3 * param_2 + param_4 * param_1,1000000,0);
        return iVar3;
      }
      iVar3 = __divdi3(param_3 * param_1,(param_3 * param_1 >> 0x20) + param_3 * param_2 + param_4 * param_1,1000000000,0);
      return iVar3;
    }
LAB_0801dcfa:
    iVar3 = __divdi3(param_3 * param_1,(param_3 * param_1 >> 0x20) + param_3 * param_2 + param_4 * param_1,0x1000,0xe8);
    return iVar3;
  }
  uVar2 = __divdi3(param_3,param_4,1000,0);
  if (iVar3 != 1) {
    iVar3 = __divdi3(uVar2 * param_1,(uVar2 * param_1 >> 0x20) + uVar2 * param_2 + param_1 * param_4,1000,0);
    return iVar3;
  }
LAB_0801de18:
  iVar3 = __divdi3(uVar2 * param_1,(uVar2 * param_1 >> 0x20) + uVar2 * param_2 + param_4 * param_1,1000000,0);
  return iVar3;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Restarted to delay deadcode elimination for space: register


void zw_set_scope_parameters_(void)

{
  uint uVar1;
  longlong lVar2;
  ulonglong uVar3;
  short sVar4;
  longlong lVar5;
  char cVar6;
  uint uVar7;
  int32_t iVar8;
  uint uVar9;
  undefined4 uVar10;
  int iVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  int iVar14;
  float in_vr0;
  float fVar15;
  
  timebase_val_ns_l = *(&DAT_080558fc + timebase_index_2_5ns_30_10s * 8);
  timebase_val_ns_h = *(&DAT_08055900 + timebase_index_2_5ns_30_10s * 8);
  printf_disabled_2("sysParm.time_div = %d\r\n");
  ch1_volt_scale_10uV = *(&DAT_08055a1c + ch1_v_div_index * 4);
  ch1_vert_offset_10uV_l = (ch1_volt_scale_10uV * ch1_vert_offset_pixels) / 0x19;
  ch1_vert_offset_10uV_h = ch1_vert_offset_10uV_l >> 0x1f;
  uVar7 = (ch1_volt_scale_10uV * 0x7f) / 0x19;
  iVar14 = uVar7 >> 0x1f;
  lVar2 = ch1_vert_offset_10uV_l + CONCAT44(ch1_trigger_level_10uV_target_h,ch1_trigger_level_10uV_target_l);
  if ((uVar7 < lVar2) || ((false && (uVar7 < lVar2)))) {
LAB_0801df48:
    lVar2 = CONCAT44(iVar14,uVar7);
  }
  else {
    uVar7 = (ch1_volt_scale_10uV * -0x7f) / 0x19;
    iVar14 = uVar7 >> 0x1f;
    if ((lVar2 < uVar7) || ((false && (lVar2 < uVar7)))) goto LAB_0801df48;
  }
  ch1_trigger_level_10uV_actual_h = lVar2 >> 0x20;
  ch1_trigger_level_10uV_actual_l = lVar2;
  iVar8 = __divdi3(lVar2 * 0x19,lVar2 * 0x19 >> 0x20,ch1_volt_scale_10uV,ch1_volt_scale_10uV >> 0x1f);
  ch2_volt_scale_10uV = *(&DAT_08055a1c + ch2_v_div_index * 4);
  ch2_vert_offset_10uV_l = (ch2_volt_scale_10uV * ch2_vert_offset_pixels) / 0x19;
  ch2_vert_offset_10uV_h = ch2_vert_offset_10uV_l >> 0x1f;
  lVar2 = ch2_vert_offset_10uV_l + CONCAT44(ch2_trigger_level_10uV_target_h,ch2_trigger_level_10uV_target_l);
  uVar7 = (ch2_volt_scale_10uV * 0x7f) / 0x19;
  iVar14 = uVar7 >> 0x1f;
  if ((uVar7 < lVar2) || ((false && (uVar7 < lVar2)))) {
LAB_0801dfae:
    lVar2 = CONCAT44(iVar14,uVar7);
  }
  else {
    uVar7 = (ch2_volt_scale_10uV * -0x7f) / 0x19;
    iVar14 = uVar7 >> 0x1f;
    if ((lVar2 < uVar7) || ((false && (lVar2 < uVar7)))) goto LAB_0801dfae;
  }
  ch2_trigger_level_10uV_h = lVar2 >> 0x20;
  ch2_trigger_level_10uV_l = lVar2;
  ch1_trigger_level_pixels___100 = iVar8;
  ch2_trigger_level_pixels = __divdi3(lVar2 * 0x19,lVar2 * 0x19 >> 0x20,ch2_volt_scale_10uV,ch2_volt_scale_10uV >> 0x1f);
  lVar2 = CONCAT44(sample_rate_hz_h,sample_rate_hz_l);
  cVar6 = ch2_enabled;
  if ((trigger_source_0_ch1_1_ch2 == '\0') || (ch2_enabled == '\0')) {
    sVar4 = iVar8;
  }
  else {
    sVar4 = ch2_trigger_level_pixels;
  }
  trigger_level_raw_adc__0_255 = sVar4 + 0x80;
  if (trigger_level_raw_adc__0_255 < 0xe4) {
    if (0x1c < trigger_level_raw_adc__0_255) goto LAB_0801dff0;
    trigger_level_raw_adc__0_255 = 0x1d;
    if (global_settings == 1) goto LAB_0801e1a4;
LAB_0801dff6:
    if (global_settings != 0) goto LAB_0801e1d6;
  }
  else {
    trigger_level_raw_adc__0_255 = 0xe3;
LAB_0801dff0:
    if (global_settings != 1) goto LAB_0801dff6;
LAB_0801e1a4:
    trigger_mode_0_auto_1_normal = trigger_mode_icon_0_auto_1_normal;
    if (((trigger_mode_icon_0_auto_1_normal == '\x01') && (roll_mode_enable == '\0')) && (DAT_2001ddc9 == '\0')) {
      DAT_200001c8 = 0x8000;
      DAT_200001c4 = 30000;
      DAT_200001bc = 10000;
      DAT_200001c0 = 12;
    }
    else {
      trigger_mode_0_auto_1_normal = '\0';
      DAT_200001c8 = 0;
      DAT_200001c4 = 60000;
      DAT_200001bc = 20000;
      DAT_200001c0 = 13;
    }
LAB_0801e1d6:
    uVar7 = DAT_200001c4;
    if (ch2_enabled == '\0') {
      if (DAT_200001c0 < timebase_index_2_5ns_30_10s) goto LAB_0801e1e8;
LAB_0801e7d8:
      sample_rate_hz_l = 250000000;
      sample_rate_hz_h = 0;
    }
    else {
      if ((ch2_enabled == '\x01') && (timebase_index_2_5ns_30_10s <= DAT_200001c0 - 1)) goto LAB_0801e7d8;
LAB_0801e1e8:
      if ((timebase_val_ns_h < 1) && ((timebase_val_ns_h != 0 || (timebase_val_ns_l < 0xf4241)))) {
        uVar10 = __divdi3(timebase_val_ns_l * 0xc,(timebase_val_ns_l * 0xc >> 0x20) + timebase_val_ns_h * 0xc,1000,0);
        iVar14 = 0;
        uVar7 = __divdi3(uVar7 * 1000,0,uVar10);
        sample_rate_hz_l = uVar7 * 1000;
        sample_rate_hz_h = (uVar7 * 1000 >> 0x20) + iVar14 * 1000;
      }
      else {
        iVar11 = DAT_200001c4 * 1000;
        iVar14 = (timebase_val_ns_l * 0xc >> 0x20) + timebase_val_ns_h * 0xc;
        uVar10 = __divdi3(timebase_val_ns_l * 0xc,iVar14,1000000,0);
        uVar7 = 0;
        sample_rate_hz_l = __divdi3(iVar11,0,uVar10,iVar14);
        sample_rate_hz_h = uVar7;
      }
    }
    lVar2 = CONCAT44(sample_rate_hz_h,sample_rate_hz_l);
    if (cVar6 == '\x01') {
      lVar2 = (sample_rate_hz_h >> 0x1f) + CONCAT44(sample_rate_hz_h,sample_rate_hz_l) >> 1;
    }
  }
  sample_rate_hz_h = lVar2 >> 0x20;
  sample_rate_hz_l = lVar2;
  printf_disabled_1("sysParm.fs = %d\r\n",sample_rate_hz_l,sample_rate_hz_l,sample_rate_hz_h);
  fast_render_flag_ = '\0';
  mid_speed_config_ = 0;
  uVar7 = sample_rate_hz_h;
  uVar9 = FUN_0801dc8c(sample_rate_hz_l,sample_rate_hz_h,timebase_val_ns_l * 12000,(timebase_val_ns_l * 12000 >> 0x20) + timebase_val_ns_h * 12000);
  printf_disabled_1("fs*div*12 = %d\r\n",uVar9);
  if (uVar7 < 1) {
    if ((uVar7 == 0) && (0xe < uVar9)) {
      if (299 < uVar9) goto LAB_0801e046;
      fast_render_flag_ = '\x01';
      printf_disabled_1("interp.longTemp_int = %d\r\n",uVar9);
    }
    else {
      fast_render_flag_ = '\x02';
      zw_draw_popup_message("Limit",5,1000,0);
    }
    if (ch2_enabled != '\0') goto LAB_0801e296;
LAB_0801e050:
    buffer_depth_l = DAT_200001c4;
    hw_buffer_wrap_addr_ = DAT_200001c8;
    if (fast_render_flag_ == '\0') goto LAB_0801e066;
LAB_0801e2b0:
    buffer_depth_h = 0;
    if (uVar9 == 0xf) {
      if (uVar7 != 0) goto LAB_0801e8d8;
      render_scale_factor__1M_timebase_ns = 200000;
      if (long_memory_enable_ == '\0') goto LAB_0801e2fe;
      goto LAB_0801e076;
    }
    if (uVar9 == 0x18) {
      if (uVar7 != 0) goto LAB_0801e8d8;
      render_scale_factor__1M_timebase_ns = 0x1e848;
    }
    else if (uVar9 == 0x1e) {
      if (uVar7 != 0) goto LAB_0801e8d8;
      render_scale_factor__1M_timebase_ns = 100000;
    }
    else if (uVar9 == 0x3c) {
      if (uVar7 != 0) goto LAB_0801e8d8;
      render_scale_factor__1M_timebase_ns = 50000;
    }
    else if (uVar9 == 0x4b) {
      if (uVar7 != 0) goto LAB_0801e8d8;
      render_scale_factor__1M_timebase_ns = 40000;
    }
    else if (uVar9 == 0x78) {
      if (uVar7 != 0) goto LAB_0801e8d8;
      render_scale_factor__1M_timebase_ns = 25000;
    }
    else if (uVar9 == 0x96) {
      if (uVar7 != 0) goto LAB_0801e8d8;
      render_scale_factor__1M_timebase_ns = 20000;
    }
    else if ((uVar9 == 0xf0) && (uVar7 == 0)) {
      render_scale_factor__1M_timebase_ns = 0x30d4;
    }
    else {
LAB_0801e8d8:
      render_scale_factor__1M_timebase_ns = 10000;
    }
    if (long_memory_enable_ != '\0') goto LAB_0801e076;
LAB_0801e2fe:
    if (fast_render_flag_ != '\x01') goto LAB_0801e086;
LAB_0801e302:
    buffer_depth_h = 0;
    printf_disabled_1("sysParm.interpTimes = %d\r\n",render_scale_factor__1M_timebase_ns);
  }
  else {
LAB_0801e046:
    if (ch2_enabled == '\0') {
      if ((0 < uVar7) || ((uVar7 == 0 && (0x5dc < uVar9)))) goto LAB_0801e050;
    }
    else if ((0 < uVar7) || ((uVar7 == 0 && (0x4af < uVar9)))) goto LAB_0801e296;
    mid_speed_config_ = 1;
    if (ch2_enabled == '\0') goto LAB_0801e050;
LAB_0801e296:
    buffer_depth_l = DAT_200001c4 >> 1;
    hw_buffer_wrap_addr_ = DAT_200001c8 >> 1;
    if (fast_render_flag_ != '\0') goto LAB_0801e2b0;
LAB_0801e066:
    buffer_depth_h = 0;
    render_scale_factor__1M_timebase_ns = 10000;
    if (long_memory_enable_ != '\0') {
LAB_0801e076:
      buffer_depth_h = 0;
      render_scale_factor__1M_timebase_ns = 200000;
      if (fast_render_flag_ == '\x01') goto LAB_0801e302;
    }
  }
LAB_0801e086:
  if (global_settings != 0) {
    if ((roll_menu_enable == '\x01') && ((0 < timebase_val_ns_h || ((timebase_val_ns_h == 0 && (199999999 < timebase_val_ns_l)))))) {
      roll_mode_enable = '\x01';
    }
    else {
      roll_mode_enable = '\0';
    }
  }
  uVar7 = sample_rate_hz_h;
  uVar10 = FUN_0801dc8c(sample_rate_hz_l,sample_rate_hz_h,horiz_trigger_delay_ps_l,horiz_trigger_delay_ps_h);
  lVar5 = (buffer_depth_h >> 0x1f) + CONCAT44(buffer_depth_h,buffer_depth_l) >> 1;
  lVar2 = lVar5 + CONCAT44(uVar7,uVar10);
  pre_trigger_samples_ = lVar2;
  if ((0 < lVar2) || ((false && (pre_trigger_samples_ != 0)))) {
    if ((CONCAT44(buffer_depth_h,buffer_depth_l) <= lVar2) && ((true || (buffer_depth_l <= pre_trigger_samples_)))) {
      pre_trigger_samples_ = buffer_depth_l;
    }
  }
  else {
    pre_trigger_samples_ = 0;
  }
  printf_disabled_1("sysParm.preDepth = %d\r\n",pre_trigger_samples_,lVar5,lVar5 >> 0x20);
  post_trigger_samples_ = buffer_depth_l - pre_trigger_samples_;
  printf_disabled_1("sysParm.postDepth = %d\r\n");
  if ((timebase_val_ns_h < 1) && ((timebase_val_ns_h != 0 || (timebase_val_ns_l < 0x186a1)))) {
    uVar7 = 100000;
  }
  else {
    uVar7 = 1000;
  }
  uVar9 = sample_rate_hz_h;
  uVar7 = FUN_0801dc8c(sample_rate_hz_l,sample_rate_hz_h,timebase_val_ns_l * uVar7,(timebase_val_ns_l * uVar7 >> 0x20) + timebase_val_ns_h * uVar7);
  printf_disabled_1("longTemp_int1\r\n");
  if (fast_render_flag_ - 1U < 2) {
    DAT_2001ddb4 = 0;
    iVar14 = 100;
  }
  else {
    uVar1 = (buffer_depth_l * 0x9c4 >> 0x20) + buffer_depth_h * 0x9c4;
    if ((uVar1 < uVar9) || ((uVar9 == uVar1 && (buffer_depth_l * 0x9c4 < uVar7)))) {
LAB_0801e356:
      __floatdisf();
    }
    else {
      if ((timebase_val_ns_h < 1) && ((timebase_val_ns_h != 0 || (timebase_val_ns_l < 0x186a1)))) {
        __floatunsidf(uVar7);
      }
      else {
        uVar1 = (buffer_depth_l * 0x19 >> 0x20) + buffer_depth_h * 0x19;
        if ((uVar1 < uVar9) || ((uVar9 == uVar1 && (buffer_depth_l * 0x19 < uVar7)))) goto LAB_0801e356;
        __floatunsidf(uVar7);
      }
      __divdf3();
      __truncdfsf2();
    }
    iVar14 = in_vr0 * 0.0;
    _global_settings = in_vr0;
  }
  printf_disabled_1("sysParm.col_len = %d\r\n",iVar14);
  lVar2 = CONCAT44((timebase_val_ns_l * 6000 >> 0x20) + timebase_val_ns_h * 6000,timebase_val_ns_l * 6000) - _roll_mode_view_offset__l;
  uVar7 = sample_rate_hz_h;
  uVar10 = FUN_0801dc8c(sample_rate_hz_l,sample_rate_hz_h,lVar2,lVar2 >> 0x20);
  if ((((global_settings == 0) && (roll_mode_enable != '\0')) && (roll_direction_0_left_1_right == 0)) && (block_mode_enable_ == '\0')) {
    uVar3 = CONCAT44(uVar7,uVar10) - buffer_pointer_;
  }
  else {
    uVar3 = CONCAT44(uVar7,uVar10) - ((buffer_depth_h >> 0x1f) + CONCAT44(buffer_depth_h,buffer_depth_l) >> 1);
  }
  if (fast_render_flag_ == '\x01') {
    lVar2 = render_scale_factor__1M_timebase_ns * (uVar3 & 0xffffffff);
    iVar14 = (lVar2 >> 0x20) + render_scale_factor__1M_timebase_ns * (uVar3 >> 0x20);
    uVar10 = __divdi3(lVar2,iVar14,10000,0);
    uVar3 = CONCAT44(iVar14,uVar10);
  }
  uVar12 = uVar3 >> 0x20;
  iVar14 = uVar3 * 1000 >> 0x20;
  uVar10 = __fixsfdi();
  iVar11 = __divdi3(uVar3 * 1000,iVar14,uVar10,uVar12);
  if ((iVar14 < 1) && ((iVar14 != 0 || (iVar11 == 0)))) {
    roll_split_index_ = 0;
    uVar7 = 0;
  }
  else {
    uVar7 = (iVar11 + 999) / 1000;
    roll_split_index_ = uVar7;
    uVar7 = uVar7 & 0x7fff;
  }
  printf_disabled_1("sysParm.start_col = %d\r\n",uVar7);
  lVar2 = CONCAT44((timebase_val_ns_l * 6000 >> 0x20) + timebase_val_ns_h * 6000,timebase_val_ns_l * 6000) + _roll_mode_view_offset__l;
  uVar7 = sample_rate_hz_h;
  uVar10 = FUN_0801dc8c(sample_rate_hz_l,sample_rate_hz_h,lVar2,lVar2 >> 0x20);
  if (((global_settings == 0) && (roll_mode_enable != '\0')) && ((block_mode_enable_ == '\0' && (roll_direction_0_left_1_right != 0)))) {
    uVar3 = CONCAT44(uVar7,uVar10) - buffer_pointer_;
  }
  else {
    uVar3 = CONCAT44(uVar7,uVar10) - ((buffer_depth_h >> 0x1f) + CONCAT44(buffer_depth_h,buffer_depth_l) >> 1);
  }
  if (fast_render_flag_ == '\x01') {
    lVar2 = render_scale_factor__1M_timebase_ns * (uVar3 & 0xffffffff);
    iVar14 = (lVar2 >> 0x20) + render_scale_factor__1M_timebase_ns * (uVar3 >> 0x20);
    uVar10 = __divdi3(lVar2,iVar14,10000,0);
    uVar3 = CONCAT44(iVar14,uVar10);
  }
  uVar13 = uVar3 >> 0x20;
  uVar10 = uVar3 * 1000 >> 0x20;
  fVar15 = _global_settings * 0.0;
  uVar12 = __fixsfdi();
  uVar12 = __divdi3(uVar3 * 1000,uVar10,uVar12,uVar13);
  uVar9 = 0;
  lVar2 = 299 - CONCAT44(uVar10,uVar12);
  uVar7 = lVar2;
  if ((0x12a < lVar2) || ((false && (0x12a < uVar7)))) {
    uVar9 = 299;
    roll_draw_cursor_x_ = 299;
    uVar7 = 299;
  }
  else if (((0x96 < lVar2) || ((false && (0x96 < uVar7)))) || ((roll_mode_enable != '\0' && (uVar9 = roll_direction_0_left_1_right, uVar9 != 0)))) {
    roll_draw_cursor_x_ = lVar2;
    uVar7 = uVar7 & 0xffff;
  }
  else {
    uVar9 = 0x96;
    roll_draw_cursor_x_ = 0x96;
    uVar7 = 0x96;
  }
  printf_disabled_1("sysParm.end_col = %d\r\n",uVar7,299,uVar9);
  uVar7 = roll_draw_cursor_x_;
  if (uVar7 < roll_split_index_) {
    roll_split_index_ = roll_draw_cursor_x_;
  }
  __floatdisf(buffer_depth_l,buffer_depth_h);
  if (fVar15 < _global_settings) {
    if (((global_settings != 0) || (roll_mode_enable == '\0')) || (block_mode_enable_ != '\0')) {
      _global_settings = fVar15 / ((uVar7 - roll_split_index_) + 1);
    }
  }
  if (horiz_ref_mode__0_center__1_trig_lock_ == '\0') {
    lVar2 = (CONCAT44((timebase_val_ns_l * 6000 >> 0x20) + timebase_val_ns_h * 6000,timebase_val_ns_l * 6000) +
            CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l)) - _roll_mode_view_offset__l;
  }
  else {
    lVar2 = (CONCAT44((timebase_val_ns_l * 6000 >> 0x20) + timebase_val_ns_h * 6000,timebase_val_ns_l * 6000) +
            CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l)) - _horiz_window_pos_ps__l;
    __divdi3(horiz_trigger_delay_ps_l,horiz_trigger_delay_ps_h,1000,0);
    printf_disabled_1("sysParm.trig_pos = %d\r\n");
  }
  iVar14 = (sample_rate_hz_l * 1000 >> 0x20) + sample_rate_hz_h * 1000;
  hardware_trigger_delay_ = FUN_0801dc8c(sample_rate_hz_l * 1000,iVar14,lVar2,lVar2 >> 0x20);
  DAT_2001dd14 = iVar14;
  if (fast_render_flag_ == '\x01') {
    buffer_trigger_index_ =
         __divdi3(render_scale_factor__1M_timebase_ns * hardware_trigger_delay_,
                  (render_scale_factor__1M_timebase_ns * hardware_trigger_delay_ >> 0x20) + iVar14 * render_scale_factor__1M_timebase_ns,10000000,0);
  }
  else {
    lVar2 = ((CONCAT44(pre_trigger_samples_ >> 0x1b,pre_trigger_samples_ << 5) - pre_trigger_samples_) * 4 + pre_trigger_samples_) * 8;
    if ((lVar2 < CONCAT44(iVar14,hardware_trigger_delay_)) || ((false && (lVar2 < hardware_trigger_delay_)))) {
      buffer_trigger_index_ = pre_trigger_samples_;
    }
    else {
      lVar2 = ((post_trigger_samples_ - CONCAT44(post_trigger_samples_ >> 0x1b,post_trigger_samples_ << 5)) * 4 - post_trigger_samples_) * 8;
      if ((lVar2 < CONCAT44(iVar14,hardware_trigger_delay_)) || ((false && (lVar2 < hardware_trigger_delay_)))) {
        buffer_trigger_index_ = hardware_trigger_delay_ / 1000;
        printf_disabled_1("sysParm.winAddrOffset = %d\r\n");
        goto joined_r0x0801e662;
      }
      buffer_trigger_index_ = -post_trigger_samples_;
    }
  }
  printf_disabled_1("sysParm.winAddrOffset = %d\r\n",buffer_trigger_index_);
joined_r0x0801e662:
  if ((hi_rate_enable == '\0') && (((ets_enable_ == '\0' || (0 < timebase_val_ns_h)) || ((timebase_val_ns_h == 0 && (200 < timebase_val_ns_l)))))) {
    highspeed_sys_flag_ = 0;
    return;
  }
  highspeed_sys_flag_ = 1;
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void zw_scope_state_change__0801ea14(int param_1)

{
  bool bVar1;
  uint uVar2;
  longlong lVar3;
  longlong lVar4;
  int iVar5;
  byte bVar6;
  byte bVar7;
  int iVar8;
  
  lVar3 = CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l);
  lVar4 = lVar3;
  if (param_1 == 10) {
    DAT_2001de0f = '\0';
    if (global_settings == 0) {
      if ((timebase_val_ns_h < 1) && ((timebase_val_ns_h != 0 || (timebase_val_ns_l < 200000000)))) {
        lVar3 = CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l) - CONCAT44(roll_mode_view_offset__h,roll_mode_view_offset__l);
      }
      else {
        lVar3 = 0;
      }
      lVar4 = ((((CONCAT44(timebase_val_ns_l >> 6 | timebase_val_ns_h << 0x1a,timebase_val_ns_l << 0x1a) - CONCAT44(timebase_val_ns_h,timebase_val_ns_l)) *
                 0x8000002 - CONCAT44(timebase_val_ns_h,timebase_val_ns_l)) * 0x10 + CONCAT44(timebase_val_ns_h,timebase_val_ns_l)) * 8 +
              CONCAT44(timebase_val_ns_h,timebase_val_ns_l)) * 0x10;
      if ((lVar4 <= lVar3) && ((true || (lVar4 <= lVar3)))) {
        uVar2 = timebase_val_ns_l * 6000;
        iVar5 = (timebase_val_ns_l * 6000 >> 0x20) + timebase_val_ns_h * 6000;
        if ((CONCAT44(iVar5,uVar2) < lVar3) || ((lVar4 = lVar3, false && (uVar2 < lVar3)))) {
          lVar4 = CONCAT44(iVar5,uVar2);
        }
      }
      roll_mode_view_offset__l = 0;
      roll_mode_view_offset__h = 0;
    }
    else {
      ch1_vert_offset_buffer_10uV_l = ch1_vert_offset_10uV_l;
      ch1_vert_offset_buffer_10uV_h = ch1_vert_offset_10uV_h;
      ch2_vert_offset_buffer_10uV_l = ch2_vert_offset_10uV_l;
      ch2_vert_offset_buffer_10uV_h = ch2_vert_offset_10uV_h;
      trigger_level_raw_adc_buffer = trigger_level_raw_adc__0_255;
    }
    ch1_vert_scroll_offset = 0;
    ch2_vert_scroll_offset = 0;
    DAT_2001de30 = 0;
    global_settings = ~(global_settings != 0);
  }
  else {
    if (param_1 == 0x12) {
      if ((system_status_ == '\x01') && (roll_mode_enable == '\0')) {
        DAT_2001de0f = roll_mode_enable;
        acq_buffer_ready_flag_ = system_status_;
        lVar3 = CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l) - CONCAT44(roll_mode_view_offset__h,roll_mode_view_offset__l);
        global_settings = 2;
        roll_mode_view_offset__l = 0;
        roll_mode_view_offset__h = 0;
        lVar4 = ((((CONCAT44(timebase_val_ns_l >> 6 | timebase_val_ns_h << 0x1a,timebase_val_ns_l << 0x1a) - CONCAT44(timebase_val_ns_h,timebase_val_ns_l)) *
                   0x8000002 - CONCAT44(timebase_val_ns_h,timebase_val_ns_l)) * 0x10 + CONCAT44(timebase_val_ns_h,timebase_val_ns_l)) * 8 +
                CONCAT44(timebase_val_ns_h,timebase_val_ns_l)) * 0x10;
        if ((lVar4 <= lVar3) && ((true || (lVar4 <= lVar3)))) {
          uVar2 = timebase_val_ns_l * 6000;
          iVar5 = (timebase_val_ns_l * 6000 >> 0x20) + timebase_val_ns_h * 6000;
          if ((CONCAT44(iVar5,uVar2) < lVar3) || ((lVar4 = lVar3, false && (uVar2 < lVar3)))) {
            lVar4 = CONCAT44(iVar5,uVar2);
          }
        }
        horiz_trigger_delay_ps_h = lVar4 >> 0x20;
        horiz_trigger_delay_ps_l = lVar4;
        ch1_vert_scroll_offset = 0;
        ch2_vert_scroll_offset = 0;
        DAT_2001de30 = 0;
        ch1_vert_offset_buffer_10uV_l = ch1_vert_offset_10uV_l;
        ch1_vert_offset_buffer_10uV_h = ch1_vert_offset_10uV_h;
        ch2_vert_offset_buffer_10uV_l = ch2_vert_offset_10uV_l;
        ch2_vert_offset_buffer_10uV_h = ch2_vert_offset_10uV_h;
        if (trigger_level_mode_0_auto_1_manual == '\0') {
          if ((trigger_source_0_ch1_1_ch2 == '\0') || (ch2_enabled == '\0')) {
            iVar5 = -ch1_volt_scale_10uV >> 0x1f;
            if ((((iVar5 < ch1_trigger_level_10uV_target_h) ||
                 ((ch1_trigger_level_10uV_target_h == iVar5 && (-ch1_volt_scale_10uV < ch1_trigger_level_10uV_target_l)))) &&
                ((iVar5 = ch1_volt_scale_10uV >> 0x1f, ch1_trigger_level_10uV_target_h < iVar5 ||
                 ((iVar5 == ch1_trigger_level_10uV_target_h && (ch1_trigger_level_10uV_target_l < ch1_volt_scale_10uV)))))) &&
               (ch1_trigger_level_10uV_target_l = ch1_volt_scale_10uV, ch1_trigger_level_10uV_target_h = iVar5, ch1_coupling_0_dc_1_ac != '\0')) {
              ch1_trigger_level_10uV_target_l = ch1_volt_scale_10uV / 2;
              ch1_trigger_level_10uV_target_h = ch1_volt_scale_10uV - iVar5 >> 0x1f;
            }
          }
          else {
            iVar5 = -ch2_volt_scale_10uV >> 0x1f;
            iVar8 = ch2_volt_scale_10uV >> 0x1f;
            if (((iVar5 < ch2_trigger_level_10uV_target_h) ||
                ((((ch2_trigger_level_10uV_target_h == iVar5 && (-ch2_volt_scale_10uV < ch2_trigger_level_10uV_target_l)) ||
                  (ch2_trigger_level_10uV_target_h < iVar8)) ||
                 ((iVar8 == ch2_trigger_level_10uV_target_h && (ch2_trigger_level_10uV_target_l < ch2_volt_scale_10uV)))))) &&
               (ch2_trigger_level_10uV_target_l = ch2_volt_scale_10uV, ch2_trigger_level_10uV_target_h = iVar8, ch2_coupling_dc_ac != '\0')) {
              ch2_trigger_level_10uV_target_l = ch2_volt_scale_10uV / 2;
              ch2_trigger_level_10uV_target_h = ch2_volt_scale_10uV - iVar8 >> 0x1f;
            }
          }
          zw_set_scope_parameters_();
          lVar4 = CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l);
        }
        trigger_level_raw_adc_buffer = trigger_level_raw_adc__0_255;
        goto LAB_0801eb40;
      }
    }
    else {
      if (param_1 == 2) {
        if ((system_status_ != '\x01') || (DAT_2001ddc9 != '\0')) goto LAB_0801eb3e;
        DAT_2001de00 = ~(DAT_2001de00 != 0);
        goto LAB_0801eb40;
      }
      if (param_1 == 7) {
        lVar4 = CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l);
        if (ch2_enabled != '\x01') goto LAB_0801eb40;
        lVar4 = lVar3;
        if ((DAT_2001de01 & 1) != 0) goto LAB_0801eb4c;
        bVar6 = active_channel_0_ch1_1_ch2_2_math + 1;
        bVar7 = active_channel_0_ch1_1_ch2_2_math + 1;
        if (channel_math_mode_0_off_1_add_2_sub == '\0') {
          if (bVar7 < 2) goto LAB_0801ed80;
LAB_0801ea54:
          active_channel_0_ch1_1_ch2_2_math = 0;
        }
        else {
          if (2 < bVar7) goto LAB_0801ea54;
LAB_0801ed80:
          bVar1 = active_channel_0_ch1_1_ch2_2_math != 0xff;
          active_channel_0_ch1_1_ch2_2_math = bVar6;
          if (bVar1) {
            if (bVar7 == 1) {
              zw_draw_popup_message("CH2",3,1000,0);
              lVar4 = CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l);
            }
            else {
              zw_draw_popup_message("Math",4,1000,0);
              lVar4 = CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l);
            }
            goto LAB_0801eb40;
          }
        }
        zw_draw_popup_message("CH1",3,1000,0);
        lVar4 = CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l);
        goto LAB_0801eb40;
      }
      if (param_1 != 0x47) goto LAB_0801eb3e;
      horiz_trigger_delay_ps_l = 0;
      horiz_trigger_delay_ps_h = 0;
      lVar4 = 0;
      roll_mode_view_offset__l = 0;
      roll_mode_view_offset__h = 0;
      if (ch2_enabled == '\0') {
        DAT_2001de09 = ch2_enabled;
        ch2_enabled = '\x01';
        if (timebase_index_2_5ns_30_10s == '\x02') {
          timebase_index_2_5ns_30_10s = '\x03';
        }
LAB_0801ebc4:
        if (global_settings == 1) goto LAB_0801eb4c;
      }
      else {
        if (DAT_2001ddc9 != '\0') goto LAB_0801ebc4;
        ch2_enabled = DAT_2001ddc9;
        FUN_08025938();
        if (global_settings == 1) goto LAB_0801eb3e;
      }
      global_settings = 1;
      DAT_2001de0f = '\0';
    }
LAB_0801eb3e:
    lVar4 = CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l);
  }
LAB_0801eb40:
  if (ch2_enabled == '\0') {
    trigger_source_0_ch1_1_ch2 = '\0';
    active_channel_0_ch1_1_ch2_2_math = 0;
  }
LAB_0801eb4c:
  horiz_trigger_delay_ps_h = lVar4 >> 0x20;
  horiz_trigger_delay_ps_l = lVar4;
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void zw_scope_settings__0801ee0c(int param_1)

{
  longlong lVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  printf_disabled_1("start setting...\r\n");
  zw_scope_state_change__0801ea14(param_1);
  if (system_status_ == '\x01') {
    zw_scope_ch1_vertical_movement_(param_1);
    zw_scope_ch2_vertical_movement_(param_1);
    if (((trigger_source_0_ch1_1_ch2 == '\x01') || ((cursors_y_enable == '\0' && (FUN_0801ce24(param_1), trigger_source_0_ch1_1_ch2 != '\0')))) &&
       (cursors_y_enable == '\0')) {
      FUN_0801cf70(param_1);
    }
    zw_horizontal_control__0801d64c(param_1);
    FUN_0801d55c(param_1);
  }
  zw_set_scope_parameters_();
  uVar3 = buffer_depth_h;
  uVar2 = buffer_depth_l;
  if ((system_status_ != '\x01') || ((param_1 != 0x11 && (param_1 != 9)))) goto LAB_0801ee2e;
  if (global_settings == 0) {
LAB_0801ee88:
    DAT_2001dcdc = 0;
    if ((param_1 == 10) && (global_settings == 0)) goto LAB_0801ee64;
  }
  else {
    if (roll_mode_enable == '\0') {
      uVar5 = 0xe8;
      uVar4 = __divdi3(0x1000,0xe8,sample_rate_hz_l,sample_rate_hz_h);
      lVar1 = ((uVar3 >> 0x1f) + CONCAT44(uVar3,uVar2) >> 1) * CONCAT44(uVar5,uVar4);
      if ((CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l) < lVar1) || ((false && (horiz_trigger_delay_ps_l < lVar1)))) {
        lVar1 = -((uVar3 >> 0x1f) + CONCAT44(uVar3,uVar2) >> 1) * CONCAT44(uVar5,uVar4);
        if ((lVar1 < CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l)) || ((false && (lVar1 < horiz_trigger_delay_ps_l)))) goto LAB_0801ee34;
        horiz_trigger_delay_ps_l = lVar1;
        horiz_trigger_delay_ps_h = lVar1 >> 0x20;
        zw_set_scope_parameters_();
      }
      else {
        horiz_trigger_delay_ps_l = lVar1;
        horiz_trigger_delay_ps_h = lVar1 >> 0x20;
        zw_set_scope_parameters_();
      }
LAB_0801ee2e:
      if (global_settings == 0) goto LAB_0801ee88;
    }
LAB_0801ee34:
    if (ch2_enabled == '\0') {
      if ((timebase_val_ns_h < 1) && ((timebase_val_ns_h != 0 || (timebase_val_ns_l <= DAT_200001bc)))) {
        adc_interleaving_enable_ = 1;
      }
      else {
        adc_interleaving_enable_ = 0;
      }
      if (system_status_ == '\x05') goto LAB_0801ee40;
      FUN_08016c3c(DAT_2000a8ac);
    }
    else {
      adc_interleaving_enable_ = 0;
LAB_0801ee40:
      FUN_08016c3c(0);
    }
    if ((roll_mode_enable != '\0') || ((global_settings != 2 && ((global_settings != 1 || (trigger_mode_icon_0_auto_1_normal != '\x01')))))) goto LAB_0801ee88;
    DAT_2001dcdc = 1;
  }
  FUN_08025290();
  if (ch2_enabled == '\x01') {
    FUN_0802539c();
  }
LAB_0801ee64:
  acq_buffer_ready_flag_ = 1;
  roll_mode_flag_ = ~(roll_mode_enable != '\0');
  settings_changed_flag_ = 1;
  return;
}




void FUN_0801eff0(int param_1)

{
  if ((param_1 != 0) && ((system_status_ == '\x01' || (system_status_ - 4U < 2)))) {
    zw_scope_settings__0801ee0c();
    return;
  }
  return;
}




void zw_global_settings_init_(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined2 *puVar3;
  undefined1 *puVar4;
  
  iVar1 = FUN_0801c3f0();
  if (iVar1 == 0) {
    ch1_vert_offset_pixels = -0x28;
    ch1_enabled_measurements_bitfield = 7;
    ch2_enabled_measurements_bitfield = 7;
    timebase_index_2_5ns_30_10s = 0x10;
    siggen_duty_cycle_0_1_ = 500;
    ch1_v_div_index = 9;
    ch2_v_div_index = 9;
    siggen_frequency_0_1hz = 10000;
    siggen_amplitude_mV = 2510;
    ch2_enabled = 1;
    horiz_trigger_delay_ps_l = 0;
    horiz_trigger_delay_ps_h = 0;
    ch1_trigger_level_10uV_target_l = 0;
    ch1_trigger_level_10uV_target_h = 0;
    ch1_coupling_0_dc_1_ac = 0;
    ch1_probe_mode_0_x1_1_x10_2_x100 = 1;
    ch2_vert_offset_pixels = -0x37;
    ch2_trigger_level_10uV_target_l = 0;
    ch2_trigger_level_10uV_target_h = 0;
    ch2_coupling_dc_ac = 0;
    ch2_probe_mode = 1;
    persistance_mode_0_off_1_infinite_2_1s = 0;
    roll_menu_enable = 1;
    trigger_mode_icon_0_auto_1_normal = 0;
    trigger_source_0_ch1_1_ch2 = 0;
    trigger_edge_0_rise_1_fall = 0;
    trigger_level_mode_0_auto_1_manual = 0;
    language_0_CN_1_EN = 1;
    active_channel_0_ch1_1_ch2_2_math = 0;
    DAT_2001de00 = 0;
    siggen_waveform_pattern = 1;
    siggen_enable = 1;
    key_beep_enable = 1;
    screen_brightness_0_80 = 40;
    system_status_ = 1;
    DAT_2001ddc9 = 0;
    cursor_x1_position = 0xffc9;
    cursor_y2_position = 0xffc9;
    ch1_color_index = 63;
    DAT_2001ddea = 0xf;
    settings_grid_style_0_none_1_dot_2_line = 2;
    settings_grid_color_0_dark_1_medium_2_light = 1;
    settings_ch2_color_0_green_1_purple_2_cyan = 1;
    hi_rate_enable = 1;
    ets_enable_ = 1;
    DAT_2001de0a = 1;
    settings_dmm_window_0_window_1_fullscreen = 1;
    ch1_gain_cal_ = 1000;
    ch2_gain_cal_ = 1000;
    frequency_meter_enable = 1;
    auto_off_enable = 0;
    fft_mode_0_off_1_log_2_lin_3_music = 0;
    cursors_x_enable = 0;
    cursors_y_enable = 0;
    cursor_x2_position = 0x37;
    cursor_y1_position = 0x37;
    DAT_2001de09 = 0;
    settings_invert_lcd = 0;
    freq_meter_ref_clock_hz = 10000600;
    counter_enable = 0;
    ch1_20mhz_limit = 0;
    ch2_20mhz_limit = 0;
    zw_draw_popup_message("Gain calib mode",0xf,1000000,0,1);
    puVar2 = &DAT_2000a834;
    iVar1 = 0xe;
    do {
      *puVar2 = 990000;
      puVar2[0xe] = 990000;
      puVar2 = puVar2 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    puVar4 = &DAT_2000a8a4;
    iVar1 = 0xe;
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    DAT_2000a8b4 = 1000;
    DAT_2000a8bc = 1000;
    DAT_2000a8b8 = 1000;
    DAT_2000a8c0 = 1000;
    puVar3 = &DAT_2001de34;
    iVar1 = 0xc;
    do {
      *puVar3 = 5000;
      puVar3 = puVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    DAT_2001de44 = 0x17ce;
    DAT_2001de48 = 0x17ce;
    printf_disabled_2("sysParm first init done! = %d\r\n",0);
    zw_siggen_waveform_gen(siggen_waveform_pattern);
    zw_siggen_freq_duty(siggen_frequency_0_1hz,siggen_duty_cycle_0_1_);
    zw_siggen_enable_(siggen_enable);
    zw_save_settings_(0x1000);
    HAL_FLASH_Write_Offset_0x96000(0x2400,&DAT_2001de34,0x18);
    DAT_2001ddef = 1;
  }
  global_settings = 1;
  if ((system_status_ == '\x01') || (system_status_ - 4U < 2)) {
    zw_scope_settings__0801ee0c(0xff);
  }
  settings_changed_flag_ = 1;
  DAT_2000a8c8 = timebase_index_2_5ns_30_10s;
  return;
}




void FUN_0801f238(void)

{
  zw_set_bits(&peripheral_gpioA_data,0x400);
  return;
}




void zw_dmm_side_menu(void)

{
  byte bVar1;
  undefined2 uStack_14;
  undefined2 uStack_12;
  byte *pbStack_c;
  undefined2 uStack_8;
  undefined2 uStack_6;
  
  zw_draw_rectangle_filled(0x118,8,0x28,0xcc,0);
  bVar1 = DAT_2001deb8 & 0xfd;
  if (bVar1 == 4) {
    zw_draw_rectangle_filled(0x11a,10,0x26,0x26,0x10);
  }
  else if (bVar1 == 5) {
    zw_draw_rectangle_filled(0x11a,0x5b,0x26,0x26,0x10);
  }
  else if (bVar1 == 8) {
    zw_draw_rectangle_filled(0x11a,0x83,0x26,0x27,0x10);
  }
  else if (bVar1 == 9) {
    zw_draw_rectangle_filled(0x11a,0xac,0x26,0x26,0x10);
  }
  else {
    zw_draw_rectangle_filled(0x11a,0x32,0x26,0x27,0x10);
  }
  uStack_8 = 1;
  uStack_6 = 0x20;
  uStack_14 = 0x11a;
  uStack_12 = 10;
  pbStack_c = image_dmm_side_menu;
  zw_draw_element(&uStack_14);
  zw_draw_line_horizontal(0x118,8,0x28,4);
  zw_draw_line_horizontal(0x118,9,0x28,4);
  zw_draw_line_horizontal(0x118,0x30,0x28,4);
  zw_draw_line_horizontal(0x118,0x31,0x28,4);
  zw_draw_line_horizontal(0x118,0x59,0x28,4);
  zw_draw_line_horizontal(0x118,0x5a,0x28,4);
  zw_draw_line_horizontal(0x118,0x81,0x28,4);
  zw_draw_line_horizontal(0x118,0x82,0x28,4);
  zw_draw_line_horizontal(0x118,0xaa,0x28,4);
  zw_draw_line_horizontal(0x118,0xab,0x28,4);
  zw_draw_line_horizontal(0x118,0xd2,0x28,4);
  zw_draw_line_horizontal(0x118,0xd3,0x28,4);
  zw_draw_line_vertical(0x118,8,0xcc,4);
  zw_draw_line_vertical(0x119,8,0xcc,4);
  return;
}




void FUN_0801f3cc(int param_1)

{
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,0x40,1,2);
  if (param_1 == 0) {
    zw_clear_bits(&peripheral_gpioA_data,0x40);
    return;
  }
  zw_set_bits(&peripheral_gpioA_data,0x40);
  return;
}




void FUN_0801f404(void)

{
  DAT_2001de58 = &peripheral_uart4_line_ctrl;
  DAT_2001de5c = 0x2580;
  DAT_2001de60 = 3;
  DAT_2001de6c = 0xc0;
  DAT_2001de64 = 0;
  DAT_2001de68 = 0;
  DAT_2001de70 = 0;
  HAL_UART_Init(&DAT_2001de58);
  HAL_UART_Receive_IT(&DAT_2001de58,&DAT_200045b8,0);
  return;
}




void FUN_0801f440(int param_1,int param_2)

{
  uint8_t local_10 [3];
  undefined1 uStack_d;
  undefined1 uStack_c;
  undefined1 uStack_b;
  undefined1 uStack_a;
  undefined1 uStack_9;
  undefined1 uStack_8;
  undefined1 uStack_7;
  
  local_10[0] = 0xaa;
  local_10[1] = 0x55;
  local_10[2] = param_1;
  uStack_c = 0;
  uStack_b = 0;
  uStack_a = 0;
  uStack_9 = 0;
  uStack_d = param_2;
  uStack_8 = param_1 + param_2 >> 8;
  uStack_7 = param_1 + param_2;
  HAL_UART_Transmit(&DAT_2001de58,local_10,10,1000);
  return;
}




void FUN_0801f490(int param_1)

{
  FUN_0802c1cc(0x1d);
  if (param_1 == 4) {
    DAT_200045a9 = 10;
    zw_clear_bits(&peripheral_gpioA_data,0x400);
  }
  else if (param_1 == 6) {
    DAT_200045a9 = 0xb;
    zw_clear_bits(&peripheral_gpioA_data,0x400);
  }
  else if (param_1 == 5) {
    DAT_200045a9 = 0xc;
    FUN_0801f238();
  }
  else if (param_1 == 7) {
    DAT_200045a9 = 0xd;
    FUN_0801f238();
  }
  else if (param_1 == 8) {
    DAT_200045a9 = 0x12;
    FUN_0801f238();
  }
  else if (param_1 == 9) {
    DAT_200045a9 = 0x10;
    FUN_0801f238();
  }
  else if (param_1 == 10) {
    DAT_200045a9 = 0x13;
    FUN_0801f238();
  }
  else if (param_1 == 0xb) {
    DAT_200045a9 = 0x11;
    FUN_0801f238();
  }
  else if (param_1 == 0) {
    DAT_200045a9 = 0x18;
    FUN_0801f238();
  }
  else if (param_1 == 2) {
    DAT_200045a9 = 0x15;
    FUN_0801f238();
    FUN_0802c1cc(0x31);
  }
  else if (param_1 == 1) {
    DAT_200045a9 = 0x16;
    FUN_0801f238();
  }
  else if (param_1 == 3) {
    DAT_200045a9 = 0x19;
    FUN_0801f238();
  }
  FUN_0801f440(5,DAT_200045a9);
  HAL_Delay(100);
  return;
}




void FUN_0801f584(void)

{
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,0x400,1,2);
  HAL_Delay(100);
  zw_clear_bits(&peripheral_gpioA_data,0x400);
  FUN_0801f404();
  DAT_2001deb8 = 4;
  zw_set_bits(&peripheral_gpioA_data,0x40);
  HAL_Delay(100);
  zw_timer_us(&DAT_200045f0,280000);
  FUN_0801f490(4);
  if (DAT_2001de0e == '\0') {
    DAT_2001de11 = 0;
  }
  return;
}




void zw_dmm_factory_calibration(int param_1)

{
  int iVar1;
  
  if (param_1 == 0x14) {
    if (2 < DAT_200045a4) goto LAB_0801f658;
    DAT_200045a4 = DAT_200045a4 + 1;
    zw_timer_us(&DAT_20004598,800000);
    printf_disabled_1("calib_keyCnt=%d\r\n",DAT_200045a4);
LAB_0801f66a:
    if (DAT_200045a4 == 0x58) {
LAB_0801f670:
      DAT_200045a4 = 5;
      DAT_200045b0 = 1;
      DAT_200045aa = 0;
      DAT_200045d9 = 0;
      FUN_0801f490(0);
      HAL_Delay(500);
      zw_draw_popup_message("Factory claib mode",0x12,1000000,0,1);
      return;
    }
  }
  else if (param_1 == 0xf) {
    if (DAT_200045a4 == 3) goto LAB_0801f670;
LAB_0801f658:
    if (DAT_200045a4 != 5) {
LAB_0801f65c:
      DAT_200045a4 = 0;
      printf_disabled_1("key_cnt0=%d\r\n",0);
      goto LAB_0801f66a;
    }
  }
  else if (param_1 == 0xe) {
    if (DAT_200045a4 != 2) goto LAB_0801f658;
    DAT_200045a4 = 99;
  }
  else if (DAT_200045a4 != 5) {
    if (param_1 == 0) {
      if (DAT_200045a4 == 0) goto LAB_0801f61a;
      iVar1 = FUN_080270a8(&DAT_20004598);
      if (iVar1 == 0) goto LAB_0801f66a;
    }
    goto LAB_0801f65c;
  }
LAB_0801f61a:
  if (DAT_200045b0 == '\0') {
    return;
  }
  if (DAT_200045d9 == 4) {
    HAL_Delay(500);
    HAL_Delay(500);
    FUN_0801f490(8);
    DAT_200045d9 = 5;
    zw_draw_popup_message("Claib: 1.0A",0xb,1000000,0,1);
  }
  else if (DAT_200045d9 < 5) {
    if (DAT_200045d9 == 1) {
      iVar1 = FUN_080270a8(&DAT_20004598);
      if (iVar1 != 0) {
        zw_draw_popup_message("Claib: 100mV",0xc,1000000,0,1);
        DAT_200045d9 = 2;
      }
    }
    else if (DAT_200045d9 == 0) {
      FUN_0801f440(2,0xa0);
      zw_draw_popup_message("Self-inspection",0xf,1000000,0,1);
      HAL_Delay(500);
      zw_timer_us(&DAT_20004598,38000000);
      DAT_200045d9 = 1;
    }
    else if (DAT_200045d9 == 2) {
      if (param_1 == 2) {
        FUN_0801f440(5,3);
        DAT_2001ddf5 = 1;
        DAT_200045d9 = 0xff;
        zw_timer_us(&DAT_20004598,12000000);
        goto LAB_0801f7ba;
      }
LAB_0801f642:
      if (param_1 == 0x13) {
        FUN_0801f440(5,1);
        DAT_200045d9 = 4;
        zw_draw_popup_message("Claib: temp",0xb,1000000,0,1);
        goto LAB_0801f64a;
      }
    }
    else if (DAT_200045d9 == 3) {
      if (param_1 != 2) goto LAB_0801f642;
LAB_0801f7ba:
      FUN_0801f440(5,3);
      goto LAB_0801f64a;
    }
  }
  else if (DAT_200045d9 == 6) {
    if (param_1 == 2) goto LAB_0801f7ba;
    if (param_1 == 0x13) {
      DAT_200045d9 = 7;
      goto LAB_0801f64a;
    }
  }
  else if (DAT_200045d9 < 6) {
    if (param_1 == 2) goto LAB_0801f7ba;
    if (param_1 == 0x13) {
      FUN_0801f490(9);
      DAT_200045d9 = 6;
      zw_draw_popup_message("Claib: 100mA",0xc,1000000,0,1);
      goto LAB_0801f64a;
    }
  }
  else {
    if (DAT_200045d9 == 7) {
      zw_draw_popup_message("Please restart!",0xf,1000000,0,1);
    }
    else if (DAT_200045d9 != 0xff) goto LAB_0801f646;
    iVar1 = FUN_080270a8(&DAT_20004598);
    if (iVar1 != 0) {
      if ((((DAT_200045a8 < 10) && (DAT_200045a7 < 10)) && (DAT_200045a6 < 10)) && (DAT_200045a5 < 10)) {
        zw_power_off();
      }
      HAL_Delay(3000);
    }
  }
LAB_0801f646:
  if (param_1 == 0) {
    return;
  }
LAB_0801f64a:
  HAL_Delay(200);
  return;
}




int FUN_0801f8ac(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  if ((DAT_2001de01 & 1) != 0) {
    return param_1;
  }
  if ((system_status_ != '\x01') && (system_status_ != '\a')) {
    return param_1;
  }
  if (DAT_2001de13 == '\0') {
    if (param_1 == 0x58) {
      if (DAT_2001de0c == '\0') {
LAB_0801f95a:
        DAT_2001de0e = 1;
        FUN_0801f490(DAT_2001deb8);
        DAT_2001de0c = 1;
        return 0;
      }
    }
    else {
LAB_0801f8e0:
      if (param_1 != 0x18) goto LAB_0801f8e4;
      if (DAT_2001de0e == '\0') {
        DAT_2001de0e = 1;
        FUN_0801f490(DAT_2001deb8);
        if ((DAT_2001ddc9 == '\0') && (settings_dmm_window_0_window_1_fullscreen != '\0')) {
          DAT_2001de0c = DAT_2001ddc9;
          return 0;
        }
        DAT_2001de0c = 1;
        return 0;
      }
    }
LAB_0801f97e:
    if (DAT_2001de0e == '\x01') {
      if (DAT_200045aa == '\0') {
        DAT_2001de11 = DAT_200045aa;
        DAT_2001de0e = DAT_200045aa;
        DAT_2001de0c = DAT_200045aa;
        DAT_200045fc = DAT_200045aa;
        FUN_0801f490(4);
        return 0;
      }
      goto LAB_0801f8e4;
    }
  }
  else {
    if (DAT_2001de0c != '\0') {
      if (param_1 != 0x58) goto LAB_0801f8e0;
      goto LAB_0801f97e;
    }
    if (((DAT_2001de0e != '\0') || (DAT_200045aa != '\0')) || (param_1 == 0x18)) {
      FUN_0801f490(4);
      zw_draw_popup_message("USB/DMM Conflict!",0x11,0x5dc,0,1);
      DAT_200045aa = 0;
      DAT_200045fc = 0;
      DAT_2001de0c = 0;
      DAT_2001de0e = 0;
      DAT_2001de11 = 0;
      return param_1;
    }
    if (param_1 == 0x58) goto LAB_0801f95a;
LAB_0801f8e4:
    if (param_1 == 0x17) {
      if (DAT_200045fc == '\0') {
        if (DAT_200045aa != '\0') {
          DAT_200045aa = DAT_200045fc;
          DAT_2001de01 = DAT_200045fc;
          DAT_2001de11 = DAT_200045fc;
          return 0;
        }
        DAT_200045aa = 1;
        DAT_2001de01 = 0x10;
        DAT_2001de11 = DAT_200045fc;
        DAT_2001de50 = DAT_2001deb8;
        return 0;
      }
    }
    else if (param_1 == 6) {
      if (DAT_2001de0e != '\0') {
        if ((DAT_2001de0c != '\0') && (DAT_200045aa == '\0')) {
          DAT_2001de11 = ~(DAT_2001de11 != '\0');
          return 0;
        }
        if (DAT_2001de11 != '\0') {
          return 6;
        }
      }
      if (DAT_200045aa == '\0') {
        return 6;
      }
      goto LAB_0801f91a;
    }
  }
  if ((DAT_2001de11 == '\0') || (DAT_2001de0e == '\0')) {
    if (DAT_200045aa == '\0') {
      return param_1;
    }
    if ((param_1 == 2) || (param_1 == 0x18)) goto LAB_0801f9d4;
  }
  else if (param_1 == 2) {
    if (DAT_2001deb8 == '\x04') {
      DAT_2001deb8 = 6;
      uVar1 = 6;
    }
    else {
      DAT_2001deb8 = 4;
      uVar1 = 4;
    }
    FUN_0801f490(uVar1);
    if (DAT_200045aa == '\0') {
      return 2;
    }
LAB_0801f9d4:
    DAT_2001deb8 = DAT_2001de50;
    DAT_200045aa = '\0';
    DAT_2001de0e = '\x01';
    DAT_2001de01 = 0;
    FUN_0801f490(DAT_2001de50);
  }
  else {
    if (param_1 == 10) {
      if (DAT_2001deb8 < 3) {
        uVar2 = DAT_2001deb8 + 1;
        uVar3 = uVar2 & 0xff;
        DAT_2001deb8 = uVar2;
      }
      else {
        DAT_2001deb8 = '\0';
        uVar3 = 0;
      }
    }
    else if (param_1 == 0x12) {
      if (DAT_2001deb8 == '\x05') {
        DAT_2001deb8 = '\a';
        uVar3 = 7;
      }
      else {
        DAT_2001deb8 = '\x05';
        uVar3 = 5;
      }
    }
    else if (param_1 == 8) {
      if (DAT_2001deb8 == '\b') {
        DAT_2001deb8 = '\n';
        uVar3 = 10;
      }
      else {
        DAT_2001deb8 = '\b';
        uVar3 = 8;
      }
    }
    else {
      if (param_1 != 0x10) {
        return param_1;
      }
      if (DAT_2001deb8 == '\t') {
        DAT_2001deb8 = '\v';
        uVar3 = 0xb;
      }
      else {
        DAT_2001deb8 = '\t';
        uVar3 = 9;
      }
    }
    FUN_0801f490(uVar3);
    if (DAT_200045aa == '\0') {
      return param_1;
    }
  }
  if (param_1 == 4) {
    DAT_2001de50 = DAT_2001de50 + '\x01';
  }
  else if (param_1 == 3) {
    DAT_2001de50 = DAT_2001de50 + -1;
  }
  else if (param_1 == 0xb) {
    DAT_2001de50 = DAT_2001de50 + -4;
  }
  else if (param_1 == 0x13) {
    DAT_2001de50 = DAT_2001de50 + '\x04';
  }
LAB_0801f91a:
  if (DAT_2001de50 < '\0') {
    DAT_2001de50 = DAT_2001de50 + '\f';
  }
  else if ('\v' < DAT_2001de50) {
    DAT_2001de50 = DAT_2001de50 + -0xc;
  }
  if (param_1 != 0) {
    DAT_200045b1 = 0;
  }
  return 0;
}




void zw_dmm_calib_mode(int param_1)

{
  if (((param_1 != 0) && (DAT_2001de0e != '\0')) && (DAT_2001de0c != '\0')) {
    if (DAT_200045a4 == 'c') {
      DAT_200045a4 = '\x05';
      DAT_200045fc = '\x01';
      DAT_200045aa = 0;
      zw_draw_popup_message("DMM claib mode",0xe,1000000,0,1);
    }
    else if (DAT_200045fc != '\0') {
      if (param_1 == 2) {
        if (DAT_200045fc == '\x01') {
          DAT_200045a4 = '\0';
          DAT_200045fc = '\0';
          if ((DAT_2001deb8 - 4U < 2) || (DAT_2001deb8 - 8U < 2)) {
            (&DAT_2001de34)[DAT_2001deb8 + 2] = (&DAT_2001de34)[DAT_2001deb8];
          }
          HAL_FLASH_Write_Offset_0x96000(0x2400,&DAT_2001de34,0x18);
          zw_draw_popup_message("Save!",5,1000,0,1);
        }
      }
      else if (param_1 == 10) {
        DAT_200045a4 = '\0';
        DAT_200045fc = '\0';
        (&DAT_2001de34)[DAT_2001deb8] = 5000;
        HAL_FLASH_Write_Offset_0x96000(0x2400,&DAT_2001de34,0x18);
        zw_draw_popup_message("SAVE!",5,1000,0,1);
      }
      else if (param_1 == 1) {
        DAT_200045a4 = '\0';
        DAT_200045fc = '\0';
        (&DAT_2001de34)[DAT_2001deb8] = 5000;
        zw_draw_popup_message("NOT SAVE!",9,1000,0,1);
      }
      else if (param_1 == 0xb) {
        (&DAT_2001de34)[DAT_2001deb8] = (&DAT_2001de34)[DAT_2001deb8] + 1;
      }
      else if (param_1 == 0x13) {
        (&DAT_2001de34)[DAT_2001deb8] = (&DAT_2001de34)[DAT_2001deb8] + -1;
      }
      else if (param_1 == 3) {
        (&DAT_2001de34)[DAT_2001deb8] = (&DAT_2001de34)[DAT_2001deb8] + 10;
      }
      else if (param_1 == 4) {
        (&DAT_2001de34)[DAT_2001deb8] = (&DAT_2001de34)[DAT_2001deb8] + -10;
      }
    }
  }
  return;
}




undefined4 FUN_0801fd34(undefined4 param_1)

{
  if (false) {
switchD_0801fd40_caseD_1:
    param_1 = 0;
  }
  else {
    switch(param_1) {
    case 0:
      param_1 = 0xff;
      break;
    default:
      goto switchD_0801fd40_caseD_1;
    case 6:
      param_1 = 1;
      break;
    case 7:
      break;
    case 0x31:
    case 0x50:
      return 0x72;
    case 0x38:
      param_1 = 0x4c;
      break;
    case 0x39:
      param_1 = 0x43;
      break;
    case 0x4f:
      param_1 = 3;
      break;
    case 0x5b:
      param_1 = 2;
      break;
    case 0x66:
      param_1 = 4;
      break;
    case 0x6d:
      param_1 = 5;
      break;
    case 0x6f:
      param_1 = 9;
      break;
    case 0x79:
      param_1 = 0x45;
      break;
    case 0x7d:
      param_1 = 6;
      break;
    case 0x7f:
      param_1 = 8;
    }
  }
  return param_1;
}




void FUN_0801fd80(int param_1)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  byte *pbVar8;
  uint uVar9;
  byte bVar10;
  undefined1 *puVar11;
  int iVar12;
  uint uVar13;
  undefined1 local_28;
  undefined1 uStack_27;
  undefined1 local_26;
  byte local_25;
  
  pbVar8 = &local_25;
  puVar11 = &DAT_200045af;
  pbVar7 = param_1 + 2;
  iVar12 = 4;
  do {
    *puVar11 = 0;
    bVar1 = *pbVar7;
    *pbVar8 = 0;
    if (false) {
      *pbVar8 = 1;
    }
    if ((bVar1 & 0x40) != 0) {
      *pbVar8 = *pbVar8 | 0x20;
    }
    if ((bVar1 & 0x20) != 0) {
      *pbVar8 = *pbVar8 | 0x10;
    }
    if ((bVar1 & 0x10) != 0) {
      *puVar11 = 1;
    }
    bVar1 = pbVar7[1];
    if ((bVar1 & 8) != 0) {
      *pbVar8 = *pbVar8 | 2;
    }
    if ((bVar1 & 4) != 0) {
      *pbVar8 = *pbVar8 | 0x40;
    }
    if ((bVar1 & 2) != 0) {
      *pbVar8 = *pbVar8 | 4;
    }
    if ((bVar1 & 1) != 0) {
      *pbVar8 = *pbVar8 | 8;
    }
    pbVar8 = pbVar8 + -1;
    puVar11 = puVar11 + -1;
    pbVar7 = pbVar7 + 1;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  bVar1 = *(param_1 + 7);
  DAT_200045ff = 0;
  DAT_20004600 = '\0';
  DAT_200045fd = '\0';
  DAT_200045fe = 0;
  if ((bVar1 & 0x20) == 0) {
    bVar10 = bVar1 & 0x10;
    if ((bVar1 & 0x10) == 0) {
      bVar2 = *(param_1 + 8);
      if ((bVar2 & 2) == 0) {
        bVar10 = bVar2 & 1;
        if ((bVar2 & 1) != 0) {
          DAT_200045fd = '\x01';
          bVar10 = bVar2 & 2;
        }
      }
      else {
        DAT_20004600 = '\x01';
      }
    }
    else {
      DAT_200045fe = 1;
      bVar10 = 1;
    }
  }
  else {
    DAT_200045ff = 1;
    bVar10 = 0;
  }
  DAT_200045b2 = 0;
  DAT_200045b3 = 0;
  DAT_200045b5 = '\0';
  DAT_200045b6 = 0;
  DAT_200045b4 = '\0';
  bVar2 = *(param_1 + 6);
  if ((bVar2 & 0x40) == 0) {
    if ((bVar2 & 0x20) == 0) {
      if ((bVar2 & 0x10) == 0) {
        if ((bVar1 & 4) == 0) {
          if ((bVar1 & 1) != 0) {
            DAT_200045b4 = '\x01';
          }
        }
        else {
          DAT_200045b3 = 1;
        }
      }
      else {
        DAT_200045b6 = 1;
      }
    }
    else {
      DAT_200045b5 = '\x01';
    }
  }
  else {
    DAT_200045b2 = 1;
  }
  uVar3 = FUN_0801fd34(local_25);
  DAT_200045a8 = uVar3;
  uVar4 = FUN_0801fd34(local_26);
  DAT_200045a7 = uVar4;
  uVar5 = FUN_0801fd34(uStack_27);
  DAT_200045a6 = uVar5;
  uVar6 = FUN_0801fd34(local_28);
  DAT_200045a5 = uVar6;
  DAT_2001de4c = uVar4 * 100 + uVar3 * 1000 + uVar5 * 10 + uVar6;
  if ((bVar10 != 0) && (DAT_200045b5 != '\0')) {
    if ((DAT_200045ad == '\0') || (4999 < DAT_2001de4c)) {
      if (DAT_200045ae != '\0') {
        if (0x9f < DAT_2001de4c) {
          DAT_2001de4c = (DAT_2001de4c * 0x7d) / 100;
        }
        goto LAB_080200c4;
      }
    }
    else {
      DAT_2001de4c = (DAT_2001de4c * 0x7d) / 100;
      if (DAT_200045ae != '\0') {
LAB_080200c4:
        if (DAT_2001de4c < 0x50) {
          DAT_2001de4c = 0;
        }
      }
    }
  }
  uVar13 = DAT_2001deb8;
  DAT_2001de4c = ~(((&DAT_2001de34)[uVar13] * DAT_2001de4c) % 5000 < 0x9c4) + ((&DAT_2001de34)[uVar13] * DAT_2001de4c) / 5000;
  if (uVar13 == 6) {
    if ((((DAT_20004600 != '\0') && (DAT_200045b4 == '\0')) && (DAT_200045ae != '\0')) && (DAT_2001de4c < 0x15)) {
LAB_08020148:
      DAT_2001de4c = 0;
    }
    goto LAB_0801ff40;
  }
  if (uVar13 == 7) {
    if ((DAT_20004600 == '\0') || (DAT_200045b4 == '\0')) goto LAB_0801ff40;
    if (DAT_200045ad == '\0') {
      if (DAT_200045ac != '\0') goto LAB_0801ff4c;
      goto LAB_08020170;
    }
    DAT_2001de4c = DAT_2001de4c + -0x6e;
    if (DAT_2001de4c < 0) {
LAB_08020208:
      DAT_2001de4c = 0;
    }
LAB_08020018:
    if (DAT_200045ac != '\0') goto LAB_0801ff4c;
LAB_08020122:
    DAT_2001de54 = DAT_2001de4c / 100;
LAB_0801ff56:
    DAT_20004594 = 0;
    uVar9 = uVar13 & 0xfffffffd;
    if (uVar9 == 4) {
      if (((DAT_20004600 == '\0') || (DAT_200045b4 != '\0')) || (DAT_2001de54 < 0x65)) {
LAB_080200da:
        if (uVar13 != 0xb) goto LAB_0801ff84;
        goto LAB_080200e0;
      }
    }
    else {
      if (uVar9 != 5) {
        if (uVar9 != 8) {
          if (uVar13 != 9) goto LAB_080200da;
          goto LAB_080200e0;
        }
        if (DAT_200045fd == '\0') goto LAB_0801ff84;
        if (DAT_200045b4 == '\0') {
          if (DAT_2001de54 < 3) goto LAB_0801ff84;
          goto LAB_08020162;
        }
        if (uVar13 != 9) goto LAB_0801ff84;
        goto LAB_080200f0;
      }
      if (DAT_20004600 == '\0') goto LAB_0801ff84;
      if ((DAT_200045b4 == '\0') || (DAT_2001de54 < 0x1f5)) goto LAB_080200da;
    }
  }
  else {
    if (uVar13 == 10) {
      if (((DAT_200045fd != '\0') && (DAT_200045b4 == '\0')) && ((DAT_200045ae != '\0' && (DAT_2001de4c < 0x1c)))) goto LAB_08020148;
LAB_0801ff40:
      if (DAT_200045ac == '\0') {
        if (DAT_200045ad != '\0') goto LAB_08020122;
LAB_08020170:
        if (DAT_200045ae != '\0') {
LAB_08020178:
          DAT_2001de54 = DAT_2001de4c / 1000;
        }
      }
      else {
LAB_0801ff4c:
        DAT_2001de54 = DAT_2001de4c / 10;
      }
      goto LAB_0801ff56;
    }
    if (((uVar13 != 0xb) || (DAT_200045fd == '\0')) || (DAT_200045b4 == '\0')) goto LAB_0801ff40;
    if (DAT_200045ad != '\0') {
      if (DAT_2001de4c < 0x24) goto LAB_08020208;
      goto LAB_08020018;
    }
    if (DAT_200045ac != '\0') goto LAB_0801ff4c;
    if (DAT_200045ae != '\0') goto LAB_08020178;
LAB_080200e0:
    DAT_20004594 = 0;
    if ((DAT_200045fd == '\0') || (DAT_200045b4 == '\0')) goto LAB_0801ff84;
LAB_080200f0:
    DAT_20004594 = 0;
    if (DAT_2001de54 < 0x1f5) goto LAB_0801ff84;
  }
LAB_08020162:
  DAT_20004594 = 1;
LAB_0801ff84:
  if ((((9 < uVar3) || (9 < uVar4)) || (9 < uVar5)) || (9 < uVar6)) {
    DAT_20004594 = 0;
  }
  return;
}




void zw_dmm_modes_(uint param_1)

{
  undefined2 uStack_30;
  undefined2 uStack_2e;
  byte *pbStack_28;
  undefined2 uStack_24;
  undefined2 uStack_22;
  
  zw_draw_rectangle_filled(9,0x61,0x12d,0x6e,0xe);
  zw_draw_rectangle_filled(9,0xcf,0x130,0x21,0);
  zw_draw_rectangle(10,0x62,0x12d,0x6d,0xd);
  zw_draw_line_vertical(0x55,0x62,0x6d,0xd);
  zw_draw_line_vertical(0xa0,0x62,0x6d,0xd);
  zw_draw_line_vertical(0xeb,0x62,0x6d,0xd);
  zw_draw_line_horizontal(10,0x86,300,0xd);
  zw_draw_line_horizontal(10,0xaa,300,0xd);
  uStack_30 = 0x18;
  uStack_2e = 0x6f;
  uStack_24 = 5;
  uStack_22 = 0xe;
  pbStack_28 = image_dmm_symbol_resistance_large;
  zw_draw_element(&uStack_30);
  uStack_30 = 0x6a;
  uStack_2e = 0x6a;
  pbStack_28 = image_dmm_symbol_continuity;
  zw_draw_element(&uStack_30);
  uStack_30 = 0xb4;
  uStack_2e = 0x6c;
  pbStack_28 = image_dmm_symbol_diode;
  zw_draw_element(&uStack_30);
  uStack_30 = 0x104;
  uStack_2e = 0x6c;
  pbStack_28 = image_dmm_symbol_capacitance;
  zw_draw_element(&uStack_30);
  uStack_24 = 5;
  uStack_2e = 0x89;
  pbStack_28 = image_dmm_symbol_V_DC;
  uStack_30 = 0x1b;
  zw_draw_element(&uStack_30);
  uStack_2e = 0x89;
  pbStack_28 = image_dmm_symbol_mV_DC;
  uStack_30 = 0x5b;
  zw_draw_element(&uStack_30);
  uStack_24 = 5;
  uStack_2e = 0x89;
  pbStack_28 = image_dmm_symbol_V_AC;
  uStack_30 = 0xb3;
  zw_draw_element(&uStack_30);
  uStack_2e = 0x89;
  pbStack_28 = image_dmm_symbol_mV_AC;
  uStack_30 = 0xf4;
  zw_draw_element(&uStack_30);
  uStack_24 = 6;
  pbStack_28 = image_dmm_symbol_A_DC;
  uStack_30 = 0x1b;
  uStack_2e = 0xad;
  zw_draw_element(&uStack_30);
  pbStack_28 = image_dmm_symbol_mA_DC;
  uStack_30 = 0x5b;
  uStack_2e = 0xad;
  zw_draw_element(&uStack_30);
  pbStack_28 = image_dmm_symbol_A_AC;
  uStack_30 = 0xb3;
  uStack_2e = 0xad;
  zw_draw_element(&uStack_30);
  pbStack_28 = image_dmm_symbol_mA_AC;
  uStack_30 = 0xf4;
  uStack_2e = 0xad;
  zw_draw_element(&uStack_30);
  uStack_24 = 0xb;
  uStack_22 = 0x20;
  uStack_30 = 0xbb;
  uStack_2e = 0xd3;
  pbStack_28 = image_dmm_symbol_jack;
  zw_draw_element(&uStack_30);
  DAT_200045b1 = DAT_200045b1 + 1;
  if (0x80 < DAT_200045b1) {
    DAT_200045b1 = 0;
  }
  uStack_24 = 2;
  uStack_22 = 0x20;
  if (((param_1 & 0xfd) == 8) && ((DAT_200045b1 & 0xf) < 8)) {
    uStack_30 = 0x1f;
    zw_draw_element(&uStack_30);
LAB_08020478:
    if (param_1 != 8) {
LAB_08020412:
      if (param_1 != 10) goto LAB_080204a0;
      goto LAB_08020418;
    }
    uStack_30 = 0x6f;
    pbStack_28 = image_dmm_symbol_jack_small;
    uStack_2e = 0xd6;
    zw_draw_element(&uStack_30);
LAB_080204ba:
    uStack_30 = 0x10a;
    uStack_2e = 0xd6;
    pbStack_28 = image_dmm_symbol_jack_small;
    zw_draw_element(&uStack_30);
  }
  else {
    if (param_1 != 9) {
      if (param_1 == 0xb) {
        if ((DAT_200045b1 & 0xf) < 8) goto LAB_08020544;
      }
      else if ((param_1 - 8 & 0xff) < 2) goto LAB_08020478;
      if ((DAT_200045b1 & 0xf) < 8) {
        uStack_30 = 0x107;
        zw_draw_element(&uStack_30);
      }
      goto LAB_08020412;
    }
    if ((DAT_200045b1 & 0xf) < 8) {
LAB_08020544:
      uStack_30 = 0x6c;
      zw_draw_element(&uStack_30);
      goto LAB_08020478;
    }
LAB_080204a0:
    uStack_30 = 0x22;
    pbStack_28 = image_dmm_symbol_jack_small;
    uStack_2e = 0xd6;
    zw_draw_element(&uStack_30);
    if (param_1 == 9) goto LAB_080204ba;
    if (param_1 == 0xb) goto LAB_080204ec;
LAB_08020418:
    uStack_30 = 0x6f;
    uStack_2e = 0xd6;
    pbStack_28 = image_dmm_symbol_jack_small;
    zw_draw_element(&uStack_30);
    if ((param_1 - 8 & 0xff) < 2) goto LAB_080204ba;
    if (param_1 == 0) {
      zw_draw_rectangle(10,0x62,0x4c,0x25,2);
      zw_draw_rectangle(9,0x61,0x4e,0x27,2);
      return;
    }
    if (param_1 == 1) {
      zw_draw_rectangle(0x55,0x62,0x4c,0x25,2);
      zw_draw_rectangle(0x54,0x61,0x4e,0x27,2);
      return;
    }
    if (param_1 == 2) {
      zw_draw_rectangle(0xa0,0x62,0x4c,0x25,2);
      zw_draw_rectangle(0x9f,0x61,0x4e,0x27,2);
      return;
    }
    if (param_1 == 3) {
      zw_draw_rectangle(0xeb,0x62,0x4c,0x25,2);
      zw_draw_rectangle(0xea,0x61,0x4e,0x27,2);
      return;
    }
    if (param_1 == 4) {
      zw_draw_rectangle(10,0x86,0x4c,0x25,2);
      zw_draw_rectangle(9,0x85,0x4e,0x27,2);
      return;
    }
  }
  if (param_1 == 5) {
    zw_draw_rectangle(0x55,0x86,0x4c,0x25,2);
    zw_draw_rectangle(0x54,0x85,0x4e,0x27,2);
  }
  else if (param_1 == 6) {
    zw_draw_rectangle(0xa0,0x86,0x4c,0x25,2);
    zw_draw_rectangle(0x9f,0x85,0x4e,0x27,2);
  }
  else if (param_1 == 7) {
    zw_draw_rectangle(0xeb,0x86,0x4c,0x25,2);
    zw_draw_rectangle(0xea,0x85,0x4e,0x27,2);
  }
  else if (param_1 == 8) {
    zw_draw_rectangle(10,0xaa,0x4c,0x25,2);
    zw_draw_rectangle(9,0xa9,0x4e,0x27,2);
  }
  else if (param_1 == 9) {
    zw_draw_rectangle(0x55,0xaa,0x4c,0x25,2);
    zw_draw_rectangle(0x54,0xa9,0x4e,0x27,2);
  }
  else if (param_1 == 10) {
    zw_draw_rectangle(0xa0,0xaa,0x4c,0x25,2);
    zw_draw_rectangle(0x9f,0xa9,0x4e,0x27,2);
  }
  else if (param_1 == 0xb) {
LAB_080204ec:
    zw_draw_rectangle(0xeb,0xaa,0x4c,0x25,2);
    zw_draw_rectangle(0xea,0xa9,0x4e,0x27,2);
    return;
  }
  return;
}




void FUN_080206c8(void)

{
  undefined4 uVar1;
  
  uVar1 = zw_dmm_chars_24x28(DAT_200045a8,0xc2,0x2c,5,0x20);
  if (DAT_200045ae != '\0') {
    uVar1 = zw_dmm_chars_24x28(0x2e,uVar1,0x2c,5,0x20);
  }
  uVar1 = zw_dmm_chars_24x28(DAT_200045a7,uVar1,0x2c,5,0x20);
  if (DAT_200045ad != '\0') {
    uVar1 = zw_dmm_chars_24x28(0x2e,uVar1,0x2c,5,0x20);
  }
  uVar1 = zw_dmm_chars_24x28(DAT_200045a6,uVar1,0x2c,5,0x20);
  if (DAT_200045ac != '\0') {
    uVar1 = zw_dmm_chars_24x28(0x2e,uVar1,0x2c,5,0x20);
  }
  zw_dmm_chars_24x28(DAT_200045a5,uVar1,0x2c,5,0x20);
  return;
}




void draw_DMM_window_values_(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = DAT_2001de4c;
  uVar3 = 5;
  if (DAT_20004594 == '\x01') {
    uVar3 = 0x13;
  }
  if (DAT_200045af != '\0') {
    zw_dmm_chars_24x28(0x2d,0xb3,0x2c,uVar3,0x20);
  }
  if ((((DAT_2001deb8 == '\x01') || (9 < DAT_200045a8)) || (9 < DAT_200045a7)) || ((9 < DAT_200045a6 || (9 < DAT_200045a5)))) {
    FUN_080206c8();
  }
  else {
    uVar2 = zw_dmm_chars_24x28(iVar1 / 1000 & 0xff,0xc2,0x2c,uVar3,0x20);
    if (DAT_200045ae != '\0') {
      uVar2 = zw_dmm_chars_24x28(0x2e,uVar2,0x2c,uVar3,0x20);
    }
    uVar2 = zw_dmm_chars_24x28((iVar1 % 1000) / 100 & 0xff,uVar2,0x2c,uVar3,0x20);
    if (DAT_200045ad != '\0') {
      uVar2 = zw_dmm_chars_24x28(0x2e,uVar2,0x2c,uVar3,0x20);
    }
    uVar2 = zw_dmm_chars_24x28((iVar1 % 100) / 10 & 0xff,uVar2,0x2c,uVar3,0x20);
    if (DAT_200045ac != '\0') {
      uVar2 = zw_dmm_chars_24x28(0x2e,uVar2,0x2c,uVar3,0x20);
    }
    zw_dmm_chars_24x28(iVar1 % 10 & 0xff,uVar2,0x2c,uVar3,0x20);
  }
  return;
}




void zw_dmm_window(void)

{
  undefined2 uStack_18;
  undefined2 uStack_16;
  byte *pbStack_10;
  undefined2 uStack_c;
  undefined2 uStack_a;
  
  uStack_c = 1;
  uStack_a = 0x20;
  uStack_18 = 0xc1;
  zw_draw_rectangle_filled(0xb4,0x13,0x81,0x42,0);
  zw_draw_rectangle(0xb4,0x13,0x81,0x42,4);
  zw_draw_rectangle_filled(0xb4,0x13,0x81,0xd,4);
  if (DAT_2001deb8 == '\x04') {
    zw_draw_string_small("DC-1000V",0xb9,0x13,8,1,0x20);
  }
  else if (DAT_2001deb8 == '\x05') {
    zw_draw_string_small("DC-600mV",0xb9,0x13,8,1,0x20);
  }
  else if (DAT_2001deb8 == '\x06') {
    zw_draw_string_small("AC-750V",0xb9,0x13,7,1,0x20);
  }
  else if (DAT_2001deb8 == '\a') {
    zw_draw_string_small("AC-600mV",0xb9,0x13,8,1,0x20);
  }
  else if (DAT_2001deb8 == '\b') {
    zw_draw_string_small("DC-10A",0xb9,0x13,6,1,0x20);
  }
  else if (DAT_2001deb8 == '\t') {
    zw_draw_string_small("DC-600mA",0xb9,0x13,8,1,0x20);
  }
  else if (DAT_2001deb8 == '\n') {
    zw_draw_string_small("AC-10A",0xb9,0x13,6,1,0x20);
  }
  else if (DAT_2001deb8 == '\v') {
    zw_draw_string_small("AC-600mA",0xb9,0x13,8,1,0x20);
  }
  else if (DAT_2001deb8 == '\0') {
    uStack_16 = 0x16;
    pbStack_10 = image_dmm_symbol_resistance_small;
    zw_draw_element(&uStack_18);
  }
  else if (DAT_2001deb8 == '\x02') {
    uStack_16 = 0x15;
    pbStack_10 = image_dmm_symbol_diode_small;
    zw_draw_element(&uStack_18);
  }
  else if (DAT_2001deb8 == '\x01') {
    uStack_16 = 0x15;
    pbStack_10 = image_dmm_symbol_continuity_small;
    zw_draw_element(&uStack_18);
  }
  else if (DAT_2001deb8 == '\x03') {
    uStack_16 = 0x15;
    pbStack_10 = image_dmm_symbol_capacitance_small;
    zw_draw_element(&uStack_18);
  }
  uStack_c = 0x13;
  if (DAT_20004594 != '\x01') {
    uStack_c = 5;
  }
  uStack_a = 0x20;
  if (DAT_200045ff != '\0') {
    uStack_18 = 0x11d;
    uStack_16 = 0x2d;
    if (DAT_200045b2 == '\0') {
      if (DAT_200045b3 != '\0') {
        pbStack_10 = image_dmm_M_small;
        zw_draw_element(&uStack_18);
      }
    }
    else {
      pbStack_10 = image_dmm_K_small;
      zw_draw_element(&uStack_18);
    }
    uStack_18 = 0x125;
    pbStack_10 = image_dmm_ohm_small;
    zw_draw_element(&uStack_18);
  }
  uStack_18 = 0x11e;
  uStack_16 = 0x40;
  if (DAT_20004600 == '\0') {
    if (DAT_200045fd != '\0') {
      if (DAT_200045b4 != '\0') {
        pbStack_10 = image_dmm_symbol_m_small;
        zw_draw_element(&uStack_18);
      }
      uStack_18 = 0x128;
      pbStack_10 = image_dmm_A_small;
      zw_draw_element(&uStack_18);
      draw_DMM_window_values_();
      return;
    }
    if (DAT_200045fe != '\0') {
      if (DAT_200045b6 == '\0') {
        if (DAT_200045b5 == '\0') {
          if (DAT_200045b4 != '\0') {
            pbStack_10 = image_dmm_symbol_m_small;
            zw_draw_element(&uStack_18);
          }
        }
        else {
          pbStack_10 = image_dmm_symbol_n_small;
          zw_draw_element(&uStack_18);
        }
      }
      else {
        pbStack_10 = image_dmm_symbol_u_small;
        zw_draw_element(&uStack_18);
      }
      uStack_18 = 0x128;
      pbStack_10 = image_dmm_F_small;
      zw_draw_element(&uStack_18);
      draw_DMM_window_values_();
      return;
    }
  }
  else {
    if (DAT_200045b4 != '\0') {
      pbStack_10 = image_dmm_symbol_m_small;
      zw_draw_element(&uStack_18);
    }
    uStack_18 = 0x128;
    pbStack_10 = image_dmm_V_small;
    zw_draw_element(&uStack_18);
  }
  draw_DMM_window_values_();
  return;
}




void FUN_08020be8(void)

{
  undefined4 uVar1;
  uint uVar2;
  byte bVar3;
  
  uVar1 = zw_dmm_chars_40x81(DAT_200045a8,0x41,0x50,5,0x20);
  uVar2 = DAT_200045d8;
  DAT_200045d8 = DAT_200045d8 + 1;
  if (DAT_200045a8 < 10) {
    bVar3 = DAT_200045a8 + 0x30;
  }
  else {
    bVar3 = DAT_200045a8;
    if (DAT_200045a8 == 0xff) {
      bVar3 = 0x20;
    }
  }
  (&DAT_200045dc)[uVar2] = bVar3;
  if (DAT_200045ae != '\0') {
    uVar1 = zw_dmm_chars_40x81(0x2e,uVar1,0x50,5,0x20);
    uVar2 = DAT_200045d8;
    DAT_200045d8 = DAT_200045d8 + 1;
    (&DAT_200045dc)[uVar2] = 0x2e;
  }
  uVar1 = zw_dmm_chars_40x81(DAT_200045a7,uVar1,0x50,5,0x20);
  uVar2 = DAT_200045d8;
  DAT_200045d8 = DAT_200045d8 + 1;
  if (DAT_200045a7 < 10) {
    (&DAT_200045dc)[uVar2] = DAT_200045a7 + 0x30;
  }
  else {
    bVar3 = DAT_200045a7;
    if (DAT_200045a7 == 0xff) {
      bVar3 = 0x20;
    }
    (&DAT_200045dc)[uVar2] = bVar3;
  }
  if (DAT_200045ad != '\0') {
    uVar1 = zw_dmm_chars_40x81(0x2e,uVar1,0x50,5,0x20);
    uVar2 = DAT_200045d8;
    DAT_200045d8 = DAT_200045d8 + 1;
    (&DAT_200045dc)[uVar2] = 0x2e;
  }
  uVar1 = zw_dmm_chars_40x81(DAT_200045a6,uVar1,0x50,5,0x20);
  uVar2 = DAT_200045d8;
  DAT_200045d8 = DAT_200045d8 + 1;
  if (DAT_200045a6 < 10) {
    (&DAT_200045dc)[uVar2] = DAT_200045a6 + 0x30;
  }
  else {
    bVar3 = DAT_200045a6;
    if (DAT_200045a6 == 0xff) {
      bVar3 = 0x20;
    }
    (&DAT_200045dc)[uVar2] = bVar3;
  }
  if (DAT_200045ac != '\0') {
    uVar1 = zw_dmm_chars_40x81(0x2e,uVar1,0x50,5,0x20);
    uVar2 = DAT_200045d8;
    DAT_200045d8 = DAT_200045d8 + 1;
    (&DAT_200045dc)[uVar2] = 0x2e;
  }
  zw_dmm_chars_40x81(DAT_200045a5,uVar1,0x50,5,0x20);
  uVar2 = DAT_200045d8;
  DAT_200045d8 = DAT_200045d8 + 1;
  if (9 < DAT_200045a5) {
    bVar3 = DAT_200045a5;
    if (DAT_200045a5 == 0xff) {
      bVar3 = 0x20;
    }
    (&DAT_200045dc)[uVar2] = bVar3;
    return;
  }
  (&DAT_200045dc)[uVar2] = DAT_200045a5 + 0x30;
  return;
}




void FUN_08020d5c(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  
  iVar1 = DAT_2001de4c;
  uVar3 = 5;
  if (DAT_20004594 == '\x01') {
    uVar3 = 0x13;
  }
  if (DAT_200045af != '\0') {
    zw_dmm_chars_40x81(0x2d,0x19,0x50,uVar3,0x20);
    uVar4 = DAT_200045d8;
    DAT_200045d8 = DAT_200045d8 + 1;
    (&DAT_200045dc)[uVar4] = 0x2d;
  }
  if ((((DAT_2001deb8 != '\x01') && (DAT_200045a8 < 10)) && (DAT_200045a7 < 10)) && ((DAT_200045a6 < 10 && (DAT_200045a5 < 10)))) {
    uVar2 = zw_dmm_chars_40x81(iVar1 / 1000 & 0xff,0x41,0x50,uVar3,0x20);
    uVar4 = DAT_200045d8;
    DAT_200045d8 = DAT_200045d8 + 1;
    (&DAT_200045dc)[uVar4] = iVar1 / 1000 + '0';
    if (DAT_200045ae != '\0') {
      uVar2 = zw_dmm_chars_40x81(0x2e,uVar2,0x50,uVar3,0x20);
      uVar4 = DAT_200045d8;
      DAT_200045d8 = DAT_200045d8 + 1;
      (&DAT_200045dc)[uVar4] = 0x2e;
    }
    uVar5 = (iVar1 % 1000) / 100;
    uVar2 = zw_dmm_chars_40x81(uVar5 & 0xff,uVar2,0x50,uVar3,0x20);
    uVar4 = DAT_200045d8;
    DAT_200045d8 = DAT_200045d8 + 1;
    (&DAT_200045dc)[uVar4] = uVar5 + '0';
    if (DAT_200045ad != '\0') {
      uVar2 = zw_dmm_chars_40x81(0x2e,uVar2,0x50,uVar3,0x20);
      uVar4 = DAT_200045d8;
      DAT_200045d8 = DAT_200045d8 + 1;
      (&DAT_200045dc)[uVar4] = 0x2e;
    }
    uVar5 = (iVar1 % 100) / 10;
    uVar2 = zw_dmm_chars_40x81(uVar5 & 0xff,uVar2,0x50,uVar3,0x20);
    uVar4 = DAT_200045d8;
    DAT_200045d8 = DAT_200045d8 + 1;
    (&DAT_200045dc)[uVar4] = uVar5 + '0';
    if (DAT_200045ac != '\0') {
      uVar2 = zw_dmm_chars_40x81(0x2e,uVar2,0x50,uVar3,0x20);
      uVar4 = DAT_200045d8;
      DAT_200045d8 = DAT_200045d8 + 1;
      (&DAT_200045dc)[uVar4] = 0x2e;
    }
    zw_dmm_chars_40x81(iVar1 % 10 & 0xff,uVar2,0x50,uVar3,0x20);
    uVar4 = DAT_200045d8;
    DAT_200045d8 = DAT_200045d8 + 1;
    (&DAT_200045dc)[uVar4] = iVar1 % 10 + '0';
    return;
  }
  FUN_08020be8();
  return;
}




void zw_dmm_fullscreen(void)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  short asStack_20 [4];
  byte *pbStack_18;
  undefined2 uStack_14;
  undefined2 uStack_12;
  
  uStack_14 = 1;
  uStack_12 = 0x20;
  asStack_20[0] = 0x6a;
  asStack_20[1] = 9;
  pbStack_18 = image_dmm_label_digital_multimeter;
  zw_draw_element(asStack_20);
  zw_draw_line_horizontal(0,0x1e,0x140,8);
  zw_draw_line_horizontal(0,0x1f,0x140,8);
  DAT_200045d8 = 0;
  FUN_08020d5c();
  asStack_20[0] = 0x15;
  asStack_20[1] = 0x2a;
  if (DAT_2001deb8 - 4U < 2) {
    if (DAT_2001deb8 == '\x05') {
      asStack_20[0] = 4;
      pbStack_18 = image_dmm_mV_large;
    }
    else {
      pbStack_18 = image_dmm_V_large;
    }
    zw_draw_element(asStack_20);
    asStack_20[0] = 0x27;
    asStack_20[1] = 0x30;
    pbStack_18 = image_dmm_DC_large;
    zw_draw_element(asStack_20);
    if (DAT_2001deb8 == '\x04') {
      zw_draw_string_small("Max 1000V",0x50,0x2d,9,1,0x20);
      goto LAB_08020fc8;
    }
  }
  else {
    if (1 < DAT_2001deb8 - 6U) {
      if (DAT_2001deb8 - 8U < 2) {
        if (DAT_2001deb8 == '\t') {
          asStack_20[0] = 4;
          pbStack_18 = image_dmm_mA_large;
        }
        else {
          pbStack_18 = image_dmm_A_large;
        }
        zw_draw_element(asStack_20);
        asStack_20[0] = 0x27;
        asStack_20[1] = 0x30;
        pbStack_18 = image_dmm_DC_large;
        zw_draw_element(asStack_20);
        bVar3 = DAT_2001deb8 != '\b';
      }
      else {
        if (1 < DAT_2001deb8 - 10U) goto LAB_08020fc8;
        if (DAT_2001deb8 == '\v') {
          asStack_20[0] = 4;
          pbStack_18 = image_dmm_mA_large;
        }
        else {
          pbStack_18 = image_dmm_A_large;
        }
        zw_draw_element(asStack_20);
        asStack_20[0] = 0x27;
        asStack_20[1] = 0x30;
        pbStack_18 = image_dmm_AC_large;
        zw_draw_element(asStack_20);
        bVar3 = DAT_2001deb8 != '\n';
      }
      if (bVar3) {
        zw_draw_string_small("Max 600mA",0x50,0x2d,9,1,0x20);
      }
      else {
        zw_draw_string_small("Max 10A",0x50,0x2d,7,1,0x20);
      }
      goto LAB_08020fc8;
    }
    if (DAT_2001deb8 == '\a') {
      asStack_20[0] = 4;
      pbStack_18 = image_dmm_mV_large;
    }
    else {
      pbStack_18 = image_dmm_V_large;
    }
    zw_draw_element(asStack_20);
    asStack_20[0] = 0x27;
    asStack_20[1] = 0x30;
    pbStack_18 = image_dmm_AC_large;
    zw_draw_element(asStack_20);
    if (DAT_2001deb8 == '\x06') {
      zw_draw_string_small("Max 750V",0x50,0x2d,8,1,0x20);
      goto LAB_08020fc8;
    }
  }
  zw_draw_string_small("Max 600mV",0x50,0x2d,9,1,0x20);
LAB_08020fc8:
  asStack_20[0] = 0x1e;
  asStack_20[1] = 0x28;
  if (DAT_2001deb8 == '\0') {
    pbStack_18 = image_dmm_Ohm_large;
    zw_draw_element(asStack_20);
  }
  else if (DAT_2001deb8 == '\x02') {
    pbStack_18 = image_dmm_symbol_diode;
    zw_draw_element(asStack_20);
  }
  else if (DAT_2001deb8 == '\x01') {
    pbStack_18 = image_dmm_symbol_continuity;
    zw_draw_element(asStack_20);
  }
  else if (DAT_2001deb8 == '\x03') {
    pbStack_18 = image_dmm_symbol_capacitance;
    zw_draw_element(asStack_20);
  }
  uStack_14 = 5;
  if (DAT_20004594 == '\x01') {
    uStack_14 = 0x13;
  }
  uStack_12 = 0x20;
  if (DAT_200045ff != '\0') {
    asStack_20[0] = 0xf4;
    if (DAT_2001de11 == '\0') {
      asStack_20[0] = 0x10e;
    }
    asStack_20[1] = 0x37;
    if (DAT_200045b2 == '\0') {
      if (DAT_200045b3 != '\0') {
        pbStack_18 = image_dmm_M_large;
        zw_draw_element(asStack_20);
        uVar2 = DAT_200045d8;
        DAT_200045d8 = DAT_200045d8 + 1;
        (&DAT_200045dc)[uVar2] = 0x4d;
      }
    }
    else {
      pbStack_18 = image_dmm_K_large;
      zw_draw_element(asStack_20);
      uVar2 = DAT_200045d8;
      DAT_200045d8 = DAT_200045d8 + 1;
      (&DAT_200045dc)[uVar2] = 0x4b;
    }
    asStack_20[0] = asStack_20[0] + 0x11;
    pbStack_18 = image_dmm_Ohm_large;
    zw_draw_element(asStack_20);
    uVar2 = DAT_200045d8;
    DAT_200045d8 = DAT_200045d8 + 1;
    (&DAT_200045dc)[uVar2] = 0x52;
  }
  asStack_20[0] = 0xf2;
  if (DAT_2001de11 == '\0') {
    asStack_20[0] = 0x10e;
  }
  asStack_20[1] = 0xa8;
  if (DAT_20004600 == '\0') {
    if (DAT_200045fd == '\0') {
      if (DAT_200045fe != '\0') {
        if (DAT_200045b6 == '\0') {
          if (DAT_200045b5 == '\0') {
            if (DAT_200045b4 != '\0') {
              pbStack_18 = image_dmm_m_large;
              zw_draw_element(asStack_20);
              uVar2 = DAT_200045d8;
              DAT_200045d8 = DAT_200045d8 + 1;
              (&DAT_200045dc)[uVar2] = 0x6d;
            }
          }
          else {
            pbStack_18 = image_dmm_n_large;
            zw_draw_element(asStack_20);
            uVar2 = DAT_200045d8;
            DAT_200045d8 = DAT_200045d8 + 1;
            (&DAT_200045dc)[uVar2] = 0x6e;
          }
        }
        else {
          pbStack_18 = image_dmm_u_large;
          zw_draw_element(asStack_20);
          uVar2 = DAT_200045d8;
          DAT_200045d8 = DAT_200045d8 + 1;
          (&DAT_200045dc)[uVar2] = 0x75;
        }
        asStack_20[0] = asStack_20[0] + 0x12;
        pbStack_18 = image_dmm_F_large;
        zw_draw_element(asStack_20);
        uVar2 = DAT_200045d8;
        DAT_200045d8 = DAT_200045d8 + 1;
        (&DAT_200045dc)[uVar2] = 0x46;
      }
    }
    else {
      if (DAT_200045b4 != '\0') {
        pbStack_18 = image_dmm_m_large;
        zw_draw_element(asStack_20);
        uVar2 = DAT_200045d8;
        DAT_200045d8 = DAT_200045d8 + 1;
        (&DAT_200045dc)[uVar2] = 0x6d;
      }
      asStack_20[0] = asStack_20[0] + 0x12;
      pbStack_18 = image_dmm_A_large;
      zw_draw_element(asStack_20);
      uVar2 = DAT_200045d8;
      DAT_200045d8 = DAT_200045d8 + 1;
      (&DAT_200045dc)[uVar2] = 0x41;
    }
  }
  else {
    if (DAT_200045b4 != '\0') {
      pbStack_18 = image_dmm_m_large;
      zw_draw_element(asStack_20);
      uVar2 = DAT_200045d8;
      DAT_200045d8 = DAT_200045d8 + 1;
      (&DAT_200045dc)[uVar2] = 0x6d;
    }
    asStack_20[0] = asStack_20[0] + 0x12;
    pbStack_18 = image_dmm_V_large;
    zw_draw_element(asStack_20);
    uVar2 = DAT_200045d8;
    DAT_200045d8 = DAT_200045d8 + 1;
    (&DAT_200045dc)[uVar2] = 0x56;
  }
  iVar1 = FUN_080270a8(&DAT_200045f0);
  if (iVar1 != 0) {
    if (DAT_200045d8 != 0) {
      uVar2 = 0;
      do {
        putchar((&DAT_200045dc)[uVar2]);
        uVar2 = uVar2 + 1 & 0xff;
      } while (uVar2 < DAT_200045d8);
    }
    puts("\r");
  }
  return;
}




void zw_dmm_setup_(void)

{
  if (DAT_200045aa != '\0') {
    zw_dmm_modes_(DAT_2001de50);
  }
  if (((DAT_2001de0e != '\0') && ((DAT_2001de01 & 1) == 0)) && (system_status_ != '\x05')) {
    if ((DAT_2001de98 == 'Z') && (DAT_2001de99 == -0x5b)) {
      FUN_0801fd80();
    }
    if (((DAT_2001de0c == '\0') && (DAT_200045aa == '\0')) && (DAT_2001de0e != '\0')) {
      zw_dmm_window();
      return;
    }
  }
  return;
}




void zw_dmm_init_(undefined4 param_1)

{
  byte bVar1;
  undefined2 local_20;
  undefined2 uStack_1e;
  byte *pbStack_18;
  undefined2 uStack_14;
  undefined2 uStack_12;
  
  if (DAT_200045aa != '\0') {
    zw_dmm_modes_(DAT_2001de50);
    zw_draw_flush_offscreen();
    return;
  }
  if (DAT_2001de0e == '\0') {
    return;
  }
  memset(framebuffer_,0,76800);
  FUN_080254c0();
  FUN_08029f44();
  if ((DAT_2001de98 == 'Z') && (DAT_2001de99 == -0x5b)) {
    FUN_0801fd80();
  }
  if (DAT_200045aa == '\0') {
    if (DAT_2001de0e == '\0') goto LAB_08021508;
    zw_dmm_fullscreen();
  }
  if ((DAT_2001de0e != '\0') && (DAT_2001de0c != '\0')) {
    zw_dmm_factory_calibration(param_1);
  }
LAB_08021508:
  zw_dmm_calib_mode(param_1);
  FUN_0802bc90();
  uStack_14 = 5;
  uStack_12 = 0x20;
  if (DAT_2001deb8 == 0) {
    local_20 = 0xcd;
    uStack_1e = 0xd8;
    pbStack_18 = image_dmm_jacks_resistance;
  }
  else if (DAT_2001deb8 == 1) {
    local_20 = 0xcd;
    uStack_1e = 0xd8;
    pbStack_18 = image_dmm_jacks_continuity;
  }
  else if (DAT_2001deb8 == 2) {
    local_20 = 0xcd;
    uStack_1e = 0xd8;
    pbStack_18 = image_dmm_jacks_diode;
  }
  else if (DAT_2001deb8 == 3) {
    local_20 = 0xcd;
    uStack_1e = 0xd8;
    pbStack_18 = image_dmm_jacks_capacitance;
  }
  else {
    bVar1 = DAT_2001deb8 & 0xfd;
    if (bVar1 == 4) {
      uStack_14 = 5;
      if (DAT_20004594 == '\x01') {
        uStack_14 = 0x13;
      }
      local_20 = 0xcd;
      uStack_1e = 0xd8;
      pbStack_18 = image_dmm_jacks_V;
    }
    else if (bVar1 == 5) {
      uStack_14 = 5;
      if (DAT_20004594 == '\x01') {
        uStack_14 = 0x13;
      }
      local_20 = 0xcd;
      uStack_1e = 0xd8;
      pbStack_18 = image_dmm_jacks_mV;
    }
    else if (bVar1 == 9) {
      uStack_14 = 5;
      if (DAT_20004594 == '\x01') {
        uStack_14 = 0x13;
      }
      local_20 = 0x75;
      uStack_1e = 0xd8;
      pbStack_18 = image_dmm_jacks_600mA;
    }
    else {
      uStack_14 = 5;
      if (DAT_20004594 == '\x01') {
        uStack_14 = 0x13;
      }
      local_20 = 0x18;
      uStack_1e = 0xd6;
      pbStack_18 = image_dmm_jacks_10A;
    }
  }
  if (DAT_200045d9 == '\0') {
    zw_draw_element(&local_20);
  }
  if (DAT_2001de11 != '\0') {
    zw_dmm_side_menu();
  }
  zw_draw_flush_offscreen();
  return;
}




void zw_dmm_calibration(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 *puVar3;
  int unaff_r9;
  undefined1 auStack_2c [12];
  
  puVar3 = &DAT_2001de34;
  iVar2 = 0xc;
  do {
    *puVar3 = 5000;
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  zw_draw_popup_message(" DCV = 5.000V ",0xe,180000,1,2);
  DAT_2001deb8 = '\x04';
  FUN_0801f490(4);
  zw_timer_us(auStack_2c,0xffffffff);
  zw_keypress_handler();
  zw_power_button_handler_();
  FUN_08016cb4();
  iVar2 = zw_button_event();
  if (iVar2 == 2) goto LAB_08021734;
  while ((iVar2 = FUN_080270a8(auStack_2c), iVar2 == 0 || (400 < unaff_r9 - 0x12c0U))) {
    while( true ) {
      zw_dmm_init_(0);
      (hwdg.Instance)->CLR = 1;
      zw_keypress_handler();
      zw_power_button_handler_();
      FUN_08016cb4();
      iVar2 = zw_button_event();
      if (iVar2 != 2) break;
LAB_08021734:
      zw_timer_us(auStack_2c,3000000);
      unaff_r9 = 25000000 / DAT_2001de4c;
      iVar2 = DAT_2001deb8;
      (&DAT_2001de34)[iVar2] = unaff_r9;
      (&DAT_2001de34)[iVar2 + 2] = unaff_r9;
    }
  }
  zw_draw_popup_message(" Res = 100.0K ",0xe,180000,1,2);
  DAT_2001deb8 = '\0';
  FUN_0801f490(0);
  zw_dmm_init_(0);
  (hwdg.Instance)->CLR = 1;
  zw_keypress_handler();
  zw_power_button_handler_();
  FUN_08016cb4();
  iVar2 = zw_button_event();
  while ((iVar2 != 2 || (400 < 5000000 / DAT_2001de4c - 0x12c0U))) {
    zw_dmm_init_(0);
    (hwdg.Instance)->CLR = 1;
    zw_keypress_handler();
    zw_power_button_handler_();
    FUN_08016cb4();
    iVar2 = zw_button_event();
  }
  (&DAT_2001de34)[DAT_2001deb8] = 5000000 / DAT_2001de4c;
  zw_draw_popup_message(" DCA = 1.000A ",0xe,180000,1,2);
  DAT_2001deb8 = '\b';
  FUN_0801f490(8);
  zw_dmm_init_(0);
  (hwdg.Instance)->CLR = 1;
  zw_keypress_handler();
  zw_power_button_handler_();
  FUN_08016cb4();
  iVar2 = zw_button_event();
  while ((iVar2 != 2 || (0xaf0 < 5000000 / DAT_2001de4c - 0x10ccU))) {
    zw_dmm_init_(0);
    (hwdg.Instance)->CLR = 1;
    zw_keypress_handler();
    zw_power_button_handler_();
    FUN_08016cb4();
    iVar2 = zw_button_event();
  }
  iVar2 = DAT_2001deb8;
  uVar1 = 5000000 / DAT_2001de4c;
  (&DAT_2001de34)[iVar2] = uVar1;
  (&DAT_2001de34)[iVar2 + 2] = uVar1;
  zw_draw_popup_message(" DCmA = 100.0mA ",0x10,180000,1,2);
  DAT_2001deb8 = '\t';
  FUN_0801f490(9);
  zw_dmm_init_(0);
  (hwdg.Instance)->CLR = 1;
  zw_keypress_handler();
  zw_power_button_handler_();
  FUN_08016cb4();
  iVar2 = zw_button_event();
  while ((iVar2 != 2 || (700 < 5000000 / DAT_2001de4c - 0x1194U))) {
    zw_dmm_init_(0);
    (hwdg.Instance)->CLR = 1;
    zw_keypress_handler();
    zw_power_button_handler_();
    FUN_08016cb4();
    iVar2 = zw_button_event();
  }
  iVar2 = DAT_2001deb8;
  uVar1 = 5000000 / DAT_2001de4c;
  (&DAT_2001de34)[iVar2] = uVar1;
  (&DAT_2001de34)[iVar2 + 2] = uVar1;
  zw_draw_popup_message(" Done! ",7,1000,1,2);
  HAL_FLASH_Write_Offset_0x96000(0x2400,&DAT_2001de34,0x18);
  DAT_2001de0e = 0;
  DAT_2001de0c = 0;
  FUN_0801f490(4);
  return;
}




void FUN_0802194c(void)

{
  DAT_2001dedc = 0x1000;
  DAT_2001dee0 = 0x2580;
  DAT_2001dee4 = 3;
  DAT_2001def0 = 0x80;
  DAT_2001dee8 = 0;
  DAT_2001deec = 0;
  DAT_2001def4 = 0;
  HAL_UART_Init(&DAT_2001dedc);
  HAL_UART_Receive_IT(&DAT_2001dedc,&DAT_20004604,0);
  return;
}




void FUN_08021988(int param_1)

{
  if (param_1 != 0) {
    zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,0x4000,1,2);
    zw_clear_bits(&peripheral_gpioA_data,0x4000);
    return;
  }
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,0x4000,0,2);
  return;
}




void FUN_080219cc(void)

{
  if (voice_control_enable == 0) {
    FUN_08021988();
    FUN_0802194c();
    return;
  }
  FUN_08021988(1);
  FUN_0802194c();
  return;
}




int zw_voice_control(int param_1)

{
  if (param_1 == 0x55) {
    voice_control_enable = ~(voice_control_enable != '\0');
    FUN_08021988();
    if (voice_control_enable != 0) {
      zw_draw_popup_message(" Voice ON (V1.0) ",0x10,2000,1,2);
      return 0;
    }
    zw_draw_popup_message(" Voice OFF ",0xb,2000,1,2);
    return 0;
  }
  if (voice_control_enable == '\0') {
    return param_1;
  }
  if (DAT_2001debc != -0x5f) {
    return param_1;
  }
  DAT_2001debc = 0;
  if (DAT_2001debd == -0x78) {
    HAL_Delay(0x4b0);
    zw_power_off();
    return 0;
  }
  if (DAT_2001debd == '\x10') {
    system_status_ = 1;
    DAT_2001debc = 0;
    return 0x20;
  }
  if (DAT_2001debd == '\x11') {
    zw_draw_popup_message(" Run/Stop ",10,0x5dc,1,2);
    return 10;
  }
  if (DAT_2001debd == '\x13') {
    zw_draw_popup_message(" Single ",8,0x5dc,1,2);
    return 0x12;
  }
  if (DAT_2001debd == '\x14') {
    zw_draw_popup_message(" X Y Mode ",10,0x5dc,1,2);
    return 0x56;
  }
  if (DAT_2001debd == '\x15') {
    zw_draw_popup_message(" Back ",6,0x5dc,1,2);
    if ((DAT_2001de0e != '\0') && (DAT_2001de0c != '\0')) {
      DAT_2001de0e = 0;
      DAT_2001de0d = 0;
      DAT_2001de0c = 0;
      FUN_0801f490(4);
      return 0xff;
    }
    if (DAT_2001de0d != '\0') {
      DAT_2001de01 = 0;
      DAT_2001de0c = 0;
      DAT_2001de0d = 0;
      return 0xff;
    }
    if (DAT_2001ddc9 == '\0') {
      if (system_status_ == '\x03') {
        return 0xe;
      }
      return 0xff;
    }
    DAT_2001ddc9 = 0;
    DAT_2001de0c = 0;
    return 0xff;
  }
  if (DAT_2001debd == ' ') {
    if (language_0_CN_1_EN == '\0') {
      if ((ch2_enabled != '\0') && (active_channel_0_ch1_1_ch2_2_math != '\0')) {
LAB_08021d04:
        ch2_coupling_dc_ac = '\0';
        zw_draw_popup_message(" CH2=DC ",8,0x5dc,1,2);
        goto LAB_08021ba2;
      }
    }
    else {
      if ((ch2_enabled != '\0') && (active_channel_0_ch1_1_ch2_2_math != '\0')) {
        if (ch2_coupling_dc_ac != '\0') goto LAB_08021d04;
        goto LAB_08021b8a;
      }
      if (ch1_coupling_0_dc_1_ac == '\0') goto LAB_08021bea;
    }
    ch1_coupling_0_dc_1_ac = '\0';
    zw_draw_popup_message(" CH1=DC ",8,0x5dc,1,2);
  }
  else {
    if (DAT_2001debd != '!') {
      if (DAT_2001debd == '2') {
        if ((ch2_enabled == '\x01') && (trigger_source_0_ch1_1_ch2 == '\0')) {
          trigger_source_0_ch1_1_ch2 = ch2_enabled;
          zw_draw_popup_message(" Triger=CH2 ",0xc,0x5dc,1,2);
        }
        else {
          trigger_source_0_ch1_1_ch2 = '\0';
          zw_draw_popup_message(" Triger=CH1 ",0xc,0x5dc,1,2);
        }
      }
      else {
        if (DAT_2001debd == '@') {
          DAT_2001debc = 0;
          return 0xe;
        }
        if (DAT_2001debd == 'A') {
          zw_draw_popup_message(" VIEW ",6,0x4b0,1,2);
          return 0x4e;
        }
        if (DAT_2001debd == 'C') {
          zw_draw_popup_message(" Generator ",0xb,1000,1,2);
          if (language_0_CN_1_EN != '\0') {
            DAT_2001de0d = '\x01';
            DAT_2001de0c = '\0';
          }
          siggen_enable = 1;
          zw_siggen_enable_(1);
          zw_siggen_waveform_gen(siggen_waveform_pattern);
          return 0x7e;
        }
        if (DAT_2001debd == 'D') {
          DAT_2001debc = 0;
          return 7;
        }
        if (DAT_2001debd == 'E') {
          zw_draw_popup_message(" 50% ",5,0x5dc,1,2);
          if (ch2_enabled != '\x01') {
            return 0x14;
          }
          if (active_channel_0_ch1_1_ch2_2_math == '\x01') {
            return 0x54;
          }
          return 0x14;
        }
        if (DAT_2001debd == 'F') {
          if (ch2_enabled != '\0') {
            zw_draw_popup_message(" CH2 is OFF ",0xc,0x4b0,1,2);
            return 0x47;
          }
          zw_draw_popup_message(" CH2 is ON ",0xb,1000,1,2);
          return 0x47;
        }
        if (DAT_2001debd == 'P') {
          DAT_2001debc = 0;
          return 0x11;
        }
        if (DAT_2001debd == 'Q') {
          DAT_2001debc = 0;
          return 9;
        }
        if (DAT_2001debd == 'R') {
          DAT_2001debc = 0;
          return 0x16;
        }
        if (DAT_2001debd == 'S') {
          DAT_2001debc = 0;
          return 0x15;
        }
        if (DAT_2001debd == 'T') {
          DAT_2001debc = 0;
          return 5;
        }
        if (DAT_2001debd == 'U') {
          DAT_2001debc = 0;
          return 0xd;
        }
        if (DAT_2001debd == 'V') {
          zw_draw_popup_message(" Move down ",0xb,1000,1,2);
          if (global_settings != 0) {
            if ((ch2_enabled == '\0') || (active_channel_0_ch1_1_ch2_2_math == '\0')) {
              ch1_vert_offset_pixels = ch1_vert_offset_pixels + -0x19;
            }
            else {
              ch2_vert_offset_pixels = ch2_vert_offset_pixels + -0x19;
            }
          }
        }
        else {
          if (DAT_2001debd != 'W') {
            if (DAT_2001debd == '`') {
              zw_draw_popup_message(" DMM RES ",9,0x4b0,1,2);
              DAT_2001de0e = 1;
              DAT_2001de0d = 0;
              DAT_2001deb8 = 0;
              FUN_0801f490(0);
              DAT_2001de0c = 1;
              return 0;
            }
            if (DAT_2001debd == 'a') {
              zw_draw_popup_message(" DMM Diode ",0xb,0x4b0,1,2);
              DAT_2001de0d = 0;
              DAT_2001deb8 = 2;
              DAT_2001de0e = 1;
              FUN_0801f490(2);
              DAT_2001de0c = 1;
              return 0;
            }
            if (DAT_2001debd == 'b') {
              zw_draw_popup_message(" DMM Cap ",9,0x4b0,1,2);
              DAT_2001de0d = 0;
              DAT_2001de0e = 1;
              DAT_2001deb8 = 3;
              FUN_0801f490(3);
              DAT_2001de0c = 1;
              return 0;
            }
            if (DAT_2001debd != 'c') {
              if (DAT_2001debd == 'd') {
                zw_draw_popup_message(" DMM DC-Vol ",0xc,0x4b0,1,2);
                DAT_2001de0d = 0;
                DAT_2001de0e = 1;
                DAT_2001deb8 = 4;
                FUN_0801f490(4);
                DAT_2001de0c = 1;
                return 0;
              }
              if (DAT_2001debd != 'e') {
                if (DAT_2001debd != 'f') {
                  DAT_2001debc = 0;
                  return 0;
                }
                zw_draw_popup_message(" DMM DC-10A ",0xc,0x4b0,1,2);
                DAT_2001de0d = 0;
                DAT_2001de0e = 1;
                DAT_2001deb8 = 8;
                FUN_0801f490(8);
                DAT_2001de0c = 1;
                return 0;
              }
              zw_draw_popup_message(" DMM AC-Vol ",0xc,0x4b0,1,2);
              DAT_2001de0d = 0;
              DAT_2001de0e = 1;
              DAT_2001deb8 = 6;
              FUN_0801f490(6);
              DAT_2001de0c = 1;
              return 0;
            }
            zw_draw_popup_message(" DMM Cont ",10,0x4b0,1,2);
            DAT_2001de0d = 0;
            DAT_2001de0e = 1;
            DAT_2001deb8 = 1;
            FUN_0801f490(1);
            DAT_2001de0c = 1;
            return 0;
          }
          zw_draw_popup_message(" Move up ",9,1000,1,2);
          if (global_settings != 0) {
            if ((ch2_enabled == '\0') || (active_channel_0_ch1_1_ch2_2_math == '\0')) {
              ch1_vert_offset_pixels = ch1_vert_offset_pixels + 0x19;
            }
            else {
              ch2_vert_offset_pixels = ch2_vert_offset_pixels + 0x19;
            }
          }
        }
      }
      goto LAB_08021ba2;
    }
    if (language_0_CN_1_EN != '\0') {
      DAT_2001debc = 0;
      return 0;
    }
    if ((ch2_enabled == '\0') || (active_channel_0_ch1_1_ch2_2_math == '\0')) {
LAB_08021bea:
      ch1_coupling_0_dc_1_ac = '\x01';
      zw_draw_popup_message(" CH1=AC ",8,0x5dc,1,2);
      goto LAB_08021ba2;
    }
LAB_08021b8a:
    ch2_coupling_dc_ac = '\x01';
    zw_draw_popup_message(" CH2=AC ",8,0x5dc,1,2);
  }
LAB_08021ba2:
  FUN_0801eff0(0xff);
  return 0;
}




void FUN_08021ffc(void)

{
  zw_timer_us(&DAT_2000464c,200000);
  return;
}




undefined4 FUN_08022014(void)

{
  ulonglong uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  byte bStack_16;
  byte bStack_15;
  
  if (DAT_2000465d != '\x01') {
    if (DAT_2000465d != '\0') {
      if ((DAT_2000465d == '\x02') && (iVar2 = FUN_080270a8(&DAT_20004660), iVar2 != 0)) {
        DAT_2000465d = '\0';
      }
      return 0;
    }
    FUN_08016c18(0);
    zw_timer_us(&DAT_20004624,100000);
    DAT_2000465d = 1;
    return 0;
  }
  iVar2 = FUN_080270a8(&DAT_20004624);
  if (iVar2 == 0) {
    return 0;
  }
  DAT_2000465e = DAT_2000465e + '\x01';
  FUN_08016c18(0);
  FUN_080172b0(&bStack_16,&bStack_15);
  uVar7 = ch1_v_div_index;
  iVar2 = (*(&DAT_08055a1c + uVar7 * 4) * 10) / *(&DAT_08055a1c + (uVar7 - 1) * 4);
  uVar5 = ch1_vert_offset_pixels - 0x80U & 0xff;
  uVar5 = (uVar5 < 0x1c) * 0x1c + (uVar5 >= 0x1c) * uVar5;
  uVar3 = bStack_16;
  uVar4 = bStack_15;
  uVar6 = (uVar5 < 0xe4) * uVar5 + (uVar5 >= 0xe4) * 0xe4;
  uVar1 = (uVar3 + uVar4) / 2;
  uVar5 = uVar1;
  DAT_20004640 = uVar1;
  if (uVar6 < uVar3) {
    uVar8 = iVar2 * (uVar3 - uVar6) & 0xffff;
  }
  else {
    uVar8 = 0;
  }
  if (uVar4 < uVar6) {
    uVar9 = (uVar6 - uVar4) * iVar2 & 0x7fff;
  }
  else {
    uVar9 = 0;
  }
  if ((((uVar3 < 0xe4) && (0x1c < uVar4)) && (((0xda - uVar6) * 10 < uVar8 || ((uVar6 - 0x26) * 10 < uVar9)))) || (DAT_2000465e == '\n')) {
    DAT_2000465e = 0;
    if (DAT_20004658 == DAT_20004642) {
      DAT_2000465e = 0;
      return 1;
    }
    DAT_20004658 = DAT_20004642;
    iVar10 = uVar3 - uVar4;
    if (false) {
      uVar4 = 0x80;
    }
    if (0xd < iVar10) {
      iVar11 = uVar5 - 0x80;
      if ((5 < uVar7) && ((iVar2 * (((uVar3 < 0x80) * 0x80 + (uVar3 >= 0x80) * uVar3) - uVar4 & 0xff)) / 10 < 0x8c)) {
        iVar11 = (iVar2 * iVar11) / 10;
        ch1_v_div_index = uVar7 - 1;
        DAT_20004640 = ((uVar5 - uVar6) * iVar2) / 10 + uVar6 & 0x7fff;
      }
      ch1_vert_offset_pixels = ch1_vert_offset_pixels - iVar11;
      DAT_20004640 = DAT_20004640 - iVar11;
      if (0x18 < iVar10) {
        DAT_20004647 = 0;
        goto LAB_080221b0;
      }
      uVar7 = ch1_v_div_index;
    }
    DAT_20004647 = 1;
    if (((uVar7 < 6) && (0x6c < uVar5)) && (uVar5 < 0x94)) {
      DAT_20004642 = 0;
      ch1_v_div_index = 8;
    }
LAB_080221b0:
    DAT_2000465d = 0;
    FUN_0801eff0(0xff);
    return 1;
  }
  uVar5 = DAT_20004642;
  if (uVar5 < 9) {
    if ((uVar3 < 0xe4) && (0x1c < uVar4)) {
      if (uVar5 == 4) {
        return 0;
      }
      if (5 < uVar5) goto LAB_080221da;
      if (uVar5 == 5) {
        DAT_20004642 = 0;
        ch1_v_div_index = 8;
        goto LAB_080221e8;
      }
      ch1_v_div_index = DAT_20004642;
      if (uVar5 == 4) goto LAB_080221e8;
LAB_08022232:
      uVar3 = uVar5 + 1;
      uVar5 = uVar3 & 0xff;
      DAT_20004642 = uVar3;
    }
    else {
      uVar3 = uVar5 - 1 & 0xff;
      if (uVar3 < 4) {
        DAT_20004642 = uVar5 - 1;
        ch1_v_div_index = (&DAT_08057d38)[uVar3];
        goto LAB_080221e8;
      }
      if (uVar5 == 0) {
        DAT_20004642 = 5;
        ch1_v_div_index = 9;
        goto LAB_080221e8;
      }
      if ((uVar5 - 5 & 0xff) < 4) goto LAB_08022232;
    }
    ch1_v_div_index = (&DAT_08057d38)[uVar5];
  }
  else {
LAB_080221da:
    DAT_20004642 = uVar5 - 1;
    ch1_v_div_index = (&DAT_08057d38)[uVar5 - 1 & 0xff];
  }
LAB_080221e8:
  ch1_vert_offset_pixels = 0;
  FUN_0801eff0(0xff);
  if (ch1_v_div_index == 9) {
    zw_timer_us(&DAT_20004660,200000);
  }
  else {
    zw_timer_us(&DAT_20004660,50000);
  }
  DAT_2000465d = 2;
  return 0;
}




undefined4 FUN_080222e8(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  byte bStack_16;
  byte bStack_15;
  
  if (DAT_2000465d != '\x01') {
    if (DAT_2000465d != '\0') {
      if ((DAT_2000465d == '\x02') && (iVar1 = FUN_080270a8(&DAT_20004660), iVar1 != 0)) {
        DAT_2000465d = '\0';
      }
      return 0;
    }
    FUN_08016c18(1);
    FUN_08016c18(1);
    zw_timer_us(&DAT_20004624,100000);
    DAT_2000465d = 1;
    return 0;
  }
  iVar1 = FUN_080270a8(&DAT_20004624);
  if (iVar1 == 0) {
    return 0;
  }
  DAT_2000465e = DAT_2000465e + '\x01';
  FUN_08016c18(1);
  FUN_080172b0(&bStack_16,&bStack_15);
  DAT_20004644 = (bStack_16 + bStack_15) / 2;
  printf_disabled_1("max min %d %d<<<<<<<<<<\r\n");
  uVar8 = ch2_v_div_index;
  iVar1 = (*(&DAT_08055a1c + uVar8 * 4) * 10) / *(&DAT_08055a1c + (uVar8 - 1) * 4);
  uVar4 = ch2_vert_offset_pixels - 0x80U & 0xff;
  uVar4 = (uVar4 < 0x1c) * 0x1c + (uVar4 >= 0x1c) * uVar4;
  uVar4 = (uVar4 < 0xe4) * uVar4 + (uVar4 >= 0xe4) * 0xe4;
  uVar7 = bStack_16;
  if (uVar4 < uVar7) {
    uVar2 = iVar1 * (uVar7 - uVar4) & 0xffff;
  }
  else {
    uVar2 = 0;
  }
  uVar5 = bStack_15;
  if (uVar5 < uVar4) {
    uVar3 = iVar1 * (uVar4 - uVar5) & 0xffff;
  }
  else {
    uVar3 = 0;
  }
  if ((((uVar7 < 0xe4) && (0x1c < uVar5)) && (((0xda - uVar4) * 10 < uVar2 || ((uVar4 - 0x26) * 10 < uVar3)))) || (DAT_2000465e == '\n')) {
    DAT_2000465e = 0;
    if (DAT_20004659 != DAT_20004646) {
      DAT_20004659 = DAT_20004646;
      uVar2 = 0x80;
      if ((bStack_15 & 0x80000000U) == 0) {
        uVar2 = uVar5;
      }
      if (0xd < uVar7 - uVar5) {
        iVar6 = (uVar7 + uVar5) / 2 + -0x80;
        if ((5 < uVar8) && ((iVar1 * (((uVar7 < 0x80) * 0x80 + (uVar7 >= 0x80) * uVar7) - uVar2 & 0xff)) / 10 < 0x8c)) {
          DAT_20004644 = uVar4 + (iVar1 * (DAT_20004644 - uVar4)) / 10;
          ch2_v_div_index = uVar8 - 1;
          iVar6 = (iVar1 * iVar6) / 10;
        }
        ch2_vert_offset_pixels = ch2_vert_offset_pixels - iVar6;
        DAT_20004644 = DAT_20004644 - iVar6;
      }
      DAT_2000465d = 0;
      printf_disabled_1("vertical done !\r\n");
      if (bStack_16 - bStack_15 < 0x19) {
        DAT_20004648 = 1;
        if (((ch2_v_div_index < 6) && (uVar4 = (bStack_16 + bStack_15) / 2, 0x6c < uVar4)) && (uVar4 < 0x94)) {
          DAT_20004646 = 0;
          ch2_v_div_index = 8;
        }
      }
      else {
        DAT_20004648 = 0;
      }
      FUN_0801eff0(0xff);
      return 1;
    }
    DAT_2000465e = 0;
    return 1;
  }
  uVar4 = DAT_20004646;
  if (uVar4 < 9) {
    if ((0xe3 < uVar7) || (uVar5 < 0x1d)) {
      uVar7 = uVar4 - 1 & 0xff;
      if (uVar7 < 4) {
        DAT_20004646 = uVar4 - 1;
        ch2_v_div_index = (&DAT_08057d38)[uVar7];
      }
      else if (uVar4 == 0) {
        DAT_20004646 = 5;
        ch2_v_div_index = 9;
      }
      else {
        if ((uVar4 - 5 & 0xff) < 4) {
          uVar7 = uVar4 + 1;
          uVar4 = uVar7 & 0xff;
          DAT_20004646 = uVar7;
        }
        ch2_v_div_index = (&DAT_08057d38)[uVar4];
      }
      ch2_vert_offset_pixels = 0;
      FUN_0801eff0(0xff);
      printf_disabled_1("ch2_VolDiv_sel = %d\r\n",ch2_v_div_index);
      goto joined_r0x0802256c;
    }
    if (uVar4 == 4) {
      return 0;
    }
  }
  printf_disabled_1("maxdiff mindiff %d %d<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\\r\n");
  if (DAT_20004646 < 6) {
    if (DAT_20004646 == 5) {
      DAT_20004646 = 0;
      ch2_v_div_index = 8;
    }
    else {
      ch2_v_div_index = DAT_20004646;
      if (DAT_20004646 != 4) {
        DAT_20004646 = DAT_20004646 + 1;
        ch2_v_div_index = (&DAT_08057d38)[DAT_20004646];
      }
    }
  }
  else {
    DAT_20004646 = DAT_20004646 - 1;
    ch2_v_div_index = (&DAT_08057d38)[DAT_20004646];
  }
  ch2_vert_offset_pixels = 0;
  FUN_0801eff0(0xff);
  printf_disabled_1("ch2_VolDiv_sel = %d\r\n",ch2_v_div_index);
  printf_disabled_1("sysParm.ch2_VolDiv = %d\r\n",ch2_volt_scale_10uV);
joined_r0x0802256c:
  if (ch2_v_div_index == 9) {
    zw_timer_us(&DAT_20004660,200000);
  }
  else {
    zw_timer_us(&DAT_20004660,50000);
  }
  DAT_2000465d = 2;
  return 0;
}




undefined4 FUN_08022610(void)

{
  int iVar1;
  char *pcVar2;
  uint local_14;
  
  if (DAT_2000465c == '\0') {
    DAT_2000465b = trigger_source_0_ch1_1_ch2;
    DAT_2000465a = trigger_level_mode_0_auto_1_manual;
    trigger_source_0_ch1_1_ch2 = DAT_2000465c;
    trigger_level_mode_0_auto_1_manual = 1;
    trigger_level_raw_adc__0_255 = DAT_20004640;
    FUN_08017190();
    FUN_08016c18(0);
    zw_timer_us(&DAT_20004624,200000);
    DAT_2000465c = 1;
    printf_disabled_1("cntTime=%d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\r\n",200000);
    return 0;
  }
  if ((DAT_2000465c != '\x01') || (iVar1 = FUN_080270a8(&DAT_20004624), iVar1 == 0)) {
    return 0;
  }
  FUN_08016c18(0);
  FUN_080172c4(&local_14);
  trigger_level_mode_0_auto_1_manual = DAT_2000465a;
  printf_disabled_1("edge_cnt=%d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\r\n",local_14);
  if (local_14 < 2) {
    trigger_source_0_ch1_1_ch2 = DAT_2000465b;
    timebase_index_2_5ns_30_10s = '\x0e';
    FUN_0801eff0(0xff);
  }
  else {
    pcVar2 = "\n";
    timebase_index_2_5ns_30_10s = '\x03';
    iVar1 = 0x14;
    do {
      if ((0 < *(pcVar2 + 4)) || ((*(pcVar2 + 4) == 0 && (200000000 / local_14 >> 2 < *pcVar2)))) goto LAB_0802267c;
      timebase_index_2_5ns_30_10s = timebase_index_2_5ns_30_10s + '\x01';
      pcVar2 = pcVar2 + 8;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    timebase_index_2_5ns_30_10s = '\x17';
LAB_0802267c:
    printf_disabled_1("timeBase_sel=%d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\r\n");
    FUN_0801eff0(0xff);
  }
  DAT_2000465c = 0;
  return 1;
}




undefined4 FUN_08022734(void)

{
  int iVar1;
  char *pcVar2;
  uint local_14;
  
  if (DAT_2000465c == '\0') {
    DAT_2000465b = trigger_source_0_ch1_1_ch2;
    DAT_2000465a = trigger_level_mode_0_auto_1_manual;
    trigger_source_0_ch1_1_ch2 = 1;
    trigger_level_mode_0_auto_1_manual = 1;
    trigger_level_raw_adc__0_255 = DAT_20004644;
    FUN_08017190();
    FUN_08016c18(1);
    zw_timer_us(&DAT_20004624,200000);
    DAT_2000465c = 1;
    printf_disabled_1("cntTime2=%d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\r\n",200000);
    return 0;
  }
  if ((DAT_2000465c != '\x01') || (iVar1 = FUN_080270a8(&DAT_20004624), iVar1 == 0)) {
    return 0;
  }
  FUN_08016c18(1);
  FUN_080172c4(&local_14);
  trigger_level_mode_0_auto_1_manual = DAT_2000465a;
  printf_disabled_1("edge_cnt2=%d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\r\n",local_14);
  trigger_source_0_ch1_1_ch2 = DAT_2000465b;
  if (1 < local_14) {
    pcVar2 = "\n";
    timebase_index_2_5ns_30_10s = '\x03';
    iVar1 = 0x14;
    do {
      if ((0 < *(pcVar2 + 4)) || ((*(pcVar2 + 4) == 0 && (200000000 / local_14 >> 2 < *pcVar2)))) goto LAB_080227a8;
      timebase_index_2_5ns_30_10s = timebase_index_2_5ns_30_10s + '\x01';
      pcVar2 = pcVar2 + 8;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    timebase_index_2_5ns_30_10s = '\x17';
LAB_080227a8:
    printf_disabled_1("timeBase_sel2=%d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\r\n");
    FUN_0801eff0(0xff);
  }
  DAT_2000465c = 0;
  return 1;
}




void FUN_08022848(int param_1)

{
  char cVar1;
  int iVar2;
  
  if (system_status_ != '\x04') {
    iVar2 = FUN_080270a8(&DAT_2000464c);
    if (iVar2 == 0) {
LAB_08022862:
      if (param_1 == 0x20) goto LAB_080228a0;
LAB_08022868:
      if ((param_1 == 0x60) && (system_status_ == '\x01')) {
        RTAuto_enable_ = '\x01';
        ch2_enabled = '\0';
        goto LAB_080228a4;
      }
    }
    else {
      if (DAT_20004649 != '\0') {
        if (DAT_20004649 == '\x01') {
          FUN_08016c18();
          FUN_080172b0(&DAT_2001df1c,&DAT_2001df1d);
          goto LAB_0802288e;
        }
        DAT_20004649 = '\0';
        goto LAB_08022862;
      }
      FUN_08016c18();
      FUN_080172b0(&DAT_2001df1e,&DAT_2001df1f);
      if ((ch2_enabled == '\x01') && (cVar1 = trigger_source_0_ch1_1_ch2, trigger_source_0_ch1_1_ch2 == '\x01')) {
        FUN_08016c18(1);
        DAT_20004649 = cVar1;
        goto LAB_08022862;
      }
LAB_0802288e:
      FUN_08016c18(0);
      DAT_20004649 = '\0';
      if (param_1 != 0x20) goto LAB_08022868;
LAB_080228a0:
      if (system_status_ == '\x01') {
LAB_080228a4:
        FUN_08018734();
        system_status_ = 4;
        DAT_2000465c = 0;
        DAT_2001de01 = 0;
        trigger_mode_icon_0_auto_1_normal = 0;
        DAT_20004630 = 0;
        ch1_v_div_index = 8;
        DAT_2000465d = 0;
        global_settings = 1;
        roll_menu_enable = 1;
        acq_buffer_ready_flag_ = 1;
        ch1_vert_offset_pixels = 0;
        ch1_trigger_level_10uV_target_l = 0;
        ch1_trigger_level_10uV_target_h = 0;
        DAT_20004642 = 0;
        DAT_20004646 = 0;
        DAT_20004658 = 0;
        DAT_20004659 = 0;
        DAT_2000465e = 0;
        timebase_index_2_5ns_30_10s = DAT_200001c0;
        FUN_0801b974();
        if (ch2_enabled == '\x01') {
          ch2_v_div_index = 8;
          ch2_vert_offset_pixels = 0;
          ch2_trigger_level_10uV_target_l = 0;
          ch2_trigger_level_10uV_target_h = 0;
          FUN_0801ba08();
        }
        horiz_trigger_delay_ps_l = 0;
        horiz_trigger_delay_ps_h = 0;
        roll_mode_view_offset__l = 0;
        roll_mode_view_offset__h = 0;
        DAT_2001dcd8 = DAT_2001dcd8 | 0x10;
        FUN_0801eff0(0xff);
        zw_timer_us(&DAT_20004634,8000000);
        zw_timer_us(&DAT_20004624,100000);
        zw_timer_us(&DAT_20004660,50000);
        HAL_Delay(100);
        if (RTAuto_enable_ == '\0') {
          zw_draw_popup_message("AUTO",4,12000,1,2);
          return;
        }
        zw_draw_popup_message("AUTO",4,1000,1,2);
        return;
      }
    }
    if (system_status_ != '\x04') {
      return;
    }
  }
  if (RTAuto_enable_ == '\0') {
    iVar2 = FUN_080270a8(&DAT_20004634);
    if (iVar2 == 0) {
      if (param_1 != 10) goto LAB_08022970;
      printf_disabled_1("auto time out!!!!!!=================!!!!!!!\r\n");
LAB_08022a34:
      system_status_ = '\x01';
      FUN_0801eff0(10);
    }
    else {
      printf_disabled_1("auto time out!!!!!!=================!!!!!!!\r\n");
      system_status_ = '\x01';
      if (param_1 == 10) goto LAB_08022a34;
    }
    DAT_2001dcd8 = DAT_2001dcd8 & 0xffffffef;
    zw_draw_popup_message(" ",1,10,0,0);
  }
LAB_08022970:
  if (DAT_20004630 == 0) {
    iVar2 = FUN_08022014();
    if (iVar2 == 0) {
      return;
    }
    if (ch2_enabled == '\x01') {
      DAT_20004630 = 1;
      return;
    }
    if (DAT_20004647 != '\0') {
      DAT_20004630 = 4;
      timebase_index_2_5ns_30_10s = 0x10;
      return;
    }
LAB_08022a88:
    DAT_20004630 = 2;
  }
  else {
    if (DAT_20004630 == 1) {
      iVar2 = FUN_080222e8();
      if (iVar2 == 0) {
        return;
      }
      if (DAT_20004647 == '\0') goto LAB_08022a88;
      if (DAT_20004648 == '\0') {
        DAT_20004630 = 3;
        return;
      }
    }
    else {
      if (DAT_20004630 == 3) {
        iVar2 = FUN_08022734();
        if (iVar2 == 0) {
          return;
        }
        if (0x28 < DAT_2001a160 - DAT_2001a161) {
          DAT_20004630 = 4;
          trigger_source_0_ch1_1_ch2 = 1;
          return;
        }
        DAT_20004630 = 4;
        return;
      }
      if (3 < DAT_20004630) {
        if (DAT_20004630 == 4) {
          if (RTAuto_enable_ == '\0') {
            DAT_20004630 = 0;
            system_status_ = 1;
            FUN_0801bacc(ch1_vert_offset_pixels);
            FUN_0801bb08(ch2_vert_offset_pixels);
            FUN_0801eff0(0xff);
            zw_draw_popup_message("AUTO",4,10,1,2);
            return;
          }
          DAT_20004630 = 5;
          zw_timer_us(&DAT_20004624,2000000);
          return;
        }
        if (DAT_20004630 == 5) {
          iVar2 = FUN_080270a8(&DAT_20004624);
          if (iVar2 != 0) {
            DAT_20004630 = 0;
            DAT_2000465c = 0;
            DAT_2000465d = 0;
            DAT_2000465e = 0;
            return;
          }
          return;
        }
        return;
      }
      if (DAT_20004630 != 2) {
        return;
      }
      iVar2 = FUN_08022610();
      if (iVar2 == 0) {
        return;
      }
      DAT_2000465c = 0;
      if (ch2_enabled == '\x01') {
        if (DAT_20019ca4 - DAT_20019ca5 < 0x29) {
          DAT_2000465c = 0;
          DAT_20004630 = 3;
          return;
        }
        trigger_source_0_ch1_1_ch2 = '\0';
      }
    }
    DAT_20004630 = 4;
  }
  return;
}




int zw_draw_personalization_menu(int param_1)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 unaff_r4;
  undefined4 uVar5;
  ushort uVar6;
  ushort *puVar7;
  undefined2 uStack_28;
  undefined2 uStack_26;
  byte *pbStack_20;
  undefined2 uStack_1c;
  undefined2 uStack_1a;
  
  if ((param_1 == 0) || (system_status_ != '\b')) {
    return param_1;
  }
  if (param_1 == 4) {
    bVar1 = DAT_2000466c + 1;
LAB_08022bd0:
    DAT_2000466c = bVar1;
    if (DAT_2000466c < '\r') goto LAB_08022dc4;
    DAT_2000466c = DAT_2000466c - 0xd;
  }
  else {
    if (param_1 == 3) {
      bVar1 = DAT_2000466c - 1;
      goto LAB_08022bd0;
    }
    if (param_1 == 0x13) {
      if ('\a' < DAT_2000466c) {
        bVar1 = DAT_2000466c + 2;
        goto LAB_08022bd0;
      }
      DAT_2000466c = DAT_2000466c + 3;
    }
    else {
      bVar1 = DAT_2000466c;
      if ((param_1 != 0xb) || (bVar1 = DAT_2000466c - 2, 8 < DAT_2000466c - 2)) goto LAB_08022bd0;
      DAT_2000466c = DAT_2000466c - 3;
    }
LAB_08022dc4:
    if (DAT_2000466c < '\0') {
      DAT_2000466c = DAT_2000466c + 0xd;
    }
  }
  if (param_1 != 2) {
    if (param_1 == 0x7f) {
      FUN_080265c0(0,0,0x140,0xf0,0x969);
      uStack_28 = 0x14;
      uStack_26 = 0x16;
      uStack_1a = 0xe;
      pbStack_20 = image_personalization_title_label_EN;
      if (language_0_CN_1_EN == '\0') {
        pbStack_20 = image_personalization_title_label_CN;
      }
      uStack_1c = 0xd;
      zw_draw_element(&uStack_28);
      zw_flushOffscreenRectangle(uStack_28,uStack_26,*pbStack_20,pbStack_20[1]);
      zw_draw_element_16bpp(image_personalization_background_top_left,0x1b,0x30);
      zw_draw_element_16bpp(image_personalization_background_top_right,0x121,0x30);
      zw_draw_element_16bpp(image_personalization_background_bottom_left,0x1b,0xbd);
      zw_draw_element_16bpp(image_personalization_background_bottom_right,0x121,0xbd);
      FUN_080265c0(33,54,256,135,8846);
      FUN_080264d0(0x21,0x30,0x100,0x9492);
      FUN_080265c0(0x21,0x31,0x100,5,0x228e);
      FUN_080264d0(0x21,0xc2,0x100,0x9492);
      FUN_080265c0(0x21,0xbd,0x100,5,0x228e);
      FUN_08026548(0x1b,0x36,0x87,0x9492);
      FUN_080265c0(0x1c,0x36,5,0x87,0x228e);
      FUN_08026548(0x126,0x36,0x87,0x9492);
      FUN_080265c0(0x121,0x36,5,0x87,0x228e);
      zw_draw_element_16bpp(image_personalization_background_left,0x21,0x37);
      zw_draw_element_16bpp(image_personalization_background_left,0x21,0x52);
      zw_draw_element_16bpp(image_personalization_background_left,0x21,0x6d);
      zw_draw_element_16bpp(image_personalization_background_left,0x21,0x88);
      zw_draw_element_16bpp(image_personalization_background_left,0x21,0xa3);
      zw_draw_element_16bpp(image_personalization_background_right,0x11a,0x37);
      zw_draw_element_16bpp(image_personalization_background_right,0x11a,0x52);
      zw_draw_element_16bpp(image_personalization_background_right,0x11a,0x6d);
      zw_draw_element_16bpp(image_personalization_background_right,0x11a,0x88);
      zw_draw_element_16bpp(image_personalization_background_right,0x11a,0xa3);
      FUN_080264d0(0x26,0x37,0xf4,0x9492);
      FUN_080264d0(0x26,0x48,0xf4,0x9492);
      FUN_080264d0(0x26,0x52,0xf4,0x9492);
      FUN_080264d0(0x26,99,0xf4,0x9492);
      FUN_080264d0(0x26,0x6d,0xf4,0x9492);
      FUN_080264d0(0x26,0x7e,0xf4,0x9492);
      FUN_080264d0(0x26,0x88,0xf4,0x9492);
      FUN_080264d0(0x26,0x99,0xf4,0x9492);
      FUN_080264d0(0x26,0xa3,0xf4,0x9492);
      FUN_080264d0(0x26,0xb4,0xf4,0x9492);
      FUN_080265c0(0x26,0x38,0xf4,0x10,0x250);
      FUN_080265c0(0x26,0x53,0xf4,0x10,0x250);
      FUN_080265c0(0x26,0x6e,0xf4,0x10,0x250);
      FUN_080265c0(0x26,0x89,0xf4,0x10,0x250);
      FUN_080265c0(0x26,0xa4,0xf4,0x10,0x250);
      uStack_28 = 0x26;
      uStack_26 = 0x38;
      uStack_1a = 0x10;
      pbStack_20 = image_personalization_grid_style_EN;
      if (language_0_CN_1_EN == '\0') {
        pbStack_20 = image_personalization_grid_style_CN;
      }
      uStack_1c = 0xd;
      zw_draw_element(&uStack_28);
      zw_flushOffscreenRectangle(uStack_28,uStack_26,*pbStack_20,pbStack_20[1]);
      uStack_26 = 0x53;
      pbStack_20 = image_personalization_grid_color_EN;
      if (language_0_CN_1_EN == '\0') {
        pbStack_20 = image_personalization_grid_color_CN;
      }
      zw_draw_element(&uStack_28);
      zw_flushOffscreenRectangle(uStack_28,uStack_26,*pbStack_20,pbStack_20[1]);
      uStack_26 = 0x6e;
      pbStack_20 = image_personalization_CH2_color_EN;
      if (language_0_CN_1_EN == '\0') {
        pbStack_20 = image_personalization_CH2_color_CN;
      }
      zw_draw_element(&uStack_28);
      zw_flushOffscreenRectangle(uStack_28,uStack_26,*pbStack_20,pbStack_20[1]);
      uStack_26 = 0x89;
      pbStack_20 = image_personalization_dmm_EN;
      if (language_0_CN_1_EN == '\0') {
        pbStack_20 = image_personalization_dmm_CN;
      }
      zw_draw_element(&uStack_28);
      zw_flushOffscreenRectangle(uStack_28,uStack_26,*pbStack_20,pbStack_20[1]);
      uStack_26 = 0xa4;
      pbStack_20 = image_personalization_disp_inver_EN;
      if (language_0_CN_1_EN == '\0') {
        pbStack_20 = image_personalization_disp_inver_CN;
      }
      zw_draw_element(&uStack_28);
      zw_flushOffscreenRectangle(uStack_28,uStack_26,*pbStack_20,pbStack_20[1]);
      FUN_080265c0(0x7e,0x59,0x16,4,0x39c7);
      FUN_080265c0(0xad,0x59,0x16,4,0x9cd3);
      FUN_080265c0(0xe2,0x59,0x16,4,0xffff);
      FUN_080265c0(0x8d,0x72,8,8,0x7e0);
      FUN_080265c0(0xbb,0x72,8,8,0xf81f);
      FUN_080265c0(0xf0,0x72,8,8,0x7ff);
    }
    goto switchD_08022e2c_default;
  }
  switch(DAT_2000466c) {
  case 0:
    settings_grid_style_0_none_1_dot_2_line = '\x01';
    goto LAB_08022bea;
  case 1:
    settings_grid_style_0_none_1_dot_2_line = '\x02';
    goto LAB_08022e4e;
  case 2:
    settings_grid_style_0_none_1_dot_2_line = '\0';
    goto LAB_08022f3c;
  case 3:
    settings_grid_color_0_dark_1_medium_2_light = '\0';
    unaff_r4 = 0x86;
    break;
  case 4:
    settings_grid_color_0_dark_1_medium_2_light = '\x01';
    unaff_r4 = 0xb7;
    break;
  case 5:
    settings_grid_color_0_dark_1_medium_2_light = '\x02';
    unaff_r4 = 0xeb;
    break;
  case 6:
    settings_ch2_color_0_green_1_purple_2_cyan = '\0';
    puVar7 = &ch2_configured_color_gradient_0_31;
    uVar2 = 0;
    iVar4 = 0x20;
    do {
      uVar3 = uVar2 | 0x20;
      uVar2 = uVar2 + 0x40;
      *puVar7 = uVar3;
      puVar7 = puVar7 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    goto LAB_08022f12;
  case 7:
    settings_ch2_color_0_green_1_purple_2_cyan = '\x01';
    uVar3 = 0;
    puVar7 = &ch2_configured_color_gradient_0_31;
    uVar2 = 0;
    iVar4 = 0x20;
    do {
      uVar6 = uVar3 | uVar2;
      uVar3 = uVar3 + 0x800;
      *puVar7 = uVar6;
      puVar7 = puVar7 + 1;
      uVar2 = uVar2 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    goto LAB_08022ef0;
  case 8:
    settings_ch2_color_0_green_1_purple_2_cyan = '\x02';
    uVar3 = 0;
    puVar7 = &ch2_configured_color_gradient_0_31;
    uVar2 = 0;
    iVar4 = 0x20;
    do {
      uVar6 = uVar3 | uVar2;
      uVar3 = uVar3 + 0x40;
      *puVar7 = uVar6 | 0x20;
      puVar7 = puVar7 + 1;
      uVar2 = uVar2 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    goto LAB_08022ec6;
  case 9:
    settings_dmm_window_0_window_1_fullscreen = '\x01';
    goto LAB_08022e90;
  case 10:
    settings_dmm_window_0_window_1_fullscreen = '\0';
    goto LAB_08022e78;
  case 0xb:
    settings_invert_lcd = '\0';
    FUN_080262e4(0);
  default:
switchD_08022e2c_default:
    if (DAT_2000466c == 0) {
LAB_08022bea:
      unaff_r4 = 0x85;
      if (language_0_CN_1_EN == '\0') {
        unaff_r4 = 0x83;
      }
      uVar5 = 0x49;
      goto LAB_08022bfa;
    }
    if (DAT_2000466c == 1) {
LAB_08022e4e:
      unaff_r4 = 0xb2;
      if (language_0_CN_1_EN != '\0') {
        unaff_r4 = 0xb5;
      }
    }
    else {
      if (DAT_2000466c != 2) {
        if (DAT_2000466c == 3) {
          unaff_r4 = 0x86;
        }
        else if (DAT_2000466c == 4) {
          unaff_r4 = 0xb7;
        }
        else {
          if (DAT_2000466c != 5) {
            if (DAT_2000466c == 6) {
LAB_08022f12:
              unaff_r4 = 0x8c;
            }
            else if (DAT_2000466c == 7) {
LAB_08022ef0:
              unaff_r4 = 0xbb;
            }
            else {
              if (DAT_2000466c != 8) {
                if (DAT_2000466c == 9) {
LAB_08022e90:
                  unaff_r4 = 0x71;
                  if (language_0_CN_1_EN != '\0') {
                    unaff_r4 = 0x81;
                  }
                }
                else {
                  if (DAT_2000466c != 10) {
                    if (DAT_2000466c == 0xb) {
                      unaff_r4 = 0x93;
                      if (language_0_CN_1_EN != '\0') {
                        unaff_r4 = 0x9a;
                      }
                    }
                    else {
                      if (DAT_2000466c != 0xc) {
                        uVar5 = 0;
                        if (DAT_2000466c < '\x03') {
                          uVar5 = 0x49;
                        }
                        goto LAB_08022bfa;
                      }
                      unaff_r4 = 0xd2;
                      if (language_0_CN_1_EN == '\0') {
                        unaff_r4 = 0xcb;
                      }
                    }
                    uVar5 = 0xb5;
                    goto LAB_08022bfa;
                  }
LAB_08022e78:
                  unaff_r4 = 0xe0;
                  if (language_0_CN_1_EN == '\0') {
                    unaff_r4 = 0xcd;
                  }
                }
                uVar5 = 0x9a;
                goto LAB_08022bfa;
              }
LAB_08022ec6:
              unaff_r4 = 0xf0;
            }
            uVar5 = 0x7f;
            goto LAB_08022bfa;
          }
          unaff_r4 = 0xeb;
        }
        break;
      }
LAB_08022f3c:
      unaff_r4 = 0xee;
      if (language_0_CN_1_EN == '\0') {
        unaff_r4 = 0xea;
      }
    }
    uVar5 = 0x49;
    goto LAB_08022bfa;
  case 0xc:
    settings_invert_lcd = '\x01';
    FUN_080262e4(1);
    goto switchD_08022e2c_default;
  }
  uVar5 = 100;
LAB_08022bfa:
  FUN_080265c0(0x6e,0x49,0x8c,7,0x228e);
  FUN_080265c0(0x6e,100,0x8c,7,0x228e);
  FUN_080265c0(0x6e,0x7f,0x8c,7,0x228e);
  FUN_080265c0(0x6e,0x9a,0x8c,7,0x228e);
  FUN_080265c0(0x6e,0xb5,0x8c,7,0x228e);
  zw_draw_element_16bpp(image_personalization_symbol_yellow_arrow,unaff_r4,uVar5);
  if (settings_grid_style_0_none_1_dot_2_line == '\x01') {
    unaff_r4 = 0x74;
  }
  else if (settings_grid_style_0_none_1_dot_2_line == '\x02') {
    unaff_r4 = 0xa2;
  }
  else if (settings_grid_style_0_none_1_dot_2_line == '\0') {
    unaff_r4 = 0xd7;
  }
  FUN_080265c0(0x74,0x3d,6,6,0x250);
  FUN_080265c0(0xa2,0x3d,6,6,0x250);
  FUN_080265c0(0xd7,0x3d,6,6,0x250);
  zw_draw_element_16bpp(image_personalization_symbol_red_check,unaff_r4,0x3d);
  if (settings_grid_color_0_dark_1_medium_2_light == '\0') {
    unaff_r4 = 0x74;
  }
  else if (settings_grid_color_0_dark_1_medium_2_light == '\x01') {
    unaff_r4 = 0xa2;
  }
  else if (settings_grid_color_0_dark_1_medium_2_light == '\x02') {
    unaff_r4 = 0xd7;
  }
  FUN_080265c0(0x74,0x58,6,6,0x250);
  FUN_080265c0(0xa2,0x58,6,6,0x250);
  FUN_080265c0(0xd7,0x58,6,6,0x250);
  zw_draw_element_16bpp(image_personalization_symbol_red_check,unaff_r4,0x58);
  if (settings_ch2_color_0_green_1_purple_2_cyan == '\0') {
    unaff_r4 = 0x80;
  }
  else if (settings_ch2_color_0_green_1_purple_2_cyan == '\x01') {
    unaff_r4 = 0xae;
  }
  else if (settings_ch2_color_0_green_1_purple_2_cyan == '\x02') {
    unaff_r4 = 0xe3;
  }
  FUN_080265c0(0x80,0x73,6,6,0x250);
  FUN_080265c0(0xae,0x73,6,6,0x250);
  FUN_080265c0(0xe3,0x73,6,6,0x250);
  zw_draw_element_16bpp(image_personalization_symbol_red_check,unaff_r4,0x73);
  if (settings_dmm_window_0_window_1_fullscreen == '\x01') {
    unaff_r4 = 0x5d;
  }
  else if (settings_dmm_window_0_window_1_fullscreen == '\0') {
    unaff_r4 = 0xba;
  }
  FUN_080265c0(0x5d,0x8e,6,6,0x250);
  FUN_080265c0(0xba,0x8e,6,6,0x250);
  zw_draw_element_16bpp(image_personalization_symbol_red_check,unaff_r4,0x8e);
  if (settings_invert_lcd == '\0') {
    unaff_r4 = 0x88;
  }
  else if (settings_invert_lcd == '\x01') {
    unaff_r4 = 0xc0;
  }
  FUN_080265c0(0x88,0xa9,6,6,0x250);
  FUN_080265c0(0xc0,0xa9,6,6,0x250);
  zw_draw_element_16bpp(image_personalization_symbol_red_check,unaff_r4,0xa9);
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_080233e8(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = buffer_pointer_ - buffer_trigger_index_;
  if (global_settings == 0) {
    if ((roll_mode_enable != '\0') && (block_mode_enable_ == '\0')) {
      uVar1 = (-1 < uVar1) * uVar1;
      goto LAB_08023410;
    }
  }
  else if ((roll_mode_enable != '\0') && (block_mode_enable_ == '\0')) {
    uVar1 = 0;
    goto LAB_08023410;
  }
  if (uVar1 < 0) {
    uVar1 = uVar1 + hw_buffer_wrap_addr_;
  }
  else if (hw_buffer_wrap_addr_ <= uVar1) {
    uVar1 = uVar1 - hw_buffer_wrap_addr_;
  }
LAB_08023410:
  if (ch2_enabled == '\x01') {
    uVar1 = uVar1 * 2;
  }
  uVar3 = ((roll_draw_cursor_x_ - roll_split_index_) + 1) * _global_settings;
  uVar2 = (uVar3 != (uVar3 / 6000) * 6000) + uVar3 / 6000;
  DAT_20004670 = _global_settings / uVar2;
  FUN_080173f4(&DAT_2001bb30,uVar1 & 0x7ffff,uVar3 / uVar2,0,uVar2);
  if (ch2_enabled == '\x01') {
    FUN_080173f4(&DAT_2001af78,uVar1 & 0x7ffff,uVar3 / uVar2,1,uVar2);
  }
  DAT_2001d29f = DAT_2001d29e;
  return;
}




void FUN_080234d4(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  float fVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  byte *pbVar16;
  int iVar17;
  uint uVar18;
  uint uVar19;
  int iVar20;
  
  fVar4 = DAT_20004670;
  bVar3 = false;
  iVar20 = DAT_20004670;
  uVar6 = 0xff;
  DAT_2001df20 = 0;
  DAT_20019ca4 = 0;
  DAT_20019ca5 = 0;
  uVar19 = 0;
  pbVar16 = &DAT_2001bb30;
  bVar2 = false;
  uVar18 = 0;
  uVar12 = 0;
  uVar13 = 0;
  uVar5 = 0xff;
  iVar15 = 0;
  iVar17 = 0;
  uVar14 = 0;
  do {
    uVar11 = ~*pbVar16;
    uVar8 = uVar11 - 0x1c;
    if ((uVar8 & 0xff) < 200) {
      bVar7 = (&DAT_2000a8cc)[iVar17 + uVar8 * 300] + 1;
      uVar9 = bVar7;
      (&DAT_2000a8cc)[iVar17 + uVar8 * 300] = bVar7;
      if (uVar12 < uVar9) goto LAB_0802357e;
LAB_08023538:
      uVar13 = (uVar13 < uVar11) * uVar11 + (uVar13 >= uVar11) * uVar13;
      uVar6 = (uVar6 < uVar11) * uVar6 + (uVar6 >= uVar11) * uVar11;
    }
    else {
      uVar9 = (&DAT_2000a8cc)[iVar17 + uVar8 * 300];
      if (uVar9 <= uVar12) goto LAB_08023538;
LAB_0802357e:
      bVar2 = true;
      uVar13 = (uVar13 < uVar11) * uVar11 + (uVar13 >= uVar11) * uVar13;
      uVar6 = (uVar6 < uVar11) * uVar6 + (uVar6 >= uVar11) * uVar11;
      uVar12 = uVar9;
    }
    uVar8 = uVar14;
    if (iVar20 == iVar15 + 1) {
      uVar8 = (uVar5 < uVar6) * uVar5 + (uVar5 >= uVar6) * uVar6 & 0xff;
      uVar5 = (uVar14 < uVar13) * uVar13 + (uVar14 >= uVar13) * uVar14 & 0xff;
      if (uVar8 + 1 < uVar5) {
        pcVar10 = &DAT_20008928 + iVar17 + uVar8 * 300;
        uVar13 = uVar8 - 0x1b;
        do {
          if (uVar13 < 200) {
            *pcVar10 = *pcVar10 + '\x01';
          }
          uVar6 = uVar13 + 0x1d;
          pcVar10 = pcVar10 + 300;
          uVar13 = uVar13 + 1;
        } while (uVar6 < uVar5);
      }
      bVar1 = uVar18 < uVar5;
      iVar20 = (iVar17 + 2) * fVar4;
      iVar17 = iVar17 + 1;
      uVar18 = uVar19;
      if (bVar1) {
        bVar3 = true;
        uVar18 = uVar5;
      }
      if (iVar17 == 300) {
        if (!bVar2) {
          uVar12 = DAT_2001df20;
        }
        DAT_2001df20 = uVar12;
        if (bVar3) {
          DAT_20019ca4 = uVar18;
          return;
        }
        return;
      }
      uVar6 = 0xff;
      uVar13 = 0;
      uVar19 = uVar18;
    }
    iVar15 = iVar15 + 1;
    pbVar16 = pbVar16 + 1;
    uVar14 = uVar8;
  } while( true );
}




void FUN_0802364c(void)

{
  byte bVar1;
  char *pcVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  char cVar6;
  uint uVar7;
  
  uVar4 = roll_draw_cursor_x_;
  if (uVar4 < 300) {
    if (DAT_2001df20 != 0) {
      if (DAT_2001df20 < 0x40) {
        cVar6 = 0x40 / DAT_2001df20;
      }
      else {
        DAT_2001df20 = 0x40;
        cVar6 = '\x01';
      }
      uVar7 = roll_split_index_;
      if (uVar7 <= uVar4) {
        do {
          pcVar2 = &DAT_2000a8cc + uVar7;
          pbVar3 = framebuffer_ + uVar7 + 0x168a;
          iVar5 = 200;
          do {
            if (*pcVar2 != '\0') {
              bVar1 = *pbVar3;
              *pbVar3 = (bVar1 < 0x60) * '`' + (bVar1 >= 0x60) * bVar1 + *pcVar2 * cVar6;
            }
            pcVar2 = pcVar2 + 300;
            pbVar3 = pbVar3 + 0x140;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
          uVar7 = uVar7 + 1 & 0x7fff;
        } while (uVar7 != (uVar4 + 1 & 0x7fff));
      }
    }
  }
  return;
}




void zw_siggen_waveform_gen(int waveform_pattern)

{
  ushort uVar1;
  undefined2 uVar2;
  double *pdVar3;
  undefined2 *puVar4;
  uint uVar5;
  undefined2 *puVar6;
  uint uVar7;
  undefined4 uVar8;
  ushort *puVar9;
  int iVar10;
  byte *pbVar11;
  int iVar12;
  short *psVar13;
  ushort *puVar14;
  uint uVar15;
  ushort in_stack_fffffde4;
  ushort uVar16;
  undefined6 in_stack_fffffde6;
  undefined2 local_11c [128];
  
  puVar9 = &stack0xfffffde4;
  puVar4 = &stack0xfffffde4;
  puVar6 = &stack0xfffffde4;
  psVar13 = &stack0xfffffde4;
  if (waveform_pattern == 0) {
    iVar12 = 1;
    uVar16 = 0x80;
    puVar14 = &stack0xfffffde6;
    if (true) {
      do {
        __floatunsidf(iVar12);
        __muldf3();
        pdVar3 = __muldf3();
        sin(pdVar3,CONCAT62(in_stack_fffffde6,uVar16));
        __muldf3();
        __adddf3();
        uVar1 = __fixunsdfsi();
        if (uVar1 < 0x100) {
          *puVar14 = uVar1;
        }
        else {
          *puVar14 = 0xff;
        }
        puVar14 = puVar14 + 1;
        iVar12 = iVar12 + 1;
      } while (iVar12 != 0x100);
    }
  }
  else if (waveform_pattern == 1) {
    uVar5 = 0;
    iVar12 = 0x100;
    do {
      uVar2 = 0xff;
      if ((siggen_duty_cycle_0_1_ << 8) / 1000 <= uVar5) {
        uVar2 = 0;
      }
      *(&stack0xfffffde4 + uVar5 * 2) = uVar2;
      uVar5 = uVar5 + 1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
  }
  else if (waveform_pattern == 2) {
    uVar15 = (siggen_duty_cycle_0_1_ << 8) / 1000;
    uVar5 = 0;
    iVar12 = 0x100;
    uVar7 = 0;
    do {
      if (uVar15 < uVar7) {
        *puVar4 = (0xff00 - uVar5) / (0x100 - uVar15);
      }
      else {
        *puVar4 = uVar5 / uVar15;
      }
      uVar7 = uVar7 + 1;
      uVar5 = uVar5 + 0xff;
      puVar4 = puVar4 + 1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
  }
  else if (waveform_pattern == 3) {
    iVar10 = 0;
    iVar12 = 0x100;
    do {
      *(&stack0xfffffde4 + iVar10 * 2) = iVar10;
      iVar10 = iVar10 + 1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
  }
  else if (waveform_pattern == 4) {
    pdVar3 = 0x0;
    uVar8 = 0;
    iVar12 = 0;
    while( true ) {
      __muldf3(pdVar3,uVar8,0,0x406fe000);
      uVar2 = __fixunsdfsi();
      *(&stack0xfffffde4 + iVar12 * 2) = uVar2;
      iVar12 = iVar12 + 1;
      if (iVar12 == 0x80) break;
      __floatunsidf(iVar12);
      __muldf3();
      pdVar3 = __muldf3();
      pdVar3 = sin(pdVar3,CONCAT62(in_stack_fffffde6,in_stack_fffffde4));
    }
    puVar4 = local_11c;
    iVar12 = 0x80;
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
  }
  else if (waveform_pattern == 5) {
    pdVar3 = 0x0;
    uVar8 = 0;
    iVar12 = 0;
    while( true ) {
      __muldf3(pdVar3,uVar8,0,0x406fe000);
      uVar2 = __fixunsdfsi();
      *(&stack0xfffffde4 + iVar12 * 2) = uVar2;
      iVar12 = iVar12 + 1;
      if (iVar12 == 0x80) break;
      __floatunsidf(iVar12);
      __muldf3();
      pdVar3 = __muldf3();
      pdVar3 = sin(pdVar3,CONCAT62(in_stack_fffffde6,in_stack_fffffde4));
    }
    pdVar3 = 0x0;
    puVar4 = local_11c;
    uVar8 = 0;
    iVar12 = 0;
    while( true ) {
      __muldf3(pdVar3,uVar8,0,0x406fe000);
      iVar12 = iVar12 + 1;
      uVar2 = __fixunsdfsi();
      *puVar4 = uVar2;
      puVar4 = puVar4 + 1;
      if (iVar12 == 0x80) break;
      __floatunsidf(iVar12);
      __muldf3();
      pdVar3 = __muldf3();
      pdVar3 = sin(pdVar3,CONCAT62(in_stack_fffffde6,in_stack_fffffde4));
    }
  }
  else if (waveform_pattern == 6) {
    pbVar11 = sinc_waveform_pattern;
    uVar8 = 0x2d;
    while( true ) {
      *puVar6 = uVar8;
      puVar6 = puVar6 + 1;
      if (pbVar11 == "%") break;
      uVar8 = *pbVar11;
      pbVar11 = pbVar11 + 1;
    }
  }
  else if (waveform_pattern == 7) {
    do {
      iVar12 = rand();
      *psVar13 = iVar12 + (iVar12 / 0xff) * -0xff;
      psVar13 = psVar13 + 1;
    } while (&stack0xffffffe4 != psVar13);
  }
  else if (waveform_pattern == 0xff) {
    memset(&stack0xfffffde4,0,0x200);
  }
  iVar12 = 0x100;
  do {
    if (siggen_amplitude_mV == 3010) {
      *puVar9 = (*puVar9 * 30) / 33;
    }
    else if (siggen_amplitude_mV != 3000) {
      if (siggen_amplitude_mV == 2510) {
        *puVar9 = (*puVar9 * 27) / 35;
      }
      else {
        *puVar9 = (*puVar9 * 26) / 30;
      }
    }
    puVar9 = puVar9 + 1;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  FUN_08016fb8(&stack0xfffffde4);
  return;
}




void zw_siggen_init(void)

{
  char cVar1;
  
  DAT_200046cc = 0x55;
  DAT_200046d0 = 0x57;
  DAT_200046d4 = image_signal_generator_window;
  DAT_200046dc = 0xffffffff;
  DAT_200046b0 = 0xffffffff;
  DAT_200046a0 = 0xd2;
  DAT_200046a4 = 0x2a;
  DAT_200046a8 = image_signal_generator_full_screen_frequency;
  DAT_200046c8 = 0xffffffff;
  DAT_200046b8 = 0x109;
  DAT_200046bc = 0x2d;
  DAT_200046c0 = image_signal_generator_full_screen_on_off;
  DAT_20004674 = 0xa0;
  DAT_20004676 = 0x7f;
  DAT_2000467c = image_signal_generator_waveform_sine_small;
  DAT_20004680 = 0;
  DAT_20004682 = 0x20;
  DAT_20004692 = 0x20;
  DAT_20004684 = 0x54;
  DAT_20004686 = 3;
  DAT_2000468c = image_signal_generator_scope_icon;
  DAT_20004690 = 5;
  zw_siggen_freq_duty(siggen_frequency_0_1hz,siggen_duty_cycle_0_1_);
  cVar1 = '\0';
  if (siggen_enable != '\0') {
    zw_siggen_waveform_gen(siggen_waveform_pattern);
    cVar1 = siggen_enable;
  }
  zw_siggen_enable_(cVar1);
  return;
}




void zw_siggen_related_FUN_08023a88(int param_1)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  
  if (param_1 == 0xf) {
    bVar2 = DAT_2001de01 & 0x21;
    if ((DAT_2001de01 & 0x21) == 0) {
      bVar1 = DAT_2001de01 & 4;
      DAT_2001de01 = bVar2;
      if (bVar1 == 0) {
        DAT_2001de01 = 4;
        bVar2 = DAT_2001de0d;
      }
      goto LAB_08023af8;
    }
    if ((DAT_2001de01 & 4) == 0) {
      return;
    }
    goto LAB_08023abe;
  }
  if (param_1 == 0x7e) {
    DAT_2001de0d = 1;
    DAT_2001de01 = 4;
    bVar2 = DAT_2001de0d;
LAB_08023af8:
    DAT_2001de0d = bVar2;
    DAT_200046e0 = 2;
    if (siggen_frequency_0_1hz < 10000) {
      DAT_200046b4 = 0;
      DAT_2000469c = siggen_frequency_0_1hz * 10;
    }
    else if (siggen_frequency_0_1hz < 10000000) {
      DAT_200046b4 = 1;
      DAT_2000469c = siggen_frequency_0_1hz / 100;
    }
    else {
      DAT_200046b4 = 2;
      DAT_2000469c = siggen_frequency_0_1hz / 100000;
    }
    DAT_20004694 = siggen_duty_cycle_0_1_;
    event_id = 0;
    return;
  }
  if (((DAT_2001de01 & 4) == 0) || (param_1 == 0)) {
    return;
  }
  if (param_1 == 3) {
    if (DAT_200046e0 == '\0') {
      DAT_200046e0 = '\b';
    }
    else {
      DAT_200046e0 = DAT_200046e0 + -1;
    }
LAB_08023abe:
    uVar3 = param_1 - 9;
  }
  else {
    if (param_1 == 4) {
      if (DAT_200046e0 == '\b') {
        DAT_200046e0 = '\0';
      }
      else {
        DAT_200046e0 = DAT_200046e0 + '\x01';
      }
      goto LAB_08023abe;
    }
    if (param_1 == 0xb) {
      switch(DAT_200046e0) {
      case '\0':
        if (DAT_2000469c < 90000) {
          DAT_2000469c = DAT_2000469c + 10000;
        }
        break;
      case '\x01':
        if (DAT_2000469c < 99000) {
          DAT_2000469c = DAT_2000469c + 1000;
        }
        break;
      case '\x02':
        if (DAT_2000469c < 0x1863c) {
          DAT_2000469c = DAT_2000469c + 100;
        }
        break;
      case '\x03':
        if (DAT_2000469c < 0x18696) {
          DAT_2000469c = DAT_2000469c + 10;
        }
        break;
      case '\x04':
        if (DAT_2000469c < 99999) {
          DAT_2000469c = DAT_2000469c + 1;
        }
        break;
      case '\x05':
        if (DAT_200046b4 != 0) {
          DAT_200046b4 = DAT_200046b4 + -1;
          break;
        }
        DAT_200046b4 = 2;
        goto LAB_08023c92;
      case '\x06':
        if (DAT_20004694 < 0x37b) {
          DAT_20004694 = DAT_20004694 + 100;
        }
        break;
      case '\a':
        if (DAT_20004694 < 0x3d5) {
          DAT_20004694 = DAT_20004694 + 10;
        }
        break;
      case '\b':
        if (DAT_20004694 < 0x3de) {
          DAT_20004694 = DAT_20004694 + 1;
        }
      }
switchD_08023bbc_default:
      if (DAT_200046b4 == 0) {
        siggen_frequency_0_1hz = ~(DAT_2000469c % 10 < 5) + DAT_2000469c / 10;
      }
      else {
        if (DAT_200046b4 == 1) goto LAB_08023ef0;
        if (DAT_200046b4 == 2) {
LAB_08023c92:
          siggen_frequency_0_1hz = DAT_2000469c * 100000;
        }
      }
    }
    else {
      if (param_1 == 0x13) {
        switch(DAT_200046e0) {
        case '\0':
          if (DAT_2000469c < 10000) break;
          DAT_2000469c = DAT_2000469c + -10000;
          goto LAB_08023db8;
        case '\x01':
          if (999 < DAT_2000469c) {
            DAT_2000469c = DAT_2000469c + -1000;
            goto LAB_08023db8;
          }
          break;
        case '\x02':
          if (99 < DAT_2000469c) {
            DAT_2000469c = DAT_2000469c + -100;
            goto LAB_08023db8;
          }
          break;
        case '\x03':
          if (9 < DAT_2000469c) {
            DAT_2000469c = DAT_2000469c + -10;
            goto LAB_08023db8;
          }
          break;
        case '\x04':
          if (0 < DAT_2000469c) {
            DAT_2000469c = DAT_2000469c + -1;
            goto LAB_08023db8;
          }
          break;
        case '\x05':
          if (DAT_200046b4 == 2) {
            DAT_200046b4 = 0;
          }
          else {
            DAT_200046b4 = DAT_200046b4 + 1;
          }
          break;
        case '\x06':
          if (99 < DAT_20004694) {
            DAT_20004694 = DAT_20004694 - 100;
          }
          break;
        case '\a':
          if (9 < DAT_20004694) {
            DAT_20004694 = DAT_20004694 - 10;
            break;
          }
LAB_08023e8c:
          if (DAT_2000469c < 0) goto LAB_08023e9e;
          goto LAB_08023e98;
        case '\b':
          if (DAT_20004694 < 1) goto LAB_08023e8c;
          DAT_20004694 = DAT_20004694 - 1;
        }
        if (DAT_2000469c < 0) {
LAB_08023e9e:
          DAT_2000469c = 0;
        }
LAB_08023db8:
        if (DAT_20004694 < 10) {
LAB_08023e98:
          DAT_20004694 = 10;
        }
        goto switchD_08023bbc_default;
      }
      if (param_1 != 0x12) {
        if (param_1 == 10) {
          siggen_enable = ~(siggen_enable != 0);
          zw_siggen_enable_();
          goto LAB_08023b56;
        }
        if (param_1 == 9) {
          if (siggen_waveform_pattern == '\a') {
            siggen_waveform_pattern = '\0';
          }
          else {
            siggen_waveform_pattern = siggen_waveform_pattern + '\x01';
          }
        }
        else {
          if (param_1 != 0x11) {
            if (param_1 == 2) {
              event_id = 0;
              DAT_2001de01 = 0;
              return;
            }
            goto LAB_08023abe;
          }
          if (siggen_waveform_pattern == '\0') {
            siggen_waveform_pattern = '\a';
          }
          else {
            siggen_waveform_pattern = siggen_waveform_pattern + -1;
          }
        }
        goto switchD_08023bbc_default;
      }
      DAT_2000469c = 100;
      DAT_20004694 = 500;
      DAT_200046b4 = 1;
LAB_08023ef0:
      siggen_frequency_0_1hz = DAT_2000469c * 100;
    }
    if (siggen_waveform_pattern == '\0') {
      if (50000000 < siggen_frequency_0_1hz) {
        DAT_2000469c = 500;
        siggen_frequency_0_1hz = 50000000;
      }
    }
    else if (20000000 < siggen_frequency_0_1hz) {
      DAT_2000469c = 200;
      siggen_frequency_0_1hz = 20000000;
    }
    if (DAT_20004694 < 0x3df) {
      siggen_duty_cycle_0_1_ = DAT_20004694;
      if (DAT_20004694 < 10) {
        siggen_duty_cycle_0_1_ = 10;
      }
    }
    else {
      siggen_duty_cycle_0_1_ = 0x3de;
    }
    zw_siggen_freq_duty(siggen_frequency_0_1hz,siggen_duty_cycle_0_1_);
    if ((param_1 - 9U & 0xff) < 2) goto LAB_08023b56;
    uVar3 = param_1 - 0x11;
  }
  if (1 < (uVar3 & 0xff)) {
    if ((param_1 != 0xb) && (param_1 != 0x13)) {
      event_id = 0;
      return;
    }
    if (2 < DAT_200046e0 - 6U) {
      event_id = 0;
      return;
    }
  }
LAB_08023b56:
  if (siggen_enable == 0) {
    zw_siggen_waveform_gen(0xff);
  }
  else {
    zw_siggen_waveform_gen(siggen_waveform_pattern);
  }
  event_id = 0;
  return;
}




void zw_scope_siggen_window(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  ushort local_3c [4];
  undefined2 uStack_34;
  undefined2 uStack_30;
  undefined2 uStack_2e;
  undefined2 uStack_2c;
  
  if (siggen_enable == '\0') {
    DAT_20004690 = 0xb;
  }
  else {
    DAT_20004690 = 5;
  }
  zw_draw_element(&DAT_20004684);
  if ((DAT_2001de01 & 4) == 0) {
    return;
  }
  DAT_200046d8 = 1 << (DAT_200046b4 + 0x10U & 0x3f) | 1 << (DAT_200046e0 & 0x3f);
  zw_draw_ParametrizedGlyph(&DAT_200046cc);
  iVar2 = DAT_2000469c;
  iVar1 = DAT_20004694;
  uVar4 = 0;
  iVar3 = 9;
  do {
    local_3c[uVar4] = (uVar4 & 0xff) != DAT_200046e0;
    uVar4 = uVar4 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  zw_siggen_7_segment_digits(DAT_2000469c / 10000 & 0xff,DAT_200046cc + 3U & 0xffff,DAT_200046d0 + 6U & 0xffff,local_3c[0],0x20,0);
  zw_siggen_7_segment_digits((iVar2 % 10000) / 1000 & 0xff,DAT_200046cc + 0x19U & 0xffff,DAT_200046d0 + 6U & 0xffff,local_3c[1],0x20,0);
  zw_siggen_7_segment_digits((iVar2 % 1000) / 100 & 0xff,DAT_200046cc + 0x2fU & 0xffff,DAT_200046d0 + 6U & 0xffff,local_3c[2],0x20,0);
  zw_siggen_7_segment_digits((iVar2 % 100) / 10 & 0xff,DAT_200046cc + 0x4bU & 0xffff,DAT_200046d0 + 6U & 0xffff,local_3c[3],0x20,0);
  zw_siggen_7_segment_digits(iVar2 % 10 & 0xff,DAT_200046cc + 0x62U & 0xffff,DAT_200046d0 + 6U & 0xffff,uStack_34,0x20,0);
  zw_siggen_7_segment_digits(iVar1 / 100 & 0xff,DAT_200046cc + 3U & 0xffff,DAT_200046d0 + 0x2aU & 0xffff,uStack_30,0x20,1);
  zw_siggen_7_segment_digits((iVar1 % 100) / 10 & 0xff,DAT_200046cc + 0xfU & 0xffff,DAT_200046d0 + 0x2aU & 0xffff,uStack_2e,0x20,1);
  zw_siggen_7_segment_digits(iVar1 % 10 & 0xff,DAT_200046cc + 0x1fU & 0xffff,DAT_200046d0 + 0x2aU & 0xffff,uStack_2c,0x20,1);
  if (siggen_waveform_pattern == '\0') {
    DAT_2000467c = image_signal_generator_waveform_sine_small;
  }
  else if (siggen_waveform_pattern == '\x01') {
    DAT_2000467c = image_signal_generator_waveform_square_small;
  }
  else if (siggen_waveform_pattern == '\x02') {
    DAT_2000467c = image_signal_generator_waveform_triangle_small;
  }
  else if (siggen_waveform_pattern == '\x03') {
    DAT_2000467c = image_signal_generator_waveform_sawtooth_small;
  }
  else if (siggen_waveform_pattern == '\x04') {
    DAT_2000467c = image_signal_generator_waveform_halfwave_small;
  }
  else if (siggen_waveform_pattern == '\x05') {
    DAT_2000467c = image_signal_generator_waveform_fullwave_small;
  }
  else if (siggen_waveform_pattern == '\x06') {
    DAT_2000467c = image_signal_generator_waveform_sinc_small;
  }
  else if (siggen_waveform_pattern == '\a') {
    DAT_2000467c = image_signal_generator_waveform_noise_small;
  }
  zw_draw_element(&DAT_20004674);
  if (siggen_enable != '\0') {
    zw_draw_string_small("ON",DAT_200046cc + 0x7dU & 0xffff,DAT_200046d0 + 0x2dU & 0xffff,2,0,3);
    return;
  }
  zw_draw_string_small("OFF",DAT_200046cc + 0x79U & 0xffff,DAT_200046d0 + 0x2dU & 0xffff,3,0,2);
  return;
}




uint zw_siggen_related_FUN_08024208(uint param_1)

{
  if (DAT_2001de0d == '\0') {
    return param_1;
  }
  if (param_1 == 0xf) {
    DAT_2001de01 = 0;
    DAT_2001de0d = 0;
    return 0;
  }
  if (param_1 == 0x7e) {
    DAT_2001de0d = 1;
    DAT_2001de01 = 4;
    DAT_200046e0 = 2;
    if (siggen_frequency_0_1hz < 10000) {
      DAT_200046b4 = 0;
      DAT_2000469c = siggen_frequency_0_1hz * 10;
    }
    else if (siggen_frequency_0_1hz < 10000000) {
      DAT_200046b4 = 1;
      DAT_2000469c = siggen_frequency_0_1hz / 100;
    }
    else {
      DAT_200046b4 = 2;
      DAT_2000469c = siggen_frequency_0_1hz / 100000;
    }
    DAT_20004694 = siggen_duty_cycle_0_1_;
    event_id = 0;
    return 0;
  }
  if (param_1 == 0) {
    return 0;
  }
  if (param_1 == 3) {
    DAT_20004698 = 0;
    if (DAT_200046e0 == 10) {
      if (siggen_waveform_pattern == '\x01') goto LAB_08024678;
      DAT_200046e0 = 6;
    }
    else if (DAT_200046e0 == 0) {
      DAT_200046e0 = 0x11;
    }
    else {
LAB_08024678:
      DAT_200046e0 = DAT_200046e0 - 1;
    }
LAB_08024262:
    if ((param_1 & 0xfd) != 9) goto LAB_080244b8;
  }
  else {
    if (param_1 == 4) {
      DAT_20004698 = 0;
      if (DAT_200046e0 == 6) {
        if (siggen_waveform_pattern == '\x01') goto LAB_080244dc;
        DAT_200046e0 = 10;
      }
      else if (DAT_200046e0 == 0x11) {
        DAT_200046e0 = 0;
      }
      else {
LAB_080244dc:
        DAT_200046e0 = DAT_200046e0 + 1;
      }
      goto LAB_08024262;
    }
    if (param_1 == 0xb) {
      switch(DAT_200046e0) {
      case 0:
        if (DAT_2000469c < 90000) {
          DAT_2000469c = DAT_2000469c + 10000;
        }
        break;
      case 1:
        if (DAT_2000469c < 99000) {
          DAT_2000469c = DAT_2000469c + 1000;
        }
        break;
      case 2:
        if (DAT_2000469c < 0x1863c) {
          DAT_2000469c = DAT_2000469c + 100;
        }
        break;
      case 3:
        if (DAT_2000469c < 0x18696) {
          DAT_2000469c = DAT_2000469c + 10;
        }
        break;
      case 4:
        if (DAT_2000469c < 99999) {
          DAT_2000469c = DAT_2000469c + 1;
        }
        break;
      case 5:
        if (DAT_200046b4 == 0) {
          DAT_200046b4 = 2;
        }
        else {
          DAT_200046b4 = DAT_200046b4 + -1;
        }
        break;
      case 6:
        siggen_enable = ~(siggen_enable != 0);
        break;
      case 7:
        if (DAT_20004694 < 0x37b) {
          DAT_20004694 = DAT_20004694 + 100;
        }
        break;
      case 8:
        if (DAT_20004694 < 0x3d5) {
          DAT_20004694 = DAT_20004694 + 10;
        }
        break;
      case 9:
        if (DAT_20004694 < 0x3de) {
          DAT_20004694 = DAT_20004694 + 1;
        }
        break;
      default:
        if (DAT_200046e0 - 10 < 4) {
          DAT_200046e0 = 2;
        }
        else if (DAT_200046e0 - 0xe < 4) {
          DAT_200046e0 = DAT_200046e0 - 4;
        }
      }
      goto LAB_08024270;
    }
    if (param_1 != 0x13) {
      if (param_1 == 0x12) {
        DAT_2000469c = 100;
        DAT_20004694 = 500;
        DAT_200046b4 = 1;
      }
      else {
        if (param_1 != 10) {
          if (param_1 == 9) {
            if (siggen_waveform_pattern == '\a') {
              siggen_waveform_pattern = '\0';
            }
            else {
              siggen_waveform_pattern = siggen_waveform_pattern + '\x01';
            }
          }
          else {
            if (param_1 == 0x11) {
              if (siggen_waveform_pattern == '\0') {
                siggen_waveform_pattern = '\a';
              }
              else {
                siggen_waveform_pattern = siggen_waveform_pattern + -1;
              }
              goto LAB_080244b8;
            }
            if (param_1 != 2) goto LAB_08024262;
            if (DAT_200046e0 == 6) {
              siggen_enable = ~(siggen_enable != 0);
            }
            else if (9 < DAT_200046e0) {
              siggen_waveform_pattern = DAT_200046e0 - 10;
            }
          }
          goto LAB_08024270;
        }
        siggen_enable = ~(siggen_enable != 0);
        zw_siggen_enable_();
      }
      goto LAB_080244b8;
    }
    switch(DAT_200046e0) {
    case 0:
      if (DAT_2000469c < 10000) break;
      DAT_2000469c = DAT_2000469c + -10000;
      goto LAB_0802453c;
    case 1:
      if (999 < DAT_2000469c) {
        DAT_2000469c = DAT_2000469c + -1000;
        goto LAB_0802453c;
      }
      break;
    case 2:
      if (99 < DAT_2000469c) {
        DAT_2000469c = DAT_2000469c + -100;
        goto LAB_0802453c;
      }
      break;
    case 3:
      if (9 < DAT_2000469c) {
        DAT_2000469c = DAT_2000469c + -10;
        goto LAB_0802453c;
      }
      break;
    case 4:
      if (0 < DAT_2000469c) {
        DAT_2000469c = DAT_2000469c + -1;
        goto LAB_0802453c;
      }
      break;
    case 5:
      if (DAT_200046b4 == 2) {
        DAT_200046b4 = 0;
      }
      else {
        DAT_200046b4 = DAT_200046b4 + 1;
      }
      break;
    case 6:
      siggen_enable = ~(siggen_enable != 0);
      break;
    case 7:
      if (99 < DAT_20004694) {
        DAT_20004694 = DAT_20004694 - 100;
      }
      break;
    case 8:
      if (9 < DAT_20004694) {
        DAT_20004694 = DAT_20004694 - 10;
        break;
      }
LAB_08024680:
      if (DAT_2000469c < 0) goto LAB_080246d6;
      goto LAB_0802468c;
    case 9:
      if (DAT_20004694 < 1) goto LAB_08024680;
      DAT_20004694 = DAT_20004694 - 1;
    }
    if (DAT_2000469c < 0) {
LAB_080246d6:
      DAT_2000469c = 0;
    }
LAB_0802453c:
    if (DAT_20004694 < 10) {
LAB_0802468c:
      DAT_20004694 = 10;
    }
    if (DAT_200046e0 - 10 < 4) {
      DAT_200046e0 = DAT_200046e0 + 4;
    }
    else if (DAT_200046e0 - 0xe < 4) {
      DAT_200046e0 = 2;
    }
LAB_080244b8:
    if (2 < (param_1 - 0x11 & 0xff)) {
      if (param_1 != 10) {
        return 0;
      }
      goto LAB_080242d0;
    }
  }
LAB_08024270:
  if (DAT_200046b4 == 0) {
    siggen_frequency_0_1hz = ~(DAT_2000469c % 10 < 5) + DAT_2000469c / 10;
  }
  else if (DAT_200046b4 == 1) {
    siggen_frequency_0_1hz = DAT_2000469c * 100;
  }
  else if (DAT_200046b4 == 2) {
    siggen_frequency_0_1hz = DAT_2000469c * 100000;
  }
  if (siggen_waveform_pattern == '\0') {
    if (100000000 < siggen_frequency_0_1hz) {
      DAT_2000469c = 1000;
      siggen_frequency_0_1hz = 100000000;
    }
  }
  else if (20000000 < siggen_frequency_0_1hz) {
    DAT_2000469c = 200;
    siggen_frequency_0_1hz = 20000000;
  }
  if (DAT_20004694 < 0x3df) {
    siggen_duty_cycle_0_1_ = DAT_20004694;
    if (DAT_20004694 < 10) {
      siggen_duty_cycle_0_1_ = 10;
    }
  }
  else {
    siggen_duty_cycle_0_1_ = 0x3de;
  }
  zw_siggen_freq_duty(siggen_frequency_0_1hz,siggen_duty_cycle_0_1_);
  if (param_1 < 0x13) {
    if ((0x60604U >> (param_1 & 0x3f) & 1) != 0) goto LAB_080242d0;
    if (param_1 != 0xb) goto LAB_080242be;
  }
  else {
LAB_080242be:
    if (param_1 != 0x13) {
      return 0;
    }
  }
  if (2 < DAT_200046e0 - 6) {
    return 0;
  }
LAB_080242d0:
  if (siggen_enable != 0) {
    zw_siggen_waveform_gen(siggen_waveform_pattern);
    return 0;
  }
  zw_siggen_waveform_gen(0xff);
  return 0;
}




void zw_siggen_fullscreen(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined2 uVar6;
  int iVar7;
  short asStack_30 [4];
  byte *pbStack_28;
  undefined2 uStack_24;
  undefined2 uStack_22;
  
  if (DAT_2001de0d == '\0') {
    return;
  }
  memset(framebuffer_,0,0x12c00);
  FUN_080254c0();
  FUN_08029f44();
  uStack_24 = 1;
  uStack_22 = 0x20;
  asStack_30[0] = 0x6a;
  asStack_30[1] = 9;
  pbStack_28 = image_signal_generator_full_screen_title_label;
  zw_draw_element(asStack_30);
  zw_draw_line_horizontal(0,0x1e,0x140,8);
  zw_draw_line_horizontal(0,0x1f,0x140,8);
  iVar1 = DAT_2000469c;
  iVar7 = DAT_2000469c % 10000;
  uVar2 = zw_siggen_chars_32x53(DAT_2000469c / 10000 & 0xff,10,0x2e,5,0x20);
  uVar2 = zw_siggen_chars_32x53(iVar7 / 1000 & 0xff,uVar2,0x2e,5,0x20);
  uVar2 = zw_siggen_chars_32x53((iVar1 % 1000) / 100 & 0xff,uVar2,0x2e,5,0x20);
  uVar2 = zw_siggen_chars_32x53(0x2e,uVar2,0x2e,5,0x20);
  uVar2 = zw_siggen_chars_32x53((iVar1 % 100) / 10 & 0xff,uVar2,0x2e,5,0x20);
  zw_siggen_chars_32x53(iVar1 % 10 & 0xff,uVar2,0x2e,5,0x20);
  uVar2 = 5;
  if (siggen_waveform_pattern != '\x01') {
    uVar2 = 0x20;
  }
  zw_siggen_7_segment_digits(DAT_20004694 / 100 & 0xff,0x14,0x78,uVar2,0x20,1);
  zw_siggen_7_segment_digits((DAT_20004694 % 100) / 10 & 0xff,0x20,0x78,uVar2,0x20,1);
  zw_draw_string_large(".",0x2c,0x78,1,uVar2,0x20);
  zw_siggen_7_segment_digits(DAT_20004694 % 10 & 0xff,0x30,0x78,uVar2,0x20,1);
  zw_draw_string_large("%",0x3d,0x78,1,uVar2,0x20);
  DAT_200046ac = 1 << (DAT_200046b4 & 0x3f);
  zw_draw_ParametrizedGlyph(&DAT_200046a0);
  if (siggen_enable == '\0') {
    DAT_200046c4 = 2;
  }
  else {
    DAT_200046c4 = 1;
  }
  zw_draw_ParametrizedGlyph(&DAT_200046b8);
  uVar5 = DAT_200046e0;
  if (uVar5 < 3) {
    uVar3 = DAT_200046e0 * 0x22 + 0xe;
    uVar2 = 0x6b;
    uVar4 = 0x18;
  }
  else {
    if (uVar5 == 3) {
      uVar3 = 0x8a;
    }
    else if (uVar5 == 4) {
      uVar3 = 0xac;
    }
    else if (uVar5 == 5) {
      uVar3 = DAT_200046a0 + 8;
    }
    else {
      if (uVar5 != 6) {
        if (uVar5 == 7) {
          uVar3 = 0x15;
        }
        else if (uVar5 == 8) {
          uVar3 = 0x21;
        }
        else {
          if (uVar5 != 9) {
            if (uVar5 < 0xe) {
              uVar3 = (uVar5 - 10) * 0x45 + 0x2c;
            }
            else if (uVar5 < 0x12) {
              uVar3 = (uVar5 - 0xe) * 0x45 + 0x2c;
            }
            else {
              uVar3 = 0xe;
            }
            if (uVar5 < 0xe) {
              uVar2 = 0xc2;
            }
            else {
              uVar2 = 0;
              if (uVar5 < 0x12) {
                uVar2 = 0xeb;
              }
            }
            uVar4 = 0x18;
            goto LAB_08024938;
          }
          uVar3 = 0x31;
        }
        uVar2 = 0x89;
        uVar4 = 10;
        goto LAB_08024938;
      }
      uVar3 = DAT_200046b8 + 0xd;
    }
    uVar2 = 0x6b;
    uVar4 = 0x18;
  }
LAB_08024938:
  DAT_20004698 = DAT_20004698 + 1;
  if (((DAT_20004698 & 0x1f) < 0x10) || (0x80 < DAT_20004698)) {
    zw_draw_rectangle_filled(uVar3 & 0xffff,uVar2,uVar4,2,3);
  }
  asStack_30[1] = 0xa0;
  uVar6 = 5;
  uStack_24 = 2;
  if (siggen_waveform_pattern != 0) {
    uStack_24 = 5;
  }
  pbStack_28 = image_signal_generator_waveform_sine_large;
  uStack_22 = 0x20;
  asStack_30[0] = 0x20;
  zw_draw_element(asStack_30);
  asStack_30[0] = asStack_30[0] + 0x45;
  uStack_24 = 2;
  if (siggen_waveform_pattern != 1) {
    uStack_24 = 5;
  }
  pbStack_28 = image_signal_generator_waveform_square_large;
  zw_draw_element(asStack_30);
  asStack_30[0] = asStack_30[0] + 0x45;
  uStack_24 = 2;
  if (siggen_waveform_pattern != 2) {
    uStack_24 = 5;
  }
  pbStack_28 = image_signal_generator_waveform_triangle_large;
  zw_draw_element(asStack_30);
  asStack_30[0] = asStack_30[0] + 0x45;
  uStack_24 = 2;
  if (siggen_waveform_pattern != 3) {
    uStack_24 = 5;
  }
  pbStack_28 = image_signal_generator_waveform_sawtooth_large;
  zw_draw_element(asStack_30);
  asStack_30[1] = 0xc9;
  uStack_24 = 2;
  if (siggen_waveform_pattern != 4) {
    uStack_24 = 5;
  }
  pbStack_28 = image_signal_generator_waveform_halfwave_large;
  asStack_30[0] = 0x20;
  zw_draw_element(asStack_30);
  asStack_30[0] = asStack_30[0] + 0x45;
  uStack_24 = 2;
  if (siggen_waveform_pattern != 5) {
    uStack_24 = 5;
  }
  pbStack_28 = image_signal_generator_waveform_fullwave_large;
  zw_draw_element(asStack_30);
  asStack_30[0] = asStack_30[0] + 0x45;
  uStack_24 = 2;
  if (siggen_waveform_pattern != 6) {
    uStack_24 = 5;
  }
  pbStack_28 = image_signal_generator_waveform_sinc_large;
  zw_draw_element(asStack_30);
  asStack_30[0] = asStack_30[0] + 0x45;
  if (siggen_waveform_pattern == 7) {
    uVar6 = 2;
  }
  pbStack_28 = image_signal_generator_waveform_noise_large;
  uStack_24 = uVar6;
  zw_draw_element(asStack_30);
  zw_draw_flush_offscreen();
  return;
}




void FUN_08024b68(void)

{
  DAT_20004718 = 1000000;
  DAT_2000471c = 0;
  DAT_20004720 = 0xd2;
  DAT_20004722 = 0x18;
  DAT_20004724._0_2_ = 5;
  DAT_20004724._2_2_ = 0;
  DAT_20004728._0_2_ = 6;
  DAT_2000472c._0_1_ = 1;
  DAT_20004728._3_1_ = 1;
  zw_timer_us(&DAT_200046f4,300000);
  zw_timer_us(&DAT_20004708,1500000);
  zw_timer_us(&DAT_200046e8,50000);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Restarted to delay deadcode elimination for space: register


void zw_scope_frequency_meter(void)

{
  longlong lVar1;
  longlong lVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  uint unaff_r6;
  int unaff_r7;
  
  if (frequency_meter_enable == '\x03') {
    frequency_meter_enable = '\x01';
    iVar4 = (DAT_2001df1e + DAT_2001df1f) / 2;
    uVar8 = DAT_2001df1e - DAT_2001df1f;
    if ((uVar8 & 0x80000000) != 0) {
      uVar8 = uVar8 + 3;
    }
    FUN_08016f1c(iVar4 + (uVar8 >> 2) & 0xff,iVar4 - (uVar8 >> 2) & 0xff);
    FUN_08016d18();
  }
  uVar8 = DAT_20004738;
  iVar4 = DAT_2000473c;
  lVar1 = CONCAT44(DAT_2000471c,DAT_20004718);
  if (frequency_meter_enable != '\0') {
    zw_draw_rectangle_filled(DAT_20004720 + -0x1b,DAT_20004722 + -4,0x7b,0x18);
    zw_draw_string_large("F:",DAT_20004720 + -0x17,DAT_20004722,2);
    zw_scope_int_values(DAT_20004718,DAT_2000471c,_DAT_20004720,DAT_20004724);
    FUN_08027850((_DAT_20004720 & 0xffff) - 0x1d,(_DAT_20004720 >> 0x10) - 6,0x7f,0x1c);
    FUN_08027850((_DAT_20004720 & 0xffff) - 0x1c,(_DAT_20004720 >> 0x10) - 5,0x7d,0x1a);
    iVar3 = FUN_080270a8(&DAT_200046f4);
    uVar8 = DAT_20004738;
    iVar4 = DAT_2000473c;
    lVar1 = CONCAT44(DAT_2000471c,DAT_20004718);
    if ((iVar3 != 0) && (lVar1 = CONCAT44(DAT_2000471c,DAT_20004718), global_settings == 1)) {
      if (DAT_2001df1e - DAT_2001df1f < 0x14) {
        lVar1 = 1;
      }
      else {
        iVar4 = FUN_08016d38(&DAT_20004700);
        if (iVar4 == 0) {
          iVar3 = FUN_080270a8(&DAT_20004708);
          lVar1 = CONCAT44(DAT_2000471c,DAT_20004718);
          uVar8 = DAT_20004738;
          iVar4 = DAT_2000473c;
          if (iVar3 != 0) {
            iVar4 = (DAT_2001df1e + DAT_2001df1f) / 2;
            uVar8 = DAT_2001df1e - DAT_2001df1f;
            if ((uVar8 & 0x80000000) != 0) {
              uVar8 = uVar8 + 3;
            }
            FUN_08016f1c((uVar8 >> 2) + iVar4 & 0xff,iVar4 - (uVar8 >> 2) & 0xff);
            FUN_08016d18();
            DAT_20004718 = 1;
            DAT_2000471c = 0;
            DAT_20004730 = 1;
            DAT_20004734 = 0;
            printf_disabled_1("freq_hz timeout\n");
            lVar1 = CONCAT44(DAT_2000471c,DAT_20004718);
            uVar8 = DAT_20004738;
            iVar4 = DAT_2000473c;
          }
        }
        else {
          zw_timer_us(&DAT_20004708,1500000);
          iVar3 = (DAT_2001df1e + DAT_2001df1f) / 2;
          uVar8 = DAT_2001df1e - DAT_2001df1f;
          if ((uVar8 & 0x80000000) != 0) {
            uVar8 = uVar8 + 3;
          }
          uVar5 = iVar3 + (uVar8 >> 2) & 0xff;
          uVar8 = iVar3 - (uVar8 >> 2) & 0xff;
          if (uVar5 - uVar8 < 5) {
            uVar5 = uVar8 + 5 & 0xff;
          }
          FUN_08016f1c(uVar5);
          FUN_08016d18();
          uVar8 = freq_meter_ref_clock_hz;
          if (iVar4 == 2) {
            DAT_20004730 = 1;
            DAT_20004734 = 0;
            DAT_20004738 = 1;
            DAT_2000473c = 0;
            DAT_20004740 = 1;
            DAT_20004744 = 0;
          }
          else {
            unaff_r6 = DAT_20004700;
            unaff_r7 = DAT_20004704;
            if (freq_meter_ref_clock_hz - 0x9882f9 < 9999) {
              if ((DAT_20004704 < 1) && ((DAT_20004704 != 0 || (DAT_20004700 < 0x4876e801)))) {
                uVar6 = freq_meter_ref_clock_hz * DAT_20004700;
                unaff_r7 = (freq_meter_ref_clock_hz * DAT_20004700 >> 0x20) + DAT_20004704 * freq_meter_ref_clock_hz;
                uVar7 = 10000000;
              }
              else {
                iVar4 = DAT_20004704;
                uVar5 = __divdi3(DAT_20004700,DAT_20004704,10000,0);
                lVar1 = uVar5 * uVar8;
                uVar6 = lVar1;
                unaff_r7 = (lVar1 >> 0x20) + iVar4 * uVar8;
                uVar7 = 1000;
              }
              unaff_r6 = __divdi3(uVar6,unaff_r7,uVar7,0);
            }
          }
          iVar4 = DAT_20004734;
          uVar8 = DAT_20004730;
          if ((DAT_20004734 < unaff_r7) || ((unaff_r7 == DAT_20004734 && (DAT_20004730 < unaff_r6)))) {
            lVar1 = CONCAT44(unaff_r7,unaff_r6) - CONCAT44(DAT_20004734,DAT_20004730);
          }
          else {
            lVar1 = CONCAT44(DAT_20004734,DAT_20004730) - CONCAT44(unaff_r7,unaff_r6);
          }
          iVar3 = unaff_r7;
          uVar5 = __divdi3(unaff_r6,unaff_r7,10000,0);
          lVar2 = CONCAT44(iVar3,uVar5);
          DAT_20004730 = unaff_r6;
          DAT_20004734 = unaff_r7;
          if ((lVar1 <= lVar2) && ((true || (lVar1 <= uVar5)))) {
            if ((DAT_2000473c < unaff_r7) || ((unaff_r7 == DAT_2000473c && (DAT_20004738 < unaff_r6)))) {
              lVar1 = CONCAT44(unaff_r7,unaff_r6) - CONCAT44(DAT_2000473c,DAT_20004738);
            }
            else {
              lVar1 = CONCAT44(DAT_2000473c,DAT_20004738) - CONCAT44(unaff_r7,unaff_r6);
            }
            if ((lVar1 <= lVar2) && ((true || (lVar1 <= uVar5)))) {
              if ((DAT_20004744 < unaff_r7) || ((unaff_r7 == DAT_20004744 && (DAT_20004740 < unaff_r6)))) {
                lVar1 = CONCAT44(unaff_r7,unaff_r6) - CONCAT44(DAT_20004744,DAT_20004740);
              }
              else {
                lVar1 = CONCAT44(DAT_20004744,DAT_20004740) - CONCAT44(unaff_r7,unaff_r6);
              }
              if ((lVar1 <= lVar2) && ((true || (lVar1 <= uVar5)))) {
                lVar1 = CONCAT44(unaff_r7,unaff_r6) + CONCAT44(iVar4,uVar8) + CONCAT44(DAT_2000473c,DAT_20004738) + CONCAT44(DAT_20004744,DAT_20004740);
                if (lVar1 < 0) {
                  lVar1 = lVar1 + 3;
                }
                lVar1 = lVar1 >> 2;
                DAT_20004740 = DAT_20004738;
                DAT_20004744 = DAT_2000473c;
                goto LAB_08024be0;
              }
            }
          }
          lVar1 = CONCAT44(unaff_r7,unaff_r6);
          uVar8 = unaff_r6;
          iVar4 = unaff_r7;
          DAT_20004740 = unaff_r6;
          DAT_20004744 = unaff_r7;
        }
      }
    }
  }
LAB_08024be0:
  DAT_2000473c = iVar4;
  DAT_20004738 = uVar8;
  DAT_2000471c = lVar1 >> 0x20;
  DAT_20004718 = lVar1;
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void FUN_08024f0c(void)

{
  longlong lVar1;
  int iVar2;
  
  lVar1 = CONCAT44(DAT_20004704,DAT_20004700) + -0x3b9328e1;
  if (lVar1 >> 0x20 == 0) {
    if (lVar1 < 999999) {
      iVar2 = __divdi3(0,0x2386f2,DAT_20004700,DAT_20004704);
      freq_meter_ref_clock_hz = iVar2 + 1;
      printf_disabled_1("sysParm.freq_calib_val=%d\n");
      return;
    }
  }
  return;
}




void FUN_08024f5c(int param_1)

{
  int iVar1;
  ushort uVar2;
  ushort uVar3;
  
  if (frequency_meter_enable == '\x04') {
    frequency_meter_enable = 3;
    counter_enable = 0;
    return;
  }
  if (counter_enable == '\x04') {
    counter_enable = 1;
    frequency_meter_enable = 0;
    uVar3 = trigger_level_raw_adc__0_255 & 0xff;
    DAT_20004714 = ~(global_settings != 1);
    uVar2 = trigger_level_raw_adc__0_255 - 10;
    if ((trigger_level_raw_adc__0_255 - 10 & 0x80000000U) != 0) {
      uVar2 = 0;
    }
    ch1_trigger_level_10uV_target_h = ch1_volt_scale_10uV >> 0x1f;
    ch1_trigger_level_10uV_target_l = ch1_volt_scale_10uV;
    zw_set_scope_parameters_();
    FUN_08016f1c(uVar3,uVar2 & 0xff);
    FUN_08016cf0(DAT_20004714);
    FUN_08016ce0();
    return;
  }
  if (param_1 == 10) {
    DAT_20004714 = global_settings != 1;
    FUN_08016cf0();
    if (counter_enable == '\0') {
      return;
    }
  }
  else {
    if (counter_enable == '\0') {
      return;
    }
    if (param_1 == 0) {
      iVar1 = FUN_080270a8(&DAT_200046e8);
      if (iVar1 == 0) {
        return;
      }
      goto LAB_08024fd2;
    }
  }
  uVar2 = trigger_level_raw_adc__0_255 - 5;
  if ((trigger_level_raw_adc__0_255 - 5 & 0x80000000U) != 0) {
    uVar2 = 0;
  }
  FUN_08016f1c(trigger_level_raw_adc__0_255 & 0xff,uVar2 & 0xff);
  iVar1 = FUN_080270a8(&DAT_200046e8);
  if (iVar1 == 0) {
    return;
  }
LAB_08024fd2:
  DAT_200046e4 = FUN_08016d0c();
  return;
}




void zw_scope_counter(void)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  undefined1 auStack_18 [9];
  char local_f [3];
  
  if (counter_enable != '\0') {
    zw_draw_rectangle_filled(0xb2,0x14,0x8a,0x1c,0);
    FUN_08027850(0xb0,0x12,0x8e,0x20);
    FUN_08027850(0xb1,0x13,0x8c,0x1e);
    zw_draw_string_large("C:",0xb6,0x18,2,5,0);
    if (DAT_200046e4 < 2000000000) {
      pcVar1 = local_f;
      iVar2 = 10;
      uVar3 = DAT_200046e4;
      do {
        *pcVar1 = uVar3 + (uVar3 / 10) * -10 + '0';
        pcVar1 = pcVar1 + -1;
        iVar2 = iVar2 + -1;
        uVar3 = uVar3 / 10;
      } while (iVar2 != 0);
      zw_draw_string_large(auStack_18,0xcd,0x18,10,5,0);
      return;
    }
    zw_draw_string_large("1999999999+",0xcd,0x18,0xb,5,0);
  }
  return;
}




void FUN_080250f0(uint param_1,undefined1 *param_2,undefined1 *param_3,undefined1 *param_4)

{
  if (499999 < param_1) {
    param_1 = param_1 / 0x32;
  }
  if (param_1 == 40000) {
    *param_4 = 0;
    *param_3 = 1;
    *param_2 = 0;
    return;
  }
  if (param_1 < 0x9c41) {
    if (param_1 == 10000) {
      *param_4 = 0;
      *param_3 = 0;
      *param_2 = 0;
      return;
    }
    if (param_1 == 20000) {
      *param_4 = 0;
      *param_3 = 0;
      *param_2 = 1;
      return;
    }
  }
  else {
    if (param_1 == 100000) {
      *param_4 = 1;
      *param_3 = 0;
      *param_2 = 0;
      return;
    }
    if (param_1 == 200000) {
      *param_4 = 1;
      *param_3 = 0;
      *param_2 = 1;
      return;
    }
  }
  *param_4 = 0;
  *param_3 = 1;
  *param_2 = 1;
  return;
}




void zw_HAL_Init_(void)

{
  zw_HAL_MspInit_();
  zw_timer_us(&DAT_20004750,20000);
  return;
}




void FUN_08025194(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_2 >> 0x14;
  uVar1 = __udivdi3(param_2 << 0xc,uVar2,3300000,0);
  if ((uVar2 != 0) || (0xfff < uVar1)) {
    uVar1 = 0xfff;
  }
  uVar3 = param_1 >> 0x14;
  uVar2 = __udivdi3(param_1 << 0xc,uVar3,3300000,0);
  if ((uVar3 != 0) || (0xfff < uVar2)) {
    uVar2 = 0xfff;
  }
  zw_SPI_Transmit__FUN_080267ac(0x13,uVar1 << 0xc | uVar2);
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void FUN_080251e4(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  iVar2 = ch1_vert_offset_10uV_h;
  uVar1 = ch1_vert_offset_10uV_l;
  if (ch1_volt_scale_10uV < 100000) {
    uVar3 = 100000 / ch1_volt_scale_10uV;
    uVar4 = uVar3 * ch1_vert_offset_10uV_l;
    iVar5 = (uVar3 * ch1_vert_offset_10uV_l >> 0x20) + ch1_vert_offset_10uV_h * uVar3 + (uVar3 >> 0x1f) * ch1_vert_offset_10uV_l;
  }
  else {
    iVar5 = ch1_vert_offset_10uV_h;
    uVar4 = __divdi3(ch1_vert_offset_10uV_l,ch1_vert_offset_10uV_h,ch1_volt_scale_10uV / 100000,ch1_volt_scale_10uV / 100000 >> 0x1f);
  }
  if ((system_status_ != '\x05') && ((uVar3 = DAT_2000a8b4, 0 < iVar2 || (((iVar2 == 0 && (uVar1 != 0)) || (uVar3 = DAT_2000a8bc, uVar1 != 0 || iVar2 != 0))))))
  {
    uVar4 = __divdi3(uVar3 * uVar4,(uVar3 * uVar4 >> 0x20) + uVar3 * iVar5,1000,0);
  }
  DAT_20004748 = (&DAT_2000a834)[ch1_v_div_index] + uVar4;
  FUN_08025194(DAT_20004748,DAT_2000474c);
  return;
}




void FUN_08025290(void)

{
  undefined4 local_10;
  undefined4 uStack_c;
  
  FUN_08025888(~(ch2_enabled != '\x01'));
  local_10 = CONCAT31(local_10._1_3_,~(ch1_coupling_0_dc_1_ac != '\x01'));
  FUN_080250f0(ch1_volt_scale_10uV,&local_10 + 2,&local_10 + 3,&uStack_c);
  local_10._0_2_ = CONCAT11(499999 < ch1_volt_scale_10uV,local_10);
  FUN_080258b0(local_10,uStack_c);
  FUN_080251e4();
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void FUN_080252e4(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  iVar2 = ch2_vert_offset_10uV_h;
  uVar1 = ch2_vert_offset_10uV_l;
  if (ch2_volt_scale_10uV < 100000) {
    uVar3 = 100000 / ch2_volt_scale_10uV;
    uVar4 = uVar3 * ch2_vert_offset_10uV_l;
    iVar5 = (uVar3 * ch2_vert_offset_10uV_l >> 0x20) + ch2_vert_offset_10uV_h * uVar3 + (uVar3 >> 0x1f) * ch2_vert_offset_10uV_l;
  }
  else {
    iVar5 = ch2_vert_offset_10uV_h;
    uVar4 = __divdi3(ch2_vert_offset_10uV_l,ch2_vert_offset_10uV_h,ch2_volt_scale_10uV / 100000,ch2_volt_scale_10uV / 100000 >> 0x1f);
  }
  if ((system_status_ != '\x05') && ((uVar3 = DAT_2000a8b8, 0 < iVar2 || (((iVar2 == 0 && (uVar1 != 0)) || (uVar3 = DAT_2000a8c0, uVar1 != 0 || iVar2 != 0))))))
  {
    uVar4 = __divdi3(uVar3 * uVar4,(uVar3 * uVar4 >> 0x20) + uVar3 * iVar5,1000,0);
  }
  DAT_2000474c = (&DAT_2000a834)[ch2_v_div_index + 0xe] + uVar4;
  FUN_08025194(DAT_20004748,DAT_2000474c);
  return;
}




void FUN_0802539c(void)

{
  undefined4 local_10;
  undefined4 uStack_c;
  
  local_10 = CONCAT31(local_10._1_3_,~(ch2_coupling_dc_ac != '\x01'));
  FUN_080250f0(ch2_volt_scale_10uV,&local_10 + 2,&local_10 + 3,&uStack_c);
  local_10._0_2_ = CONCAT11(499999 < ch2_volt_scale_10uV,local_10);
  FUN_080258f4(local_10,uStack_c);
  FUN_080252e4();
  return;
}




void HAL_FLASH_Read_Offset_0x96000(uint32_t addr,uint8_t *buf,uint32_t len)

{
  HAL_FLASH_Read(addr + 0x96000,buf,len);
  return;
}




void HAL_FLASH_Write_Offset_0x96000(uint32_t addr,uint8_t *buf,uint32_t len)

{
  HAL_FLASH_Write(addr + 0x96000,buf,len);
  return;
}




void FUN_08025410(void)

{
  undefined4 uStack_10;
  
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioB_data,0,1,2);
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,2,0,2,uStack_10);
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,0x80,0,2,uStack_10);
  hadc = 0x200;
  DAT_2001df38 = 500;
  DAT_2001df34 = 0;
  HAL_ADC_Init(&hadc);
  zw_timer_us(&DAT_20004760,200);
  DAT_2001df28 = 0;
  DAT_2000476e = 8;
  DAT_2000476c = 3;
  return;
}




void FUN_080254a0(int param_1)

{
  if (param_1 == 0) {
    zw_clear_bits(&peripheral_gpioB_data,0);
    return;
  }
  zw_set_bits(&peripheral_gpioB_data,0);
  return;
}




void FUN_080254c0(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_080270a8(&DAT_20004760);
  if (iVar1 != 0) {
    uVar2 = peripheral_gpioA_data;
    DAT_2001de13 = uVar2 >> 7 & 1;
    DAT_2001df28 = DAT_2001df28 + 1;
    if ((DAT_2001df28 == 0x708) && (auto_off_enable != 0)) {
      zw_save_settings_(0x1000);
      zw_power_on(100);
      HAL_Delay(100);
      zw_clear_bits(&peripheral_gpioB_data,0);
    }
    iVar1 = HAL_ADC_GET_INPUT_VOLTAGE(&hadc);
    DAT_2000475c = DAT_2000475c + 1;
    DAT_2001df2c = DAT_2001df2c + iVar1;
    if (4 < DAT_2000475c) {
      zw_timer_us(&DAT_20004760,500000);
      uVar2 = (DAT_2001df2c * 2) / 5 + 0x50;
      uVar2 = uVar2 / 100 + (0x32 < uVar2 % 100);
      DAT_2000475c = 0;
      DAT_2001df2c = 0;
      printf_disabled_1("batValue keyAdcVal= %d %d \r\n",uVar2,iVar1);
      if (uVar2 < 0x20) {
        zw_draw_rectangle_filled(0,0,0x140,0xf0,0);
        zw_draw_rectangle_filled(0x6e,0x5d,100,0x32,1);
        zw_draw_rectangle_filled(0xd2,0x6a,8,0x18,1);
        zw_draw_rectangle_filled(0x6f,0x5e,5,0x30,2);
        zw_draw_flush_offscreen();
        HAL_Delay(0x5dc);
        zw_clear_bits(&peripheral_gpioB_data,0);
        printf_disabled_1("Low power..\r\n");
      }
      else if (uVar2 == 0x20) {
        DAT_2000476e = 2;
        DAT_2000476c = 2;
      }
      else if (uVar2 < 0x23) {
        DAT_2000476e = 4;
        DAT_2000476c = 9;
      }
      else {
        if (uVar2 < 0x28) {
          if (uVar2 == 0x27) {
            DAT_2000476e = 0xf;
          }
          else if (uVar2 == 0x26) {
            DAT_2000476e = 0xd;
          }
          else if (uVar2 == 0x25) {
            DAT_2000476e = 0xb;
          }
          else if (uVar2 == 0x24) {
            DAT_2000476e = 8;
          }
          else {
            DAT_2000476e = 6;
          }
        }
        else {
          DAT_2000476e = 0x10;
        }
        DAT_2000476c = 3;
      }
    }
  }
  return;
}




void FUN_08025680(void)

{
  DAT_2001df24 = DAT_2001df24 + 1;
  if ((DAT_2000476e == 2) && ((DAT_2001df24 & 8) != 0)) {
    zw_draw_rectangle_filled(0x122,4,0x16,8,0);
    return;
  }
  zw_draw_rectangle_filled(0x123,5,0x11,6,1);
  zw_draw_rectangle_filled(0x123,5,DAT_2000476e,6,DAT_2000476c);
  return;
}




undefined4 FUN_080256e8(void)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  uVar1 = peripheral_gpioA_data;
  if ((uVar1 & 0x40) != 0) {
    uVar2 = 3;
  }
  return uVar2;
}




void FUN_08025700(void)

{
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,0x40,0,2);
  return;
}




void FUN_0802571c(uint param_1)

{
  uint uVar1;
  int iVar2;
  
  zw_clear_bits(&peripheral_gpioA_data,0x1000);
  iVar2 = 3;
  do {
    uVar1 = 0;
    do {
      if ((0x80 >> (uVar1 & 0x3f) & param_1) == 0) {
        zw_clear_bits(&peripheral_gpioB_data,4);
      }
      else {
        zw_set_bits(&peripheral_gpioB_data,4);
      }
      zw_clear_bits(&peripheral_gpioB_data,8);
      uVar1 = uVar1 + 1;
      zw_set_bits(&peripheral_gpioB_data,8);
    } while (uVar1 != 8);
    iVar2 = iVar2 + -1;
    param_1 = param_1 >> 8;
  } while (iVar2 != 0);
  zw_clear_bits(&peripheral_gpioB_data,8);
  zw_set_bits(&peripheral_gpioA_data,0x1000);
  FUN_08027028(800);
  zw_clear_bits(&peripheral_gpioA_data,0x1000);
  return;
}




void zw_HAL_MspInit_(void)

{
  undefined4 uStack_1c;
  
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioB_data,8);
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioB_data,4,1,2,uStack_1c);
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,0x1000,1,2,uStack_1c);
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,0x30,0,2,uStack_1c);
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioB_data,0,0,2,uStack_1c);
  zw_clear_bits(&peripheral_gpioB_data,8);
  zw_clear_bits(&peripheral_gpioB_data,4);
  zw_clear_bits(&peripheral_gpioA_data,0x1000);
  zw_timer_us(&DAT_2000477c,15000);
  zw_timer_us(&DAT_2000479c,15000);
  DAT_20004774 = DAT_20004774 & 0xffff7fbf;
  FUN_0802571c();
  return;
}




void zw_bw_limit_(int ch1_limit_enable,int ch2_limit_enable)

{
  DAT_20004774 = DAT_20004774 & 0xffff7fbf;
  if (ch1_limit_enable != 0) {
    DAT_20004774 = DAT_20004774 | 0x40;
  }
  if (ch2_limit_enable != 0) {
    DAT_20004774 = DAT_20004774 | 0x8000;
  }
  FUN_0802571c(DAT_20004774);
  return;
}




void FUN_08025888(int param_1)

{
  if (param_1 != 0) {
    DAT_20004774 = DAT_20004774 & 0xffffff7f;
    FUN_0802571c();
    return;
  }
  DAT_20004774 = DAT_20004774 | 0x80;
  FUN_0802571c();
  return;
}




void FUN_080258b0(uint param_1,uint param_2)

{
  DAT_20004774 = (param_1 & 0xff) * 2 | (param_1 >> 8 & 0xff) << 2 | (param_1 >> 0x10 & 0xff) << 3 | (param_1 >> 0x18) << 4 | (param_2 & 0xff) << 5 |
                 DAT_20004774 & 0xffffffc1;
  FUN_0802571c();
  return;
}




void FUN_080258f4(uint param_1,uint param_2)

{
  DAT_20004774 = (param_1 & 0xff) << 9 | (param_1 >> 8 & 0xff) << 10 | (param_1 >> 0x10 & 0xff) << 0xb | (param_1 >> 0x18) << 0xc | (param_2 & 0xff) << 0xd |
                 DAT_20004774 & 0xffffc1ff;
  FUN_0802571c();
  return;
}




void FUN_08025938(int param_1)

{
  if (param_1 == 0) {
    DAT_20004774 = DAT_20004774 & 0xfffffbff;
    FUN_0802571c();
    return;
  }
  DAT_20004774 = DAT_20004774 | 0x400;
  FUN_0802571c();
  return;
}




void zw_power_off(void)

{
  if (DAT_2001de04 == '\0') {
    zw_save_settings_(0x1000);
  }
  FUN_0802571c(0);
  FUN_080254a0(0);
  zw_lcd_set_pwm(1);
  HAL_Delay(10);
  zw_lcd_set_pwm(0);
  zw_draw_rectangle_filled(0,0,0x140,0xf0,0);
  zw_draw_flush_offscreen();
  zw_power_control_(0);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}




uint FUN_080259b8(void)

{
  uint uVar1;
  
  uVar1 = peripheral_gpioB_data;
  return uVar1 >> 0x15 & 1;
}




uint zw_keypress_scan(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = peripheral_gpioA_data;
  if (((uVar2 & 0x30) == 0) && (iVar3 = FUN_080256e8(), iVar3 == 0)) {
    return 0;
  }
  iVar3 = 0;
  do {
    FUN_0802571c();
    FUN_08027040(10);
    uVar2 = peripheral_gpioA_data;
    if ((uVar2 & 0x20) != 0) {
      uVar2 = 0;
LAB_08025a10:
      FUN_0802571c();
      return uVar2 + 2 + iVar3 & 0xff;
    }
    if ((uVar2 & 0x10) != 0) {
      uVar2 = 8;
      goto LAB_08025a10;
    }
    iVar1 = FUN_080256e8();
    if (iVar1 != 0) {
      uVar2 = (iVar1 + 0x1fffffff) * 8 & 0xff;
      goto LAB_08025a10;
    }
    iVar3 = iVar3 + 1;
    if (iVar3 == 8) {
      FUN_0802571c();
      return 0;
    }
  } while( true );
}




void zw_keypress_handler(void)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  byte bVar4;
  
  iVar3 = FUN_080270a8(&DAT_2000477c);
  if (iVar3 == 0) {
    return;
  }
  if ((DAT_2001ddbb != '\0') && (iVar3 = FUN_080270a8(&DAT_2000478c), iVar3 != 0)) {
    DAT_2001ddbb = '\0';
  }
  cVar2 = DAT_20004779;
  if (DAT_20004779 != '\x01') {
    if (DAT_20004779 == '\0') {
      iVar3 = zw_keypress_scan();
      key_raw = iVar3;
      if (iVar3 != 0) {
        keypress_hold_counter_ = cVar2;
        DAT_20004779 = 1;
        DAT_2001df28 = 0;
        return;
      }
      DAT_20004770 = 1;
      force_fine_movement_ = 1;
      DAT_20004798 = 0;
      return;
    }
    if (DAT_20004779 == '\x02') {
      keypress_hold_counter_ = keypress_hold_counter_ + 1;
      if (keypress_hold_counter_ < 3) {
        return;
      }
      DAT_20004779 = 0;
      return;
    }
    if (DAT_20004779 != '\x03') {
      return;
    }
    uVar1 = peripheral_gpioA_data;
    if ((uVar1 & 0x30) != 0) {
      return;
    }
    iVar3 = FUN_080256e8();
    if (iVar3 == 0) {
      DAT_20004779 = 0;
      return;
    }
    return;
  }
  bVar4 = keypress_hold_counter_ + 1;
  uVar1 = peripheral_gpioA_data;
  iVar3 = 1;
  keypress_hold_counter_ = bVar4;
  if ((uVar1 & 0x20) == 0) {
    if ((uVar1 & 0x10) != 0) {
      iVar3 = 2;
      goto LAB_08025ada;
    }
    iVar3 = FUN_080256e8();
    if ((DAT_2001de01 == '\0') && (system_status_ == '\x01')) goto LAB_08025ae8;
  }
  else {
LAB_08025ada:
    if ((DAT_2001de01 != '\0') || (system_status_ != '\x01')) goto LAB_08025b7e;
LAB_08025ae8:
    if ((key_raw < 0x14) && ((~(0x818U >> (key_raw & 0x3f)) & 1) == 0)) {
      DAT_20004779 = 0;
      if (false) {
        keypress_with_short_long_flag = key_raw;
      }
      else {
        keypress_with_short_long_flag = key_raw + 0x40;
      }
      DAT_2001ddbb = 1;
      zw_timer_us(&DAT_2000478c,800000);
      DAT_20004798 = DAT_20004798 + '\x01';
      if (DAT_20004798 == '\n') {
        force_fine_movement_ = 0;
      }
      if (DAT_20004770 == '\0') {
        return;
      }
      zw_power_on(0x14);
      DAT_20004770 = 0;
      return;
    }
  }
  if (iVar3 == 0) {
    DAT_20004779 = 2;
    if (false) {
      keypress_with_short_long_flag = key_raw;
    }
    else {
      keypress_with_short_long_flag = key_raw + 0x40;
    }
    zw_power_on(0x32);
    return;
  }
LAB_08025b7e:
  if (bVar4 < 0x2e) {
    return;
  }
  DAT_20004779 = 3;
  bVar4 = key_raw;
  if (true) {
    bVar4 = key_raw + 0x40;
  }
  keypress_with_short_long_flag = bVar4 | 0x80;
  zw_power_on(0x50);
  return;
}




void zw_power_button_handler_(void)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_080270a8(&DAT_2000479c);
  cVar1 = DAT_2000479a;
  if (iVar2 != 0) {
    if (DAT_2000479a == '\x01') {
      DAT_20004799 = DAT_20004799 + 1;
      if (true) {
        iVar2 = zw_keypress_scan();
        if (iVar2 != 0) {
          DAT_2000479a = 3;
          return;
        }
        if (DAT_20004799 < 0x1f) {
          return;
        }
        DAT_2000479a = 3;
        keypress_with_short_long_flag = 0x81;
        zw_power_on(0x50);
        DAT_20004799 = 0;
        zw_power_off();
      }
      else {
        iVar2 = zw_keypress_scan();
        if ((DAT_20004799 < 0x1e) && (iVar2 == 0)) {
          DAT_2000479a = 2;
          keypress_with_short_long_flag = cVar1;
          zw_power_on(0x32);
          DAT_20004799 = 0;
          return;
        }
      }
      DAT_2000479a = 2;
      return;
    }
    if (DAT_2000479a == '\0') {
      if (true) {
        DAT_20004799 = 0;
        DAT_2000479a = 1;
        return;
      }
    }
    else {
      if (DAT_2000479a == '\x02') {
        DAT_20004799 = DAT_20004799 + 1;
        if (DAT_20004799 < 3) {
          return;
        }
      }
      else {
        if (DAT_2000479a != '\x03') {
          return;
        }
        if (true) {
          return;
        }
      }
      DAT_2000479a = '\0';
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


uint zw_button_event(void)

{
  uint uVar1;
  
  uVar1 = keypress_with_short_long_flag;
  keypress_with_short_long_flag = 0;
  if (uVar1 == 0) {
    keypress_with_short_long_flag = 0;
    return 0;
  }
  if (RTAuto_enable_ != '\0') {
    RTAuto_enable_ = 0;
    return 0;
  }
  if (uVar1 == 2) {
    if (DAT_2001de01 != '\0') {
      keypress_with_short_long_flag = 0;
      return 2;
    }
    if (system_status_ != '\x01') {
      keypress_with_short_long_flag = 0;
      return 2;
    }
    if (DAT_2001de0c != '\0') {
      keypress_with_short_long_flag = 0;
      return 2;
    }
    if (DAT_2001de0a == '\0') {
      if (shift_key_ == '\0') {
        keypress_with_short_long_flag = 0;
        return 0x20;
      }
      keypress_with_short_long_flag = 0;
      shift_key_ = 0;
      return 0x60;
    }
    keypress_with_short_long_flag = 0;
    return 2;
  }
  if (_DAT_2001de0c != 0) {
    keypress_with_short_long_flag = 0;
    shift_key_ = 0;
    return uVar1;
  }
  if (uVar1 == 0xb) {
    if ((DAT_2001de01 != '\0') || (system_status_ != '\x01')) goto LAB_08025d70;
    if (DAT_2001ddc9 != '\0') {
      keypress_with_short_long_flag = 0;
      return 0x23;
    }
    if (cursors_y_enable == '\0') {
      if (shift_key_ == '\0') {
        if (active_channel_0_ch1_1_ch2_2_math == '\0') {
          keypress_with_short_long_flag = 0;
          return 0x21;
        }
        if (active_channel_0_ch1_1_ch2_2_math == '\x01') {
          keypress_with_short_long_flag = 0;
          return 0x23;
        }
        keypress_with_short_long_flag = 0;
        return 0x31;
      }
      uVar1 = 0x27;
      if (trigger_source_0_ch1_1_ch2 == '\0') {
        uVar1 = 0x25;
      }
    }
    else {
      if (shift_key_ == '\0') {
        keypress_with_short_long_flag = 0;
        return 0x29;
      }
      uVar1 = 0x2d;
    }
  }
  else {
    if (uVar1 == 0x13) {
      if ((DAT_2001de01 == '\0') && (system_status_ == '\x01')) {
        if (DAT_2001ddc9 != '\0') {
          keypress_with_short_long_flag = 0;
          return 0x24;
        }
        if (cursors_y_enable == '\0') {
          if (shift_key_ == '\0') {
            if (active_channel_0_ch1_1_ch2_2_math == '\0') {
              keypress_with_short_long_flag = 0;
              return 0x22;
            }
            if (active_channel_0_ch1_1_ch2_2_math == '\x01') {
              keypress_with_short_long_flag = 0;
              return 0x24;
            }
            keypress_with_short_long_flag = 0;
            return 0x32;
          }
          uVar1 = 0x28;
          if (trigger_source_0_ch1_1_ch2 == '\0') {
            uVar1 = 0x26;
          }
        }
        else {
          if (shift_key_ == '\0') {
            keypress_with_short_long_flag = 0;
            return 0x2a;
          }
          uVar1 = 0x2e;
        }
        goto LAB_08025df2;
      }
    }
    else if (uVar1 == 3) {
      if ((DAT_2001de01 == '\0') && (system_status_ == '\x01')) {
        if (DAT_2001ddc9 != '\0') {
          keypress_with_short_long_flag = 0;
          return 0x22;
        }
        if (cursors_x_enable == '\0') {
          keypress_with_short_long_flag = 0;
          return 3;
        }
        if (shift_key_ == '\0') {
          keypress_with_short_long_flag = 0;
          return 0x2b;
        }
        uVar1 = 0x2f;
        goto LAB_08025df2;
      }
    }
    else if (uVar1 == 4) {
      if ((DAT_2001de01 == '\0') && (system_status_ == '\x01')) {
        if (DAT_2001ddc9 != '\0') {
          keypress_with_short_long_flag = 0;
          return 0x21;
        }
        if (cursors_x_enable == '\0') {
          keypress_with_short_long_flag = 0;
          return 4;
        }
        if (shift_key_ == '\0') {
          keypress_with_short_long_flag = 0;
          return 0x2c;
        }
        uVar1 = 0x30;
        goto LAB_08025df2;
      }
    }
    else if (uVar1 == 0xc) {
      if (system_status_ != '\x01') {
        keypress_with_short_long_flag = 0;
        shift_key_ = 0;
        return 0xc;
      }
      keypress_with_short_long_flag = 0;
      shift_key_ = ~(shift_key_ != '\0');
      return 0xc;
    }
LAB_08025d70:
    if (shift_key_ == '\0') {
      keypress_with_short_long_flag = 0;
      return uVar1;
    }
    uVar1 = uVar1 + 0x40 & 0xff;
    if (system_status_ != '\x01') goto LAB_08025d82;
  }
LAB_08025df2:
  if (0x16 < (uVar1 - 0x42 & 0xff)) {
    keypress_with_short_long_flag = 0;
    return uVar1;
  }
  if ((0x7df9f9U >> (uVar1 - 0x42 & 0x3f) & 1) == 0) {
    keypress_with_short_long_flag = 0;
    return uVar1;
  }
LAB_08025d82:
  if (DAT_2001de0a == '\0') {
    shift_key_ = 0;
    return uVar1;
  }
  keypress_with_short_long_flag = 0;
  return uVar1;
}




void FUN_08025f20(uint param_1)

{
  peripheral_gpioB_data = param_1;
  peripheral_gpioB_data = param_1 | 0x40000;
  peripheral_gpioB_data = param_1;
  return;
}




void FUN_08025f44(void)

{
  zw_clear_bits(&peripheral_gpioB_data,0);
  DAT_200047a8 = peripheral_gpioB_data;
  return;
}




void FUN_08025f64(void)

{
  zw_set_bits(&peripheral_gpioB_data,0);
  return;
}




void zw_draw_sendPixelColorToDisplay(uint rgb)

{
  peripheral_gpioB_data = rgb;
  peripheral_gpioB_data = rgb | 0x40000;
  return;
}




void FUN_08025f98(void)

{
  peripheral_gpioB_data = 0xfe;
  peripheral_gpioB_data = 0xfe;
  peripheral_gpioB_data = 0x44400fe;
  peripheral_gpioB_data = 0xef;
  peripheral_gpioB_data = 0xef;
  peripheral_gpioB_data = 0x44400ef;
  peripheral_gpioB_data = 0x36;
  peripheral_gpioB_data = 0x36;
  peripheral_gpioB_data = 0x4440036;
  peripheral_gpioB_data = 100;
  peripheral_gpioB_data = 0x440064;
  peripheral_gpioB_data = 0x4440064;
  peripheral_gpioB_data = 0x3a;
  peripheral_gpioB_data = 0x3a;
  peripheral_gpioB_data = 0x444003a;
  peripheral_gpioB_data = 0x400005;
  peripheral_gpioB_data = 5;
  peripheral_gpioB_data = 5;
  if (settings_invert_lcd == '\0') {
    peripheral_gpioB_data = 0x21;
    peripheral_gpioB_data = 0x21;
    peripheral_gpioB_data = 0x4440021;
  }
  else {
    peripheral_gpioB_data = 0x20;
    peripheral_gpioB_data = 0x40020;
    peripheral_gpioB_data = 0x20;
  }
  peripheral_gpioB_data = 0x2a;
  peripheral_gpioB_data = 0x2a;
  peripheral_gpioB_data = 0x444002a;
  peripheral_gpioB_data = 0x400000;
  peripheral_gpioB_data = 0x440000;
  peripheral_gpioB_data = 0;
  peripheral_gpioB_data = 0x400000;
  peripheral_gpioB_data = 0x440000;
  peripheral_gpioB_data = 0;
  peripheral_gpioB_data = 0x400001;
  peripheral_gpioB_data = 0x440001;
  peripheral_gpioB_data = 0x4440001;
  peripheral_gpioB_data = 0x3f;
  peripheral_gpioB_data = 0x44003f;
  peripheral_gpioB_data = 0x444003f;
  peripheral_gpioB_data = 0x2b;
  peripheral_gpioB_data = 0x2b;
  peripheral_gpioB_data = 0x444002b;
  peripheral_gpioB_data = 0x400000;
  peripheral_gpioB_data = 0x440000;
  peripheral_gpioB_data = 0;
  peripheral_gpioB_data = 0x400000;
  peripheral_gpioB_data = 0x440000;
  peripheral_gpioB_data = 0;
  peripheral_gpioB_data = 0x400000;
  peripheral_gpioB_data = 0x440000;
  peripheral_gpioB_data = 0;
  peripheral_gpioB_data = 0xef;
  peripheral_gpioB_data = 0x4400ef;
  peripheral_gpioB_data = 0x44400ef;
  peripheral_gpioB_data = 0x13;
  peripheral_gpioB_data = 0x40013;
  peripheral_gpioB_data = 0x13;
  peripheral_gpioB_data = 0x34;
  peripheral_gpioB_data = 0x34;
  peripheral_gpioB_data = 0x4440034;
  peripheral_gpioB_data = 0x11;
  peripheral_gpioB_data = 0x40011;
  peripheral_gpioB_data = 0x11;
  HAL_Delay(0x78);
  peripheral_gpioB_data = 0x29;
  peripheral_gpioB_data = 0x29;
  peripheral_gpioB_data = 0x4440029;
  return;
}




void FUN_08026294(void)

{
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioB_data,0xffffffff,1,0);
  HAL_Delay(0x32);
  zw_set_bits(&peripheral_gpioB_data,0);
  zw_set_bits(&peripheral_gpioB_data,0);
  zw_set_bits(&peripheral_gpioB_data,0);
  HAL_Delay(10);
  FUN_08025f98();
  return;
}




void FUN_080262e4(int param_1)

{
  if (param_1 == 0) {
    peripheral_gpioB_data = 0x21;
    peripheral_gpioB_data = 0x21;
    peripheral_gpioB_data = 0x4440021;
    return;
  }
  peripheral_gpioB_data = 0x20;
  peripheral_gpioB_data = 0x40020;
  peripheral_gpioB_data = 0x20;
  return;
}




void zw_draw_setActiveDisplayRect(uint param_1,uint positionY,int param_3,int height)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = (height + positionY) - 1;
  uVar3 = (param_3 + param_1) - 1;
  peripheral_gpioB_data = 0x2a;
  peripheral_gpioB_data = 0x2a;
  peripheral_gpioB_data = 0x444002a;
  uVar1 = param_1 >> 8;
  peripheral_gpioB_data = uVar1 | 0x400000;
  peripheral_gpioB_data = uVar1 | 0x440000;
  peripheral_gpioB_data = uVar1;
  param_1 = param_1 & 0xff;
  peripheral_gpioB_data = param_1 | 0x400000;
  peripheral_gpioB_data = param_1 | 0x440000;
  peripheral_gpioB_data = param_1;
  uVar1 = (uVar3 & 0x7fffff) >> 8;
  peripheral_gpioB_data = uVar1 | 0x400000;
  peripheral_gpioB_data = uVar1 | 0x440000;
  peripheral_gpioB_data = uVar1;
  uVar3 = uVar3 & 0x7f;
  peripheral_gpioB_data = uVar3 | 0x400000;
  peripheral_gpioB_data = uVar3 | 0x440000;
  peripheral_gpioB_data = uVar3;
  peripheral_gpioB_data = 0x2b;
  peripheral_gpioB_data = 0x2b;
  peripheral_gpioB_data = 0x444002b;
  uVar3 = positionY >> 8;
  peripheral_gpioB_data = uVar3 | 0x400000;
  peripheral_gpioB_data = uVar3 | 0x440000;
  peripheral_gpioB_data = uVar3;
  positionY = positionY & 0xff;
  peripheral_gpioB_data = positionY | 0x400000;
  peripheral_gpioB_data = positionY | 0x440000;
  peripheral_gpioB_data = positionY;
  uVar3 = (uVar2 & 0x7fffff) >> 8;
  peripheral_gpioB_data = uVar3 | 0x400000;
  peripheral_gpioB_data = uVar3 | 0x440000;
  peripheral_gpioB_data = uVar3;
  uVar2 = uVar2 & 0x7f;
  peripheral_gpioB_data = uVar2 | 0x400000;
  peripheral_gpioB_data = uVar2 | 0x440000;
  peripheral_gpioB_data = uVar2;
  return;
}




void FUN_080264d0(undefined4 param_1,undefined4 param_2,uint param_3,uint param_4)

{
  uint uVar1;
  
  zw_draw_setActiveDisplayRect();
  peripheral_gpioB_data = 0x2c;
  peripheral_gpioB_data = 0x2c;
  peripheral_gpioB_data = 0x444002c;
  zw_clear_bits(&peripheral_gpioB_data,0);
  DAT_200047a8 = peripheral_gpioB_data;
  if (param_3 != 0) {
    uVar1 = 0;
    do {
      uVar1 = uVar1 + 1 & 0xffff;
      peripheral_gpioB_data = param_4;
      peripheral_gpioB_data = param_4 | 0x40000;
    } while (param_3 != uVar1);
  }
  zw_set_bits(&peripheral_gpioB_data,0);
  return;
}




void FUN_08026548(undefined4 param_1,undefined4 param_2,uint param_3,uint param_4)

{
  uint uVar1;
  
  zw_draw_setActiveDisplayRect(param_1,param_2,1,param_3);
  peripheral_gpioB_data = 0x2c;
  peripheral_gpioB_data = 0x2c;
  peripheral_gpioB_data = 0x444002c;
  zw_clear_bits(&peripheral_gpioB_data,0);
  DAT_200047a8 = peripheral_gpioB_data;
  if (param_3 != 0) {
    uVar1 = 0;
    do {
      uVar1 = uVar1 + 1 & 0xffff;
      peripheral_gpioB_data = param_4;
      peripheral_gpioB_data = param_4 | 0x40000;
    } while (param_3 != uVar1);
  }
  zw_set_bits(&peripheral_gpioB_data,0);
  return;
}




void FUN_080265c0(undefined4 param_1,undefined4 param_2,uint param_3,uint param_4,ushort param_5)

{
  uint uVar1;
  uint uVar2;
  
  zw_draw_setActiveDisplayRect();
  peripheral_gpioB_data = 0x2c;
  peripheral_gpioB_data = 0x2c;
  peripheral_gpioB_data = 0x444002c;
  zw_clear_bits(&peripheral_gpioB_data,0);
  DAT_200047a8 = peripheral_gpioB_data;
  if (param_4 != 0) {
    uVar2 = 0;
    do {
      if (param_3 != 0) {
        uVar1 = 0;
        do {
          uVar1 = uVar1 + 1 & 0xffff;
          peripheral_gpioB_data = param_5;
          peripheral_gpioB_data = param_5 | 0x40000;
        } while (param_3 != uVar1);
      }
      uVar2 = uVar2 + 1 & 0xffff;
    } while (param_4 != uVar2);
  }
  zw_set_bits(&peripheral_gpioB_data,0);
  return;
}




void zw_draw_bitmap(uint *imageData,undefined2 param_2,undefined2 param_3,uint width,uint height)

{
  uint uVar1;
  uint *puVar2;
  
  zw_draw_setActiveDisplayRect(param_2,param_3,width & 0xffff,height & 0xffff);
  peripheral_gpioB_data = 0x2c;
  peripheral_gpioB_data = 0x2c;
  peripheral_gpioB_data = 0x444002c;
  zw_clear_bits(&peripheral_gpioB_data,0);
  DAT_200047a8 = peripheral_gpioB_data;
  if (width * height != 0) {
    puVar2 = width * height * 2 + imageData;
    do {
      uVar1 = *imageData;
      imageData = imageData + 2;
      peripheral_gpioB_data = uVar1;
      peripheral_gpioB_data = uVar1 | 0x40000;
    } while (puVar2 != imageData);
  }
  zw_set_bits(&peripheral_gpioB_data,0);
  return;
}




void zw_draw_element_16bpp(ushort *param_1,undefined2 param_2,undefined2 param_3)

{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  ushort *puVar4;
  int iVar5;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  zw_draw_setActiveDisplayRect(param_2,param_3,uVar1,uVar2);
  peripheral_gpioB_data = 0x2c;
  peripheral_gpioB_data = 0x2c;
  peripheral_gpioB_data = 0x444002c;
  zw_clear_bits(&peripheral_gpioB_data,0);
  iVar5 = uVar1 * uVar2;
  DAT_200047a8 = peripheral_gpioB_data;
  if (iVar5 != 0) {
    puVar3 = param_1;
    do {
      puVar4 = puVar3 + 1;
      peripheral_gpioB_data = puVar3[2];
      peripheral_gpioB_data = puVar3[2] | 0x40000;
      puVar3 = puVar4;
    } while (param_1 + iVar5 != puVar4);
  }
  zw_set_bits(&peripheral_gpioB_data,0);
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


int SPIFLS_Init(void)

{
  uint8_t *id;
  int iVar1;
  
  hspi.Instance = 0x400;
  hspi.Init.Mode = 4;
  hspi.Init.NSS = 2;
  hspi.Init.CLKPolarity = 0;
  hspi.Init.CLKPhase = 0;
  hspi.Init.BaudRatePrescaler = 1;
  hspi.Init.FirstByte = 0;
  id = HAL_SPI_Init(&hspi);
  iVar1 = 0;
  if (id != 0x0) {
    iVar1 = fls_drv_read_id(id);
  }
  uRam00000e00 = uRam00000e00 | 0x100;
  return iVar1;
}




void zw_SPI_Transmit__FUN_080267ac(byte param_1,undefined4 param_2)

{
  st77xx_buf_tx[1] = param_2 >> 0x18;
  st77xx_buf_tx[0] = param_1 & 0x7f;
  st77xx_buf_tx[2] = param_2 >> 0x10;
  st77xx_buf_tx[3] = param_2 >> 8;
  st77xx_buf_tx[4] = param_2;
  (hspi.Instance)->CH_CFG = (hspi.Instance)->CH_CFG & 0xfffffffb;
  HAL_SPI_Transmit(&hspi,st77xx_buf_tx,5,5000);
  (hspi.Instance)->CH_CFG = (hspi.Instance)->CH_CFG | 4;
  return;
}




undefined4 FUN_080267f0(byte param_1)

{
  st77xx_buf_tx[0] = param_1 | 0x80;
  (hspi.Instance)->CH_CFG = (hspi.Instance)->CH_CFG & 0xfffffffb;
  HAL_SPI_Transmit(&hspi,st77xx_buf_tx,1,5000);
  HAL_SPI_Receive(&hspi,st77xx_buf_rx,4,5000);
  (hspi.Instance)->CH_CFG = (hspi.Instance)->CH_CFG | 4;
  return CONCAT31(CONCAT21(CONCAT11(st77xx_buf_rx._0_4_,SUB41(st77xx_buf_rx._0_4_,1)),SUB41(st77xx_buf_rx._0_4_,1)),st77xx_buf_rx._0_4_);
}




void FUN_08026840(uint8_t *pData,uint32_t Size)

{
  if (1000 < Size) {
    return;
  }
  st77xx_buf_tx[0] = 0x8a;
  (hspi.Instance)->CH_CFG = (hspi.Instance)->CH_CFG & 0xfffffffb;
  HAL_SPI_Transmit(&hspi,st77xx_buf_tx,1,5000);
  HAL_SPI_Receive(&hspi,pData,Size,5000);
  (hspi.Instance)->CH_CFG = (hspi.Instance)->CH_CFG | 4;
  return;
}




void FUN_08026890(void)

{
  st77xx_buf_tx[0] = 0x8a;
  (hspi.Instance)->CH_CFG = (hspi.Instance)->CH_CFG & 0xfffffffb;
  HAL_SPI_Transmit(&hspi,st77xx_buf_tx,1,5000);
  return;
}




void zw_SPI_Receive_FUN_080268b8(uint8_t *pData,uint32_t Size)

{
  HAL_SPI_Receive(&hspi,pData,Size,5000);
  return;
}




void FUN_080268d0(void)

{
  (hspi.Instance)->CH_CFG = (hspi.Instance)->CH_CFG | 4;
  return;
}




void FUN_080268e4(undefined4 *param_1,char *param_2,uint param_3)

{
  short sVar1;
  float *pfVar2;
  float *pfVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  byte *pbVar7;
  short *psVar8;
  int iVar9;
  float fVar10;
  float *pfVar11;
  float *pfVar12;
  float *pfVar13;
  float fVar14;
  int *piVar15;
  undefined4 *puVar16;
  int iVar17;
  float *pfVar18;
  int iVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  int iVar23;
  uint uVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  
  sVar1 = ch1_vert_offset_pixels;
  if (param_3 < 0x401) {
    uVar5 = param_3;
    if (param_3 != 0) {
      psVar8 = &DAT_200057ac;
      puVar16 = param_1 + param_3;
      do {
        uVar4 = *param_1;
        param_1 = param_1 + 1;
        *psVar8 = uVar4 + (-0x80 - sVar1);
        psVar8 = psVar8 + 1;
      } while (puVar16 != param_1);
      if (param_3 == 0x400) goto LAB_0802694e;
    }
    do {
      (&DAT_200057ac)[uVar5] = 0;
      uVar5 = uVar5 + 1;
    } while (uVar5 != 0x400);
  }
  else {
    uVar24 = param_3 * 1000 >> 10;
    pbVar7 = param_1 + 1;
    uVar20 = 1;
    uVar5 = uVar24;
    uVar21 = 0;
    do {
      while (uVar5 / 1000 != uVar20) {
        uVar20 = uVar20 + 1;
        pbVar7 = pbVar7 + 1;
        if (param_3 == uVar20) goto LAB_08026d96;
      }
      uVar22 = uVar21 + 1;
      uVar5 = uVar5 + uVar24;
      (&DAT_200057ac)[uVar21] = (-sVar1 - 0x80U & 0x7fff) + *pbVar7;
      if (uVar22 == 0x400) goto LAB_0802694e;
      uVar20 = uVar20 + 1;
      pbVar7 = pbVar7 + 1;
      uVar21 = uVar22;
    } while (param_3 != uVar20);
LAB_08026d96:
    if (uVar21 < 0x400) {
      puVar16 = &DAT_200057ac + uVar21;
      do {
        *puVar16 = 0;
        puVar16 = puVar16 + 2;
      } while (puVar16 != &DAT_20005fac);
    }
  }
LAB_0802694e:
  psVar8 = &DAT_200057ac;
  pfVar11 = &DAT_20006fac;
  pfVar3 = &DAT_20005fac;
  iVar23 = 0x100;
  do {
    iVar17 = psVar8[0x100];
    iVar9 = *psVar8;
    iVar19 = psVar8[0x200];
    iVar6 = psVar8[0x300];
    *pfVar11 = iVar9 + iVar17 + iVar19 + iVar6;
    *pfVar3 = iVar6 - iVar17;
    *pfVar11 = iVar9 - iVar19;
    *pfVar11 = iVar9 - iVar19;
    *pfVar3 = 0.0;
    *pfVar11 = ((iVar9 - iVar17) + iVar19) - iVar6;
    pfVar3[2] = 0.0;
    *pfVar3 = iVar17 - iVar6;
    psVar8 = psVar8 + 1;
    pfVar11 = pfVar11 + 4;
    pfVar3 = pfVar3 + 4;
    iVar23 = iVar23 + -1;
  } while (iVar23 != 0);
  fVar14 = 0.0;
  uVar5 = 1;
  do {
    pfVar12 = &DAT_20006fac;
    pfVar3 = &DAT_20005fac;
    pfVar11 = &DAT_20008fac;
    pfVar2 = &DAT_20007fac;
    if ((uVar5 & 1) == 0) {
      pfVar12 = &DAT_20008fac;
      pfVar3 = &DAT_20007fac;
      pfVar11 = &DAT_20006fac;
      pfVar2 = &DAT_20005fac;
    }
    if (uVar5 - 2 < 6) {
      uVar21 = *("Low power..\r\n" + uVar5 * 4 + 8);
    }
    else {
      uVar21 = 4;
    }
    fVar10 = 0.0;
    uVar20 = 0;
    pfVar13 = pfVar2;
    pfVar18 = pfVar11;
    fVar25 = fVar14;
    fVar30 = fVar10;
    fVar26 = fVar10;
    fVar27 = fVar14;
    fVar31 = fVar14;
    while( true ) {
      fVar28 = (pfVar12[0x100] - pfVar3[0x100]) * fVar10;
      fVar32 = (fVar25 - fVar10) * pfVar12[0x100] + fVar28;
      fVar28 = (fVar10 + fVar25) * pfVar3[0x100] + fVar28;
      fVar25 = (pfVar12[0x200] - pfVar3[0x200]) * fVar26;
      fVar10 = (fVar26 + fVar27) * pfVar3[0x200] + fVar25;
      fVar25 = (fVar27 - fVar26) * pfVar12[0x200] + fVar25;
      fVar29 = *pfVar12;
      fVar26 = (pfVar12[0x300] - pfVar3[0x300]) * fVar30;
      fVar27 = (fVar30 + fVar31) * pfVar3[0x300] + fVar26;
      fVar26 = (fVar31 - fVar30) * pfVar12[0x300] + fVar26;
      fVar30 = *pfVar3;
      *pfVar18 = fVar29 + fVar32 + fVar25 + fVar26;
      *pfVar13 = fVar30 + fVar28 + fVar10 + fVar27;
      *pfVar18 = ((fVar29 + fVar28) - fVar25) - fVar27;
      *pfVar13 = ((fVar30 - fVar32) - fVar10) + fVar26;
      *pfVar18 = ((fVar29 - fVar32) + fVar25) - fVar26;
      uVar20 = uVar20 + 1;
      *pfVar13 = ((fVar30 - fVar28) + fVar10) - fVar27;
      *pfVar18 = ((fVar29 - fVar28) - fVar25) + fVar27;
      *pfVar13 = ((fVar30 + fVar32) - fVar10) - fVar26;
      pfVar12 = pfVar12 + 1;
      pfVar3 = pfVar3 + 1;
      pfVar18 = pfVar18 + 4;
      pfVar13 = pfVar13 + 4;
      if (uVar20 == 0x100) break;
      iVar23 = uVar20 - (uVar20 / uVar21) * uVar21;
      fVar10 = *(&DAT_0805bfac + iVar23 * 4);
      fVar25 = *(&DAT_0805c3ac + iVar23 * 4);
      fVar26 = *(&DAT_0805c7ac + iVar23 * 4);
      fVar27 = *(&DAT_0805cbac + iVar23 * 4);
      fVar30 = *(&DAT_0805cfac + iVar23 * 4);
      fVar31 = *(&DAT_0805d3ac + iVar23 * 4);
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 != 5);
  fVar14 = *pfVar11 * *pfVar11 + *pfVar2 * *pfVar2;
  fVar25 = SQRT(fVar14);
  if ((true) && (fVar14 < 0.0)) {
    pfVar3 = sqrtf(pfVar3);
  }
  fVar14 = (param_3 < 0x400) * 0x400 + (param_3 >= 0x400) * 0x400;
  uVar5 = (fVar25 * 0.0) / fVar14;
  if (fft_mode_0_off_1_log_2_lin_3_music == '\x02') {
    *param_2 = uVar5 >> 10;
  }
  else if (uVar5 < 1000) {
    *param_2 = ""[uVar5];
  }
  else if (uVar5 < 10000) {
    *param_2 = ""[uVar5 / 10] + '\x1e';
  }
  else {
    *param_2 = ""[uVar5 / 100] + '<';
  }
  piVar15 = &DAT_0805b7b4;
  fVar25 = 0.0;
  iVar23 = 0x100;
  while( true ) {
    param_2 = param_2 + 1;
    fVar30 = pfVar11[iVar23] * pfVar11[iVar23] + pfVar2[iVar23] * pfVar2[iVar23];
    fVar26 = SQRT(fVar30);
    if ((true) && (fVar30 < 0.0)) {
      pfVar3 = sqrtf(pfVar3);
    }
    uVar5 = ((fVar26 + fVar26) * fVar25) / fVar14;
    if (fft_mode_0_off_1_log_2_lin_3_music == '\x03') {
      uVar5 = uVar5 >> 6;
      *param_2 = (uVar5 < 0x95) * uVar5 + (uVar5 >= 0x95) * -0x6b;
    }
    else if (fft_mode_0_off_1_log_2_lin_3_music == '\x02') {
      *param_2 = uVar5 >> 10;
    }
    else if (uVar5 < 1000) {
      *param_2 = ""[uVar5];
    }
    else if (uVar5 < 10000) {
      *param_2 = ""[uVar5 / 10] + '\x1e';
    }
    else {
      *param_2 = ""[uVar5 / 100] + '<';
    }
    if (piVar15 == &DAT_0805bfac) break;
    iVar23 = *piVar15;
    piVar15 = piVar15 + 1;
  }
  return;
}




void FUN_08026e44(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined4 *puVar8;
  
  if (fft_mode_0_off_1_log_2_lin_3_music == '\0') {
    return;
  }
  printf_disabled_1("measure_len=%d\n",measurement_sample_count_);
  puVar2 = &DAT_20004fac;
  FUN_080268e4(&DAT_2001bb30,&DAT_20004fac,measurement_sample_count_);
  puVar8 = &DAT_20004fac;
  puVar7 = &DAT_200053ac;
  puVar6 = &DAT_200055ac;
  puVar3 = 0xff;
  iVar4 = 300;
  puVar5 = 0x0;
  do {
    puVar1 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar2 = (puVar1 < puVar3) * puVar2 + (puVar1 >= puVar3) * puVar3;
    puVar3 = (puVar1 < puVar5) * puVar5 + (puVar1 >= puVar5) * puVar1;
    *puVar7 = puVar3;
    puVar7 = puVar7 + 1;
    *puVar6 = puVar2;
    puVar6 = puVar6 + 1;
    iVar4 = iVar4 + -1;
    puVar5 = puVar2;
  } while (iVar4 != 0);
  return;
}




void FUN_08026eb4(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  short sVar5;
  uint uVar6;
  
  sVar5 = 10;
  uVar1 = 0;
  do {
    uVar2 = uVar1 & 0xffff;
    uVar6 = uVar1 + 0xf;
    if (uVar1 < uVar6) {
      uVar4 = 0;
      do {
        uVar2 = uVar2 + 1 & 0xffff;
        uVar1 = *(&DAT_20004fac + uVar1 + 1);
        uVar4 = (uVar1 < uVar4) * uVar4 + (uVar1 >= uVar4) * uVar1;
        uVar1 = uVar2;
      } while (uVar2 < uVar6);
      uVar2 = (uVar4 < 0x95) * uVar4 + (uVar4 >= 0x95) * 0x95 & 0xff;
      uVar1 = 0xa8 - uVar2 & 0x7fff;
      zw_draw_rectangle_filled(sVar5,uVar1,0xe,uVar2,4);
      if (1 < uVar2 / 5) {
        uVar4 = 0xa3;
        do {
          uVar3 = uVar4 - 5 & 0xffff;
          zw_draw_line_horizontal(sVar5,uVar4,0xe,0);
          uVar4 = uVar3;
        } while (((uVar2 / 5) * -5 + 0xa8 & 0x7fff) != uVar3);
      }
      if (3 < uVar2) {
        zw_draw_rectangle_filled(sVar5,uVar1,0xe,3,6);
      }
    }
    else {
      zw_draw_rectangle_filled(sVar5,0xa8,0xe,0,4);
    }
    sVar5 = sVar5 + 0xf;
    uVar1 = uVar6;
  } while (sVar5 != 0x136);
  zw_draw_line_horizontal(10,0xa8,300,4);
  return;
}




void FUN_08026f94(void)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  
  if (fft_mode_0_off_1_log_2_lin_3_music != 0) {
    if (fft_mode_0_off_1_log_2_lin_3_music == 3) {
      FUN_08026eb4();
      return;
    }
    pbVar2 = &DAT_200053ac;
    pbVar4 = &DAT_200055ac;
    do {
      bVar1 = *pbVar2;
      for (uVar3 = *pbVar4; uVar3 <= bVar1; uVar3 = uVar3 + 1 & 0xffff) {
        if (uVar3 < 0x96) {
          pbVar2[(0xa8 - uVar3) * 0x140 + 0x18c02] = 2;
        }
      }
      pbVar2 = pbVar2 + 1;
      pbVar4 = pbVar4 + 1;
    } while (pbVar2 != 0x200054d8);
  }
  return;
}




void printf_disabled_1(char *fmt,...)

{
  return;
}




uint FUN_08027028(uint param_1)

{
  int iVar1;
  
  param_1 = param_1 >> 5;
  iVar1 = param_1 - 1;
  if (param_1 != 0) {
    do {
      iVar1 = iVar1 + -1;
    } while (iVar1 != -1);
  }
  return param_1;
}




int FUN_08027040(int param_1)

{
  int iVar1;
  
  param_1 = param_1 * 0x78;
  iVar1 = param_1 + -1;
  if (param_1 != 0) {
    do {
      iVar1 = iVar1 + -1;
    } while (iVar1 != -1);
  }
  return param_1;
}




void HAL_Delay(uint32_t Delay)

{
  uint32_t uVar1;
  uint32_t uVar2;
  
  uVar1 = HAL_GetTick();
  do {
    uVar2 = HAL_GetTick();
  } while (uVar2 - uVar1 < Delay);
  return;
}




void zw_timer_us(uint32_t *param_1,uint time_us)

{
  uint32_t uVar1;
  
  if (999 < time_us) {
    uVar1 = HAL_GetTick();
    *param_1 = uVar1;
    param_1[1] = (499 < time_us % 1000) + time_us / 1000;
    return;
  }
  uVar1 = HAL_GetTick();
  *param_1 = uVar1;
  param_1[1] = 1;
  return;
}




undefined4 FUN_080270a8(uint32_t *param_1)

{
  uint32_t uVar1;
  
  uVar1 = HAL_GetTick();
  if (param_1[1] <= uVar1 - *param_1) {
    *param_1 = uVar1;
    return 1;
  }
  return 0;
}




void FUN_080270c4(undefined2 *param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar2 = *(param_1 + 0x42);
  uVar4 = *(param_1 + 0x40);
  if (uVar2 != 0) {
    uVar3 = uVar2;
    if (uVar4 - 1 < uVar2) {
      uVar3 = uVar4 - 1;
    }
    uVar3 = uVar3 & 0xff;
    if (uVar3 != 0) {
      puVar1 = param_1 + uVar3 + 0x7fffffff;
      do {
        puVar1[1] = *puVar1;
        puVar1 = puVar1 + -1;
      } while (puVar1 != param_1 + ((uVar3 + 0x7ffffffe) - (uVar3 - 1 & 0xff)));
    }
  }
  uVar2 = uVar2 + 1;
  *param_1 = param_2;
  *(param_1 + 0x42) = (uVar2 < uVar4) * uVar2 + (uVar2 >= uVar4) * uVar4;
  return;
}




void zw_screenshot_delete_(int param_1,uint param_2)

{
  uint uVar1;
  undefined2 *puVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = *(param_1 + 0x84);
  if ((uVar3 != 0) && (param_2 < uVar3)) {
    uVar4 = *(param_1 + 0x80) - 1;
    uVar1 = uVar3;
    if (uVar4 < uVar3) {
      uVar1 = uVar4;
    }
    for (; param_2 < (uVar1 & 0xff) - 1; param_2 = param_2 + 1 & 0xff) {
      puVar2 = param_2 * 2 + param_1;
      *puVar2 = puVar2[1];
    }
    *(param_1 + 0x84) = uVar3 - 1;
  }
  return;
}




void printf_disabled_2(char *fmt,...)

{
  return;
}




int FifoInit(uint8_t *fifo_addr,uint32_t fifo_size)

{
  int iVar1;
  
  if ((fifo_addr == 0x0) || (fifo_size == 0)) {
    iVar1 = -1;
  }
  else {
    _fifo_str.in = 0;
    _fifo_str.out = 0;
    iVar1 = 0;
    _fifo_str.buf = fifo_addr;
    _fifo_str.size = fifo_size;
  }
  return iVar1;
}




int FifoDataLen(void)

{
  return _fifo_str.in - _fifo_str.out;
}




int FifoRead(uint8_t *buf,uint32_t len)

{
  void *pvVar1;
  int iVar2;
  size_t __n;
  uint uVar3;
  uint uVar4;
  
  iVar2 = _fifo_str.out - _fifo_str.size * (_fifo_str.out / _fifo_str.size);
  uVar3 = _fifo_str.in - _fifo_str.out;
  uVar4 = (uVar3 < len) * uVar3 + (uVar3 >= len) * len;
  uVar3 = _fifo_str.size - iVar2;
  __n = (uVar3 < uVar4) * uVar3 + (uVar3 >= uVar4) * uVar4;
  pvVar1 = memcpy(buf,_fifo_str.buf + iVar2,__n);
  memcpy(pvVar1 + __n,_fifo_str.buf,uVar4 - __n);
  _fifo_str.out = _fifo_str.out + uVar4;
  return uVar4;
}




int FifoWrite(uint8_t *buf,uint32_t len)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int unaff_r5;
  size_t __n;
  
  iVar2 = _fifo_str.in - _fifo_str.size * (_fifo_str.in / _fifo_str.size);
  uVar3 = (_fifo_str.out + _fifo_str.size) - _fifo_str.in;
  uVar3 = (uVar3 < len) * uVar3 + (uVar3 >= len) * len;
  bVar1 = _fifo_str.size - iVar2 < uVar3;
  __n = bVar1 * unaff_r5 + !bVar1 * uVar3;
  memcpy(_fifo_str.buf + iVar2,buf,__n);
  memcpy(_fifo_str.buf,buf + __n,uVar3 - __n);
  _fifo_str.in = _fifo_str.in + uVar3;
  return uVar3;
}




void zw_fifoInit(void)

{
  _fifo_str.in = 0;
  _fifo_str.out = 0;
  return;
}




void zw_draw_ParametrizedGlyph(ushort *param_1)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  ushort *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  byte bVar9;
  uint uVar10;
  
  if (*(param_1 + 8) == 0) {
    return;
  }
  puVar4 = *(param_1 + 4);
  *(param_1 + 8) = *(param_1 + 8) + -1;
  uVar6 = *param_1;
  uVar3 = param_1[2];
  uVar10 = uVar6 + *puVar4;
  uVar7 = puVar4[1] + uVar3;
  iVar8 = 4;
  do {
    uVar2 = *(puVar4 + iVar8);
    uVar1 = *(puVar4 + iVar8 + 2);
    if ((uVar2 & 0x7fff) != 0) {
      uVar5 = 0;
      do {
        if ((uVar1 & 0x20) == 0) {
          if (uVar1 != 0xffdf) {
            framebuffer_[uVar6 + uVar3 * 0x140] = uVar1;
          }
        }
        else {
          bVar9 = uVar1 & 0x1f;
          if ((1 << (uVar1 >> 0xb) & *(param_1 + 6)) == 0) {
            bVar9 = (uVar1 & 0x3ff) >> 6;
          }
          framebuffer_[uVar6 + uVar3 * 0x140] = bVar9;
        }
        uVar6 = uVar6 + 1 & 0xffff;
        if ((uVar10 & 0x7fff) == uVar6) {
          uVar3 = uVar3 + 1 & 0xffff;
          uVar6 = *param_1;
          if ((uVar7 & 0xffff) == uVar3) {
            return;
          }
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 != (uVar2 & 0x7fff));
      puVar4 = *(param_1 + 4);
    }
    iVar8 = iVar8 + 4;
  } while( true );
}




void zw_boot_logo(uint positionX,uint positionY,byte *bmp)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  bVar3 = *bmp;
  bVar1 = bmp[1];
  bVar2 = bmp[3];
  iVar8 = positionY + bmp[2];
  bmp = bmp + 4;
  uVar6 = positionX;
  do {
    uVar7 = *bmp;
    bVar4 = bmp[1];
    if (uVar7 != 0) {
      uVar5 = 0;
      do {
        while( true ) {
          if (bVar4 != 0x20) {
            framebuffer_[uVar6 + positionY * 0x140] = bVar4;
          }
          uVar6 = uVar6 + 1 & 0xffff;
          if ((positionX + bVar3 + bVar1 * 0x100 & 0x7fff) != uVar6) break;
          positionY = positionY + 1 & 0xffff;
          if ((iVar8 + bVar2 * 0x100 & 0x7fff) == positionY) {
            return;
          }
          uVar5 = uVar5 + 1;
          uVar6 = positionX;
          if (uVar5 == uVar7) goto LAB_08027382;
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 != uVar7);
    }
LAB_08027382:
    bmp = bmp + 2;
  } while( true );
}




void zw_draw_element(ushort *p_Desc)

{
  uint uVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  pbVar2 = *(p_Desc + 4);
  uVar3 = *p_Desc;
  uVar6 = p_Desc[1];
  uVar7 = uVar6 + pbVar2[1];
  uVar1 = uVar3 + *pbVar2 & 0x7fff;
  uVar5 = 2;
  uVar4 = 0;
  do {
    if ((pbVar2[uVar5] & 0x80 >> (uVar4 & 0x3f)) == 0) {
      if (p_Desc[7] == 0x20) goto LAB_080273d4;
      uVar4 = uVar4 + 1 & 0xffff;
      framebuffer_[uVar3 + uVar6 * 0x140] = p_Desc[7];
      uVar3 = uVar3 + 1 & 0xffff;
      if (uVar4 != 8) goto LAB_080273e0;
LAB_08027416:
      uVar5 = uVar5 + 1 & 0xffff;
      if (uVar1 == uVar3) {
LAB_0802742c:
        uVar6 = uVar6 + 1 & 0x7fff;
        uVar3 = *p_Desc;
        if ((uVar7 & 0x7fff) == uVar6) {
          return;
        }
      }
      uVar4 = 0;
    }
    else {
      framebuffer_[uVar3 + uVar6 * 0x140] = p_Desc[6];
LAB_080273d4:
      uVar4 = uVar4 + 1 & 0xffff;
      uVar3 = uVar3 + 1 & 0xffff;
      if (uVar4 == 8) goto LAB_08027416;
LAB_080273e0:
      if (uVar1 == uVar3) {
        uVar5 = uVar5 + 1 & 0xffff;
        goto LAB_0802742c;
      }
    }
    pbVar2 = *(p_Desc + 4);
  } while( true );
}




void zw_drawGlyph2(ushort *p_Desc)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar2 = *p_Desc;
  uVar5 = p_Desc[1];
  uVar6 = uVar5 + p_Desc[3];
  uVar4 = 0;
  uVar1 = uVar2 + p_Desc[2] & 0x7fff;
  uVar3 = 0;
  while ((*(*(p_Desc + 4) + uVar4) & 0x80 >> (uVar3 & 0x3f)) != 0) {
    framebuffer_[uVar2 + uVar5 * 0x140] = p_Desc[6];
LAB_08027494:
    uVar3 = uVar3 + 1 & 0xffff;
    uVar2 = uVar2 + 1 & 0xffff;
    if (uVar3 == 8) goto LAB_080274e0;
LAB_080274a0:
    if (uVar1 == uVar2) {
      uVar4 = uVar4 + 1 & 0xffff;
LAB_080274ac:
      uVar5 = uVar5 + 1 & 0x7fff;
      uVar2 = *p_Desc;
      if ((uVar6 & 0x7fff) == uVar5) {
        return;
      }
LAB_080274bc:
      uVar3 = 0;
    }
  }
  if (p_Desc[7] == 0x20) goto LAB_08027494;
  uVar3 = uVar3 + 1 & 0xffff;
  framebuffer_[uVar2 + uVar5 * 0x140] = p_Desc[7];
  uVar2 = uVar2 + 1 & 0xffff;
  if (uVar3 != 8) goto LAB_080274a0;
LAB_080274e0:
  uVar4 = uVar4 + 1 & 0xffff;
  if (uVar1 == uVar2) goto LAB_080274ac;
  goto LAB_080274bc;
}




void FUN_080274f4(ushort *param_1)

{
  uint uVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  pbVar2 = *(param_1 + 4);
  uVar3 = *param_1;
  uVar6 = param_1[1];
  uVar7 = uVar6 + pbVar2[1];
  uVar1 = uVar3 + *pbVar2 & 0x7fff;
  uVar5 = 2;
  uVar4 = 0;
  do {
    if ((pbVar2[uVar5] & 0x80 >> (uVar4 & 0x3f)) != 0) {
      if (framebuffer_[uVar3 + uVar6 * 0x140] == 0) {
        framebuffer_[uVar3 + uVar6 * 0x140] = param_1[6];
      }
      else {
        framebuffer_[uVar3 + uVar6 * 0x140] = param_1[7];
      }
    }
    uVar4 = uVar4 + 1 & 0xffff;
    uVar3 = uVar3 + 1 & 0xffff;
    if (uVar4 == 8) {
      uVar5 = uVar5 + 1 & 0xffff;
      if (uVar1 == uVar3) {
LAB_08027582:
        uVar6 = uVar6 + 1 & 0x7fff;
        uVar3 = *param_1;
        if ((uVar7 & 0x7fff) == uVar6) {
          return;
        }
      }
      uVar4 = 0;
    }
    else if (uVar1 == uVar3) {
      uVar5 = uVar5 + 1 & 0xffff;
      goto LAB_08027582;
    }
    pbVar2 = *(param_1 + 4);
  } while( true );
}




void zw_draw_flush_offscreen(void)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  zw_draw_setActiveDisplayRect(0,0,0x140,0xf0);
  FUN_08025f20(0x2c);
  FUN_08025f44();
  pbVar2 = framebuffer_;
  do {
    pbVar3 = pbVar2 + 0x140;
    do {
      iVar1 = *pbVar2;
      pbVar2 = pbVar2 + 1;
      zw_draw_sendPixelColorToDisplay(*(&DAT_200001cc + iVar1 * 2));
    } while (pbVar2 != pbVar3);
  } while (pbVar2 != &DAT_20030ba4);
  FUN_08025f64();
  return;
}




void zw_flushOffscreenRectangle(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  zw_draw_setActiveDisplayRect(param_1 & 0xffff,param_2 & 0xffff,param_3 & 0xffff,param_4 & 0xffff);
  FUN_08025f20(0x2c);
  param_4 = param_4 + param_2;
  FUN_08025f44();
  if (param_2 < param_4) {
    pbVar3 = framebuffer_ + param_1 + param_2 * 0x140;
    do {
      if (param_1 < param_1 + param_3) {
        pbVar2 = pbVar3;
        do {
          iVar1 = *pbVar2;
          pbVar2 = pbVar2 + 1;
          zw_draw_sendPixelColorToDisplay(*(&DAT_200001cc + iVar1 * 2));
        } while (pbVar2 != pbVar3 + param_3);
      }
      param_2 = param_2 + 1;
      pbVar3 = pbVar3 + 0x140;
    } while (param_2 != param_4);
  }
  FUN_08025f64();
  return;
}




void zw_draw_line_horizontal(int positionX,int positionY,int width,byte color)

{
  byte *pbVar1;
  
  if (width != 0) {
    pbVar1 = framebuffer_ + positionY * 320 + positionX;
    do {
      *pbVar1 = color;
      pbVar1 = pbVar1 + 1;
    } while (pbVar1 != framebuffer_ + (width - 1U & 0xffff) + positionX + positionY * 320 + 1);
  }
  return;
}




void zw_draw_line_vertical(int positionX,int positionY,int height,byte color)

{
  byte *pbVar1;
  
  if (height != 0) {
    pbVar1 = framebuffer_ + positionX + positionY * 0x140;
    do {
      *pbVar1 = color;
      pbVar1 = pbVar1 + 0x140;
    } while (pbVar1 != framebuffer_ + positionX + ((height - 1U & 0xffff) + positionY) * 0x140 + 0x140);
  }
  return;
}




void zw_draw_line_horizontal_dashed(int param_1,int param_2,uint param_3,byte param_4)

{
  byte *pbVar1;
  uint uVar2;
  
  if (param_3 != 0) {
    pbVar1 = framebuffer_ + param_1 + param_2 * 0x140 + 1;
    uVar2 = 1;
    if (param_3 != 1) {
      do {
        if ((uVar2 & 3) != 0) {
          *pbVar1 = param_4;
        }
        uVar2 = uVar2 + 1 & 0xffff;
        pbVar1 = pbVar1 + 1;
      } while (param_3 != uVar2);
    }
  }
  return;
}




void zw_draw_line_vertical_dashed(int positionX,int positionY,uint height,byte color)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  
  if (height != 0) {
    pbVar1 = framebuffer_ + positionX + positionY * 0x140 + 0x140;
    uVar2 = 0;
    while( true ) {
      uVar3 = uVar2 + 1;
      uVar2 = uVar3 & 0xffff;
      if (height == uVar2) break;
      if ((uVar3 & 3) != 0) {
        *pbVar1 = color;
      }
      pbVar1 = pbVar1 + 0x140;
    }
  }
  return;
}




void zw_draw_rectangle_filled(int positionX,int positionY,int width,int height,byte color)

{
  byte *pbVar1;
  byte *pbVar2;
  
  if (height != 0) {
    pbVar2 = framebuffer_ + positionX + positionY * 0x140;
    do {
      if (width != 0) {
        pbVar1 = pbVar2;
        do {
          *pbVar1 = color;
          pbVar1 = pbVar1 + 1;
        } while (pbVar1 != pbVar2 + (width - 1U & 0xffff) + 1);
      }
      pbVar2 = pbVar2 + 0x140;
    } while (pbVar2 != framebuffer_ + positionX + ((height - 1U & 0xffff) + positionY) * 0x140 + 0x140);
  }
  return;
}




void zw_draw_rectangle(int positionX,int positionY,int width,int height,byte color)

{
  uint uVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  if (width != 0) {
    iVar3 = (width - 1U & 0x7fff) + 1 + positionX;
    pbVar2 = framebuffer_ + positionX + positionY * 0x140;
    do {
      *pbVar2 = color & 0x7f;
      pbVar2 = pbVar2 + 1;
    } while (pbVar2 != framebuffer_ + iVar3 + positionY * 0x140);
    iVar4 = (positionY + height + -1 & 0x7fffU) * 0x140;
    pbVar2 = framebuffer_ + iVar4 + positionX;
    do {
      *pbVar2 = color & 0x7f;
      pbVar2 = pbVar2 + 1;
    } while (pbVar2 != framebuffer_ + iVar3 + iVar4);
  }
  if (height != 0) {
    iVar3 = (positionY + (height - 1U & 0xffff)) * 0x140;
    pbVar2 = framebuffer_ + positionY * 0x140 + positionX;
    do {
      *pbVar2 = color & 0x7f;
      pbVar2 = pbVar2 + 0x140;
    } while (pbVar2 != framebuffer_ + positionX + iVar3 + 0x140);
    uVar1 = width + -1 + positionX & 0xffff;
    pbVar2 = framebuffer_ + positionY * 0x140 + uVar1;
    do {
      *pbVar2 = color & 0x7f;
      pbVar2 = pbVar2 + 0x140;
    } while (pbVar2 != framebuffer_ + uVar1 + iVar3 + 0x140);
  }
  return;
}




void FUN_08027850(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  
  uVar5 = (2 < param_3 % 6) + param_3 / 6 & 0xffff;
  uVar9 = (2 < param_4 % 6) + param_4 / 6 & 0x7fff;
  uVar2 = param_1 & 0x7fff;
  uVar1 = param_2 & 0x7fff;
  uVar10 = uVar2;
  uVar12 = uVar2;
  uVar13 = uVar2;
  uVar14 = uVar2;
  if (uVar5 != 0) {
    iVar6 = (param_2 & 0x7fff) * 0x140;
    uVar12 = uVar5 - 1 & 0x7fff;
    pbVar7 = framebuffer_ + (param_1 & 0x7fff) + iVar6;
    do {
      *pbVar7 = 2;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + (param_1 & 0x7fff) + iVar6 + uVar12 + 1);
    uVar13 = uVar5 + uVar2 & 0x7fff;
    pbVar7 = framebuffer_ + uVar13 + iVar6;
    do {
      *pbVar7 = 6;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + iVar6 + 1 + uVar13 + uVar12);
    uVar10 = uVar5 + uVar13 & 0x7fff;
    iVar11 = iVar6 + 1 + uVar12;
    pbVar7 = framebuffer_ + uVar10 + iVar6;
    do {
      *pbVar7 = 3;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + iVar11 + uVar10);
    uVar12 = uVar5 + uVar10 & 0x7fff;
    pbVar7 = framebuffer_ + uVar12 + iVar6;
    do {
      *pbVar7 = 4;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + iVar11 + uVar12);
    uVar14 = uVar5 + uVar12 & 0x7fff;
    pbVar7 = framebuffer_ + uVar14 + iVar6;
    do {
      *pbVar7 = 7;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + iVar11 + uVar14);
  }
  uVar8 = uVar5 * 5 & 0xffff;
  uVar3 = (param_3 & 0xffff) - uVar8 & 0x7fff;
  uVar8 = uVar2 + uVar8 & 0xffff;
  if (uVar3 != 0) {
    iVar6 = (param_2 & 0x7fff) * 0x140;
    pbVar7 = framebuffer_ + uVar8 + iVar6;
    do {
      *pbVar7 = 5;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + iVar6 + uVar8 + (uVar3 - 1 & 0xffff) + 1);
  }
  uVar4 = (uVar1 - 1) + (param_4 & 0xffff) & 0xffff;
  if (uVar5 != 0) {
    iVar6 = uVar4 * 0x140;
    uVar5 = uVar5 - 1;
    pbVar7 = framebuffer_ + (param_1 & 0x7fff) + iVar6;
    do {
      *pbVar7 = 5;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + (param_1 & 0x7fff) + iVar6 + (uVar5 & 0xffff) + 1);
    pbVar7 = framebuffer_ + uVar13 + iVar6;
    do {
      *pbVar7 = 7;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + iVar6 + (uVar5 & 0xffff) + uVar13 + 1);
    iVar6 = uVar4 * 0x140;
    pbVar7 = framebuffer_ + uVar10 + iVar6;
    iVar11 = iVar6 + 1 + (uVar5 & 0xffff);
    do {
      *pbVar7 = 4;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + iVar11 + uVar10);
    pbVar7 = framebuffer_ + uVar12 + iVar6;
    do {
      *pbVar7 = 3;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + iVar11 + uVar12);
    pbVar7 = framebuffer_ + uVar14 + uVar4 * 0x140;
    do {
      *pbVar7 = 6;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + uVar4 * 0x140 + (uVar5 & 0xffff) + uVar14 + 1);
  }
  if (uVar3 != 0) {
    pbVar7 = framebuffer_ + uVar8 + uVar4 * 0x140;
    do {
      *pbVar7 = 2;
      pbVar7 = pbVar7 + 1;
    } while (pbVar7 != framebuffer_ + uVar4 * 0x140 + uVar8 + (uVar3 - 1 & 0x7fff) + 1);
  }
  uVar10 = uVar1;
  uVar12 = uVar1;
  uVar13 = uVar1;
  uVar14 = uVar1;
  if (uVar9 != 0) {
    uVar5 = param_1 & 0x7fff;
    pbVar7 = framebuffer_ + uVar5 + (param_2 & 0x7fff) * 0x140;
    iVar6 = uVar5 + 0x140;
    uVar3 = uVar9 - 1 & 0xffff;
    do {
      *pbVar7 = 5;
      pbVar7 = pbVar7 + 0x140;
    } while (pbVar7 != framebuffer_ + iVar6 + ((param_2 & 0x7fff) + uVar3) * 0x140);
    uVar13 = uVar9 + uVar1 & 0x7fff;
    pbVar7 = framebuffer_ + uVar5 + uVar13 * 0x140;
    do {
      *pbVar7 = 7;
      pbVar7 = pbVar7 + 0x140;
    } while (pbVar7 != framebuffer_ + iVar6 + (uVar13 + uVar3) * 0x140);
    uVar10 = uVar9 + uVar13 & 0x7fff;
    pbVar7 = framebuffer_ + uVar5 + uVar10 * 0x140;
    do {
      *pbVar7 = 4;
      pbVar7 = pbVar7 + 0x140;
    } while (pbVar7 != framebuffer_ + iVar6 + (uVar10 + uVar3) * 0x140);
    uVar12 = uVar9 + uVar10 & 0x7fff;
    pbVar7 = framebuffer_ + uVar5 + uVar12 * 0x140;
    do {
      *pbVar7 = 3;
      pbVar7 = pbVar7 + 0x140;
    } while (pbVar7 != framebuffer_ + iVar6 + (uVar12 + uVar3) * 0x140);
    uVar14 = uVar9 + uVar12 & 0x7fff;
    pbVar7 = framebuffer_ + uVar5 + uVar14 * 0x140;
    do {
      *pbVar7 = 6;
      pbVar7 = pbVar7 + 0x140;
    } while (framebuffer_ + iVar6 + (uVar14 + uVar3) * 0x140 != pbVar7);
  }
  uVar5 = uVar9 * 5 & 0xffff;
  uVar3 = (param_4 & 0xffff) - uVar5 & 0xffff;
  uVar1 = uVar1 + uVar5 & 0x7fff;
  if (uVar3 != 0) {
    pbVar7 = framebuffer_ + (param_1 & 0x7fff) + uVar1 * 0x140;
    do {
      *pbVar7 = 2;
      pbVar7 = pbVar7 + 0x140;
    } while (framebuffer_ + (param_1 & 0x7fff) + ((uVar3 - 1 & 0xffff) + uVar1) * 0x140 + 0x140 != pbVar7);
  }
  uVar2 = (uVar2 - 1) + (param_3 & 0xffff) & 0xffff;
  if (uVar9 != 0) {
    uVar9 = uVar9 - 1;
    pbVar7 = framebuffer_ + uVar2 + (param_2 & 0x7fff) * 0x140;
    iVar6 = uVar2 + 0x140;
    do {
      *pbVar7 = 2;
      pbVar7 = pbVar7 + 0x140;
    } while (pbVar7 != framebuffer_ + iVar6 + ((uVar9 & 0x7fff) + (param_2 & 0x7fff)) * 0x140);
    pbVar7 = framebuffer_ + uVar2 + uVar13 * 0x140;
    do {
      *pbVar7 = 6;
      pbVar7 = pbVar7 + 0x140;
    } while (framebuffer_ + iVar6 + ((uVar9 & 0x7fff) + uVar13) * 0x140 != pbVar7);
    pbVar7 = framebuffer_ + uVar2 + uVar10 * 0x140;
    do {
      *pbVar7 = 3;
      pbVar7 = pbVar7 + 0x140;
    } while (framebuffer_ + iVar6 + ((uVar9 & 0x7fff) + uVar10) * 0x140 != pbVar7);
    pbVar7 = framebuffer_ + uVar2 + uVar12 * 0x140;
    do {
      *pbVar7 = 4;
      pbVar7 = pbVar7 + 0x140;
    } while (pbVar7 != framebuffer_ + iVar6 + (uVar12 + (uVar9 & 0x7fff)) * 0x140);
    pbVar7 = framebuffer_ + uVar2 + uVar14 * 0x140;
    do {
      *pbVar7 = 7;
      pbVar7 = pbVar7 + 0x140;
    } while (framebuffer_ + iVar6 + ((uVar9 & 0x7fff) + uVar14) * 0x140 != pbVar7);
  }
  if (uVar3 != 0) {
    pbVar7 = framebuffer_ + uVar2 + uVar1 * 0x140;
    do {
      *pbVar7 = 5;
      pbVar7 = pbVar7 + 0x140;
    } while (pbVar7 != framebuffer_ + uVar2 + ((uVar3 - 1 & 0xffff) + uVar1) * 0x140 + 0x140);
  }
  return;
}




void zw_draw_init_(void)

{
  byte *pbVar1;
  byte *pbVar2;
  
  if (((persistance_mode_0_off_1_infinite_2_1s == '\0') || (settings_changed_flag_ != '\0')) || (DAT_2001de09 != '\0')) {
    memset(framebuffer_,0,76800);
    settings_changed_flag_ = 0;
  }
  else {
    pbVar1 = framebuffer_ + 320;
    do {
      pbVar2 = pbVar1 + -320;
      do {
        if (64 < *pbVar2 - 32) {
          *pbVar2 = 0;
        }
        pbVar2 = pbVar2 + 1;
      } while (pbVar2 != pbVar1);
      pbVar1 = pbVar1 + 320;
    } while (pbVar1 != 0x20030ce4);
  }
  zw_scope_fullscreen();
  FUN_0801bdec();
  if (DAT_2001de15 == 0) {
    zw_scope_persistance();
  }
  else {
    FUN_0801841c();
  }
  FUN_0801876c();
  zw_scope_channel_level_();
  zw_scope_trigger_();
  zw_scope_trigger_icons_();
  zw_draw_measurement_labels_setup_();
  FUN_08026f94();
  zw_scope_cursor_measurements_window();
  zw_scope_siggen_window();
  zw_dmm_setup_();
  zw_scope_frequency_meter();
  zw_scope_counter();
  zw_scope_menu();
  zw_scope_menu_math_roll();
  FUN_0801b950();
  FUN_0802bc90();
  if (shift_key_ != 0) {
    zw_draw_string_small("Shift",0x10d,0x13,5,1,2);
  }
  if (RTAuto_enable_ != 0) {
    zw_draw_string_small("RTAuto",0x105,0x13,6,1,2);
  }
  if (ch1_20mhz_limit != 0) {
    zw_draw_string_small("20",0x130,0x96,2,0x3f,0x20);
    zw_draw_string_small("M",0x137,0xa1,1,0x3f,0x20);
  }
  if (ch2_20mhz_limit != 0) {
    zw_draw_string_small("20",0x130,0xb4,2,0x5f,0x20);
    zw_draw_string_small("M",0x137,0xbf,1,0x5f,0x20);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_08027f1c(void)

{
  byte *pbVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  byte *pbVar7;
  
  pbVar7 = _global_settings * 0.0;
  if (pbVar7 < 0xbb9) {
    uVar6 = 1;
  }
  else {
    uVar6 = (pbVar7 != (pbVar7 / 3000) * 3000) + pbVar7 / 3000;
  }
  uVar6 = pbVar7 / uVar6;
  if ((scan_mode__0_start_1_pretrigger_2_block_3_roll == '\0') || (roll_mode_enable != '\0')) {
    if (fast_render_flag_ == '\0') {
      pbVar7 = FUN_08018bbc(pbVar7 & 0xffff);
    }
    else {
      pbVar7 = generate_interpolated__FUN_08019078();
    }
  }
  if (uVar6 != 0) {
    pbVar1 = &DAT_2001bb30;
    pbVar5 = &DAT_2001af78;
    do {
      uVar2 = *pbVar1 + 0x20;
      iVar3 = 0xf8 - *pbVar5;
      iVar4 = (iVar3 < 0xda) * iVar3 + (iVar3 >= 0xda) * 0xda;
      iVar3 = 0x3c;
      if (0x3b < uVar2) {
        iVar3 = (uVar2 < 0x104) * pbVar7 + (uVar2 >= 0x104) * 0x104;
      }
      pbVar1 = pbVar1 + 1;
      pbVar7 = framebuffer_ + ((iVar4 < 0x12) * 0x12 + (iVar4 >= 0x12) * iVar4) * 0x140;
      pbVar7[iVar3] = 5;
      pbVar5 = pbVar5 + 1;
    } while (pbVar1 != &DAT_2001bb30 + uVar6);
  }
  return;
}




void zw_scope_init(int param_1)

{
  memset(framebuffer_,param_1,76800);
  zw_scope_XY_fullscreen_();
  FUN_08027f1c();
  FUN_08029d40();
  zw_scope_menu();
  zw_scope_menu_math_roll();
  zw_scope_siggen_window();
  FUN_0801b950();
  FUN_0802bc90();
  if (shift_key_ != '\0') {
    zw_draw_string_small("Shift",0x10c,0x13,5,1,2);
  }
  if (RTAuto_enable_ != '\0') {
    zw_draw_string_small("RTAuto",0x10c,0x13,6,1,2);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void zw_debug_dump(void)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  
  if ((scan_mode__0_start_1_pretrigger_2_block_3_roll != '\0') && (roll_mode_enable == '\0')) {
    return;
  }
  zw_power_control_(0);
  if (fast_render_flag_ != 0) {
    generate_interpolated__FUN_08019078();
    puVar7 = &DAT_2001bb30;
    puts("--------CH1--------\r");
    do {
      pcVar2 = *puVar7;
      puVar7 = puVar7 + 1;
      wm_printf("%d ",pcVar2);
    } while (puVar7 != 0x2001bc5c);
    if (ch2_enabled != 1) {
      return;
    }
    puVar7 = &DAT_2001af78;
    puts("\r\n--------CH2--------\r");
    do {
      pcVar2 = *puVar7;
      puVar7 = puVar7 + 1;
      wm_printf("%d \r\n",pcVar2);
    } while (puVar7 != 0x2001b0a4);
    return;
  }
  bVar1 = _global_settings * 0.0 < 60000;
  uVar4 = bVar1 * 60000 + !bVar1 * 60000;
  uVar5 = uVar4 / 3000;
  uVar4 = uVar4 % 3000;
  puts("--------CH1--------\r");
  if (uVar5 == 0) {
    if (uVar4 == 0) goto LAB_08028120;
    iVar6 = 0;
  }
  else {
    iVar3 = 0;
    iVar6 = uVar5 * 3000;
    do {
      FUN_08019190(iVar3,3000);
      puVar7 = &DAT_2001bb30;
      do {
        pcVar2 = *puVar7;
        puVar7 = puVar7 + 1;
        wm_printf("%d ",pcVar2);
      } while (puVar7 != &DAT_2001c6e8);
      iVar3 = iVar3 + 3000;
      (hwdg.Instance)->CLR = 1;
    } while (iVar3 != uVar5 * 3000);
    if (uVar4 == 0) {
LAB_08028120:
      goto joined_r0x08028128;
    }
  }
  FUN_08019190(iVar6,3000);
  puVar7 = &DAT_2001bb30;
  do {
    pcVar2 = *puVar7;
    puVar7 = puVar7 + 1;
    wm_printf("%d ",pcVar2);
  } while (puVar7 != &DAT_2001bb30 + uVar4);
joined_r0x08028128:
  if (ch2_enabled == 1) {
    puts("\r\n--------CH2--------\r");
    iVar6 = 0;
    if (uVar5 != 0) {
      iVar6 = uVar5 * 3000;
      iVar3 = 0;
      do {
        FUN_08019190(iVar3,3000);
        puVar7 = &DAT_2001af78;
        do {
          pcVar2 = *puVar7;
          puVar7 = puVar7 + 1;
          wm_printf("%d ",pcVar2);
        } while (puVar7 != &DAT_2001bb30);
        iVar3 = iVar3 + 3000;
        (hwdg.Instance)->CLR = 1;
      } while (iVar3 != iVar6);
    }
    if (uVar4 != 0) {
      puVar7 = &DAT_2001af78;
      FUN_08019190(iVar6,3000);
      do {
        pcVar2 = *puVar7;
        puVar7 = puVar7 + 1;
        wm_printf("%d ",pcVar2);
      } while (&DAT_2001af78 + uVar4 != puVar7);
      return;
    }
  }
  return;
}




undefined4 zw_IntToStr(uint param_1,char *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  *param_2 = param_1 / 1000 + '0';
  if (param_1 < 1000) {
    if (param_1 < 100) {
      *param_2 = param_1 / 10 + '0';
      uVar1 = 2;
      if (param_1 < 10) {
        uVar1 = 1;
      }
      iVar2 = 0;
      if (9 < param_1) {
        iVar2 = 1;
      }
      goto LAB_08028284;
    }
    *param_2 = param_1 / 100 + '0';
    uVar1 = 3;
    iVar2 = 2;
    iVar3 = 1;
  }
  else {
    param_2[1] = (param_1 % 1000) / 100 + '0';
    uVar1 = 4;
    iVar2 = 3;
    iVar3 = 2;
  }
  param_2[iVar3] = (param_1 % 100) / 10 + '0';
LAB_08028284:
  param_2[iVar2] = param_1 + (param_1 / 10) * -10 + '0';
  return uVar1;
}




uint zw_draw_string_small(byte *str,uint positionX,int positionY,int strlen,byte foregroundColor,short backgroundColor)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  uint uVar7;
  uint uVar8;
  
  if (strlen == 0) {
    return 0;
  }
  pbVar4 = str + (strlen - 1U & 0xffff) + 1;
  uVar7 = positionX;
  do {
    if (*str == 0x2e) {
      uVar8 = 4;
    }
    else {
      uVar8 = 8;
    }
    pbVar6 = image_fonts_small_EN + (*str - 0x20) * 0xd;
    pbVar5 = framebuffer_ + uVar7 + positionY * 0x140;
    do {
      bVar1 = *pbVar6;
      uVar3 = 0;
      pbVar2 = pbVar5;
LAB_08028360:
      do {
        if ((0x80 >> (uVar3 & 0x3f) & bVar1) == 0) {
          if (backgroundColor != 0x20) {
            uVar3 = uVar3 + 1;
            *pbVar2 = backgroundColor;
            pbVar2 = pbVar2 + 1;
            if (uVar8 <= (uVar3 & 0xff)) break;
            goto LAB_08028360;
          }
        }
        else {
          *pbVar2 = foregroundColor;
        }
        uVar3 = uVar3 + 1;
        pbVar2 = pbVar2 + 1;
      } while ((uVar3 & 0xff) < uVar8);
      pbVar5 = pbVar5 + 0x140;
      pbVar6 = pbVar6 + 1;
    } while (pbVar5 != framebuffer_ + positionY * 0x140 + uVar7 + 0x1040);
    str = str + 1;
    uVar7 = uVar7 + uVar8 & 0x7fff;
    if (str == pbVar4) {
      return uVar7 - positionX & 0xffff;
    }
  } while( true );
}




uint zw_draw_string_large(byte *str,uint positionX,int positionY,int strlen,byte foregroundColor,short backgroundColor)

{
  uint uVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  
  if (strlen == 0) {
    return 0;
  }
  pbVar2 = str + (strlen - 1U & 0xffff) + 1;
  uVar7 = positionX;
  do {
    if (*str == 0x2e) {
      uVar4 = 4;
    }
    else {
      uVar4 = 10;
    }
    iVar6 = (*str - 0x20) * 0x20;
    pbVar5 = framebuffer_ + uVar7 + positionY * 0x140;
    do {
      uVar1 = 0;
      pbVar3 = pbVar5;
LAB_08028432:
      do {
        if ((image_fonts_large_EN[(uVar1 >> 3) + iVar6] & 0x80 >> (uVar1 & 7)) == 0) {
          if (backgroundColor != 0x20) {
            uVar1 = uVar1 + 1 & 0xff;
            *pbVar3 = backgroundColor;
            pbVar3 = pbVar3 + 1;
            if (uVar4 == uVar1) break;
            goto LAB_08028432;
          }
        }
        else {
          *pbVar3 = foregroundColor;
        }
        uVar1 = uVar1 + 1 & 0xff;
        pbVar3 = pbVar3 + 1;
      } while (uVar4 != uVar1);
      pbVar5 = pbVar5 + 0x140;
      iVar6 = iVar6 + 2;
    } while (framebuffer_ + positionY * 0x140 + uVar7 + 0x1400 != pbVar5);
    str = str + 1;
    uVar7 = uVar7 + uVar4 & 0x7fff;
    if (pbVar2 == str) {
      return uVar7 - positionX & 0xffff;
    }
  } while( true );
}




ushort zw_draw_string_large_integer(uint number,undefined4 positionX,undefined4 positionY,undefined4 fg_color,undefined2 bg_color,byte digits)

{
  short sVar1;
  ushort uVar2;
  undefined1 auStack_20 [8];
  
  if ((number < 10000) && (digits < 5)) {
    sVar1 = zw_IntToStr(number,auStack_20);
    zw_draw_string_large(auStack_20,positionX,positionY,sVar1,fg_color,bg_color);
    uVar2 = sVar1 * 10 & 0xff;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}




void zw_siggen_7_segment_digits(short param_1,int param_2,int param_3,byte param_4,short param_5,char param_6)

{
  int iVar1;
  uint uVar2;
  byte *pbVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  
  if (param_6 == '\0') {
    pbVar7 = image_fonts_signal_generator_window_digits_large + param_1 * 0x51;
    iVar8 = 3;
    uVar4 = 0x13;
    iVar1 = 0x1b;
  }
  else {
    pbVar7 = image_fonts_signal_generator_window_digits_small + param_1 * 0x1c;
    iVar8 = 2;
    uVar4 = 10;
    iVar1 = 0xe;
  }
  pbVar5 = framebuffer_ + param_2 + param_3 * 0x140;
  iVar6 = 0;
  do {
    uVar2 = 0;
    pbVar3 = pbVar5;
LAB_0802857a:
    do {
      if ((pbVar7[(uVar2 >> 3) + iVar6] & 0x80 >> (uVar2 & 7)) == 0) {
        if (param_5 != 0x20) {
          uVar2 = uVar2 + 1 & 0xff;
          *pbVar3 = param_5;
          pbVar3 = pbVar3 + 1;
          if (uVar2 == uVar4) break;
          goto LAB_0802857a;
        }
      }
      else {
        *pbVar3 = param_4;
      }
      uVar2 = uVar2 + 1 & 0xff;
      pbVar3 = pbVar3 + 1;
    } while (uVar2 != uVar4);
    pbVar5 = pbVar5 + 0x140;
    iVar6 = iVar6 + iVar8;
    if (pbVar5 == framebuffer_ + param_2 + (param_3 + (iVar1 - 1U & 0xff)) * 0x140 + 0x140) {
      return;
    }
  } while( true );
}




void FUN_080285e4(undefined1 *param_1,uint param_2,int param_3)

{
  *param_1 = 0x20;
  param_1[1] = 0x20;
  param_1[2] = 0x20;
  if (param_3 < 1) {
    if ((param_3 != 0) || (param_2 < 1000)) {
      *param_1 = 0x75;
      param_1[1] = 0x48;
      param_1[2] = 0x7a;
      __floatundidf(param_2,param_3);
      return;
    }
    if (param_2 < 1000000) {
      *param_1 = 0x6d;
      param_1[1] = 0x48;
      param_1[2] = 0x7a;
      __floatundidf(param_2,0);
      __divdf3();
      return;
    }
    if (param_2 < 1000000000) {
      *param_1 = 0x48;
      param_1[1] = 0x7a;
      __floatundidf(param_2,0);
      __divdf3();
      return;
    }
  }
  else if ((0xe8 < param_3) || ((param_3 == 0xe8 && (0xd4a50fff < param_2)))) {
    if ((param_3 < 0x38d7f) && ((param_3 != 0x38d7e || (param_2 < 0xa4c68000)))) {
      *param_1 = 0x4d;
      param_1[1] = 0x48;
      param_1[2] = 0x7a;
      __floatundidf(param_2,param_3);
      __divdf3();
      return;
    }
    *param_1 = 0x47;
    param_1[1] = 0x48;
    __floatundidf(param_2,param_3);
    __divdf3();
    return;
  }
  *param_1 = 0x4b;
  param_1[1] = 0x48;
  param_1[2] = 0x7a;
  __floatundidf(param_2,param_3);
  __divdf3();
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void FUN_08028700(undefined1 *param_1,int param_2,int param_3,int param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  
  lVar2 = CONCAT44(param_3,param_2);
  if (param_3 < 0) {
    lVar2 = -CONCAT44(param_3,param_2);
  }
  iVar10 = lVar2 >> 0x20;
  uVar8 = lVar2;
  if (param_4 == 1) {
    if (lVar2 < 0x100000000) {
      if ((iVar10 == 0) && (999 < uVar8)) {
        if (9999 < uVar8) goto LAB_08028740;
        uVar9 = 5;
        iVar10 = 0;
      }
      else {
        uVar9 = 0;
        iVar10 = 0;
      }
LAB_080287f8:
      lVar2 = lVar2 + CONCAT44(iVar10,uVar9);
      if (lVar2 == 0) {
        *param_1 = 0x48;
        param_1[1] = 0x7a;
        param_1[2] = 0x20;
        return;
      }
    }
    else {
LAB_08028740:
      uVar9 = 0x32;
      iVar10 = 0;
      uVar3 = 100000;
      iVar6 = 0;
      iVar11 = 0x13;
      do {
        if ((lVar2 < CONCAT44(iVar6,uVar3)) || ((false && (uVar8 < uVar3)))) goto LAB_080287f8;
        uVar1 = uVar3;
        uVar3 = uVar1 * 10;
        iVar6 = iVar6 * 10 + (uVar1 * 10 >> 0x20);
        uVar1 = uVar9;
        uVar9 = uVar1 * 10;
        iVar10 = iVar10 * 10 + (uVar1 * 10 >> 0x20);
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
    }
    if (lVar2 < 0x100000000) {
      if ((lVar2 >> 0x20 != 0) || (lVar2 < 1000)) {
        *param_1 = 0x75;
        param_1[1] = 0x48;
        param_1[2] = 0x7a;
        return;
      }
      goto LAB_080288ac;
    }
  }
  else {
    if (param_4 == 3) {
      *param_1 = 0x25;
      __floatsidf(uVar8);
      __divdf3();
      __truncdfsf2();
      return;
    }
    if (param_2 == 0 && param_3 == 0) {
      if (param_4 == 0) {
        uVar5 = 0x56;
      }
      else {
        if (param_4 != 2) {
          return;
        }
        uVar5 = 0x73;
      }
      *param_1 = uVar5;
      param_1[1] = 0x20;
      return;
    }
    if (lVar2 < 0x100000000) {
      if ((iVar10 != 0) || (uVar8 < 1000)) {
        if (param_4 == 0) {
          *param_1 = 0x75;
          param_1[1] = 0x56;
          return;
        }
        if (param_4 != 2) {
          return;
        }
        *param_1 = 0x70;
        param_1[1] = 0x73;
        return;
      }
LAB_080288ac:
      if (lVar2 < 0x100000000) {
        if ((lVar2 >> 0x20 != 0) || (lVar2 < 1000000)) {
          if (param_4 == 0) {
            *param_1 = 0x6d;
            param_1[1] = 0x56;
          }
          else if (param_4 == 1) {
            *param_1 = 0x6d;
            param_1[1] = 0x48;
            param_1[2] = 0x7a;
          }
          else if (param_4 == 2) {
            *param_1 = 0x6e;
            param_1[1] = 0x73;
          }
          uVar4 = 10;
          uVar7 = 0;
          goto LAB_08028880;
        }
        if (lVar2 < 1000000000) {
          if (param_4 == 0) {
            *param_1 = 0x56;
            param_1[1] = 0x20;
          }
          else if (param_4 == 1) {
            *param_1 = 0x48;
            param_1[1] = 0x7a;
            param_1[2] = 0x20;
          }
          else if (param_4 == 2) {
            *param_1 = 0x75;
            param_1[1] = 0x73;
          }
          uVar4 = 10000;
          uVar7 = 0;
          goto LAB_08028880;
        }
      }
    }
  }
  if ((999999999999 < lVar2) || ((false && (0xd4a50fff < lVar2)))) {
    if ((999999999999999 < lVar2) || ((false && (0xa4c67fff < lVar2)))) {
      if (param_4 == 1) {
        *param_1 = 0x47;
        param_1[1] = 0x48;
        param_1[2] = 0x20;
      }
      else if (param_4 == 2) {
        *param_1 = 0x4b;
        param_1[1] = 0x73;
      }
      uVar4 = 0x4e72a000;
      uVar7 = 0x918;
    }
    else {
      if (param_4 == 1) {
        *param_1 = 0x4d;
        param_1[1] = 0x48;
        param_1[2] = 0x7a;
      }
      else if (param_4 == 2) {
        *param_1 = 0x73;
        param_1[1] = 0x20;
      }
      uVar4 = 0x540be400;
      uVar7 = 2;
    }
  }
  else {
    if (param_4 == 0) {
      *param_1 = 0x4b;
      param_1[1] = 0x56;
    }
    else if (param_4 == 1) {
      *param_1 = 0x4b;
      param_1[1] = 0x48;
      param_1[2] = 0x7a;
    }
    else if (param_4 == 2) {
      *param_1 = 0x6d;
      param_1[1] = 0x73;
    }
    uVar4 = 10000000;
    uVar7 = 0;
  }
LAB_08028880:
  __divdi3(lVar2,lVar2 >> 0x20,uVar4,uVar7);
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: stack


uint zw_scope_int_values(uint param_1,int param_2,uint param_3,undefined4 param_4,uint param_5,char param_6)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  char cVar10;
  uint uVar11;
  float in_vr0;
  uint uVar12;
  float fVar13;
  undefined1 auStack_48 [4];
  char local_44 [8];
  
  uVar4 = param_3 & 0xffff;
  param_3 = param_3 >> 0x10;
  if ((param_1 == 1) && (param_2 == 0)) {
    if (param_6 != '\0') {
      uVar4 = zw_draw_string_large();
      return uVar4;
    }
    uVar4 = zw_draw_string_small("---",uVar4,param_3,3);
    return uVar4;
  }
  if (param_5._2_2_ == 2) {
    uVar3 = param_1 * 100;
    iVar1 = (param_1 * 100 >> 0x20) + param_2 * 100;
  }
  else {
    uVar3 = param_1;
    iVar1 = param_2;
    if (param_5._2_2_ == 1) {
      uVar3 = param_1 * 10;
      iVar1 = (param_1 * 10 >> 0x20) + param_2 * 10;
    }
  }
  uVar7 = param_5 & 0xffff;
  if ((param_5._3_1_ == '\x01') && (3 < uVar7)) {
    FUN_080285e4(auStack_48,param_1,param_2);
    __truncdfsf2();
  }
  else {
    FUN_08028700(auStack_48,uVar3,iVar1,param_5._3_1_);
  }
  if (in_vr0 < 0.0) {
    uVar3 = 100000;
  }
  else {
    iVar6 = 6;
    iVar1 = 1;
    fVar13 = in_vr0;
    do {
      iVar2 = iVar1;
      fVar13 = fVar13 / 0.0;
      if (fVar13 < 0.0) break;
      iVar6 = iVar6 + -1;
      iVar1 = iVar2 * 10;
    } while (iVar6 != 0);
    uVar3 = iVar2 * 1000000;
  }
  if (uVar7 != 0) {
    uVar5 = 0;
    uVar9 = 0;
    uVar11 = 0xf;
    do {
      while( true ) {
        uVar12 = (in_vr0 * 100000.0) / uVar3;
        uVar8 = uVar9 + 1 & 0xff;
        local_44[uVar9] = uVar12 + (uVar12 / 10) * -10 + '0';
        if (uVar3 != 100000) break;
        uVar5 = uVar5 + 1 & 0xff;
        local_44[uVar8] = '.';
        uVar3 = 10000;
        uVar9 = uVar9 + 2 & 0xff;
        uVar11 = uVar8;
        if (uVar7 <= uVar5) goto LAB_08028adc;
      }
      uVar5 = uVar5 + 1 & 0xff;
      uVar3 = uVar3 / 10;
      uVar9 = uVar8;
    } while (uVar5 < uVar7);
LAB_08028adc:
    if (uVar11 < uVar7) {
      uVar7 = uVar7 + 1 & 0xffff;
    }
  }
  if (param_5._3_1_ == '\x01') {
    cVar10 = '\x03';
  }
  else {
    cVar10 = (param_5._3_1_ != '\x03') + '\x01';
  }
  if (param_2 < 0) {
    if (param_6 == '\0') {
      iVar1 = zw_draw_string_small("-",uVar4,param_3,1);
LAB_08028b76:
      iVar6 = zw_draw_string_small(local_44,uVar4 + iVar1 & 0xffff,param_3,uVar7);
      uVar3 = iVar1 + iVar6 & 0xffff;
      iVar1 = zw_draw_string_small(auStack_48,uVar4 + uVar3 & 0xffff,param_3,cVar10);
      return iVar1 + uVar3 & 0xffff;
    }
    iVar1 = zw_draw_string_large();
  }
  else {
    iVar1 = 0;
    if (param_6 == '\0') goto LAB_08028b76;
    iVar1 = 0;
  }
  iVar6 = zw_draw_string_large(local_44,uVar4 + iVar1 & 0xffff,param_3,uVar7);
  uVar3 = iVar6 + iVar1 & 0xffff;
  iVar1 = zw_draw_string_large(auStack_48,uVar4 + uVar3 & 0xffff,param_3,cVar10);
  return iVar1 + uVar3 & 0xffff;
}




void zw_draw_CN(int glyphIndex,undefined2 positionX,undefined2 positionY,undefined2 foregroundColor,undefined2 backgroundColor)

{
  undefined2 local_14;
  undefined2 uStack_12;
  undefined2 uStack_10;
  undefined2 uStack_e;
  byte *pbStack_c;
  undefined2 uStack_8;
  undefined2 uStack_6;
  
  uStack_10 = 0xc;
  uStack_e = 0xc;
  pbStack_c = image_fonts_CN + glyphIndex * 0x18;
  uStack_6 = backgroundColor;
  local_14 = positionX;
  uStack_12 = positionY;
  uStack_8 = foregroundColor;
  zw_drawGlyph2(&local_14);
  return;
}




short zw_dmm_chars_24x28(int param_1,short param_2,undefined2 param_3,undefined2 param_4,undefined2 param_5)

{
  short local_18;
  undefined2 uStack_16;
  short sStack_14;
  undefined2 uStack_12;
  byte *pbStack_10;
  undefined2 uStack_c;
  undefined2 uStack_a;
  
  if (param_1 != 0xff) {
    sStack_14 = 0x12;
    uStack_12 = 0x1c;
    pbStack_10 = image_fonts_dmm_digits_small + param_1 * 0x54;
    uStack_a = param_5;
    if (param_1 == 0x2d) {
      pbStack_10 = image_fonts_dmm_hyphen_small;
    }
    else if (param_1 == 0x4c) {
      pbStack_10 = image_fonts_dmm_L_small;
    }
    else if (param_1 == 0x45) {
      pbStack_10 = image_fonts_dmm_E_small;
    }
    else if (param_1 == 0x72) {
      pbStack_10 = image_fonts_dmm_r_small;
    }
    else if (param_1 == 0x43) {
      pbStack_10 = image_fonts_dmm_C_small;
    }
    else if (param_1 == 0x2e) {
      sStack_14 = 8;
      pbStack_10 = image_fonts_dmm___small;
    }
    local_18 = param_2;
    uStack_16 = param_3;
    uStack_c = param_4;
    zw_drawGlyph2(&local_18);
    return param_2 + sStack_14 + 2;
  }
  return param_2 + 0x12;
}




short zw_dmm_chars_40x81(int param_1,short param_2,undefined2 param_3,undefined2 param_4,undefined2 param_5)

{
  short local_18;
  undefined2 uStack_16;
  short sStack_14;
  undefined2 uStack_12;
  byte *pbStack_10;
  undefined2 uStack_c;
  undefined2 uStack_a;
  
  if (param_1 != 0xff) {
    sStack_14 = 0x28;
    uStack_12 = 0x51;
    pbStack_10 = image_fonts_dmm_digits_large + param_1 * 0x195;
    uStack_a = param_5;
    if (param_1 == 0x2d) {
      pbStack_10 = image_fonts_dmm_hyphen_large;
    }
    else if (param_1 == 0x4c) {
      pbStack_10 = image_fonts_dmm_L_large;
    }
    else if (param_1 == 0x45) {
      pbStack_10 = image_fonts_dmm_E_large;
    }
    else if (param_1 == 0x72) {
      pbStack_10 = image_fonts_dmm_r_large;
    }
    else if (param_1 == 0x43) {
      pbStack_10 = image_fonts_dmm_C_large;
    }
    else if (param_1 == 0x2e) {
      sStack_14 = 0x14;
      pbStack_10 = image_fonts_dmm___large;
    }
    local_18 = param_2;
    uStack_16 = param_3;
    uStack_c = param_4;
    zw_drawGlyph2(&local_18);
    return param_2 + sStack_14 + 2;
  }
  return param_2 + 0x28;
}




short zw_siggen_chars_32x53(int param_1,short param_2,undefined2 param_3,undefined2 param_4,undefined2 param_5)

{
  short local_18;
  undefined2 uStack_16;
  short sStack_14;
  undefined2 uStack_12;
  byte *pbStack_10;
  undefined2 uStack_c;
  undefined2 uStack_a;
  
  if (param_1 != 0xff) {
    sStack_14 = 0x20;
    uStack_12 = 0x35;
    pbStack_10 = image_fonts_signal_generator_full_screen_digits + param_1 * 0xd4;
    uStack_a = param_5;
    if (param_1 == 0x2e) {
      sStack_14 = 0x12;
      pbStack_10 = image_fonts_signal_generator_full_screen____;
    }
    local_18 = param_2;
    uStack_16 = param_3;
    uStack_c = param_4;
    zw_drawGlyph2(&local_18);
    return param_2 + sStack_14 + 2;
  }
  return param_2 + 0x20;
}




void zw_scope_active_channel_icon_Math_label(void)

{
  if (DAT_2000a118 == active_channel_0_ch1_1_ch2_2_math) {
    if (DAT_2000a115 == 0) goto LAB_08028e80;
    DAT_2000a115 = DAT_2000a115 - 1;
    if ((DAT_2000a115 & 7) < 4) goto LAB_08028e80;
  }
  else {
    DAT_2000a118 = active_channel_0_ch1_1_ch2_2_math;
    DAT_2000a115 = 0x1e;
  }
  if (system_status_ != '\x03') {
    return;
  }
LAB_08028e80:
  if (active_channel_0_ch1_1_ch2_2_math == '\0') {
    ui_element_channel_switch.color_index = 0x3f;
    ui_element_channel_switch.image = image_scope_icon_channel_switch_1;
    zw_draw_element(&ui_element_channel_switch);
    ui_element_channel_switch.color_index = 8;
    ui_element_channel_switch.image = image_scope_icon_channel_switch_2;
    zw_draw_element(&ui_element_channel_switch);
    return;
  }
  if (active_channel_0_ch1_1_ch2_2_math != '\x01') {
    zw_draw_rectangle_filled(ui_element_channel_switch.x,ui_element_channel_switch.y,*ui_element_channel_switch.image,*(ui_element_channel_switch.image + 1),0);
    zw_draw_string_small("Math",ui_element_channel_switch.x,ui_element_channel_switch.y,4,2,0x20);
    return;
  }
  ui_element_channel_switch.color_index = 0x5f;
  ui_element_channel_switch.image = image_scope_icon_channel_switch_2;
  zw_draw_element(&ui_element_channel_switch);
  ui_element_channel_switch.color_index = 8;
  ui_element_channel_switch.image = image_scope_icon_channel_switch_1;
  zw_draw_element(&ui_element_channel_switch);
  return;
}




void zw_scope_icons_init(void)

{
  ui_element_channel_level_0.y = 0x32;
  ui_element_channel_level_0.x = 6;
  ui_element_channel_level_0.image = image_scope_icon_channel_level;
  ui_element_channel_level_0.color_index = 0x3f;
  ui_element_channel_level_0.flags = 0x20;
  ui_element_channel_level_1.x = 6;
  ui_element_channel_level_1.y = 100;
  ui_element_channel_level_1.image = image_scope_icon_channel_level;
  ui_element_channel_level_1.color_index = 0x5f;
  ui_element_channel_level_1.flags = 0x20;
  ui_element_channel_level_2.y = 100;
  ui_element_channel_level_2.x = 6;
  ui_element_channel_level_2.image = image_scope_icon_channel_level;
  ui_element_channel_level_2.color_index = 2;
  ui_element_channel_level_2.flags = 0x20;
  ui_element_arrow_down_0.flags = 0x20;
  ui_element_arrow_down_0.x = 0x96;
  ui_element_arrow_down_0.y = 0x12;
  ui_element_arrow_down_0.image = image_scope_icon_arrow_down;
  ui_element_arrow_down_0.color_index = 0x3f;
  ui_element_arrow_right.flags = 0x20;
  ui_element_arrow_right.x = 0x3c;
  ui_element_arrow_right.y = 0x78;
  ui_element_arrow_right.color_index = 0x5f;
  ui_element_arrow_right.image = image_scope_icon_arrow_right;
  ui_element_trigger.x = 300;
  ui_element_trigger.y = 0x78;
  ui_element_trigger.flags = 0x20;
  ui_element_trigger.image = image_scope_icon_trigger;
  ui_element_trigger.color_index = 1;
  ui_element_arrow_down_1.y = 0x12;
  ui_element_arrow_down_1.x = 0x96;
  ui_element_arrow_down_1.image = image_scope_icon_arrow_down;
  ui_element_arrow_down_1.color_index = 7;
  ui_element_arrow_down_1.flags = 0x20;
  ui_element_arrow_T_down.flags = 0x20;
  ui_element_arrow_T_down.x = 0x96;
  ui_element_arrow_T_down.y = 1;
  ui_element_arrow_T_down.color_index = 1;
  ui_element_arrow_T_down.image = image_scope_icon_arrow_T_down;
  ui_element_trigger_edge.flags = 0x20;
  ui_element_trigger_edge.h = 0xd;
  ui_element_trigger_edge.x = 0x10f;
  ui_element_trigger_edge.image = image_scope_icon_trigger_rising_edge;
  ui_element_trigger_edge.y = 1;
  ui_element_trigger_edge.color_index = 5;
  ui_element_trigger_edge.w = 10;
  ui_element_battery.x = 290;
  ui_element_battery.image = image_scope_icon_battery;
  ui_element_battery.y = 4;
  ui_element_battery.color_index = 1;
  ui_element_battery.flags = 0;
  ui_element_ch1_icon.image = image_scope_icon_channel_1;
  ui_element_ch1_icon.x = 10;
  ui_element_ch1_icon.y = 0xe1;
  ui_element_ch1_icon.color_index = 0x3f;
  ui_element_ch1_icon.flags = 0x20;
  ui_element_ch2_icon.flags = 0x20;
  ui_element_ch2_icon.color_index = 0x5f;
  ui_element_ch2_icon.x = 0xca;
  ui_element_ch2_icon.y = 0xe1;
  ui_element_ch2_icon.image = image_scope_icon_channel_2;
  ui_element_measurement_label_bg.color_index = 4;
  ui_element_measurement_label_bg.x = 0x82;
  ui_element_measurement_label_bg.y = 0xde;
  ui_element_measurement_label_bg.flags = 0x20;
  ui_element_measurement_label_bg.image = image_scope_measurement_label_background;
  ui_element_ch1_coupling.flags = 0x20;
  ui_element_ch1_coupling.x = 0x4b;
  ui_element_ch1_coupling.color_index = 1;
  ui_element_ch1_coupling.y = 0xe4;
  ui_element_ch1_coupling.image = image_scope_icon_dc;
  ui_element_ch2_coupling.image = image_scope_icon_dc;
  ui_element_ch2_coupling.color_index = 1;
  ui_element_ch2_coupling.flags = 0x20;
  ui_element_ch2_coupling.x = 0x10b;
  ui_element_ch2_coupling.y = 0xe4;
  ui_element_run_pause.flags = 0x20;
  ui_element_run_pause.color_index = 3;
  ui_element_run_pause.x = 10;
  ui_element_run_pause.y = 2;
  ui_element_run_pause.image = image_scope_icon_run;
  ui_element_auto_normal.image = image_scope_icon_run;
  ui_element_auto_normal.flags = 0x20;
  ui_element_auto_normal.x = 0xde;
  ui_element_auto_normal.y = 2;
  ui_element_auto_normal.color_index = 6;
  ui_element_channel_switch.flags = 0x20;
  ui_element_channel_switch.x = 0x2a;
  ui_element_channel_switch.y = 2;
  ui_element_channel_switch.color_index = 0x3f;
  ui_element_channel_switch.image = image_scope_icon_channel_switch_1;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void zw_ui_all_init(void)

{
  int iVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  
  _DAT_2000a0d4 = 0x19;
  DAT_2000a0cc = 500;
  DAT_2000a0d0 = 0;
  _DAT_2000a0da = 0x20;
  DAT_2000a0df = 0;
  _DAT_2000a0d6 = 0xde;
  _DAT_2000a0dc = 3;
  _DAT_2000a0d8 = 1;
  DAT_2000a0e0._0_1_ = 1;
  DAT_2000a0f8._0_1_ = 1;
  DAT_2000a0e4 = 500;
  DAT_2000a0e8 = 0;
  _DAT_2000a0ec = 0xd9;
  _DAT_2000a0f2 = 0x20;
  DAT_2000a0f7 = 0;
  _DAT_2000a0ee = 0xde;
  _DAT_2000a0f4 = 3;
  _DAT_2000a0f0 = 1;
  _DAT_2000a10a = 0x20;
  DAT_2000a0fc = 200000;
  DAT_2000a100 = 0;
  _DAT_2000a104 = 0x87;
  _DAT_2000a106 = 0xde;
  _DAT_2000a10c = 3;
  _DAT_2000a108 = 1;
  DAT_2000a10f = 2;
  DAT_2000a110 = 1;
  if (settings_ch2_color_0_green_1_purple_2_cyan == '\x01') {
    uVar4 = 0;
    puVar5 = &ch2_configured_color_gradient_0_31;
    uVar3 = 0;
    iVar1 = 0x20;
    do {
      uVar2 = uVar4 | uVar3;
      uVar4 = uVar4 + 0x800;
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar3 = uVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  else if (settings_ch2_color_0_green_1_purple_2_cyan == '\x02') {
    uVar4 = 0;
    puVar5 = &ch2_configured_color_gradient_0_31;
    uVar3 = 0;
    iVar1 = 0x20;
    do {
      uVar2 = uVar3 | 0x20 | uVar4;
      uVar4 = uVar4 + 0x40;
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar3 = uVar3 + 1 & 0xff;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  zw_scope_icons_init();
  zw_draw_rectangle_filled(0,0,0x140,0xf0,2);
  return;
}




void zw_scope_memory_bar(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  zw_draw_line_horizontal(0x70,7,0x60,1);
  iVar4 = sample_rate_hz_h;
  uVar1 = FUN_0801dc8c(sample_rate_hz_l,sample_rate_hz_h,timebase_val_ns_l * 12000,(timebase_val_ns_l * 12000 >> 0x20) + timebase_val_ns_h * 12000);
  iVar4 = (uVar1 * 0x60 >> 0x20) + iVar4 * 0x60;
  uVar1 = __divdi3(uVar1 * 0x60,iVar4,buffer_depth_l,buffer_depth_h);
  iVar3 = sample_rate_hz_h;
  uVar2 = FUN_0801dc8c(sample_rate_hz_l,sample_rate_hz_h,roll_mode_view_offset__l,roll_mode_view_offset__h);
  iVar3 = __divdi3(uVar2 * 0x60,(uVar2 * 0x60 >> 0x20) + iVar3 * 0x60,buffer_depth_l,buffer_depth_h);
  if ((iVar4 < 0) || ((iVar4 == 0 && (uVar1 < 6)))) {
    uVar1 = 6;
    iVar4 = 0;
  }
  uVar1 = uVar1 >> 1 | iVar4 << 0x1f;
  iVar4 = iVar3 - uVar1;
  iVar3 = iVar3 + uVar1;
  iVar5 = (iVar4 < 0x30) * iVar4 + (iVar4 >= 0x30) * 0x30;
  iVar4 = (iVar3 < 0x30) * iVar3 + (iVar3 >= 0x30) * 0x30;
  iVar3 = (iVar5 < -0x30) * -0x30 + (iVar5 >= -0x30) * iVar5;
  uVar2 = ((iVar4 < -0x30) * -0x30 + (iVar4 >= -0x30) * iVar4) - iVar3;
  uVar1 = iVar3 + 0xa0U & 0xffff;
  uVar6 = uVar2 & 0xffff;
  zw_draw_rectangle(uVar1,4,uVar6,7);
  if (8 < uVar2) {
    uVar1 = uVar1 + 4 & 0xffff;
    uVar2 = uVar6 - 8 & 0xffff;
    zw_draw_line_horizontal(uVar1,4,uVar2,0);
    zw_draw_line_horizontal(uVar1,10,uVar2,0);
  }
  if (global_settings != 0) {
    iVar4 = sample_rate_hz_h;
    uVar1 = FUN_0801dc8c(sample_rate_hz_l,sample_rate_hz_h,horiz_trigger_delay_ps_l,horiz_trigger_delay_ps_h);
    iVar4 = (uVar1 * 0x60 >> 0x20) + iVar4 * 0x60;
    uVar1 = __divdi3(uVar1 * 0x60,iVar4,buffer_depth_l,buffer_depth_h);
    if ((0 < iVar4) || ((iVar4 == 0 && (0x30 < uVar1)))) {
      uVar1 = 0x30;
      iVar4 = 0;
    }
    if ((iVar4 < -1) || ((iVar4 == -1 && (uVar1 < 0xffffffd0)))) {
      uVar1 = 0xffffffd0;
    }
    DAT_2000a116 = uVar1;
  }
  if (roll_mode_enable == '\0') {
    ui_element_arrow_T_down.x = (DAT_2000a116 + 0xa0) - (*ui_element_arrow_T_down.image >> 1);
    zw_draw_element();
  }
  return;
}




void zw_scope_grid(void)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  byte bVar4;
  
  if (settings_grid_style_0_none_1_dot_2_line != '\0') {
    if (settings_grid_color_0_dark_1_medium_2_light == '\0') {
      bVar4 = 10;
    }
    else if (settings_grid_color_0_dark_1_medium_2_light == '\x01') {
      bVar4 = 0xb;
    }
    else if (settings_grid_color_0_dark_1_medium_2_light == '\x02') {
      bVar4 = 0xc;
    }
    else {
      bVar4 = 0;
    }
    if (settings_grid_style_0_none_1_dot_2_line == '\x01') {
      pbVar1 = framebuffer_ + 0x35cf;
      do {
        iVar3 = 0x3b;
        pbVar2 = pbVar1;
        do {
          *pbVar2 = bVar4;
          pbVar2 = pbVar2 + 5;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        pbVar1 = pbVar1 + 8000;
      } while (pbVar1 != framebuffer_ + 0x1108f);
      pbVar1 = framebuffer_ + 0x1ce3;
      do {
        iVar3 = 0x27;
        pbVar2 = pbVar1;
        do {
          *pbVar2 = bVar4;
          pbVar2 = pbVar2 + 0x640;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        pbVar1 = pbVar1 + 0x19;
      } while (pbVar1 != framebuffer_ + 0x1df6);
    }
    else {
      pbVar1 = framebuffer_ + 0x35ca;
      do {
        iVar3 = 300;
        pbVar2 = pbVar1;
        do {
          *pbVar2 = bVar4;
          pbVar2 = pbVar2 + 1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        pbVar1 = pbVar1 + 8000;
      } while (pbVar1 != framebuffer_ + 0x1108a);
      pbVar1 = framebuffer_ + 0x16a3;
      do {
        iVar3 = 200;
        pbVar2 = pbVar1;
        do {
          *pbVar2 = bVar4;
          pbVar2 = pbVar2 + 0x140;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        pbVar1 = pbVar1 + 0x19;
      } while (pbVar1 != framebuffer_ + 0x17b6);
    }
    if (DAT_2001de15 == '\0') {
      pbVar1 = framebuffer_ + 0x924f;
      iVar3 = 0x3b;
      do {
        *pbVar1 = bVar4;
        pbVar1 = pbVar1 + 5;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      pbVar1 = framebuffer_ + 0x94cf;
      iVar3 = 0x3b;
      do {
        *pbVar1 = bVar4;
        pbVar1 = pbVar1 + 5;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      zw_draw_line_horizontal(10,0x76,300,bVar4);
    }
    else {
      zw_draw_line_horizontal(10,0x75,300,bVar4);
      zw_draw_line_horizontal(10,0x77,300,bVar4);
      zw_draw_line_horizontal(10,0x76,300,0);
      pbVar1 = framebuffer_ + 0x53cf;
      iVar3 = 0x3b;
      do {
        *pbVar1 = bVar4;
        pbVar1 = pbVar1 + 5;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      pbVar1 = framebuffer_ + 0x564f;
      iVar3 = 0x3b;
      do {
        *pbVar1 = bVar4;
        pbVar1 = pbVar1 + 5;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      pbVar1 = framebuffer_ + 0xd0cf;
      iVar3 = 0x3b;
      do {
        *pbVar1 = bVar4;
        pbVar1 = pbVar1 + 5;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      pbVar1 = framebuffer_ + 0xd34f;
      iVar3 = 0x3b;
      do {
        *pbVar1 = bVar4;
        pbVar1 = pbVar1 + 5;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    pbVar1 = framebuffer_ + 0x1d5f;
    iVar3 = 0x27;
    do {
      *pbVar1 = bVar4;
      pbVar1 = pbVar1 + 0x640;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    pbVar1 = framebuffer_ + 0x1d61;
    iVar3 = 0x27;
    do {
      *pbVar1 = bVar4;
      pbVar1 = pbVar1 + 0x640;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    zw_draw_line_vertical(0xa0,0x12,200,bVar4);
    zw_draw_rectangle(9,0x11,0x12e,0xca,bVar4);
    return;
  }
  zw_draw_line_horizontal(9,0x11,0x12e,0x4208);
  zw_draw_line_horizontal(9,0xdb,0x12e,0x4208);
  return;
}




void FUN_080295bc(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if (DAT_2001a158 == 0) {
    DAT_2001a158 = 1;
  }
  iVar3 = DAT_2001a158;
  iVar1 = __divdi3(*(&DAT_080558fc + zoom_timebase_index_ * 8) * 0x96,
                   (*(&DAT_080558fc + zoom_timebase_index_ * 8) * 0x96 >> 0x20) + *(&DAT_08055900 + zoom_timebase_index_ * 8) * 0x96,DAT_2001a158,0);
  iVar4 = horiz_window_pos_ps__h;
  uVar2 = __divdi3(horiz_window_pos_ps__l,horiz_window_pos_ps__h,1000,0);
  iVar3 = __divdi3(uVar2 * 0x19,(uVar2 * 0x19 >> 0x20) + iVar4 * 0x19,iVar3,0);
  DAT_2000a120 = (0x96 - iVar1) + iVar3;
  DAT_2000a124 = iVar3 + iVar1 + 0x96;
  zw_draw_rectangle_filled(10,0x12,DAT_2000a120 & 0xffff,100);
  zw_draw_rectangle_filled(DAT_2000a124 + 10,0x12,300 - DAT_2000a124,100);
  return;
}




void FUN_08029668(void)

{
  zw_draw_line_vertical(DAT_2000a120 + 9U & 0xffff,0x12,100,10);
  zw_draw_line_vertical(DAT_2000a120 + 10U & 0xffff,0x12,100,0xc);
  zw_draw_line_vertical(DAT_2000a124 + 10U & 0xffff,0x12,100,0xc);
  zw_draw_line_vertical(DAT_2000a124 + 0xbU & 0xffff,0x12,100,10);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void zw_scope_channel_level_(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (DAT_2001de15 == '\0') {
    iVar2 = 100 - ch1_vert_offset_pixels;
    iVar1 = 100 - ch2_vert_offset_pixels;
  }
  else {
    iVar2 = 0x32 - ch1_vert_offset_pixels / 2;
    iVar1 = 0x32 - ch2_vert_offset_pixels / 2;
  }
  iVar2 = (-1 < iVar2) * iVar2;
  if (ch2_enabled == '\x01') {
    uVar4 = (-1 < iVar1) * iVar1 + (0x12 - (*(ui_element_channel_level_1.image + 1) >> 1));
    uVar3 = uVar4 & 0xffff;
    ui_element_channel_level_1.y = uVar4;
    if (uVar3 < 0x12) {
      ui_element_channel_level_1.y = 0x12;
      goto LAB_080296f4;
    }
    if (DAT_2001de15 != '\0') {
      iVar1 = 0x76 - *(ui_element_channel_level_1.image + 1);
      if (iVar1 < uVar3) {
        ui_element_channel_level_1.y = iVar1;
      }
      uVar3 = (iVar2 - (*(ui_element_channel_level_0.image + 1) >> 1)) + 0x12;
      uVar4 = uVar3 & 0xffff;
      ui_element_channel_level_0.y = uVar3;
      if (0x11 < uVar4) goto LAB_0802977e;
      goto LAB_0802970c;
    }
    iVar1 = 0xda - *(ui_element_channel_level_1.image + 1);
    if (iVar1 < uVar3) {
      ui_element_channel_level_1.y = iVar1;
    }
    uVar3 = (iVar2 - (*(ui_element_channel_level_0.image + 1) >> 1)) + 0x12;
    uVar4 = uVar3 & 0xffff;
    ui_element_channel_level_0.y = uVar3;
    if (uVar4 < 0x12) goto LAB_0802970c;
  }
  else {
LAB_080296f4:
    uVar3 = (iVar2 - (*(ui_element_channel_level_0.image + 1) >> 1)) + 0x12;
    uVar4 = uVar3 & 0xffff;
    ui_element_channel_level_0.y = uVar3;
    if (uVar4 < 0x12) {
LAB_0802970c:
      ui_element_channel_level_0.y = 0x12;
      goto joined_r0x08029790;
    }
    if (DAT_2001de15 != '\0') {
LAB_0802977e:
      iVar2 = 0x76 - *(ui_element_channel_level_0.image + 1);
      if (iVar2 < uVar4) {
        ui_element_channel_level_0.y = iVar2;
      }
      goto joined_r0x08029790;
    }
  }
  iVar2 = 0xda - *(ui_element_channel_level_0.image + 1);
  if (iVar2 < uVar4) {
    ui_element_channel_level_0.y = iVar2;
  }
joined_r0x08029790:
  if (ch2_enabled == '\x01') {
    if (active_channel_0_ch1_1_ch2_2_math == '\x01') {
      zw_draw_element(&ui_element_channel_level_0);
      zw_draw_element(&ui_element_channel_level_1);
    }
    else {
      zw_draw_element(&ui_element_channel_level_1);
      zw_draw_element(&ui_element_channel_level_0);
    }
  }
  else {
    zw_draw_element(&ui_element_channel_level_0);
  }
  if (channel_math_mode_0_off_1_add_2_sub != '\0') {
    uVar4 = (0x76 - _DAT_2001de2c) - (*(ui_element_channel_level_2.image + 1) >> 1);
    uVar3 = uVar4 & 0xffff;
    ui_element_channel_level_2.y = uVar4;
    if (uVar3 < 0x12) {
      ui_element_channel_level_2.y = 0x12;
    }
    else {
      iVar2 = 0xda - *(ui_element_channel_level_2.image + 1);
      if (iVar2 < uVar3) {
        ui_element_channel_level_2.y = iVar2;
      }
    }
    zw_draw_element(&ui_element_channel_level_2);
  }
  if (DAT_2001de15 != '\0') {
    ui_element_channel_level_0.y = ui_element_channel_level_0.y + 100;
    ui_element_channel_level_1.y = ui_element_channel_level_1.y + 100;
    if (ch2_enabled == '\x01') {
      if (active_channel_0_ch1_1_ch2_2_math != '\x01') {
        zw_draw_element(&ui_element_channel_level_1);
        zw_draw_element(&ui_element_channel_level_0);
        return;
      }
      zw_draw_element(&ui_element_channel_level_0);
      zw_draw_element(&ui_element_channel_level_1);
      return;
    }
    zw_draw_element(&ui_element_channel_level_0);
  }
  return;
}




void zw_scope_trigger_(void)

{
  int iVar1;
  uint uVar2;
  
  if ((DAT_2001dcd8 & 2) == 0) {
    if (DAT_2000a11c != 0) {
      DAT_2000a11c = DAT_2000a11c + -1;
    }
  }
  else {
    DAT_2001dcd8 = DAT_2001dcd8 & 0xfffffffd;
    DAT_2000a11c = 0x14;
  }
  iVar1 = trigger_level_raw_adc__0_255;
  if (iVar1 - 0x24U < 0xbd) {
    uVar2 = 100 - ((*(ui_element_trigger.image + 1) >> 1) + iVar1 + -0x80) & 0xffff;
  }
  else if (iVar1 < 0x61) {
    uVar2 = 200 - *(ui_element_trigger.image + 1);
  }
  else {
    uVar2 = 0;
  }
  if (DAT_2001de15 == '\0') {
    ui_element_trigger.y = uVar2 + 0x12;
  }
  else {
    ui_element_trigger.y = (uVar2 >> 1) + 0x76;
  }
  if (trigger_source_0_ch1_1_ch2 == '\0') {
    ui_element_trigger.color_index = 0x3f;
    if (DAT_2000a11c != 0) {
      zw_draw_line_horizontal(10,(*(ui_element_trigger.image + 1) >> 1) + ui_element_trigger.y,300,0x3f);
      zw_draw_element(&ui_element_trigger);
      return;
    }
  }
  else {
    ui_element_trigger.color_index = 0x5f;
    if (DAT_2000a11c != 0) {
      zw_draw_line_horizontal(10,(*(ui_element_trigger.image + 1) >> 1) + ui_element_trigger.y,300,0x5f);
      zw_draw_element(&ui_element_trigger);
      return;
    }
  }
  zw_draw_element(&ui_element_trigger);
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: register


void zw_scope_trigger_icons_(void)

{
  longlong lVar1;
  ulonglong uVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  if (roll_mode_enable == '\0') {
    uVar2 = CONCAT44(horiz_trigger_delay_ps_h,horiz_trigger_delay_ps_l) - CONCAT44(roll_mode_view_offset__h,roll_mode_view_offset__l);
    lVar1 = (uVar2 & 0xffffffff) * 0x19;
    iVar5 = (lVar1 >> 0x20) + (uVar2 >> 0x20) * 0x19;
    uVar4 = __divdi3(lVar1,iVar5,timebase_val_ns_l * 1000,(timebase_val_ns_l * 1000 >> 0x20) + timebase_val_ns_h * 1000);
    bVar3 = *ui_element_arrow_down_1.image >> 1;
    uVar7 = bVar3 - 0x96;
    iVar6 = uVar7 >> 0x1f;
    if ((iVar5 < iVar6) || ((iVar6 == iVar5 && (uVar4 < uVar7)))) {
      ui_element_arrow_down_1.x = 10;
      ui_element_arrow_down_1.image = image_scope_icon_T_left;
    }
    else {
      uVar7 = 0x96 - bVar3;
      iVar6 = uVar7 >> 0x1f;
      if ((iVar5 < iVar6) || ((iVar6 == iVar5 && (uVar4 < uVar7)))) {
        ui_element_arrow_down_1.x = (uVar4 - bVar3) + 0xa0;
        ui_element_arrow_down_1.image = image_scope_icon_arrow_down;
      }
      else {
        ui_element_arrow_down_1.x = 0x136 - *ui_element_arrow_down_1.image;
        ui_element_arrow_down_1.image = image_scope_icon_T_right;
      }
    }
    zw_draw_element(&ui_element_arrow_down_1);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void zw_scope_icons_channel_modes(void)

{
  undefined2 uVar1;
  
  zw_draw_element(&ui_element_ch1_icon);
  _DAT_2000a0dc = CONCAT12(ch1_probe_mode_0_x1_1_x10_2_x100,_DAT_2000a0dc);
  DAT_2000a0d0 = ch1_volt_scale_10uV >> 0x1f;
  DAT_2000a0cc = ch1_volt_scale_10uV;
  zw_scope_int_values(ch1_volt_scale_10uV,DAT_2000a0d0,_DAT_2000a0d4,_DAT_2000a0d8);
  if (ch1_coupling_0_dc_1_ac == '\0') {
    ui_element_ch1_coupling.y = 0xe4;
    ui_element_ch1_coupling.color_index = 1;
    ui_element_ch1_coupling.image = image_scope_icon_dc;
    zw_draw_element(&ui_element_ch1_coupling);
  }
  else {
    ui_element_ch1_coupling.y = 0xe0;
    ui_element_ch1_coupling.color_index = 7;
    ui_element_ch1_coupling.image = image_scope_icon_ac;
    zw_draw_element(&ui_element_ch1_coupling);
  }
  if (ch1_probe_mode_0_x1_1_x10_2_x100 == '\0') {
    zw_draw_string_small("X1",100,0xe1,2);
  }
  else if (ch1_probe_mode_0_x1_1_x10_2_x100 == '\x01') {
    zw_draw_string_small("X10",0x60,0xe1,3);
  }
  else {
    zw_draw_string_small("X100",0x60,0xe1,4);
  }
  if (ch2_enabled == '\x01') {
    ui_element_ch2_icon.color_index = 0x5f;
    uVar1 = 1;
    if ((ch2_probe_mode != '\0') && (ch2_probe_mode == '\x01')) {
      uVar1 = 1;
    }
  }
  else {
    ui_element_ch2_icon.color_index = 0xb;
    uVar1 = 0xb;
  }
  zw_draw_element(&ui_element_ch2_icon);
  _DAT_2000a0f4 = CONCAT12(ch2_probe_mode,_DAT_2000a0f4);
  DAT_2000a0e8 = ch2_volt_scale_10uV >> 0x1f;
  _DAT_2000a0f0 = CONCAT22(_DAT_2000a0f2,uVar1);
  DAT_2000a0e4 = ch2_volt_scale_10uV;
  zw_scope_int_values(ch2_volt_scale_10uV,DAT_2000a0e8,_DAT_2000a0ec,_DAT_2000a0f0);
  if (ch2_coupling_dc_ac == '\0') {
    ui_element_ch2_coupling.y = 0xe4;
    ui_element_ch2_coupling.color_index = 1;
    ui_element_ch2_coupling.image = image_scope_icon_dc;
  }
  else {
    ui_element_ch2_coupling.y = 0xe0;
    ui_element_ch2_coupling.color_index = 7;
    ui_element_ch2_coupling.image = image_scope_icon_ac;
  }
  if (ch2_enabled != '\x01') {
    ui_element_ch2_coupling.color_index = 0xb;
  }
  zw_draw_element(&ui_element_ch2_coupling);
  if (ch2_probe_mode == '\0') {
    zw_draw_string_small("X1",0x124,0xe1,2);
  }
  else if (ch2_probe_mode == '\x01') {
    zw_draw_string_small("X10",0x120,0xe1,3);
  }
  else {
    zw_draw_string_small("X100",0x11f,0xe1,4);
  }
  zw_draw_element(&ui_element_measurement_label_bg);
  DAT_2000a0fc = timebase_val_ns_l * 1000;
  DAT_2000a100 = (timebase_val_ns_l * 1000 >> 0x20) + timebase_val_ns_h * 1000;
  zw_scope_int_values(DAT_2000a0fc,DAT_2000a100,_DAT_2000a104,_DAT_2000a108);
  if ((global_settings == 2) || (DAT_2001de0f != '\0')) {
    DAT_2000a114 = DAT_2000a114 + 1;
    ui_element_run_pause.color_index = 7;
    if ((DAT_2000a114 & 8) == 0) {
      ui_element_run_pause.color_index = 0x20;
    }
    ui_element_run_pause.image = image_scope_icon_pause;
  }
  else if (global_settings == 0) {
    ui_element_run_pause.color_index = 2;
    ui_element_run_pause.image = image_scope_icon_pause;
  }
  else {
    ui_element_run_pause.color_index = 3;
    ui_element_run_pause.image = image_scope_icon_run;
  }
  zw_draw_element(&ui_element_run_pause);
  if (trigger_mode_icon_0_auto_1_normal == '\0') {
    ui_element_auto_normal.image = image_scope_icon_auto;
    ui_element_auto_normal.color_index = 6;
  }
  else {
    ui_element_auto_normal.image = image_scope_icon_normal;
    ui_element_auto_normal.color_index = 7;
  }
  zw_draw_element(&ui_element_auto_normal);
  if (trigger_edge_0_rise_1_fall == '\0') {
    ui_element_trigger_edge.image = image_scope_icon_trigger_rising_edge;
    zw_drawGlyph2();
    return;
  }
  ui_element_trigger_edge.image = image_scope_icon_trigger_falling_edge;
  zw_drawGlyph2();
  return;
}




void zw_scope_fullscreen(void)

{
  if (DAT_2001de15 != '\0') {
    FUN_080295bc();
  }
  zw_scope_grid(0xb);
  if (DAT_2001de15 != '\0') {
    FUN_08029668();
  }
  zw_scope_icons_channel_modes();
  if (ch2_enabled != '\0') {
    zw_scope_active_channel_icon_Math_label();
  }
  zw_scope_memory_bar();
  zw_draw_element(&ui_element_battery);
  FUN_08025680();
  return;
}




void FUN_08029d40(void)

{
  if (ch2_vert_offset_pixels + 0x5cU < 0xbc) {
    ui_element_arrow_right.y = (0x76 - ch2_vert_offset_pixels) - (*(ui_element_arrow_right.image + 1) >> 1);
  }
  else if (ch2_vert_offset_pixels < 0x60) {
    ui_element_arrow_right.y = 0xda - *(ui_element_arrow_right.image + 1);
  }
  else {
    ui_element_arrow_right.y = 0x12;
  }
  if (ch1_vert_offset_pixels + 0x5cU < 0xbc) {
    ui_element_arrow_down_0.x = (ch1_vert_offset_pixels + 0xa0) - (*(ui_element_arrow_down_0.image + 1) >> 1);
  }
  else if (ch1_vert_offset_pixels < 0x60) {
    ui_element_arrow_down_0.x = 0x3c;
  }
  else {
    ui_element_arrow_down_0.x = 0x104 - *(ui_element_arrow_down_0.image + 1);
  }
  zw_draw_element(&ui_element_arrow_down_0);
  zw_draw_element(&ui_element_arrow_right);
  return;
}




void zw_scope_XY_grid(void)

{
  byte bVar1;
  byte *pbVar2;
  byte bVar3;
  byte *pbVar4;
  int iVar5;
  
  if (settings_grid_style_0_none_1_dot_2_line == '\0') {
    bVar3 = 0;
    goto LAB_08029e8a;
  }
  if (settings_grid_color_0_dark_1_medium_2_light == '\0') {
    bVar3 = 10;
    bVar1 = 10;
    if (settings_grid_style_0_none_1_dot_2_line != '\x01') goto LAB_08029e02;
LAB_08029ea2:
    pbVar2 = framebuffer_ + 0x3601;
    do {
      iVar5 = 0x27;
      pbVar4 = pbVar2;
      do {
        *pbVar4 = bVar3;
        pbVar4 = pbVar4 + 5;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      pbVar2 = pbVar2 + 8000;
    } while (pbVar2 != framebuffer_ + 0x110c1);
    pbVar2 = framebuffer_ + 0x1d15;
    do {
      iVar5 = 0x27;
      pbVar4 = pbVar2;
      do {
        *pbVar4 = bVar3;
        pbVar4 = pbVar4 + 0x640;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      pbVar2 = pbVar2 + 0x19;
    } while (pbVar2 != framebuffer_ + 0x1dc4);
  }
  else {
    if (settings_grid_color_0_dark_1_medium_2_light == '\x01') {
      bVar3 = 0xb;
    }
    else if (settings_grid_color_0_dark_1_medium_2_light == '\x02') {
      bVar3 = 0xc;
    }
    else {
      bVar3 = 0;
    }
    bVar1 = bVar3;
    if (settings_grid_style_0_none_1_dot_2_line == '\x01') goto LAB_08029ea2;
LAB_08029e02:
    bVar3 = bVar1;
    pbVar2 = framebuffer_ + 0x35fc;
    do {
      iVar5 = 200;
      pbVar4 = pbVar2;
      do {
        *pbVar4 = bVar3;
        pbVar4 = pbVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      pbVar2 = pbVar2 + 8000;
    } while (pbVar2 != framebuffer_ + 0x110bc);
    pbVar2 = framebuffer_ + 0x16d5;
    do {
      iVar5 = 200;
      pbVar4 = pbVar2;
      do {
        *pbVar4 = bVar3;
        pbVar4 = pbVar4 + 0x140;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      pbVar2 = pbVar2 + 0x19;
    } while (pbVar2 != framebuffer_ + 0x1784);
  }
  pbVar2 = framebuffer_ + 0x9281;
  iVar5 = 0x27;
  do {
    *pbVar2 = bVar3;
    pbVar2 = pbVar2 + 5;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  pbVar2 = framebuffer_ + 0x9501;
  iVar5 = 0x27;
  do {
    *pbVar2 = bVar3;
    pbVar2 = pbVar2 + 5;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  pbVar2 = framebuffer_ + 0x1d5f;
  iVar5 = 0x27;
  do {
    *pbVar2 = bVar3;
    pbVar2 = pbVar2 + 0x640;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  pbVar2 = framebuffer_ + 0x1d61;
  iVar5 = 0x27;
  do {
    *pbVar2 = bVar3;
    pbVar2 = pbVar2 + 0x640;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  zw_draw_line_horizontal(0x3c,0x76,200,bVar3);
  zw_draw_line_vertical(0xa0,0x12,200,bVar3);
LAB_08029e8a:
  zw_draw_rectangle(0x3b,0x11,0xca,0xca,bVar3);
  return;
}




void zw_scope_XY_fullscreen_(void)

{
  zw_scope_XY_grid(0xb);
  zw_scope_icons_channel_modes();
  if (ch2_enabled != '\0') {
    zw_scope_active_channel_icon_Math_label();
  }
  zw_scope_memory_bar();
  zw_draw_element(&ui_element_battery);
  FUN_08025680();
  return;
}




void FUN_08029f44(void)

{
  zw_draw_element(&ui_element_battery);
  FUN_08025680();
  return;
}




void zw_scope_menu_CN(void)

{
  DAT_2000a15a = 0x29;
  DAT_2000a160 = image_scope_menu_CN;
  DAT_2000a164 = 1;
  DAT_2000a166 = 0x10;
  DAT_2000a158 = 0xfa;
  DAT_2000a188 = 0x3c;
  DAT_2000a18a = 0x2f;
  DAT_2000a194 = 1;
  DAT_2000a196 = 0x10;
  DAT_2000a190 = image_scope_menu_measurements_icon;
  DAT_2000a176 = 0x20;
  DAT_2000a170 = image_scope_menu_icon_arrow_up;
  DAT_2000a174 = 2;
  DAT_2000a144 = 1;
  DAT_2000a138 = 0x3b;
  DAT_2000a13a = 0x4b;
  DAT_2000a140 = image_scope_menu_measurements_CN;
  DAT_2000a146 = 0;
  DAT_2000a1a6 = 0;
  DAT_2000a198 = 0x41;
  DAT_2000a19a = 0x4e;
  DAT_2000a1a0 = image_scope_menu_trigger_CN;
  DAT_2000a1a4 = 1;
  DAT_2000a136 = 0;
  DAT_2000a12a = 0x4e;
  DAT_2000a128 = 0x41;
  DAT_2000a134 = 1;
  DAT_2000a130 = image_scope_menu_disp_CN;
  DAT_2000a184 = 1;
  DAT_2000a178 = 0x3e;
  DAT_2000a17a = 0x49;
  DAT_2000a180 = image_scope_menu_settings_CN;
  DAT_2000a186 = 0;
  DAT_2000a148 = 0xfa;
  DAT_2000a154 = 2;
  DAT_2000a156 = 0x20;
  DAT_2000a150 = image_scope_menu_icon_arrow_left;
  DAT_2000a1bf = 0;
  DAT_2000a1c0 = 0;
  return;
}




void zw_scope_ch1_measurements_menu(int param_1)

{
  uint uVar1;
  
  if (param_1 == 2) {
    uVar1 = DAT_2000a1c0;
    if (uVar1 == 0xe) {
      if (DAT_2000a1a8 == 0) {
        DAT_2000a1c4 = ch1_enabled_measurements_bitfield;
        DAT_2000a1a8 = 1;
        ch1_enabled_measurements_bitfield = 0x7fff;
        return;
      }
      DAT_2000a1a8 = 0;
      ch1_enabled_measurements_bitfield = DAT_2000a1c4 & 0xffffbfff;
      return;
    }
    ch1_enabled_measurements_bitfield = ch1_enabled_measurements_bitfield ^ 1 << (uVar1 & 0x3f);
joined_r0x0802a0ac:
    if (uVar1 < 0) {
LAB_0802a0b0:
      DAT_2000a1c0 = uVar1 + '\x0f';
      goto joined_r0x0802a0b8;
    }
  }
  else {
    if (param_1 == 4) {
      DAT_2000a1c0 = DAT_2000a1c0 + '\x01';
      uVar1 = DAT_2000a1c0;
      goto joined_r0x0802a0ac;
    }
    if (param_1 == 3) {
      DAT_2000a1c0 = DAT_2000a1c0 + -1;
      uVar1 = DAT_2000a1c0;
      goto joined_r0x0802a0ac;
    }
    uVar1 = DAT_2000a1c0;
    if (param_1 != 0xb) {
      if (param_1 != 0x13) goto joined_r0x0802a0ac;
      if (uVar1 == 0xb) {
        DAT_2000a1c0 = 3;
        return;
      }
      if (0xb < uVar1) {
        DAT_2000a1c0 = DAT_2000a1c0 + '\x03';
        uVar1 = DAT_2000a1c0;
        goto joined_r0x0802a0ac;
      }
      uVar1 = DAT_2000a1c0 + '\x04';
      DAT_2000a1c0 = DAT_2000a1c0 + '\x04';
      if (-1 < uVar1) {
        return;
      }
      goto LAB_0802a0b0;
    }
    if (uVar1 == 3) {
      DAT_2000a1c0 = 0xb;
      return;
    }
    if (uVar1 < 3) {
      DAT_2000a1c0 = DAT_2000a1c0 + -3;
      uVar1 = DAT_2000a1c0;
      goto joined_r0x0802a0ac;
    }
    DAT_2000a1c0 = DAT_2000a1c0 + -4;
    uVar1 = DAT_2000a1c0;
  }
  if (0xe < uVar1) {
    DAT_2000a1c0 = uVar1 + -0xf;
  }
joined_r0x0802a0b8:
  if (param_1 == 0x8e) {
    zw_debug_dump();
    return;
  }
  return;
}




void zw_scope_calib_(int param_1)

{
  uint uVar1;
  
  if (param_1 == 2) {
    uVar1 = DAT_2000a1c0;
    if (uVar1 == 0xe) {
      if (DAT_2000a1ac == 0) {
        DAT_2000a1ac = 1;
        DAT_2000a1c8 = ch2_enabled_measurements_bitfield;
        ch2_enabled_measurements_bitfield = 0x7fff;
        return;
      }
      DAT_2000a1ac = 0;
      ch2_enabled_measurements_bitfield = DAT_2000a1c8 & 0xffffbfff;
      return;
    }
    ch2_enabled_measurements_bitfield = ch2_enabled_measurements_bitfield ^ 1 << (uVar1 & 0x3f);
joined_r0x0802a1ac:
    if (uVar1 < 0) {
LAB_0802a1b0:
      DAT_2000a1c0 = uVar1 + '\x0f';
      goto LAB_0802a17a;
    }
  }
  else {
    if (param_1 == 4) {
      DAT_2000a1c0 = DAT_2000a1c0 + '\x01';
      uVar1 = DAT_2000a1c0;
      goto joined_r0x0802a1ac;
    }
    if (param_1 == 3) {
      DAT_2000a1c0 = DAT_2000a1c0 + -1;
      uVar1 = DAT_2000a1c0;
      goto joined_r0x0802a1ac;
    }
    uVar1 = DAT_2000a1c0;
    if (param_1 != 0xb) {
      if (param_1 != 0x13) goto joined_r0x0802a1ac;
      if (uVar1 == 0xb) {
        DAT_2000a1c0 = 3;
        return;
      }
      if (0xb < uVar1) {
        DAT_2000a1c0 = DAT_2000a1c0 + '\x03';
        uVar1 = DAT_2000a1c0;
        goto joined_r0x0802a1ac;
      }
      uVar1 = DAT_2000a1c0 + '\x04';
      if (-1 < uVar1) {
        DAT_2000a1c0 = DAT_2000a1c0 + '\x04';
        return;
      }
      goto LAB_0802a1b0;
    }
    if (uVar1 == 3) {
      DAT_2000a1c0 = 0xb;
      return;
    }
    if (uVar1 < 3) {
      DAT_2000a1c0 = DAT_2000a1c0 + -3;
      uVar1 = DAT_2000a1c0;
      goto joined_r0x0802a1ac;
    }
    DAT_2000a1c0 = DAT_2000a1c0 + -4;
    uVar1 = DAT_2000a1c0;
  }
  if (0xe < uVar1) {
    DAT_2000a1c0 = uVar1 + -0xf;
  }
LAB_0802a17a:
  if (param_1 == 0x85) {
    DAT_2001de01 = 0;
    DAT_2001de0a = 1;
    zw_draw_popup_message("Calib:AC gain",0xd,900000,0,1);
  }
  else if (param_1 == 0x8d) {
    DAT_2001de01 = 0;
    DAT_2001de0a = 2;
    zw_draw_popup_message("Calib:DC offset",0xf,900000,0,1);
  }
  else if (param_1 == 0x95) {
    DAT_2001de01 = 0;
    DAT_2001de0a = 3;
    zw_draw_popup_message("Calib:DC offset2",0x10,900000,0,1);
    return;
  }
  return;
}




void FUN_0802a2cc(int param_1)

{
  if (param_1 == 2) {
    switch(DAT_2000a1c0) {
    case '\0':
      trigger_mode_icon_0_auto_1_normal = 0;
      break;
    case '\x01':
      trigger_mode_icon_0_auto_1_normal = 1;
      break;
    case '\x02':
      trigger_level_mode_0_auto_1_manual = 0;
      break;
    case '\x03':
      trigger_level_mode_0_auto_1_manual = 1;
      break;
    case '\x04':
      trigger_edge_0_rise_1_fall = 0;
      break;
    case '\x05':
      trigger_edge_0_rise_1_fall = 1;
      break;
    case '\x06':
      trigger_source_0_ch1_1_ch2 = 0;
      break;
    case '\a':
      trigger_source_0_ch1_1_ch2 = 1;
      break;
    default:
      goto joined_r0x0802a318;
    }
  }
  else {
    if (param_1 == 4) {
      DAT_2000a1c0 = DAT_2000a1c0 + '\x01';
    }
    else if (param_1 == 3) {
      DAT_2000a1c0 = DAT_2000a1c0 + -1;
    }
    else if (param_1 == 0xb) {
      DAT_2000a1c0 = DAT_2000a1c0 + -2;
    }
    else if (param_1 == 0x13) {
      DAT_2000a1c0 = DAT_2000a1c0 + '\x02';
    }
joined_r0x0802a318:
    if (DAT_2000a1c0 < '\0') {
      DAT_2000a1c0 = DAT_2000a1c0 + '\b';
      return;
    }
    if ('\a' < DAT_2000a1c0) {
      DAT_2000a1c0 = DAT_2000a1c0 + -8;
    }
  }
  return;
}




void FUN_0802a394(int param_1)

{
  bool bVar1;
  bool bVar2;
  byte bVar3;
  
  if (param_1 == 0x10) {
    bVar1 = DAT_2000a1bd != 0;
    DAT_2000a1c0 = 0;
    bVar2 = DAT_2000a1bd == 0;
    DAT_2000a1bd = ~bVar1;
    if (bVar2) {
      DAT_2000a1c0 = 0;
      return;
    }
    goto LAB_0802a42e;
  }
  if (DAT_2000a1bd != 0) {
    if (param_1 == 4) {
      DAT_2000a1c0 = DAT_2000a1c0 + 1;
    }
    else if (param_1 == 3) {
      DAT_2000a1c0 = DAT_2000a1c0 - 1;
    }
    else if (param_1 == 0xb) {
      DAT_2000a1c0 = DAT_2000a1c0 - 2;
    }
    else if (param_1 == 0x13) {
      DAT_2000a1c0 = DAT_2000a1c0 + 2;
    }
    if (DAT_2000a1c0 < '\0') {
      DAT_2000a1c0 = DAT_2000a1c0 + 8;
    }
    else if ('\a' < DAT_2000a1c0) {
      DAT_2000a1c0 = DAT_2000a1c0 - 8;
    }
    if (param_1 != 2) {
      return;
    }
    switch(DAT_2000a1c0) {
    case 0:
      frequency_meter_enable = 4;
      counter_enable = 0;
      return;
    case 1:
      frequency_meter_enable = 0;
      return;
    case 2:
      counter_enable = 4;
      frequency_meter_enable = 0;
      return;
    case 3:
      counter_enable = 0;
      return;
    case 4:
      ch1_20mhz_limit = 1;
      break;
    case 5:
      ch1_20mhz_limit = 0;
      break;
    case 6:
      ch2_20mhz_limit = 1;
      break;
    case 7:
      ch2_20mhz_limit = 0;
      break;
    default:
      if (3 < DAT_2000a1c0 - 4) {
        return;
      }
    }
    zw_bw_limit_(ch1_20mhz_limit,ch2_20mhz_limit);
    return;
  }
  if (param_1 != 2) {
    if (param_1 == 4) {
      bVar3 = DAT_2000a1c0 + 1;
      goto LAB_0802a476;
    }
    if (param_1 == 3) {
      bVar3 = DAT_2000a1c0 - 1;
      goto LAB_0802a476;
    }
    if (param_1 == 0xb) {
      bVar3 = DAT_2000a1c0 - 2;
      if (2 < DAT_2000a1c0 - 2) goto LAB_0802a476;
      DAT_2000a1c0 = DAT_2000a1c0 - 3;
      if (-1 < DAT_2000a1c0) goto LAB_0802a42e;
      goto LAB_0802a412;
    }
    bVar3 = DAT_2000a1c0;
    if (param_1 != 0x13) goto LAB_0802a476;
    if (1 < DAT_2000a1c0) {
      bVar3 = DAT_2000a1c0 + 2;
      goto LAB_0802a476;
    }
    DAT_2000a1c0 = DAT_2000a1c0 + 3;
    goto LAB_0802a47a;
  }
  switch(DAT_2000a1c0) {
  case 0:
    persistance_mode_0_off_1_infinite_2_1s = '\0';
    goto LAB_0802a57a;
  case 1:
    persistance_mode_0_off_1_infinite_2_1s = '\x02';
    goto LAB_0802a5c2;
  case 2:
    persistance_mode_0_off_1_infinite_2_1s = '\x01';
    goto LAB_0802a57a;
  case 3:
    roll_menu_enable = 1;
    break;
  case 4:
    roll_menu_enable = 0;
    break;
  case 5:
    hi_rate_enable = '\x01';
    break;
  case 6:
    hi_rate_enable = '\0';
    break;
  case 7:
    screen_brightness_0_80 = screen_brightness_0_80 - 5;
    break;
  case 8:
    screen_brightness_0_80 = screen_brightness_0_80 + 5;
  }
  if (persistance_mode_0_off_1_infinite_2_1s == '\x02') {
LAB_0802a5c2:
    zw_timer_us(&DAT_20030ba4,32000);
  }
LAB_0802a57a:
  if (screen_brightness_0_80 < 6) {
    screen_brightness_0_80 = 6;
  }
  else if (0x50 < screen_brightness_0_80) {
    screen_brightness_0_80 = 0x50;
  }
  zw_lcd_set_pwm(screen_brightness_0_80);
  bVar3 = DAT_2000a1c0;
LAB_0802a476:
  DAT_2000a1c0 = bVar3;
  if (DAT_2000a1c0 < '\0') {
LAB_0802a412:
    DAT_2000a1c0 = DAT_2000a1c0 + 9;
  }
  else {
LAB_0802a47a:
    if ('\b' < DAT_2000a1c0) {
      DAT_2000a1c0 = DAT_2000a1c0 - 9;
    }
  }
LAB_0802a42e:
  if ((hi_rate_enable == '\0') && (param_1 == 0x92)) {
    ets_enable_ = ~(ets_enable_ != '\0');
    return;
  }
  if (param_1 != 0x8a) {
    if ((param_1 == 0x82) &&
       (settings_grid_style_0_none_1_dot_2_line = settings_grid_style_0_none_1_dot_2_line + '\x01', settings_grid_style_0_none_1_dot_2_line == '\x03')) {
      settings_grid_style_0_none_1_dot_2_line = '\0';
    }
    return;
  }
  DAT_2001de09 = ~(DAT_2001de09 != '\0');
  return;
}




void zw_scope_state_handler_(int param_1)

{
  int iVar1;
  uint uVar2;
  uint unaff_r5;
  
  if (param_1 != 2) {
    if (param_1 == 4) {
      DAT_2000a1c0 = DAT_2000a1c0 + '\x01';
      goto joined_r0x0802a6c4;
    }
    if (param_1 == 3) {
      DAT_2000a1c0 = DAT_2000a1c0 + -1;
      goto joined_r0x0802a6c4;
    }
    if (param_1 != 0xb) {
      if (param_1 == 0x13) {
        if (DAT_2000a1c0 < '\x02') {
LAB_0802a786:
          DAT_2000a1c0 = '\x02';
          goto LAB_0802a660;
        }
        if (DAT_2000a1c0 < '\x04') {
LAB_0802a658:
          DAT_2000a1c0 = '\x04';
          goto LAB_0802a660;
        }
        if ('\a' < DAT_2000a1c0) {
          if (DAT_2000a1c0 != '\b') goto LAB_0802a6c8;
          goto LAB_0802a778;
        }
        goto LAB_0802a754;
      }
      goto joined_r0x0802a6c4;
    }
    if (DAT_2000a1c0 < '\x02') {
LAB_0802a754:
      DAT_2000a1c0 = '\b';
      goto LAB_0802a660;
    }
    if (DAT_2000a1c0 < '\x04') {
LAB_0802a778:
      DAT_2000a1c0 = '\0';
      goto LAB_0802a660;
    }
    if (DAT_2000a1c0 < '\b') goto LAB_0802a786;
    if (DAT_2000a1c0 == '\b') goto LAB_0802a658;
LAB_0802a6c8:
    if ('\b' < DAT_2000a1c0) {
      DAT_2000a1c0 = DAT_2000a1c0 + -9;
      return;
    }
    if (param_1 == 0x95) {
      zw_draw_popup_message("v3.0.7_III",10,0x5dc,0,1);
      return;
    }
    if (param_1 == 0x91) {
      DAT_2000a1be = DAT_2000a1be + '\x01';
      if (DAT_2000a1be == '\x04') {
        DAT_2000a1be = '\0';
      }
      else if (DAT_2000a1be != '\0') {
        if (DAT_2000a1be == '\x01') {
          ch1_color_index = 5;
          DAT_2001ddea = 0x10;
          return;
        }
        if (DAT_2000a1be != '\x02') {
          if (DAT_2000a1be != '\x03') {
            return;
          }
          ch1_color_index = 0;
          DAT_2001ddea = 8;
          return;
        }
        ch1_color_index = 5;
        DAT_2001ddea = 4;
        return;
      }
      ch1_color_index = 5;
      DAT_2001ddea = 0;
      return;
    }
    if (param_1 == 0x82) {
      ch1_enabled_measurements_bitfield = 7;
      ch2_enabled_measurements_bitfield = 7;
      siggen_duty_cycle_0_1_ = 500;
      siggen_frequency_0_1hz = 10000;
      timebase_index_2_5ns_30_10s = 16;
      siggen_amplitude_mV = 2500;
      screen_brightness_0_80 = 50;
      horiz_trigger_delay_ps_l = 0;
      horiz_trigger_delay_ps_h = 0;
      ch1_v_div_index = 9;
      ch1_vert_offset_pixels = 0;
      ch1_trigger_level_10uV_target_l = 0;
      ch1_trigger_level_10uV_target_h = 0;
      ch1_coupling_0_dc_1_ac = 0;
      ch2_v_div_index = 9;
      ch2_vert_offset_pixels = 0;
      ch2_trigger_level_10uV_target_l = 0;
      ch2_trigger_level_10uV_target_h = 0;
      ch2_enabled = 0;
      ch1_probe_mode_0_x1_1_x10_2_x100 = 1;
      ch2_coupling_dc_ac = 0;
      ch2_probe_mode = 1;
      persistance_mode_0_off_1_infinite_2_1s = 0;
      roll_menu_enable = 1;
      trigger_mode_icon_0_auto_1_normal = 0;
      trigger_source_0_ch1_1_ch2 = 0;
      trigger_edge_0_rise_1_fall = 0;
      trigger_level_mode_0_auto_1_manual = 0;
      active_channel_0_ch1_1_ch2_2_math = 0;
      DAT_2001de00 = 0;
      siggen_waveform_pattern = 1;
      siggen_enable = 1;
      key_beep_enable = 1;
      system_status_ = 1;
      DAT_2001ddc9 = 0;
      auto_off_enable = 0;
      cursor_x1_position = 0xffc9;
      cursor_y2_position = 0xffc9;
      ch1_color_index = 0x3f;
      DAT_2001ddea = 0xf;
      cursor_x2_position = 0x37;
      cursor_y1_position = 0x37;
      settings_grid_style_0_none_1_dot_2_line = 2;
      fft_mode_0_off_1_log_2_lin_3_music = 0;
      cursors_x_enable = 0;
      cursors_y_enable = 0;
      settings_grid_color_0_dark_1_medium_2_light = 1;
      settings_ch2_color_0_green_1_purple_2_cyan = 1;
      hi_rate_enable = 1;
      DAT_2001de09 = 0;
      ets_enable_ = 1;
      DAT_2001de0a = 0;
      settings_dmm_window_0_window_1_fullscreen = 1;
      frequency_meter_enable = 0;
      counter_enable = 0;
      zw_draw_popup_message("Reset",5,1000,0,1);
      DAT_2001de01 = 0;
      global_settings = 1;
      FUN_0801eff0(0xff);
      settings_changed_flag_ = 1;
      roll_direction_0_left_1_right = 0;
      return;
    }
    if ((DAT_2000a1c0 == '\x05') && (param_1 == 0x8e)) {
      zw_draw_popup_message("Reset All",9,1000,0,1);
      FUN_0801c508(0x1000);
      FUN_080254a0(0);
      zw_lcd_set_pwm(0);
      zw_power_on(10);
      return;
    }
    if (param_1 != 0x11) goto LAB_0802a660;
    if (DAT_2000a1bc < 5) {
      zw_timer_us(&DAT_2000a1b0,800000);
      DAT_2000a1bc = DAT_2000a1bc + 1;
      return;
    }
    goto LAB_0802a678;
  }
  if (DAT_2000a1bc == 3) {
joined_r0x0802a6c4:
    if (DAT_2000a1c0 < '\0') {
      DAT_2000a1c0 = DAT_2000a1c0 + '\t';
      return;
    }
    goto LAB_0802a6c8;
  }
  switch(DAT_2000a1c0) {
  case '\0':
    auto_off_enable = ~(auto_off_enable != 0);
    break;
  case '\x01':
    key_beep_enable = ~(key_beep_enable != 0);
    break;
  case '\x02':
    language_0_CN_1_EN = 0;
    break;
  case '\x03':
    language_0_CN_1_EN = 1;
    break;
  case '\x04':
    fft_mode_0_off_1_log_2_lin_3_music = 0;
    break;
  case '\x05':
    fft_mode_0_off_1_log_2_lin_3_music = 1;
    if (2 < DAT_2000a1bc - 3) goto LAB_0802a678;
    goto LAB_0802a870;
  case '\x06':
    fft_mode_0_off_1_log_2_lin_3_music = 2;
    break;
  case '\a':
    fft_mode_0_off_1_log_2_lin_3_music = 3;
    break;
  case '\b':
    system_status_ = 5;
    DAT_2001de01 = 0;
    break;
  default:
    goto joined_r0x0802a6c4;
  }
LAB_0802a660:
  if (DAT_2000a1bc - 3 < 3) {
    if (param_1 == 2) {
LAB_0802a870:
      iVar1 = FUN_080270a8(&DAT_2000a1b0);
      if (iVar1 != 0) {
        if (DAT_2000a1bc == 0) {
          return;
        }
        goto LAB_0802a882;
      }
      zw_draw_rectangle_filled(0,0,0x140,0xf0,0);
      zw_draw_string_large("Loading fpga firmware1...",0x14,0x6e,0x17,1,0);
      zw_draw_string_large("It takes about 20 seconds.",0x14,0x82,0x1a,1,0);
      zw_draw_flush_offscreen();
      HAL_Delay(0x32);
      zw_power_control_(0);
      if (DAT_2000a1bc == 3) {
        uVar2 = zw_firmware_uart_upgrade(460800,0);
        unaff_r5 = uVar2 & 0xff;
      }
      else if (DAT_2000a1bc == 4) {
        uVar2 = zw_firmware_uart_upgrade(115200,0);
        unaff_r5 = uVar2 & 0xff;
      }
      else if (DAT_2000a1bc == 5) {
        uVar2 = zw_firmware_uart_upgrade(230400,0);
        unaff_r5 = uVar2 & 0xff;
      }
    }
    else if (param_1 == 0x14) {
      iVar1 = FUN_080270a8(&DAT_2000a1b0);
      if (iVar1 != 0) goto LAB_0802a678;
      zw_draw_rectangle_filled(0,0,0x140,0xf0,0);
      zw_draw_string_large("Loading fpga firmware2...",0x14,0x6e,0x19,1,0);
      zw_draw_string_large("It takes about 20 seconds.",0x14,0x82,0x1a,1,0);
      zw_draw_flush_offscreen();
      HAL_Delay(0x32);
      zw_power_control_(0);
      if (DAT_2000a1bc == 3) {
        uVar2 = zw_firmware_uart_upgrade(460800,1);
        unaff_r5 = uVar2 & 0xff;
      }
      else if (DAT_2000a1bc == 4) {
        uVar2 = zw_firmware_uart_upgrade(115200,1);
        unaff_r5 = uVar2 & 0xff;
      }
      else if (DAT_2000a1bc == 5) {
        uVar2 = zw_firmware_uart_upgrade(230400,1);
        unaff_r5 = uVar2 & 0xff;
      }
    }
    else {
      if (param_1 != 0xf) goto LAB_0802a674;
      iVar1 = FUN_080270a8(&DAT_2000a1b0);
      if (iVar1 != 0) goto LAB_0802a678;
      zw_draw_rectangle_filled(0,0,0x140,0xf0,0);
      zw_draw_string_large("Loading fpga firmware3...",0x14,0x6e,0x19,1,0);
      zw_draw_string_large("It takes about 20 seconds.",0x14,0x82,0x1a,1,0);
      zw_draw_flush_offscreen();
      HAL_Delay(0x32);
      zw_power_control_(0);
      if (DAT_2000a1bc == 3) {
        uVar2 = zw_firmware_uart_upgrade(460800,2);
        unaff_r5 = uVar2 & 0xff;
      }
      else if (DAT_2000a1bc == 4) {
        uVar2 = zw_firmware_uart_upgrade(115200,2);
        unaff_r5 = uVar2 & 0xff;
      }
      else if (DAT_2000a1bc == 5) {
        uVar2 = zw_firmware_uart_upgrade(230400,2);
        unaff_r5 = uVar2 & 0xff;
      }
    }
    if (unaff_r5 == 0) {
      FUN_08026294();
      zw_draw_rectangle_filled(0,0,0x140,0xf0,0);
      zw_draw_string_large("Upgrade failed!",0x14,0x6e,0xf,2,0);
      zw_draw_string_large("Please restart and try again.",0x14,0x82,0x1d,2,0);
      zw_draw_flush_offscreen();
      HAL_Delay(5000);
      FUN_080254a0(0);
    }
    else {
      FUN_08026294();
      zw_draw_rectangle_filled(0,0,0x140,0xf0,0);
      zw_draw_string_large("Upgrade successful!",0x14,0x6e,0x13,3,0);
      zw_draw_string_large("Please restart.",0x14,0x82,0xf,3,0);
      zw_draw_flush_offscreen();
      HAL_Delay(3000);
      FUN_080254a0(0);
    }
  }
  else {
LAB_0802a674:
    if (param_1 == 0) {
      return;
    }
LAB_0802a678:
    if (DAT_2000a1bc == 0) {
      if (param_1 != 0x8f) {
        return;
      }
      if (siggen_amplitude_mV == 0x9c4) {
        siggen_amplitude_mV = 0x9ce;
        zw_draw_popup_message("Vol=2.5V",8,1000,0,1);
        return;
      }
      if (siggen_amplitude_mV == 0x9ce) {
        siggen_amplitude_mV = 3000;
        zw_draw_popup_message("Vol 3.0V",8,1000,0,1);
        return;
      }
      if (siggen_amplitude_mV != 3000) {
        siggen_amplitude_mV = 0x9c4;
        zw_draw_popup_message("Vol 2.5V",8,1000,0,1);
        return;
      }
      siggen_amplitude_mV = 0xbc2;
      zw_draw_popup_message("Vol=3.0V",8,1000,0,1);
      return;
    }
LAB_0802a882:
    DAT_2000a1bc = 6;
  }
  return;
}




int zw_scope_init_settings_(int param_1)

{
  byte bVar1;
  undefined1 uVar2;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar2 = DAT_2000a1bf;
  if ((param_1 == 6) && (system_status_ == '\x01')) {
    bVar1 = DAT_2001de01 & 1;
    if ((DAT_2001de01 & 0x20) == 0) {
      if ((DAT_2001de01 & 1) != 0) {
        DAT_2001de01 = DAT_2001de01 & 0x20;
        return 0xff;
      }
      DAT_2001de01 = 1;
      DAT_2000a1c0 = bVar1;
      DAT_2000a1bd = 1;
      DAT_2000a1bc = bVar1;
      return 0xff;
    }
    if ((DAT_2001de01 & 1) == 0) {
      return 6;
    }
  }
  else {
    if ((DAT_2001de01 & 1) == 0) {
      return param_1;
    }
    if (param_1 == 10) {
      DAT_2000a1bf = 0;
      uVar2 = 0;
    }
    else if (param_1 == 0x12) {
      DAT_2000a1bf = 1;
      uVar2 = 1;
    }
    else if (param_1 == 8) {
      DAT_2000a1bf = 2;
      uVar2 = 2;
    }
    else {
      if (param_1 == 0x10) {
        DAT_2000a1bf = 3;
        DAT_2000a1c0 = 0;
        DAT_2000a1bc = 0;
switchD_0802ad36_caseD_3:
        FUN_0802a394();
        return 0;
      }
      if (param_1 != 0x18) goto LAB_0802ad2a;
      DAT_2000a1bf = 4;
      uVar2 = 4;
    }
    DAT_2000a1c0 = 0;
    DAT_2000a1bc = 0;
    DAT_2000a1bd = 1;
  }
LAB_0802ad2a:
  switch(uVar2) {
  case 0:
    zw_scope_ch1_measurements_menu();
    return 0;
  case 1:
    zw_scope_calib_();
    return 0;
  case 2:
    FUN_0802a2cc();
    return 0;
  case 3:
    goto switchD_0802ad36_caseD_3;
  case 4:
    zw_scope_state_handler_();
    return 0;
  default:
    return 0;
  }
}




void zw_scope_menu_Meas(int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  short asStackY_60 [26];
  short local_28 [8];
  
  local_28[0] = 0x3c;
  local_28[1] = 0x65;
  local_28[2] = 0x8e;
  local_28[3] = 0xb7;
  local_28[4] = 0x4b;
  local_28[5] = 0x60;
  local_28[6] = 0x75;
  local_28[7] = 0x8a;
  zw_draw_rectangle_filled(0x36,0x2d,0xac,0x14,0x10);
  zw_draw_rectangle(0x36,0x40,0xac,0x65,0x10);
  zw_draw_rectangle_filled(0x37,0x41,0xaa,99,0);
  DAT_2000a18a = 0x2f;
  DAT_2000a190 = image_scope_menu_measurements_icon;
  zw_draw_element();
  if (param_1 == 0) {
    uVar3 = 0x3f;
    uVar1 = ch1_enabled_measurements_bitfield;
  }
  else {
    uVar3 = 0x5f;
    uVar1 = ch2_enabled_measurements_bitfield;
  }
  if ((uVar1 & 1) != 0) {
    zw_draw_rectangle_filled(0x3c,0x4b,0x26,0xe,uVar3);
  }
  if ((uVar1 & 2) != 0) {
    zw_draw_rectangle_filled(0x65,0x4b,0x26,0xe,uVar3);
  }
  if ((uVar1 & 4) != 0) {
    zw_draw_rectangle_filled(0x8e,0x4b,0x26,0xe,uVar3);
  }
  if ((uVar1 & 8) != 0) {
    zw_draw_rectangle_filled(0xb7,0x4b,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x10) != 0) {
    zw_draw_rectangle_filled(0x3c,0x60,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x20) != 0) {
    zw_draw_rectangle_filled(0x65,0x60,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x40) != 0) {
    zw_draw_rectangle_filled(0x8e,0x60,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x80) != 0) {
    zw_draw_rectangle_filled(0xb7,0x60,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x100) != 0) {
    zw_draw_rectangle_filled(0x3c,0x75,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x200) != 0) {
    zw_draw_rectangle_filled(0x65,0x75,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x400) != 0) {
    zw_draw_rectangle_filled(0x8e,0x75,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x800) != 0) {
    zw_draw_rectangle_filled(0xb7,0x75,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x1000) != 0) {
    zw_draw_rectangle_filled(0x3c,0x8a,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x2000) != 0) {
    zw_draw_rectangle_filled(0x65,0x8a,0x26,0xe,uVar3);
  }
  if ((uVar1 & 0x4000) != 0) {
    zw_draw_rectangle_filled(0x8e,0x8a,0x26,0xe,uVar3);
  }
  DAT_2000a140 = image_scope_menu_measurements_CN;
  if (language_0_CN_1_EN != '\0') {
    DAT_2000a140 = image_scope_menu_measurements_EN;
  }
  FUN_080274f4();
  uVar2 = DAT_2000a1c0;
  uVar1 = uVar2 & 0x80000003;
  if (uVar1 < 0) {
    uVar1 = (uVar1 - 1 | 0xfffffffc) + 1;
  }
  if ((uVar2 & 0x80000000) != 0) {
    uVar2 = uVar2 + 3;
  }
  DAT_2000a168 = local_28[uVar1] + 0xe;
  DAT_2000a16a = local_28[(uVar2 >> 2) + 4] + 0xf;
  zw_draw_element(&DAT_2000a168);
  return;
}




void zw_scope_menu_Trig(void)

{
  uint uVar1;
  short local_1c [6];
  
  local_1c[0] = 0x86;
  local_1c[1] = 0xb5;
  local_1c[2] = 0x4d;
  local_1c[3] = 0x61;
  local_1c[4] = 0x75;
  local_1c[5] = 0x89;
  zw_draw_rectangle_filled(0x36,0x2d,0xac,0x14,0x10);
  zw_draw_rectangle(0x36,0x40,0xac,0x65,0x10);
  zw_draw_rectangle_filled(0x37,0x41,0xaa,99,0);
  DAT_2000a18a = 0x30;
  DAT_2000a190 = image_scope_menu_trigger_icon;
  zw_draw_element();
  if (trigger_mode_icon_0_auto_1_normal == '\0') {
    zw_draw_rectangle_filled(0x86,0x4d,0x1c,0xe,5);
  }
  else if (language_0_CN_1_EN == '\0') {
    zw_draw_rectangle_filled(0xb5,0x4d,0x1c,0xe,5);
  }
  else {
    zw_draw_rectangle_filled(0xaf,0x4d,0x28,0xe,5);
  }
  if (trigger_level_mode_0_auto_1_manual == '\0') {
    zw_draw_rectangle_filled(0x86,0x61,0x1c,0xe,5);
  }
  else if (language_0_CN_1_EN == '\0') {
    zw_draw_rectangle_filled(0xb5,0x61,0x1c,0xe,5);
  }
  else {
    zw_draw_rectangle_filled(0xaf,0x61,0x29,0xe,5);
  }
  if (trigger_edge_0_rise_1_fall == '\0') {
    zw_draw_rectangle_filled(0x86,0x75,0x1c,0xe,5);
  }
  else {
    zw_draw_rectangle_filled(0xb5,0x75,0x1c,0xe,5);
  }
  if (trigger_source_0_ch1_1_ch2 == '\0') {
    zw_draw_rectangle_filled(0x86,0x89,0x1c,0xe,5);
  }
  else {
    zw_draw_rectangle_filled(0xb5,0x89,0x1c,0xe,5);
  }
  DAT_2000a1a0 = image_scope_menu_trigger_CN;
  if (language_0_CN_1_EN != '\0') {
    DAT_2000a1a0 = image_scope_menu_trigger_EN;
  }
  FUN_080274f4();
  uVar1 = DAT_2000a1c0 & 0x80000001;
  if (uVar1 < 0) {
    uVar1 = (uVar1 - 1 | 0xfffffffe) + 1;
  }
  DAT_2000a168 = local_1c[uVar1] + 9;
  DAT_2000a16a = local_1c[DAT_2000a1c0 / 2 + 2] + 0xf;
  zw_draw_element(&DAT_2000a168);
  return;
}




void zw_scope_menu_Disp(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  short asStack_1c [4];
  
  asStack_1c[0] = 0x66;
  asStack_1c[1] = 0x8d;
  asStack_1c[2] = 0xb4;
  zw_draw_rectangle_filled(0x36,0x2d,0xac,0x14,0x10);
  zw_draw_rectangle(0x36,0x40,0xac,0x65,0x10);
  zw_draw_rectangle_filled(0x37,0x41,0xaa,99,0);
  DAT_2000a18a = 0x31;
  DAT_2000a190 = image_scope_menu_disp_icon;
  zw_draw_element();
  if (DAT_2000a1bd != '\0') {
    zw_draw_string_small("F_Meter:",0x3e,0x4b,8,1,0);
    zw_draw_string_small("Counter:",0x3e,0x5f,8,1,0);
    if (frequency_meter_enable == '\0') {
      zw_draw_string_small(" ON ",0x86,0x4b,4,1,0);
      zw_draw_string_small(" OFF ",0xae,0x4b,5,0,5);
    }
    else {
      zw_draw_string_small(" ON ",0x86,0x4b,4,0,5);
      zw_draw_string_small(" OFF ",0xae,0x4b,5,1,0);
    }
    if (counter_enable == '\0') {
      zw_draw_string_small(" ON ",0x86,0x5f,4,1,0);
      zw_draw_string_small(" OFF ",0xae,0x5f,5,0,5);
    }
    else {
      zw_draw_string_small(" ON ",0x86,0x5f,4,0,5);
      zw_draw_string_small(" OFF ",0xae,0x5f,5,1,0);
    }
    zw_draw_string_small("CH1_20M:",0x3e,0x73,8,1,0);
    zw_draw_string_small("CH2_20M:",0x3e,0x87,8,1,0);
    if (ch1_20mhz_limit == '\0') {
      zw_draw_string_small(" ON ",0x86,0x73,4,1,0);
      zw_draw_string_small(" OFF ",0xae,0x73,5,0,5);
    }
    else {
      zw_draw_string_small(" ON ",0x86,0x73,4,0,5);
      zw_draw_string_small(" OFF ",0xae,0x73,5,1,0);
    }
    if (ch2_20mhz_limit == '\0') {
      zw_draw_string_small(" ON ",0x86,0x87,4,1,0);
      zw_draw_string_small(" OFF ",0xae,0x87,5,0,5);
    }
    else {
      zw_draw_string_small(" ON ",0x86,0x87,4,0,5);
      zw_draw_string_small(" OFF ",0xae,0x87,5,1,0);
    }
    uVar1 = DAT_2000a1c0;
    uVar2 = uVar1 & 0x80000001;
    if (uVar2 < 0) {
      uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
    }
    DAT_2000a168 = uVar2 * 0x2c + 0x92;
    DAT_2000a16a = (((uVar1 >> 0x1f) + uVar1) / 2) * 0x14 + 0x59;
    zw_draw_element(&DAT_2000a168);
    return;
  }
  zw_draw_rectangle_filled(0x72,0x8c,screen_brightness_0_80 - 5,8,1);
  if (persistance_mode_0_off_1_infinite_2_1s == '\0') {
    zw_draw_rectangle_filled(0x66,0x4f,0x1b,0xb,5);
  }
  else if (persistance_mode_0_off_1_infinite_2_1s == '\x02') {
    zw_draw_rectangle_filled(0x8d,0x4f,0x1b,0xb,5);
  }
  else {
    zw_draw_rectangle_filled(0xb4,0x4f,0x1b,0xb,5);
  }
  if (roll_menu_enable == '\x01') {
    zw_draw_rectangle_filled(0x66,0x62,0x1b,0xb,5);
  }
  else {
    zw_draw_rectangle_filled(0x8d,0x62,0x1b,0xb,5);
  }
  if (hi_rate_enable == '\x01') {
    zw_draw_rectangle_filled(0x66,0x75,0x1b,0xb,5);
  }
  else {
    zw_draw_rectangle_filled(0x8d,0x75,0x1b,0xb,5);
  }
  DAT_2000a128 = 0x41;
  DAT_2000a12a = 0x4e;
  if (language_0_CN_1_EN == '\x01') {
    DAT_2000a128 = 0x3a;
    DAT_2000a12a = 0x50;
    DAT_2000a130 = image_scope_menu_disp_EN;
  }
  else {
    DAT_2000a130 = image_scope_menu_disp_CN;
    if (language_0_CN_1_EN != '\0') {
      DAT_2000a130 = image_scope_menu_disp_EN;
    }
  }
  FUN_080274f4(&DAT_2000a128);
  iVar3 = DAT_2000a1c0;
  if (iVar3 < 3) {
    DAT_2000a168 = asStack_1c[DAT_2000a1c0 % '\x03'] + 8;
    DAT_2000a16a = 0x5b;
  }
  else if (iVar3 < 7) {
    DAT_2000a168 = asStack_1c[iVar3 - 3U & 1] + 8;
    if (iVar3 < 5) {
      DAT_2000a16a = 0x6e;
    }
    else {
      DAT_2000a16a = 0x81;
    }
  }
  else {
    if (iVar3 == 7) {
      DAT_2000a168 = 0x61;
    }
    else {
      DAT_2000a168 = 199;
    }
    DAT_2000a16a = 0x96;
  }
  zw_draw_element(&DAT_2000a168);
  return;
}




void zw_scope_menu_Set(void)

{
  int iVar1;
  short asStackY_11c [130];
  undefined2 uStack_14;
  undefined2 uStack_12;
  undefined2 uStack_10;
  undefined2 uStack_e;
  
  uStack_14 = 0x59;
  uStack_12 = 0x7b;
  uStack_10 = 0x9d;
  uStack_e = 0xbf;
  zw_draw_rectangle_filled(0x36,0x2d,0xac,0x14,0x10);
  zw_draw_rectangle(0x36,0x40,0xac,0x65,0x10);
  zw_draw_rectangle_filled(0x37,0x41,0xaa,99,0);
  DAT_2000a18a = 0x2f;
  DAT_2000a190 = image_scope_menu_settings_icon;
  zw_draw_element();
  if (auto_off_enable == '\x01') {
    zw_draw_rectangle_filled(0x41,0x50,4,4,5);
  }
  if (key_beep_enable == '\x01') {
    zw_draw_rectangle_filled(0xa6,0x50,4,4,5);
  }
  if (voice_control_enable == '\x01') {
    zw_draw_rectangle_filled(0xc5,0x50,4,4,5);
  }
  if (language_0_CN_1_EN == '\0') {
    zw_draw_rectangle_filled(0x62,0x60,0x1b,0xe,5);
    if (fft_mode_0_off_1_log_2_lin_3_music != '\0') goto LAB_0802b6ae;
LAB_0802b738:
    zw_draw_rectangle_filled(0x59,0x76,0x1b,0xe,5);
  }
  else {
    zw_draw_rectangle_filled(0x83,0x60,0x2c,0xe,5);
    if (fft_mode_0_off_1_log_2_lin_3_music == '\0') goto LAB_0802b738;
LAB_0802b6ae:
    if (fft_mode_0_off_1_log_2_lin_3_music == '\x01') {
      zw_draw_rectangle_filled(0x7b,0x76,0x1b,0xe,5);
    }
    else if (fft_mode_0_off_1_log_2_lin_3_music == '\x02') {
      zw_draw_rectangle_filled(0x9d,0x76,0x1b,0xe,5);
    }
    else {
      zw_draw_rectangle_filled(0xbf,0x76,0x1b,0xe,5);
    }
  }
  DAT_2000a178 = 0x3e;
  DAT_2000a17a = 0x4b;
  if (language_0_CN_1_EN == '\x01') {
    DAT_2000a178 = 0x3b;
    DAT_2000a180 = image_scope_menu_settings_EN;
  }
  else {
    DAT_2000a180 = image_scope_menu_settings_CN;
    if (language_0_CN_1_EN != '\0') {
      DAT_2000a180 = image_scope_menu_settings_EN;
    }
  }
  FUN_080274f4(&DAT_2000a178);
  zw_draw_rectangle_filled(DAT_2000a178 + 0x81,DAT_2000a17a + -1,0x1e,0x12,0);
  iVar1 = DAT_2000a1c0;
  if (iVar1 == 0) {
    DAT_2000a168 = 0x5d;
  }
  else {
    if (iVar1 != 1) {
      if (iVar1 == 2) {
        DAT_2000a168 = 0x6a;
      }
      else {
        if (iVar1 != 3) {
          if (iVar1 < 8) {
            DAT_2000a168 = *(&stack0xffffffec + (iVar1 + -4) * 2) + 9;
            if (iVar1 < 2) goto LAB_0802b712;
          }
          else {
            DAT_2000a168 = 0x5d;
          }
          if (7 < iVar1) {
            DAT_2000a16a = 0x9b;
            zw_draw_element(&DAT_2000a168);
            return;
          }
          DAT_2000a16a = 0x84;
          zw_draw_element(&DAT_2000a168);
          return;
        }
        DAT_2000a168 = 0x94;
      }
      DAT_2000a16a = 0x6e;
      zw_draw_element(&DAT_2000a168);
      return;
    }
    DAT_2000a168 = 0xb0;
  }
LAB_0802b712:
  DAT_2000a16a = 0x58;
  zw_draw_element(&DAT_2000a168);
  return;
}




void zw_scope_menu(void)

{
  if ((DAT_2001de01 & 1) != 0) {
    DAT_2000a160 = image_scope_menu_CN;
    if (language_0_CN_1_EN != '\0') {
      DAT_2000a160 = image_scope_menu_EN;
    }
    zw_draw_rectangle(DAT_2000a158 + -1,DAT_2000a15a + -1,0x45,200,0xd);
    zw_draw_element(&DAT_2000a158);
    DAT_2000a14a = DAT_2000a15a + 0x10 + DAT_2000a1bf * 0x28;
    zw_draw_element();
    switch(DAT_2000a1bf) {
    case '\0':
      zw_scope_menu_Meas(0);
      return;
    case '\x01':
      zw_scope_menu_Meas(1);
      return;
    case '\x02':
      zw_scope_menu_Trig();
      return;
    case '\x03':
      zw_scope_menu_Disp();
      return;
    case '\x04':
      zw_scope_menu_Set();
    }
  }
  return;
}




void FUN_0802b8e4(void)

{
  if (DAT_2000a1a8 != 0) {
    ch1_enabled_measurements_bitfield = DAT_2000a1c4;
  }
  return;
}




void zw_scope_mode_setup_(int param_1)

{
  undefined4 uVar1;
  
  if ((DAT_2001de01 & 1) != 0) {
    return;
  }
  if (system_status_ != '\x01') {
    return;
  }
  if ((DAT_2001de0e != '\0') && (DAT_2001de0c != '\0')) {
    return;
  }
  if (param_1 == 0x56) {
    if (DAT_2001ddc9 != '\0') {
      DAT_2001ddc9 = 0;
      DAT_2001de01 = 0;
      return;
    }
    DAT_2001de01 = 0;
    DAT_2001de00 = 0;
    cursors_x_enable = 0;
    cursors_y_enable = 0;
    fft_mode_0_off_1_log_2_lin_3_music = 0;
    DAT_2001ddc9 = 1;
    if (ch2_enabled != '\0') {
      DAT_2001ddc9 = 1;
      fft_mode_0_off_1_log_2_lin_3_music = 0;
      cursors_x_enable = 0;
      cursors_y_enable = 0;
      DAT_2001de00 = 0;
      DAT_2001de01 = 0;
      return;
    }
    FUN_0801eff0(0x47);
    return;
  }
  if (param_1 == 8) {
    if (ch1_coupling_0_dc_1_ac == 0) {
      uVar1 = 5;
      ch1_coupling_0_dc_1_ac = 0xff;
LAB_0802b9a8:
      zw_draw_popup_message(" AC ",4,1000,0,uVar1);
      return;
    }
    uVar1 = 5;
    ch1_coupling_0_dc_1_ac = ~(ch1_coupling_0_dc_1_ac != 0);
LAB_0802b94e:
    zw_draw_popup_message(" DC ",4,1000,0,uVar1);
  }
  else {
    if (param_1 == 0x10) {
      if (ch1_probe_mode_0_x1_1_x10_2_x100 == '\0') {
        ch1_probe_mode_0_x1_1_x10_2_x100 = 1;
        zw_draw_popup_message(" 10X ",5,1000,0,5);
        return;
      }
      if (ch1_probe_mode_0_x1_1_x10_2_x100 == '\x01') {
        ch1_probe_mode_0_x1_1_x10_2_x100 = '\x02';
        uVar1 = 5;
LAB_0802bb0a:
        zw_draw_popup_message(" 100X ",6,1000,0,uVar1);
        return;
      }
      ch1_probe_mode_0_x1_1_x10_2_x100 = '\0';
      uVar1 = 5;
    }
    else {
      if (param_1 == 0x48) {
        if (ch2_coupling_dc_ac == 0) {
          uVar1 = 3;
          ch2_coupling_dc_ac = 0xff;
          goto LAB_0802b9a8;
        }
        uVar1 = 3;
        ch2_coupling_dc_ac = ~(ch2_coupling_dc_ac != 0);
        goto LAB_0802b94e;
      }
      if (param_1 != 0x50) {
        if (param_1 == 0x46) {
          trigger_mode_icon_0_auto_1_normal = trigger_mode_icon_0_auto_1_normal != '\x01';
          if (trigger_mode_icon_0_auto_1_normal) {
            zw_draw_popup_message("normal",6,0x5dc,0,1);
            return;
          }
        }
        else {
          if (param_1 == 0x4f) {
            trigger_edge_0_rise_1_fall = trigger_edge_0_rise_1_fall != '\x01';
            if (!trigger_edge_0_rise_1_fall) {
              zw_draw_popup_message("Rise",4,0x5dc,0,1);
              return;
            }
            zw_draw_popup_message("Fall",4,0x5dc,0,1);
            return;
          }
          if (param_1 != 0x45) {
            if (param_1 == 0x57) {
              trigger_source_0_ch1_1_ch2 = trigger_source_0_ch1_1_ch2 != '\x01';
              if (!trigger_source_0_ch1_1_ch2) {
                zw_draw_popup_message("CH1",3,0x5dc,0,1);
                return;
              }
              zw_draw_popup_message("CH2",3,0x5dc,0,1);
              return;
            }
            if (param_1 == 0x51) {
              if (DAT_2001ddc9 != '\0') {
                return;
              }
              cursors_x_enable = ~(cursors_x_enable != '\0');
              return;
            }
            if (param_1 != 0x49) {
              return;
            }
            if (DAT_2001ddc9 != '\0') {
              return;
            }
            cursors_y_enable = ~(cursors_y_enable != '\0');
            return;
          }
          trigger_level_mode_0_auto_1_manual = trigger_level_mode_0_auto_1_manual != '\x01';
          if (trigger_level_mode_0_auto_1_manual) {
            zw_draw_popup_message("Manual",6,0x5dc,0,1);
            return;
          }
        }
        zw_draw_popup_message("Auto",4,0x5dc,0,1);
        return;
      }
      if (ch2_probe_mode == '\0') {
        ch2_probe_mode = 1;
        zw_draw_popup_message(" 10X ",5,1000,0,3);
        return;
      }
      if (ch2_probe_mode == '\x01') {
        ch2_probe_mode = '\x02';
        uVar1 = 3;
        goto LAB_0802bb0a;
      }
      ch2_probe_mode = '\0';
      uVar1 = 3;
    }
    zw_draw_popup_message(" 1X ",4,1000,0,uVar1);
  }
  return;
}




void zw_draw_popup_message(undefined4 *string,uint strlen,int time_ms,undefined2 foregroundColor,undefined2 backgroundColor)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  
  DAT_2000a260 = 1;
  zw_timer_us(&DAT_2000a254,time_ms * 1000);
  DAT_2000a1e4 = strlen;
  DAT_2000a24e = foregroundColor;
  DAT_2000a250 = backgroundColor;
  if ((strlen & 1) == 0) {
    DAT_2000a24a = (strlen >> 1) * -10 + 0xa0;
    DAT_2000a24c = 0x6e;
    if (strlen == 0) {
      return;
    }
  }
  else {
    DAT_2000a24a = (strlen >> 1) * -10 + 0x9b;
  }
  DAT_2000a24c = 0x6e;
  puVar3 = &DAT_2000a1e6;
  puVar2 = (strlen - 1 & 0xffff) + 1 + string;
  do {
    uVar1 = *string;
    string = string + 1;
    *puVar3 = uVar1;
    puVar3 = puVar3 + 1;
  } while (string != puVar2);
  return;
}




void FUN_0802bc38(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,int param_7)

{
  DAT_2000a260 = 1;
  zw_timer_us(&DAT_2000a254,param_7 * 1000);
  DAT_2000a1e4 = 0;
  DAT_2000a1cc = param_1;
  DAT_2000a1d0 = param_2;
  DAT_2000a1d4 = param_3;
  DAT_2000a1d8 = param_4;
  DAT_2000a1dc = param_5;
  DAT_2000a1e0 = param_6;
  return;
}




void FUN_0802bc90(void)

{
  int iVar1;
  
  if (DAT_2000a260 != '\0') {
    iVar1 = FUN_080270a8(&DAT_2000a254);
    if (iVar1 != 0) {
      DAT_2000a260 = 0;
      return;
    }
    if (DAT_2000a1e4 == 0) {
      zw_scope_int_values(DAT_2000a1cc,DAT_2000a1d0,DAT_2000a1d4,DAT_2000a1d8,DAT_2000a1dc,DAT_2000a1e0);
      return;
    }
    zw_draw_string_large(&DAT_2000a1e6,DAT_2000a24a,DAT_2000a24c,DAT_2000a1e4,DAT_2000a24e,DAT_2000a250);
  }
  return;
}




int FUN_0802bd04(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  if (param_1 == 0x94) {
    DAT_20030bb0 = ~(DAT_20030bb0 != 0);
  }
  else {
    if (param_1 != 0x86) {
      if ((DAT_2001de01 & 0x20) == 0) {
        return param_1;
      }
      if (param_1 == 6) {
        DAT_2001de01 = 0;
      }
      else if (param_1 == 4) {
        DAT_2000a261 = DAT_2000a261 + '\x01';
      }
      else if (param_1 == 3) {
        DAT_2000a261 = DAT_2000a261 + -1;
      }
      else if (param_1 == 0xb) {
        DAT_2000a261 = DAT_2000a261 + -2;
      }
      else if (param_1 == 0x13) {
        DAT_2000a261 = DAT_2000a261 + '\x02';
      }
      goto LAB_0802bd66;
    }
    if ((system_status_ == '\x01') && ((DAT_2001de01 & 1) == 0)) {
      if ((DAT_2001de01 & 0x20) == 0) {
        DAT_2000a261 = DAT_2001de01 & 0x20;
        DAT_2001de01 = 0x20;
        return 0xff;
      }
      DAT_2001de01 = DAT_2001de01 & 1;
      return 0xff;
    }
  }
  if ((DAT_2001de01 & 0x20) == 0) {
    return param_1;
  }
LAB_0802bd66:
  if (DAT_2000a261 < '\0') {
    DAT_2000a261 = DAT_2000a261 + '\x06';
  }
  else if ('\x05' < DAT_2000a261) {
    if (param_1 == 2) {
      DAT_2000a261 = 0;
      channel_math_mode_0_off_1_add_2_sub = 1;
      return 0;
    }
    DAT_2000a261 = 0;
    return 0;
  }
  if (param_1 == 2) {
    switch(DAT_2000a261) {
    case 0:
      channel_math_mode_0_off_1_add_2_sub = 1;
      return 0;
    case 1:
      if (channel_math_mode_0_off_1_add_2_sub == '\x01') {
        channel_math_mode_0_off_1_add_2_sub = 0;
        return 0;
      }
      break;
    case 2:
      channel_math_mode_0_off_1_add_2_sub = 2;
      return 0;
    case 3:
      if (channel_math_mode_0_off_1_add_2_sub == '\x02') {
        channel_math_mode_0_off_1_add_2_sub = 0;
        return 0;
      }
      break;
    case 4:
      roll_direction_0_left_1_right = 0;
      return 0;
    case 5:
      roll_direction_0_left_1_right = 1;
    }
  }
  return 0;
}




void zw_scope_menu_math_roll(void)

{
  undefined2 uStack_20;
  undefined2 uStack_1e;
  byte *pbStack_18;
  undefined2 uStack_14;
  undefined2 uStack_12;
  
  if ((DAT_2001de01 & 0x20) == 0) {
    return;
  }
  zw_draw_rectangle_filled(0x39,0x3c,200,10,4);
  zw_draw_rectangle(0x39,0x3c,200,0x86,4);
  zw_draw_rectangle(0x3a,0x3d,0xc6,0x84,4);
  zw_draw_rectangle_filled(0x3b,0x46,0xc4,0x7a,0);
  if (channel_math_mode_0_off_1_add_2_sub == 1) {
    zw_draw_rectangle_filled(0x83,0x4f,0x18,0xd,0xf);
  }
  else {
    zw_draw_rectangle_filled(0xaf,0x4f,0x18,0xd,0xf);
  }
  if (channel_math_mode_0_off_1_add_2_sub == 2) {
    zw_draw_rectangle_filled(0x83,100,0x18,0xd,0xf);
  }
  else {
    zw_draw_rectangle_filled(0xaf,100,0x18,0xd,0xf);
  }
  if (roll_direction_0_left_1_right == 0) {
    zw_draw_rectangle_filled(0x83,0x79,0x18,0xe,0xf);
  }
  else {
    zw_draw_rectangle_filled(0xaf,0x79,0x18,0xe,0xf);
  }
  uStack_1e = 0x52;
  pbStack_18 = image_scope_math_menu_sub;
  uStack_20 = 0x44;
  uStack_14 = 1;
  uStack_12 = 0x20;
  zw_draw_element(&uStack_20);
  uStack_1e = 0x67;
  pbStack_18 = image_scope_math_menu_add;
  uStack_20 = 0x44;
  uStack_14 = 1;
  uStack_12 = 0x20;
  zw_draw_element(&uStack_20);
  uStack_20 = 0x4f;
  uStack_1e = 0x7b;
  pbStack_18 = image_scope_roll_menu;
  uStack_14 = 1;
  uStack_12 = 0x20;
  zw_draw_element(&uStack_20);
  pbStack_18 = image_scope_menu_icon_arrow_up;
  uStack_14 = 2;
  uStack_12 = 0x20;
  if (((DAT_2000a261 & 0xfd) == 0) || (DAT_2000a261 == 4)) {
    uStack_20 = 0x8b;
  }
  else if (((DAT_2000a261 & 0xfd) == 1) || (DAT_2000a261 == 5)) {
    uStack_20 = 0xb8;
  }
  if (DAT_2000a261 < 2) {
    uStack_1e = 0x5c;
  }
  else if (DAT_2000a261 - 2 < 2) {
    uStack_1e = 0x71;
  }
  else if (DAT_2000a261 - 4 < 2) {
    uStack_1e = 0x86;
  }
  zw_draw_element(&uStack_20);
  return;
}




void zw_gpio_init__FUN_0802bfdc(GPIO_TypeDef *param_1,uint32_t param_2,uint32_t param_3,int param_4)

{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  uRam00000e00 = uRam00000e00 | 0x800;
  if (param_3 == 1) {
    GPIO_InitStruct.Mode = 2;
  }
  else {
    GPIO_InitStruct.Mode = param_3;
    if (param_3 == 0) {
      GPIO_InitStruct.Mode = 1;
    }
  }
  if (param_4 == 0) {
    GPIO_InitStruct.Pull = 0x13;
  }
  else {
    GPIO_InitStruct.Pull = 0x12;
    if (param_4 == 1) {
      GPIO_InitStruct.Pull = 0x14;
    }
  }
  GPIO_InitStruct.Pin = param_2;
  HAL_GPIO_Init(param_1,&GPIO_InitStruct);
  return;
}




void zw_set_bits(uint32_t *word,uint32_t mask)

{
  *word = mask | *word;
  return;
}




void zw_clear_bits(uint32_t *word,uint32_t mask)

{
  *word = *word & ~mask;
  return;
}




void FUN_0802c058(void)

{
  DAT_20030bf0 = 0x1d;
  hpwm0__DAT_20030be0 = &peripheral_pwm_clkdiv01;
  DAT_20030bf4 = 1;
  DAT_20030be8 = 1;
  DAT_20030be4 = 1;
  DAT_20030bec = 99;
  DAT_20030bf8 = 0;
  DAT_20030c08 = 0;
  HAL_PWM_Init(&hpwm0__DAT_20030be0);
  DAT_20030c10 = 0x29a;
  hpwm1__DAT_20030c0c = &peripheral_pwm_clkdiv01;
  DAT_20030c20 = 1;
  DAT_20030c14 = 1;
  DAT_20030c28 = 1;
  DAT_20030c18 = 99;
  DAT_20030c1c = 3;
  DAT_20030c24 = 0;
  DAT_20030c34 = 1;
  HAL_PWM_Init(&hpwm1__DAT_20030c0c);
  DAT_20030bb8 = 400;
  DAT_20030bb4 = &peripheral_pwm_clkdiv01;
  DAT_20030bc8 = 1;
  DAT_20030bbc = 1;
  DAT_20030bc0 = 99;
  DAT_20030bc4 = 0;
  DAT_20030bcc = 0;
  DAT_20030bdc = 3;
  HAL_PWM_Init(&DAT_20030bb4);
  HAL_PWM_Start(&hpwm0__DAT_20030be0);
  HAL_PWM_Start(&hpwm1__DAT_20030c0c);
  HAL_PWM_Stop(&hpwm1__DAT_20030c0c);
  return;
}




void FUN_0802c0f8(uint32_t param_1)

{
  if (DAT_20030c08 == param_1) {
    HAL_PWM_Duty_Set(&hpwm0__DAT_20030be0,DAT_20030c08);
    return;
  }
  if (param_1 != DAT_20030c34) {
    HAL_PWM_Duty_Set(&DAT_20030bb4,DAT_20030bdc);
    return;
  }
  HAL_PWM_Duty_Set(&hpwm1__DAT_20030c0c,param_1);
  return;
}




void HAL_PWM_Start_wrapper__FUN_0802c13c(int param_1)

{
  PWM_HandleTypeDef *hpwm;
  
  hpwm = &hpwm0__DAT_20030be0;
  if ((DAT_20030c08 != param_1) && (hpwm = &hpwm1__DAT_20030c0c, param_1 != DAT_20030c34)) {
    HAL_PWM_Start(&DAT_20030bb4);
    return;
  }
  HAL_PWM_Start(hpwm);
  return;
}




void HAL_PWM_Stop_wrapper__FUN_0802c170(int param_1)

{
  PWM_HandleTypeDef *hpwm;
  
  hpwm = &hpwm0__DAT_20030be0;
  if ((DAT_20030c08 != param_1) && (hpwm = &hpwm1__DAT_20030c0c, param_1 != DAT_20030c34)) {
    HAL_PWM_Stop(&DAT_20030bb4);
    return;
  }
  HAL_PWM_Stop(hpwm);
  return;
}




void zw_lcd_set_pwm(int param_1)

{
  if (param_1 != 0) {
    FUN_0802c0f8(DAT_20030bdc,param_1);
    HAL_PWM_Start_wrapper__FUN_0802c13c(DAT_20030bdc);
    return;
  }
  HAL_PWM_Stop_wrapper__FUN_0802c170(DAT_20030bdc);
  return;
}




void FUN_0802c1cc(int param_1)

{
  if (param_1 != 0) {
    FUN_0802c0f8(DAT_20030c08,param_1);
    HAL_PWM_Start_wrapper__FUN_0802c13c(DAT_20030c08);
    return;
  }
  HAL_PWM_Stop_wrapper__FUN_0802c170(DAT_20030c08);
  return;
}




void zw_HAL_PWM_Start_wrapper__FUN_0802c1f4(void)

{
  HAL_PWM_Start_wrapper__FUN_0802c13c(DAT_20030c34);
  return;
}




void zw_HAL_PWM_Stop_wrapper__FUN_0802c204(void)

{
  HAL_PWM_Stop_wrapper__FUN_0802c170(DAT_20030c34);
  return;
}




void FUN_0802c214(uint param_1,uint *data)

{
  uint *puVar1;
  uint uVar2;
  uint8_t uVar3;
  uint uVar4;
  uint8_t local_18;
  uint8_t uStack_17;
  uint8_t uStack_16;
  uint8_t uStack_15;
  
  uVar2 = (param_1 & 0xff) - 1;
  uVar4 = uVar2 & 0xff;
  uVar3 = uVar2;
  if (param_1 < 0x101) {
    uStack_15 = uVar3;
    HAL_UART_Transmit(&DAT_20030c38,&uStack_15,1,10);
    if (data == 0x0) {
      uVar3 = -param_1;
      goto LAB_0802c262;
    }
    HAL_UART_Transmit(&DAT_20030c38,data,param_1,(param_1 & 0x7fff) * 10);
    if (param_1 == 0) goto LAB_0802c262;
  }
  else {
    uVar2 = param_1 - 1 & 0x7fff;
    uStack_17 = uVar2 >> 8;
    HAL_UART_Transmit(&DAT_20030c38,&uStack_17,1,10);
    uStack_16 = uVar3;
    HAL_UART_Transmit(&DAT_20030c38,&uStack_16,1,10);
    uVar4 = uVar4 ^ uVar2 >> 8;
    uVar3 = uVar4;
    if (data == 0x0) goto LAB_0802c262;
    HAL_UART_Transmit(&DAT_20030c38,data,param_1,(param_1 & 0x7fff) * 10);
  }
  puVar1 = data + param_1;
  do {
    uVar2 = *data;
    data = data + 1;
    uVar4 = uVar4 ^ uVar2;
    uVar3 = uVar4;
  } while (data != puVar1);
LAB_0802c262:
  local_18 = uVar3;
  HAL_UART_Transmit(&DAT_20030c38,&local_18,1,10);
  return;
}




void FUN_0802c2c4(void)

{
  undefined4 uStack_8;
  
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,0x8000);
  zw_gpio_init__FUN_0802bfdc(&peripheral_gpioA_data,0x800,1,2,uStack_8);
  return;
}




void FUN_0802c2fc(undefined4 baudrate)

{
  DAT_20030c38 = &peripheral_uart3_line_ctrl;
  DAT_20030c40 = 3;
  DAT_20030c48 = 8;
  DAT_20030c4c = 0xc0;
  DAT_20030c44 = 0;
  DAT_20030c50 = 0;
  DAT_20030c3c = baudrate;
  HAL_UART_Init(&DAT_20030c38);
  HAL_UART_Receive_IT(&DAT_20030c38,&DAT_2001af78,0);
  FifoInit(&DAT_2001bb30,0x1000);
  return;
}




void FUN_0802c344(int param_1)

{
  if (DAT_2000a268 == '\0') {
    if (*(param_1 + 0x2e) != 1) goto LAB_0802c358;
    DAT_2000a268 = '\x01';
  }
  if (*(param_1 + 0x2e) != 0) {
    FifoWrite(*(param_1 + 0x28),*(param_1 + 0x2e));
  }
LAB_0802c358:
  if (1 < *(param_1 + 0x2e)) {
    (hwdg.Instance)->CLR = 1;
  }
  return;
}




undefined4 FUN_0802c388(void)

{
  int iVar1;
  int iVar2;
  uint8_t local_28 [32];
  
  iVar2 = 500;
  while( true ) {
    FUN_08027040(2000);
    iVar1 = FifoDataLen();
    if ((0 < iVar1) && (FifoRead(local_28,1), local_28[0] == 'y')) break;
    iVar2 = iVar2 + -1;
    FUN_08027040(20000);
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 1;
}




undefined4 FUN_0802c3d0(void)

{
  int iVar1;
  uint8_t uStack_31;
  uint8_t auStack_30 [32];
  
  iVar1 = 0x14;
  do {
    uStack_31 = '\x7f';
    HAL_UART_Transmit(&DAT_20030c38,&uStack_31,1,10);
    FUN_08027040(100000);
    FifoRead(auStack_30,1);
    if (auStack_30[0] == 'y') {
      return 1;
    }
    iVar1 = iVar1 + -1;
    HAL_Delay(100);
  } while (iVar1 != 0);
  return 1;
}




void FUN_0802c420(byte param_1)

{
  byte local_8;
  byte bStack_7;
  
  bStack_7 = ~param_1;
  local_8 = param_1;
  HAL_UART_Transmit(&DAT_20030c38,&local_8,2,0x14);
  FUN_0802c388(DAT_2000a278);
  return;
}




void FUN_0802c450(undefined4 param_1,undefined4 param_2)

{
  byte local_10;
  byte bStack_f;
  byte bStack_e;
  byte bStack_d;
  byte bStack_c;
  
  bStack_f = param_1 >> 0x10 & 0x7f;
  bStack_e = param_1 >> 8 & 0x7f;
  local_10 = param_1 >> 0x18;
  bStack_d = param_1;
  bStack_c = bStack_d ^ local_10 ^ bStack_f ^ bStack_e;
  HAL_UART_Transmit(&DAT_20030c38,&local_10,5,0x32);
  FUN_0802c388(param_2);
  return;
}




undefined4 FUN_0802c498(int param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  uint uVar4;
  uint uVar5;
  ushort *puVar6;
  undefined1 *puVar7;
  uint *puVar8;
  
  puVar7 = &stack0xfffffff8;
  if (param_1 != 0) {
    iVar1 = (param_1 + 2) * 2;
    puVar3 = &stack0xfffffff8;
    for (uVar4 = iVar1 + 4U & 0xfffffffc; 0x1000 < uVar4; uVar4 = uVar4 - 0x1000) {
      puVar7 = puVar3 + -0x1000;
      *(puVar3 + -0x1000) = puVar3 + -0x1000;
      puVar3 = puVar3 + -0x1000;
    }
    iVar2 = -uVar4;
    puVar6 = puVar7 + iVar2;
    uVar4 = param_1 - 1U & 0xffff;
    *(puVar7 + iVar2) = param_1 - 1U >> 8 | uVar4 << 8;
    puVar8 = param_2 + iVar1 + -4;
    do {
      puVar6 = puVar6 + 1;
      uVar5 = *param_2;
      param_2 = param_2 + 2;
      *puVar6 = uVar5 << 8 | uVar5 >> 8;
      uVar4 = uVar4 ^ uVar5;
    } while (puVar8 != param_2);
    *(puVar7 + (param_1 + 1) * 2 + iVar2) = uVar4 ^ uVar4 >> 8;
    uVar4 = (param_1 + 1) * 2 + 1;
    HAL_UART_Transmit(&DAT_20030c38,puVar7 + iVar2,uVar4,(uVar4 & 0xffff) * 10);
  }
  return 1;
}




void FUN_0802c544(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0802c420(0x21);
  if (iVar1 == 0) {
    return;
  }
  FUN_0802c450(param_1,DAT_2000a278);
  return;
}




undefined4 FUN_0802c564(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0802c420(0x44);
  if ((iVar1 != 0) && (iVar1 = FUN_0802c498(param_1,param_2), iVar1 != 0)) {
    uVar2 = FUN_0802c388(param_1 * 0x14);
    return uVar2;
  }
  return 0;
}




undefined4 FUN_0802c590(undefined4 param_1,uint param_2,undefined4 data)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 0x31;
  if (0x100 < param_2) {
    uVar1 = 0x33;
  }
  iVar2 = FUN_0802c420(uVar1);
  if (((iVar2 != 0) && (iVar2 = FUN_0802c450(param_1,DAT_2000a278), iVar2 != 0)) && ((0x1f < DAT_2000a27c || (iVar2 = FUN_0802c420(0), iVar2 != 0)))) {
    if (param_2 != 0) {
      FUN_0802c214(param_2,data);
    }
    uVar1 = FUN_0802c388(param_2 * 10);
    return uVar1;
  }
  return 0;
}




int FUN_0802c5f8(undefined4 param_1,uint param_2,uint8_t *param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 0x11;
  if (0x100 < param_2) {
    uVar1 = 0x13;
  }
  iVar2 = FUN_0802c420(uVar1);
  if (((iVar2 != 0) && (iVar2 = FUN_0802c450(param_1,DAT_2000a278), iVar2 != 0)) && ((0x1f < DAT_2000a27c || (iVar2 = FUN_0802c420(0), iVar2 != 0)))) {
    if (param_2 != 0) {
      FUN_0802c214(param_2,0);
    }
    iVar2 = FUN_0802c388(10);
    if (iVar2 != 0) {
      FUN_08027040(param_2 * 0x96);
      FifoRead(param_3,param_2);
      return iVar2;
    }
  }
  return 0;
}




void FUN_0802c674(void)

{
  int iVar1;
  
  iVar1 = FUN_0802c420(0xa2);
  if (iVar1 == 0) {
    return;
  }
  FUN_0802c388(10);
  return;
}




void FUN_0802c68c(void)

{
  int iVar1;
  
  iVar1 = FUN_0802c420(0xa3);
  if (iVar1 == 0) {
    return;
  }
  FUN_0802c388(0x14);
  return;
}




undefined4 zw_fpga_flash_erase_(uint addr,int length)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  ushort local_210 [256];
  
  if (length != 0) {
    uVar3 = addr & 0xfffff000;
    uVar4 = addr + 0xfff + length & 0xfffff000;
    if (uVar3 < uVar4) {
      if (addr < 0x80) {
        uVar2 = FUN_0802c68c();
        return uVar2;
      }
      iVar1 = 0;
      do {
        while( true ) {
          if (((uVar3 & 0x7fff) == 0) && (uVar3 <= uVar4)) {
            local_210[iVar1] = uVar3 >> 0xc | 0x8000;
          }
          else {
            local_210[iVar1] = uVar3 >> 0xc;
            uVar3 = uVar3 + 0x1000;
          }
          if (iVar1 + 1U < 0xff) break;
          iVar1 = FUN_0802c564(iVar1 + 1,local_210);
          if (iVar1 == 0) {
            return 0;
          }
          if (uVar4 <= uVar3) {
            return 1;
          }
          iVar1 = 0;
        }
        iVar1 = iVar1 + 1;
      } while (uVar3 < uVar4);
      iVar1 = FUN_0802c564(iVar1,local_210);
      if (iVar1 == 0) {
        return 0;
      }
    }
  }
  return 1;
}




undefined4 FUN_0802c74c(int param_1,int len,byte *data)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  int iVar8;
  undefined1 *puVar9;
  
  puVar9 = &stack0xffffffe0;
  uVar7 = DAT_2000a26c << 8;
  puVar2 = &stack0xffffffe0;
  for (uVar5 = uVar7; 0x1000 < uVar5; uVar5 = uVar5 - 0x1000) {
    puVar9 = puVar2 + -0x1000;
    *(puVar2 + -0x1000) = puVar2 + -0x1000;
    puVar2 = puVar2 + -0x1000;
  }
  iVar1 = -uVar5;
  if (len < 1) {
LAB_0802c7c2:
    uVar4 = 1;
  }
  else {
    while( true ) {
      iVar8 = (uVar7 < len) * uVar7 + (uVar7 >= len) * len;
      iVar3 = FUN_0802c5f8(param_1,iVar8,puVar9 + iVar1);
      uVar4 = 0;
      if (iVar3 == 0) break;
      if (iVar8 != 0) {
        if (puVar9[iVar1] != *data) {
          return 0;
        }
        puVar6 = puVar9 + iVar1;
        while( true ) {
          puVar6 = puVar6 + 1;
          data = data + 1;
          if (puVar6 == puVar9 + iVar8 + iVar1) break;
          if (*data != *puVar6) {
            return 0;
          }
        }
      }
      len = len - iVar8;
      if (len < 1) goto LAB_0802c7c2;
      param_1 = param_1 + iVar8;
      uVar7 = DAT_2000a26c << 8;
    }
  }
  return uVar4;
}




void zw_fpga_firmware_upload_setup(int param_1,int len,int data)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = param_1;
  iVar3 = len;
  iVar5 = data;
  while( true ) {
    if (iVar3 < 1) {
      FUN_0802c74c(param_1,len,data);
      return;
    }
    iVar1 = DAT_2000a270 * 0x100;
    iVar2 = (iVar1 < iVar3) * iVar1 + (iVar1 >= iVar3) * iVar3;
    iVar1 = FUN_0802c590(iVar4,iVar2,iVar5);
    if (iVar1 == 0) break;
    iVar3 = iVar3 - iVar2;
    iVar4 = iVar4 + iVar2;
    iVar5 = iVar5 + iVar2;
  }
  return;
}




int FUN_0802c818(void)

{
  int iVar1;
  undefined2 local_50 [28];
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  uint uStack_c;
  
  iVar1 = FUN_0802c68c();
  if (iVar1 != 0) {
    memcpy(local_50,data_48_,0x48);
    local_50[0] = 0x5aa5;
    uStack_18 = DAT_2000a264 + 0x7fff6b00;
    uStack_14 = ~uStack_18;
    uStack_10 = DAT_2000a264 + 0x7fff6000;
    uStack_c = ~uStack_10;
    DAT_2000a278 = DAT_2000a278 + 0x28;
    iVar1 = zw_fpga_firmware_upload_setup(0,0x48,local_50);
    if (iVar1 != 0) {
      DAT_2000a278 = DAT_2000a278 + -0x28;
      return iVar1;
    }
  }
  return 0;
}




int FUN_0802c88c(void)

{
  int iVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 uStack_14;
  uint uStack_10;
  uint uStack_c;
  
  local_18 = 0x8001045a;
  uStack_14 = 0x34;
  iVar1 = FUN_0802c590(&peripheral_bbp_102c,4,&local_18);
  if (((iVar1 != 0) && (iVar1 = FUN_0802c590(&peripheral_bbp_1014,4,&uStack_14), iVar1 != 0)) &&
     (iVar1 = FUN_0802c5f8(&peripheral_bbp_1010,4,&uStack_10), iVar1 != 0)) {
    uStack_10 = uStack_10 | 0x4040;
    iVar1 = FUN_0802c590(&peripheral_bbp_1010,4,&uStack_10);
    if (iVar1 != 0) {
      iVar1 = 100;
      do {
        iVar2 = FUN_0802c5f8(&peripheral_bbp_100c,4,&uStack_c);
        if (iVar2 == 0) {
          return 0;
        }
      } while (((uStack_c & 1) != 0) && (iVar1 = iVar1 + -1, iVar1 != 0));
      uStack_10 = uStack_10 & 0xffffbfbf;
      iVar1 = FUN_0802c590(&peripheral_bbp_1010,4,&uStack_10);
      if ((iVar1 != 0) && (iVar1 = FUN_0802c5f8(&peripheral_bbp_1030,4,&DAT_2000a264), iVar1 != 0)) {
        DAT_2000a264 = (DAT_2000a264 >> 3) + 1;
        return iVar1;
      }
    }
  }
  return 0;
}




int FUN_0802c954(uint baudrate)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  char *pcVar7;
  undefined4 *puVar8;
  uint uVar9;
  uint len;
  int iVar10;
  undefined1 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  undefined4 uVar17;
  undefined1 auStack_50 [3];
  undefined1 uStack_4d;
  uint8_t local_4c [32];
  
  puVar11 = auStack_50;
  uVar9 = baudrate;
  if (DAT_2000a27c < 0x20) {
    uVar9 = (baudrate < 0x1c200) * 0x1c200 + (baudrate >= 0x1c200) * 0x1c200;
  }
  DAT_2000a278 = 0x14;
  iVar3 = FUN_0802c3d0(uVar9);
  if (iVar3 != 0) {
    HAL_Delay(10);
    iVar3 = FUN_0802c420(0);
    if (iVar3 != 0) {
      HAL_Delay(0x14);
      FifoRead(local_4c,1);
      len = local_4c[0] + 1;
      puVar2 = auStack_50;
      for (uVar6 = len + 3 & 0xfffffffc; 0x1000 < uVar6; uVar6 = uVar6 - 0x1000) {
        puVar11 = puVar2 + -0x1000;
        *(puVar2 + -0x1000) = puVar2 + -0x1000;
        puVar2 = puVar2 + -0x1000;
      }
      iVar3 = -uVar6;
      puVar8 = puVar11 + iVar3;
      FifoRead(puVar11 + iVar3,len);
      printf_disabled_1("uart_init0 bytes(%d) ={\r\n",len);
      if (len != 0) {
        do {
          uVar5 = *puVar8;
          puVar8 = puVar8 + 1;
          printf_disabled_1("%x ",uVar5);
        } while (puVar8 != puVar11 + len + iVar3);
      }
      printf_disabled_1("}\r\n");
      iVar4 = FUN_0802c388(DAT_2000a278);
      if (iVar4 != 0) {
        uVar5 = 1;
        DAT_2000a274 = 0;
        DAT_2000a270 = 1;
        DAT_2000a26c = 1;
        if (1 < len) {
          pcVar7 = puVar11 + iVar3 + 1;
          iVar10 = 0;
          iVar14 = 0;
          uVar17 = 1;
          iVar13 = 0;
          iVar16 = 0;
          do {
            cVar1 = *pcVar7;
            if (cVar1 == '3') {
              uVar17 = 0x10;
              iVar12 = iVar13;
              iVar14 = iVar4;
              iVar15 = iVar16;
            }
            else {
              iVar12 = iVar4;
              iVar15 = iVar4;
              if ((cVar1 != -0x5f) && (iVar12 = iVar13, iVar15 = iVar16, cVar1 == '\x13')) {
                uVar5 = 4;
                iVar10 = iVar4;
              }
            }
            pcVar7 = pcVar7 + 1;
            iVar13 = iVar12;
            iVar16 = iVar15;
          } while (puVar11 + len + iVar3 != pcVar7);
          if (iVar14 != 0) {
            DAT_2000a270 = uVar17;
          }
          if (iVar10 != 0) {
            DAT_2000a26c = uVar5;
          }
          if (iVar12 != 0) {
            DAT_2000a274 = iVar15;
          }
        }
        DAT_2000a27c = puVar11[iVar3];
        iVar3 = FUN_0802c5f8(0,1,&uStack_4d);
        if (iVar3 == 0) {
          iVar3 = FUN_0802c420(0x92);
          if ((iVar3 != 0) && (iVar3 = FUN_0802c388(0x14), iVar3 != 0)) {
LAB_0802cae2:
            iVar3 = FUN_0802c954(baudrate);
            return iVar3;
          }
        }
        else if (DAT_2000a27c < 0x20) {
          iVar3 = zw_fpga_firmware_upload_setup(0,0x14f8,fpga_firmware_0_);
          if ((iVar3 != 0) && (iVar3 = FUN_0802c544(0), iVar3 != 0)) {
            iVar3 = 2400000;
            do {
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
            DAT_2000a27c = 0x20;
            iVar3 = FUN_0802c954(baudrate);
            return iVar3;
          }
        }
        else {
          if (uVar9 == baudrate) {
            return iVar3;
          }
          iVar3 = FUN_0802c674();
          if (iVar3 != 0) {
            iVar3 = 2400000;
            do {
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
            goto LAB_0802cae2;
          }
        }
      }
    }
  }
  return 0;
}




undefined4 FUN_0802cb64(void)

{
  undefined4 uVar1;
  int iVar2;
  
  zw_clear_bits(&peripheral_gpioA_data,0x800);
  iVar2 = 240000;
  do {
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  uVar1 = zw_set_bits(&peripheral_gpioA_data,0x800);
  iVar2 = 2400000;
  do {
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return uVar1;
}




void FUN_0802cba0(undefined4 baudrate)

{
  FUN_0802c2c4();
  FUN_0802c2fc(baudrate);
  DAT_2000a27c = 0;
  zw_set_bits(&peripheral_gpioA_data,0x8000);
  FUN_0802cb64();
  HAL_Delay(2000);
  FUN_0802c954(baudrate);
  return;
}




void FUN_0802cbdc(void)

{
  FUN_0802c2c4();
  HAL_UART_DeInit(&DAT_20030c38);
  DAT_2000a27c = 0;
  zw_clear_bits(&peripheral_gpioA_data,0x8000);
  FUN_0802cb64();
  return;
}




void FUN_0802cc0c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = zw_fpga_flash_erase_(0,param_1);
  if (iVar1 == 0) {
    return;
  }
  zw_fpga_firmware_upload_setup(0,param_1,param_2);
  return;
}




undefined4 FUN_0802cc30(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0802c88c();
  if ((iVar1 != 0) && (iVar1 = FUN_0802c818(), iVar1 != 0)) {
    uVar2 = FUN_0802cc0c(0x10,&DAT_0807ddb4);
    return uVar2;
  }
  return 0;
}




undefined4 zw_fpga_firmware_upload(int firmware_version_select_)

{
  int iVar1;
  undefined4 uVar2;
  byte *pbVar3;
  
  printf_disabled_1("\n******************start fpga upload...****************************\n");
  iVar1 = zw_fpga_flash_erase_(DAT_2000a264 + 0x7fff6000,40960);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = zw_fpga_firmware_upload_setup(DAT_2000a264 + 0x7fff6000,2720,fpga_firmware_1);
  if (iVar1 == 0) {
    return 0;
  }
  if (firmware_version_select_ == 0) {
    pbVar3 = fpga_firmware_2_v1;
LAB_0802ccc0:
    iVar1 = zw_fpga_firmware_upload_setup(DAT_2000a264 + 0x7fff6b00,24832,pbVar3);
  }
  else {
    if (firmware_version_select_ != 1) {
      if (firmware_version_select_ != 2) goto LAB_0802cc96;
      pbVar3 = fpga_firmware_2_v2;
      goto LAB_0802ccc0;
    }
    iVar1 = zw_fpga_firmware_upload_setup(DAT_2000a264 + 0x7fff6b00,25296,fpga_firmware_3);
  }
  if (iVar1 == 0) {
    return 0;
  }
LAB_0802cc96:
  printf_disabled_1("\n******************start mcu_cor2 upload...****************************\n");
  iVar1 = zw_fpga_flash_erase_(0,32768);
  if (iVar1 == 0) {
    return 0;
  }
  uVar2 = zw_fpga_firmware_upload_setup(0,14216,mcu_cor2_firmware);
  return uVar2;
}




int zw_firmware_uart_upgrade(uint32_t baudrate,undefined4 firmware_version_select_)

{
  int iVar1;
  
  puts("start download...");
  HAL_WDG_DeInit(&hwdg);
  zw_fifoInit();
  iVar1 = FUN_0802cba0(baudrate);
  if (iVar1 == 0) {
    puts("uart_download_init failed!");
    HAL_Delay(1000);
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0802cc30();
    if (iVar1 == 0) {
      puts("uart_init_flash failed!");
      HAL_Delay(1000);
      return 0;
    }
    iVar1 = zw_fpga_firmware_upload(firmware_version_select_);
    if (iVar1 == 0) {
      puts("uart_update_logic failed!");
      HAL_Delay(1000);
      return 0;
    }
    puts("upgrade successful!");
    HAL_WDG_Init_wrapper();
  }
  return iVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


void SystemInit(void)

{
  system_VIC_IABR0 = 0;
  system_VIC_ICPR0 = 0xffffffff;
  return;
}




void trap_c(uint32_t *regs)

{
  undefined4 in_r1;
  undefined4 in_r2;
  undefined4 in_r3;
  char *unaff_r4;
  char *format;
  
  wm_printf("CPU Exception : %u",unaff_r4,in_r1 >> 0x10,in_r2,in_r3);
  putchar(10);
  wm_printf("r%d: %08x\t",0x0,*regs);
  format = 0x0;
  while (format = format + 1, format != 0x10) {
    while (wm_printf("r%d: %08x\t",format,regs[format]), format % 5 == 4) {
      format = format + 1;
      putchar(10);
      if (format == 0x10) goto LAB_0802ce2e;
    }
  }
LAB_0802ce2e:
  putchar(10);
  wm_printf("epsr: %8x\n",regs[0x10]);
  wm_printf("epc : %8x\n",regs[0x11]);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


void board_init(void)

{
  system_VIC_ICER0 = 0;
  system_VIC_ICPR0 = 0;
  peripheral_uart0_baud_rate_ctrl = 0x14;
  peripheral_uart0_line_ctrl = 0xc3;
  peripheral_uart0_auto_flow_ctrl = 0;
  peripheral_uart0_dma_ctrl = 0;
  peripheral_uart0_fifo_ctrl = 0;
  return;
}




void _out_uart(char character,void *buffer,size_t idx,size_t maxlen)

{
  uint uVar1;
  undefined3 in_register_00000001;
  
  do {
    uVar1 = peripheral_uart0_fifo_status;
  } while (0x1f < (uVar1 & 0x3f));
  peripheral_uart0_tx_data_window = CONCAT31(in_register_00000001,character);
  return;
}




void _out_null(char character,void *buffer,size_t idx,size_t maxlen)

{
  return;
}




size_t _out_rev(out_fct_type out,char *buffer,size_t idx,size_t maxlen,char *buf,size_t len,uint width,uint flags)

{
  size_t sVar1;
  char *pcVar2;
  uint uVar3;
  size_t sVar4;
  size_t sVar5;
  size_t sVar6;
  
  sVar4 = idx;
  if (((flags & 3) == 0) && (len < width)) {
    sVar1 = idx;
    do {
      sVar4 = sVar1 + 1;
      (*(out & 0xfffffffe))(0x20,buffer,sVar1,maxlen);
      sVar1 = sVar4;
    } while (sVar4 != (width - len) + idx);
  }
  if (len != 0) {
    pcVar2 = buf + (len - 1);
    sVar5 = len + sVar4;
    sVar1 = sVar4;
    do {
      sVar6 = sVar1 + 1;
      (*(out & 0xfffffffe))(*pcVar2,buffer,sVar1,maxlen);
      pcVar2 = pcVar2 + -1;
      sVar1 = sVar6;
      sVar4 = sVar5;
    } while (sVar6 != sVar5);
  }
  if ((flags & 2) != 0) {
    uVar3 = sVar4 - idx;
    while (uVar3 < width) {
      (*(out & 0xfffffffe))(0x20,buffer,sVar4,maxlen);
      uVar3 = (sVar4 + 1) - idx;
      sVar4 = sVar4 + 1;
    }
  }
  return sVar4;
}




size_t _ntoa_format(out_fct_type out,char *buffer,size_t idx,size_t maxlen,char *buf,size_t len,bool negative,uint base,uint prec,uint width,uint flags)

{
  size_t sVar1;
  uint uVar2;
  char *pcVar3;
  
  if ((flags & 2) == 0) {
    if ((width == 0) || ((flags & 1) == 0)) {
      if ((len < prec) && (len < 0x20)) {
LAB_0802cf7c:
        pcVar3 = buf + len;
        do {
          len = len + 1;
          *pcVar3 = '0';
          if (prec <= len) break;
          pcVar3 = pcVar3 + 1;
        } while (len != 0x20);
        uVar2 = width;
        if ((flags & 1) != 0) goto LAB_0802cfa2;
      }
      goto LAB_0802cfd6;
    }
    if ((negative) || ((flags & 0xc) != 0)) {
      width = width - 1;
    }
    uVar2 = width;
    if (len < prec) {
      if (len < 0x20) goto LAB_0802cf7c;
      if (width <= len) goto LAB_0802cfd6;
    }
    else {
LAB_0802cfa2:
      width = uVar2;
      if (uVar2 <= len) goto LAB_0802cfd6;
      if (len < 0x20) {
        pcVar3 = buf + len;
        do {
          len = len + 1;
          *pcVar3 = '0';
          width = len;
          if (len == uVar2) goto LAB_0802cfd6;
          pcVar3 = pcVar3 + 1;
          width = uVar2;
        } while (len != 0x20);
      }
    }
    if ((flags & 0x10) == 0) goto LAB_0802d032;
    uVar2 = len;
    if ((flags & 0x400) == 0) goto LAB_0802d082;
    goto LAB_0802cfea;
  }
LAB_0802cfd6:
  if ((flags & 0x10) != 0) {
    if (((flags & 0x400) == 0) && (uVar2 = len, len != 0)) {
LAB_0802d082:
      if (((prec != uVar2) && (len = uVar2, uVar2 != width)) || (len = uVar2 - 1, len == 0)) goto LAB_0802cfea;
      if (base == 0x10) {
        len = uVar2 - 2;
        goto LAB_0802d0d8;
      }
LAB_0802cff2:
      if (base == 2) {
        if (0x1f < len) goto LAB_0802d032;
        buf[len] = 'b';
        len = len + 1;
      }
    }
    else {
LAB_0802cfea:
      if (base != 0x10) goto LAB_0802cff2;
LAB_0802d0d8:
      if ((flags & 0x20) == 0) {
        if (0x1f < len) goto LAB_0802d032;
        buf[len] = 'x';
        len = len + 1;
      }
      else {
        if (0x1f < len) goto LAB_0802d032;
        buf[len] = 'X';
        len = len + 1;
      }
    }
    if (0x1f < len) goto LAB_0802d032;
    buf[len] = '0';
    len = len + 1;
  }
  if (len < 0x20) {
    if (negative) {
      buf[len] = '-';
      len = len + 1;
    }
    else if ((flags & 4) == 0) {
      if ((flags & 8) != 0) {
        buf[len] = ' ';
        len = len + 1;
      }
    }
    else {
      buf[len] = '+';
      len = len + 1;
    }
  }
LAB_0802d032:
  sVar1 = _out_rev(out,buffer,idx,maxlen,buf,len,width,flags);
  return sVar1;
}




size_t _ntoa_long(out_fct_type *out,char *buffer,size_t idx,size_t maxlen,ulong value,bool negative,ulong base,uint prec,uint width,uint flags)

{
  char cVar1;
  uint uVar2;
  uint flags_00;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  size_t sVar6;
  char cVar7;
  char local_30 [32];
  
  flags_00 = flags;
  if ((value == 0) && (flags_00 = flags & 0xffffffef, (flags & 0x400) != 0)) {
    sVar6 = 0;
  }
  else {
    cVar7 = 'A';
    if ((flags_00 & 0x20) == 0) {
      cVar7 = 'a';
    }
    pcVar4 = local_30;
    sVar6 = 0;
    iVar5 = 0x20;
    do {
      uVar3 = value / base;
      uVar2 = value - uVar3 * base;
      sVar6 = sVar6 + 1;
      cVar1 = uVar2;
      if ((uVar2 & 0xff) < 10) {
        cVar1 = cVar1 + '0';
      }
      else {
        cVar1 = cVar1 + cVar7 + -10;
      }
      *pcVar4 = cVar1;
      if (uVar3 == 0) break;
      pcVar4 = pcVar4 + 1;
      iVar5 = iVar5 + -1;
      value = uVar3;
    } while (iVar5 != 0);
  }
  sVar6 = _ntoa_format(out,buffer,idx,maxlen,local_30,sVar6,negative,base,prec,width,flags_00);
  return sVar6;
}




size_t _ntoa_long_long(out_fct_type out,char *buffer,size_t idx,size_t maxlen,ulonglong value,bool negative,ulonglong base,uint prec,uint width,uint flags)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  size_t sVar6;
  char *pcVar7;
  char cVar8;
  uint in_stack_0000000c;
  char local_4c [32];
  
  if ((value == 0) && (uVar5 = width & 0x400, width = width & 0xffffffef, uVar5 != 0)) {
    sVar6 = 0;
  }
  else {
    cVar8 = 'A';
    if ((width & 0x20) == 0) {
      cVar8 = 'a';
    }
    pcVar7 = local_4c;
    sVar6 = 0;
    do {
      iVar4 = value >> 0x20;
      bVar2 = __umoddi3(value,iVar4,in_stack_0000000c,base);
      sVar6 = sVar6 + 1;
      if (bVar2 < 10) {
        cVar1 = bVar2 + 0x30;
      }
      else {
        cVar1 = bVar2 + cVar8 + -10;
      }
      *pcVar7 = cVar1;
      iVar3 = __udivdi3(value,iVar4,in_stack_0000000c,base);
      value = CONCAT44(iVar4,iVar3);
    } while ((iVar4 != 0 || iVar3 != 0) && (pcVar7 = pcVar7 + 1, sVar6 != 0x20));
  }
  sVar6 = _ntoa_format(out,buffer,idx,maxlen,local_4c,sVar6,negative,in_stack_0000000c,base._4_4_,prec,width);
  return sVar6;
}




size_t _ftoa(out_fct_type out,char *buffer,size_t idx,size_t maxlen,double value,uint prec,uint width,uint flags)

{
  bool bVar1;
  int iVar2;
  size_t sVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  uint uVar13;
  uint uVar14;
  char *pcVar15;
  int iVar16;
  char *pcVar17;
  uint uStack_6c;
  char local_4c [32];
  
  uStack_6c = width;
  iVar2 = __nedf2(value._0_4_,value._4_4_,value._0_4_,value._4_4_);
  if (iVar2 != 0) {
    pcVar17 = "nan";
    sVar3 = 3;
    goto LAB_0802d33a;
  }
  iVar2 = __ltdf2(value._0_4_,value._4_4_,0xffffffff,0xffffffff);
  if (iVar2 < 0) {
    pcVar17 = "fni-";
    sVar3 = 4;
    goto LAB_0802d33a;
  }
  iVar2 = __gtdf2(value._0_4_,value._4_4_,0xffffffff,0xffffffff);
  if (0 < iVar2) {
    pcVar17 = "fni+";
    if ((flags & 4) == 0) {
      pcVar17 = "fni";
    }
    sVar3 = 4;
    if ((flags & 4) == 0) {
      sVar3 = 3;
    }
    goto LAB_0802d33a;
  }
  iVar2 = __gtdf2(value._0_4_,value._4_4_,0,0x41cdcd65);
  if ((0 < iVar2) || (iVar2 = __ltdf2(value._0_4_,value._4_4_,0,0xc1cdcd65), iVar2 < 0)) {
    sVar3 = _etoa(out,buffer,idx,maxlen,value,prec,width,flags);
    return sVar3;
  }
  iVar2 = __ltdf2(value._0_4_,value._4_4_,0,0);
  bVar1 = iVar2 < 0;
  if (bVar1) {
    uVar10 = 0;
    uVar11 = __subdf3(0,0,value._0_4_,value._4_4_);
    value = CONCAT44(uVar10,uVar11);
  }
  uVar11 = value >> 0x20;
  uVar10 = SUB84(value,0);
  if ((flags & 0x400) == 0) {
    iVar2 = 0;
    uVar13 = 6;
  }
  else if (prec < 10) {
    iVar2 = 0;
    uVar13 = prec;
  }
  else {
    local_4c[0] = '0';
    uVar13 = prec - 1;
    pcVar17 = local_4c;
    iVar2 = 1;
    iVar8 = 0x1f;
    do {
      pcVar17 = pcVar17 + 1;
      if (iVar2 == prec - 9) break;
      iVar2 = iVar2 + 1;
      *pcVar17 = '0';
      uVar13 = uVar13 - 1;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  pcVar17 = local_4c;
  uVar9 = uVar11;
  uVar4 = __fixdfsi(uVar10,uVar11);
  uVar5 = __floatsidf();
  uVar12 = uVar11;
  __subdf3(uVar10,uVar11,uVar5,uVar9);
  uVar5 = __muldf3();
  uVar9 = uVar12;
  uVar6 = __fixunsdfsi();
  uVar7 = __floatunsidf();
  uVar5 = __subdf3(uVar5,uVar12,uVar7,uVar9);
  uVar9 = uVar12;
  iVar8 = __gtdf2();
  if (iVar8 < 1) {
    iVar8 = __ltdf2(uVar5,uVar12,0,0);
    if ((-1 < iVar8) && ((uVar6 == 0 || ((uVar6 & 1) != 0)))) {
      uVar6 = uVar6 + 1;
    }
  }
  else {
    uVar6 = uVar6 + 1;
    __floatunsidf(uVar6);
    iVar8 = __gedf2();
    uVar12 = uVar9;
    if (-1 < iVar8) {
      uVar4 = uVar4 + 1;
      uVar6 = 0;
    }
  }
  if (uVar13 == 0) {
    uVar9 = __floatsidf(uVar4);
    uVar10 = __subdf3(uVar10,uVar11,uVar9,uVar12);
    iVar8 = __ltdf2();
    if (((-1 < iVar8) || (iVar8 = __gtdf2(uVar10,uVar11,0,0), 0 < iVar8)) && ((uVar4 & 1) != 0)) {
      uVar4 = uVar4 + 1;
    }
LAB_0802d490:
    if (iVar2 == 0x20) goto LAB_0802d596;
    iVar8 = uVar4 / 10;
    sVar3 = iVar2 + 1;
    pcVar17[iVar2] = uVar4 + iVar8 * -10 + '0';
    if (iVar8 != 0) {
      pcVar15 = pcVar17 + sVar3;
      do {
        if (sVar3 == 0x20) goto LAB_0802d596;
        iVar2 = iVar8 / 10;
        *pcVar15 = iVar8 + iVar2 * -10 + '0';
        pcVar15 = pcVar15 + 1;
        sVar3 = sVar3 + 1;
        iVar8 = iVar2;
      } while (iVar2 != 0);
    }
    uVar13 = sVar3;
    if ((flags & 3) == 1) goto LAB_0802d690;
  }
  else {
    if (iVar2 != 0x20) {
      uVar14 = uVar6 / 10;
      iVar16 = uVar13 - 1;
      iVar8 = iVar2 + 1;
      pcVar17[iVar2] = uVar6 + uVar14 * -10 + '0';
      if (uVar14 != 0) {
        pcVar15 = pcVar17 + iVar8;
        do {
          if (iVar8 == 0x20) goto LAB_0802d596;
          uVar13 = uVar14 / 10;
          *pcVar15 = uVar14 + uVar13 * -10 + '0';
          pcVar15 = pcVar15 + 1;
          iVar16 = iVar16 + -1;
          iVar8 = iVar8 + 1;
          uVar14 = uVar13;
        } while (uVar13 != 0);
      }
      if (iVar8 != 0x20) {
        if (iVar16 != 0) {
          pcVar15 = pcVar17 + iVar8;
          iVar16 = iVar16 + iVar8;
          do {
            iVar8 = iVar8 + 1;
            *pcVar15 = '0';
            if (iVar8 == 0x20) goto LAB_0802d596;
            pcVar15 = pcVar15 + 1;
          } while (iVar8 != iVar16);
        }
        iVar2 = iVar8 + 1;
        pcVar17[iVar8] = '.';
        goto LAB_0802d490;
      }
    }
LAB_0802d596:
    if ((flags & 3) != 1) {
      sVar3 = 0x20;
      goto LAB_0802d33a;
    }
    sVar3 = 0x20;
LAB_0802d690:
    uVar13 = sVar3;
    if (width != 0) {
      if ((bVar1) || ((flags & 0xc) != 0)) {
        uStack_6c = width - 1;
      }
      if (sVar3 < uStack_6c) {
        width = uStack_6c;
        if (sVar3 != 0x20) {
          pcVar15 = pcVar17 + sVar3;
          do {
            sVar3 = sVar3 + 1;
            *pcVar15 = '0';
            uVar13 = uStack_6c;
            if (sVar3 == uStack_6c) goto LAB_0802d4de;
            pcVar15 = pcVar15 + 1;
          } while (sVar3 != 0x20);
        }
        goto LAB_0802d33a;
      }
    }
  }
LAB_0802d4de:
  sVar3 = uVar13;
  width = uStack_6c;
  if (uVar13 != 0x20) {
    if (bVar1) {
      pcVar17[uVar13] = '-';
      sVar3 = uVar13 + 1;
    }
    else if ((flags & 4) == 0) {
      if ((flags & 8) != 0) {
        pcVar17[uVar13] = ' ';
        sVar3 = uVar13 + 1;
      }
    }
    else {
      pcVar17[uVar13] = '+';
      sVar3 = uVar13 + 1;
    }
  }
LAB_0802d33a:
  sVar3 = _out_rev(out,buffer,idx,maxlen,pcVar17,sVar3,width,flags);
  return sVar3;
}




size_t _etoa(out_fct_type out,char *buffer,size_t idx,size_t maxlen,double value,uint prec,uint width,uint flags)

{
  double value_00;
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  size_t sVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  ulong value_01;
  uint uVar10;
  uint uVar11;
  uint uStack_64;
  uint uStack_60;
  uint uStack_58;
  
  uStack_64 = flags;
  iVar1 = __nedf2(value._0_4_,value._4_4_,value._0_4_,value._4_4_);
  if (((iVar1 == 0) && (iVar1 = __gtdf2(value._0_4_,value._4_4_,0xffffffff,0xffffffff), iVar1 < 1)) &&
     (iVar1 = __ltdf2(value._0_4_,value._4_4_,0xffffffff,0xffffffff), -1 < iVar1)) {
    uVar11 = value._4_4_;
    __ltdf2(value._0_4_,value._4_4_,0,0);
    if ((flags & 0x400) == 0) {
      prec = 6;
    }
    __floatsidf(((value._4_4_ & 0x3fffffff) >> 0x14) - 0x3ff);
    __muldf3();
    uVar2 = __adddf3();
    uVar10 = value._4_4_ & 0x7ffff;
    __subdf3(value._0_4_,uVar10,0,0);
    uVar3 = __muldf3();
    __adddf3(uVar2,uVar11,uVar3,uVar10);
    uStack_58 = __fixdfsi();
    uVar2 = __floatsidf();
    __muldf3();
    __adddf3();
    uVar3 = __fixdfsi();
    uVar2 = __muldf3(uVar2,uVar11,0xbbb55516,0x40026bb1);
    uVar10 = uVar11;
    __floatsidf(uVar3);
    uVar3 = __muldf3();
    uVar2 = __subdf3(uVar2,uVar11,uVar3,uVar10);
    uVar10 = uVar11;
    uVar3 = __muldf3();
    uVar7 = uVar11;
    uVar4 = __adddf3(uVar2,uVar11,uVar2,uVar11);
    uVar8 = uVar10;
    __divdf3(uVar3,uVar10,0,0);
    uVar5 = __adddf3();
    uVar9 = uVar10;
    __divdf3(uVar3,uVar10,uVar5,uVar8);
    uVar5 = __adddf3();
    uVar3 = __divdf3(uVar3,uVar10,uVar5,uVar9);
    uVar5 = 0;
    uVar2 = __subdf3(0,0,uVar2,uVar11);
    uVar2 = __adddf3(uVar3,uVar10,uVar2,uVar5);
    __divdf3(uVar4,uVar7,uVar2,uVar10);
    __adddf3();
    uVar2 = __muldf3();
    iVar1 = __ltdf2(value._0_4_,value._4_4_,uVar2,uVar7);
    if (iVar1 < 0) {
      uStack_58 = uStack_58 - 1;
      uVar2 = __divdf3(uVar2,uVar7,0,0);
    }
    uVar11 = (0xc6 < uStack_58 + 99) + 4;
    uStack_60 = prec;
    if ((flags & 0x800) != 0) {
      iVar1 = __gedf2(value._0_4_,value._4_4_,0xeb1c432d,0x3f1a36e2);
      if ((iVar1 < 0) || (iVar1 = __ltdf2(value._0_4_,value._4_4_,0,0x412e8480), -1 < iVar1)) {
        if ((prec != 0) && ((flags & 0x400) != 0)) {
          uStack_60 = prec - 1;
        }
      }
      else {
        if (uStack_58 < prec) {
          uStack_60 = (prec - uStack_58) - 1;
        }
        else {
          uStack_60 = 0;
        }
        uStack_64 = flags | 0x400;
        uVar11 = 0;
        uStack_58 = 0;
      }
    }
    uVar10 = width - uVar11;
    if (width <= uVar11) {
      uVar10 = 0;
    }
    if (((uStack_64 & 2) != 0) && (uVar11 != 0)) {
      uVar10 = 0;
    }
    value_00 = value;
    if (uStack_58 != 0) {
      uVar8 = value._4_4_;
      uVar2 = __divdf3(value._0_4_,value._4_4_,uVar2,uVar7);
      value_00 = CONCAT44(uVar8,uVar2);
    }
    __ltdf2(value._0_4_,value._4_4_,0,0);
    sVar6 = _ftoa(out,buffer,idx,maxlen,value_00,uStack_60,uVar10,uStack_64 & 0xfffff7ff);
    if ((uStack_60 == 0) && (uVar11 != 0)) {
      uVar2 = 0x45;
      if ((uStack_64 & 0x20) == 0) {
        uVar2 = 0x65;
      }
      (*(out & 0xfffffffe))(uVar2,buffer,sVar6,maxlen);
      value_01 = uStack_58;
      if (uStack_58 < 0) {
        value_01 = ~uStack_58 + 1;
      }
      sVar6 = _ntoa_long(out,buffer,sVar6 + 1,maxlen,value_01,SUB41(uStack_58 >> 0x1f,0),10,0,uVar11 - 1,5);
      if ((uStack_64 & 2) != 0) {
        uVar11 = sVar6 - idx;
        while (uVar11 < width) {
          (*(out & 0xfffffffe))(0x20,buffer,sVar6,maxlen);
          uVar11 = (sVar6 + 1) - idx;
          sVar6 = sVar6 + 1;
        }
      }
    }
  }
  else {
    sVar6 = _ftoa(out,buffer,idx,maxlen,value,prec,width,flags);
  }
  return sVar6;
}



// WARNING: Restarted to delay deadcode elimination for space: register


byte * _vsnprintf(out_fct_type *__s,char *__maxlen,byte *__format,byte *__arg,double *param_5)

{
  byte bVar1;
  char cVar2;
  bool bVar3;
  uint uVar4;
  byte *pbVar5;
  ulong value;
  uint uVar6;
  ulong base;
  byte bVar7;
  uint uVar8;
  byte *pbVar9;
  double *pdVar10;
  uint uVar11;
  uint uVar12;
  char *pcVar13;
  double *pdVar14;
  out_fct_type *out;
  double *prec;
  byte *idx;
  uint uVar15;
  int iVar16;
  char *pcVar17;
  double *prec_00;
  int iVar18;
  uint *puVar19;
  uint *puVar20;
  double value_00;
  ulonglong uVar21;
  double *in_stack_ffffff9c;
  double *pdStack_60;
  uint uStack_5c;
  undefined4 uStack_58;
  char local_54 [17];
  undefined1 uStack_43;
  
  out = _out_null;
  if (__maxlen != 0x0) {
    out = __s;
  }
  pbVar5 = 0x0;
LAB_0802dbfe:
  bVar1 = *__arg;
  idx = pbVar5;
  while( true ) {
    uVar4 = bVar1;
    if (uVar4 == 0) {
      pbVar5 = idx;
      if (__format <= idx) {
        pbVar5 = __format + -1;
      }
      (*(out & 0xfffffffe))(0,__maxlen,pbVar5,__format);
      return idx;
    }
    if (uVar4 == 0x25) break;
switchD_0802dca6_caseD_1:
    __arg = __arg + 1;
    (*(out & 0xfffffffe))(uVar4,__maxlen,idx,__format);
    bVar1 = *__arg;
    idx = idx + 1;
  }
  __arg = __arg + 1;
  uStack_5c = 0;
  while( true ) {
    uVar4 = *__arg;
    if (false) break;
    switch(uVar4 - 0x20 & 0xff) {
    case 0:
      uStack_5c = uStack_5c | 8;
      __arg = __arg + 1;
      break;
    default:
      goto switchD_0802dc20_caseD_1;
    case 3:
      uStack_5c = uStack_5c | 0x10;
      __arg = __arg + 1;
      break;
    case 0xb:
      uStack_5c = uStack_5c | 4;
      __arg = __arg + 1;
      break;
    case 0xd:
      uStack_5c = uStack_5c | 2;
      __arg = __arg + 1;
      break;
    case 0x10:
      uStack_5c = uStack_5c | 1;
      __arg = __arg + 1;
    }
  }
switchD_0802dc20_caseD_1:
  if ((uVar4 - 0x30 & 0xff) < 10) {
    prec_00 = 0x0;
    do {
      __arg = __arg + 1;
      prec_00 = uVar4 + prec_00 * 10 + -0x30;
      uVar4 = *__arg;
    } while ((uVar4 - 0x30 & 0xff) < 10);
    pbVar5 = __arg;
    if (uVar4 == 0x2e) goto LAB_0802dd38;
LAB_0802dc70:
    prec = 0x0;
  }
  else {
    if (uVar4 == 0x2a) {
      prec_00 = *param_5;
      param_5 = param_5 + 4;
      if (prec_00 < 0) {
        uStack_5c = uStack_5c | 2;
        prec_00 = -prec_00;
      }
      uVar4 = __arg[1];
      __arg = __arg + 1;
    }
    else {
      prec_00 = 0x0;
    }
    pbVar5 = __arg;
    if (uVar4 != 0x2e) goto LAB_0802dc70;
LAB_0802dd38:
    uVar4 = pbVar5[1];
    uStack_5c = uStack_5c | 0x400;
    __arg = pbVar5 + 1;
    if ((uVar4 - 0x30 & 0xff) < 10) {
      prec = 0x0;
      do {
        __arg = __arg + 1;
        prec = uVar4 + prec * 10 + -0x30;
        uVar4 = *__arg;
      } while ((uVar4 - 0x30 & 0xff) < 10);
    }
    else {
      if (uVar4 != 0x2a) goto LAB_0802dc70;
      uVar4 = pbVar5[2];
      prec = (-1 < *param_5) * *param_5;
      param_5 = param_5 + 4;
      __arg = pbVar5 + 2;
    }
  }
  if (false) goto switchD_0802dc84_caseD_1;
  switch(uVar4 - 0x68 & 0xff) {
  case 0:
    uVar4 = __arg[1];
    if (uVar4 == 0x68) {
      uVar4 = __arg[2];
      uStack_5c = uStack_5c | 0xc0;
      __arg = __arg + 2;
    }
    else {
      uStack_5c = uStack_5c | 0x80;
      __arg = __arg + 1;
    }
    break;
  case 2:
    uVar4 = __arg[1];
    uStack_5c = uStack_5c | 0x200;
    __arg = __arg + 1;
    break;
  case 4:
    uVar4 = __arg[1];
    if (uVar4 == 0x6c) {
      uVar4 = __arg[2];
      uStack_5c = uStack_5c | 0x300;
      __arg = __arg + 2;
      break;
    }
    uStack_5c = uStack_5c | 0x100;
    __arg = __arg + 1;
    goto joined_r0x0802dcc6;
  case 0xc:
  case 0x12:
    uVar4 = __arg[1];
    uStack_5c = uStack_5c | 0x100;
    __arg = __arg + 1;
  }
switchD_0802dc84_caseD_1:
joined_r0x0802dcc6:
  if (false) goto switchD_0802dca6_caseD_1;
  switch(uVar4 - 0x25 & 0xff) {
  case 0:
    pbVar5 = idx + 1;
    (*(out & 0xfffffffe))(0x25,__maxlen,idx,__format);
    __arg = __arg + 1;
    goto LAB_0802dbfe;
  default:
    goto switchD_0802dca6_caseD_1;
  case 0x20:
  case 0x22:
  case 0x40:
  case 0x42:
    if ((uVar4 & 0xdf) == 0x47) {
      uStack_5c = uStack_5c | 0x800;
      uVar4 = uVar4 & 0xfd;
    }
    if (uVar4 == 0x45) {
      uStack_5c = uStack_5c | 0x20;
    }
    pbVar5 = _etoa(out,__maxlen,idx,__format,*param_5,prec,prec_00,uStack_5c);
    __arg = __arg + 1;
    param_5 = param_5 + 1;
    goto LAB_0802dbfe;
  case 0x21:
  case 0x41:
    if (uVar4 == 0x46) {
      uStack_5c = uStack_5c | 0x20;
    }
    pbVar5 = _ftoa(out,__maxlen,idx,__format,*param_5,prec,prec_00,uStack_5c);
    __arg = __arg + 1;
    param_5 = param_5 + 1;
    goto LAB_0802dbfe;
  case 0x28:
    pbVar5 = *param_5;
    pcVar17 = local_54;
    iVar18 = 6;
    do {
      bVar1 = *pbVar5 >> 4;
      bVar7 = *pbVar5 & 0xf;
      if (bVar1 < 10) {
        *pcVar17 = bVar1 + 0x30;
        if (bVar7 < 10) goto LAB_0802e3ac;
LAB_0802e274:
        pcVar17[1] = bVar7 + 0x37;
      }
      else {
        *pcVar17 = bVar1 + 0x37;
        if (9 < bVar7) goto LAB_0802e274;
LAB_0802e3ac:
        pcVar17[1] = bVar7 + 0x30;
      }
      pcVar17[2] = '-';
      pbVar5 = pbVar5 + 1;
      pcVar17 = pcVar17 + 3;
      iVar18 = iVar18 + -1;
    } while (iVar18 != 0);
    uStack_43 = 0;
    if ((uStack_5c & 0x400) == 0) {
      in_stack_ffffff9c = 0x11;
    }
    else {
      in_stack_ffffff9c = (prec < 0x11) * (uStack_5c & 0x400) + (prec >= 0x11) * 0x11;
    }
    uStack_58 = uStack_5c & 2;
    if (uStack_58 == 0x0) {
      pdVar10 = in_stack_ffffff9c;
      if (in_stack_ffffff9c < prec_00) {
        pbVar9 = prec_00 + idx;
        pbVar5 = idx;
        do {
          idx = pbVar5 + 1;
          (*(out & 0xfffffffe))(0x20,__maxlen,pbVar5,__format);
          pbVar5 = idx;
          pdVar10 = prec_00;
        } while (idx != pbVar9 + -in_stack_ffffff9c);
      }
      in_stack_ffffff9c = pdVar10 + 1;
      if (local_54[0] == '\0') break;
LAB_0802e2e2:
      uStack_5c = uStack_5c & 0x400;
      pcVar17 = local_54;
      cVar2 = local_54[0];
      do {
        pdVar10 = prec;
        if ((uStack_5c != 0) && (pdVar10 = prec + -1, prec == 0x0)) break;
        pcVar17 = pcVar17 + 1;
        pbVar5 = idx + 1;
        (*(out & 0xfffffffe))(cVar2,__maxlen,idx,__format);
        cVar2 = *pcVar17;
        idx = pbVar5;
        prec = pdVar10;
      } while (cVar2 != '\0');
      pbVar5 = idx;
      if (uStack_58 != 0x0) goto LAB_0802e316;
    }
    else {
      if (local_54[0] != '\0') goto LAB_0802e2e2;
LAB_0802e316:
      pdStack_60 = param_5 + 4;
      pbVar5 = idx;
      if (in_stack_ffffff9c < prec_00) {
        iVar18 = -in_stack_ffffff9c;
        pbVar9 = idx;
        do {
          pbVar5 = pbVar9 + 1;
          (*(out & 0xfffffffe))(0x20,__maxlen,pbVar9,__format);
          pbVar9 = pbVar5;
        } while (pbVar5 != prec_00 + idx + iVar18);
        __arg = __arg + 1;
        param_5 = pdStack_60;
        goto LAB_0802dbfe;
      }
    }
    pdStack_60 = param_5 + 4;
    __arg = __arg + 1;
    param_5 = pdStack_60;
    goto LAB_0802dbfe;
  case 0x31:
    puVar19 = *param_5;
    puVar20 = puVar19 + 4;
    iVar18 = 0;
    do {
      uVar4 = 0;
      uVar12 = *puVar19;
      bVar3 = false;
      iVar16 = 4;
      do {
        uVar15 = uVar12 >> (uVar4 & 0x3f);
        uVar8 = (uVar15 & 0xff) >> 4;
        uVar15 = uVar15 & 0xf;
        uVar11 = iVar18 + 1U & 0x7f;
        cVar2 = uVar8;
        if (uVar8 < 10) {
          local_54[iVar18] = cVar2 + '0';
        }
        else {
          local_54[iVar18] = cVar2 + '7';
        }
        iVar18 = uVar11 + 1;
        cVar2 = uVar15;
        if (uVar15 < 10) {
          local_54[uVar11] = cVar2 + '0';
        }
        else {
          local_54[uVar11] = cVar2 + '7';
        }
        if (bVar3) {
          iVar18 = uVar11 + 2;
          local_54[uVar11 + 1] = ':';
        }
        bVar3 = bVar3 ^ 1;
        uVar4 = uVar4 + 8;
        iVar16 = iVar16 + -1;
      } while (iVar16 != 0);
      puVar19 = puVar19 + 1;
    } while (puVar20 != puVar19);
    local_54[iVar18 + -1] = '\0';
    in_stack_ffffff9c = iVar18 + -1;
    if ((uStack_5c & 0x400) != 0) {
      in_stack_ffffff9c = (in_stack_ffffff9c < prec) * in_stack_ffffff9c + (in_stack_ffffff9c >= prec) * prec;
    }
    uStack_58 = uStack_5c & 2;
    if (uStack_58 != 0x0) {
      if (local_54[0] != '\0') goto LAB_0802e1e2;
LAB_0802e218:
      pdStack_60 = param_5 + 4;
      if (in_stack_ffffff9c < prec_00) {
        iVar18 = -in_stack_ffffff9c;
        pbVar9 = idx;
        do {
          pbVar5 = pbVar9 + 1;
          (*(out & 0xfffffffe))(0x20,__maxlen,pbVar9,__format);
          pbVar9 = pbVar5;
        } while (prec_00 + idx + iVar18 != pbVar5);
        __arg = __arg + 1;
        param_5 = pdStack_60;
      }
      else {
LAB_0802e3d8:
        pdStack_60 = param_5 + 4;
        __arg = __arg + 1;
        param_5 = pdStack_60;
        pbVar5 = idx;
      }
      goto LAB_0802dbfe;
    }
    pdVar10 = in_stack_ffffff9c;
    if (in_stack_ffffff9c < prec_00) {
      pbVar9 = prec_00 + idx;
      pbVar5 = idx;
      do {
        idx = pbVar5 + 1;
        (*(out & 0xfffffffe))(0x20,__maxlen,pbVar5,__format);
        pbVar5 = idx;
        pdVar10 = prec_00;
      } while (pbVar9 + -in_stack_ffffff9c != idx);
    }
    in_stack_ffffff9c = pdVar10 + 1;
    if (local_54[0] != '\0') {
LAB_0802e1e2:
      uStack_5c = uStack_5c & 0x400;
      pcVar17 = local_54;
      cVar2 = local_54[0];
      do {
        pdVar10 = prec;
        if ((uStack_5c != 0) && (pdVar10 = prec + -1, prec == 0x0)) break;
        pcVar17 = pcVar17 + 1;
        pbVar5 = idx + 1;
        (*(out & 0xfffffffe))(cVar2,__maxlen,idx,__format);
        cVar2 = *pcVar17;
        idx = pbVar5;
        prec = pdVar10;
      } while (cVar2 != '\0');
      if (uStack_58 != 0x0) goto LAB_0802e218;
      goto LAB_0802e3d8;
    }
    break;
  case 0x33:
  case 0x3d:
  case 0x3f:
  case 0x44:
  case 0x4a:
  case 0x50:
  case 0x53:
    uVar12 = uStack_5c;
    if (uVar4 == 0x78) {
      base = 0x10;
      goto LAB_0802e49a;
    }
    if (uVar4 == 0x58) {
      uVar11 = uStack_5c & 0xfffffff3 | 0x20;
      base = 0x10;
      if ((uStack_5c & 0x400) != 0) goto LAB_0802e056;
LAB_0802e068:
      if ((uVar11 & 0x200) != 0) {
        bVar3 = false;
        value_00 = *param_5;
        goto LAB_0802e576;
      }
      if ((uVar11 & 0x100) != 0) {
        uVar21 = *param_5;
        goto LAB_0802e5ce;
      }
      if ((uVar11 & 0x40) == 0) {
        if ((uVar11 & 0x80) == 0) {
          value = *param_5;
        }
        else {
          value = *param_5;
        }
      }
      else {
        value = *param_5;
      }
      bVar3 = false;
    }
    else {
      if (uVar4 == 0x6f) {
        base = 8;
LAB_0802e49a:
        uVar11 = uVar12 & 0xfffffff3;
        if ((uVar12 & 0x400) != 0) {
LAB_0802e056:
          uVar11 = uVar11 & 0xfffffffe;
        }
        if ((uVar4 != 0x69) && (uVar4 != 100)) goto LAB_0802e068;
      }
      else {
        if (uVar4 == 0x62) {
          base = 2;
          goto LAB_0802e49a;
        }
        uVar11 = uStack_5c & 0xffffffef;
        if (uVar4 == 0x69) {
          base = 10;
          if ((uStack_5c & 0x400) == 0) goto LAB_0802e4be;
          goto LAB_0802e056;
        }
        base = 10;
        uVar12 = uVar11;
        if (uVar4 != 100) goto LAB_0802e49a;
        if ((uStack_5c & 0x400) != 0) goto LAB_0802e056;
      }
LAB_0802e4be:
      if ((uVar11 & 0x200) != 0) {
        value_00 = *param_5;
        bVar3 = SUB41(*(param_5 + 4) >> 0x1f,0);
        if (*(param_5 + 4) < 0) {
          value_00 = -*param_5;
        }
LAB_0802e576:
        pbVar5 = _ntoa_long_long(out,__maxlen,idx,__format,value_00,bVar3,ZEXT48(prec) << 0x20,prec_00,uVar11,in_stack_ffffff9c);
        __arg = __arg + 1;
        param_5 = param_5 + 1;
        goto LAB_0802dbfe;
      }
      if ((uVar11 & 0x100) != 0) {
        uVar4 = *param_5;
        uVar12 = uVar4 >> 0x1f;
        if (uVar4 < 0) {
          uVar4 = ~uVar4 + 1;
        }
        uVar21 = CONCAT44(uVar12,uVar4);
LAB_0802e5ce:
        pbVar5 = _ntoa_long(out,__maxlen,idx,__format,uVar21,SUB81(uVar21 >> 0x20,0),base,prec,prec_00,uVar11);
        __arg = __arg + 1;
        param_5 = param_5 + 4;
        goto LAB_0802dbfe;
      }
      if ((uVar11 & 0x40) == 0) {
        if ((uVar11 & 0x80) == 0) {
          value = *param_5;
          bVar3 = SUB41(value >> 0x1f,0);
        }
        else {
          value = *param_5;
          bVar3 = (*param_5 >> 0xf) >> 7;
        }
      }
      else {
        value = *param_5;
        bVar3 = false;
      }
      if (value < 0) {
        value = ~value + 1;
      }
    }
    pbVar5 = _ntoa_long(out,__maxlen,idx,__format,value,bVar3,base,prec,prec_00,uVar11);
    __arg = __arg + 1;
    param_5 = param_5 + 4;
    goto LAB_0802dbfe;
  case 0x3e:
    if ((uStack_5c & 2) == 0) {
      if (0x1 < prec_00) {
        pbVar9 = idx + -1;
        pbVar5 = idx;
        do {
          idx = pbVar5 + 1;
          (*(out & 0xfffffffe))(0x20,__maxlen,pbVar5,__format);
          pbVar5 = idx;
        } while (pbVar9 + prec_00 != idx);
      }
      bVar1 = *param_5;
      param_5 = param_5 + 4;
      (*(out & 0xfffffffe))(bVar1,__maxlen,idx,__format);
      __arg = __arg + 1;
      pbVar5 = idx + 1;
    }
    else {
      (*(out & 0xfffffffe))(*param_5,__maxlen,idx,__format);
      param_5 = param_5 + 4;
      pbVar5 = idx + 1;
      if (prec_00 < 0x2) {
        __arg = __arg + 1;
      }
      else {
        do {
          pbVar9 = pbVar5 + 1;
          (*(out & 0xfffffffe))(0x20,__maxlen,pbVar5,__format);
          pbVar5 = pbVar9;
        } while (prec_00 + idx != pbVar9);
        __arg = __arg + 1;
        pbVar5 = prec_00 + idx;
      }
    }
    goto LAB_0802dbfe;
  case 0x4b:
    pbVar5 = _ntoa_long(out,__maxlen,idx,__format,*param_5,false,0x10,prec,8,uStack_5c | 0x21);
    __arg = __arg + 1;
    param_5 = param_5 + 4;
    goto LAB_0802dbfe;
  case 0x4e:
    pcVar17 = *param_5;
    in_stack_ffffff9c = param_5 + 4;
    cVar2 = *pcVar17;
    pdVar10 = 0xffffffff;
    if (prec != 0x0) {
      pdVar10 = prec;
    }
    pcVar13 = pcVar17;
    if (cVar2 != '\0') {
      do {
        pcVar13 = pcVar13 + 1;
        if (*pcVar13 == '\0') break;
        pdVar10 = pdVar10 + -1;
      } while (pdVar10 != 0x0);
    }
    pdVar14 = pcVar13 + -pcVar17;
    if ((uStack_5c & 0x400) != 0) {
      pdVar14 = (pdVar14 < prec) * pdVar10 + (pdVar14 >= prec) * prec;
    }
    if ((uStack_5c & 2) == 0) {
      if (pdVar14 < prec_00) {
        pbVar9 = prec_00 + idx;
        pbVar5 = idx;
        do {
          idx = pbVar5 + 1;
          (*(out & 0xfffffffe))(0x20,__maxlen,pbVar5,__format);
          pbVar5 = idx;
        } while (pbVar9 + -pdVar14 != idx);
        cVar2 = *pcVar17;
        pdVar14 = prec_00;
      }
      pbVar5 = idx;
      pdVar14 = pdVar14 + 1;
      if (cVar2 != '\0') {
LAB_0802df4e:
        do {
          uStack_58 = pdVar14;
          pdVar10 = prec;
          if (((uStack_5c & 0x400) != 0) && (pdVar10 = prec + -1, idx = pbVar5, prec == 0x0)) break;
          pcVar17 = pcVar17 + 1;
          idx = pbVar5 + 1;
          (*(out & 0xfffffffe))(cVar2,__maxlen,pbVar5,__format);
          cVar2 = *pcVar17;
          pbVar5 = idx;
          prec = pdVar10;
          pdVar14 = uStack_58;
        } while (cVar2 != '\0');
        pdVar14 = uStack_58;
        if ((uStack_5c & 2) != 0) goto LAB_0802df7a;
      }
    }
    else {
      pbVar5 = idx;
      if (cVar2 != '\0') goto LAB_0802df4e;
LAB_0802df7a:
      if (pdVar14 < prec_00) {
        pbVar9 = prec_00 + idx;
        pbVar5 = idx;
        do {
          idx = pbVar5 + 1;
          (*(out & 0xfffffffe))(0x20,__maxlen,pbVar5,__format);
          pbVar5 = idx;
        } while (pbVar9 + -pdVar14 != idx);
      }
    }
    __arg = __arg + 1;
    param_5 = in_stack_ffffff9c;
    pbVar5 = idx;
    goto LAB_0802dbfe;
  case 0x51:
    uVar4 = 0;
    uVar11 = *param_5;
    uVar12 = 0;
    iVar18 = 4;
    do {
      uVar8 = uVar11 >> (uVar4 & 0x3f) & 0xff;
      if (uVar8 / 100 == 0) {
        uVar6 = (uVar8 % 100) / 10;
        cVar2 = uVar6;
        uVar15 = uVar12;
        if (uVar6 != 0) goto LAB_0802e3c4;
      }
      else {
        uVar6 = (uVar8 % 100) / 10;
        cVar2 = uVar6;
        uVar15 = uVar12 + 1 & 0xff;
        local_54[uVar12] = uVar8 / 100 + '0';
        if (uVar6 == 0) {
          uVar12 = uVar12 + 2 & 0xff;
          local_54[uVar15] = '0';
        }
        else {
LAB_0802e3c4:
          uVar12 = uVar15 + 1 & 0xff;
          local_54[uVar15] = cVar2 + '0';
        }
      }
      uVar15 = uVar12 + 1;
      local_54[uVar12] = (uVar8 % 100) % 10 + '0';
      uVar12 = uVar12 + 2 & 0xff;
      local_54[uVar15 & 0xff] = '.';
      uVar4 = uVar4 + 8;
      iVar18 = iVar18 + -1;
    } while (iVar18 != 0);
    local_54[uVar12 - 1] = '\0';
    in_stack_ffffff9c = uVar12 - 1;
    if ((uStack_5c & 0x400) != 0) {
      in_stack_ffffff9c = (in_stack_ffffff9c < prec) * in_stack_ffffff9c + (in_stack_ffffff9c >= prec) * prec;
    }
    uStack_58 = uStack_5c & 2;
    if (uStack_58 == 0x0) {
      pdVar10 = in_stack_ffffff9c;
      if (in_stack_ffffff9c < prec_00) {
        pbVar9 = prec_00 + idx;
        pbVar5 = idx;
        do {
          idx = pbVar5 + 1;
          (*(out & 0xfffffffe))(0x20,__maxlen,pbVar5,__format);
          pbVar5 = idx;
          pdVar10 = prec_00;
        } while (pbVar9 + -in_stack_ffffff9c != idx);
      }
      in_stack_ffffff9c = pdVar10 + 1;
      if (local_54[0] == '\0') break;
LAB_0802de5c:
      pcVar17 = local_54;
      cVar2 = local_54[0];
      do {
        pdVar10 = prec;
        if (((uStack_5c & 0x400) != 0) && (pdVar10 = prec + -1, prec == 0x0)) break;
        pcVar17 = pcVar17 + 1;
        pbVar5 = idx + 1;
        (*(out & 0xfffffffe))(cVar2,__maxlen,idx,__format);
        cVar2 = *pcVar17;
        idx = pbVar5;
        prec = pdVar10;
      } while (cVar2 != '\0');
      if (uStack_58 == 0x0) goto LAB_0802e3d8;
    }
    else if (local_54[0] != '\0') goto LAB_0802de5c;
    if (prec_00 <= in_stack_ffffff9c) goto LAB_0802e3d8;
    pbVar9 = prec_00 + idx;
    iVar18 = -in_stack_ffffff9c;
    pbVar5 = idx;
    do {
      idx = pbVar5 + 1;
      (*(out & 0xfffffffe))(0x20,__maxlen,pbVar5,__format);
      pbVar5 = idx;
    } while (pbVar9 + iVar18 != idx);
  }
  pdStack_60 = param_5 + 4;
  __arg = __arg + 1;
  param_5 = pdStack_60;
  pbVar5 = idx;
  goto LAB_0802dbfe;
}




int fputc(int __c,FILE *__stream)

{
  uint uVar1;
  
  do {
    uVar1 = peripheral_uart0_fifo_status;
  } while (0x1f < (uVar1 & 0x3f));
  peripheral_uart0_tx_data_window = __c & 0xff;
  return 0;
}




int wm_printf(char *str,char *format,...)

{
  size_t in_r0;
  int iVar1;
  undefined4 in_r1;
  undefined4 in_r2;
  undefined4 in_r3;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_c = in_r1;
  uStack_8 = in_r2;
  uStack_4 = in_r3;
  iVar1 = _vsnprintf(_out_uart,str,0xffffffff,str,&uStack_c);
  return iVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked


void vTaskSwitchContext(void)

{
  UBaseType_t UVar1;
  xLIST_ITEM *pxVar2;
  UBaseType_t iVar3;
  char *unaff_retaddr;
  
  if (uxSchedulerSuspended != 0) {
    xYieldPending = 1;
    return;
  }
  xYieldPending = 0;
  UVar1 = pxReadyTasksLists[uxTopReadyPriority].uxNumberOfItems;
  iVar3 = uxTopReadyPriority;
  while( true ) {
    if (UVar1 != 0) {
      pxVar2 = (pxReadyTasksLists[iVar3].pxIndex)->pxNext;
      pxReadyTasksLists[iVar3].pxIndex = pxVar2;
      if (pxVar2 == iVar3 * 0x14 + 0x2000a28c) {
        pxVar2 = pxVar2->pxNext;
        pxReadyTasksLists[iVar3].pxIndex = pxVar2;
      }
      pxCurrentTCB = pxVar2->pvOwner;
      uxTopReadyPriority = iVar3;
      return;
    }
    if (iVar3 == 0) break;
    iVar3 = iVar3 - 1;
    UVar1 = pxReadyTasksLists[iVar3].uxNumberOfItems;
  }
  wm_printf("Assert : %s %d\r\n",unaff_retaddr,"../../../../../../../platform/component/FreeRTOS/tasks.c",0xbe7,0);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}


