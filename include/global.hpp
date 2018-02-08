#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#define CFG_FRAMEWORK_NAME "eMBPTA"
#define CFG_FRAMEWORK_VERSION "0.1"

#ifdef GIT_VERSION
#define CFG_FRAMEWORK_GIT_VERSION GIT_VERSION
#else
#define CFG_FRAMEWORK_GIT_VERSION "unknown"
#endif

#ifdef VERBOSITY_NONE
#define VERB(x)
#else
#define VERB(x) x
#endif

#endif
