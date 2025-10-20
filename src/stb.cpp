/* *
 *	By defining STB_IMAGE_IMPLEMENTATION the preprocessor modifies the header file
 *	such that it only contains the relevant definition source code.
 *
 *	#define STB_IMAGE_IMPLEMENTATION
 *	#include <stb/stb_image.h>
 * */

#define STB_IMAGE_IMPLEMENTATION
#include<stb/stb_image.h>
#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include <stb/stb_truetype.h>