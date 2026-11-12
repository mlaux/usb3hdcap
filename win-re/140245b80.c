
void FUN_140245b80(undefined8 param_1,undefined8 param_2,uint *param_3)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  uint uVar8;
  ushort uVar9;
  ulonglong uVar10;
  undefined uVar11;
  undefined auStack_548 [32];
  undefined8 local_528;
  undefined8 local_520;
  uint local_518;
  undefined8 local_510;
  undefined8 local_508;
  undefined8 local_500;
  undefined4 local_4f8;
  longlong local_4e8;
  undefined4 local_4e0;
  short local_4d8;
  short local_4d6;
  undefined *local_4d0;
  undefined local_4c8 [16];
  undefined4 local_4b8 [2];
  undefined8 local_4b0;
  short *local_4a8;
  undefined4 local_4a0;
  undefined local_498 [16];
  undefined local_488 [16];
  undefined local_478 [8];
  uint local_470;
  char local_463;
  undefined8 local_460;
  undefined2 local_458;
  undefined local_448 [256];
  undefined local_348 [256];
  undefined local_248 [528];
  ulonglong local_38;
  
  local_38 = DAT_14035a610 ^ (ulonglong)auStack_548;
  uVar6 = KsGetFilterFromIrp();
  lVar7 = KsGetDevice(uVar6);
  lVar7 = *(longlong *)(lVar7 + 0x10);
  local_4e8 = 0;
  *(uint *)(lVar7 + 0x1c3bc) = *param_3 & 0xfff00cff;
  cVar2 = FUN_140227010(lVar7);
  if (cVar2 == '\0') goto LAB_140246030;
  uVar3 = *param_3 & 0xf;
  if (uVar3 == 0) {
    uVar11 = 0xa4;
  }
  else if (uVar3 == 1) {
    uVar11 = 0xa2;
  }
  else {
    if (uVar3 != 2) {
      *(uint *)(lVar7 + 0x1c3bc) = *(uint *)(lVar7 + 0x1c3bc) | 0x1300;
      goto LAB_140246030;
    }
    uVar11 = 0xa8;
  }
  local_460 = 0x5c003f003f005c;
  local_458 = 0;
  FUN_140259530(local_248,0x208,&local_460);
  uVar10 = 0xffffffffffffffff;
  do {
    uVar10 = uVar10 + 1;
    uVar9 = 0;
  } while (*(short *)((longlong)&local_460 + uVar10 * 2) != 0);
  RtlInitAnsiString(local_488,lVar7 + 0x1c378);
  local_4d8 = 0;
  local_4d6 = (short)uVar10 * -2 + 0x208;
  local_4d0 = local_248 + (uVar10 & 0xffff) * 2;
  RtlAnsiStringToUnicodeString(&local_4d8,local_488,0);
  local_4d8 = local_4d8 + (short)uVar10 * 2;
  local_4d0 = local_248;
  local_4a8 = &local_4d8;
  local_4b8[0] = 0x30;
  uVar3 = 0x100;
  local_4b0 = 0;
  local_4a0 = 0x40;
  local_498 = ZEXT816(0);
  if (((byte)*param_3 & 0xf) == 2) {
    uVar3 = 0x80;
  }
  FUN_14022e8dc(lVar7);
  uVar4 = FUN_1402271a8(lVar7);
  uVar8 = *param_3 & 0xf;
  local_4e0 = uVar4;
  if (((uVar8 == 0) || (uVar8 == 1)) || (uVar8 == 2)) {
    FUN_14022722c(lVar7);
  }
  FUN_140001220(5);
  if ((*param_3 & 0xf0) == 0) {
    local_4f8 = 0;
    local_500 = 0;
    local_508 = CONCAT44(local_508._4_4_,0x20);
    local_510 = CONCAT44(local_510._4_4_,1);
    local_518 = 1;
    local_520 = (undefined *)CONCAT44(local_520._4_4_,0x80);
    local_528 = (undefined *)0x0;
    uVar8 = ZwCreateFile(&local_4e8,1,local_4b8,local_4c8);
    if ((uVar8 & 0xc0000000) != 0xc0000000) {
      local_528 = (undefined *)CONCAT44(local_528._4_4_,5);
      ZwQueryInformationFile(local_4e8,local_4c8,local_478,0x18);
      if (local_463 != '\x01') {
        if (local_470 == uVar3) {
          local_508 = 0;
          local_510 = 0;
          local_520 = local_348;
          local_528 = local_4c8;
          local_518 = uVar3;
          uVar8 = ZwReadFile(local_4e8,0,0,0);
          if ((uVar8 & 0xc0000000) != 0xc0000000) {
            iVar5 = 1;
            do {
              local_528 = (undefined *)CONCAT44(local_528._4_4_,iVar5);
              cVar2 = i2c_write(lVar7,uVar11,(char)uVar9,local_348 + uVar9);
              if (cVar2 == '\0') {
                *(uint *)(lVar7 + 0x1c3bc) = *(uint *)(lVar7 + 0x1c3bc) | 0x5300;
                uVar4 = local_4e0;
                goto LAB_140245ffa;
              }
              iVar1 = 5;
              do {
                do {
                  iVar5 = iVar1;
                  local_528 = (undefined *)CONCAT44(local_528._4_4_,1);
                  cVar2 = FUN_140228198(lVar7,uVar11,(char)uVar9,local_448 + uVar9);
                  iVar1 = iVar5;
                } while (cVar2 == '\0');
                iVar1 = iVar5 + -1;
              } while (iVar5 + -1 != 0);
              uVar9 = uVar9 + (short)iVar5;
              uVar4 = local_4e0;
            } while (uVar9 < (ushort)uVar3);
            goto LAB_140245eac;
          }
          *(uint *)(lVar7 + 0x1c3bc) = *(uint *)(lVar7 + 0x1c3bc) | 0x3300;
        }
        else {
          *(uint *)(lVar7 + 0x1c3bc) = *(uint *)(lVar7 + 0x1c3bc) | 0x4300;
        }
        goto LAB_140245ffa;
      }
    }
    *(uint *)(lVar7 + 0x1c3bc) = *(uint *)(lVar7 + 0x1c3bc) | 0x2300;
  }
  else {
LAB_140245eac:
    memset(local_448,0,0x100);
    uVar9 = 0;
    do {
      local_528 = (undefined *)CONCAT44(local_528._4_4_,1);
      cVar2 = FUN_140228198(lVar7,uVar11,(char)uVar9,local_448 + uVar9);
      if (cVar2 == '\0') {
        *(uint *)(lVar7 + 0x1c3bc) = *(uint *)(lVar7 + 0x1c3bc) | 0x6300;
        goto LAB_140245ffa;
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < (ushort)uVar3);
    if ((*param_3 & 0xf0) == 0) {
      iVar5 = memcmp(local_348,local_448,(ulonglong)uVar3);
      if (iVar5 == 0) {
LAB_140245fe6:
        *(uint *)(lVar7 + 0x1c3bc) = *(uint *)(lVar7 + 0x1c3bc) | 0x100;
      }
      else {
        *(uint *)(lVar7 + 0x1c3bc) = *(uint *)(lVar7 + 0x1c3bc) | 0x7300;
      }
    }
    else {
      if ((*param_3 & 0xf0) != 0x10) goto LAB_140245fe6;
      local_4f8 = 0;
      local_500 = 0;
      local_508 = CONCAT44(local_508._4_4_,0x20);
      local_510 = local_510 & 0xffffffff00000000;
      local_518 = 1;
      local_520 = (undefined *)CONCAT44(local_520._4_4_,0x80);
      local_528 = (undefined *)0x0;
      uVar8 = ZwCreateFile(&local_4e8,2,local_4b8,local_4c8);
      if ((uVar8 & 0xc0000000) == 0xc0000000) {
        *(uint *)(lVar7 + 0x1c3bc) = *(uint *)(lVar7 + 0x1c3bc) | 0x9300;
      }
      else {
        local_508 = 0;
        local_510 = 0;
        local_528 = local_4c8;
        local_520 = local_448;
        local_518 = uVar3;
        uVar3 = ZwWriteFile(local_4e8,0,0,0);
        if ((uVar3 & 0xc0000000) != 0xc0000000) goto LAB_140245fe6;
        *(uint *)(lVar7 + 0x1c3bc) = *(uint *)(lVar7 + 0x1c3bc) | 0x8300;
      }
    }
  }
LAB_140245ffa:
  FUN_140001220(5);
  FUN_14022710c(lVar7,uVar4);
  if (local_4e8 != 0) {
    ZwClose();
  }
  FUN_140001220(5);
  make_signal_monitoring_thread(lVar7);
LAB_140246030:
  __security_check_cookie(local_38 ^ (ulonglong)auStack_548);
  return;
}


