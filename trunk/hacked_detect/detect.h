/*
 * Detect a Library for hardware detection
 *
 * Copyright (C) 1998-2000 MandrakeSoft
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef DETECT_H
#define DETECT_H

#include <sys/types.h>
#include <linux/genhd.h>


/* Configurable path */
#define PATH_PROC_PCI           "/proc/bus/pci/devices"
#define PATH_PROC_USB           "/proc/bus/usb/devices"
#define PATH_PROC_ISAPNP        "/proc/isapnp"
#define PATH_PROC_CPUINFO       "/proc/cpuinfo"
#define PATH_PROC_MEMINFO       "/proc/meminfo"
#define PATH_PROC_SCSI          "/proc/scsi/scsi"
#define PATH_PROC_IDE           "/proc/ide"

#define PCMCIA_UNKNOWN          -1
#define PCMCIA_MULTIFUNCTION    0
#define PCMCIA_MEMORY           1
#define PCMCIA_SERIAL           2
#define PCMCIA_PARALLEL         3
#define PCMCIA_FIXEDDISK        4
#define PCMCIA_VIDEO            5
#define PCMCIA_ETHERNET         6
#define PCMCIA_AIMS             7
#define PCMCIA_SCSI             8


/* Options */
#define HAS_OPL3           1    /* Start with soundcard options       */
#define HAS_MPU401     (1<<1)
#define HAS_DMA16      (1<<2)
#define HAS_AWE        (1<<4)
#define HAS_DREAM      (1<<5)
#define HAS_MAD16      (1<<6)
#define HAS_TRIX       (1<<7)
#define HAS_PAS2       (1<<8)
#define HAS_SMGAMES    (1<<9)
#define HAS_JOYSTICK   (1<<10)
                
#define HAS_FPU        (1<<11)  /* CPU options                        */
#define HAS_TDNOW      (1<<12)
#define HAS_MMX        (1<<13)

#define IS_SERIAL      (1<<14)  /* indicate SERIAL device             */

/* Modprobe version to be used */
#define DETECT_MODPROBE_MAJOR 2
#define DETECT_MODPROBE_MINOR 3
#define DETECT_MODPROBE_PATCH 1

typedef enum {
  DETECT_STATUS_OK = 0,         /* everything OK                      */
  DETECT_STATUS_WRITE_ERROR,    /* could not write a file             */
  DETECT_STATUS_READ_ERROR,     /* could not read a file              */
  DETECT_STATUS_UNSUPPORTED,    /* operation is not supported         */
  DETECT_STATUS_CANCELLED,      /* operation was cancelled            */
  DETECT_STATUS_DEVICE_BUSY,    /* device is busy; try again later    */
  DETECT_STATUS_INVAL,          /* data is invalid                    */
                                /*          (includes no dev at open) */
  DETECT_STATUS_EOF,            /* no more data available (eof)       */
  DETECT_STATUS_IO_ERROR,       /* error during device I/O            */
  DETECT_STATUS_NO_MEM,         /* out of memory                      */
  DETECT_STATUS_ACCESS_DENIED   /* access to resource has been denied */
} DETECT_Status;


typedef enum {
  UNKNOWN_BUS,                  /* Bus type unknown                   */
  IDE,                          /* Intelligent Drive Electronics      */
  ISA,                          /* Industry Standard Architecture     */
  PCI,                          /* Peripheral Component Interconnect  */
  PCMCIA,                       /* Personal Computer Memory Card      */
                                /*        International Association   */
  SERIAL,                       /* Serial Bus                         */
  USB,                          /* Universal Serial Bus               */
  PS2,                          /*                                    */
  VLB,                          /* VESA Local Bus                     */
  SCSI,                         /* Small Computer System Interface    */
  FDC,                          /* Floppy Drive Controller            */
  PARALLEL,
  GAMEPORT
} BusType;


typedef enum {
  UNKNOWN_DEVICE,
  CPU,
  MEMORY,
  FLOPPY,
  DISK,
  CDROM,
  TAPE,
  ETHERNETCARD,
  MODEM,
  VIDEOCARD,
  TVCARD,
  SOUNDCARD,
  PRINTER,
  SCANNER,
  MOUSE,
  OTHERS,
  IDEINTERFACE,
  SCSIINTERFACE,
  USBINTERFACE,
  JOYSTICK,
  ISDN,
  WEBCAM,
  BRIDGE
} DeviceType;


/**********************************************************************/
/* Generic hardware device list                                       */
/* Contains all ISA and PCI cards recognized by detect library        */
/**********************************************************************/
struct bus_lst {
  struct isa_info *isa;         /* list of ISA bus devices            */
  struct pci_info *pci;         /* list of PCI bus devices            */
  struct pcmcia_info *pcmcia;   /* list of PCMCIA bus devices         */
  struct ide_info *ide;         /* list of IDE bus devices            */
  struct scsi_info *scsi;       /* list of SCSI bus devices           */
  struct parallel_info *parallel;  /* list of parallel ports          */
  struct serial_info *serial;   /* list of serial ports               */
  struct usb_info *usb;         /* list of USB bus devices            */
};

/**********************************************************************/
/* Generic hardware device list                                       */
/* Contains all ISA and PCI cards recognized by detect library        */
/**********************************************************************/
struct cards_lst {
  char *vendor;
  char *model;
  char *modulename;
  BusType bus;
  char *dev_id;
  unsigned long long_id;
  int type;
  unsigned int options;
  struct cards_lst *next;
};


/* Definition of ISA card */
struct isa_info {
  char *vendor;                 /* vendor name of the ISA card        */
  char *model;                  /* model name of the ISA card         */
  char *modulename;             /* module name used by the kernel     */
  DeviceType type;              /* type of the card, e.g. SOUND       */
  char *board_id;
  int board_num;
  char *dev_id;
  int dev_num;
  unsigned int options;         /* e.g. soundcard abilities           */
  int io, irq, dma8, dma16;
  struct isa_info *next;        /* pointer to next ISA board          */
}; 


/* Definition of PCMCIA card */
struct pcmcia_info {
  char *vendor;                 /* vendor name of the PCMCIA card     */
  char *model;                  /* model name of the PCMCIA card      */
  char *modulename;             /* module name used by the kernel     */
  DeviceType type;              /* type of the card, e.g. SOUND       */
  unsigned long id;
  struct pcmcia_info *next;     /* pointer to next PCMCIA card        */
};


/* Definition of PCI card */
struct pci_info {
  char *vendor;                 /* vendor name of the PCI card        */
  char *model;                  /* model name of the PCI card         */
  char *modulename;             /* module name used by the kernel     */
  DeviceType type;              /* type of the card, e.g. SOUND       */
  unsigned long id;
  unsigned int options;         /* e.g. soundcard abilities           */
  struct pci_info *next;        /* pointer to next PCI card           */
};


/* Definition of USB device */
struct usb_info {
  char *vendor;                 /* vendor name of the USB device      */
  char *model;                  /* model name of the USB device       */
  char *modulename;             /* module name used by the kernel     */
  DeviceType type;              /* type of the card, e.g. SOUND       */
  unsigned long id;
  struct usb_info *next;        /* pointer to next USB card           */
};


/**********************************************************************/
/* IDE/SCSI bus information                                           */
/**********************************************************************/

/* Definition of IDE drive */
struct ide_info {
  char *device;                 /* device of the ide drive            */
  char *model;                  /* model name of the ATAPI drive      */
  DeviceType type;              /* type of the ATAPI/IDE drive:       */
                                /*      ZIP, DISK, CDROM, etc.        */
  int cylinders;
  short heads;
  short sectors;
  struct ide_info *next;        /* pointer to next ide device         */
};


/* Definition of IDE interface */
struct identf_info {
  char *vendor;                 /* vendor name of the interface       */
  char *model;                  /* model name of the interface        */
  char *module;                 /* kernel module of the interface     */
  BusType bus;                  /* Bus of the card (ISA, PCI)         */
  char *board_id;
  int board_num;                /* Numbering of the interface         */
  char *dev_id;
  int dev_num;                  /* Numbering of the dev               */
  int io, irq;
  unsigned long long_id;
  struct identf_info *next;     /* pointer to next IDE interface      */
};


/* Definition of SCSI interface */
struct scsintf_info {
  char *vendor;                 /* vendor name of the interface       */
  char *model;                  /* model name of the interface        */
  char *module;                 /* kernel module of the interface     */
  BusType bus;                  /* Bus of the card (ISA, PCI)         */
  char *board_id;
  int board_num;                /* Numbering of the interface         */
  char *dev_id;
  int dev_num;                  /* Numbering of the dev               */
  unsigned long long_id;
  int io, irq;
  struct scsintf_info *next;    /* pointer to next SCSI interface     */
};


/* Definition of USB interface */
struct usbntf_info {
  char *vendor;                 /* vendor name of the interface       */
  char *model;                  /* model name of the interface        */
  char *module;                 /* kernel module of the interface     */
  BusType bus;                  /* Bus of the card (ISA, PCI)         */
  char *board_id;
  int board_num;                /* Numbering of the interface         */
  char *dev_id;
  int dev_num;
  unsigned long long_id;
  int io, irq;
  struct usbntf_info *next;     /* pointer to next USB interface      */
};


/**********************************************************************/
/* Devices information                                                */
/**********************************************************************/

/* Definition of CPU */
struct cpu_info {
  unsigned short proc_id;       /* processor number                   */
  char *vendor;                 /* vendor name of CPU                 */
  char *model;                  /* model name of CPU                  */
  char *bogomips;               /* bogomips                           */
  char *bugs;                   /* bugs detected in the micro         */
  int freq;                     /* frequency of CPU                   */
  char *cache;                  /* cache size                         */
  unsigned int options;         /* CPU options as FPU, MMX, 3DNOW...  */
  struct cpu_info *next;
};


/* Definition of MEMORY */
struct memory_info {
  int total;                    /* total amount of memory             */
  int free;                     /* total free amount of memory        */
  int shared;                   /* total shared amount of memory      */
  int buffers;                  /* total buffers                      */
  int cached;                   /* total cached amount of memory      */
  int swap_total;
  int swap_free;
};


/* Definition of SERIAL */
struct serial_info {
  char *device;
  char *dos_equivalent;
  /* those tags are not related to the port, */
  /* they reflect the connected device. */
  char *vendor;
  char *model;
  char *modulename;
  DeviceType type;              /* type of the device, e.g. MODEM     */
  char *dev_id;
  long speed;
  struct serial_info *next;
};


/* Definition of PARALLEL */
struct parallel_info {
  char *device;
  char *dos_equivalent;
  struct parallel_info *next;
};


/* Definition of GAMEPORT */
struct gameport_info {
  char *vendor;
  char *model;
  int io, irq;
  struct gameport_info *next;
};


/* Definition of FLOPPY drive */
struct floppy_info {
  char *vendor;                 /* vendor name of the floppy drive    */
  char *model;                  /* model of the floppy drive          */
  char *device;                 /* device of the floppy drive         */
  char *module;                 /* kernel module of the floppy drive  */
  BusType bus;                  /* bus type of the floppy drive       */
  struct floppy_info *next;
};


/* Definition of CDROM drive */
struct cdrom_info {
  char *vendor;                 /* vendor name of the cdrom drive     */
  char *model;                  /* model of the cdrom drive           */
  char *device;                 /* device of the cdrom drive          */
  char *module;                 /* kernel module of the cdrom drive   */
  BusType bus;                  /* bus type of the cdrom drive        */
  struct cdrom_info *next;
};


/* Definition of hard DISK */
struct disk_info {
  char *vendor;                 /* vendor name of the hard disk       */
  char *model;                  /* model name of the hard disk        */
  char *device;                 /* device of the hard disk            */
  char *path;
  BusType bus;                  /* bus type of the hard disk          */
  int cylinders;                /* \                                  */
  short heads;                  /*  > heads, sectors and cylinders    */
  short sectors;                /* /  of the disk                     */
  short host, did;
  int size;
  struct disk_info *next;
};


/* Definition of TAPE */
struct tape_info {
  char *vendor;                 /* vendor name of the tape drive      */
  char *model;                  /* model of the tape drive            */
  char *device;                 /* device of the tape drive           */
  char *module;                 /* kernel module of the tape drive    */
  BusType bus;                  /* bus type of the tape drive         */
  struct tape_info *next;
};


/* Definition of ETHERNETCARD */
struct ethernet_info {
  char *vendor;                 /* vendor name of the ethernet card   */
  char *model;                  /* model name of the ethernet card    */
  char *module;                 /* kernel module name of the card     */
  BusType bus;                  /* bus type of the ethernet card      */
  char *board_id;
  int board_num;                /* numbering of the board             */
  char *dev_id;
  int dev_num;                  /* numbering of the dev               */
  unsigned long long_id;
  int io, irq;
  struct ethernet_info *next;
};


/* Definition of ISDNCARD */
struct isdn_info {
  char *vendor;                 /* vendor name of the ISDN card   */
  char *model;                  /* model name of the ISDN card    */
  char *module;                 /* kernel module name of the card     */
  BusType bus;                  /* bus type of the ISDN card      */
  char *board_id;
  int board_num;                /* numbering of the board             */
  char *dev_id;
  int dev_num;                  /* numbering of the dev               */
  unsigned long long_id;
  int io, irq;
  struct isdn_info *next;
};


/* Definition of BRIDGECARD */
struct bridge_info {
  char *vendor;                 /* vendor name of the BRIDGE*/
  char *model;                  /* model name of the BRIDGE*/
  char *module;                 /* kernel module name of the bridge*/
  BusType bus;                  /* bus type of the BRIDGE card*/
  unsigned long long_id;
  struct bridge_info *next;
};


/* Definition of SOUNDCARD */
struct soundcard_info {
  char *vendor;                 /* vendor name of the soundcard       */
  char *model;                  /* model name of the soundcard        */
  char *module;                 /* kernel module name of the soundcard*/
  BusType bus;                  /* bus type of the soundcard          */
  char *board_id;
  int board_num;                /* numbering of the board             */
  char *dev_id;
  int dev_num;                  /* numbering of the dev               */
  unsigned int options;         /* soundcard options                  */
  int io, irq, dma8, dma16;
  unsigned long long_id;
  struct soundcard_info *next;
};


/* Definition of SCSI device */
struct scsi_info {
  char *vendor;                 /* vendor name of the SCSI device     */
  char *model;                  /* model name of the SCSI device      */
  char *device;                 /* device of the SCSI device          */
  DeviceType type;              /* type of the SCSI device:           */
                                /*  ZIP, DISK, CD-ROM, etc.       */
  struct scsi_info *next;
};


/* Definition of VIDEO card */
struct video_info {
  char *vendor;                 /* vendor name of the videocard       */
  char *model;                  /* model name of the videocard        */
  char *server;                 /* X server name of the videocard     */
  BusType bus;                  /* bus type of the videocard          */
  int memory;                   /* videocard memory in Kb             */
                                /*                 (default 256Kb)    */
  char *ramdac;                 /* videocard RamDAC                   */
  char *clockchip;              /* videocard ClockChip                */
  unsigned long long_id;
  struct video_info *next;
};


/* Definition of TVCARD card */
struct tvcard_info {
  char *vendor;                 /* vendor name of the card            */
  char *model;                  /* model name of the card             */
  char *reserved;               /* !!! currently unused !!!           */
  char *module;                 /* kernel module name of the card     */
  BusType bus;                  /* bus type of the card               */
  char *board_id;
  int board_num;                /* numbering of the board             */
  char *dev_id;
  unsigned long long_id;
  struct tvcard_info *next;
};


/* Definition of MOUSE */
struct mouse_info {
  char *vendor;                 /* vendor name of the mouse           */
  char *model;                  /* model name of the mouse            */
  char *device;                 /* device name of the mouse           */
  char *module;                 /* kernel module name for the mouse   */
  BusType bus;                  /* bus type of the mouse              */
  struct mouse_info *next;
};


/* Definition of JOYSTICK */
struct joystick_info {
  char *vendor;                 /* vendor name of the joystick        */
  char *model;                  /* model name of the joystick         */
  char *device;                 /* device name of the joystick        */
  char *module;                 /* kernel module name for the joystick*/
  BusType bus;                  /* bus type of the joystick           */
  struct joystick_info *next;
};


/* Definition of MODEM */
struct modem_info {
  char *board_id;
  int board_num;                /* numbering of the board             */
  char *dev_id;
  int dev_num;                  /* numbering of the dev               */
  char *vendor;                 /* vendor name of the modem           */
  char *model;                  /* model name of the modem            */
  char *device;                 /* device of the modem                */
  char *module;                 /* kernel module name for the modem   */
  BusType bus;                  /* bus type of the modem              */
  int io, irq;
  long speed;                   /* modem speed, e.g.: 115200          */
  unsigned long long_id;
  struct modem_info *next;
};


/* Definition of PRINTER */
struct printer_info {
  char *vendor;                 /* vendor name of the printer         */
  char *model;                  /* model name of the printer          */
  char *device;                 /* device name of the printer         */
  char *module;                 /* kernel module name for the printer */
  BusType bus;                  /* bus type of the printer            */
  unsigned long long_id;
  struct printer_info *next;
};

/* Definition of SCANNER */
struct scanner_info {
  char *vendor;                 /* vendor name of the scanner         */
  char *model;                  /* model name of the scanner          */
  char *device;                 /* device name of the scanner         */
  char *module;                 /* kernel module name for the scanner */
  BusType bus;                  /* bus type of the scanner            */
  unsigned long long_id;
  struct scanner_info *next;
};


/* Definition of WEBCAM */
struct webcam_info {
  char *vendor;                 /* vendor name of the webcam         */
  char *model;                  /* model name of the webcam          */
  char *device;                 /* device name of the webcam         */
  char *module;                 /* kernel module name for the webcam */
  BusType bus;                  /* bus type of the webcam            */
  unsigned long long_id;
  struct webcam_info *next;
};



/* Definition of OTHERS */
struct others_info {
  unsigned long long_id;
  char *board_id;
  int board_num;                /* numbering of the board             */
  char *dev_id;
  int dev_num;                  /* numbering of the dev               */
  char *vendor;                 /* vendor name of the device          */
  char *model;                  /* model name of the device           */
  char *device;                 /* device name used for the device    */
  char *module;                 /* kernel module name for the device  */
  BusType bus;                  /* bus type of the device             */
  int io, irq;
  unsigned long id;
  struct others_info *next;
};

int debug;

extern char s_ignore[];
extern char s_not_available[];
extern char s_none[];
extern char s_unknown[];

/**********************************************************************/
/* Debug functions                                                    */
/**********************************************************************/

/* Make a report file */
extern DETECT_Status report_detect(char *filename);
extern DETECT_Status report_verbose_detect(char *filename, int verbose);

/**********************************************************************/
/* Detection functions                                                */
/**********************************************************************/
        

/*bridge.c*/
extern struct bridge_info *bridge_detect(struct bus_lst *bus);

/*isa.c*/
extern struct isa_info *isa_detect(struct cards_lst *lst);
extern int free_irqs_dmas_detect(int irqs[], int dmas[]);

/*pci.c*/
extern struct pci_info *pci_detect(struct cards_lst *lst);

/*pcmcia.c*/
extern struct pcmcia_info *pcmcia_detect(struct cards_lst *lst);

/*ide.c*/
extern struct identf_info *ideinterface_detect(struct bus_lst *bus);
extern struct ide_info *ide_detect(void);

/*scsi.c*/
extern struct scsi_info *scsi_detect(void);

/* parallel.c */
extern struct parallel_info *parallel_detect();

/* serial.c */
extern struct serial_info *serial_detect(struct cards_lst *lst);

/*memory.c*/
extern struct memory_info *memory_detect(void);

/*cpu.c*/
extern struct cpu_info *cpu_detect(void);

/*disk.c*/
extern struct disk_info *disk_detect(struct bus_lst *bus);        

/*joystick.c*/
extern struct gameport_info *gameport_detect(struct bus_lst *bus);
extern struct joystick_info *joystick_detect(struct bus_lst *bus);

/*partitions.c*/
extern struct partition_info *partitions_detect(void);

/*mouse.c*/
extern struct mouse_info *mouse_detect(struct bus_lst *bus);

/*modem.c*/
extern struct modem_info *modem_detect(struct bus_lst *bus);

/*scsicard.c*/
extern struct scsintf_info *scsiinterface_detect(struct bus_lst *bus);

/*cdrom.c*/
extern struct cdrom_info *cdrom_detect(struct bus_lst *bus);

/*ethernet.c*/
extern struct ethernet_info *ethernet_detect(struct bus_lst *bus);

/*floppy.c*/
extern struct floppy_info *floppy_detect(struct bus_lst *bus);

/*isdn.c*/
extern struct isdn_info *isdn_detect(struct bus_lst *bus);

/*others.c*/
extern struct others_info *others_detect(struct bus_lst *bus);

/*printer.c*/
extern struct printer_info *printer_detect(struct bus_lst *bus);

/*scanner.c*/
extern struct scanner_info *scanner_detect(struct bus_lst *bus);

/*soundcard.c*/
extern struct soundcard_info *soundcard_detect(struct bus_lst *bus);

/*tape.c*/
extern struct tape_info *tape_detect(struct bus_lst *bus);

/*video.c*/
extern struct video_info *video_detect(struct bus_lst *bus);

/*tvcard.c*/
extern struct tvcard_info *tvcard_detect(struct bus_lst *bus);

/*usb.c*/
extern struct usb_info *usb_detect(struct cards_lst *but);
extern struct usbntf_info *usbinterface_detect(struct bus_lst *bus);

/*webcam.c*/
extern struct webcam_info *webcam_detect(struct bus_lst *bus);


/*calls.c*/
extern int exec_detect_helper(char *path, char *args[], 
                                char **out, char **err);
extern int check_helper_version(char *path, 
                                int major, int minor, int patch);
extern char *exec_modprobe(char *modulename, char *tmpconfmodule);

/*conv.c*/
extern DeviceType pciclass2device(int class);
extern DeviceType pcmciaclass2device(unsigned char class);
extern DeviceType usbclass2device(unsigned char class);

extern char *bus2str(BusType bus);
extern BusType str2bus(char *str);
    
extern DeviceType str2device(char *str);
extern char *device2str(DeviceType type);
extern char *device2text(DeviceType type);

extern unsigned int str2options(char *str);
extern char *options2str(unsigned int options);

extern char *trim(char *str);

/*bus.c*/
extern struct bus_lst *init_bus(struct cards_lst *lst);


/*lst.c*/
extern struct cards_lst *init_lst(char *isa_lst, 
                                char *pci_lst, 
                                char *pcmcia_lst,
                                char *usb_lst);
#endif
