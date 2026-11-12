    if (((uVar34 == 0) || (iVar35 == 0)) || (iVar19 == 0)) {
      send_mst(param_1,0,CONCAT71(uVar40,0xe2),
               CONCAT71((uint7)(uint3)(int3)(char)((ushort)*psVar1 >> 8),0x80));
      send_mst(param_1,0,0xe3,8);
      send_mst(param_1,0,0xe4,0);
      read_mst(param_1,0,0x6c);
      read_mst(param_1,0,0x6d);
      if ((ulonglong)local_84 * 10000 < 10000) {
        uVar22 = 1;
      }
      else {
        uVar22 = ((ulonglong)local_84 * 10000) / 10000;
      }
      FUN_140001220(uVar22 & 0xffffffff);
      bVar10 = read_mst(param_1,0,0xf4);
      bVar12 = read_mst(param_1,0,0xf3);
      local_res10 = CONCAT44(local_res10._4_4_,(uint)bVar12 | (bVar10 & 0xf) << 8);
      bVar10 = read_mst(param_1,0,0xf6);
      bVar12 = read_mst(param_1,0,0xf5);
      local_80 = (uint)bVar12 | (bVar10 & 0xf) << 8;
      bVar10 = read_mst(param_1,0,0xf8);
      bVar12 = read_mst(param_1,0,0xf7);
      local_84 = (uint)bVar12 | (bVar10 & 0xf) << 8;
      bVar10 = read_mst(param_1,0,0xfa);
      bVar12 = read_mst(param_1,0,0xf9);
      uVar18 = (int)local_res10 + 0xc;
      uVar42 = (uint)bVar12 | (bVar10 & 0xf) << 8;
      local_50 = (ulonglong)((local_80 - (int)local_res10) + 1);
      if ((0xffe < local_80) && (local_50 != (local_78 & 0xfff))) {
        local_50 = local_78 & 0xfff;
      }
      uVar23 = (ulonglong)local_84;
      local_78 = local_78 & 0xffffffff00000ff8;
      local_50 = local_50 & 0xfffffff8;
      uVar20 = (uVar42 - local_84) + 1;
      local_58 = (ulonglong)uVar20;
      uVar22 = local_res10 & 0xffffffff;
      lVar37 = local_58 * local_50;
      local_res10 = CONCAT44(local_res10._4_4_,uVar20);
      DbgPrint("MST3367_HDMI_MODE_DETECT_AUTO( %d ? %d ? %d ? %d ? %d ? %d ? %d )",uVar22,local_80,
               uVar23,CONCAT44(uVar17,uVar42),CONCAT44(uVar53,uVar18 / 0x18 << 3),
               CONCAT44(uVar16,(int)local_50),CONCAT44(uVar51,uVar20));
      uVar18 = *(uint *)(param_1 + 0x1e40) >> 1;
      if (uVar18 < 0x2a3001) {
        uVar18 = 0x2a3000;
      }
      if (((lVar37 - (ulonglong)uVar18 == 0 || lVar37 < (longlong)(ulonglong)uVar18) &&
          (local_50 == (local_78 & 0xffffffff))) && ((1 < local_50 && (1 < local_58)))) {
        iVar35 = (int)local_50;
        *(int *)(uVar31 + 0x4c) = local_88;
        uVar34 = (uVar43 + 5) / 10;
        iVar19 = (int)local_res10;
        if ((uVar34 * (int)local_res10 * iVar35 < 0x4c4b401) &&
           ((uint)((int)local_res10 * iVar35) < 0x1fa401)) {
          *(undefined4 *)(uVar31 + 100) = 0;
        }
        else {
          *(undefined4 *)(uVar31 + 100) = 1;
        }
      }
    }
    else {
      *(undefined4 *)(uVar31 + 0x4c) = 0;
      uVar23 = 0;
      *(undefined4 *)(uVar31 + 100) = 0;
      send_mst(param_1,0,CONCAT71(uVar40,0xe2),0);
    }
    if ((int)local_res8 != 0) {
      *(undefined4 *)(uVar31 + 0x4c) = 1;
      *(undefined4 *)(uVar31 + 100) = 1;
    }
    if (((iVar35 == 0) || (iVar19 == 0)) ||
       ((uVar34 != 0 &&
        (((*(int *)(param_1 + 0x8bf0) == 1 &&
          (*(char *)(*(longlong *)(param_1 + 0x120) + 0xe) == '\f')) &&
         (0x4f1a000 < uVar34 * iVar19 * iVar35)))))) goto LAB_14024f7d0;
    uVar16 = FUN_140249c74(param_1);
    if (((*(int *)(uVar31 + 0x30) != iVar35) || (*(int *)(uVar31 + 0x34) != iVar19)) ||
       (*(uint *)(uVar31 + 0x38) != uVar34)) {
      if (((*(int *)(uVar31 + 0x30) == 0) || (*(int *)(uVar31 + 0x34) == 0)) ||
         (*(int *)(uVar31 + 0x38) == 0)) {
        uVar11 = read_mst(param_1,2,7);
        uVar22 = CONCAT71((int7)(uVar23 >> 8),uVar11) | 0x10;
        send_mst(param_1,2,7,uVar22);
        send_mst(param_1,2,7,CONCAT71((int7)(uVar22 >> 8),uVar11) & 0xffffffffffffffef);
      }
      *(int *)(uVar31 + 0x30) = iVar35;
      *(int *)(uVar31 + 0x34) = iVar19;
      *(uint *)(uVar31 + 0x38) = uVar34;
      *(undefined4 *)(uVar31 + 0x3c) = uVar16;
      if (((((iVar35 == 0x2d0) && ((iVar19 == 0xf0 || (iVar19 == 0x120)))) ||
           ((iVar35 == 0x5a0 && ((iVar19 == 0xf0 || (iVar19 == 0x120)))))) ||
          (((iVar35 == 0x300 && (iVar19 == 0x120)) || ((iVar35 == 0x5a0 && (iVar19 == 0x21c)))))) ||
         ((iVar35 == 0x780 && (iVar19 == 0x21c)))) {
        uVar16 = 1;
      }
      else {
        uVar16 = 0;
      }
      *(undefined4 *)(uVar31 + 0x40) = uVar16;
      local_res18 = 1;
    }
    bVar10 = read_mst(param_1,2,0x49);
    bVar12 = read_mst(param_1,2,0x4a);
    *(uint *)(uVar31 + 0x58) = (uint)(bVar10 >> 6);
    uVar18 = bVar12 >> 2 & 3;
    iVar35 = FUN_14024a600(param_1);
    if ((*(int *)(uVar31 + 0x60) != iVar35) || (*(uint *)(uVar31 + 0x5c) != uVar18)) {
      *(int *)(uVar31 + 0x60) = iVar35;
      *(uint *)(uVar31 + 0x5c) = uVar18;
      send_csc_maybe(param_1);
      send_csc_inner(param_1,*(undefined *)(param_1 + 0x64d0),*(undefined *)(param_1 + 0x6550),
                     *(undefined *)(param_1 + 0x6610),*(undefined *)(param_1 + 0x65d0),
                     *(byte *)(param_1 + 0x6650) >> 5);
    }
