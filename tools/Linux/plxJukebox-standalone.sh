#!/bin/sh

prefix="/usr/local"
exec_prefix="${prefix}"
bindir="${exec_prefix}/bin"
XBMC="${bindir}/plxJukebox --standalone $@"

PULSE_START="$(which start-pulseaudio-x11)"
if [ -n "$PULSE_START" ]; then
  $PULSE_START
else
  PULSE_SESSION="$(which pulse-session)"
  if [ -n "$PULSE_SESSION" ]; then
    XBMC="$PULSE_SESSION $XBMC"
  fi
fi

LOOP=1
CRASHCOUNT=0
LASTSUCCESSFULSTART=$(date +%s)

while [ $(( $LOOP )) = "1" ]
do
  $XBMC
  RET=$?
  NOW=$(date +%s)
  if [ $(( ($RET >= 64 && $RET <=66) || $RET == 0 )) = "1" ]; then # clean exit
    LOOP=0
  else # crash
    DIFF=$((NOW-LASTSUCCESSFULSTART))
    if [ $(($DIFF > 60 )) = "1" ]; then # Not on startup, ignore
      LASTSUCESSFULSTART=$NOW
      CRASHCOUNT=0
    else # at startup, look sharp
      CRASHCOUNT=$((CRASHCOUNT+1))
      if [ $(($CRASHCOUNT >= 3)) = "1" ]; then # Too many, bail out
        LOOP=0
        echo "PleXus Jukebox has exited uncleanly 3 times in the last ${DIFF} seconds."
        echo "Something is probably wrong"
      fi
    fi
  fi
done
