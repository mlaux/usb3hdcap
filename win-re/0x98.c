void FUN_14022710c(undefined8 param_1,undefined4 param_2)

{
  undefined local_res10 [24];
  
  local_res10[0] = (undefined)param_2;
  i2c_write(param_1,0x98,0,local_res10,1);
  local_res10[0] = (undefined)((uint)param_2 >> 8);
  i2c_write(param_1,0x98,1,local_res10,1);
  local_res10[0] = (undefined)((uint)param_2 >> 0x10);
  i2c_write(param_1,0x98,0x10,local_res10,1);
  local_res10[0] = (undefined)((uint)param_2 >> 0x18);
  i2c_write(param_1,0x98,0x11,local_res10,1);
  return;
}

undefined FUN_14022722c(undefined8 param_1,ushort param_2)

{
  byte bVar1;
  byte bVar2;
  undefined uVar3;
  undefined uVar4;
  uint uVar5;
  byte local_res10 [8];

  bVar1 = (byte)param_2 >> 3;
  if (bVar1 == 0) {
    uVar4 = 0;
    uVar3 = 0x10;
  }
  else {
    if (bVar1 != 1) {
      return 0;
    }
    uVar4 = 1;
    uVar3 = 0x11;
  }
  bVar1 = i2c_read(param_1,0x98,uVar4,0);
  bVar2 = i2c_read(param_1,0x98,uVar3,0);
  uVar5 = (byte)param_2 & 7;
  if ((param_2 >> 8 & 1) == 0) {
    local_res10[0] = bVar1 & ~(byte)(1 << uVar5);
  }
  else {
    local_res10[0] = bVar1 | (byte)(1 << uVar5);
  }
  if ((short)param_2 < 0) {
    bVar2 = bVar2 | (byte)(1 << uVar5);
  }
  else {
    bVar2 = bVar2 & ~(byte)(1 << uVar5);
  }
  i2c_write(param_1,0x98,uVar4,local_res10,1);
  local_res10[0] = bVar2;
  i2c_write(param_1,0x98,uVar3,local_res10,1);
  return 1;
}

void FUN_140227f1c(longlong param_1)

{
  longlong lVar1;
  ushort uVar2;
  byte local_res8 [8];

  FUN_14022b780();
  FUN_140227cf8(param_1,0,0,10);
  FUN_140227cf8(param_1,0x24,4,10);
  FUN_140227cf8(param_1,9,0x2c83,10);
  uVar2 = FUN_140227a80(param_1,0x200,10);
  FUN_140227cf8(param_1,0x200,uVar2 & 0xfaff | 0xa00,10);
  uVar2 = FUN_140227a80(param_1,0x408,10);
  FUN_140227cf8(param_1,0x408,uVar2 & 0xff | 0xaa00,10);
  local_res8[0] = i2c_read(param_1,0x98,0x20,0);
  local_res8[0] = local_res8[0] | 10;
  i2c_write(param_1,0x98,0x20,local_res8,1);
  lVar1 = *(longlong *)(param_1 + 0x1c528);
  *(undefined8 *)(lVar1 + 0x30) = 0;
  *(undefined8 *)(lVar1 + 0x38) = 0;
  *(undefined8 *)(lVar1 + 0x58) = 0;
  *(undefined4 *)(lVar1 + 0x60) = 0;
  *(undefined8 *)(lVar1 + 0x40) = 0;
  *(undefined4 *)(lVar1 + 0x48) = 0;
  *(undefined4 *)(lVar1 + 0x1cd4) = 0;
  *(undefined4 *)(lVar1 + 0x1cdc) = 0;
  return;
}

void FUN_14022b780(longlong param_1)

{
  short sVar1;
  longlong lVar2;
  char cVar3;
  ushort uVar4;
  uint uVar5;
  char local_res8 [8];

  lVar2 = *(longlong *)(param_1 + 0x1c528);
  *(undefined4 *)(lVar2 + 0x30dd4) = 0x1000;
  *(undefined2 *)(lVar2 + 0x1f94) = 0;
  *(undefined *)(lVar2 + 0x1f74) = 0;
  lVar2 = *(longlong *)(param_1 + 0x120);
  sVar1 = *(short *)(lVar2 + 8);
  if (((((sVar1 != 0x4bb) || ((*(ushort *)(lVar2 + 10) & 0xfff) != 0x543)) &&
       ((sVar1 != 0xfd9 ||
        ((uVar4 = *(short *)(lVar2 + 10) - 0x4f, 0x27 < uVar4 ||
         ((0xa000008001U >> ((ulonglong)uVar4 & 0x3f) & 1) == 0)))))) &&
      ((sVar1 != 0x17ef || (*(short *)(lVar2 + 10) != 0x7219)))) &&
     ((sVar1 != 0x1164 || (3 < (ushort)((*(ushort *)(lVar2 + 10) & 0xfff) - 0x535))))) {
    FUN_14022e3f4(param_1,0x402d);
    FUN_14022e3f4(param_1,0x12d);
    FUN_140001220(0x32);
    FUN_14022e3f4(param_1,0x2d);
    FUN_140001220(0x32);
    FUN_14022e3f4(param_1,0x12d);
    FUN_140001220(0x32);
    FUN_14022e3f4(param_1,0x802d);
    send_mst(param_1,0,0x51,0x80);
    FUN_14022eef8(param_1);
    FUN_140228034(param_1);
    cVar3 = FUN_14022bb68(param_1);
    if (cVar3 != '\0') {
      CheckIsMCUExist(param_1);
    }
  }
  cVar3 = i2c_read(param_1,0x98,0x3b,0);
  if (cVar3 != '\0') {
    uVar5 = *(uint *)(param_1 + 0x6840);
    if ((uVar5 == 2) || (uVar5 == 3)) {
      local_res8[0] = -0x80;
      i2c_write(param_1,0x98,0x3b,local_res8,1);
      uVar5 = *(uint *)(param_1 + 0x6840);
    }
    if (uVar5 < 2) {
      local_res8[0] = '\x02';
      i2c_write(param_1,0x98,0x3b,local_res8,1);
    }
  }
  local_res8[0] = '\x05';
  i2c_write(param_1,0x98,0x20,local_res8,1);
  cVar3 = FUN_140226fc4(param_1);
  local_res8[0] = '\x01';
  i2c_write(param_1,0x98,0,local_res8,1);
  local_res8[0] = (-(cVar3 != '\0') & 0xfeU) - 2;
  i2c_write(param_1,0x98,0x10,local_res8,1);
  return;
}


void signal_monitoring_thread(longlong param_1)

{
  longlong lVar1;
  longlong lVar2;
  undefined uVar3;
  char cVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  ushort uVar8;
  ushort uVar9;
  short sVar10;
  short sVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  undefined4 uVar15;
  uint uVar16;
  uint *puVar17;
  int iVar18;
  uint uVar19;
  ulonglong uVar20;
  uint uVar21;
  int iVar22;
  ulonglong uVar24;
  ulonglong uVar25;
  ulonglong uVar26;
  int iVar27;
  uint uVar28;
  undefined8 uVar29;
  undefined4 uVar30;
  undefined4 uVar31;
  uint uVar32;
  ushort uVar33;
  undefined2 local_res8;
  int local_res10;
  uint local_res18;
  uint local_res20;
  int local_58;
  uint local_54;
  uint local_50;
  ulonglong uVar23;

  KeSetPriorityThread(SystemReserved1[0xf],0x10);
  lVar1 = *(longlong *)(param_1 + 0x1c528);
  uVar26 = 0;
  local_58 = 0;
  local_50 = 0;
  local_54 = 0;
  FUN_14022bae8(param_1);
  cVar4 = *(char *)(param_1 + 0x6ab0);
  uVar20 = uVar26;
  uVar25 = uVar26;
  do {
    if (cVar4 != '\0') {
      FUN_1402275e0(param_1);
                    /* WARNING: Could not recover jumptable at 0x00014022d10c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      PsTerminateSystemThread(0);
      return;
    }
    uVar24 = 0;
    iVar27 = 0;
    iVar12 = 0;
    iVar18 = 0;
    uVar14 = (uint)uVar25;
    uVar23 = uVar24;
    do {
      if (*(char *)(param_1 + 0x6ab0) != '\0') break;
      FUN_140001220(10);
      uVar21 = (int)uVar23 + 1;
      uVar23 = (ulonglong)uVar21;
    } while (uVar21 < 10);
    uVar21 = (int)uVar26 + 1;
    uVar26 = (ulonglong)uVar21;
    if (uVar21 != 0) {
      local_res18 = 0;
      if (((*(uint *)(param_1 + 0x1c374) & 0x1000000) != 0) &&
         (local_50 = (int)uVar20 + 1, local_50 == 10)) {
        local_50 = 0;
        uVar3 = i2c_read(param_1,0x98,0,0);
        local_res8 = CONCAT11(local_res8._1_1_,uVar3) ^ 1;
        i2c_write(param_1,0x98,0,&local_res8,1);
      }
      uVar26 = uVar24;
      if (*(int *)(param_1 + 0x1e5ec) == 0x12345678) {
        *(undefined8 *)(lVar1 + 0x1f60) = 0;
        *(undefined8 *)(lVar1 + 0x1f68) = 0;
        *(undefined4 *)(lVar1 + 0x1f70) = 5;
      }
      else {
        cVar4 = FUN_14022d468(param_1,0x32);
        if (cVar4 == '\0') {
          iVar22 = *(int *)(param_1 + 0x6840);
          if (iVar22 == 4) {
            uVar8 = FUN_140227a80(param_1,6,10);
            uVar33 = uVar8 >> 8 & 0x3f;
            local_res8 = FUN_140227a80(param_1,0x1f,10);
            local_res8 = local_res8 & 0x3fff;
            uVar8 = FUN_140227a80(param_1,0x21,10);
            uVar8 = uVar8 & 0x7ff;
            uVar9 = FUN_140227a80(param_1,0x22,10);
            local_res10 = 0;
            local_res20 = (uint)(uVar9 >> 0xe);
            uVar14 = uVar9 >> 0xd & 1;
            if (uVar33 == 0x16 || uVar33 == 0x17) {
              iVar18 = 0x2d0;
              uVar24 = 0xf0;
              iVar12 = 0x3c;
            }
            if ((uVar33 - 0x19 & 0xfffd) == 0) {
              iVar18 = 0x2d0;
              uVar24 = 0xf0;
              iVar12 = 0x3c;
            }
            if ((uVar33 - 0x18 & 0xfffd) == 0) {
              iVar18 = 0x2d0;
              iVar12 = 0x32;
              uVar24 = 0x120;
            }
            if (uVar33 == 0x1e) {
              if (uVar8 == 0x271) {
                iVar18 = 0x2d0;
                uVar24 = 0x120;
                uVar14 = 0;
LAB_14022c5bd:
                iVar12 = 0x32;
                goto LAB_14022c5dc;
              }
              uVar21 = 0;
              if (uVar8 != 0x271) {
                uVar21 = uVar14;
              }
              uVar14 = uVar21;
              if (uVar8 == 0x20d) {
                iVar18 = 0x2d0;
                uVar24 = 0xf0;
                iVar12 = 0x3c;
                uVar14 = 1;
                goto LAB_14022c294;
              }
LAB_14022c5c4:
              local_res10 = iVar27;
              if ((iVar18 != 0) && (iVar27 = local_res10, (int)uVar24 != 0)) goto LAB_14022c5dc;
              uVar31 = 0;
              *(undefined8 *)(lVar1 + 0x30) = 0;
              uVar30 = 0;
              *(undefined8 *)(lVar1 + 0x38) = 0;
              *(undefined8 *)(lVar1 + 0x40) = 0;
              *(undefined8 *)(lVar1 + 0x58) = 0;
              *(undefined4 *)(lVar1 + 0x60) = 0;
              *(undefined4 *)(lVar1 + 0x1cdc) = 0;
              *(undefined8 *)(param_1 + 0x75dc) = 0;
              uVar15 = uVar31;
            }
            else {
              if (uVar33 == 0x20) {
                uVar24 = 0x2d0;
                iVar18 = 0x500;
                iVar12 = 0x3c;
LAB_14022c294:
                if (((uVar33 - 4 & 0xffdf) == 0) &&
                   ((local_res8 == 0x500 ||
                    (((*(int *)(lVar1 + 0x30) == 0x500 && (*(int *)(lVar1 + 0x34) == 0x2d0)) &&
                     (*(int *)(lVar1 + 0x38) == 0x32)))))) {
                  iVar12 = 0x32;
                  uVar24 = 0x2d0;
                  iVar18 = 0x500;
                }
                if ((uVar33 - 2 & 0xffdf) == 0) {
                  iVar18 = 0x500;
                  uVar24 = 0x2d0;
                  iVar12 = 0x1e;
                }
                if ((uVar33 - 6 & 0xffdf) == 0) {
                  iVar18 = 0x500;
                  uVar24 = 0x2d0;
                  iVar12 = 0x19;
                }
                if ((uVar33 - 8 & 0xffdf) == 0) {
                  iVar18 = 0x500;
                  uVar24 = 0x2d0;
                  iVar12 = 0x18;
                }
                if ((uVar33 - 10 & 0xffdf) == 0) {
                  sVar10 = FUN_140227a80(param_1,0x19,10);
                  sVar11 = FUN_140227a80(param_1,0x1a,10);
                  if ((*(int *)(param_1 + 0x8cd8) != 0) || (*(int *)(param_1 + 0x8cdc) != 0)) {
                    iVar12 = 0x3c;
                    iVar18 = 0x780;
                    uVar24 = 0x21c;
                    goto LAB_14022c454;
                  }
                  if (((sVar10 == 0) && (sVar11 == 0)) && (local_res20 == 2)) {
                    iVar27 = 1;
                    uVar24 = 0x438;
                    local_res10 = 1;
                  }
                  else {
                    uVar24 = 0x21c;
                    local_res10 = 0;
                    iVar27 = 0;
                  }
                  iVar12 = 0x3c;
                  iVar18 = 0x780;
                }
                else {
LAB_14022c454:
                  local_res10 = 0;
                  iVar27 = 0;
                }
                uVar21 = local_res20;
                if ((uVar33 - 0xc & 0xffdf) == 0) {
                  sVar10 = FUN_140227a80(param_1,0x19,10);
                  sVar11 = FUN_140227a80(param_1,0x1a,10);
                  if (((*(int *)(param_1 + 0x8cd8) == 0) && (*(int *)(param_1 + 0x8cdc) == 0)) &&
                     ((sVar10 == 0 && ((sVar11 == 0 && (uVar21 == 2)))))) {
                    iVar27 = 1;
                    iVar18 = 0x780;
                    local_res10 = 1;
                    uVar24 = 0x438;
                    iVar12 = 0x32;
                  }
                  else {
                    local_res10 = 0;
                    iVar18 = 0x780;
                    uVar24 = 0x21c;
                    iVar12 = 0x32;
                    iVar27 = 0;
                  }
                }
                if (uVar33 != 0x11) {
                  if ((uVar33 == 0x2b) || (uVar33 == 0xb)) {
                    iVar18 = 0x780;
                    uVar24 = 0x438;
                    iVar12 = 0x1e;
                  }
                  if ((uVar33 == 0x2d) || (uVar33 == 0xd)) {
                    iVar18 = 0x780;
                    uVar24 = 0x438;
                    iVar12 = 0x19;
                  }
                  if ((uVar33 == 0x30) || (uVar33 == 0x10)) {
                    iVar18 = 0x780;
                    uVar24 = 0x438;
                    iVar12 = 0x18;
                  }
                  uVar21 = (uint)uVar24;
                  if (uVar33 == 0x2b) {
                    if (local_res8 == 0x780) {
                      iVar18 = 0x780;
                      uVar24 = 0x438;
                      goto LAB_14022c3e3;
                    }
                  }
                  else {
LAB_14022c59c:
                    uVar24 = (ulonglong)uVar21;
                    if ((uVar33 == 0x2d) && (local_res8 == 0x780)) {
                      iVar18 = 0x780;
                      uVar24 = 0x438;
                      goto LAB_14022c5bd;
                    }
                  }
                  goto LAB_14022c5c4;
                }
                iVar18 = 0x780;
                uVar24 = 0x21c;
                iVar12 = 0x30;
              }
              else {
                if (uVar33 != 0) goto LAB_14022c294;
                if (local_res8 != 0x500) {
                  if (((*(int *)(lVar1 + 0x30) != 0x500) ||
                      (iVar27 = 0, *(int *)(lVar1 + 0x34) != 0x2d0)) ||
                     (*(int *)(lVar1 + 0x38) != 0x3c)) goto LAB_14022c5c4;
                  iVar12 = 0x3c;
                  uVar21 = 0x2d0;
                  iVar18 = 0x500;
                  iVar27 = 0;
                  goto LAB_14022c59c;
                }
                iVar18 = 0x500;
                uVar24 = 0x2d0;
LAB_14022c3e3:
                iVar12 = 0x3c;
              }
LAB_14022c5dc:
              iVar22 = (int)uVar24;
              if ((*(int *)(lVar1 + 0x30) != iVar18) ||
                 ((((*(int *)(lVar1 + 0x34) != iVar22 || (*(int *)(lVar1 + 0x38) != iVar12)) ||
                   (*(uint *)(lVar1 + 0x3c) != uVar14)) || (*(int *)(lVar1 + 0x44) != iVar27)))) {
                FUN_140227cf8(param_1,1,~-(ushort)(iVar27 != 0) & 0x100,10);
                *(int *)(lVar1 + 0x30) = iVar18;
                *(int *)(lVar1 + 0x34) = iVar22;
                *(int *)(lVar1 + 0x38) = iVar12;
                *(uint *)(lVar1 + 0x3c) = uVar14;
                *(int *)(lVar1 + 0x44) = local_res10;
                if (((iVar22 == 0xf0) || (iVar22 == 0x120)) || (iVar22 == 0x21c)) {
                  uVar31 = 1;
                }
                else {
                  uVar31 = 0;
                }
                *(undefined4 *)(lVar1 + 0x40) = uVar31;
                *(undefined4 *)(lVar1 + 0x1cd4) = 1;
                *(undefined4 *)(lVar1 + 0x1cdc) = 48000;
                *(undefined4 *)(lVar1 + 0x5c) = 1;
                *(uint *)(lVar1 + 0x58) = (iVar18 != 0x2d0) + 1;
                *(undefined4 *)(lVar1 + 0x60) = 1;
                bVar5 = i2c_read(param_1,0x98,0x20,0);
                if ((iVar22 == 0xf0) || (iVar22 == 0x120)) {
                  bVar5 = bVar5 | 0x40;
                }
                else {
                  bVar5 = bVar5 & 0xbf;
                }
                local_res8 = CONCAT11(local_res8._1_1_,bVar5);
                i2c_write(param_1,0x98,0x20,&local_res8,1);
              }
              uVar30 = 1;
              DbgPrint(&DAT_140260d30,*(undefined4 *)(param_1 + 0x1e5a8),iVar18,uVar24,iVar12);
              *(uint *)(param_1 + 0x75dc) = *(int *)(lVar1 + 0x30) << 0x10 | *(uint *)(lVar1 + 0x34)
              ;
              uVar31 = uVar30;
              if ((*(uint *)(lVar1 + 0x38) < 0x33) && (4 < *(uint *)(lVar1 + 0x38) - 0x1a)) {
                uVar31 = 0x10;
              }
              *(undefined4 *)(param_1 + 0x6714) = uVar31;
              *(undefined4 *)(param_1 + 0x75e0) = *(undefined4 *)(lVar1 + 0x38);
              uVar31 = *(undefined4 *)(lVar1 + 0x40);
              uVar15 = 48000;
            }
            *(undefined4 *)(param_1 + 0x75e4) = uVar31;
            *(undefined4 *)(param_1 + 0x7a10) = uVar15;
            *(undefined4 *)(param_1 + 0x67f4) = 0;
            *(undefined4 *)(param_1 + 0x6758) = uVar30;
            uVar14 = local_54;
          }
          else if (iVar22 == 5 || iVar22 == 6) {
            FUN_14022e9bc(param_1);
            if (*(int *)(param_1 + 0x6758) == 1) {
              bVar5 = i2c_read(param_1,0x88,0x30);
              bVar5 = bVar5 & 0xf;
              if ((bVar5 == 0xe) || (bVar5 == 6)) {
                uVar21 = 3;
              }
              else if ((bVar5 == 0xf) || (bVar5 == 7)) {
                uVar21 = 2;
              }
              else if (bVar5 == 0xc) {
                uVar21 = 1;
              }
              else {
                uVar21 = (uint)(bVar5 == 4);
              }
              *(uint *)(param_1 + 0x67f4) = uVar21;
              FUN_140001220(1);
              i2c_read(param_1,0x88,0x4f);
              cVar4 = i2c_read(param_1,0x88,0x53);
              bVar5 = i2c_read(param_1,0x88,0x54);
              if ((-1 < cVar4) && ((bVar5 & 0xc0) == 0xc0)) {
                *(undefined4 *)(param_1 + 0x6838) = 1;
                goto LAB_14022c9e3;
              }
            }
            else {
              *(undefined4 *)(param_1 + 0x67f4) = 0;
            }
            *(undefined4 *)(param_1 + 0x6838) = 0;
          }
          else if (*(int *)(lVar1 + 0x1f84) == 0) {
            FUN_14024b514();
            if (((*(uint *)(param_1 + 0x6840) < 2) && (*(int *)(param_1 + 0x6758) == 1)) &&
               (*(int *)(param_1 + 0x6854) == 0)) {
              bVar5 = read_mst(param_1,2,0xb);
              if (*(int *)(lVar1 + 0x1ce0) == 0) {
                if ((bVar5 & 0x60) != 0x60) {
                  if ((bVar5 & 0x40) != 0) {
                    FUN_140001220(2000);
                    bVar5 = read_mst(param_1,2,0xb);
                    if ((bVar5 & 0x60) == 0x60) {
                      DbgPrint("fix it to embedded R020B(0x%x)\n",bVar5);
                      goto LAB_14022c8ab;
                    }
                  }
                  *(undefined4 *)(lVar1 + 0x1ce0) = 1;
                  DbgPrint("[SET TO LINE IN] R020B(0x%x)\n",bVar5);
                  uVar29 = 1;
LAB_14022c86c:
                  tw9900_init_all(param_1,0xffffffff,0xffffffff,uVar29,0xffffffff,1);
                }
              }
              else if ((bVar5 & 0x40) != 0) {
                *(undefined4 *)(lVar1 + 0x1ce0) = 0;
                DbgPrint("[SET TO EMBEDDED] R020B(0x%x)\n",bVar5);
                uVar29 = 0;
                goto LAB_14022c86c;
              }
            }
LAB_14022c8ab:
            sVar10 = FUN_140249e14(param_1);
            DbgPrint("GetHDMIDotClock => Audio Sample Freq = %d\n",sVar10);
            if (sVar10 == -1) {
              read_mst(param_1,2,0x12);
              read_mst(param_1,2,0x11);
            }
            else if (1 < *(uint *)(param_1 + 0x6840)) goto LAB_14022c9e3;
            send_mst(param_1,2,0x20);
          }
          else {
            FUN_14022d6c8();
          }
LAB_14022c9e3:
          uVar21 = 1;
          uVar26 = 0;
          iVar27 = *(int *)(lVar1 + 0x1cd4);
          uVar32 = 0;
          *(undefined4 *)(lVar1 + 0x1cd4) = 0;
          if (iVar27 != 0) {
            *(undefined4 *)(lVar1 + 0x1ce8) = *(undefined4 *)(lVar1 + 0x30);
            uVar16 = *(uint *)(lVar1 + 0x38) >> 1;
            if (*(int *)(lVar1 + 0x40) == 0) {
              uVar16 = *(uint *)(lVar1 + 0x38);
            }
            *(uint *)(lVar1 + 0x1cf0) = uVar16;
            *(undefined4 *)(lVar1 + 0x1cec) = *(undefined4 *)(lVar1 + 0x34);
            *(int *)(lVar1 + 0x1cf4) = *(int *)(lVar1 + 0x3c);
            if (*(int *)(lVar1 + 0x3c) == 0) {
              uVar16 = uVar16 * 1000;
            }
            else {
              uVar16 = (uVar16 * 1000000) / 0x3e9;
            }
            *(uint *)(lVar1 + 0x1cf8) = uVar16;
            *(undefined8 *)(lVar1 + 0x1cfc) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d04) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d0c) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d14) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d1c) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d24) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d2c) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d34) = 0x6400000064;
            *(undefined4 *)(lVar1 + 0x1d3c) = *(undefined4 *)(lVar1 + 0x1cdc);
            *(undefined4 *)(lVar1 + 0x1d40) = *(undefined4 *)(lVar1 + 0x1cdc);
            *(undefined8 *)(lVar1 + 0x1d44) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d4c) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d54) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d5c) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d64) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d6c) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d74) = 0x6400000064;
            *(undefined8 *)(lVar1 + 0x1d7c) = 0x6400000064;
          }
          lVar2 = *(longlong *)(param_1 + 0x120);
          sVar10 = *(short *)(lVar2 + 8);
          if (sVar10 == 0x4bb) {
            if ((*(ushort *)(lVar2 + 10) & 0xfff) == 0x543) goto LAB_14022cb55;
LAB_14022caeb:
            if (sVar10 != 0x17ef) goto LAB_14022cb2d;
            if (*(short *)(lVar2 + 10) == 0x7219) goto LAB_14022cb55;
          }
          else {
            if (sVar10 != 0xfd9) goto LAB_14022caeb;
            uVar8 = *(short *)(lVar2 + 10) - 0x4f;
            if ((uVar8 < 0x26) && ((0x2000008001U >> ((ulonglong)uVar8 & 0x3f) & 1) != 0))
            goto LAB_14022cb55;
LAB_14022cb2d:
            if ((sVar10 == 0x1164) && ((ushort)((*(ushort *)(lVar2 + 10) & 0xfff) - 0x535) < 4)) {
LAB_14022cb55:
              uVar3 = FUN_140246588(*(undefined4 *)(param_1 + 0x6840),*(undefined4 *)(lVar1 + 0x30),
                                    *(undefined4 *)(lVar1 + 0x34));
              *(undefined *)(lVar1 + 0x1f58) = uVar3;
              if (*(int *)(param_1 + 0x6758) == 0) {
                uVar3 = 0x44;
              }
              else {
                if (iVar27 != 0) {
                  maybe_setup_hdmi(lVar1 + 0x1d88,0x44);
                }
                uVar3 = *(undefined *)(lVar1 + 0x1f58);
              }
              maybe_setup_hdmi(lVar1 + 0x1d88,uVar3);
            }
          }
          cVar4 = FUN_140226fc4(param_1);
          if (cVar4 != '\0') {
            bVar6 = i2c_read(param_1,0x98,0,0);
            bVar7 = i2c_read(param_1,0x98,0x20,0);
            bVar5 = bVar6 | 2;
            if ((bVar7 & 0x10) == 0) {
              bVar5 = bVar6 & 0xfd;
            }
            local_res8 = CONCAT11(local_res8._1_1_,bVar5);
            i2c_write(param_1,0x98,0,&local_res8,1);
          }
          lVar2 = *(longlong *)(param_1 + 0x120);
          sVar10 = *(short *)(lVar2 + 8);
          if (sVar10 == 0x4bb) {
            if ((*(ushort *)(lVar2 + 10) & 0xfff) != 0x543) {
LAB_14022cc45:
              if (sVar10 != 0x17ef) goto LAB_14022ccbd;
              if (*(short *)(lVar2 + 10) == 0x7219) goto LAB_14022cd83;
              goto LAB_14022cc63;
            }
          }
          else {
            if (sVar10 != 0xfd9) goto LAB_14022cc45;
            uVar8 = *(short *)(lVar2 + 10) - 0x4f;
            if ((uVar8 < 0x28) && ((0xa000008001U >> ((ulonglong)uVar8 & 0x3f) & 1) != 0))
            goto LAB_14022cd83;
LAB_14022ccbd:
            if ((sVar10 != 0x1164) || (3 < (ushort)((*(ushort *)(lVar2 + 10) & 0xfff) - 0x535))) {
LAB_14022cc63:
              cVar4 = FUN_14022bb68(param_1);
              if (cVar4 != '\0') {
                cVar4 = i2c_read(param_1,0x98,0xf0);
                if (cVar4 == 'T') {
                  local_58 = 0;
                }
                else {
                  local_58 = local_58 + 1;
                  if (local_58 == 3) {
                    local_58 = 0;
                    if ((*(ushort *)(*(longlong *)(param_1 + 0x120) + 10) & 0xfff) == 0x531) {
                      FUN_14022b780(param_1);
                    }
                    FUN_140247328(param_1);
                    CheckIsMCUExist(param_1);
                    if (((*(ushort *)(*(longlong *)(param_1 + 0x120) + 10) & 0xfff) == 0x531) &&
                       (*(char *)(param_1 + 0x63f0) == '\x01')) {
                      tw9900_init_all(param_1,*(undefined4 *)(param_1 + 0x6840),
                                      *(undefined4 *)(param_1 + 0x6850),
                                      *(undefined4 *)(param_1 + 0x6854),
                                      *(undefined4 *)(param_1 + 0x6858),1);
                    }
                  }
                }
              }
            }
          }
LAB_14022cd83:
          cVar4 = FUN_140227010(param_1);
          if (cVar4 != '\0') {
            local_res8 = local_res8 & 0xff00;
            bVar5 = i2c_read(param_1,0x98,0,&local_res8);
            uVar19 = bVar5 >> 4 & 1;
            uVar16 = uVar19 | 2;
            if ((bVar5 & 4) == 0) {
              uVar16 = uVar19;
            }
            uVar19 = uVar16 | 4;
            if ((bVar5 & 8) == 0) {
              uVar19 = uVar16;
            }
            uVar19 = -(uint)((char)local_res8 != '\0') & uVar19;
            bVar5 = (byte)uVar19 ^ (byte)*(undefined4 *)(param_1 + 0x7668);
            if ((bVar5 & 1) != 0) {
              DbgPrint("DP PLUG %d -> %d\n",~uVar19 & 1);
            }
            if ((bVar5 & 2) != 0) {
              DbgPrint("HDMI PLUG %d -> %d\n",~(uVar19 >> 1) & 1);
            }
            if ((bVar5 & 4) != 0) {
              DbgPrint("VGA PLUG %d -> %d\n",~(uVar19 >> 2) & 1);
            }
            *(uint *)(param_1 + 0x7668) = uVar19;
          }
          if (*(char *)(lVar1 + 0x1f74) == '\x01') {
            *(undefined *)(lVar1 + 0x1f74) = 2;
            DbgPrint("AUDIO OFF\n");
            uVar3 = i2c_read(param_1,0x98,0x20,0);
            local_res8 = CONCAT11(local_res8._1_1_,uVar3) & 0xfffb;
            i2c_write(param_1,0x98,0x20,&local_res8,1);
          }
          uVar25 = uVar26;
          if (*(int *)(param_1 + 0x6758) == 0) {
            uVar25 = (ulonglong)(uVar14 + 1);
          }
          local_54 = (uint)uVar25;
          if (*(int *)(param_1 + 0x6844) == 1) {
            uVar14 = *(uint *)(param_1 + 0x6840);
            uVar16 = *(uint *)(param_1 + 0x6848) / 100;
            if ((uVar14 == 3) && (*(int *)(lVar1 + 0x88) != 0)) {
              uVar16 = 0x50;
            }
            if (uVar16 < local_54) {
              local_54 = 0;
              uVar16 = (uVar14 + 1) % 7;
              if (uVar16 == 0) {
                uVar19 = 2;
              }
              else if (uVar16 == 1) {
                uVar19 = 3;
              }
              else if (uVar16 == 2) {
                uVar19 = 4;
              }
              else if (uVar16 == 3) {
                uVar19 = 5;
              }
              else if (uVar16 == 4) {
                uVar19 = 6;
              }
              else {
                uVar19 = uVar32;
                if ((uVar16 != 5) && (uVar19 = uVar16, uVar16 == 6)) {
                  uVar19 = 1;
                }
              }
              puVar17 = &DAT_140358260;
              uVar20 = uVar26;
              do {
                if ((puVar17[1] &
                    CONCAT22(*(undefined2 *)(*(longlong *)(param_1 + 0x120) + 8),
                             *(undefined2 *)(*(longlong *)(param_1 + 0x120) + 10))) == *puVar17) {
                  uVar16 = (&DAT_140358268)[uVar20 * 4];
                  if (uVar16 != 0) goto LAB_14022cfd8;
                  break;
                }
                uVar16 = (int)uVar20 + 1;
                uVar20 = (ulonglong)uVar16;
                puVar17 = puVar17 + 4;
              } while (uVar16 < 0xe8);
              uVar16 = 0x7c;
LAB_14022cfd8:
              if (*(int *)(param_1 + 0x8c78) != 0) {
                uVar16 = 0x28;
              }
              if (*(int *)(param_1 + 0x8c7c) != 0) {
                uVar16 = 0x24;
              }
              uVar20 = uVar26;
              uVar25 = uVar26;
              uVar23 = (ulonglong)uVar19;
              if (uVar16 < (uint)(1 << (sbyte)uVar19)) {
                uVar20 = 0;
                uVar25 = 0;
                uVar23 = uVar26;
              }
              do {
                uVar19 = (uint)uVar20;
                uVar28 = 1 << ((byte)uVar20 & 0x1f) & uVar16;
                if ((uVar28 != 0) && ((uint)uVar23 <= uVar19)) {
                  if (uVar19 == 2) {
                    uVar21 = 0;
                  }
                  else if (uVar19 != 3) {
                    if (uVar19 == 4) {
                      uVar21 = 2;
                    }
                    else if (uVar19 == 5) {
                      uVar21 = 3;
                    }
                    else if (uVar19 == 6) {
                      uVar21 = 4;
                    }
                    else if (uVar19 == 0) {
                      uVar21 = 5;
                    }
                    else {
                      uVar21 = uVar19;
                      if (uVar19 == 1) {
                        uVar21 = 6;
                      }
                    }
                  }
                  uVar25 = 0;
                  if (uVar14 == uVar21) goto LAB_14022d0d3;
                  DbgPrint("AUTO.INPUT( %d -> %d )",uVar14,uVar21);
                  *(uint *)(param_1 + 0x6840) = uVar21;
                  goto LAB_14022d0ae;
                }
                uVar13 = uVar19;
                if (uVar28 == 0) {
                  uVar13 = (uint)uVar25;
                }
                uVar20 = (ulonglong)(uVar19 + 1);
                uVar25 = (ulonglong)uVar13;
              } while (uVar19 + 1 < 7);
              if ((uVar13 != 2) && (uVar32 = uVar21, uVar13 != 3)) {
                if (uVar13 == 4) {
                  uVar32 = 2;
                }
                else if (uVar13 == 5) {
                  uVar32 = 3;
                }
                else if (uVar13 == 6) {
                  uVar32 = 4;
                }
                else if (uVar13 == 0) {
                  uVar32 = 5;
                }
                else {
                  uVar32 = uVar13;
                  if (uVar13 == 1) {
                    uVar32 = 6;
                  }
                }
              }
              uVar25 = uVar26;
              if (uVar14 != uVar32) {
                DbgPrint("AUTO.INPUT( %d -> %d )",uVar14,uVar32);
                *(uint *)(param_1 + 0x6840) = uVar32;
                uVar21 = uVar32;
LAB_14022d0ae:
                tw9900_init_all(param_1,uVar21,*(undefined4 *)(param_1 + 0x6850),
                                *(undefined4 *)(param_1 + 0x6854),*(undefined4 *)(param_1 + 0x6858),
                                1);
                uVar25 = 0;
              }
            }
          }
LAB_14022d0d3:
          uVar26 = (ulonglong)local_res18;
        }
      }
    }
    cVar4 = *(char *)(param_1 + 0x6ab0);
    uVar20 = (ulonglong)local_50;
  } while( true );
}