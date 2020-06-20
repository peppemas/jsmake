/***************************************************
 *
 * JSMAKEFILE Compilation Script Test
 * 
 * Copyright (C) 2020 Victrix Games
 *
 ***************************************************/

var platform = "You are running on ";

// ----------------------------------------------------------------------- Test Platform

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
Logger.info(platform);

// ----------------------------------------------------------------------- Test Collect Files

var FILES = Directory.collectAllFiles(".",true,false); 
Logger.info("This directory contains " + FILES.length + " file(s)");

// ----------------------------------------------------------------------- Test Colors

Logger.blank();
Logger.info("==================================================");
Logger.warn("This is a Warning Message");
Logger.error("This is an Error Message");
Logger.info("==================================================");

// ----------------------------------------------------------------------- Test Template Engine

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
 
Logger.blank();
var template_result = Template.render("Hello {{name}} {{surname}} !!!", JSON.stringify(template_vars));
Logger.info(template_result);

var template_result2 = Template.render("{% for i in range(4) %}{{ loop.index1 }}{% endfor %}", JSON.stringify(template_vars2));
Logger.info(template_result2);

var template_result3 = Template.render("I count {{ length(guests) }} guests", JSON.stringify(template_vars3)); 
Logger.info(template_result3);

var template_result4 = Template.render("The second guest is {{ guests.2 }}", JSON.stringify(template_vars3)); 
Logger.info(template_result4);

var template_result5 = Template.render("Time start {{ time.start }}", JSON.stringify(template_vars3)); 
Logger.info(template_result5);

var template_result6 = Template.render("{% if \"Peppe\" in guests %}I found Peppe{% else %}Cannot find Peppe{% endif %}", JSON.stringify(template_vars3));
Logger.info(template_result6);

var template_result7 = Template.render("{% if \"Gaia\" in guests %}I found Gaia{% else %}Cannot find Gaia{% endif %}", JSON.stringify(template_vars3));
Logger.info(template_result7);

// ----------------------------------------------------------------------- Directory Operations

Logger.info("The current Directory is: ");
var currentDir = Directory.getCurrent();
Logger.warn(currentDir);

Logger.info("Create directory ciccio");
var result = Directory.make("ciccio");

Logger.info("Change current directory to ciccio");
Directory.setCurrent("./ciccio");
Logger.warn(Directory.getCurrent());

Logger.info("Return to previous directory");
Directory.setCurrent(currentDir);

Logger.warn("Delete directory ciccio");
Directory.remove("./ciccio");

// ----------------------------------------------------------------------- File Operations
