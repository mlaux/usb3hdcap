void send_reset_vendors(longlong param_1)

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



void tw9900_init_all(longlong param_1,int param_2,undefined8 param_3,uint param_4,undefined8 param_5
                    ,int param_6)

{
  short sVar1;
  int iVar2;
  longlong lVar3;
  longlong lVar4;
  byte bVar5;
  char cVar6;
  ushort uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined auStack_108 [32];
  undefined4 local_e8;
  byte local_d8 [16];
  undefined local_c8 [144];
  ulonglong local_38;

  local_38 = DAT_14035a610 ^ (ulonglong)auStack_108;
  bVar5 = (byte)param_4;
  if (param_6 == 0) {
    FUN_14022e8dc();
  }
  lVar3 = *(longlong *)(param_1 + 0x1c528);
  if (param_2 != -1) {
    iVar2 = *(int *)(param_1 + 0x6840);
    if (iVar2 == 5) {
      tw9900_init_static(param_1);
      local_d8[0] = 0x40;
      local_e8 = 1;
      i2c_write(param_1,0x88,2,local_d8);
      local_d8[0] = 0x42;
LAB_14022dcb9:
      local_e8 = 1;
      i2c_write(param_1,0x88,6,local_d8);
    }
    else {
      if (iVar2 == 6) {
        tw9900_init_static(param_1);
        local_d8[0] = 0x54;
        local_e8 = 1;
        i2c_write(param_1,0x88,2,local_d8);
        local_d8[0] = 0x40;
        goto LAB_14022dcb9;
      }
      if (iVar2 == 4) {
        FUN_140227f1c(param_1);
      }
      else {
        if ((*(short *)(*(longlong *)(param_1 + 0x120) + 8) == 0x5ca) &&
           (*(short *)(*(longlong *)(param_1 + 0x120) + 10) == 0x901)) {
          *(uint *)(param_1 + 0x8bd4) = (uint)(iVar2 != 0);
        }
        if (*(int *)(lVar3 + 0x1f84) == 0) {
          init_mst(param_1);
        }
      }
    }
    cVar6 = FUN_14022ba14(param_1);
    if (cVar6 != '\0') {
      FUN_1402468f4(param_1);
    }
    set_brightness_contrast(param_1,1);
    *(undefined4 *)(param_1 + 0x75dc) = 0;
    *(undefined4 *)(param_1 + 0x75e0) = 0;
    *(undefined4 *)(param_1 + 0x75e4) = 0;
    *(undefined4 *)(param_1 + 0x7a10) = 0;
    *(undefined4 *)(param_1 + 0x6758) = 0;
    *(undefined4 *)(param_1 + 0x67f4) = 0;
  }
  if (param_4 != 0xffffffff) {
    lVar4 = *(longlong *)(param_1 + 0x120);
    sVar1 = *(short *)(lVar4 + 8);
    if ((((sVar1 == 0xfd9) && (uVar7 = *(short *)(lVar4 + 10) - 0x4f, uVar7 < 0x28)) &&
        ((0xa000008001U >> ((ulonglong)uVar7 & 0x3f) & 1) != 0)) ||
       (((sVar1 == 0x17ef && (*(short *)(lVar4 + 10) == 0x7219)) ||
        ((sVar1 == 0x1164 && ((ushort)((*(ushort *)(lVar4 + 10) & 0xfff) - 0x535) < 4)))))) {
      if (*(int *)(lVar3 + 0x1f84) == 0) {
        FUN_140251b10(param_1,CONCAT11((char)((ushort)sVar1 >> 8),bVar5));
        FUN_14025165c(param_1,*(undefined4 *)(param_1 + 0x7a08),*(undefined4 *)(param_1 + 0x7a04));
        uVar9 = 0x20;
        local_d8[0] = 5;
        uVar8 = 0x98;
      }
      else {
        param_4 = param_4 & 0xff;
        if (((bVar5 != 0) && (param_4 != 1)) &&
           ((param_4 != 2 && ((param_4 != 3 && (param_4 != 4)))))) goto LAB_14022df41;
        memset(local_c8,0,0x82);
        local_e8 = 1;
        local_d8[0] = bVar5;
        i2c_write(param_1,100,0x3a,local_d8);
        FUN_140001220(5);
        if (bVar5 == 0) {
          local_d8[0] = *(byte *)(param_1 + 0x7a08);
          uVar9 = 0x3b;
        }
        else {
          if ((param_4 != 1) && (param_4 != 2)) {
            if ((param_4 != 3) && (param_4 != 4)) goto LAB_14022df41;
            local_d8[0] = *(byte *)(param_1 + 0x7a08);
            local_e8 = 1;
            i2c_write(param_1,100,0x3b,local_d8);
            FUN_140001220(0x32);
          }
          local_d8[0] = *(byte *)(param_1 + 0x7a04);
          uVar9 = 0x3c;
        }
        uVar8 = 100;
      }
    }
    else {
      cVar6 = FUN_140227314(param_1);
      if (cVar6 != '\0') {
        configure_audio_regs(param_1);
      }
      if ((((*(uint *)(param_1 + 0x6840) & 0xfffffffa) != 0) || (*(uint *)(param_1 + 0x6840) == 5))
         || (*(int *)(lVar3 + 0x1f84) != 0)) goto LAB_14022df41;
      local_d8[0] = i2c_read(param_1,0x98,0x20,0);
      if (param_4 == 0) {
        local_d8[0] = local_d8[0] & 0xef;
      }
      else if (param_4 == 1) {
        local_d8[0] = local_d8[0] | 0x10;
      }
      uVar9 = 0x20;
      uVar8 = 0x98;
    }
    local_e8 = 1;
    i2c_write(param_1,uVar8,uVar9,local_d8);
  }
LAB_14022df41:
  if (param_6 == 0) {
    make_main_thread(param_1);
  }
  if ((param_2 != -1) && (*(int *)(param_1 + 0x6840) == 5 || *(int *)(param_1 + 0x6840) == 6)) {
    set_tw9900_standard_and_make_signal_monitor_thread
              (param_1,*(undefined4 *)(param_1 + 0x6714),param_6);
  }
  __security_check_cookie(local_38 ^ (ulonglong)auStack_108);
  return;
}



undefined8
set_tw9900_standard_and_make_signal_monitor_thread(longlong param_1,uint param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  byte local_res8 [8];

  if (1 < *(int *)(param_1 + 0x6840) - 5U) {
    return 0;
  }
  if (param_3 == 0) {
    FUN_14022e8dc();
  }
                    /* CNTRL1 */
  bVar1 = i2c_read(param_1,0x88,0xc,0);
  bVar2 = bVar1 & 0xef | 8;
  if (param_2 < 0x801) {
    if (param_2 != 0x800) {
      if (param_2 < 0x41) {
        if (param_2 != 0x40) {
          if (param_2 == 1) {
LAB_14022e11c:
            bVar2 = bVar1 & 0xef | 0x18;
          }
          else if (param_2 != 2) {
            if (param_2 == 4) goto LAB_14022e11c;
            if (param_2 != 0x10) {
              bVar3 = param_2 == 0x20;
              goto LAB_14022e166;
            }
          }
        }
      }
      else if ((param_2 != 0x80) && (param_2 != 0x100)) {
        if ((param_2 != 0x200) && (param_2 != 0x400)) goto LAB_14022e181;
        goto LAB_14022e11c;
      }
    }
  }
  else if (((((param_2 != 0x1000) && (param_2 != 0x2000)) && (param_2 != 0x4000)) &&
           ((param_2 != 0x8000 && (param_2 != 0x10000)))) &&
          ((param_2 != 0x20000 && ((param_2 != 0x40000 && (param_2 != 0x80000)))))) {
    bVar3 = param_2 == 0x100000;
LAB_14022e166:
    if (!bVar3) goto LAB_14022e181;
  }
  local_res8[0] = bVar2;
                    /* CNTRL1 */
  i2c_write(param_1,0x88,0xc,local_res8,1);
LAB_14022e181:
  set_tw9900_for_ntsc_or_pal(param_1,param_2);
  if (param_3 == 0) {
    make_main_thread(param_1);
  }
  return 0;
}



void set_tw9900_for_ntsc_or_pal(longlong param_1,uint param_2)

{
  longlong lVar1;
  byte bVar2;
  byte bVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  bool bVar6;
  byte local_res10 [8];

  lVar1 = *(longlong *)(param_1 + 0x1c528);
  if (*(int *)(lVar1 + 0x1f5c) != 0) goto LAB_14022f0e5;
  if (param_2 < 0x801) {
    if (param_2 == 0x800) {
      local_res10[0] = 7;
    }
    else if (param_2 < 0x41) {
      if (param_2 == 0x40) {
LAB_14022efaf:
        local_res10[0] = 1;
      }
      else if ((param_2 == 1) || (param_2 == 2)) {
        local_res10[0] = 0;
      }
      else {
        if (param_2 != 4) {
          if ((param_2 != 0x10) && (param_2 != 0x20)) goto LAB_14022f058;
          goto LAB_14022efaf;
        }
        local_res10[0] = 3;
      }
    }
    else {
      if ((param_2 == 0x80) || (param_2 == 0x100)) goto LAB_14022efaf;
      if (param_2 == 0x200) {
        local_res10[0] = 4;
      }
      else {
        if (param_2 != 0x400) goto LAB_14022f058;
        local_res10[0] = 5;
      }
    }
LAB_14022f045:
    i2c_write(param_1,0x88,0x1c,local_res10,1);
  }
  else if ((((((param_2 == 0x1000) || (param_2 == 0x2000)) || (param_2 == 0x4000)) ||
            ((param_2 == 0x8000 || (param_2 == 0x10000)))) ||
           ((param_2 == 0x20000 || ((param_2 == 0x40000 || (param_2 == 0x80000)))))) ||
          (param_2 == 0x100000)) {
    local_res10[0] = 2;
    goto LAB_14022f045;
  }
LAB_14022f058:
  *(undefined4 *)(lVar1 + 0x1cd4) = 1;
  *(undefined4 *)(lVar1 + 0x1cdc) = 48000;
  *(undefined4 *)(lVar1 + 0x40) = 1;
  *(undefined4 *)(lVar1 + 0x58) = 1;
  *(undefined4 *)(lVar1 + 0x5c) = 1;
  *(undefined4 *)(lVar1 + 0x60) = 1;
  *(undefined4 *)(lVar1 + 0x30) = 0x2d0;
                    /* set PAL settings */
  bVar6 = (param_2 & 0x1ff5f0) == 0;
  if (bVar6) {
    uVar4 = 0x3c;
    uVar5 = 0xf0;
  }
  else {
    uVar5 = 0x120;
    uVar4 = 0x32;
  }
  *(undefined4 *)(lVar1 + 0x34) = uVar5;
  *(undefined4 *)(lVar1 + 0x38) = uVar4;
  *(uint *)(lVar1 + 0x3c) = (uint)bVar6;
  *(uint *)(param_1 + 0x75dc) = *(int *)(lVar1 + 0x30) << 0x10 | *(uint *)(lVar1 + 0x34);
  *(undefined4 *)(param_1 + 0x75e0) = *(undefined4 *)(lVar1 + 0x38);
  *(undefined4 *)(param_1 + 0x75e4) = *(undefined4 *)(lVar1 + 0x40);
  *(undefined4 *)(param_1 + 0x7a10) = 48000;
LAB_14022f0e5:
                    /* set NTSC settings */
  if ((param_2 & 0xa07) != 0) {
                    /* CROP_HI */
    bVar2 = i2c_read(param_1,0x88,7,0);
                    /* VVBI */
    bVar3 = i2c_read(param_1,0x88,0x55,0);
    local_res10[0] = bVar2 & 0xf;
    i2c_write(param_1,0x88,7,local_res10,1);
    local_res10[0] = 0x14;
    i2c_write(param_1,0x88,8,local_res10,1);
    local_res10[0] = 0xf2;
    i2c_write(param_1,0x88,9,local_res10,1);
    local_res10[0] = 0x10;
    i2c_write(param_1,0x88,10,local_res10,1);
    local_res10[0] = 0xd0;
    i2c_write(param_1,0x88,0xb,local_res10,1);
    local_res10[0] = bVar3 & 0xef | 0x10;
    i2c_write(param_1,0x88,0x55,local_res10,1);
    local_res10[0] = 0;
    i2c_write(param_1,0x88,0xd,local_res10,1);
    local_res10[0] = 0x11;
    i2c_write(param_1,0x88,0xe,local_res10,1);
    local_res10[0] = 0;
    i2c_write(param_1,0x88,0xf,local_res10,1);
  }
  if ((param_2 & 0x1ff5f0) != 0) {
    bVar2 = i2c_read(param_1,0x88,7,0);
    bVar3 = i2c_read(param_1,0x88,0x55,0);
    local_res10[0] = bVar2 & 0xf | 0x10;
    i2c_write(param_1,0x88,7,local_res10,1);
    local_res10[0] = 0x19;
    i2c_write(param_1,0x88,8,local_res10,1);
    local_res10[0] = 0x20;
    i2c_write(param_1,0x88,9,local_res10,1);
    local_res10[0] = 10;
    i2c_write(param_1,0x88,10,local_res10,1);
    local_res10[0] = 0xd0;
    i2c_write(param_1,0x88,0xb,local_res10,1);
    local_res10[0] = bVar3 & 0xef;
    i2c_write(param_1,0x88,0x55,local_res10,1);
    local_res10[0] = 0;
    i2c_write(param_1,0x88,0xd,local_res10,1);
    local_res10[0] = 0x11;
    i2c_write(param_1,0x88,0xe,local_res10,1);
    local_res10[0] = 0;
    i2c_write(param_1,0x88,0xf,local_res10,1);
  }
  return;
}


void tw9900_init_static(longlong param_1)

{
  longlong lVar1;
  undefined local_res8 [8];

  send_reset_vendors();
  local_res8[0] = 0x75;
  i2c_write(param_1,0x98,0x20,local_res8,1);
  local_res8[0] = 0;
  i2c_write(param_1,0x88,6,local_res8,1);
  local_res8[0] = 0xa2;
  i2c_write(param_1,0x88,3,local_res8,1);
  local_res8[0] = 1;
  i2c_write(param_1,0x88,5,local_res8,1);
  local_res8[0] = 0x14;
  i2c_write(param_1,0x88,8,local_res8,1);
  local_res8[0] = 0xf2;
  i2c_write(param_1,0x88,9,local_res8,1);
  local_res8[0] = 0xb;
  i2c_write(param_1,0x88,10,local_res8,1);
  local_res8[0] = 0xd2;
  i2c_write(param_1,0x88,0xb,local_res8,1);
  local_res8[0] = 0x57;
  i2c_write(param_1,0x88,0x19,local_res8,1);
  local_res8[0] = 0xf;
  i2c_write(param_1,0x88,0x1a,local_res8,1);
  local_res8[0] = 0;
  i2c_write(param_1,0x88,0x1b,local_res8,1);
  local_res8[0] = 7;
  i2c_write(param_1,0x88,0x1c,local_res8,1);
  local_res8[0] = 0xe;
  i2c_write(param_1,0x88,0x28,local_res8,1);
  local_res8[0] = 3;
  i2c_write(param_1,0x88,0x29,local_res8,1);
  local_res8[0] = 7;
  i2c_write(param_1,0x88,0x2d,local_res8,1);
  local_res8[0] = 6;
  i2c_write(param_1,0x88,0x2f,local_res8,1);
  local_res8[0] = 1;
  i2c_write(param_1,0x88,0x4c,local_res8,1);
  local_res8[0] = 0;
  i2c_write(param_1,0x88,0x55,local_res8,1);
  local_res8[0] = 0x26;
  i2c_write(param_1,0x88,0x6b,local_res8,1);
  local_res8[0] = 0x36;
  i2c_write(param_1,0x88,0x6c,local_res8,1);
  local_res8[0] = 0xf0;
  i2c_write(param_1,0x88,0x6d,local_res8,1);
  local_res8[0] = 0x28;
  i2c_write(param_1,0x88,0x6e,local_res8,1);
  local_res8[0] = 0x80;
  i2c_write(param_1,0x88,6,local_res8,1);
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


