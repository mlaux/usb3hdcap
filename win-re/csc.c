
undefined8 FUN_14023f990(undefined8 param_1,undefined8 param_2,undefined4 *param_3)

{
  undefined8 uVar1;
  longlong lVar2;
  
  uVar1 = KsGetFilterFromIrp();
  lVar2 = KsGetDevice(uVar1);
  lVar2 = *(longlong *)(lVar2 + 0x10);
  DbgPrint("CDevice::OnSetCustomAnalogVideoColorRangeProperty( %08X )\n",*param_3);
  *(undefined4 *)(lVar2 + 0x7650) = *param_3;
  if ((*(short *)(*(longlong *)(lVar2 + 0x120) + 8) == 0xfd9) &&
     (*(short *)(*(longlong *)(lVar2 + 0x120) + 10) == 0x76)) {
    FUN_14022df9c(lVar2);
  }
  else {
    FUN_14022e8dc(lVar2);
    send_csc_maybe(lVar2);
    make_main_thread(lVar2);
  }
  return 0;
}


void send_csc_maybe(longlong param_1)

{
  int iVar1;
  longlong lVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  
  lVar2 = *(longlong *)(param_1 + 0x1c528);
  bVar3 = read_mst(param_1,0,0xab);
  send_mst(param_1,0,0xab,bVar3 & 0x7f | 0x80);
  send_mst(param_1,0,0x90,0x15);
  send_mst(param_1,0,0x91,0x15);
  iVar1 = *(int *)(lVar2 + 0x60);
  if (*(int *)(lVar2 + 0x5c) == 1) {
    cVar5 = (-(iVar1 != 0) & 0x11U) + 0x55;
  }
  else {
    cVar5 = (-(iVar1 != 0) & 0x22U) + 0x40;
  }
  send_mst(param_1,0,0x92,cVar5);
  FUN_140249474(param_1,*(undefined *)(param_1 + 0x64d0),*(undefined *)(param_1 + 0x6550),
                *(undefined *)(param_1 + 0x6610),*(undefined *)(param_1 + 0x65d0),
                *(byte *)(param_1 + 0x6650) >> 5);
  bVar4 = read_mst(param_1,0,0xb0);
  send_mst(param_1,0,0xb0,bVar4 & 0xc2 | 0x21);
  send_mst(param_1,0,0xab,bVar3 & 0x7f);
  return;
}

