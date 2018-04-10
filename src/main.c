#include "lib.h"
#include "component.h"
#include "screen.h"
#include "kb_respond.h"

extern Screen screen;

void try();

/*static void input_test(_Device *dev);
static void timer_test(_Device *dev);
static void video_test(_Device *dev);
static void pciconf_test(_Device *dev);
static void ata_test(_Device *dev);*/

int main() {
  if (_ioe_init() != 0) _halt(1);
  /*printf("_heap = [%08x, %08x)\n", _heap.start, _heap.end);
  for (int n = 1; ; n++) {
    _Device *dev = _device(n);
    if (!dev) break;
    printf("* Device: %s\n", dev->name);
    switch (dev->id) {
      case _DEV_INPUT: input_test(dev); break;
      case _DEV_TIMER: timer_test(dev); break;
      case _DEV_VIDEO: video_test(dev); break;
      case _DEV_PCICONF: pciconf_test(dev); break;
      case _DEV_ATA0: ata_test(dev); break;
    }

    printf("\n");
  }*/
  
  try();

  return 0;
}

/*static void input_test(_Device *dev) {
  printf("Input device test skipped.\n");
}

static void timer_test(_Device *dev) {
  _UptimeReg uptime;
  uint32_t t0, t1;

  dev->read(_DEVREG_TIMER_UPTIME, &uptime, sizeof(uptime));
  t0 = uptime.lo;

  for (int volatile i = 0; i < 10000000; i ++) ;

  dev->read(_DEVREG_TIMER_UPTIME, &uptime, sizeof(uptime));
  t1 = uptime.lo;

  printf("Loop 10^7 time elapse: %d ms\n", t1 - t0);
}

static void video_test(_Device *dev) {
  _VideoInfoReg info;
  dev->read(_DEVREG_VIDEO_INFO, &info, sizeof(info));
  printf("Screen size: %d x %d\n", info.width, info.height);
  for (int x = 0; x < 100; x++)
    for (int y = 0; y < 100; y++) {
      _FBCtlReg ctl;
      uint32_t pixel = 0x006a005f;
      ctl.x = info.width / 2 - 50 + x;
      ctl.y = info.height / 2 - 50 + y;
      ctl.w = ctl.h = 1;
      ctl.sync = 1;
      ctl.pixels = &pixel;
      dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(ctl));
    }
  printf("You should see a purple square on the screen.\n");
}

static uint32_t pci_conf_read(_Device *dev, uint8_t bus, uint8_t slot,
                              uint8_t func, uint8_t offset) {
  uint32_t res;
  dev->read(_DEVREG_PCICONF(bus, slot, func, offset), &res, 4);
  return res;
}

static void pciconf_test(_Device *dev) {
  for (int bus = 0; bus < 256; bus ++)
    for (int slot = 0; slot < 32; slot ++) {
      uint32_t info = pci_conf_read(dev, bus, slot, 0, 0);
      uint16_t id = info >> 16, vendor = info & 0xffff;
      if (vendor != 0xffff) {
        printf("Get device %d:%d, id %x vendor %x", bus, slot, id, vendor);
        if (id == 0x100e && vendor == 0x8086) {
          printf(" <-- This is an Intel e1000 NIC card!");
        }
        printf("\n");
      }
    }
}

static uint8_t readb(_Device *dev, uint32_t reg) {
  uint8_t res;
  dev->read(reg, &res, 1);
  return res;
}

static uint32_t readl(_Device *dev, uint32_t reg) {
  uint32_t res;
  dev->read(reg, &res, 4);
  return res;
}

static void writeb(_Device *dev, uint32_t reg, uint8_t res) {
  dev->write(reg, &res, 1);
}

#define SECTSZ 512

static void ata_test(_Device *dev) {
  int offset = 0;
  while ((readb(dev, _DEVREG_ATA_STATUS) & 0xc0) != 0x40);
  writeb(dev, _DEVREG_ATA_NSECT,  1);
  writeb(dev, _DEVREG_ATA_SECT,   offset);
  writeb(dev, _DEVREG_ATA_CYLOW,  offset >> 8);
  writeb(dev, _DEVREG_ATA_CYHIGH, offset >> 16);
  writeb(dev, _DEVREG_ATA_DRIVE,  (offset >> 24) | 0xe0);
  writeb(dev, _DEVREG_ATA_STATUS, 0x20);
  while ((readb(dev, _DEVREG_ATA_STATUS) & 0xc0) != 0x40);
  uint32_t buf[SECTSZ / sizeof(uint32_t)];
  for (int i = 0; i < SECTSZ / sizeof(uint32_t); i++) {
    buf[i] = readl(dev, _DEVREG_ATA_DATA);
  }
  printf("Reading out the MBR:\n");
  for (int i = 0; i < SECTSZ / 16 / sizeof(uint16_t); i ++) {
    for (int j = 0; j < 16; j++) {
      printf("%04x ", ((uint16_t *)buf)[i * 16 + j] & 0xffff);
    }
    printf("\n");
  }
}*/

void try_rect()
{
  RectProperty p;
  
  p.s_color.r = 255;
  p.s_color.g = 255;
  p.s_color.b = 255;
  p.s_color.a = 0;
  p.f_color.r = 128;
  p.f_color.g = 128;
  p.f_color.b = 255;
  p.f_color.a = 0;
  p.is_fill = TRUE;
  p.stroke = 20;
  p.x = 100;
  p.y = 10;
  p.width = 100;
  p.height = 100;

  Rect* rect=build_rect(p);
  if(rect != NULL){
    screen_add(rect);
    //cp_virtual_move(rect, 100, 100);
  }
}

void try_circle()
{
  CircleProperty c;
  c.color.r = 0;
  c.color.g = 255;
  c.color.b = 255;
  c.color.a = 0;
  c.x = 100;
  c.y = 100;
  c.r = 100;
  
  Circle* circle=build_circle(c);
  if(circle != NULL){
    screen_add(circle);
    //cp_virtual_move(circle, 200, 200);
  }
}

void try_line()
{
  LineProperty l;
  l.color.r = 0;
  l.color.g = 0;
  l.color.b = 128;
  l.x = 10;
  l.y = 10;
  l.stroke = 20;
  l.length = 150;
  l.is_vertical = TRUE;
  
  Line *line = build_line(l);
  if(line != NULL)
  {
    screen_add(line);
    //cp_virtual_move(line, 200, 200);
  }
}

void try_planeI()
{
  PlaneIProperty i;
  i.x = 10;
  i.y = 10;
  i.vx = 40;
  i.vy = 20;
  i.size = 2;
  i.hp_max = 100;
  
  PlaneI *planeI = build_planeI(i);
  if(planeI != NULL)
  {
    /*cp_virtual_draw(planeI);
    for(int i =0; i < 5; i++)
    {
      mv_virtual_automove(planeI);
      cp_virtual_draw(planeI);
    }*/
    battle_virtual_hurt(planeI, 10);
    screen_add(planeI);
  }
}

void try_planeX()
{
  PlaneIProperty x;
  x.x = 10;
  x.y = 100;
  x.vx = 40;
  x.vy = 20;
  x.size = 2;
  x.hp_max = 100;
  
  PlaneX *planeX = build_planeX(x);
  if(planeX != NULL)
  {
    /*cp_virtual_draw(planeX);
    for(int i = 0; i < 5; i++)
    {
      mv_virtual_automove(planeX);
      cp_virtual_draw(planeX);
    }*/
    battle_virtual_hurt(planeX, 20);
    screen_add(planeX);
  }
}

void try_planeU()
{
  PlaneIProperty u;
  u.x = 100;
  u.y = 10;
  u.vx = 40;
  u.vy = 20;
  u.size = 2;
  u.hp_max = 100;
  
  PlaneU *planeU = build_planeU(u);
  if(planeU != NULL)
  {
    /*cp_virtual_draw(planeU);
    for(int i = 0; i < 5; i++)
    {
      mv_virtual_automove(planeU);
      cp_virtual_draw(planeU);
    }*/
    battle_virtual_hurt(planeU, 90);
    screen_add(planeU);
  }
}

void try_planeT()
{
  PlaneIProperty t;
  t.x = 100;
  t.y = 100;
  t.vx = 40;
  t.vy = 20;
  t.size = 2;
  t.hp_max = 100;
  
  PlaneT *planeT = build_planeT(t);
  if(planeT != NULL)
  {
    /*cp_virtual_draw(planeT);
    for(int i = 0; i < 5; i++)
    {
      mv_virtual_automove(planeT);
      cp_virtual_draw(planeT);
    }*/
    battle_virtual_hurt(planeT, 50);
    screen_add(planeT);
  }
}

void try_player1()
{
  Player1Property t;
  t.x = 150;
  t.y = 150;
  t.size = 2;
  t.hp_max = 100;
  
  Player1 *player1 = build_player1(t);
  if(player1 != NULL)
  {
    /*cp_virtual_draw(player1);
    for(int i = 0; i < 5; i++)
    {
      mv_virtual_automove(player1);
      cp_virtual_draw(player1);
    }*/
    battle_virtual_hurt(player1, 50);
    kbRespond_add(player1);
    screen_add(player1);
  }
}

void try_bigExplosion3()
{
  BigExplosion3Property b;
  b.x = 100;
  b.y = 100;
  b.vx = 40;
  b.vy = 20;
  b.size = 2;
  
  BigExplosion3 *bigExplosion3 = build_bigExplosion3(b);
  if(bigExplosion3 != NULL)
  {
    /*cp_virtual_draw(planeT);
    for(int i = 0; i < 5; i++)
    {
      mv_virtual_automove(planeT);
      cp_virtual_draw(planeT);
    }*/
    screen_add(bigExplosion3);
  }
}

void try_bullet()
{
  BulletProperty b;
  b.x = 10;
  b.y = 10;
  b.vx = 10;
  b.vy = 20;
  b.size = 1;
  Bullet *bullet = build_bullet(b);
  if(bullet != NULL)
  {
    cp_virtual_draw(bullet);
    for(int i =0; i < 10; i++)
    {
      mv_virtual_automove(bullet);
      cp_virtual_draw(bullet);
    }
    //cp_virtual_move(bullet, 10, 20);
    //cp_virtual_draw(bullet);
  }
}

void try_hp()
{
  HpProperty h;
  h.x = 100;
  h.y = 100;
  h.size = 2;
  h.is_player = false;
  h.hp_max = 100;

  Hp *hp = build_hp(h);
  if(hp != NULL)
  {
    hp_draw(hp);
    for(int i = 0; i < 5; i++)
    {
      hp_decrease(hp, 10);
      hp_move(hp, 0, 20);
      hp_draw(hp);
    }
  }
}

void try(){
  screen_init();
  
  //try_rect();
  //try_circle();
  //try_line();
  //try_planeI();
  //try_planeX();
  //try_planeU();
  //try_planeT();
  try_player1();
  //try_bullet();
  //try_bigExplosion3();
  //try_hp();
  
  while(1)
  {
    kbRespond_action();
    screen_draw();
  }
  
  //screen_draw();

  /*_KbdReg reg = read_key();
  printf("%d\n", reg.keycode);*/
}
