SRCS=JukeboxManager.cpp \
     ProfessionalDatabase.cpp \
     StatsDatabase.cpp  \
     ReportsManager.cpp	  \
     CryptoManager.cpp  \
     CoinsManager.cpp  \
     PartyModeManager.cpp  \
     RandomManager.cpp
     
LIB=jukebox.a

#Laureon: this is just to remember what we need!!
LIBS+=-lcryptopp
INCLUDES+=-I/usr/include/cryptopp

include ../../Makefile.include
-include $(patsubst %.cpp,%.P,$(patsubst %.c,%.P,$(SRCS)))
