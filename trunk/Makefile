USE_SETUPDB = true

SETUPDB_DIR = ../setupdb

BUILD_DIR = build
SCRIPT_DIR = scripts
KEY_DIR = keys

# FIXME: This needs to be able to read from host.def somehow. Hnngh.

KEY_NAME = yoyodyne_key.pub

.PHONY : all

# FIXME: sidebar.png should be declared in host.def somewhere.

all : 	$(BUILD_DIR) \
	$(BUILD_DIR)/lst \
	$(BUILD_DIR)/detect \
	$(BUILD_DIR)/qagent_en.qm \
	$(BUILD_DIR)/encrypt_gpg.sh \
	$(BUILD_DIR)/gldump.sh \
	$(BUILD_DIR)/hwdump.sh \
	$(BUILD_DIR)/netdump.sh \
	$(BUILD_DIR)/procdump.sh \
	$(BUILD_DIR)/md5sum.sh \
	$(BUILD_DIR)/md5sum \
	$(BUILD_DIR)/sidebar.png \
	$(BUILD_DIR)/qagent.sh \
	$(BUILD_DIR)/rpmdump.sh \
	$(BUILD_DIR)/stackdump.sh \
	$(BUILD_DIR)/transport_file.sh \
	$(BUILD_DIR)/transport_mail.sh \
	$(BUILD_DIR)/xinfo.sh \
	$(BUILD_DIR)/qagent \
	$(BUILD_DIR)/privacy.txt \
	$(BUILD_DIR)/$(KEY_NAME)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

#FIXME: file name should be declared in host.def.
#FIXME: do we care?

.PRECIOUS : qt_gui/%.qm qt_gui/%.ts

$(BUILD_DIR)/sidebar.png : data/sidebar.png
	cp data/sidebar.png $(BUILD_DIR)/sidebar.png

$(BUILD_DIR)/privacy.txt : data/privacy.txt
	cp data/privacy.txt $(BUILD_DIR)/privacy.txt

$(BUILD_DIR)/detect: hacked_detect/detect.c hacked_detect/report.c
	cd hacked_detect && make && cp detect ../$(BUILD_DIR) && cd ..

$(BUILD_DIR)/lst: hacked_detect/lst/pci.lst hacked_detect/lst/isa.lst \
	hacked_detect/lst/pcmcia.lst hacked_detect/lst/usb.lst
	cp -r hacked_detect/lst $(BUILD_DIR)/lst

$(SCRIPT_DIR)/encrypt_gpg.sh: $(SCRIPT_DIR)/gen_encrypt_gpg.sh host.def
	cd $(SCRIPT_DIR) && ./gen_encrypt_gpg.sh && cd ..

$(SCRIPT_DIR)/transport_mail.sh : $(SCRIPT_DIR)/gen_transport_mail.sh host.def
	cd $(SCRIPT_DIR) && ./gen_transport_mail.sh && cd ..

$(BUILD_DIR)/%.qm : qt_gui/%.qm
	cp $< $@

qt_gui/%.qm : qt_gui/%.ts
	cd qt_gui && make qmfiles && cd ..

qt_gui/%.ts :
	cd qt_gui && make tsfiles && cd ..

$(BUILD_DIR)/%.sh : $(SCRIPT_DIR)/%.sh
	cp $< $@

$(BUILD_DIR)/$(KEY_NAME): $(KEY_DIR)/$(KEY_NAME)
	cp $< $@

$(KEY_DIR)/$(KEY_NAME):
	echo "WARNING: KEY NOT FOUND, TRYING TO CALL GENERATION SCRIPT"
	cd $(KEY_DIR) && ./gen_key.sh cd ..
	
$(BUILD_DIR)/qagent: qt_gui/*.cpp qt_gui/*.h host.def
	cd qt_gui && make && cd ..
	cp qt_gui/qagent build/ && cd ..

$(BUILD_DIR)/md5sum: $(SETUPDB_DIR)/md5sum
	cp $(SETUPDB_DIR)/md5sum $(BUILD_DIR)

$(SETUPDB_DIR)/md5sum : $(SETUPDB_DIR)/md5.c
	cd $(SETUPDB_DIR) && make md5sum

clean:
	rm -rf build
	cd qt_gui && make clean && cd ..
	cd hacked_detect && make clean && cd ..
	cd scripts && rm transport_mail.sh && rm encrypt_gpg.sh
