
/* WARNING: Removing unreachable block (ram,0x00014024df3e) */

undefined8 FUN_14024b514(ulonglong param_1)

{
  uVar16 = (undefined4)((ulonglong)in_stack_ffffffffffffff58 >> 0x20);
  uVar50 = (undefined4)((ulonglong)in_stack_ffffffffffffff60 >> 0x20);
  uVar18 = 0;
  uVar30 = *(ulonglong *)(param_1 + 0x1c528);
  local_6c = 0x270;
  local_res8 = param_1;
  local_78 = uVar30;
  if (*(int *)(param_1 + 0x6840) - 2U < 2) {
    puVar49 = &local_60;
    local_68 = 0;
    puVar47 = &local_res10;
    local_64 = 0;
    piVar48 = &local_88;
    local_res18 = 0;
    puVar46 = &local_70;
    local_70 = 0;
    local_58 = local_58 & 0xffffffff00000000;
    local_5c = 0;
    local_88 = 0;
    local_res10 = local_res10 & 0xffffffff00000000;
    local_60 = 0;
    uVar22 = FUN_140248f68(param_1,&local_68,&local_64,&local_res18,puVar46,piVar48,puVar47,puVar49)
    ;
    uVar16 = (undefined4)((ulonglong)puVar47 >> 0x20);
    uVar50 = (undefined4)((ulonglong)puVar49 >> 0x20);
    local_84 = 0;
    if (uVar22 == 0x123456789abcdef) {
      return 0;
    }
    if ((longlong)uVar22 < 0) {
      uVar20 = (uint)uVar22;
      local_80 = uVar20 & 0xfff;
      uVar33 = (uint)(uVar22 >> 0x10) & 0xfff;
      local_50 = (ulonglong)uVar33;
      local_res10 = CONCAT44(local_res10._4_4_,uVar20) & 0xffffffff00000fff;
      iVar34 = 0;
      uVar15 = (ushort)(uVar22 >> 0x30) & 1;
      uVar25 = (uint)(uVar22 >> 0x20);
      uVar36 = uVar25 & 0xfff;
      local_7c = *(uint *)(uVar30 + 0x1ce4);
      local_res20 = 0;
      uVar42 = 0;
      uVar25 = uVar25 >> 0x11;
      uVar41 = uVar25 & 3;
      bVar10 = (byte)(uVar22 >> 0x34) & 3;
      if ((local_7c != 0xffff) && ((byte)(*(char *)(uVar30 + 0x1f88) - 2U) < 2)) {
        if (*(char *)(uVar30 + 0x1f89) == '\x01') {
          uVar41 = local_80 + *(int *)(uVar30 + 0x1f8c);
LAB_14024b6ca:
          local_res10 = CONCAT44(local_res10._4_4_,uVar41);
        }
        else if (*(char *)(uVar30 + 0x1f89) == '\x03') {
          if (local_80 == 0x46a) {
            local_res10 = CONCAT44(local_res10._4_4_,0x465);
          }
          else if (local_80 == 0x2f3) {
            local_res10 = CONCAT44(local_res10._4_4_,0x2ee);
          }
          else if (local_80 - 0x241 < 3) {
            local_res10 = CONCAT44(local_res10._4_4_,0x232);
          }
          else {
            if (2 < local_80 - 0x10f) {
              uVar41 = local_80;
              if (local_80 - 0x13f < 3) {
                uVar41 = 0x138;
              }
              goto LAB_14024b6ca;
            }
            local_res10 = CONCAT44(local_res10._4_4_,0x106);
          }
        }
        uVar41 = *(uint *)(uVar30 + 0x54);
      }
      if ((*(uint *)(uVar30 + 0x50) < (int)local_res10 + uVar15 * -2) ||
         ((int)local_res10 + uVar15 * 2 < *(uint *)(uVar30 + 0x50))) {
LAB_14024b739:
        *(char *)(uVar30 + 0x1f8a) = (char)uVar15;
        *(byte *)(uVar30 + 0x1f88) = bVar10;
        *(undefined4 *)(uVar30 + 0x1ce4) = 0xffff;
        local_res10 = CONCAT44(local_res10._4_4_,uVar20) & 0xffffffff00000fff;
        puVar46 = (uint *)(CONCAT44((int)((ulonglong)puVar46 >> 0x20),uVar25) & 0xffffffff00000003);
        uVar16 = FUN_140250920(param_1,*(undefined4 *)(param_1 + 0x6840),local_80,
                               (ulonglong)(uVar36 + 3) / 10,puVar46);
        *(undefined4 *)(uVar30 + 0x1ce4) = uVar16;
        uVar37 = 8;
        if ((byte)(*(char *)(uVar30 + 0x1f88) - 2U) < 2) {
          uVar37 = 0x20;
        }
        send_mst(param_1,0,0xf,uVar37);
      }
      else {
        uVar28 = (uVar36 + 3) / 10;
        if ((*(int *)(uVar30 + 0x38) + 1U < uVar28) ||
           (((((uVar28 < *(int *)(uVar30 + 0x38) - 1U || (*(byte *)(uVar30 + 0x1f88) != bVar10)) ||
              (*(byte *)(uVar30 + 0x1f8a) != uVar15)) ||
             ((*(uint *)(uVar30 + 0x54) != uVar41 && (bVar10 == 1)))) || (local_7c == 0xffff))))
        goto LAB_14024b739;
      }
      uVar16 = (undefined4)((ulonglong)puVar47 >> 0x20);
      uVar50 = (undefined4)((ulonglong)puVar49 >> 0x20);
      uVar20 = *(uint *)(uVar30 + 0x1ce4);
      uVar41 = local_res18;
      if (uVar20 != 0xffff) {
        if (*(int *)(param_1 + 0x6840) == 2) {
          if (uVar20 < 0x1a) {
            lVar26 = (ulonglong)uVar20 * 0x4c;
            local_res20 = *(int *)(&DAT_14030382c + lVar26);
            uVar18 = *(uint *)(&DAT_140303838 + lVar26);
            iVar34 = *(int *)(&DAT_14030383c + lVar26);
            uVar42 = *(uint *)(&DAT_140303840 + lVar26);
            *(undefined4 *)(uVar30 + 0x4c) = *(undefined4 *)(&DAT_140303828 + lVar26);
            uVar17 = *(undefined4 *)(&DAT_140303844 + lVar26);
LAB_14024b840:
            *(undefined4 *)(uVar30 + 0x54) = uVar17;
            goto LAB_14024b84f;
          }
        }
        else if (uVar20 < 0x1a9) {
          lVar26 = (ulonglong)uVar20 * 0x4c;
          local_res20 = *(int *)(&DAT_14030b65c + lVar26);
          uVar18 = *(uint *)(&DAT_14030b668 + lVar26);
          iVar34 = *(int *)(&DAT_14030b66c + lVar26);
          uVar42 = *(uint *)(&DAT_14030b670 + lVar26);
          *(undefined4 *)(uVar30 + 0x4c) = *(undefined4 *)(&DAT_14030b658 + lVar26);
          uVar17 = *(undefined4 *)(&DAT_14030b674 + lVar26);
          goto LAB_14024b840;
        }
        goto LAB_14024d08b;
      }
      if (*(int *)(param_1 + 0x6840) != 3) goto LAB_14024d08b;
LAB_14024d08b:
      *(undefined8 *)(param_1 + 0x75dc) = 0;
      *(undefined4 *)(param_1 + 0x75e4) = 0;
      *(undefined4 *)(param_1 + 0x7a10) = 0;
      *(undefined4 *)(param_1 + 0x6758) = 0;
LAB_14024d0a8:
      uVar18 = 0;
    }
    *(uint *)(param_1 + 0x67f4) = uVar18;
    if (local_84 != 0) {
      uVar37 = 0;
      uVar11 = FUN_14022809c(param_1,0x20,0);
      local_res20 = CONCAT31(local_res20._1_3_,uVar11);
      FUN_14022e3cc(param_1,0x20,
                    CONCAT71((int7)((ulonglong)uVar37 >> 8),uVar11) & 0xfffffffffffffffe);
      uVar11 = read_mst(param_1,0,0xab);
      local_res18 = CONCAT31(local_res18._1_3_,uVar11) & 0xffffff7f;
      send_mst(param_1,0,0xab);
      iVar34 = *(int *)(param_1 + 0x6840);
      uVar18 = *(uint *)(uVar30 + 0x1ce4);
      uVar42 = 0x19;
      if (iVar34 == 3) {
        uVar42 = 0x1a8;
      }
      if (uVar18 == 0xffff) {
        if (*(int *)(uVar30 + 0x4c) == 0) {
          uVar18 = uVar42 - 1;
          do {
            lVar26 = (ulonglong)uVar18 * 0x4c;
            param_1 = local_res8;
            if (iVar34 == 3) {
              if (((*(int *)(&DAT_14030b668 + lVar26) == *(int *)(uVar30 + 0x30)) &&
                  (*(int *)(&DAT_14030b66c + lVar26) == *(int *)(uVar30 + 0x34))) &&
                 (*(int *)(&DAT_14030b670 + lVar26) == *(int *)(uVar30 + 0x38))) break;
            }
            else if (((*(int *)(&DAT_140303838 + lVar26) == *(int *)(uVar30 + 0x30)) &&
                     (*(int *)(&DAT_14030383c + lVar26) == *(int *)(uVar30 + 0x34))) &&
                    (*(int *)(&DAT_140303840 + lVar26) == *(int *)(uVar30 + 0x38))) break;
            uVar18 = uVar18 - 1;
          } while (uVar18 != 0);
        }
        else {
          lVar26 = (ulonglong)uVar42 * 0x4c;
          bVar44 = iVar34 != 3;
          puVar24 = &DAT_14030b640;
          if (bVar44) {
            puVar24 = &DAT_140303810;
          }
          *(undefined4 *)(puVar24 + lVar26) = 0xe8;
          puVar24 = &DAT_14030b644;
          if (bVar44) {
            puVar24 = &DAT_140303814;
          }
          *(undefined4 *)(puVar24 + lVar26) = 8;
          puVar24 = &DAT_14030b648;
          if (bVar44) {
            puVar24 = &DAT_140303818;
          }
          *(undefined4 *)(puVar24 + lVar26) = 0x30;
          puVar24 = &DAT_14030b64c;
          if (bVar44) {
            puVar24 = &DAT_14030381c;
          }
          *(undefined4 *)(puVar24 + lVar26) = 0x60;
          puVar24 = &DAT_14030b650;
          if (bVar44) {
            puVar24 = &DAT_140303820;
          }
          *(undefined4 *)(puVar24 + lVar26) = 0;
          puVar24 = &DAT_14030b654;
          if (bVar44) {
            puVar24 = &DAT_140303824;
          }
          *(undefined4 *)(puVar24 + lVar26) = 0;
          puVar24 = &DAT_14030b658;
          if (bVar44) {
            puVar24 = &DAT_140303828;
          }
          puVar27 = &DAT_14030b65c;
          *(uint *)(puVar24 + lVar26) = uVar41;
          if (bVar44) {
            puVar27 = &DAT_14030382c;
          }
          *(uint *)(puVar27 + lVar26) = local_70;
          puVar24 = &DAT_14030b660;
          if (bVar44) {
            puVar24 = &DAT_140303830;
          }
          *(int *)(puVar24 + lVar26) = (int)local_58;
          puVar24 = &DAT_14030b664;
          if (bVar44) {
            puVar24 = &DAT_140303834;
          }
          *(int *)(puVar24 + lVar26) = local_5c;
          uVar18 = uVar42;
        }
        if (((*(int *)(param_1 + 0x8c04) != 0) && (*(int *)(param_1 + 0x6840) == 3)) &&
           ((lVar26 = (ulonglong)uVar18 * 0x4c, *(int *)(&DAT_14030b668 + lVar26) == 0x640 &&
            ((*(int *)(&DAT_14030b66c + lVar26) == 0x4b0 &&
             (*(int *)(&DAT_14030b670 + lVar26) == 0x3c)))))) {
          *(undefined4 *)(&DAT_14030b658 + lVar26) = 0x84e;
        }
      }
      else {
        if (iVar34 == 3) {
          bVar44 = uVar18 < 0x1a8;
          bVar45 = uVar18 == 0x1a8;
        }
        else {
          bVar44 = uVar18 < 0x19;
          bVar45 = uVar18 == 0x19;
        }
        if (!bVar44 && !bVar45) {
          *(undefined4 *)(uVar30 + 0x1ce4) = 0xffff;
          return 0;
        }
      }
      uVar22 = (ulonglong)uVar18;
      lVar26 = uVar22 * 0x4c;
      uVar17 = CONCAT31((int3)((uint)iVar34 >> 8),3);
      if (*(int *)(param_1 + 0x6840) == 3) {
      }
      else {
        send_mst(param_1,0,uVar17,(&DAT_140303810)[lVar26]);
        send_mst(param_1,0,5,(&DAT_140303814)[lVar26]);
        send_mst(param_1,0,6,(&DAT_140303818)[lVar26]);
        send_mst(param_1,0,7,(&DAT_14030381c)[lVar26]);
        send_mst(param_1,0,0x1e,(&DAT_140303820)[lVar26]);
        send_mst(param_1,0,0x1f,(&DAT_140303824)[lVar26]);
        if (*(int *)(uVar30 + 0x4c) != 0) {
          if (((uint)(*(int *)(uVar30 + 0x34) * *(int *)(uVar30 + 0x30) * *(int *)(uVar30 + 0x38)) <
               0x4c4b401) && ((uint)(*(int *)(uVar30 + 0x34) * *(int *)(uVar30 + 0x30)) < 0x1fa401))
          {
            *(undefined4 *)(uVar30 + 100) = 0;
          }
          else {
            *(undefined4 *)(uVar30 + 100) = 1;
          }
        }
        iVar34 = *(int *)(&DAT_140303828 + lVar26);
        iVar21 = *(int *)(uVar30 + 0x1bec + uVar22 * 4);
        *(int *)(uVar30 + 0x1cc8) = iVar34;
        iVar34 = iVar34 + iVar21;
        send_mst(param_1,0,1,iVar34 + -1 >> 4);
        iVar34 = iVar34 + -1;
        uVar38 = (ulonglong)CONCAT31((int3)((uint)iVar34 >> 8),(char)iVar34 << 4);
        send_mst(param_1,0,2,uVar38);
        uVar11 = read_mst(param_1,0,0x10);
        uVar38 = CONCAT71((int7)(uVar38 >> 8),uVar11) | 5;
        send_mst(param_1,0,0x10,uVar38);
        uVar11 = read_mst(param_1,0,0xf);
        uVar38 = CONCAT71((int7)(uVar38 >> 8),uVar11) | 0x20;
        send_mst(param_1,0,0xf,uVar38);
        uVar37 = CONCAT71((int7)(uVar38 >> 8),4);
        send_mst(param_1,0,0x12,uVar37);
        uVar11 = read_mst(param_1,0,0x17);
        send_mst(param_1,0,0x17,CONCAT71((int7)((ulonglong)uVar37 >> 8),uVar11) | 2);
        send_mst(param_1,0,0xb,0x80);
        send_mst(param_1,0,0xc,0x60);
        send_mst(param_1,0,0xd,0x80);
        send_mst(param_1,0,8,0xa0);
        send_mst(param_1,0,9,0xc0);
        send_mst(param_1,0,10,0xa0);
        send_mst(param_1,0,0x1b,0);
        send_mst(param_1,0,0x1c,0);
        uVar37 = 0;
        send_mst(param_1,0,0x1d,0);
        uVar37 = CONCAT71((int7)((ulonglong)uVar37 >> 8),0x10);
        send_mst(param_1,0,0x18,uVar37);
        uVar37 = CONCAT71((int7)((ulonglong)uVar37 >> 8),0x10);
        send_mst(param_1,0,0x19,uVar37);
        uVar37 = CONCAT71((int7)((ulonglong)uVar37 >> 8),0x10);
        send_mst(param_1,0,0x1a,uVar37);
        uVar37 = CONCAT71((int7)((ulonglong)uVar37 >> 8),0x11);
        send_mst(param_1,0,0x2d,uVar37);
        uVar37 = CONCAT71((int7)((ulonglong)uVar37 >> 8),0x11);
        send_mst(param_1,0,0x2e,uVar37);
        uVar11 = read_mst(param_1,0,0x2f);
        send_mst(param_1,0,0x2f,CONCAT71((int7)((ulonglong)uVar37 >> 8),uVar11) | 2);
        send_mst(param_1,0,0x3a,0xc);
        send_mst(param_1,0,0x3b,8);
        bVar10 = read_mst(param_1,0,5);
        iVar34 = read_mst(param_1,0,6);
        uVar38 = (ulonglong)
                 CONCAT31((int3)(iVar34 + (uint)bVar10 >> 8),(char)(iVar34 + (uint)bVar10) + -0x78);
        send_mst(param_1,0,0x39,uVar38);
        uVar37 = CONCAT71((int7)(uVar38 >> 8),0x9d);
      }
      send_mst(param_1,0,0x2c,uVar37);
      uVar11 = read_mst(param_1,0,0x60);
      send_mst(param_1,0,0x60,CONCAT71((int7)((ulonglong)uVar37 >> 8),uVar11) & 0xfffffffffffffffb);
      uVar11 = read_mst(param_1,0,0x14);
      local_res8 = CONCAT71(local_res8._1_7_,uVar11);
      uVar11 = read_mst(param_1,0,0x80);
      local_res10 = CONCAT71(local_res10._1_7_,uVar11) & 0xfffffffffffffff0;
      if (*(int *)(param_1 + 0x6840) == 3) {
        iVar35 = *(int *)(&DAT_14030b660 + lVar26) + -1;
        iVar34 = *(int *)(&DAT_14030b664 + uVar22 * 0x4c);
        iVar21 = *(int *)(uVar30 + 0x8c + uVar22 * 4);
        iVar19 = *(int *)(uVar30 + 0x730 + uVar22 * 4);
      }
      else {
        iVar35 = *(int *)(&DAT_140303830 + lVar26);
        iVar34 = *(int *)(&DAT_140303834 + lVar26);
        iVar21 = *(int *)(uVar30 + 0x1b1c + uVar22 * 4);
        iVar19 = *(int *)(uVar30 + 0x1b84 + uVar22 * 4);
      }
      *(int *)(uVar30 + 0x1cc0) = iVar35;
      pcVar31 = "HSYNC";
      iVar35 = iVar35 + iVar21;
      *(int *)(uVar30 + 0x1cc4) = iVar34;
      *(uint *)(uVar30 + 0x1cbc) = uVar18;
      if ((local_res8 & 0x40) != 0) {
        pcVar31 = "SOG";
      }
      DbgPrint("MST3367_ADC_GET_SYNC( %s ? %02X )\n",pcVar31,local_res8 & 0xff);
      send_mst(param_1,0,0x80,
               (ulonglong)
               CONCAT21((short)((uint)iVar35 >> 0x10),(byte)((uint)iVar35 >> 8) | (byte)local_res10)
              );
      send_mst(param_1,0,0x81,(char)iVar35);
      send_mst(param_1,0,0x82,*(uint *)(uVar30 + 0x30) >> 8);
      send_mst(param_1,0,0x83,*(undefined *)(uVar30 + 0x30));
      send_mst(param_1,0,0x84,iVar19 + iVar34);
      uVar22 = (ulonglong)(*(uint *)(uVar30 + 0x34) >> 8);
      send_mst(param_1,0,0x85,uVar22);
      iVar34 = 0;
      if (*(int *)(uVar30 + 0x40) != 0) {
        uVar22 = (ulonglong)(*(uint *)(uVar30 + 0x34) >> 8) | 0x20;
        send_mst(param_1,0,0x85,uVar22);
        uVar11 = read_mst(param_1,0,0x60);
        uVar22 = CONCAT71((int7)(uVar22 >> 8),uVar11) & 0xfffffffffffffffb;
        send_mst(param_1,0,0x60,uVar22);
      }
      lVar26 = *(longlong *)(param_1 + 0x120);
      if (*(char *)(lVar26 + 0xf) == -0x1b) {
LAB_14024d9ba:
        if (*(int *)(param_1 + 0x6840) == 3) {
          if (*(int *)(uVar30 + 0x30) == 0x2d0) {
            iVar21 = *(int *)(uVar30 + 0x34);
            if (iVar21 == 0xf0) {
              bVar44 = *(int *)(uVar30 + 0x38) == 0x3c;
            }
            else {
LAB_14024d9ea:
              if (iVar21 != 0x120) goto LAB_14024da12;
              bVar44 = *(int *)(uVar30 + 0x38) == 0x32;
            }
            if (bVar44) {
              uVar11 = read_mst(param_1,0,0x60);
              send_mst(param_1,0,0x60,CONCAT71((int7)(uVar22 >> 8),uVar11) | 4);
            }
          }
          else {
            iVar21 = *(int *)(uVar30 + 0x34);
            if (*(int *)(uVar30 + 0x30) == 0x300) goto LAB_14024d9ea;
          }
        }
      }
      else {
        sVar2 = *(short *)(lVar26 + 8);
        if (sVar2 == 0x5ca) {
          if (*(short *)(lVar26 + 10) != 0x901) goto LAB_14024d950;
          goto LAB_14024d9ba;
        }
        if (sVar2 == 0x4bb) {
          if (*(short *)(lVar26 + 10) == 0x543) goto LAB_14024d9ba;
LAB_14024d98f:
          if ((sVar2 == 0x17ef) && (*(short *)(lVar26 + 10) == 0x7219)) goto LAB_14024d9ba;
        }
        else {
LAB_14024d950:
          if (sVar2 != 0xfd9) goto LAB_14024d98f;
          uVar13 = *(short *)(lVar26 + 10) - 0x4f;
          if ((uVar13 < 0x26) && ((0x2000008001U >> ((ulonglong)uVar13 & 0x3f) & 1) != 0))
          goto LAB_14024d9ba;
        }
        if ((*(ushort *)(lVar26 + 10) & 0xff0) == 0x530) goto LAB_14024d9ba;
      }
LAB_14024da12:
      send_mst(param_1,0,0x86,*(undefined *)(uVar30 + 0x34));
      if (*(int *)(param_1 + 0x6840) == 2) {
        if (((*(int *)(uVar30 + 0x30) == 0x500) && (*(int *)(uVar30 + 0x34) == 0x2d0)) &&
           ((*(int *)(uVar30 + 0x38) == 0x1e ||
            ((*(int *)(uVar30 + 0x38) == 0x19 || (*(int *)(uVar30 + 0x38) == 0x18)))))) {
          uVar37 = 0;
        }
        else {
          uVar37 = 4;
        }
        send_mst(param_1,0,0x12,uVar37);
      }
      send_mst(param_1,0,0xab,(undefined)local_res18);
      FUN_14024b244(param_1);
      FUN_140248be8(param_1);
      FUN_140249474(param_1,*(undefined *)(param_1 + 0x64d0),*(undefined *)(param_1 + 0x6550),
                    *(undefined *)(param_1 + 0x6610),*(undefined *)(param_1 + 0x65d0),
                    *(byte *)(param_1 + 0x6650) >> 5);
      *(undefined4 *)(uVar30 + 0x1cd4) = 1;
      lVar26 = *(longlong *)(param_1 + 0x120);
      bVar10 = *(byte *)(lVar26 + 0xe);
      if (bVar10 == 1) {
        if (*(char *)(lVar26 + 0xf) != '\a') {
LAB_14024daff:
          if (bVar10 != 10) goto LAB_14024db17;
          if (*(char *)(lVar26 + 0xf) == '\a') goto LAB_14024db3e;
LAB_14024db31:
          if ((*(byte *)(lVar26 + 0xf) & 0xf) != 5) goto LAB_14024dd80;
        }
LAB_14024db3e:
        iVar21 = *(int *)(uVar30 + 0x30);
        if (iVar21 == 0x500) {
          iVar19 = *(int *)(uVar30 + 0x34);
          if (iVar19 == 0x300) {
            if (*(int *)(uVar30 + 0x38) != 0x55) {
LAB_14024db60:
              if (iVar19 != 0x3c0) goto LAB_14024dbc2;
              lVar26 = 0;
              if ((*(int *)(uVar30 + 0x38) != 0x4b) && (*(int *)(uVar30 + 0x38) != 0x55))
              goto LAB_14024db79;
            }
          }
          else {
            if (iVar19 != 800) goto LAB_14024db60;
            if (*(int *)(uVar30 + 0x38) == 0x55) goto LAB_14024dba7;
LAB_14024dbc2:
            if (iVar19 != 0x400) goto LAB_14024db79;
            lVar26 = 0;
            if ((*(int *)(uVar30 + 0x38) != 0x4b) && (*(int *)(uVar30 + 0x38) != 0x55))
            goto LAB_14024dc4a;
          }
LAB_14024dba7:
          FUN_14025af80(param_1,CONCAT71((int7)((ulonglong)lVar26 >> 8),0x24),iVar19 == 0x4b0);
          iVar34 = 1;
        }
        else {
          if (iVar21 == 0x578) {
            if (*(int *)(uVar30 + 0x34) == 0x41a) {
              iVar19 = 0x41a;
              if (*(int *)(uVar30 + 0x38) != 0) goto LAB_14024dba7;
              goto LAB_14024dbf6;
            }
          }
          else {
LAB_14024dc4a:
            lVar26 = 0;
            if (iVar21 == 0x5a0) {
              if (*(int *)(uVar30 + 0x34) != 900) goto LAB_14024db79;
              iVar19 = 900;
              if ((*(int *)(uVar30 + 0x38) == 0x4b) || (*(int *)(uVar30 + 0x38) == 0x55))
              goto LAB_14024dba7;
LAB_14024dc76:
              if (iVar21 != 0x780) goto LAB_14024dc1b;
              if (*(int *)(uVar30 + 0x34) == 0x438) {
                iVar19 = 0x438;
                if (((*(int *)(uVar30 + 0x38) == 0x3c) || (*(int *)(uVar30 + 0x38) == 0x3d)) ||
                   (*(int *)(uVar30 + 0x38) == 0x32)) goto LAB_14024dba7;
                goto LAB_14024dcaa;
              }
LAB_14024dcb2:
              iVar19 = *(int *)(uVar30 + 0x34);
LAB_14024dcb6:
              if (iVar19 == 0x4b0) {
                iVar19 = 0x4b0;
                if (*(int *)(uVar30 + 0x38) != 0) goto LAB_14024dba7;
LAB_14024dccb:
                if ((iVar21 == 0xf00) && (*(int *)(uVar30 + 0x34) == 0x400)) {
                  iVar19 = 0x400;
                  goto LAB_14024dc36;
                }
              }
            }
            else {
LAB_14024dbf6:
              if (iVar21 != 0x690) goto LAB_14024dc76;
              if (*(int *)(uVar30 + 0x34) != 0x41a) goto LAB_14024db79;
              iVar19 = 0x41a;
              if ((*(int *)(uVar30 + 0x38) == 0x3c) || (*(int *)(uVar30 + 0x38) == 0x32))
              goto LAB_14024dba7;
LAB_14024dc1b:
              if (iVar21 != 0x640) {
LAB_14024dcaa:
                if (iVar21 == 0x780) goto LAB_14024dcb2;
                goto LAB_14024dccb;
              }
              iVar19 = *(int *)(uVar30 + 0x34);
              if (iVar19 != 900) goto LAB_14024dcb6;
LAB_14024dc36:
              if (*(int *)(uVar30 + 0x38) != 0) goto LAB_14024dba7;
            }
          }
LAB_14024db79:
          if (*(int *)(uVar30 + 0x4c) != 0) {
            iVar34 = *(int *)(uVar30 + 100);
            FUN_14025af80(param_1,CONCAT71((int7)((ulonglong)lVar26 >> 8),0x24),0);
          }
        }
        if (((*(byte *)(*(longlong *)(param_1 + 0x120) + 0xe) & 0xf0) == 0) &&
           ((*(byte *)(*(longlong *)(param_1 + 0x120) + 0xf) & 0xf) == 5)) {
          FUN_14025af80(param_1,0x21,iVar34 != 0);
          FUN_14025af80(param_1,0x21,iVar34 == 0);
        }
        else {
          uVar18 = FUN_14025ac5c(param_1,0xe004,4);
          if (iVar34 == 0) {
            FUN_14025b00c(param_1,0xe004,uVar18 & 0xfffdffff,4);
            uVar18 = uVar18 & 0xfffdffff | 0x20000;
          }
          else {
            FUN_14025b00c(param_1,0xe004,uVar18 | 0x20000,4);
            uVar18 = uVar18 & 0xfffdffff;
          }
          FUN_14025b00c(param_1,0xe004,uVar18,4);
        }
      }
      else {
        if (bVar10 != 4) goto LAB_14024daff;
        if (*(char *)(lVar26 + 0xf) == '\a') goto LAB_14024db3e;
LAB_14024db17:
        if ((bVar10 < 0x20) && ((0x80c10000U >> (bVar10 & 0x1f) & 1) != 0)) goto LAB_14024db3e;
        if ((bVar10 & 0xf0) == 0) goto LAB_14024db31;
      }
LAB_14024dd80:
      FUN_14022e3cc(param_1,0x20,(undefined)local_res20);
      send_mst(param_1,0,0xb3,0);
      send_mst(param_1,2,0x27,0);
    }
  }
  return 1;
}

