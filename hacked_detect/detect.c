// An unabashed hack of Mandrake's detect.c. Blggggphbbt. -- n.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "detect.h"
#include "utils.h"

// HACK!

#define verbose (0)

int main ( void ) {

  
  struct cards_lst *lst = (struct cards_lst *)NULL;
  struct bus_lst *bus = (struct bus_lst *)NULL;
  
  struct cpu_info *cpu = (struct cpu_info *)NULL;
  struct memory_info *memory = (struct memory_info *)NULL;
  struct bridge_info *bridge = (struct bridge_info *)NULL;
  struct floppy_info *floppy = (struct floppy_info *)NULL;
  struct disk_info *disk = (struct disk_info *)NULL;
  struct cdrom_info *cdrom = (struct cdrom_info *)NULL;
  struct tape_info *tape = (struct tape_info *)NULL;
  struct ethernet_info *ethernet = (struct ethernet_info *)NULL;
  struct modem_info *modem = (struct modem_info *)NULL;
  struct isdn_info *isdn = (struct isdn_info *)NULL;
  struct video_info *video = (struct video_info *)NULL;
  struct tvcard_info *tvcard = (struct tvcard_info *)NULL;
  struct soundcard_info *sound = (struct soundcard_info *)NULL;
  struct printer_info *printer = (struct printer_info *)NULL;
  struct scanner_info *scanner = (struct scanner_info *)NULL;
  struct webcam_info *webcam = (struct webcam_info *)NULL;
  struct mouse_info *mouse = (struct mouse_info *)NULL;
  struct joystick_info *joystick = (struct joystick_info *)NULL;
  struct serial_info *serial = (struct serial_info *)NULL;
  struct parallel_info *parallel = (struct parallel_info *)NULL;
  struct gameport_info *gameport = (struct gameport_info *)NULL;
  struct others_info *others = (struct others_info *)NULL;

  struct identf_info *ideinterface = (struct identf_info *)NULL;
  struct scsintf_info *scsiinterface = (struct scsintf_info *)NULL;
  struct usbntf_info *usbinterface = (struct usbntf_info *)NULL;
  
#ifdef HAVE_LIBISAPNP
  int irqs[16];
  int dmas[8];
  int i;
#endif

  FILE *report;

  /* sync before all                                                  */
  /* Shoudl be called in all programs linked with detect ...          */
  sync();
  
  report = stdout;

  /* Initialize hardware device list                                  */
  lst = init_lst("./lst/isa.lst", "./lst/pci.lst", "./lst/pcmcia.lst", "./lst/usb.lst");
  bus = init_bus(lst);
  
  /********************************************************************/
  /* report CPU(s)                                                    */
  /********************************************************************/
  if(((cpu = cpu_detect()) != NULL) && (verbose == 1)){
    fprintf(report, "# %s:%s:%s:%s:[%s]:%s:%s\n",
            ToUpper(device2str(CPU)),
            _("vendor"),
            _("model"),
            _("frequency"),
            _("flags"),
            _("bogomips"),
            _("bugs"));
  }/*endif*/
  for(; cpu; cpu = cpu->next){
    fprintf(report, "%s:%s:%s:%d:%s:%s:%s\n",
            ToUpper(device2str(CPU)),
            cpu->vendor, 
            cpu->model, 
            cpu->freq, 
            options2str(cpu->options),
            cpu->bogomips, 
            cpu->bugs);
  }/*next cpu*/
  
  /********************************************************************/
  /* report memory                                                    */
  /********************************************************************/
  if(verbose == 1){
    fprintf(report, "\n# %s:%s:%s:%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(MEMORY)),
            _("total"),
            _("free"),
            _("shared"),
            _("buffers"),
            _("cached"),
            _("free_swap"),
            _("total_swap"));
  }/*endif*/
  memory = memory_detect();
  fprintf(report, "%s:%d:%d:%d:%d:%d:%d:%d\n", 
          ToUpper(device2str(MEMORY)),
          memory->total, 
          memory->free, 
          memory->shared, 
          memory->buffers, 
          memory->cached,
          memory->swap_free, 
          memory->swap_total);


  /********************************************************************/
  /* report BRIDGE(s)                                                 */
  /********************************************************************/
  if(((bridge = bridge_detect(bus)) != NULL) && 
     (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(BRIDGE)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; bridge; bridge = bridge->next){
    fprintf(report, "%s:%s:%s:%s:%s\n",
            ToUpper(device2str(BRIDGE)),
            bus2str(bridge->bus), 
            bridge->vendor, 
            bridge->model,
            bridge->module);
  }/*next bridge*/


  
  /********************************************************************/
  /* report IDE-interface(s)                                          */
  /********************************************************************/
  if(((ideinterface = ideinterface_detect(bus)) != NULL) && 
     (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(IDEINTERFACE)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; ideinterface; ideinterface = ideinterface->next){
    fprintf(report, "%s:%s:%s:%s:%s\n",
            ToUpper(device2str(IDEINTERFACE)),
            bus2str(ideinterface->bus), 
            ideinterface->vendor, 
            ideinterface->model,
            ideinterface->module);
  }/*next ideinterface*/
  
  /********************************************************************/
  /* report SCSI-interface(s)                                         */
  /********************************************************************/
  if(((scsiinterface = scsiinterface_detect(bus)) != NULL) && 
                                                        (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(SCSIINTERFACE)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; scsiinterface; scsiinterface = scsiinterface->next){
    fprintf(report, "%s:%s:%s:%s:%s\n",
            ToUpper(device2str(SCSIINTERFACE)),
            bus2str(scsiinterface->bus), 
            scsiinterface->vendor, 
            scsiinterface->model,
            scsiinterface->module);
  }/*next scsiinterface*/
  
  /********************************************************************/
  /* report USB-interface(s)                                          */
  /********************************************************************/
  if(((usbinterface = usbinterface_detect(bus)) != NULL) && 
                                                        (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(USBINTERFACE)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; usbinterface; usbinterface = usbinterface->next){
    fprintf(report, "%s:%s:%s:%s:%s\n",
            ToUpper(device2str(USBINTERFACE)),
            bus2str(usbinterface->bus), 
            usbinterface->vendor, 
            usbinterface->model,
            usbinterface->module);
  }/*next usbinterface*/
  
  /********************************************************************/
  /* report hard disk(s)                                              */
  /********************************************************************/
  if(((disk = disk_detect(bus)) != NULL) &&(verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(DISK)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("device"),
            _("size(512k-blocks)"),
            _("heads"),
            _("sectors"),
            _("cylinders"));
  }/*endif*/
  for(; disk; disk = disk->next){
    fprintf(report, "%s:%s:%s:%s:%s:%d:%d:%d:%d\n", 
            ToUpper(device2str(DISK)),
            bus2str(disk->bus),
            disk->vendor,
            disk->model,
            disk->device,
            disk->size,
            disk->heads,
            disk->sectors,
            disk->cylinders);
  }/*next disk*/
  
  /********************************************************************/
  /* report flopy disk drive(s)                                       */
  /********************************************************************/
  if(((floppy = floppy_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(FLOPPY)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("device"));
  }/*endif*/
  for(; floppy; floppy = floppy->next){
    fprintf(report, "%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(FLOPPY)),
            bus2str(floppy->bus), 
            floppy->vendor, 
            floppy->model, 
            floppy->device);
  }/*next floppy*/
    
  /********************************************************************/
  /* report CD drive(s)                                               */
  /********************************************************************/
  if(((cdrom = cdrom_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(CDROM)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("device"));
  }/*endif*/
  for(; cdrom; cdrom = cdrom->next){
    fprintf(report, "%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(CDROM)),
            bus2str(cdrom->bus),
            cdrom->vendor,
            cdrom->model,
            cdrom->device);
  }/*next cdrom*/
  
  /********************************************************************/
  /* report tape(s)                                                   */
  /********************************************************************/
  if(((tape = tape_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(TAPE)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("device"));
  }/*endif*/
  for(; tape; tape = tape->next){
    fprintf(report, "%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(TAPE)),
            bus2str(tape->bus),
            tape->vendor,
            tape->model,
            tape->device);
  }/*next tape*/
  
  /********************************************************************/
  /* report scanner                                                   */
  /********************************************************************/
  if(((scanner = scanner_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(SCANNER)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("device"));
  }/*endif*/
  for(; scanner; scanner = scanner->next){
    fprintf(report, "%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(SCANNER)),
            bus2str(scanner->bus),
            scanner->vendor,
            scanner->model,
           scanner->device);
  }/*next scanner*/
  

  /********************************************************************/
  /* report webcam(s)                                                 */
  /********************************************************************/
  if(((webcam = webcam_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(WEBCAM)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("device"));
  }/*endif*/
  for(; webcam; webcam = webcam->next){
    fprintf(report, "%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(WEBCAM)),
            bus2str(webcam->bus),
            webcam->vendor,
            webcam->model,
            webcam->device);
  }/*next webcam*/


  /********************************************************************/
  /* report video card(s)                                             */
  /********************************************************************/
  if(((video = video_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(VIDEOCARD)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("server"),
            _("memory"),
            _("ramdac"),
            _("clockchip"));
  }/*endif*/
  for(; video; video = video->next){
    fprintf(report, "%s:%s:%s:%s:[%s]:%d:%s:%s\n", 
            ToUpper(device2str(VIDEOCARD)),
            bus2str(video->bus), 
            video->vendor, 
            video->model,
            video->server,
            video->memory,
            video->ramdac,
            video->clockchip);
  }/*next video*/
  
  /********************************************************************/
  /* report ethernet card(s)                                          */
  /********************************************************************/
  if(((ethernet = ethernet_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(ETHERNETCARD)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; ethernet; ethernet = ethernet->next){
    fprintf(report, "%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(ETHERNETCARD)),
            bus2str(ethernet->bus), 
            ethernet->vendor, 
            ethernet->model,
            ethernet->module);
  }/*next ethernet*/
  
  /********************************************************************/
  /* report sound card(s)                                             */
  /********************************************************************/
  if(((sound = soundcard_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:[%s]:%s\n", 
            ToUpper(device2str(SOUNDCARD)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("flags"),
            _("module"));
  }/*endif*/
  for(; sound; sound = sound->next){
    fprintf(report, "%s:%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(SOUNDCARD)),
            bus2str(sound->bus),  
            sound->vendor, 
            sound->model, 
            options2str(sound->options),
            sound->module);
  }/*next sound*/
  
  /********************************************************************/
  /* report tvcards                                                   */
  /********************************************************************/
  if(((tvcard = tvcard_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(TVCARD)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; tvcard; tvcard = tvcard->next){
    fprintf(report, "%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(TVCARD)),
            bus2str(tvcard->bus),
            tvcard->vendor,
            tvcard->model,
            tvcard->module);
  }/*next tvcard*/
  
  /********************************************************************/
  /* report mices                                                     */
  /********************************************************************/
  if(((mouse = mouse_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(MOUSE)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("device"));
  }/*endif*/
  for(; mouse; mouse = mouse->next){
    fprintf(report, "%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(MOUSE)),
            bus2str(mouse->bus),
            mouse->vendor,
            mouse->model,
            mouse->device);
  }/*next mouse*/
  
  /********************************************************************/
  /* report joystick(s)                                               */
  /********************************************************************/
  if(((joystick = joystick_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(JOYSTICK)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("device"),
            _("module"));
  }/*endif*/
  for(; joystick; joystick = joystick->next){
    fprintf(report, "%s:%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(JOYSTICK)),
            bus2str(joystick->bus),
            joystick->vendor,
            joystick->model,
            joystick->device,
            joystick->module);
  }/*next joystick*/
  
  /********************************************************************/
  /* report modem(s)                                                  */
  /********************************************************************/
  if(((modem = modem_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s:%s:%s\n",
            ToUpper(device2str(MODEM)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("device"),
            _("speed"),
            _("module"));
  }/*endif*/
  for(; modem; modem = modem->next){
    fprintf(report, "%s:%s:%s:%s:%s:%ld:%s\n",
            ToUpper(device2str(MODEM)),
            bus2str(modem->bus),
            modem->vendor, 
            modem->model,
            modem->device,
            modem->speed,
            modem->module);
  }/*next modem*/
  
  /********************************************************************/
  /* report isdn adpaters                                             */
  /********************************************************************/
  if(((isdn = isdn_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(ISDN)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; isdn; isdn = isdn->next){
    fprintf(report, "%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(ISDN)),
            bus2str(isdn->bus),
            isdn->vendor, 
            isdn->model,
            isdn->module);
  }/*next isdn*/
  
  /********************************************************************/
  /* report parallel port(s)                                          */
  /********************************************************************/
  if(((parallel = bus->parallel) != NULL) && (verbose == 1)){
    fprintf(report, "\n# PARALLEL:%s:%s\n", 
            _("device"),
            _("DOS_equivalent"));
  }/*endif*/
  for(; parallel; parallel=parallel->next){
    fprintf(report, "PARALLEL:%s:%s\n", 
            parallel->device,
            parallel->dos_equivalent);
  }/*next parallel*/
  
  /********************************************************************/
  /* report serial port(s)                                            */
  /********************************************************************/
  if(((serial = bus->serial) != NULL) && (verbose == 1)){
    fprintf(report, "\n# SERIAL:%s:%s\n", 
            _("device"),
            _("DOS_equivalent"));
  }/*endif*/
  for(; serial; serial=serial->next){
    fprintf(report, "SERIAL:%s:%s\n", 
            serial->device,
            serial->dos_equivalent);
  }/*next serial*/
  
  /********************************************************************/
  /* report game port(s)                                              */
  /********************************************************************/
  if(((gameport = gameport_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# GAMEPORT:%s:%s\n", 
            _("vendor"),
            _("model"));
  }/*endif*/
  for(; gameport; gameport=gameport->next){
    fprintf(report, "GAMEPORT:%s:%s\n", 
            gameport->vendor,
            gameport->model);
  }/*next gameport*/
  
  /********************************************************************/
  /* report printer(s)                                                */
  /********************************************************************/
  if(((printer = printer_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s\n", 
            ToUpper(device2str(PRINTER)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("device"));
  }/*endif*/
  for(; printer; printer=printer->next){
    fprintf(report, "%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(PRINTER)),
            bus2str(printer->bus),
            printer->vendor,
            printer->model,
            printer->device);
  }/*next printer*/
  
  /********************************************************************/
  /* report other(s)                                                  */
  /********************************************************************/
  if(((others = others_detect(bus)) != NULL) && (verbose == 1)){
    fprintf(report, "\n# %s:%s:%s:%s:%s:%s\n", 
            ToUpper(device2str(OTHERS)),
            _("ID"),
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; others; others=others->next){
    if((others->bus == ISA) || (others->bus == SERIAL)){
      fprintf(report, "%s:%s:%s:%s:%s:%s\n", 
              ToUpper(device2str(OTHERS)),
              others->dev_id,
              bus2str(others->bus), 
              others->vendor, 
              others->model,
              others->module);
    }else{
      fprintf(report, "%s:%08lx:%s:%s:%s:%s\n",  
              ToUpper(device2str(OTHERS)),
              others->long_id,
              bus2str(others->bus),
              others->vendor,
              others->model,
              others->module);
    }/*endif*/
  }/*next others*/


#ifdef HAVE_LIBISAPNP
  if(free_irqs_dmas_detect(irqs, dmas) == 0){
    /******************************************************************/
    /* report free IRQ(s)                                             */
    /******************************************************************/
    if(verbose == 1){
      fprintf(report, "\n# FREE_IRQS:[%s:]\n", 
              _("IRQ"));
    }/*endif*/
    fprintf(report, "FREE_IRQS:");
    for(i = 0; irqs[i] != -1; i++){
      fprintf(report, "%d:", irqs[i]);
    }/*next i*/
    fprintf(report, "\n");

    /******************************************************************/
    /* report free DMA(s)                                             */
    /******************************************************************/
    if(verbose == 1){
      fprintf(report, "\n# FREE_DMAS:[%s:]\n", 
              _("DMA"));
    }/*endif*/
    fprintf(report, "FREE_DMAS:");
    for(i = 0; dmas[i] != -1; i++){
      fprintf(report, "%d:", dmas[i]);
    }/*next i*/
  }else{
    fprintf(report, 
          "\n# Got some errors reporting FREE_IRQS and FREE_DMAS!!!\n");
  }/*endif*/
#endif

  /********************************************************************/
  /* finally we have detected all hardware :-)                        */
  /********************************************************************/
  fclose(report);
}/*endfunc report_verbose_detect*/

	