
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
