

#ifndef status_indicator_h
#define status_indicator_h


// initialise the status led
void init_status_indicator(void);

// turn on the error light and write error flag
void mark_as_error(void);

// turn off error light and green ligt on. removes flags.
void release_error(void);

#endif