#include <cstdio>
#include <cstdlib>
#include <fstream>

#include <argparse.h>

#include <bind_logger.hpp>
#include <bind_processor.hpp>
#include <bind_platform.hpp>
#include <bind_filesystem.hpp>
#include <bind_template.hpp>
#include <bind_args.hpp>
#include <bind_javascript.hpp>
#include <bind_system.hpp>
#include <bind_terminal.hpp>

#define CUTE_FILES_IMPLEMENTATION

DUK_CPP_DEF_CLASS_NAME(LoggerBinder::Log);
DUK_CPP_DEF_CLASS_NAME(ProcessorBinder::Process);
DUK_CPP_DEF_CLASS_NAME(PlatformBinder::Info);
DUK_CPP_DEF_CLASS_NAME(FileSystemBinder::Directory);
DUK_CPP_DEF_CLASS_NAME(FileSystemBinder::Path);
DUK_CPP_DEF_CLASS_NAME(TemplateBinder::Template);
DUK_CPP_DEF_CLASS_NAME(ArgsBinder::Args);
DUK_CPP_DEF_CLASS_NAME(JavascriptBinder::Javascript);
DUK_CPP_DEF_CLASS_NAME(SystemBinder::System);
DUK_CPP_DEF_CLASS_NAME(TerminalBinder::Terminal);

//using namespace argparse;

int main(int argc, const char** argv)
{
	duk::Context ctx;

	try {
	    const char *VERSION = "2.0.0";

		const char *input_filename = nullptr;
		const char *extra_arguments = nullptr;

		const char *logo = "\n"
		"	     @@@   @@@@@@   @@@@@@@@@@    @@@@@@   @@@  @@@  @@@@@@@@\n"
		"	     @@@  @@@@@@@   @@@@@@@@@@@  @@@@@@@@  @@@  @@@  @@@@@@@@\n"
		"	     @@!  !@@       @@! @@! @@!  @@!  @@@  @@!  !@@  @@!     \n"
		"	     !@!  !@!       !@! !@! !@!  !@!  @!@  !@!  @!!  !@!     \n"
		"	     !!@  !!@@!!    @!! !!@ @!@  @!@!@!@!  @!@@!@!   @!!!:!  \n" 
		"	     !!!   !!@!!!   !@!   ! !@!  !!!@!!!!  !!@!!!    !!!!!:  \n"
		"	     !!:       !:!  !!:     !!:  !!:  !!!  !!: :!!   !!:     \n"
		"	!!:  :!:      !:!   :!:     :!:  :!:  !:!  :!:  !:!  :!:     \n"
		"	::: : ::  :::: ::   :::     ::   ::   :::   ::  :::   :: ::::\n"
		"	 : :::    :: : :     :      :     :   : :   :   :::  : :: ::\n";

	    struct argparse_option options[] = {
	        OPT_HELP(),
	        OPT_STRING('i', "input", &input_filename, "input filename (default Makefile.js)", nullptr, 0, 0),
	        OPT_STRING('a', "arguments", &extra_arguments, "pass arguments to the script", nullptr, 0, 0),
	        OPT_END(),
	    };
		static const char *const usages[] = {
			"jsmake [options]",
			nullptr,
		};

		struct argparse argparse;
		argparse_init(&argparse, options, usages, 0);
		argparse_describe(&argparse, logo, nullptr);
		argc = argparse_parse(&argparse, argc, argv);

		ctx.registerClass<LoggerBinder::Log>();
		ctx.registerClass<ProcessorBinder::Process>();
		ctx.registerClass<PlatformBinder::Info>();
		ctx.registerClass<FileSystemBinder::Directory>();
		ctx.registerClass<FileSystemBinder::Path>();
		ctx.registerClass<TemplateBinder::Template>();
		ctx.registerClass<ArgsBinder::Args>();
		ctx.registerClass<JavascriptBinder::Javascript>();
		ctx.registerClass<SystemBinder::System>();
		ctx.registerClass<TerminalBinder::Terminal>();

		ctx.evalStringNoRes("var Log = new LoggerBinder.Log()");
		ctx.evalStringNoRes("var Processor = new ProcessorBinder.Process()");
		ctx.evalStringNoRes("var Platform = new PlatformBinder.Info()");
		ctx.evalStringNoRes("var Directory = new FileSystemBinder.Directory()");
		ctx.evalStringNoRes("var Path = new FileSystemBinder.Path()");
		ctx.evalStringNoRes("var Template = new TemplateBinder.Template()");
		ctx.evalStringNoRes("var Args = new ArgsBinder.Args()");
		ctx.evalStringNoRes("var Js = new JavascriptBinder.Javascript()");
        ctx.evalStringNoRes("var System = new SystemBinder.System()");
        ctx.evalStringNoRes("var Terminal = new TerminalBinder.Terminal()");

		std::shared_ptr<LoggerBinder::Log> log;
		ctx.getGlobal("Log", log);
		assert(log);

		std::shared_ptr<ProcessorBinder::Process> processor;
		ctx.getGlobal("Processor", processor);
		assert(processor);

		std::shared_ptr<PlatformBinder::Info> platform;
		ctx.getGlobal("Platform", platform);
		assert(platform);

		std::shared_ptr<FileSystemBinder::Directory> directory;
		ctx.getGlobal("Directory", directory);
		assert(directory);

		std::shared_ptr<FileSystemBinder::Path> path;
		ctx.getGlobal("Path", path);
		assert(path);

		std::shared_ptr<TemplateBinder::Template> jstemplate;
		ctx.getGlobal("Template", jstemplate);
		assert(jstemplate);

		std::shared_ptr<ArgsBinder::Args> jsargs;
		ctx.getGlobal("Args", jsargs);
		assert(jsargs);
		if (extra_arguments != nullptr) {
		    jsargs->SetCommandLine(extra_arguments);
		}

		std::shared_ptr<JavascriptBinder::Javascript> jsscript;
		ctx.getGlobal("Js", jsscript);
		assert(jsscript);
		jsscript->Initialize(&ctx);

        std::shared_ptr<SystemBinder::System> system;
        ctx.getGlobal("System", system);
        assert(system);

        std::shared_ptr<TerminalBinder::Terminal> terminal;
        ctx.getGlobal("Terminal", terminal);
        assert(terminal);

        if (input_filename == nullptr) {
             input_filename = "Makefile.js";
		}
		int result = cf_file_exists(input_filename);
		if (result == 0) {
			std::cout << "File '" << input_filename << "' not found." << std::endl;
			exit(1);
		}

		std::ifstream t(input_filename);
		std::string code((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

		ctx.evalStringNoRes(code.c_str());

	} catch (duk::ScriptEvaluationExcepton &e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
