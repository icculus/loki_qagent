// An unabashed hack of Mandrake's detect.c. Blggggphbbt. -- n.
// Later modified to dump XML. Even MORE Blggggphbbt. -- n.

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
/*    fprintf(report, "# %s:%s:%s:%s:[%s]:%s:%s\n",
            ToUpper(device2str(CPU)),
            _("vendor"),
            _("model"),
            _("frequency"),
            _("flags"),
            _("bogomips"),
            _("bugs"));
*/
	fprintf (report, 
		"<cpu>\n<vendor>%s</vendor>\n<model>%s</model>\n<frequency>%i</frequency>\n<flags>%s</flags>\n<bogomips>%s</bogomips>\n<bugs>%s</bugs>\n</cpu>\n",
            _("vendor"),
            _("model"),
            _("frequency"),
            _("flags"),
            _("bogomips"),
            _("bugs"));

  }/*endif*/
  for(; cpu; cpu = cpu->next){
	fprintf (report, 
		"<cpu>\n<name>%s</name>\n<vendor>%s</vendor>\n<model>%s</model>\n<frequency>%i</frequency>\n<flags>%s</flags>\n<bogomips>%s</bogomips>\n<bugs>%s</bugs>\n</cpu>\n",
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
  memory = memory_detect();
  fprintf(report, 
  "<memory>\n<total>%d</total>\n<free>%d</free>\n<shared>%d</shared>\n<buffers>%d</buffers>\n<cached>%d</cached>\n<swap_free>%d</swap_free>\n<swap_total>%d</swap_total>\n</memory>\n",
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
    fprintf(report,
     "<bridge><bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<module>%s</module>\n</bridge>\n", 
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; bridge; bridge = bridge->next){
    fprintf(report,
     "<bridge><bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<module>%s</module>\n</bridge>\n", 
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
    fprintf(report, "<ide>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<module>%s</module>\n</ide>\n", 
            ToUpper(device2str(IDEINTERFACE)),
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; ideinterface; ideinterface = ideinterface->next){
    fprintf(report, "<ide>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<module>%s</module>\n</ide>\n", 
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
    fprintf(report, "<scsi>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<module>%s</module>\n</scsi>\n", 
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; scsiinterface; scsiinterface = scsiinterface->next){
    fprintf(report, "<scsi>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<module>%s</module>\n</scsi>\n", 
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
    fprintf(report, "<usb>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<module>%s</module>\n</usb>\n", 
            _("bus"),
            _("vendor"),
            _("model"),
            _("module"));
  }/*endif*/
  for(; usbinterface; usbinterface = usbinterface->next){
    fprintf(report, "<usb>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<module>%s</module>\n</usb>\n", 
            bus2str(usbinterface->bus), 
            usbinterface->vendor, 
            usbinterface->model,
            usbinterface->module);
  }/*next usbinterface*/
  
  /********************************************************************/
  /* report hard disk(s)                                              */
  /********************************************************************/
  if(((disk = disk_detect(bus)) != NULL) &&(verbose == 1)){
	fprintf(report,"<harddisk>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<device>%s</device>\n<size>%s</size>\n<heads>%i</heads>\n<sectors>%i</sectors>\n<cylinders>%i</cylinders>\n</harddisk>\n",
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
	fprintf(report,"<harddisk>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<device>%s</device>\n<size>%s</size>\n<heads>%i</heads>\n<sectors>%i</sectors>\n<cylinders>%i</cylinders>\n</harddisk>\n",
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
  for(; floppy; floppy = floppy->next){
	fprintf(report,"<floppy>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<device>%s</device>\n</floppy>\n",
            bus2str(floppy->bus), 
            floppy->vendor, 
            floppy->model, 
            floppy->device);
  }/*next floppy*/
    
  /********************************************************************/
  /* report CD drive(s)                                               */
  /********************************************************************/
 if ((cdrom = cdrom_detect(bus)) != NULL)
 {
  for(; cdrom; cdrom = cdrom->next){
	fprintf(report,"<cdrom>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<device>%s</device>\n</cdrom>\n",
            bus2str(cdrom->bus),
            cdrom->vendor,
            cdrom->model,
            cdrom->device);
  }/*next cdrom*/
 } 
  /********************************************************************/
  /* report video card(s)                                             */
  /********************************************************************/
  if((video = video_detect(bus)) != NULL)
  {
  for(; video; video = video->next){
	fprintf(report,"<videocard>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<server>%s</server>\n<memory>%d</memory>\n<ramdac>%s</ramdac>\n<clock>%s</clock>\n</videocard>\n",
            bus2str(video->bus), 
            video->vendor, 
            video->model,
            video->server,
            video->memory,
            video->ramdac,
            video->clockchip);
  }/*next video*/
  }  
  /********************************************************************/
  /* report ethernet card(s)                                          */
  /********************************************************************/
  if((ethernet = ethernet_detect(bus)) != NULL)
  {
  for(; ethernet; ethernet = ethernet->next){
	fprintf(report,"<ethernet>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<module>%s</module>\n</ethernet>\n",
            bus2str(ethernet->bus), 
            ethernet->vendor, 
            ethernet->model,
            ethernet->module);
  }/*next ethernet*/
  }
  /********************************************************************/
  /* report sound card(s)                                             */
  /********************************************************************/
  if((sound = soundcard_detect(bus)) != NULL)
  {
   for(; sound; sound = sound->next){
	fprintf(report,"<sound>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<options>%s</options>\n</sound>\n",
            bus2str(sound->bus),  
            sound->vendor, 
            sound->model, 
            options2str(sound->options),
            sound->module);
  }/*next sound*/
  }
  
  /********************************************************************/
  /* report mices                                                     */
  /********************************************************************/
  if((mouse = mouse_detect(bus)) != NULL)
  {
  	for(; mouse; mouse = mouse->next){
   		fprintf(report, 
"<mouse>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<model>%s</model>\n<device>%s</device>\n</mouse>\n", 
            		bus2str(mouse->bus),
            		mouse->vendor,
            		mouse->model,
            		mouse->device);
  	}/*next mouse*/
  }
  
  /********************************************************************/
  /* report joystick(s)                                               */
  /********************************************************************/
  if((joystick = joystick_detect(bus)) != NULL)
  {
  	for(; joystick; joystick = joystick->next){
    		fprintf(report, "<joystick>\n<bus>%s</bus>\n<vendor>%s</vendor>\n<device>%s</device>\n<module>%s</module>\n</joystick>\n", 
            		ToUpper(device2str(JOYSTICK)),
            		bus2str(joystick->bus),
            		joystick->vendor,
            		joystick->model,
            		joystick->device,
            		joystick->module);
  	}/*next joystick*/
  }


  /********************************************************************/
  /* finally we have detected all hardware :-)                        */
  /********************************************************************/
  fclose(report);
}/*endfunc report_verbose_detect*/

	