#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <streambuf>

#include <argparse.h>
#include <duktape.h>

#include <bind_logger.hpp>
#include <bind_processor.hpp>
#include <bind_platform.hpp>
#include <bind_filesystem.hpp>
#include <bind_template.hpp>
#include <bind_args.hpp>

#define CUTE_FILES_IMPLEMENTATION
#include <cute_files.h>

DUK_CPP_DEF_CLASS_NAME(Logger::Log);
DUK_CPP_DEF_CLASS_NAME(Processor::Process);
DUK_CPP_DEF_CLASS_NAME(Platform::Info);
DUK_CPP_DEF_CLASS_NAME(FileSystem::Directory);
DUK_CPP_DEF_CLASS_NAME(FileSystem::Path);
DUK_CPP_DEF_CLASS_NAME(TemplateEngine::Template);
DUK_CPP_DEF_CLASS_NAME(ArgsEngine::Args);

//using namespace argparse;

int main(int argc, const char** argv)
{
	duk::Context ctx;

	try {

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
	        OPT_STRING('i', "input", &input_filename, "input filename (default Makefile.js)", NULL, 0, 0),
	        OPT_STRING('a', "arguments", &extra_arguments, "pass arguments to the script", NULL, 0, 0),
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

		ctx.registerClass<Logger::Log>();
		ctx.registerClass<Processor::Process>();
		ctx.registerClass<Platform::Info>();
		ctx.registerClass<FileSystem::Directory>();
		ctx.registerClass<FileSystem::Path>();
		ctx.registerClass<TemplateEngine::Template>();
		ctx.registerClass<ArgsEngine::Args>();

		ctx.evalStringNoRes("var Logger = new Logger.Log()");
		ctx.evalStringNoRes("var Processor = new Processor.Process()");
		ctx.evalStringNoRes("var Platform = new Platform.Info()");
		ctx.evalStringNoRes("var Directory = new FileSystem.Directory()");
		ctx.evalStringNoRes("var Path = new FileSystem.Path()");
		ctx.evalStringNoRes("var Template = new TemplateEngine.Template();");
		ctx.evalStringNoRes("var Args = new ArgsEngine.Args();");

		std::shared_ptr<Logger::Log> logger;
		ctx.getGlobal("Logger", logger);
		assert(logger);

		std::shared_ptr<Processor::Process> processor;
		ctx.getGlobal("Processor", processor);
		assert(processor);

		std::shared_ptr<Platform::Info> platform;
		ctx.getGlobal("Platform", platform);
		assert(platform);

		std::shared_ptr<FileSystem::Directory> directory;
		ctx.getGlobal("Directory", directory);
		assert(directory);

		std::shared_ptr<FileSystem::Path> path;
		ctx.getGlobal("Path", path);
		assert(path);

		std::shared_ptr<TemplateEngine::Template> jstemplate;
		ctx.getGlobal("Template", jstemplate);
		assert(jstemplate);

		std::shared_ptr<ArgsEngine::Args> jsargs; 
		ctx.getGlobal("Args", jsargs);
		assert(jsargs);
		if (extra_arguments != nullptr) {
		    jsargs->SetCommandLine(extra_arguments);
		    jsargs->AddOption('x',"extra","extra parameters for JS");
            jsargs->AddOption('f',"fake","fake parameter");
            jsargs->Parse();
            //jsargs->GetOption('x');
		}

		std::cout << "?????????????????????????????????????????????????" << std::endl;

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
