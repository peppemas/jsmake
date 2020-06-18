#include <argparse.h>

namespace ArgsEngine {

	class Args {
		private:
		public:
			explicit Args() {}

			void Test(int argc, const char** argv) {
			}

		    /**
		     * Inspect method defines class meta information (methods, properties etc..)
		     * You can define `inspect` method inline or specialize `duk::Inspect` for your class
		     */
		    template <class Inspector>
		    static void inspect(Inspector &i) 
		    {
		        i.construct(&std::make_shared<Args>);
		    }
	};

}