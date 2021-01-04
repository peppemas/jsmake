/***************************************************
 *
 * JSMAKEFILE Script Test
 * 
 * Copyright (C) 2020 Victrix Games
 *
 ***************************************************/

var platform = "You are running on ";

function title(str)
{
	Log.info("------------------------------------------");
	Log.info(str);
	Log.info("------------------------------------------");
}

// ----------------------------------------------------------------------- Test Processor
title("Test Processor");
Log.info("Who Am I ???");
var proc_result = Processor.run("whoami");
var proc_output = Processor.getOutput();
Log.warn("["+ proc_result + "]: " + proc_output);
proc_result = Processor.run("thisprocessnotexists");
proc_output = Processor.getError();
Log.warn("["+ proc_result + "]: " + proc_output);

// ----------------------------------------------------------------------- Test Args
title("Test Args");
if (Args.exists("-o")) {
	Log.info("Parameter -o exists.");
	var value = Args.get("-o");
	Log.info("Value of -o :" + value);
} else {
	Log.error("Parameter -o not exists.");
}

// ----------------------------------------------------------------------- Test Platform
title("Test Platform");
if (Platform.isWindows()) {
	platform += "Windows"; 
	if (Platform.isWindows64()) {
		platform += " (64bit)";
	}
} else if (Platform.isLinux()) {
	platform += "Linux";
} else if (Platform.isMacOS()) {
	platform += "MacOS";
}
Log.info(platform);

// ----------------------------------------------------------------------- Test Collect Files
title("Test Collect Files");
var FILES = Directory.collectAllFiles(".",true,false);
Log.info("This directory contains " + FILES.length + " file(s)");

// ----------------------------------------------------------------------- Test Colors
title("Test Terminal Colors");

Log.blank();
Log.info("==================================================");
Log.warn("This is a Warning Message");
Log.error("This is an Error Message");
Log.bold("This is a Bold Message");
// NOTE: With colors you have to add manually the \n to end the line
Log.red("red\n");
Log.grey("grey\n");
Log.green("green\n");
Log.yellow("yellow\n");
Log.blue("blue\n");
Log.magenta("magenta\n");
Log.cyan("cyan\n");
Log.white("white\n");
Log.oncyan("on cyan\n");
Log.ongrey("on grey\n");
Log.ongreen("on green\n");
Log.onred("on red\n");
Log.onblue("on blue\n");
Log.info("==================================================");

// ----------------------------------------------------------------------- Test Template Engine
title("Test Template Engine");

var template_vars = { "name":"John", "surname": "Smith" }; 
var template_vars2 = {}; 
var template_vars3 = { 
	"guests": [ "Gaia", "Ann", "Toby", "Patricia", "John" ],
	"availableRooms" : [ 12, 24, 35 ],
	"time": {
		"start":"10.10.2020", 
		"end":"21.10.2020"
	}
};
 
Log.blank();
var template_result = Template.render("Hello {{name}} {{surname}} !!!", JSON.stringify(template_vars));
Log.info(template_result);

var template_result2 = Template.render("{% for i in range(4) %}{{ loop.index1 }}{% endfor %}", JSON.stringify(template_vars2));
Log.info(template_result2);

var template_result3 = Template.render("I count {{ length(guests) }} guests", JSON.stringify(template_vars3)); 
Log.info(template_result3);

var template_result4 = Template.render("The second guest is {{ guests.2 }}", JSON.stringify(template_vars3)); 
Log.info(template_result4);

var template_result5 = Template.render("Time start {{ time.start }}", JSON.stringify(template_vars3)); 
Log.info(template_result5);

var template_result6 = Template.render("{% if \"Peppe\" in guests %}I found Peppe{% else %}Cannot find Peppe{% endif %}", JSON.stringify(template_vars3));
Log.info(template_result6);

var template_result7 = Template.render("{% if \"Gaia\" in guests %}I found Gaia{% else %}Cannot find Gaia{% endif %}", JSON.stringify(template_vars3));
Log.info(template_result7);

// ----------------------------------------------------------------------- Directory Operations
title("Test Directory Operations");

Log.info("The current Directory is: ");
var currentDir = Directory.getCurrent();
Log.warn(currentDir);

Log.info("Create directory ciccio");
var result = Directory.make("ciccio");

Log.info("Change current directory to ciccio");
Directory.setCurrent("./ciccio");
Log.warn(Directory.getCurrent());

Log.info("Return to previous directory");
Directory.setCurrent(currentDir);

Log.warn("Delete directory ciccio");
Directory.remove("./ciccio");

// ----------------------------------------------------------------------- File Operations
title("Test File Operations");

Log.bold("Write a file");
Directory.writeTextFile("ciccio.txt","this is the content for ciccio.txt:\nHello World!!!");

Log.info("Read the text file");
var content = Directory.readTextFile("ciccio.txt");
Log.info(content);

title("Read the file line by line");
var arrayContent = Directory.readLineByLine("ciccio.txt");
Log.warn("the file contains: " + arrayContent.length + " lines.");
Log.info("add a line between...");
if (arrayContent.length === 2) {
	arrayContent.splice(1, 0, "\nthis is a patch line.\n");	// NOTE: pay attention to newline for formatting
}
Log.info("now the array contains " + arrayContent.length + " lines.");
Log.info("the content is now:")
Log.warn(arrayContent.join(""));

title("Read the file line by line (test #2)");
arrayContent = Directory.readLineByLine("../test/test_include.js");
for (var i=0; i<arrayContent.length; i++) {
	if (arrayContent[i] === "function test_include() {") {
		Log.warn("line found!");
	}
	Log.info(arrayContent[i]);
}

if (Directory.exists("../test/test_include.js")) {
	Log.info("test_include.js exists");
	var filetime = Directory.fileTime("../test/test_include.js");
	Log.info("File was modified at: " + filetime);
}
if (!Directory.exists("not_exists.txt")) {
	Log.warn("note_exists.txt ... not exists!");
}

// ----------------------------------------------------------------------- Include
title("Test Include");

Directory.setCurrent("../test/");
Js.include("test_include.js");
test_include();
Directory.setCurrent(currentDir);

// ----------------------------------------------------------------------- System
title("Test System");

var ENVPATH = System.env("PATH");
Log.info("Current Environment PATH:");
Log.info(ENVPATH);

// ----------------------------------------------------------------------- Terminal
title("Test Terminal");

var name = Terminal.prompt("Please enter your name: ");
Log.warn("Hello  " + name + "!" );
