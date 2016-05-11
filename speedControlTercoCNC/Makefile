
TARGET         = speedControlTercoCNC
MCU            = atmega328p
AVRTYPE        = __AVR_ATmega328__
F_CPU          = 16000000
ARDUINO_PORT   = /dev/ttyUSB0
AVRDUDE_ARD_PROGRAMMER = arduino
AVRDUDE_ARD_BAUDRATE   = 57600

ARDUINO_DIR    = /usr/share/arduino
AVR_TOOLS_PATH = /usr/bin

ARDUINO_CORE_PATH = $(ARDUINO_DIR)/hardware/arduino/cores/arduino
ARDUINO_VAR_PATH = $(ARDUINO_DIR)/hardware/arduino/variants/standard
ARDUINO_LIBS_PATH = $(ARDUINO_DIR)/libraries

ARDUINO_LIBS = \
	Wire \
	Wire/utility

LOCAL_LIBS = \
	LiquidCrystal_I2C

########################################################################
# Do not print commands override with make Q=
########################################################################
Q       ?= @

########################################################################
# Names of executables
########################################################################

CC      = $(AVR_TOOLS_PATH)/avr-gcc
CXX     = $(AVR_TOOLS_PATH)/avr-g++
OBJCOPY = $(AVR_TOOLS_PATH)/avr-objcopy
OBJDUMP = $(AVR_TOOLS_PATH)/avr-objdump
AR      = $(AVR_TOOLS_PATH)/avr-ar
SIZE    = $(AVR_TOOLS_PATH)/avr-size
NM      = $(AVR_TOOLS_PATH)/avr-nm
MKDIR   = mkdir
REMOVE  = rm -f
RMDIR   = rmdir
MV      = mv -f
CP      = cp
TOUCH   = touch
CAT     = cat
ECHO    = echo

PDEHEADER  = \\\#include \"Arduino.h\"

########################################################################
# Everything gets built in here
########################################################################

BUILDDIR   = build

########################################################################
# Targets
########################################################################

TARGET_HEX = $(BUILDDIR)/$(TARGET).hex
TARGET_EEP = $(BUILDDIR)/$(TARGET).eep
TARGET_ELF = $(BUILDDIR)/$(TARGET).elf
TARGET_CPP = $(BUILDDIR)/$(TARGET).cpp
TARGET_C   = $(BUILDDIR)/$(TARGET).c
TARGET_O   = $(BUILDDIR)/$(TARGET).o
TARGET_INO = $(TARGET).ino
TARGETS    = $(BUILDDIR)/$(TARGET).*

########################################################################
# Local files
########################################################################

LOCAL_C_SRCS    = $(wildcard *.c)
LOCAL_CPP_SRCS  = $(wildcard *.cpp)
LOCAL_CC_SRCS   = $(wildcard *.cc)
LOCAL_INO_SRCS  = $(wildcard *.ino)
LOCAL_AS_SRCS   = $(wildcard *.s)
LOCAL_OBJ_FILES = $(LOCAL_C_SRCS:.c=.o) $(LOCAL_CPP_SRCS:.cpp=.o) \
			$(LOCAL_CC_SRCS:.cc=.o) $(LOCAL_INO_SRCS:.ino=.o) \
			$(LOCAL_AS_SRCS:.S=.o)
LOCAL_OBJS      = $(patsubst %,$(BUILDDIR)/%,$(LOCAL_OBJ_FILES))

########################################################################
# Core files
########################################################################

CORE_NAME       = core
CORE_C_SRCS     = $(wildcard $(ARDUINO_CORE_PATH)/*.c)
CORE_CPP_SRCS   = $(wildcard $(ARDUINO_CORE_PATH)/*.cpp)
CORE_OBJ_FILES  = $(CORE_C_SRCS:.c=.o) $(CORE_CPP_SRCS:.cpp=.o)
CORE_OBJS       = $(patsubst $(ARDUINO_CORE_PATH)/%, \
			$(BUILDDIR)/%,$(CORE_OBJ_FILES))
CORE_LIB        = $(BUILDDIR)/lib$(CORE_NAME).a

########################################################################
# System Library files
########################################################################

SYSLIB_NAME      = syslib
SYSLIB_DIRS      = $(patsubst %,$(ARDUINO_LIBS_PATH)/%,$(ARDUINO_LIBS))
SYSLIB_C_SRCS    = $(wildcard $(patsubst %,%/*.c,$(SYSLIB_DIRS)))
SYSLIB_CPP_SRCS  = $(wildcard $(patsubst %,%/*.cpp,$(SYSLIB_DIRS)))
SYSLIB_SRCS      = $(SYSLIB_C_SRCS) $(SYSLIB_CPP_SRCS)
SYSLIB_OBJ_FILES = $(notdir $(SYSLIB_C_SRCS:.c=.o) $(SYSLIB_CPP_SRCS:.cpp=.o))
SYSLIB_OBJS      = $(patsubst %,$(BUILDDIR)/%,$(SYSLIB_OBJ_FILES))
SYSLIB_LIB       = $(BUILDDIR)/lib$(SYSLIB_NAME).a

########################################################################
# Local Library files
########################################################################

LIBS_NAME       = libs
LIBS_DIRS      = $(patsubst %,../libraries/%,$(LOCAL_LIBS))
LIBS_C_SRCS    = $(wildcard $(patsubst %,%/*.c,$(LIBS_DIRS)))
LIBS_CPP_SRCS  = $(wildcard $(patsubst %,%/*.cpp,$(LIBS_DIRS)))
#LIBS_DIRS       = $(wildcard ../libraries/*)
#LIBS_C_SRCS     = $(wildcard ../libraries/*/*.c)
#LIBS_CPP_SRCS   = $(wildcard ../libraries/*/*.cpp)
LIBS_SRCS       = $(LIBS_C_SRCS) $(LIBS_CPP_SRCS)
LIBS_OBJ_FILES  = $(notdir $(LIBS_C_SRCS:.c=.o) $(LIBS_CPP_SRCS:.cpp=.o))
LIBS_OBJS       = $(patsubst %,$(BUILDDIR)/%,$(LIBS_OBJ_FILES))
LIBS_LIB        = $(BUILDDIR)/lib$(LIBS_NAME).a

########################################################################
# Include dirs
########################################################################

CORE_INCLUDES   = $(ARDUINO_CORE_PATH)
VAR_INCLUDES    = $(ARDUINO_VAR_PATH)
SYSLIB_INCLUDES = $(patsubst %,-I%,$(SYSLIB_DIRS))
LIB_INCLUDES    = $(patsubst %,-I%,$(LIBS_DIRS))

VPATH = $(LIBS_DIRS) $(SYSLIB_DIRS) $(ARDUINO_CORE_PATH)

########################################################################
# Flags
########################################################################

CPPFLAGS      = -mmcu=$(MCU) \
		-D$(AVRTYPE) \
		-DF_CPU=$(F_CPU) \
		-I. \
		-I$(ARDUINO_VAR_PATH) \
		-I$(ARDUINO_CORE_PATH) \
		$(SYSLIB_INCLUDES) \
		$(LIB_INCLUDES) \
		-DARDUINO=105 \
		-g -Os -w -Wall \
		-ffunction-sections \
		-fshort-enums \
		-fpack-struct \
		-fdata-sections
#LISTING       = -Wa,-acdhmnls
LISTING       = -Wa,-acdhlmns
CFLAGS        = -std=gnu99
CXXFLAGS      = -fno-exceptions
ASFLAGS       = -mmcu=$(MCU) -I. -x assembler-with-cpp
LDFLAGS       = -mmcu=$(MCU) -lm -Wl,--gc-sections -Os

all: $(TARGET_EEP) $(TARGET_HEX)

docs:
	cd ..; doxygen

########################################################################
# Rules to make build dirs
########################################################################

$(BUILDDIR):
	@$(ECHO) "[  MKD  ] ==> $@"
	$(Q)$(MKDIR) -p $@

OBJS          = $(LOCAL_OBJS) $(CORE_OBJS) $(LIBS_OBJS) $(SYSLIB_OBJS)

$(OBJS):       | $(BUILDDIR)

$(TARGET_CPP): $(TARGET_INO)

########################################################################
# Rules to build local files
########################################################################

$(BUILDDIR)/%.o: %.c
	@$(ECHO) "[  C    ] ==> $@"
	$(Q)$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LISTING)=$(patsubst %.o,%.lst,$@)

$(BUILDDIR)/%.o: %.cc
	@$(ECHO) "[  CPP  ] ==> $@"
	$(Q)$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LISTING)=$(patsubst %.o,%.lst,$@)

$(BUILDDIR)/%.o: %.cpp 
	@$(ECHO) "[  CPP  ] ==> $@"
	$(Q)$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LISTING)=$(patsubst %.o,%.lst,$@)

$(BUILDDIR)/%.o: %.S
	@$(ECHO) "[  S    ] ==> $@"
	$(Q)$(CC) -c $(CPPFLAGS) $(ASFLAGS) $< -o $@ $(LISTING)=$(patsubst %.o,%.lst,$@)

$(BUILDDIR)/%.o: %.s
	@$(ECHO) "[  S    ] ==> $@"
	$(Q)$(CC) -c $(CPPFLAGS) $(ASFLAGS) $< -o $@ $(LISTING)=$(patsubst %.o,%.lst,$@)

########################################################################
# Rules to build ino -> cpp -> o file
########################################################################

$(BUILDDIR)/%.cpp: %.ino
	@$(ECHO) "[  INO  ] ==> $@"
	$(Q)$(ECHO) $(PDEHEADER) > $@
	$(Q)$(CAT)  $< >> $@

$(BUILDDIR)/%.o: $(BUILDDIR)/%.c
	@$(ECHO) "[  C    ] ==> $@"
	$(Q)$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LISTING)=$(patsubst %.o,%.lst,$@)

$(BUILDDIR)/%.o: $(BUILDDIR)/%.cpp
	@$(ECHO) "[  CPP  ] ==> $@"
	$(Q)$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@ $(LISTING)=$(patsubst %.o,%.lst,$@)

$(BUILDDIR)/%.hex: $(BUILDDIR)/%.elf
	@$(ECHO) "[  ELF  ] ==> $@"
	$(Q)$(OBJCOPY) \
		-O ihex \
		-R .eeprom $< $@
	$(Q)$(SIZE) -d --target=ihex $@

$(BUILDDIR)/%.eep: $(BUILDDIR)/%.elf
	@$(ECHO) "[  ELF  ] ==> $@"
	$(Q)$(OBJCOPY) \
		-O ihex \
		-j .eeprom \
		--no-change-warnings \
		--set-section-flags=.eeprom="alloc,load" \
		--change-section-lma \
		.eeprom=0 $< $@

$(TARGET_ELF): $(CORE_LIB) $(SYSLIB_LIB) $(LIBS_LIB) $(LOCAL_OBJS)
	@$(ECHO) "[  LNK  ] ==> $@"
	$(Q)$(CC) $(LDFLAGS) -o $@ $(LOCAL_OBJS) -l$(LIBS_NAME) -l$(SYSLIB_NAME) -l$(CORE_NAME) -L$(BUILDDIR) -Wl,-Map=linker.map
	$(Q)$(SIZE) $@

########################################################################
# Rules to build library files
########################################################################

$(CORE_LIB): $(CORE_OBJS)
	@$(ECHO) "[  AR   ] ==> $@"
	$(Q)$(AR) rcs $(CORE_LIB) $(CORE_OBJS)

$(SYSLIB_LIB): $(SYSLIB_OBJS)
	@$(ECHO) "[  AR   ] ==> $@"
	$(Q)$(AR) rcs $(SYSLIB_LIB) $(SYSLIB_OBJS)

$(LIBS_LIB): $(LIBS_OBJS)
	@$(ECHO) "[  AR   ] ==> $@"
	$(Q)$(AR) rcs $(LIBS_LIB) $(LIBS_OBJS)

core: $(CORE_LIB)

syslibs: $(SYSLIB_LIB)

libs: $(LIBS_LIB)

########################################################################
# Explicit targets
########################################################################

clean:
	@$(ECHO) "[  RM   ] ==> $@"
	$(Q)$(REMOVE) \
		$(TARGETS) $(LOCAL_OBJS) $(LIBS_OBJS) $(LIBS_LIB) linker.map

mrproper: | $(BUILDDIR)
	@$(ECHO) "[  RM   ] ==> $@"
	$(Q)$(REMOVE) \
		$(CORE_LIB) $(SYSLIB_LIB) $(LIBS_LIB) \
		$(LOCAL_OBJS) $(CORE_OBJS) $(SYSLIB_OBJS) $(LIBS_OBJS) \
		$(TARGETS) \
		$(BUILDDIR)/*.lst \
		linker.map
	$(Q)rmdir $(BUILDDIR)


AVRDUDE          = $(AVR_TOOLS_PATH)/avrdude
AVRDUDE_COM_OPTS = -p $(MCU)
ifdef AVRDUDE_CONF
AVRDUDE_COM_OPTS += -C $(AVRDUDE_CONF)
endif

AVRDUDE_ARD_OPTS = -q -D -c $(AVRDUDE_ARD_PROGRAMMER) \
			-b $(AVRDUDE_ARD_BAUDRATE) \
			-P $(ARDUINO_PORT)

upload:		raw_upload

raw_upload:	$(TARGET_HEX) $(TARGET_EEP)
		sudo $(AVRDUDE) -v $(AVRDUDE_COM_OPTS) $(AVRDUDE_ARD_OPTS) \
			-U flash:w:$(TARGET_HEX):i

setfuses:
		sudo $(AVRDUDE) -v $(AVRDUDE_COM_OPTS) $(AVRDUDE_ARD_OPTS) \
			-U lfuse:w:0xe2:m -U hfuse:w:0xd7:m -U efuse:w:0xff:m

fuses:
		sudo $(AVRDUDE) -v $(AVRDUDE_COM_OPTS) $(AVRDUDE_ARD_OPTS) \
			-U lfuse:r:-:i

eeprom: $(TARGET_EEP)
		sudo $(AVRDUDE) -v $(AVRDUDE_COM_OPTS) $(AVRDUDE_ARD_OPTS) \
			-U eeprom:w:$(TARGET_EEP):i
# stty on MacOS likes -F, but on Debian it likes -f redirecting
# stdin/out appears to work but generates a spurious error on MacOS at
# least. Perhaps it would be better to just do it in perl ?
reset:		
		for STTYF in 'stty --file' 'stty -f' 'stty <' ; \
		  do $$STTYF /dev/tty >/dev/null 2>/dev/null && break ; \
		done ;\
		$$STTYF $(ARD_PORT)  hupcl ;\
		#(sleep 0.1 || sleep 1)     ;\
		$$STTYF $(ARD_PORT) -hupcl 
