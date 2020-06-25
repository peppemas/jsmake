#pragma once

#include <memory>
#include <iostream>

#include <duktape-cpp/DuktapeCpp.h>

namespace PlatformBinder {

	class Info {
		public:
			explicit Info() {}

			bool IsWindows()
			{
				#if defined(_WIN32) 
					return true; 
				#else
					return false;
				#endif
			} 

			bool IsWindows64() 
			{
				#if defined(_WIN64)
					return true;
				#else
					return false;
				#endif
			}

			bool IsLinux()
			{
				#if defined(__linux__)
					return true;
				#else
					return false;
				#endif
			}

			bool IsMacOS() 
			{
				#if defined(__APPLE__) && defined(__MACH__)
					return true;
				#else
					return false;
				#endif
			}

			bool IsIOS() 
			{
				#if defined(__APPLE__) && defined(__MACH__)
					#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
						return true;
					#else
						return false;
					#endif
				#else
					return false;
				#endif
			}

			bool IsFreeBSD() 
			{
				#if defined(__FreeBSD__) 
					return true;
				#else
					return false;
				#endif
			}

			bool IsAndroid()
			{
				#if defined(__ANDROID__) 
					return true;
				#else
					return false;
				#endif
			}

		    /**
		     * Inspect method defines class meta information (methods, properties etc..)
		     * You can define `inspect` method inline or specialize `duk::Inspect` for your class
		     */
		    template <class Inspector>
		    static void inspect(Inspector &i) 
		    {
		        i.construct(&std::make_shared<Info>);
		        i.method("isWindows", &Info::IsWindows);
		        i.method("isWindows64", &Info::IsWindows64);
		        i.method("isLinux", &Info::IsLinux);
		        i.method("isMacOS", &Info::IsMacOS);
		        i.method("isFreeBSD", &Info::IsFreeBSD);
		        i.method("isAndroid", &Info::IsAndroid);
		        i.method("isIOS", &Info::IsIOS);
		    }
	};

}

