#ifndef UNITTEST_CONFIG_H
#define UNITTEST_CONFIG_H

#ifdef _MSC_VER
#   define VISUAL_STUDIO
#   if _MSC_VER == 1310
#       define VISUAL_STUDIO_2003
#   elif _MSC_VER == 1400
#       define VISUAL_STUDIO_2005
#   endif
#endif

#ifdef LINUX
#endif

#endif
