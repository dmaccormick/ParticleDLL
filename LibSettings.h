#ifndef LIBSETTINGS_H
#define LIBSETTINGS_H

#ifdef A2_EXPORTS
#define LIB_API __declspec(dllexport)
#elif A2_IMPORTS
#define LIB_API __declspec(dllimport)
#else
#define LIB_API
#endif

#endif
