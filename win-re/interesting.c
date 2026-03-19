
undefined8 FUN_140247d2c(longlong param_1)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  bool bVar7;
  uint local_res8 [2];
  undefined local_res10 [8];
  
  local_res8[0] = 0;
  uVar4 = 0;
  bVar1 = read_mst(*(undefined8 *)(param_1 + 0x1c8),0,0x59);
  bVar2 = read_mst(*(undefined8 *)(param_1 + 0x1c8),0,0x5a);
  uVar3 = (uint)bVar2 + (bVar1 & 0x3f) * 0x100;
  if (1 < uVar3) {
    uVar4 = (uint)(0x1312d0 / (ulonglong)(uVar3 - 1)) & 0xffff;
    if (uVar4 - 0x1eb < 0x13) {
      return 5000;
    }
    if (uVar4 - 0xf7 < 8) {
      return 0x9c4;
    }
  }
  uVar5 = 0;
  if ((*(char *)(param_1 + 2) == '\x01') &&
     (GetHDMIDotClock(param_1,local_res8,local_res10), uVar5 = local_res8[0], local_res8[0] != 0)) {
    if (0x12 < uVar4 - 0x24f) {
      if (uVar4 - 0xec < 9) {
        if (0xb52d4 < local_res8[0]) {
          return 0x960;
        }
        return 0x95d;
      }
LAB_140247e87:
      if (0x12 < uVar4 - 0x123) {
        return 5000;
      }
      if (0xb52d4 < uVar5) {
        return 3000;
      }
      return 0xbb5;
    }
    if (0x16a5a8 < local_res8[0]) {
      return 6000;
    }
    if (local_res8[0] - 0xb52d5 < 0x3ef6c) {
      return 6000;
    }
    if (local_res8[0] - 0x83e5b < 0x27006) {
      return 6000;
    }
    if (local_res8[0] - 0x41f38 < 0x381e9) {
      return 6000;
    }
    bVar6 = local_res8[0] - 0x3d7e9 < 0x1fb7;
    bVar7 = local_res8[0] - 0x3d7e9 == 0x1fb7;
  }
  else {
    if (0x12 < uVar4 - 0x24f) {
      if (uVar4 - 0xec < 9) {
        if (uVar3 < 0x1461) {
          return 0x960;
        }
        return 0x95d;
      }
      if (uVar4 - 0x123 < 0x13) {
        if (uVar3 < 0x104e) {
          return 3000;
        }
        return 0xbb5;
      }
      goto LAB_140247e87;
    }
    bVar6 = uVar3 < 0x825;
    bVar7 = uVar3 == 0x825;
  }
  if (bVar6 || bVar7) {
    return 6000;
  }
  return 0x176a;
}


void FUN_140251a48(longlong param_1,byte param_2,char param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  
  if (1 < (byte)(param_3 + 0xbbU)) {
    bVar1 = param_2 - 0xc;
    if (param_2 < 0xd) {
      bVar1 = param_2;
    }
    bVar3 = read_mst(*(undefined8 *)(param_1 + 0x1c8),0,0xb2);
    bVar4 = read_mst(*(undefined8 *)(param_1 + 0x1c8),0,0xb5);
    bVar2 = bVar3 & 0xf7 | 8;
    if (bVar1 < 6) {
      bVar2 = bVar3 & 0xf7;
    }
    send_mst(*(undefined8 *)(param_1 + 0x1c8),0,0xb2,bVar2);
    bVar2 = bVar1 - 6;
    if (bVar1 < 6) {
      bVar2 = bVar1;
    }
    send_mst(*(undefined8 *)(param_1 + 0x1c8),0,0xb5,bVar2 << 2 | bVar4 & 0xc3);
  }
  return;
}


uint FUN_140248be8(longlong param_1)

{
  longlong lVar1;
  undefined uVar2;
  undefined uVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  
  lVar1 = *(longlong *)(param_1 + 0x1c528);
  if (*(int *)(param_1 + 0x6840) - 2U < 2) {
    if ((int)*(uint *)(param_1 + 0x6d54) < 0) {
      uVar10 = 0;
      uVar8 = 0;
      uVar2 = read_mst(param_1,0,0x1e);
      uVar3 = read_mst(param_1,0,0x1f);
      send_mst(param_1,0,0x1e,0);
      send_mst(param_1,0,0x1f,0);
      send_mst(param_1,0,0xe0,0);
      uVar12 = 0;
      do {
        uVar11 = uVar12 & 0x8000003f;
        if ((int)uVar11 < 0) {
          uVar11 = (uVar11 - 1 | 0xffffffc0) + 1;
        }
        send_mst(param_1,0,4,(char)uVar11 << 2);
        send_mst(param_1,0,0xe0,0x80);
        FUN_1402499fc(param_1,500000);
        send_mst(param_1,0,0xe0,0x40);
        bVar4 = read_mst(param_1,0,0xe9);
        bVar5 = read_mst(param_1,0,0xe8);
        bVar6 = read_mst(param_1,0,0xe7);
        bVar7 = read_mst(param_1,0,0xe6);
        uVar9 = (uint)bVar7 + (((bVar4 & 3) * 0x100 + (uint)bVar5) * 0x100 + (uint)bVar6) * 0x100;
        DbgPrint("MST3367_ADC_AUTO_PHASE( %02d -> %02d )");
        if ((uVar12 != 0) && (uVar10 < uVar9)) {
          uVar10 = uVar9;
          uVar8 = uVar11;
        }
        uVar12 = uVar12 + 4;
      } while ((int)uVar12 < 0x41);
      send_mst(param_1,0,0xe0,0);
      send_mst(param_1,0,0x1e,uVar2);
      send_mst(param_1,0,0x1f,uVar3);
      send_mst(param_1,0,4,(char)uVar8 << 2);
      *(uint *)(lVar1 + 0x1cd8) = uVar8;
      DbgPrint("MST3367_ADC_AUTO_PHASE( %d )\n",uVar8);
    }
    else {
      uVar8 = *(uint *)(param_1 + 0x6d54) & 0x3fffffff;
      send_mst(param_1,0,4,(char)uVar8 << 2);
      DbgPrint("MST3367_ADC_AUTO_PHASE( %d )\n",uVar8);
    }
  }
  else {
    uVar8 = 0;
  }
  return uVar8;
}


ulonglong FUN_140248f68(longlong param_1,uint *param_2,uint *param_3,uint *param_4,uint *param_5,
                       uint *param_6,undefined4 *param_7,uint *param_8)

{
  undefined auVar1 [16];
  uint uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  undefined uVar13;
  uint uVar14;
  ulonglong uVar15;
  ulonglong uVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  byte bVar20;
  
  uVar12 = 0;
  if (*(char *)(param_1 + 0x6ab0) == '\0') {
    if ((*(short *)(*(longlong *)(param_1 + 0x120) + 8) == 0x5ca) &&
       (*(short *)(*(longlong *)(param_1 + 0x120) + 10) == 0x901)) {
      uVar13 = 0x62;
    }
    else {
      uVar13 = 0x40;
      if (*(int *)(param_1 + 0x7654) != 0) {
        uVar13 = 0x62;
      }
    }
    send_mst(param_1,0,0xe,uVar13);
    if ((*(char *)(param_1 + 0x6ab0) == '\0') &&
       (bVar3 = read_mst(param_1,0,0x14), *(char *)(param_1 + 0x6ab0) == '\0')) {
      read_mst(param_1,0,0x15);
      bVar4 = bVar3 & 0x90;
      bVar20 = bVar4 == 0x90;
      if (bVar4 == 0x80) {
        bVar20 = 2;
      }
      else if ((bVar4 == 0) && ((bVar3 & 2) != 0)) {
        bVar20 = 3;
      }
      else if (!(bool)bVar20) {
        if (*(char *)(param_1 + 0x6ab0) != '\0') {
          return 0x123456789abcdef;
        }
        if ((*(short *)(*(longlong *)(param_1 + 0x120) + 8) != 0x5ca) ||
           (*(short *)(*(longlong *)(param_1 + 0x120) + 10) != 0x901)) {
          send_mst(param_1,0,0x11,0x20);
        }
        *param_4 = 0;
        *param_5 = 0;
        *param_6 = 0;
        *param_7 = 0;
        *param_8 = 0;
        if (*(char *)(param_1 + 0x6ab0) != '\0') {
          return 0x123456789abcdef;
        }
        send_mst(param_1,0,0xb3,0xff);
        if (*(char *)(param_1 + 0x6ab0) != '\0') {
          return 0x123456789abcdef;
        }
        send_mst(param_1,2,0x27,0xff);
        return 0;
      }
      if (*(char *)(param_1 + 0x6ab0) == '\0') {
        bVar4 = read_mst(param_1,0,0x57);
        if (*(char *)(param_1 + 0x6ab0) == '\0') {
          bVar5 = read_mst(param_1,0,0x58);
          uVar18 = (bVar4 & 0x3f) << 8 | (uint)bVar5;
          if (*(char *)(param_1 + 0x6ab0) == '\0') {
            uVar14 = uVar18;
            if (((*(short *)(*(longlong *)(param_1 + 0x120) + 8) != 0x5ca) ||
                (*(short *)(*(longlong *)(param_1 + 0x120) + 10) != 0x901)) &&
               ((byte)(bVar20 - 2) < 2)) {
              if (uVar18 < 0x401) {
                uVar14 = 0x400;
              }
              send_mst(param_1,0,0x11,uVar14 >> 7);
            }
            if (*(char *)(param_1 + 0x6ab0) == '\0') {
              bVar4 = read_mst(param_1,0,0x59);
              if (*(char *)(param_1 + 0x6ab0) == '\0') {
                bVar5 = read_mst(param_1,0,0x5a);
                if (*(char *)(param_1 + 0x6ab0) == '\0') {
                  bVar6 = read_mst(param_1,0,0x5b);
                  if (*(char *)(param_1 + 0x6ab0) == '\0') {
                    bVar7 = read_mst(param_1,0,0x5c);
                    if (*(char *)(param_1 + 0x6ab0) == '\0') {
                      bVar8 = read_mst(param_1,0,0x5d);
                      if (*(char *)(param_1 + 0x6ab0) == '\0') {
                        uVar10 = read_mst(param_1,0,0x5e);
                        if (*(char *)(param_1 + 0x6ab0) == '\0') {
                          bVar9 = read_mst(param_1,0,0x5f);
                          uVar17 = (bVar4 & 0x3f) << 8 | (uint)bVar5;
                          if (uVar18 == 0) {
                            uVar18 = 0;
                          }
                          else {
                            uVar18 = (uint)(1600000 / (ulonglong)uVar18);
                          }
                          uVar16 = (ulonglong)((bVar6 & 7) << 8 | (uint)bVar7);
                          if (uVar17 == 0) {
                            uVar15 = 0;
                          }
                          else {
                            uVar15 = 0x1312d0 / (ulonglong)uVar17;
                          }
                          bVar9 = bVar9 >> 3;
                          if ((bVar9 & 1) != 0) {
                            iVar19 = 0;
                            do {
                              if (*(char *)(param_1 + 0x6ab0) != '\0') {
                                return 0x123456789abcdef;
                              }
                              bVar4 = read_mst(param_1,0,0x5f);
                              bVar9 = bVar4 >> 3;
                            } while (((bVar4 & 8) != 0) && (iVar19 = iVar19 + 1, iVar19 < 3));
                          }
                          uVar2 = bVar9 & 1 | (bVar3 >> 2 & 8 | bVar3 & 4) >> 1;
                          *param_2 = uVar14;
                          *param_3 = uVar17;
                          if (uVar18 == 0) {
                            uVar11 = 0;
                          }
                          else {
                            auVar1._8_8_ = 0;
                            auVar1._0_8_ = CONCAT44(0,uVar18);
                            uVar11 = SUB164((ZEXT816(0) << 0x40 | ZEXT816(0x192d50)) / auVar1,0) &
                                     0xfffffff8;
                          }
                          *param_4 = uVar11;
                          if (uVar14 != 0) {
                            uVar12 = ((uVar14 >> 1) + uVar17 * 0x500) / uVar14;
                          }
                          *param_5 = uVar12;
                          *param_6 = uVar18;
                          *param_7 = (int)uVar15;
                          *param_8 = (uVar17 * 2 + 0x7e) / 0x7d;
                          DbgPrint("MST3367_ADC_MODE_DETECT( %d ? %d ? %d ? %d ? %d ? status = %d )\ n"
                                   ,uVar18,(uVar10 & 0xe0) >> 4 | (uint)bVar8 << 4,uVar16,
                                   (int)uVar15,uVar2,bVar20);
                          DbgPrint("MST3367_ADC_MODE_DETECT( ht:%d ? vt:%d ? hp:%d ? vp:%d ? delay:% d )\n"
                                   ,*param_4,*param_5,*param_6,*param_7,*param_8);
                          return (((((ulonglong)bVar20 | 0xfffffffffffff800) << 4 | (ulonglong)uVar2
                                   ) << 0x10 | uVar15) << 0x10 | CONCAT44(0,uVar18)) << 0x10 |
                                 uVar16;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0x123456789abcdef;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_140249474(longlong param_1,byte param_2,byte param_3,byte param_4,char param_5,byte param_6
                  )

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  ushort uVar4;
  short sVar5;
  uint uVar6;
  int iVar7;
  ushort uVar8;
  int iVar9;
  undefined *puVar10;
  uint uVar11;
  short *psVar12;
  int iVar13;
  longlong lVar14;
  uint uVar15;
  ulonglong uVar16;
  uint uVar17;
  undefined8 *puVar18;
  undefined auStack_88 [32];
  byte local_68;
  undefined4 local_64;
  int local_60;
  undefined8 local_58;
  undefined local_50;
  ulonglong local_48;
  
  local_48 = DAT_14035a610 ^ (ulonglong)auStack_88;
  local_58 = *(longlong *)(param_1 + 0x1c528);
  uVar17 = (uint)param_4;
  iVar13 = 0x80;
  bVar3 = 0x80;
  if (*(int *)(param_1 + 0x8d4c) == 0) {
    uVar15 = *(uint *)(param_1 + 0x6840);
    uVar16 = (ulonglong)uVar15;
    if (uVar15 == 2) {
      iVar13 = 0x8e;
    }
    else if (uVar15 == 3) {
      iVar13 = 0x8c;
    }
    if (param_2 < 0x81) {
      cVar2 = (char)(iVar13 * (uint)param_2 >> 7);
    }
    else {
      iVar7 = (0xff - iVar13) * (param_2 - 0x80);
      cVar2 = (char)((int)(iVar7 + (iVar7 >> 0x1f & 0x7fU)) >> 7) + (char)iVar13;
    }
    local_64 = CONCAT31(local_64._1_3_,cVar2);
    if (uVar15 != 2) {
      bVar3 = 0x82;
    }
    if (param_3 < 0x81) {
      uVar15 = (uint)bVar3 * (uint)param_3 >> 7 & 0xff;
    }
    else {
      iVar13 = (0xff - (uint)bVar3) * (param_3 - 0x80);
      uVar15 = (uint)(byte)((char)((int)((iVar13 >> 0x1f & 0x7fU) + iVar13) >> 7) + bVar3);
    }
  }
  else {
    if (param_2 < 0x81) {
      local_64 = (int)((uint)param_2 * 0x8e) >> 7;
    }
    else {
      iVar13 = (param_2 - 0x80) * 0x71;
      local_64 = CONCAT31(local_64._1_3_,
                          (char)((int)(iVar13 + (iVar13 >> 0x1f & 0x7fU)) >> 7) + -0x72);
    }
    uVar11 = *(uint *)(param_1 + 0x6840);
    uVar16 = (ulonglong)uVar11;
    bVar1 = bVar3;
    if (uVar11 != 2) {
      bVar1 = 0x70;
    }
    if (param_3 < 0x81) {
      uVar15 = (uint)bVar1 * (uint)param_3 >> 7;
    }
    else {
      iVar13 = (param_3 - 0x80) * (0xff - (uint)bVar1);
      uVar15 = (uint)(byte)(bVar1 + (char)((int)(iVar13 + (iVar13 >> 0x1f & 0x7fU)) >> 7));
    }
    if (uVar11 != 2) {
      bVar3 = 0x6e;
    }
    if (param_4 < 0x81) {
      uVar17 = bVar3 * uVar17 >> 7;
    }
    else {
      iVar13 = (uVar17 - 0x80) * (0xff - (uint)bVar3);
      uVar17 = (uint)(byte)((char)((int)((iVar13 >> 0x1f & 0x7fU) + iVar13) >> 7) + bVar3);
    }
  }
  local_60 = *(int *)(local_58 + 0x60);
  uVar11 = *(uint *)(param_1 + 0x7650);
  iVar13 = 0;
  if ((uint)uVar16 < 2) {
    uVar6 = read_mst(param_1,2,CONCAT71((int7)(uVar16 >> 8),0x4a));
    uVar6 = uVar6 >> 2 & 3;
    iVar13 = 0;
    if (uVar6 != 0) {
      if (uVar6 == 1) {
        uVar11 = uVar11 >> 4;
        iVar13 = 1;
      }
      else if (uVar6 == 2) {
        uVar11 = uVar11 >> 8;
        iVar13 = 2;
      }
    }
  }
  iVar7 = *(int *)(param_1 + 0x6840);
  if (iVar7 == 2) {
    iVar13 = 3;
  }
  uVar6 = uVar11 >> 0xc;
  if (iVar7 != 2) {
    uVar6 = uVar11;
  }
  if (iVar7 == 3) {
    iVar13 = 4;
  }
  uVar11 = uVar6 >> 0x10;
  if (iVar7 != 3) {
    uVar11 = uVar6;
  }
  local_58 = CONCAT44(local_58._4_4_,*(undefined4 *)(local_58 + 0x58));
  bVar3 = read_mst(param_1,0,0xab);
  if (*(int *)(param_1 + 0x8d38) == 0) {
    bVar3 = bVar3 & 0x95 | 0x15;
  }
  else {
    bVar3 = bVar3 & 0xaa | 0x2a;
  }
  send_mst(param_1,0,0xab,bVar3);
  bVar3 = read_mst(param_1,0,0xac);
  if (*(int *)(param_1 + 0x8d38) == 0) {
    bVar3 = bVar3 & 0xd5 | 0x15;
  }
  else {
    bVar3 = bVar3 | 0xbf;
  }
  send_mst(param_1,0,0xac,bVar3);
  if (*(int *)(param_1 + 0x6840) - 2U < 2) {
    local_68 = param_6;
    bVar3 = 5;
    param_6 = param_6 << 4 | param_6;
  }
  else {
    if (param_6 == 0) {
      bVar3 = 7;
    }
    else {
      bVar3 = (4 < param_6) - 1U & 5;
    }
    local_68 = 1;
    param_6 = 0x11;
  }
  send_mst(param_1,0,0xad,bVar3);
  send_mst(param_1,0,0x1e,param_6);
  send_mst(param_1,0,0x1f,local_68);
  uVar17 = (uVar17 & 0xff) * 10000 >> 7;
  bVar3 = -param_5;
  DAT_14036d4b0 = (undefined2)((uVar15 & 0xff) * 10000 >> 7);
  if (bVar3 == 0) {
    bVar3 = 0xff;
  }
  bVar1 = bVar3;
  if (bVar3 < 0x80) {
    bVar1 = -bVar3;
  }
  uVar15 = (byte)(bVar1 + 0x80) & 3;
  uVar16 = (ulonglong)((byte)(bVar1 + 0x80) >> 2);
  iVar7 = ((uint)*(ushort *)(&DAT_14029af12 + uVar16 * 2) -
          (uint)*(ushort *)(&DAT_14029af10 + uVar16 * 2)) * uVar15;
  uVar4 = (short)((int)(iVar7 + (iVar7 >> 0x1f & 3U)) >> 2) +
          *(ushort *)(&DAT_14029af10 + uVar16 * 2);
  uVar8 = -uVar4;
  if (0x7f < bVar3) {
    uVar8 = uVar4;
  }
  iVar7 = ((uint)*(ushort *)(&DAT_14029af62 + uVar16 * 2) -
          (uint)*(ushort *)(&DAT_14029af60 + uVar16 * 2)) * uVar15;
  _DAT_14036d4be = (short)((uVar8 * uVar17) / 10000);
  _DAT_14036d4b8 =
       (undefined2)
       ((ulonglong)
        ((ushort)((short)((int)(iVar7 + (iVar7 >> 0x1f & 3U)) >> 2) +
                 *(ushort *)(&DAT_14029af60 + uVar16 * 2)) * uVar17) / 10000);
  _DAT_14036d4ba = -_DAT_14036d4be;
  _DAT_14036d4bc = 0;
  _DAT_14036d4b4 = 0;
  DAT_14036d4b2 = 0;
  psVar12 = &DAT_14036d4b0;
  _DAT_14036d4c0 = _DAT_14036d4b8;
  _DAT_14036d4c8 = _DAT_14036d4b8;
  _DAT_14036d4cc = _DAT_14036d4be;
  if (local_60 == 0) {
    puVar10 = &DAT_14029aeb0;
    if ((int)local_58 != 1) {
      puVar10 = &DAT_14029aee0;
    }
    FUN_14024fc3c(puVar10,&DAT_14036d4b0);
  }
  local_58 = 0x979d9f9399a1959b;
  local_50 = 0xa3;
  if ((uVar11 & 2) == 0) {
    if ((uVar11 & 1) == 0) {
      iVar7 = 0x100;
    }
    else {
      iVar7 = 0xdc;
    }
  }
  else {
    iVar7 = 0x129;
  }
  puVar18 = &local_58;
  lVar14 = 9;
  do {
    iVar9 = *psVar12 * iVar7;
    FUN_140258c40(param_1,CONCAT31((int3)(short)((short)(iVar9 / 160000) + (short)(iVar9 >> 0x1f)),
                                   *(undefined *)puVar18),iVar9 / 0x271);
    puVar18 = (undefined8 *)((longlong)puVar18 + 1);
    psVar12 = psVar12 + 1;
    lVar14 = lVar14 + -1;
  } while (lVar14 != 0);
  FUN_140258c40(param_1,0xa5,0x2000);
  sVar5 = -0x1c00;
  if (iVar13 != 1) {
    sVar5 = -0x2000;
  }
  FUN_140258c40(param_1,0xa7,(ushort)(byte)local_64 * 0x40 + sVar5);
  FUN_140258c40(param_1,0xa9,0x2000);
  __security_check_cookie(local_48 ^ (ulonglong)auStack_88);
  return;
}


void FUN_140249a3c(undefined8 param_1,int param_2,ulonglong param_3,undefined8 param_4)

{
  short sVar1;
  uint uVar2;
  ushort uVar3;
  undefined uVar4;
  byte bVar5;
  byte bVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  ushort uVar10;
  ushort uVar11;
  short sVar12;
  ulonglong uVar13;
  ushort uVar14;
  uint uVar15;
  undefined auStack_a8 [32];
  byte local_88;
  ushort local_84;
  undefined local_80;
  undefined local_7f;
  uint local_7c;
  short asStack_78 [32];
  ulonglong local_38;
  
  local_38 = DAT_14035a610 ^ (ulonglong)auStack_a8;
  local_80 = read_mst(param_1,0,0x54);
  uVar9 = CONCAT71((int7)((ulonglong)param_4 >> 8),local_80) & 0xffffffffffffffef;
  send_mst(param_1,0,0x54,uVar9);
  local_7f = read_mst(param_1,0,0xe);
  uVar13 = CONCAT71((int7)(uVar9 >> 8),local_7f) | 8;
  send_mst(param_1,0,0xe,uVar13);
  uVar10 = 0;
  local_84 = 0;
  uVar11 = 0;
  uVar9 = 2000 / (param_3 & 0xffffffff);
  local_88 = 0;
  local_7c = (uint)uVar9;
  do {
    bVar5 = local_88;
    uVar15 = 0;
    uVar4 = read_mst(param_1,0,0xe);
    send_mst(param_1,0,0xe,CONCAT71((int7)(uVar13 >> 8),uVar4) ^ 4);
    uVar2 = local_7c;
    if ((int)uVar9 != 0) {
      uVar15 = 0;
      do {
        bVar5 = read_mst(param_1,0,0x5b);
        bVar6 = read_mst(param_1,0,0x5c);
        uVar11 = (ushort)bVar6 + (ushort)bVar5 * 0x100;
        if ((param_2 + 1U < (uint)uVar11) || ((uint)uVar11 < param_2 - 1U)) break;
        uVar15 = uVar15 + 1;
      } while (uVar15 < uVar2);
      uVar9 = (ulonglong)local_7c;
      uVar10 = local_84;
      bVar5 = local_88;
    }
    uVar14 = (ushort)param_2;
    uVar13 = 0;
    uVar3 = uVar14;
    if (uVar15 != (uint)uVar9) {
      uVar3 = uVar11;
    }
    uVar11 = uVar3;
    if (0xfffd < (ushort)(uVar11 - 1)) {
LAB_140249c1c:
      send_mst(param_1,0,0x54,local_80);
      send_mst(param_1,0,0xe,local_7f);
      __security_check_cookie(local_38 ^ (ulonglong)auStack_a8);
      return;
    }
    sVar1 = uVar11 - uVar14;
    if (uVar11 <= uVar14) {
      sVar1 = uVar14 - uVar11;
    }
    if ((ushort)(sVar1 - 1U) < 0x27) {
      uVar7 = (ulonglong)uVar10;
      sVar12 = 0;
      uVar10 = uVar10 + 1;
      uVar8 = 0;
      asStack_78[uVar7] = sVar1;
      local_84 = uVar10;
      if (uVar10 != 0) {
        do {
          if ((asStack_78[uVar8] == sVar1) && (sVar12 = sVar12 + 1, sVar12 == 3))
          goto LAB_140249c1c;
          bVar6 = (char)uVar8 + 1;
          uVar8 = (ulonglong)bVar6;
        } while (bVar6 < uVar10);
      }
    }
    if ((0x13 < uVar10) || ((uVar10 == 0 && (10 < bVar5)))) goto LAB_140249c1c;
    local_88 = bVar5 + 1;
    if (0x95 < local_88) goto LAB_140249c1c;
  } while( true );
}


bool FUN_140249c74(longlong param_1)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  
  if (*(int *)(param_1 + 0x6840) == 3) {
    return false;
  }
  bVar1 = read_mst(param_1,0,0x59);
  bVar2 = read_mst(param_1,0,0x5a);
  uVar5 = (ushort)bVar2 + (ushort)(bVar1 & 0x3f) * 0x100;
  if (uVar5 == 0) {
    return false;
  }
  uVar3 = (ushort)(0x1312d0 / (ulonglong)uVar5);
  if ((ushort)(uVar3 - 0x4a7) < 0x13) {
    uVar3 = 0x412;
    goto LAB_140249dd1;
  }
  if (uVar3 < 0x3df) {
    if (0x348 < uVar3) goto LAB_140249d17;
    if (0x2e4 < uVar3) goto LAB_140249d36;
    if (0x2c6 < uVar3) {
      uVar4 = 0x2da;
      goto LAB_140249d9b;
    }
    if (0x2b2 < uVar3) {
      uVar4 = 0x2c5;
      goto LAB_140249d9b;
    }
    if (0x24e < uVar3) {
      if (uVar3 < 0x262) {
        return 0x825 < uVar5;
      }
      goto LAB_140249dac;
    }
    if (0x226 < uVar3) {
      uVar4 = 0x230;
      goto LAB_140249d9b;
    }
    if (0x1ea < uVar3) {
      uVar4 = 0x1fe;
      goto LAB_140249d9b;
    }
    if (0xf0 < uVar3) goto LAB_140249dac;
    if (uVar3 < 0xec) {
      return false;
    }
  }
  else {
    if (uVar3 < 0x3f2) {
      return false;
    }
LAB_140249d17:
    if (uVar3 < 0x35c) {
      return false;
    }
LAB_140249d36:
    uVar4 = 0x2f8;
LAB_140249d9b:
    if (uVar3 < uVar4) {
      return false;
    }
LAB_140249dac:
    if (uVar3 < 0x104) {
      return false;
    }
  }
  if (0xf4 < uVar3) {
    if (0x12 < (ushort)(uVar3 - 0x123)) {
      return false;
    }
    return 0x104d < uVar5;
  }
  uVar3 = 0x1460;
LAB_140249dd1:
  return uVar3 < uVar5;
}


void FUN_140249ec8(longlong param_1)

{
  uint uVar1;
  ulonglong uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  undefined auStack_38 [32];
  undefined4 local_18;
  undefined2 local_14;
  ulonglong local_10;
  
  local_10 = DAT_14035a610 ^ (ulonglong)auStack_38;
  bVar3 = read_mst(param_1,2,1);
  send_mst(param_1,2,1,bVar3 & 0xf | 0x60);
  bVar3 = read_mst(param_1,2,4);
  send_mst(param_1,2,4,bVar3 | 1);
  send_mst(param_1,2,6,8);
  bVar3 = read_mst(param_1,2,9);
  send_mst(param_1,2,9,bVar3 | 0x20);
  bVar3 = read_mst(param_1,0,0x54);
  send_mst(param_1,0,0x54,bVar3 & 0xef);
  bVar3 = read_mst(param_1,0,0xac);
  send_mst(param_1,0,0xac,bVar3 | 0x80);
  bVar3 = read_mst(param_1,0,0);
  send_mst(param_1,0,0,bVar3 | 0x80);
  bVar3 = read_mst(param_1,0,0xce);
  send_mst(param_1,0,0xce,bVar3 | 0x80);
  bVar3 = read_mst(param_1,0,0xcf);
  send_mst(param_1,0,0xcf,bVar3 & 0xfa | 2);
  bVar3 = read_mst(param_1,0,0);
  send_mst(param_1,0,0,bVar3 & 0x7f);
  if (*(int *)(param_1 + 0x8c28) == 0) {
    uVar1 = *(uint *)(param_1 + 0x7674);
    local_18 = 0x3040006;
    uVar2 = (ulonglong)uVar1 / 6;
    local_14 = 0x107;
    bVar5 = read_mst(param_1,CONCAT71((int7)(uVar2 >> 8),0x80),0xd0);
    bVar4 = read_mst(param_1,0x80,0xcf);
    bVar3 = *(byte *)((longlong)&local_18 + (ulonglong)(uVar1 + (int)uVar2 * -6));
    bVar4 = bVar3 << 7 | bVar4 & 0x7f;
    bVar5 = (bVar3 >> 1 ^ bVar5) & 3 ^ bVar5;
  }
  else {
    bVar3 = read_mst(param_1,0x80,0xd0);
    bVar4 = read_mst(param_1,0x80,0xcf);
    bVar4 = bVar4 | 0x80;
    bVar5 = bVar3 & 0xfd | 1;
  }
  send_mst(param_1,0x80,0xd0,bVar5);
  send_mst(param_1,0x80,0xcf,bVar4);
  __security_check_cookie(local_10 ^ (ulonglong)auStack_38);
  return;
}


ulonglong FUN_14024a0ec(longlong param_1,undefined4 *param_2,uint *param_3,int *param_4,
                       uint *param_5,uint *param_6)

{
  undefined auVar1 [16];
  uint5 uVar2;
  byte bVar3;
  undefined uVar4;
  undefined uVar5;
  undefined uVar6;
  undefined uVar7;
  undefined uVar8;
  undefined uVar9;
  undefined uVar10;
  undefined uVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  ulonglong uVar15;
  longlong lVar16;
  ulonglong uVar17;
  uint uVar18;
  ulonglong uVar19;
  uint uVar20;
  ulonglong uVar21;
  int iVar22;
  uint uVar23;
  undefined8 in_stack_ffffffffffffffa0;
  undefined4 uVar24;
  
  uVar24 = (undefined4)((ulonglong)in_stack_ffffffffffffffa0 >> 0x20);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  bVar3 = read_mst(param_1,0,0x55);
  DbgPrint("MST3367_HDMI_MODE_DETECT( 0x55 = 0x%x ) \n",bVar3);
  if ((bVar3 & 0x3c) != 0x3c) {
    *param_2 = 0;
    *param_3 = 0;
    *param_4 = 0;
    *param_5 = 0;
    *param_6 = 0;
    if (*(char *)(param_1 + 0x6ab0) == '\0') {
      send_mst(param_1,0,0xb3,0xff);
      send_mst(param_1,2,0x27,0xff);
      return 0;
    }
    return 0x123456789abcdef;
  }
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  uVar4 = read_mst(param_1,0,0x6a);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  uVar5 = read_mst(param_1,0,0x6b);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  uVar6 = read_mst(param_1,0,0x57);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  uVar7 = read_mst(param_1,0,0x58);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  uVar8 = read_mst(param_1,0,0x59);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  uVar9 = read_mst(param_1,0,0x5a);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  uVar10 = read_mst(param_1,0,0x5b);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  uVar11 = read_mst(param_1,0,0x5c);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  bVar12 = read_mst(param_1,0,0x5f);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  bVar13 = read_mst(param_1,2,0x29);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  uVar21 = (ulonglong)((uint5)CONCAT11(uVar4,uVar5) & 0xfff);
  uVar2 = (uint5)CONCAT11(uVar10,uVar11) & 0x7ff;
  bVar14 = read_mst(param_1,2,0x28);
  uVar19 = (ulonglong)bVar14 | (longlong)(int)((bVar13 & 0x1f) << 8);
  uVar15 = uVar19 + 1;
  if ((bVar14 & 1) == 0) {
    uVar15 = uVar19;
  }
  uVar18 = (uint)(CONCAT11(uVar6,uVar7) & 0x3fff);
  if (uVar18 == 0) {
    iVar22 = 0;
  }
  else {
    iVar22 = (int)(1600000 / (ulonglong)uVar18);
  }
  uVar18 = (uint)(CONCAT11(uVar8,uVar9) & 0x3fff);
  if (uVar18 == 0) {
    uVar23 = 0;
  }
  else {
    uVar23 = (uint)(0x1312d0 / (ulonglong)uVar18);
  }
  lVar16 = (longlong)(int)uVar23;
  uVar19 = (ulonglong)(bVar12 >> 3 & 1);
  if (*(char *)(param_1 + 0x6ab0) != '\0') {
    return 0x123456789abcdef;
  }
  uVar17 = read_mst(param_1,1);
  if ((uVar17 & 4) != 0) {
    if (*(char *)(param_1 + 0x6ab0) != '\0') {
      return 0x123456789abcdef;
    }
    bVar12 = read_mst(param_1,2,0x47);
    bVar12 = bVar12 & 0xf;
    if (bVar12 == 5) {
      uVar21 = (uVar21 * 4) / 5;
    }
    else {
      if (bVar12 == 6) {
        auVar1._8_8_ = 0;
        auVar1._0_8_ = uVar21 * 2;
        uVar21 = SUB168(ZEXT816(0xaaaaaaaaaaaaaaab) * auVar1,8);
      }
      else if (bVar12 != 7) goto LAB_14024a3cb;
      uVar21 = uVar21 >> 1;
    }
  }
LAB_14024a3cb:
  *param_2 = (int)uVar21;
  uVar20 = (uint)uVar2;
  *param_3 = uVar20;
  *param_4 = iVar22;
  *param_5 = uVar23;
  *param_6 = (uVar18 * 2 + 0x7e) / 0x7d;
  if ((*param_3 != 0) && (uVar18 = *param_3 + 1, uVar18 != 0)) {
    uVar18 = (uint)(iVar22 * 1000) / uVar18;
    uVar20 = *param_5;
    if (uVar20 < uVar18) {
      uVar20 = uVar18 - uVar20;
    }
    else {
      uVar20 = uVar20 - uVar18;
    }
  }
  if (*(char *)(param_1 + 0x6ab0) == '\0') {
    bVar12 = read_mst(param_1,0,0x5c);
    if (((((((uint)bVar12 ^ *param_3) & 0xfe) == 0) && (0x95 < *param_3)) &&
        ((longlong)(int)uVar23 - 200U < 0x515)) && (uVar20 < 6)) {
      DbgPrint("MST3367_HDMI_MODE_DETECT( %d ? %d ? %d ? %d ? %d ? R0055 = %02X %c )\n",
               uVar21 & 0xffffffff,uVar15,(ulonglong)uVar2,iVar22,uVar23,bVar3,
               CONCAT44(uVar24,(-(uint)(uVar19 != 0) & 0xfffffff9) + 0x70),uVar10,lVar16);
      return ((((uVar19 | 0xfffffffffffffffe) << 0xe | (longlong)(int)uVar23) << 0x10 | uVar15) <<
              0x10 | uVar21) << 0x10 | (ulonglong)uVar2;
    }
    DbgPrint();
    *param_2 = 0;
    *param_3 = 0;
    *param_4 = 0;
    *param_5 = 0;
    *param_6 = 0;
    return 0;
  }
  return 0x123456789abcdef;
}


uint FUN_14024a62c(undefined8 param_1)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  
  bVar2 = read_mst(param_1,2,0xb);
  bVar3 = read_mst(param_1,2,0xc);
  uVar4 = (bVar3 & 0x3f) << 8 | (uint)bVar2;
  bVar2 = read_mst(param_1,2,0xe);
  uVar1 = uVar4 | 0x8000;
  if ((bVar2 & 8) == 0) {
    uVar1 = uVar4;
  }
  return uVar1;
}


undefined8 init_mst(longlong param_1)

{
  char cVar1;
  short sVar2;
  longlong lVar3;
  undefined4 uVar4;
  undefined uVar5;
  byte bVar6;
  ushort uVar7;
  ushort uVar8;
  uint uVar9;
  char *pcVar10;
  undefined8 uVar11;
  undefined uVar12;
  int iVar13;
  undefined8 uVar14;
  undefined7 uVar15;
  undefined8 uVar16;
  ulonglong uVar17;
  bool bVar18;
  
  lVar3 = *(longlong *)(param_1 + 0x1c528);
  send_reset_vendors();
  FUN_140246958(param_1);
  uVar11 = 0;
  *(undefined4 *)(lVar3 + 0x1ce4) = 0xffff;
  *(undefined8 *)(lVar3 + 0x30) = 0;
  *(undefined8 *)(lVar3 + 0x38) = 0;
  *(undefined4 *)(lVar3 + 0x40) = 0;
  *(undefined8 *)(lVar3 + 0x48) = 0;
  *(undefined8 *)(lVar3 + 0x50) = 0;
  *(undefined8 *)(lVar3 + 100) = 0;
  *(undefined4 *)(lVar3 + 0x88) = 0;
  *(undefined4 *)(lVar3 + 0x1cd4) = 0;
  *(undefined8 *)(lVar3 + 0x1cdc) = 0;
  *(undefined8 *)(lVar3 + 0x58) = 0;
  *(undefined4 *)(lVar3 + 0x60) = 0;
  send_mst(param_1,0,0x13,8);
  FUN_14024b39c(param_1,0);
  send_mst(param_1,0,0x41,0x6f);
  uVar14 = 0;
  send_mst(param_1,0,0xb8,0);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),2);
  send_mst(param_1,1,0xf,uVar14);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x30);
  send_mst(param_1,1,0x16,uVar14);
  if (*(int *)(param_1 + 0x8bf0) == 1) {
    send_mst(param_1,1,0x17,0);
    send_mst(param_1,1,0x18,0);
    uVar14 = 0;
LAB_14024a837:
    send_mst(param_1,1,0x19,uVar14);
  }
  else {
    uVar9 = *(uint *)(param_1 + 0x7670);
    if (uVar9 == 0) {
      uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),2);
      send_mst(param_1,1,0x17,uVar14);
      uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),2);
      send_mst(param_1,1,0x18,uVar14);
      uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),2);
      send_mst(param_1,1,0x19,uVar14);
      uVar9 = *(uint *)(param_1 + 0x7670);
    }
    if (uVar9 == 1) {
      send_mst(param_1,1,0x17,0);
      send_mst(param_1,1,0x18,0);
      uVar14 = 0;
      send_mst(param_1,1,0x19,0);
      uVar9 = *(uint *)(param_1 + 0x7670);
    }
    if (1 < uVar9) {
      uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),1);
      send_mst(param_1,1,0x17,uVar14);
      uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),1);
      send_mst(param_1,1,0x18,uVar14);
      uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),1);
      goto LAB_14024a837;
    }
  }
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x50);
  send_mst(param_1,1,0x1a,uVar14);
  uVar5 = read_mst(param_1,1,0x2a);
  send_mst(param_1,1,0x2a,CONCAT71((int7)((ulonglong)uVar14 >> 8),uVar5) | 7);
  send_mst(param_1,2,8,3);
  lVar3 = *(longlong *)(param_1 + 0x120);
  uVar14 = 0x4bb;
  uVar16 = 0x543;
  if ((((((*(char *)(lVar3 + 0xf) == '\x1c') && (*(char *)(lVar3 + 0xe) == -6)) ||
        ((*(char *)(lVar3 + 0xf) == '\0' && ((*(char *)(lVar3 + 0xe) - 3U & 0xfd) == 0)))) ||
       ((sVar2 = *(short *)(lVar3 + 8), sVar2 == 0x4bb &&
        ((*(ushort *)(lVar3 + 10) & 0xfff) == 0x543)))) ||
      ((sVar2 == 0xfd9 &&
       ((uVar7 = *(short *)(lVar3 + 10) - 0x4f, uVar7 < 0x26 &&
        ((0x2000008001U >> ((ulonglong)uVar7 & 0x3f) & 1) != 0)))))) ||
     (((sVar2 == 0x17ef && (*(short *)(lVar3 + 10) == 0x7219)) ||
      ((sVar2 == 0x1164 && ((*(ushort *)(lVar3 + 10) & 0xfff) == 0x535)))))) {
    FUN_14024b1c4(param_1);
    bVar18 = *(int *)(param_1 + 0x5ecc) != 0;
    uVar15 = (undefined7)((ulonglong)uVar16 >> 8);
  }
  else {
    bVar18 = *(int *)(param_1 + 0x8bd4) == 1;
    uVar15 = 5;
  }
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x24);
  send_mst(param_1,1,uVar14,CONCAT71(uVar15,bVar18 + '@'));
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x24);
  bVar6 = read_mst(param_1,1,uVar14);
  if ((bVar6 & 1) != 0) {
    uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x25);
    send_mst(param_1,1,uVar14,0);
    uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x26);
    send_mst(param_1,1,uVar14,0);
    iVar13 = 5;
    do {
      uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x27);
      send_mst(param_1,1,uVar14,0);
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
  }
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x30);
  send_mst(param_1,1,uVar14,0x80);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x31);
  send_mst(param_1,1,uVar14,0);
  uVar16 = 0;
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x32);
  send_mst(param_1,1,uVar14,0);
  uVar12 = 0x14;
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0xb0);
  uVar16 = CONCAT71((int7)((ulonglong)uVar16 >> 8),0x14);
  send_mst(param_1,0,uVar14,uVar16);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0xae);
  uVar5 = read_mst(param_1,0,uVar14);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0xae);
  uVar17 = CONCAT71((int7)((ulonglong)uVar16 >> 8),uVar5) | 4;
  send_mst(param_1,0,uVar14,uVar17);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0xad);
  send_mst(param_1,0,uVar14,
           CONCAT71((int7)(uVar17 >> 8),(*(int *)(param_1 + 0x7690) != 0) + -1) & 0xffffffffffffff05
          );
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0xb1);
  send_mst(param_1,0,uVar14,0xc0);
  uVar16 = 0;
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0xb2);
  send_mst(param_1,0,uVar14,0);
  if ((*(char *)(*(longlong *)(param_1 + 0x120) + 0xf) != '\x05') ||
     (*(char *)(*(longlong *)(param_1 + 0x120) + 0xe) != '_')) {
    uVar12 = 0;
  }
  uVar16 = CONCAT71((int7)((ulonglong)uVar16 >> 8),uVar12);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0xb3);
  send_mst(param_1,0,uVar14,uVar16);
  uVar16 = CONCAT71((int7)((ulonglong)uVar16 >> 8),0x55);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0xb4);
  send_mst(param_1,0,uVar14,uVar16);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0xb4);
  uVar5 = read_mst(param_1,0,uVar14);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0xb4);
  uVar17 = CONCAT71((int7)((ulonglong)uVar16 >> 8),uVar5) & 0xfffffffffffffffc;
  send_mst(param_1,0,uVar14,uVar17);
  uVar16 = CONCAT71((int7)(uVar17 >> 8),0x61);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),1);
  send_mst(param_1,2,uVar14,uVar16);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),2);
  uVar16 = CONCAT71((int7)((ulonglong)uVar16 >> 8),0xf5);
  send_mst(param_1,2,uVar14,uVar16);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),3);
  uVar5 = read_mst(param_1,2,uVar14);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),3);
  send_mst(param_1,2,uVar14,CONCAT71((int7)((ulonglong)uVar16 >> 8),uVar5) | 2);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),4);
  send_mst(param_1,2,uVar14,1);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),5);
  send_mst(param_1,2,uVar14,0);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),6);
  send_mst(param_1,2,uVar14,8);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x1c);
  send_mst(param_1,2,uVar14,0x1a);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x1d);
  send_mst(param_1,2,uVar14,0);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x1e);
  send_mst(param_1,2,uVar14,0);
  uVar16 = 0;
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x1f);
  send_mst(param_1,2,uVar14,0);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x25);
  uVar5 = read_mst(param_1,2,uVar14);
  uVar17 = CONCAT71((int7)((ulonglong)uVar16 >> 8),uVar5) | 0xa2;
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),0x25);
  send_mst(param_1,2,uVar14,uVar17);
  uVar15 = (undefined7)((ulonglong)uVar14 >> 8);
  uVar5 = read_mst(param_1,2);
  uVar17 = CONCAT71((int7)(uVar17 >> 8),uVar5) | 0x80;
  send_mst(param_1,2,CONCAT71(uVar15,2),uVar17);
  uVar5 = read_mst(param_1,2,7);
  send_mst(param_1,2,7,CONCAT71((int7)(uVar17 >> 8),uVar5) | 4);
  send_mst(param_1,2,0x17,0xc0);
  send_mst(param_1,2,0x19,0xff);
  send_mst(param_1,2,0x1a,0xff);
  send_mst(param_1,2,0x1b,0xfc);
  uVar14 = 0;
  send_mst(param_1,2,0x20,0);
  uVar5 = read_mst(param_1,2,0x21);
  uVar17 = CONCAT71((int7)((ulonglong)uVar14 >> 8),uVar5) & 0xfffffffffffffffc;
  send_mst(param_1,2,0x21,uVar17);
  uVar14 = CONCAT71((int7)(uVar17 >> 8),0x26);
  send_mst(param_1,2,0x22,uVar14);
  uVar14 = CONCAT71((int7)((ulonglong)uVar14 >> 8),~-(*(int *)(param_1 + 0x6854) == 0));
  send_mst(param_1,2,0x27,uVar14);
  uVar5 = read_mst(param_1,2,0x2e);
  uVar17 = CONCAT71((int7)((ulonglong)uVar14 >> 8),uVar5) | 0xa1;
  send_mst(param_1,2,0x2e,uVar17);
  uVar5 = read_mst(param_1,0,0xab);
  uVar17 = CONCAT71((int7)(uVar17 >> 8),uVar5) & 0xffffffffffffff95 | 0x15;
  send_mst(param_1,0,0xab,uVar17);
  uVar5 = read_mst(param_1,0,0xac);
  send_mst(param_1,0,0xac,CONCAT71((int7)(uVar17 >> 8),uVar5) & 0xffffffffffffffd5 | 0x15);
  if (*(uint *)(param_1 + 0x6840) < 2) {
    FUN_14024b39c(param_1,0);
    FUN_140249e94(param_1);
    FUN_14024a5cc(param_1);
    lVar3 = *(longlong *)(param_1 + 0x120);
    cVar1 = *(char *)(lVar3 + 0xf);
    if (((((cVar1 == -0xb) && (*(char *)(lVar3 + 0xe) == '\a')) ||
         (bVar6 = *(byte *)(lVar3 + 0xe), bVar6 == 0xc)) ||
        (((byte)(bVar6 - 0x21) < 0x3c &&
         ((0x834899580001121U >> ((ulonglong)(bVar6 - 0x21) & 0x3f) & 1) != 0)))) ||
       (((byte)(bVar6 + 0x60) < 0x2d &&
        ((0x10290000d32bU >> ((ulonglong)(bVar6 + 0x60) & 0x3f) & 1) != 0)))) {
LAB_14024af58:
      uVar14 = 0x81;
LAB_14024af5b:
      send_mst(param_1,0,0x51,uVar14);
      FUN_14024b39c(param_1,3);
LAB_14024af73:
      uVar14 = 1;
LAB_14024af75:
      FUN_1402499b4(param_1,uVar14);
    }
    else {
      if ((((cVar1 == '\x1c') && (bVar6 == 0xfa)) || ((cVar1 == '\0' && ((bVar6 - 3 & 0xfd) == 0))))
         || (((byte)(bVar6 + 0xa2) < 2 || ((byte)(bVar6 + 0x32) < 2)))) {
LAB_14024af3e:
        send_mst(param_1,0,0x51,0x89);
        uVar14 = 0x30;
LAB_14024ae4f:
        FUN_14024b39c(param_1,uVar14);
        uVar14 = 0;
        goto LAB_14024af75;
      }
      uVar7 = *(ushort *)(lVar3 + 8);
      uVar17 = (ulonglong)uVar7;
      if ((((uVar7 == 0x4bb) && ((*(ushort *)(lVar3 + 10) & 0xfff) == 0x543)) ||
          ((((uVar7 == 0xfd9 && (uVar8 = *(short *)(lVar3 + 10) - 0x4f, uVar8 < 0x26)) &&
            ((0x2000008001U >> ((ulonglong)uVar8 & 0x3f) & 1) != 0)) ||
           ((uVar7 == 0x17ef && (*(short *)(lVar3 + 10) == 0x7219)))))) ||
         ((uVar7 == 0x1164 &&
          (uVar17 = 0x535, (ushort)((*(ushort *)(lVar3 + 10) & 0xfff) - 0x535) < 4)))) {
        uVar14 = 0x89;
        goto LAB_14024af5b;
      }
      if ((((bVar6 == 4) && (cVar1 == '\a')) || ((bVar6 == 10 && (cVar1 == '\a')))) ||
         (((bVar6 - 0x16 & 0xf6) == 0 && (bVar6 != 0x1e)))) goto LAB_14024af58;
      uVar15 = (undefined7)(uVar17 >> 8);
      if (cVar1 == 'u') {
        if (bVar6 == 0x81) {
          send_mst(param_1,0,0x51,CONCAT71(uVar15,0x81));
          uVar14 = 3;
          goto LAB_14024ae4f;
        }
        if (bVar6 == 0x80) goto LAB_14024af3e;
      }
      if (*(short *)(lVar3 + 10) == -0xacf) {
        uVar14 = CONCAT71(uVar15,0x81);
LAB_14024ae78:
        send_mst(param_1,0,0x51,uVar14);
        uVar14 = 0x30;
LAB_14024ae8a:
        FUN_14024b39c(param_1,uVar14);
      }
      else {
        iVar13 = *(int *)(param_1 + 0x6840);
        if (*(short *)(lVar3 + 10) == -0xacd) {
          if (iVar13 == 0) {
            send_mst(param_1,0,0x51,CONCAT71(uVar15,0x81));
            FUN_14024b39c(param_1,3);
            iVar13 = *(int *)(param_1 + 0x6840);
          }
          if (iVar13 == 1) {
            uVar14 = 0x89;
            goto LAB_14024ae78;
          }
        }
        else {
          if (iVar13 == 0) {
            send_mst(param_1,0,0x51,CONCAT71(uVar15,0x89));
            FUN_14024b39c(param_1,0x30);
            iVar13 = *(int *)(param_1 + 0x6840);
          }
          if (iVar13 == 1) {
            send_mst(param_1,0,0x51,0x81);
            uVar14 = 3;
            goto LAB_14024ae8a;
          }
        }
      }
      iVar13 = *(int *)(param_1 + 0x6854);
      if (iVar13 == 0) {
        FUN_1402499b4(param_1,0);
        iVar13 = *(int *)(param_1 + 0x6854);
      }
      if (iVar13 == 1) goto LAB_14024af73;
    }
    send_mst(param_1,0,0xb7,0);
    FUN_140249ec8(param_1);
  }
  if (*(int *)(param_1 + 0x6840) - 2U < 2) {
    lVar3 = *(longlong *)(param_1 + 0x120);
    bVar6 = *(byte *)(lVar3 + 0xe);
    if (((((bVar6 == 4) && (*(char *)(lVar3 + 0xf) == '\a')) ||
         ((bVar6 == 10 && (*(char *)(lVar3 + 0xf) == '\a')))) ||
        (((byte)(bVar6 - 0x16) < 2 ||
         (((byte)(bVar6 - 0x1f) < 0x3e &&
          ((0x20d2675e000044d5U >> ((ulonglong)(bVar6 - 0x1f) & 0x3f) & 1) != 0)))))) ||
       (((byte)(bVar6 + 0x60) < 0x2d &&
        ((0x10290000f3afU >> ((ulonglong)(byte)(bVar6 + 0x60) & 0x3f) & 1) != 0)))) {
      uVar11 = 3;
    }
    else if ((*(short *)(lVar3 + 8) == 0x5ca) && (*(short *)(lVar3 + 10) == 0x901)) {
      uVar11 = 0x11;
    }
    FUN_14024b39c(param_1,uVar11);
    FUN_140249e94(param_1);
    FUN_14024a5cc(param_1);
    lVar3 = *(longlong *)(param_1 + 0x120);
    if (((((*(char *)(lVar3 + 0xf) == -0xb) && ((byte)(*(char *)(lVar3 + 0xe) - 5U) < 2)) ||
         (bVar6 = *(byte *)(lVar3 + 0xe), bVar6 == 0xc)) ||
        ((bVar6 == 0x16 || ((*(char *)(lVar3 + 0xf) == 'u' && (bVar6 == 0x81)))))) ||
       ((((byte)(bVar6 - 0x23) < 0x3a &&
         ((0x20c265560000445U >> ((ulonglong)(bVar6 - 0x23) & 0x3f) & 1) != 0)) ||
        (((byte)(bVar6 + 0x60) < 0x2d &&
         ((0x10210000f2abU >> ((ulonglong)(byte)(bVar6 + 0x60) & 0x3f) & 1) != 0)))))) {
LAB_14024b0d8:
      send_mst(param_1,0,0x51,1);
      FUN_1402499b4(param_1,1);
    }
    else {
      iVar13 = *(int *)(param_1 + 0x6840);
      if (iVar13 == 2) {
        uVar4 = 1;
        if (*(int *)(param_1 + 0x7658) != 1) {
          uVar4 = 0x21;
        }
        send_mst(param_1,0,0x51,uVar4);
        FUN_1402499b4(param_1,1);
        iVar13 = *(int *)(param_1 + 0x6840);
      }
      if (iVar13 == 3) goto LAB_14024b0d8;
    }
    FUN_140248e10(param_1);
  }
  if (*(int *)(param_1 + 0x8c34) == 1) {
    return 1;
  }
  if (*(int *)(param_1 + 0x6840) - 2U < 2) {
    if (*(int *)(param_1 + 0x8c7c) == 0) {
      DbgPrint("MST3367 DELAY 2\n");
      uVar11 = 1000;
      goto LAB_14024b144;
    }
    pcVar10 = "MST3367 DELAY 1\n";
  }
  else {
    pcVar10 = "MST3367 DELAY 4\n";
  }
  DbgPrint(pcVar10);
  uVar11 = 300;
LAB_14024b144:
  FUN_140001220(uVar11);
  return 1;
}


void FUN_140251a48(longlong param_1,byte param_2,char param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  
  if (1 < (byte)(param_3 + 0xbbU)) {
    bVar1 = param_2 - 0xc;
    if (param_2 < 0xd) {
      bVar1 = param_2;
    }
    bVar3 = read_mst(*(undefined8 *)(param_1 + 0x1c8),0,0xb2);
    bVar4 = read_mst(*(undefined8 *)(param_1 + 0x1c8),0,0xb5);
    bVar2 = bVar3 & 0xf7 | 8;
    if (bVar1 < 6) {
      bVar2 = bVar3 & 0xf7;
    }
    send_mst(*(undefined8 *)(param_1 + 0x1c8),0,0xb2,bVar2);
    bVar2 = bVar1 - 6;
    if (bVar1 < 6) {
      bVar2 = bVar1;
    }
    send_mst(*(undefined8 *)(param_1 + 0x1c8),0,0xb5,bVar2 << 2 | bVar4 & 0xc3);
  }
  return;
}



undefined8 FUN_140248e10(longlong param_1)

{
  longlong lVar1;
  byte bVar2;
  undefined uVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  
  lVar1 = *(longlong *)(param_1 + 0x1c528);
  send_mst(param_1,0,0,0x80);
  send_mst(param_1,0,0x24,0xc0);
  uVar7 = 0;
  send_mst(param_1,0,0,0);
  uVar3 = read_mst(param_1,0,0x21);
  uVar8 = CONCAT71((int7)((ulonglong)uVar7 >> 8),uVar3) & 0xfffffffffffffff9 | 1;
  send_mst(param_1,0,0x21,uVar8);
  uVar7 = CONCAT71((int7)(uVar8 >> 8),*(char *)(lVar1 + 0x1cd8) << 2);
  send_mst(param_1,0,4,uVar7);
  uVar3 = read_mst(param_1,0,0x10);
  send_mst(param_1,0,0x10,CONCAT71((int7)((ulonglong)uVar7 >> 8),uVar3) & 0xffffffffffffff0f | 0xd0)
  ;
  send_mst(param_1,0,0x11,0x2d);
  send_mst(param_1,0,0x20,0xc0);
  uVar6 = 0x44;
  if (*(int *)(param_1 + 0x8d10) == 0) {
    uVar6 = 4;
  }
  uVar8 = (ulonglong)uVar6;
  send_mst(param_1,0,0x21,uVar8);
  bVar4 = read_mst(param_1,0,0xe);
  iVar5 = *(int *)(param_1 + 0x6840);
  if (iVar5 == 2) {
    send_mst(param_1,0,0xe,CONCAT71((int7)(uVar8 >> 8),bVar4) & 0xffffffffffffffef | 0x30);
    iVar5 = *(int *)(param_1 + 0x6840);
  }
  if (iVar5 == 3) {
    bVar2 = bVar4 & 0xef | 0x20;
    if (*(int *)(param_1 + 0x7654) != 0) {
      bVar2 = bVar4 & 0xef | 0x30;
    }
    send_mst(param_1,0,0xe,bVar2);
  }
  return 1;
}


undefined8 FUN_140249e94(undefined8 param_1)

{
  send_mst(param_1,0,0xb8,0x10);
  send_mst(param_1,0,0xb8,0);
  return 1;
}


undefined8 FUN_14024a5cc(undefined8 param_1)

{
  send_mst(param_1,2,7,0xf4);
  send_mst(param_1,2,7,4);
  return 1;
}


undefined8 FUN_14024b39c(longlong param_1,uint param_2)

{
  short sVar1;
  longlong lVar2;
  undefined7 uVar3;
  byte bVar4;
  ushort uVar5;
  uint uVar6;
  byte bVar7;
  ulonglong uVar8;
  
  lVar2 = *(longlong *)(param_1 + 0x120);
  sVar1 = *(short *)(lVar2 + 8);
  if (((((sVar1 != 0x4bb) || ((*(ushort *)(lVar2 + 10) & 0xfff) != 0x543)) &&
       ((sVar1 != 0xfd9 ||
        ((uVar5 = *(short *)(lVar2 + 10) - 0x4f, 0x25 < uVar5 ||
         ((0x2000008001U >> ((ulonglong)uVar5 & 0x3f) & 1) == 0)))))) &&
      ((sVar1 != 0x17ef || (*(short *)(lVar2 + 10) != 0x7219)))) &&
     ((sVar1 != 0x1164 || (3 < (ushort)((*(ushort *)(lVar2 + 10) & 0xfff) - 0x535))))) {
    uVar6 = FUN_14022809c(param_1,0xf01,0);
    uVar8 = (ulonglong)((byte)uVar6 & 0xfe);
    if ((param_2 & 1) == 0) {
      uVar8 = (ulonglong)(uVar6 | 1);
    }
    uVar3 = (undefined7)(uVar8 >> 8);
    bVar7 = (byte)uVar8 & 0xfd;
    if ((param_2 & 0x10) == 0) {
      bVar7 = (byte)uVar8 | 2;
    }
    uVar8 = CONCAT71(uVar3,bVar7);
    if ((*(short *)(*(longlong *)(param_1 + 0x120) + 8) == 0x5ca) &&
       (*(short *)(*(longlong *)(param_1 + 0x120) + 10) == 0x901)) {
      uVar8 = CONCAT71(uVar3,bVar7) & 0xfffffffffffffffd;
    }
    FUN_14022e3cc(param_1,1,uVar8);
    FUN_14022e3cc(param_1,0x11,0xfc);
  }
  bVar4 = read_mst(param_1,0,0xb7);
  bVar7 = bVar4 & 0xfd;
  if ((param_2 & 2) == 0) {
    bVar7 = bVar4 | 2;
  }
  bVar4 = bVar7 & 0xfd;
  if ((param_2 & 0x20) == 0) {
    bVar4 = bVar7;
  }
  send_mst(param_1,0,0xb7,bVar4);
  return 1;
}


void FUN_1402499b4(undefined8 param_1,int param_2)

{
  byte bVar1;
  byte bVar2;

  bVar2 = FUN_14022809c(param_1,0x20,0);
  bVar1 = bVar2 | 0x10;
  if (param_2 != 1) {
    bVar1 = bVar2 & 0xef;
  }
  FUN_14022e3cc(param_1,0x20,bVar1);
  return;
}


void FUN_14022e3cc(undefined8 param_1,undefined param_2,undefined param_3)

{
  undefined local_res18 [16];
  
  local_res18[0] = param_3;
  i2c_write(param_1,0x98,param_2,local_res18,1);
  return;
}

