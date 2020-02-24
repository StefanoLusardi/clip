#pragma once

#if defined(_MSC_VER) && (defined(_WIN32) || defined(_WIN64))
	#define CLIP_IMPORT __declspec(dllimport)
	#define CLIP_EXPORT __declspec(dllexport)
#else
	#if __GNUC__ >= 4
		#define CLIP_IMPORT __attribute__ ((visibility ("default")))
		#define CLIP_EXPORT __attribute__ ((visibility ("default")))
	#else
		#define CLIP_IMPORT
		#define CLIP_EXPORT
	#endif
#endif

#if defined(CLIP_COMPILED_LIB)
	#define CLIP_API CLIP_EXPORT
#else
	#define CLIP_API CLIP_IMPORT
#endif