
#ifndef _SCROBBLER_ERRORS_H
#define _SCROBBLER_ERRORS_H

class EScrobbler {
public:
	EScrobbler(){};
	~EScrobbler(){};

	const char *getText() const { return "Unknown Error"; }
};

class EOutOfMemory : public EScrobbler {
public:
	const char *getText() const { return "Out of Memory"; }
};

#endif

