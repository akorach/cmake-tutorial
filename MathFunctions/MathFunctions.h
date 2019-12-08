#if defined(_WIN32)
#  if defined(EXPORTING_MYMATH)
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows
#  define DECLSPEC
#endif

/// The above can probably be accomplished by setting the WINDOWS_EXPORT_ALL_SYMBOLS property on the lib target,
/// but I couldn't be bothered to check :P

namespace MathFunctions {

double DECLSPEC sqrt(double x);

}
