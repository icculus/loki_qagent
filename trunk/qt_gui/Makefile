include ../host.def

uifiles = qagent.ui

gen_hdrs = $(uifiles:.ui=.h)
gen_srcs = $(uifiles:.ui=.cpp)

new_hdrs =
new_srcs = main.cpp x_utils.cpp utils.cpp qt_gui.cpp console_gui.cpp \
	KDE/kprocctrl.cpp KDE/kprocess.cpp

moc_srcs = qagentimpl.moc.cpp qagent.moc.cpp KDE/kprocctrl.moc.cpp KDE/kprocess.moc.cpp

gen_impl_hdrs=qagentimpl.h
gen_impl_srcs=qagentimpl.cpp

hdrs = $(gen_hdrs) $(new_hdrs) $(gen_impl_hdrs)
srcs = $(moc_srcs) $(gen_srcs) $(new_srcs) $(gen_impl_srcs)

CC = gcc
CPP = gcc
UIC = /usr/local/src/qt/bin/uic
MOC = /usr/bin/moc
LIBFLAGS = -lqt -L$(QTDIR)/lib
INCLUDEFLAGS = -I$(QTDIR)/include

VERSION = 0.0.1

WARNFLAG = 

DEBUGFLAGS = -g

# Turn this on if you want to turn QAgent into a babbling idiot..

DEBUGFLAGS += -DVERBOSE

objects = $(srcs:.cpp=.o) getline.o

CFLAGS = -pipe -I/usr/local/include $(WARNFLAG) $(DEBUGFLAGS) -I/usr/X11R6/include $(INCLUDEFLAGS) 
CPPFLAGS = -pipe -I/usr/local/include -I/usr/X11R6/include $(WARNFLAG) $(DEBUGFLAGS) $(INCLUDEFLAGS)

ifeq ($(ENABLE_SETUPDB),true)
CFLAGS += -DENABLE_SETUPDB
CPPFLAGS += -DENABLE_SETUPDB
LIBFLAGS += ../../setupdb/x86/libsetupdb.a -lxml
endif

.PRECIOUS: %.h %.moc.cpp %.cpp %impl.h %impl.cpp

qagent : $(objects)
	$(CPP) -pipe -g -o qagent $(objects) $(LIBFLAGS)

%.moc.cpp: %.h
	$(MOC) -o $@ $<

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@	

%.o : %.cpp host_def.h
	$(CPP) -c $(CPPFLAGS) $< -o $@

%.moc.cpp: %.h
	$(MOC) -o $@ $<

%.h : %.ui
	$(UIC) -o $@ $<

host_def.h: ../host.def
	./gen_host_def_h.sh

%.cpp : %.ui %.h
	$(UIC) -i $(<:.ui=.h) -o $@ $<

clean:
	rm qagent $(objects) $(gen_srcs) host_def.h

real-clean:
	rm qagent $(objects) $(moc_srcs) host_def.h

# Be VERY careful with these guys if you choose to uncomment them;
# they basically give Make the power to fsck you over. I will not
# be held responsible, either. -- n.

#%impl.cpp : %impl.h
#	$(UIC) -o $@ -subimpl $(<:impl.h=Impl) $< $(<:impl.h=.ui)

#%impl.h : %.h
#	$(UIC) -o $@ -subdecl $(<:.h=Impl) $< $(<:.h=.ui)
	
all : qagent
